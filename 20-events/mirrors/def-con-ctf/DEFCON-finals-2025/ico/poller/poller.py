#!/usr/bin/env python3

import hashlib
import nautpolling
from nautpolling import player_print, nautilus_print, accept, reject
from nautpolling import nautilus_print as print  # So we don't screw anything up
import os
import random
import struct
import time

from pwn import *

HOST = os.environ.get('HOST', '127.0.0.1')
PORT = os.environ.get('PORT', 4265)

MAX_IMAGES = 16
PATCH_BUDGET = 2048
FILE_PATH = 'app/ico'

REQUEST = {
    'connect': b'\x10',
    'disconnect': b'\x11',
    'current_image': b'\x20',
    'select_image': b'\x21',
    'create_image': b'\x22',
    'destroy_image': b'\x23',
    'load_image': b'\x24',
    'store_image': b'\x25',
    'duplicate_image': b'\x26',
    'get_comment': b'\x30',
    'set_comment': b'\x31',
    'render_image': b'\x32',
    'get_styles': b'\x40',
    'get_style': b'\x41',
    'set_style': b'\x42',
    'add_style': b'\x43',
    'remove_style': b'\x44',
    'is_flat': b'\x45',
    'is_transparent': b'\x46',
    'get_color': b'\x47',
    'set_color': b'\x48',
    'get_gradient': b'\x49',
    'set_gradient': b'\x4a',
    'set_step': b'\x4b',
    'add_step': b'\x4c',
    'remove_step': b'\x4d',
    'get_gradient_transformer': b'\x4e',
    'set_gradient_transformer': b'\x4f',
    'get_paths': b'\x60',
    'get_path': b'\x61',
    'set_path': b'\x62',
    'add_path': b'\x63',
    'remove_path': b'\x64',
    'get_point': b'\x65',
    'set_point': b'\x66',
    'add_point': b'\x67',
    'remove_point': b'\x68',
    'get_shapes': b'\x80',
    'get_shape': b'\x81',
    'set_shape': b'\x82',
    'add_shape': b'\x83',
    'remove_shape': b'\x84',
    'get_shape_style': b'\x85',
    'set_shape_style': b'\x86',
    'get_shape_paths': b'\x87',
    'set_shape_paths': b'\x88',
    'add_shape_path': b'\x89',
    'remove_shape_path': b'\x8a',
    'has_hinting': b'\x8b',
    'set_hinting': b'\x8c',
    'get_min_visibility': b'\x90',
    'set_min_visibility': b'\x91',
    'get_max_visibility': b'\x92',
    'set_max_visibility': b'\x93',
    'get_transformers': b'\x94',
    'get_transformer': b'\x95',
    'set_transformer': b'\x96',
    'add_transformer': b'\x97',
    'remove_transformer': b'\x98'
}

RESPONSE_ACK = b'\x00'
RESPONSE_SCS = b'\x01'
RESPONSE_FAL = b'\x02'
RESPONSE_RES = b'\x04'

class Poller:
    def __init__(self, host, port):
        self.host = host
        self.port = port
        self.socket = None
        self.selected = 0
        self.image_count = 0
        self.flag_hash = self._create_flag_hash().upper()
        print(self.flag_hash)

    def _assert(self, expect, recvd, msg=""):
        if recvd != expect:
            reject(player_message=f"Assertion failed: {msg}")

    def _assert_not(self, bad, recvd, msg=""):
        if recvd == bad:
            reject(player_message=f"Assertion failed: {msg}")

    def _send_blob(self, blob):
        self.socket.send(struct.pack('<H', len(blob)))
        self.socket.send(blob)

    def _recv_blob(self):
        size_bytes = self.socket.recvn(2)
        if not size_bytes: return b''
        size = struct.unpack('<H', size_bytes)[0]
        return self.socket.recvn(size)

    def _byte_diff_count(self, original: bytes, patched: bytes) -> int:
        diff = sum(b1 != b2 for b1, b2 in zip(original, patched))
        diff += abs(len(original) - len(patched))
        return diff

    def _create_flag_hash(self) -> str:
        # load the flag from /flag
        with open('/flag', 'r') as flag_file:
            flag_content = flag_file.read().strip("\n")

        return hashlib.md5(flag_content.encode()).hexdigest()

    def check_files(self):
        # Read in the challenge binary from disk
        original = None
        try:
            with open('/opt/ico', 'rb') as f:
                original = f.read()
                nautilus_print(f"Read file /opt/ico (size: {len(original)})")
        except FileNotFoundError:
            reject(player_message="Challenge file not found. Poller is broken. Contact us immediately.")
        except Exception as e:
            nautilus_print(f"Error while reading challenge file: {e}")
            reject(player_message="Error while reading challenge file. Poller is broken. Contact us immediately.")

        # Read list of patched files
        patched_dir = nautpolling.load_patched_image()
        print(f"patched_dir: {patched_dir=}")

        # Make sure players don't delete any files from the base image
        deleted_files = nautpolling.get_deleted_files()
        if deleted_files and len(deleted_files) != 0:
            reject(player_message="Cannot delete files")

        # Make sure players don't change any files other than the service
        changed_files = nautpolling.get_modified_files()
        nautilus_print(f"{changed_files=}")
        if not changed_files:
            return
        if len(changed_files) == 0:
            return
        if len(changed_files) != 1:
            reject(player_message="May only patch the service itself")
        if not FILE_PATH in changed_files:
            reject(player_message="May only patch the service itself")

        # Read in file from patched directory
        patched_file = patched_dir + os.sep + FILE_PATH
        patched = None
        try:
            with open(patched_file, 'rb') as f:
                patched = f.read()
                nautilus_print(f"Read file {patched_file} (size: {len(patched)})")
        except FileNotFoundError:
            reject(player_message="Failed to read patched file. Poller is broken. Contact us immediately.")
        except Exception as e:
            nautilus_print(f"Error while reading patched file: {e}")
            reject(player_message="Error while reading patched file. Poller is broken. Contact us immediately.")

        # Check that the number of bytes different between original and patched is within patch budget
        if len(patched) > len(original) + PATCH_BUDGET:
            reject(player_message=f"May only add up to {len(original) + PATCH_BUDGET} bytes to the service")
        patched_bytes_diff = self._byte_diff_count(original, patched)
        if patched_bytes_diff > PATCH_BUDGET:
            reject(player_message=f"May only change up to {PATCH_BUDGET} bytes inside the service")

    def connect(self):
        try:
            nautilus_print("Connecting to server...")
            self.socket = remote(self.host, self.port)
            self.socket.send(REQUEST['connect'])
            response = self.socket.recvn(1)
            self._assert(RESPONSE_ACK, response, "Connection failed to establish")
        except Exception as e:
            reject(f"Connection failed: {e}")

    def disconnect(self):
        if self.socket:
            nautilus_print("Disconnecting from server...")
            self.socket.send(REQUEST['disconnect'])
            response = self.socket.recvn(1)
            self._assert(RESPONSE_ACK, response, "Disconnecting failed")
            self.socket.close()
            self.image_count = 0
            self.selected = 0
        else:
            nautilus_print("Tried to disconnect, but connection was already closed?")

    def _get_current_image(self):
        self.socket.send(REQUEST['current_image'])
        response = self.socket.recvn(1)
        self._assert(RESPONSE_RES, response, "Failed to get current image")
        selected_blob = self._recv_blob()
        self.selected = struct.unpack('<B', selected_blob)[0]

    def _select_image(self, image_idx, expect_fail=False):
        self.socket.send(REQUEST['select_image'])
        self.socket.send(struct.pack('<B', image_idx))
        response = self.socket.recvn(1)
        if expect_fail:
            self._assert(RESPONSE_FAL, response, f"Server should have failed to select image {image_idx}")
        else:
            self._assert(RESPONSE_SCS, response, f"Failed to select image {image_idx}")
            self.selected = image_idx

    def _create_image(self, expect_fail=False):
        self.socket.send(REQUEST['create_image'])
        response = self.socket.recvn(1)
        if expect_fail:
            self._assert(RESPONSE_FAL, response, "Server should have failed to create image")
        else:
            self._assert(RESPONSE_SCS, response, "Failed to create image")
            self.image_count += 1
            self._get_current_image()
            nautilus_print(f"Created new image at index {self.selected}")

    def _destroy_image(self, image_idx):
        self.socket.send(REQUEST['destroy_image'])
        self.socket.send(struct.pack('<B', image_idx))
        response = self.socket.recvn(1)
        self._assert(RESPONSE_SCS, response, f"Failed to destroy image {image_idx}")
        self.image_count -= 1
        if self.selected >= image_idx and self.selected > 0:
            self.selected -= 1

    def _load_image(self, data, expect_fail=False):
        self.socket.send(REQUEST['load_image'])
        self._send_blob(data)
        response = self.socket.recvn(1)
        if expect_fail:
            self._assert(RESPONSE_FAL, response, "Server should have failed to load image")
        else:
            self._assert(RESPONSE_SCS, response, "Failed to load image")
            self.image_count += 1
            self.selected = self.image_count - 1

    def _store_image(self):
        self.socket.send(REQUEST['store_image'])
        response = self.socket.recvn(1)
        self._assert(RESPONSE_RES, response, "Failed to receive stored image")
        return self._recv_blob()

    def _duplicate_image(self, expect_fail=False):
        self.socket.send(REQUEST['duplicate_image'])
        response = self.socket.recvn(1)
        if expect_fail:
            self._assert(RESPONSE_FAL, response, "Server should have failed to duplicate image")
        else:
            self._assert(RESPONSE_SCS, response, "Failed to duplicate image")
            self.image_count += 1
            self.selected = self.image_count - 1

    def _get_comment(self):
        self.socket.send(REQUEST['get_comment'])
        response = self.socket.recvn(1)
        self._assert(RESPONSE_RES, response, "Failed to get comment")
        return self._recv_blob()

    def _set_comment(self, comment):
        c = comment.encode('utf-8')
        self.socket.send(REQUEST['set_comment'])
        self._send_blob(c)
        response = self.socket.recvn(1)
        self._assert(RESPONSE_SCS, response, "Failed to set comment")

    def _render_image(self, size):
        self.socket.send(REQUEST['render_image'])
        self.socket.send(struct.pack('<B', size))
        response = self.socket.recvn(1)
        self._assert(RESPONSE_RES, response, "Failed to receive rendered image")
        return self._recv_blob()

    def _get_style_count(self):
        self.socket.send(REQUEST['get_styles'])
        response = self.socket.recvn(1)
        self._assert(RESPONSE_RES, response, "Failed to get style count")
        count_blob = self._recv_blob()
        return struct.unpack('<B', count_blob)[0]

    def _get_style(self, style_idx, expect_fail=False):
        self.socket.send(REQUEST['get_style'])
        self.socket.send(struct.pack('<B', style_idx))
        response = self.socket.recvn(1)
        if expect_fail:
            self._assert(RESPONSE_FAL, response, f"Server should have failed to get style {style_idx}")
            return None
        self._assert(RESPONSE_RES, response, f"Failed to get style {style_idx}")
        return self._recv_blob()

    def _set_style(self, style_idx, style_blob, expect_fail=False):
        self.socket.send(REQUEST['set_style'])
        self._send_blob(struct.pack('<B', style_idx) + style_blob)
        response = self.socket.recvn(1)
        if expect_fail:
            self._assert(RESPONSE_FAL, response, f"Server should have failed to set style {style_idx}")
        else:
            self._assert(RESPONSE_SCS, response, f"Failed to set style {style_idx}")

    def _add_style(self, style_blob, expect_fail=False):
        self.socket.send(REQUEST['add_style'])
        self._send_blob(style_blob)
        response = self.socket.recvn(1)
        if expect_fail:
            self._assert(RESPONSE_FAL, response, "Server should have failed to add style")
        else:
            self._assert(RESPONSE_SCS, response, "Failed to add style")

    def _remove_style(self, style_idx, expect_fail=False):
        self.socket.send(REQUEST['remove_style'])
        self.socket.send(struct.pack('<B', style_idx))
        response = self.socket.recvn(1)
        if expect_fail:
            self._assert(RESPONSE_FAL, response, f"Server should have failed to remove style {style_idx}")
        else:
            self._assert(RESPONSE_SCS, response, f"Failed to remove style {style_idx}")

    def _is_flat(self, style_idx):
        self.socket.send(REQUEST['is_flat'])
        self.socket.send(struct.pack('<B', style_idx))
        response = self.socket.recvn(1)
        self._assert(RESPONSE_RES, response, "Failed to get is_flat")
        return self._recv_blob() == b'\x01'

    def _is_transparent(self, style_idx):
        self.socket.send(REQUEST['is_transparent'])
        self.socket.send(struct.pack('<B', style_idx))
        response = self.socket.recvn(1)
        self._assert(RESPONSE_RES, response, "Failed to get is_transparent")
        return self._recv_blob() == b'\x01'

    def _get_color(self, style_idx):
        self.socket.send(REQUEST['get_color'])
        self.socket.send(struct.pack('<B', style_idx))
        response = self.socket.recvn(1)
        self._assert(RESPONSE_RES, response, "Failed to get color")
        return self._recv_blob()

    def _set_color(self, style_idx, color_blob, expect_fail=False):
        self.socket.send(REQUEST['set_color'])
        self._send_blob(struct.pack('<B', style_idx) + color_blob)
        response = self.socket.recvn(1)
        expected = RESPONSE_FAL if expect_fail else RESPONSE_SCS
        self._assert(expected, response, "Set color did not return expected result")

    def _get_gradient(self, style_idx, expect_fail=False):
        self.socket.send(REQUEST['get_gradient'])
        self.socket.send(struct.pack('<B', style_idx))
        response = self.socket.recvn(1)
        if expect_fail:
            self._assert(RESPONSE_FAL, response, "Server should have failed to get gradient")
            return None
        self._assert(RESPONSE_RES, response, "Failed to get gradient")
        return self._recv_blob()

    def _set_gradient(self, style_idx, gradient_blob, expect_fail=False):
        self.socket.send(REQUEST['set_gradient'])
        self._send_blob(struct.pack('<B', style_idx) + gradient_blob)
        response = self.socket.recvn(1)
        if expect_fail:
            self._assert(RESPONSE_FAL, response, "Server should have to set gradient")
        else:
            self._assert(RESPONSE_SCS, response, "Failed to set gradient")

    def _set_step(self, style_idx, step_idx, step_blob):
        self.socket.send(REQUEST['set_step'])
        self._send_blob(struct.pack('<BB', style_idx, step_idx) + step_blob)
        response = self.socket.recvn(1)
        self._assert(RESPONSE_SCS, response, "Failed to set step")

    def _add_step(self, style_idx, step_idx, step_blob):
        self.socket.send(REQUEST['add_step'])
        self._send_blob(struct.pack('<BB', style_idx, step_idx) + step_blob)
        response = self.socket.recvn(1)
        self._assert(RESPONSE_SCS, response, "Failed to add step")

    def _remove_step(self, style_idx, step_idx):
        self.socket.send(REQUEST['remove_step'])
        self.socket.send(struct.pack('<BB', style_idx, step_idx))
        response = self.socket.recvn(1)
        self._assert(RESPONSE_SCS, response, "Failed to remove step")

    def _get_gradient_transformer(self, style_idx):
        self.socket.send(REQUEST['get_gradient_transformer'])
        self.socket.send(struct.pack('<B', style_idx))
        response = self.socket.recvn(1)
        if response == RESPONSE_FAL:
            return None
        self._assert(RESPONSE_RES, response, "Failed to get gradient transformer")
        return self._recv_blob()

    def _set_gradient_transformer(self, style_idx, transformer_blob):
        self.socket.send(REQUEST['set_gradient_transformer'])
        self._send_blob(struct.pack('<B', style_idx) + transformer_blob)
        response = self.socket.recvn(1)
        self._assert(RESPONSE_SCS, response, "Failed to set gradient transformer")

    def _get_path_count(self):
        self.socket.send(REQUEST['get_paths'])
        response = self.socket.recvn(1)
        self._assert(RESPONSE_RES, response, "Failed to get path count")
        count_blob = self._recv_blob()
        return struct.unpack('<B', count_blob)[0]

    def _get_path(self, path_idx):
        self.socket.send(REQUEST['get_path'])
        self.socket.send(struct.pack('<B', path_idx))
        response = self.socket.recvn(1)
        self._assert(RESPONSE_RES, response, "Failed to get path")
        return self._recv_blob()

    def _set_path(self, path_idx, path_blob, expect_fail=False):
        self.socket.send(REQUEST['set_path'])
        self._send_blob(struct.pack('<B', path_idx) + path_blob)
        response = self.socket.recvn(1)
        if expect_fail:
            self._assert(RESPONSE_FAL, response, "Server should have failed to set path")
        else:
            self._assert(RESPONSE_SCS, response, "Failed to set path")

    def _add_path(self, path_blob, expect_fail=False):
        self.socket.send(REQUEST['add_path'])
        self._send_blob(path_blob)
        response = self.socket.recvn(1)
        if expect_fail:
            self._assert(RESPONSE_FAL, response, "Server should have failed to add path")
        else:
            self._assert(RESPONSE_SCS, response, "Failed to add path")

    def _remove_path(self, path_idx, expect_fail=False):
        self.socket.send(REQUEST['remove_path'])
        self.socket.send(struct.pack('<B', path_idx))
        response = self.socket.recvn(1)
        if expect_fail:
            self._assert(RESPONSE_FAL, response, f"Server should have failed to remove path {path_idx}")
        else:
            self._assert(RESPONSE_SCS, response, f"Failed to remove path {path_idx}")

    def _get_point(self, path_idx, point_idx, expect_fail=False):
        self.socket.send(REQUEST['get_point'])
        self.socket.send(struct.pack('<BB', path_idx, point_idx))
        response = self.socket.recvn(1)
        if expect_fail:
            self._assert(RESPONSE_FAL, response, "Server should have failed to get point")
            return None
        self._assert(RESPONSE_RES, response, "Failed to get point")
        return self._recv_blob()

    def _set_point(self, path_idx, point_idx, point_blob, expect_fail=False):
        self.socket.send(REQUEST['set_point'])
        self._send_blob(struct.pack('<BB', path_idx, point_idx) + point_blob)
        response = self.socket.recvn(1)
        if expect_fail:
            self._assert(RESPONSE_FAL, response, "Server should have failed to set point")
        else:
            self._assert(RESPONSE_SCS, response, "Failed to set point")

    def _add_point(self, path_idx, point_idx, point_blob):
        self.socket.send(REQUEST['add_point'])
        self._send_blob(struct.pack('<BB', path_idx, point_idx) + point_blob)
        response = self.socket.recvn(1)
        self._assert(RESPONSE_SCS, response, "Failed to add point")

    def _remove_point(self, path_idx, point_idx):
        self.socket.send(REQUEST['remove_point'])
        self.socket.send(struct.pack('<BB', path_idx, point_idx))
        response = self.socket.recvn(1)
        self._assert(RESPONSE_SCS, response, "Failed to remove point")

    def _get_shape_count(self):
        self.socket.send(REQUEST['get_shapes'])
        response = self.socket.recvn(1)
        self._assert(RESPONSE_RES, response, "Failed to get shape count")
        count_blob = self._recv_blob()
        return struct.unpack('<B', count_blob)[0]

    def _get_shape(self, shape_idx):
        self.socket.send(REQUEST['get_shape'])
        self.socket.send(struct.pack('<B', shape_idx))
        response = self.socket.recvn(1)
        self._assert(RESPONSE_RES, response, "Failed to get shape")
        return self._recv_blob()

    def _set_shape(self, shape_idx, shape_blob, expect_fail=False):
        self.socket.send(REQUEST['set_shape'])
        self._send_blob(struct.pack('<B', shape_idx) + shape_blob)
        response = self.socket.recvn(1)
        if expect_fail:
            self._assert(RESPONSE_FAL, response, "Server should have failed to set shape")
        else:
            self._assert(RESPONSE_SCS, response, "Failed to set shape")

    def _add_shape(self, shape_blob, expect_fail=False):
        self.socket.send(REQUEST['add_shape'])
        self._send_blob(shape_blob)
        response = self.socket.recvn(1)
        if expect_fail:
            self._assert(RESPONSE_FAL, response, "Server should have failed to add shape")
        else:
            self._assert(RESPONSE_SCS, response, "Failed to add shape")

    def _remove_shape(self, shape_idx):
        self.socket.send(REQUEST['remove_shape'])
        self.socket.send(struct.pack('<B', shape_idx))
        response = self.socket.recvn(1)
        self._assert(RESPONSE_SCS, response, f"Failed to remove shape at index {shape_idx}")

    def _get_shape_style(self, shape_idx):
        self.socket.send(REQUEST['get_shape_style'])
        self.socket.send(struct.pack('<B', shape_idx))
        response = self.socket.recvn(1)
        self._assert(RESPONSE_RES, response, "Failed to get shape style")
        return self._recv_blob()

    def _set_shape_style(self, shape_idx, style_idx):
        self.socket.send(REQUEST['set_shape_style'])
        self.socket.send(struct.pack('<BB', shape_idx, style_idx))
        response = self.socket.recvn(1)
        self._assert(RESPONSE_SCS, response, "Failed to set shape style")

    def _get_shape_paths(self, shape_idx):
        self.socket.send(REQUEST['get_shape_paths'])
        self.socket.send(struct.pack('<B', shape_idx))
        response = self.socket.recvn(1)
        self._assert(RESPONSE_RES, response, "Failed to get shape paths")
        return self._recv_blob()

    def _set_shape_paths(self, shape_idx, paths_blob):
        self.socket.send(REQUEST['set_shape_paths'])
        self._send_blob(struct.pack('<B', shape_idx) + paths_blob)
        response = self.socket.recvn(1)
        self._assert(RESPONSE_SCS, response, "Failed to set shape paths")

    def _add_shape_path(self, shape_idx, path_idx):
        self.socket.send(REQUEST['add_shape_path'])
        self.socket.send(struct.pack('<BB', shape_idx, path_idx))
        response = self.socket.recvn(1)
        self._assert(RESPONSE_SCS, response, "Failed to add shape path")

    def _remove_shape_path(self, shape_idx, path_idx):
        self.socket.send(REQUEST['remove_shape_path'])
        self.socket.send(struct.pack('<BB', shape_idx, path_idx))
        response = self.socket.recvn(1)
        self._assert(RESPONSE_SCS, response, "Failed to remove shape path")

    def _has_hinting(self, shape_idx):
        self.socket.send(REQUEST['has_hinting'])
        self.socket.send(struct.pack('<B', shape_idx))
        response = self.socket.recvn(1)
        self._assert(RESPONSE_RES, response, "Failed to get hinting")
        return self._recv_blob() == b'\x01'

    def _set_hinting(self, shape_idx, hinting):
        self.socket.send(REQUEST['set_hinting'])
        self.socket.send(struct.pack('<BB', shape_idx, 1 if hinting else 0))
        response = self.socket.recvn(1)
        self._assert(RESPONSE_SCS, response, "Failed to set hinting")

    def _get_min_visibility(self, shape_idx):
        self.socket.send(REQUEST['get_min_visibility'])
        self.socket.send(struct.pack('<B', shape_idx))
        response = self.socket.recvn(1)
        self._assert(RESPONSE_RES, response, "Failed to get min visibility")
        return self._recv_blob()

    def _set_min_visibility(self, shape_idx, val):
        self.socket.send(REQUEST['set_min_visibility'])
        self.socket.send(struct.pack('<BB', shape_idx, val))
        response = self.socket.recvn(1)
        self._assert(RESPONSE_SCS, response, "Failed to set min visibility")

    def _get_max_visibility(self, shape_idx):
        self.socket.send(REQUEST['get_max_visibility'])
        self.socket.send(struct.pack('<B', shape_idx))
        response = self.socket.recvn(1)
        self._assert(RESPONSE_RES, response, "Failed to get max visibility")
        return self._recv_blob()

    def _set_max_visibility(self, shape_idx, val):
        self.socket.send(REQUEST['set_max_visibility'])
        self.socket.send(struct.pack('<BB', shape_idx, val))
        response = self.socket.recvn(1)
        self._assert(RESPONSE_SCS, response, "Failed to set max visibility")

    def _get_transformer_count(self, shape_idx):
        self.socket.send(REQUEST['get_transformers'])
        self.socket.send(struct.pack('<B', shape_idx))
        response = self.socket.recvn(1)
        self._assert(RESPONSE_RES, response, "Failed to get transformer count from shape")
        count_blob = self._recv_blob()
        return struct.unpack('<B', count_blob)[0]

    def _get_transformer(self, shape_idx, transformer_idx):
        self.socket.send(REQUEST['get_transformer'])
        self.socket.send(struct.pack('<BB', shape_idx, transformer_idx))
        response = self.socket.recvn(1)
        self._assert(RESPONSE_RES, response, "Failed to get transformer from shape")
        return self._recv_blob()

    def _set_transformer(self, shape_idx, transformer_idx, transformer_blob, expect_fail=False):
        self.socket.send(REQUEST['set_transformer'])
        self._send_blob(struct.pack('<BB', shape_idx, transformer_idx) + transformer_blob)
        response = self.socket.recvn(1)
        if expect_fail:
            self._assert(RESPONSE_FAL, response, "Server should have failed to set transformer")
        else:
            self._assert(RESPONSE_SCS, response, "Failed to set transformer")

    def _add_transformer(self, shape_idx, transformer_blob):
        self.socket.send(REQUEST['add_transformer'])
        self._send_blob(struct.pack('<B', shape_idx) + transformer_blob)
        response = self.socket.recvn(1)
        self._assert(RESPONSE_SCS, response, "Failed to add transformer to shape")

    def _remove_transformer(self, shape_idx, transformer_idx):
        self.socket.send(REQUEST['remove_transformer'])
        self.socket.send(struct.pack('<BB', shape_idx, transformer_idx))
        response = self.socket.recvn(1)
        self._assert(RESPONSE_SCS, response, "Failed to remove transformer")

    def _extract_text_chunks(self, png_bytes):
        text_chunks = []
        offset = 8  # Skip signature

        while offset < len(png_bytes):
            # Read chunk length (4 bytes, big-endian)
            length = struct.unpack(">I", png_bytes[offset:offset+4])[0]
            chunk_type = png_bytes[offset+4:offset+8]
            chunk_data = png_bytes[offset+8:offset+8+length]

            if chunk_type == b"tEXt":
                text_chunks.append(chunk_data.decode("utf-8"))

            # Move to the next chunk (length + type + data + CRC)
            offset += 8 + length + 4

        return "".join(text_chunks)

    def test_file_roundtrip(self, filename: str) -> None:
        nautilus_print("Testing round-trip of icon...")

        # Read the file
        nautilus_print(f"Using {filename} as the icon.")
        try:
            with open(filename, 'rb') as f:
                original_data = f.read()
        except FileNotFoundError:
            nautilus_print(f"Could not find icon {filename} to test round-trip!")
            reject(player_message=f"Could not find icon to test round-trip. Poller is broken. Please contact us immediately.")

        # Load the image
        self._load_image(original_data)

        # Store the image
        new_data = self._store_image()

        # Make sure we got back the same thing we put in
        self._assert(original_data, new_data, "Round-tripped icon does not match original icon.")

        nautilus_print(f"Round-trip of icon successful.\n")

    def test_object_manipulation(self):
        nautilus_print("Testing some complex object manipulation...")

        # Helper for packing some floating-point values
        def _pack_float(f):
            if f == 1.0: return b'\x40\x00\x00'
            if f == 0.0: return b'\x00\x00\x00'
            if f == 2.0: return b'\x42\x00\x00'
            reject(f"Don't know how to pack float {f}")

        # Make a new image
        self._create_image()

        # Perform style and gradient tests
        nautilus_print("Testing style and gradient properties...")
        color_style_blob = b'\x03\xff\x00\x00' # SolidColorNoAlpha, Red
        self._add_style(color_style_blob)
        self._assert(True, self._is_flat(0), "Style should be flat")
        self._assert(False, self._is_transparent(0), "Style should not be transparent")
        self._assert(color_style_blob, self._get_color(0), "Color mismatch")

        gradient_blob = b'\x02\x00\x04\x02\x00\xff\x00\x00\xff\x00\x00\xff'
        self._set_gradient(0, gradient_blob)
        self._assert(False, self._is_flat(0), "Style should now be a gradient")

        step_blob = b'\x80\xff\xff\x00' # Stop 128, Yellow
        self._add_step(0, 1, step_blob)
        self._set_step(0, 0, b'\x40\x00\xff\x00') # Stop 64, Green
        self._remove_step(0, 2)

        # TODO: Maybe perform some path and point tests?
        #       We already kinda do this in the next test, though...

        # Perform some shape and transformer tests
        nautilus_print("Testing shape and transformer properties...")
        self._add_path(b'\x08\x01\x20\x20') # Path at index 0: no curves, 1 point
        shape_blob = b'\x0a\x00\x01\x00\x00'
        self._add_shape(shape_blob)
        self._assert(shape_blob, self._get_shape(0), "Shape data mismatch")

        self._set_hinting(0, True)
        self._assert(True, self._has_hinting(0), "Hinting should have been enabled")
        self._set_min_visibility(0, 32)
        self._assert(b'\x20', self._get_min_visibility(0), "Min visibility mismatch")
        self._set_max_visibility(0, 192)
        self._assert(b'\xc0', self._get_max_visibility(0), "Max visibility mismatch")

        self._add_style(b'\x03\x00\x00\xff') # Blue style at index 1
        self._set_shape_style(0, 1)
        self._assert(b'\x01', self._get_shape_style(0), "Shape style should have been updated")

        self._add_path(b'\x08\x01\x40\x40') # Path at index 1: no curves, 1 point
        self._add_shape_path(0, 1)
        self._assert(b'\x00\x01', self._get_shape_paths(0), "Shape paths should have path 1")
        self._remove_shape_path(0, 0)
        self._assert(b'\x01', self._get_shape_paths(0), "Shape paths should only have path 1")
        self._set_shape_paths(0, b'\x00')
        self._assert(b'\x00', self._get_shape_paths(0), "Shape paths should have been reset")

        stroke_transformer_blob = b'\x17\x82\x11\x04'
        self._add_transformer(0, stroke_transformer_blob)
        contour_transformer_blob = b'\x15\x81\x00\x00'
        self._set_transformer(0, 0, contour_transformer_blob)
        self._assert(contour_transformer_blob, self._get_transformer(0, 0), "Transformer should have been updated")
        self._remove_transformer(0, 0)
        self._assert(0, self._get_transformer_count(0), "Transformer should have been removed")

        nautilus_print("Complex object manipulation test successful.\n")

    def test_single_image_state(self):
        nautilus_print("Testing single image state integrity...")
        self._create_image()

        num_items = 50
        nautilus_print(f"Adding {num_items} styles, paths, and shapes...")
        style_blob = b'\x03\xde\xad\xbe'
        path_blob = b'\x08\x01\x20\x20'
        for i in range(num_items):
            self._add_style(style_blob)
            self._add_path(path_blob)
            shape_blob = b'\x0a' + struct.pack('<B', i) + b'\x01' + struct.pack('<B', i) + b'\x00'
            self._add_shape(shape_blob)

        self._assert(num_items, self._get_style_count(), "Style count mismatch after adding")
        self._assert(num_items, self._get_path_count(), "Path count mismatch after adding")
        self._assert(num_items, self._get_shape_count(), "Shape count mismatch after adding")
        nautilus_print("Counts verified after additions.")

        # Path and point manipulation
        nautilus_print("Testing path and point manipulation...")
        path_idx_to_test = 25
        original_path = self._get_path(path_idx_to_test)
        point_blob = b'\x80\x00\x80\x00\x80\x00\x80\x00\x80\x00\x80\x00' # (64, 64)
        self._add_point(path_idx_to_test, 1, point_blob)
        self._set_point(path_idx_to_test, 0, point_blob)
        self._remove_point(path_idx_to_test, 1)
        self._assert(point_blob, self._get_point(path_idx_to_test, 0), "Point data mismatch")
        self._set_path(path_idx_to_test, original_path)
        self._assert(original_path, self._get_path(path_idx_to_test), "Path should be restored")

        indices_to_remove = list(range(10)) + list(range(20, 30)) + list(range(40, 50))
        nautilus_print(f"Removing {len(indices_to_remove)} items...")
        for i in sorted(indices_to_remove, reverse=True):
            self._remove_shape(i)
            self._remove_style(i)
            self._remove_path(i)

        expected_remaining = num_items - len(indices_to_remove)
        self._assert(expected_remaining, self._get_style_count(), "Style count mismatch after removing")
        self._assert(expected_remaining, self._get_path_count(), "Path count mismatch after removing")
        self._assert(expected_remaining, self._get_shape_count(), "Shape count mismatch after removing")
        nautilus_print("Counts verified after removals.")

        nautilus_print("Single image state integrity test successful.\n")

    def _test_image_max_count(self, max):
        # Clean slate
        nautilus_print("Cleaning up pre-existing images...")
        while self.image_count > 0:
            self._destroy_image(0)
            nautilus_print(f"Images remaining: {self.image_count-1}")

        # Make all new images
        nautilus_print(f"Creating {max} new images...")
        for _ in range(max):
            self._create_image()

        # Next one should fail as we are at capacity
        self._create_image(expect_fail=True)

        # ...and the total should still be the max
        self._assert(max, self.image_count, "Total image count is incorrect")

    def test_image_context_switching(self):
        nautilus_print("Testing image context switching...")

        # Make a bunch of empty images
        self._test_image_max_count(MAX_IMAGES)

        # Make some solid colors without alpha for testing (TODO: Add more modifications)
        modifications = {
            i: {'style': b'\x03' + struct.pack('<B', i*16) + b'\x00\x00'} for i in range(MAX_IMAGES)
        }

        # Apply modifications across all images
        nautilus_print("Applying modifications in random, but deterministic, order...")
        image_indices = [7, 5, 13, 10, 2, 0, 15, 11, 14, 9, 6, 8, 3, 12, 4, 1]
        for i in image_indices:
            self._select_image(i)
            self._add_style(modifications[i]['style'])

        # Verify modifications across all images
        nautilus_print("Verifying modifications in random, but deterministic, order...")
        image_indices = [14, 6, 5, 3, 0, 1, 12, 7, 10, 11, 9, 8, 4, 15, 13, 2]
        for i in image_indices:
            self._select_image(i)
            self._assert(1, self._get_style_count(), f"Image {i} should have 1 style")
            retrieved_style = self._get_style(0)
            if i == 0:
                # Handle automatic conversion to SolidGrayNoAlpha for the black style
                self._assert(b'\x05\x00', retrieved_style, f"Style for image {i} is incorrect")
            else:
                self._assert(modifications[i]['style'], retrieved_style, f"Style for image {i} is incorrect")

        # TODO: Remove all modifications across all images?

        nautilus_print("Image context switching test successful.\n")

    def test_image_rendering(self, filename: str, comment: str = '') -> None:
        nautilus_print("Testing image rendering...")

        # Read the file
        nautilus_print(f"Using {filename} as the icon.")
        try:
            with open(filename, 'rb') as f:
                original_data = f.read()
        except FileNotFoundError:
            nautilus_print(f"Could not find icon {filename} to test round-trip!")
            reject(player_message=f"Could not find icon to test round-trip. Poller is broken. Please contact us immediately.")

        # Load the image
        self._load_image(original_data)

        # Set the comment, if one was provided
        if comment != '':
            self._set_comment(comment)
            self._assert(comment, self._get_comment().decode('utf-8'), "Could not retrieve correct comment")

        # Render the image
        png_data = self._render_image(64)
        text = self._extract_text_chunks(png_data)

        # Check the tEXt chunk
        if comment == '':
            comment = 'Nautilus Institute' # Default comment if none was provided
        if not self.flag_hash in text:
            reject(player_message="Incorrect author chunk content.")
        if not 'ico v0.1' in text:
            reject(player_message="Incorrect software chunk content.")
        if not comment in text:
            reject(player_message="Incorrect comment chunk content.")

        nautilus_print(f"Image rendering successful.\n")

    def test_image_duplicate(self, filename: str) -> None:
        nautilus_print("Testing image duplication...")

        # Set a new comment
        #self._set_comment(f"Duplicate of {comment}")

        # Normal rendering test
        self.test_image_rendering(filename, '')

        # Make a duplicate
        self._duplicate_image()

        # Render the image
        png_data = self._render_image(64)
        text = self._extract_text_chunks(png_data)

        # Check the tEXt chunk again
        if not self.flag_hash in text:
            reject(player_message="Incorrect author chunk content.")
        if not 'ico v0.1' in text:
            reject(player_message="Incorrect software chunk content.")

        nautilus_print("Image duplication test successful.\n")

def main():
    poller = Poller(HOST, PORT)

    # Make sure the team didn't do anything silly first
    #poller.check_files()

    # Simple test of functionality
    time.sleep(random.choice([0, 1, 2]))
    poller.connect()
    poller.test_file_roundtrip('/opt/tests/Prefs_Mouse_processed.hvif')
    poller.disconnect()

    # Do it again, but different this time
    time.sleep(random.choice([0, 1, 2]))
    poller.connect()
    poller.test_image_rendering('/opt/tests/File_Archive_ZIP_processed.hvif')
    poller.test_image_rendering('/opt/tests/File_Device_processed.hvif', 'This is a test comment')
    poller.disconnect()

    # MORE
    time.sleep(random.choice([0, 1, 2]))
    poller.connect()
    poller.test_file_roundtrip('/opt/tests/App_About_processed.hvif')
    poller.test_image_rendering('/opt/tests/App_Generic_3_processed.hvif')
    poller.test_image_rendering('/opt/tests/App_Mail_processed.hvif', 'mail mail mail mail mail mail mail mail mail')
    poller.test_file_roundtrip('/opt/tests/App_TkWish_processed.hvif')
    poller.test_object_manipulation()
    poller.test_single_image_state()
    poller.test_image_context_switching()
    poller.disconnect()

    # Encore
    time.sleep(random.choice([0, 1, 2]))
    poller.connect()
    poller.test_image_duplicate('/opt/tests/Misc_Bomb_processed.hvif') # 💣
    poller.disconnect()

    accept("All tests completed successfully. Polling has finished.")

if __name__ == "__main__":
    main()
