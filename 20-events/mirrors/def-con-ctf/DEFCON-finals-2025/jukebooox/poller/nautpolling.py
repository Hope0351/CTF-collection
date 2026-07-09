import os
import sys
import json
import subprocess
import tempfile
import tarfile
import fcntl
import time
import shutil
import random
import string
from pathlib import Path
from typing import List, Optional, Tuple

try:
    import pwn
    pwn.context.log_console = sys.stderr
except ImportError:
    pass

# Global variable to store the combined directory path from the last load_patched_image call
_last_combined_dir: Optional[str] = os.environ.get('POLLER_TESTING_CHANGED_FILES',None)
_last_deleted_files: Optional[List[str]] = None

def handle_uncaught_exception(exc_type, exc_value, exc_traceback):
    """
    Global exception handler for uncaught exceptions.
    
    Args:
        exc_type: The exception type
        exc_value: The exception instance
        exc_traceback: The traceback object
    """
    import traceback
    # just print to stderr
    traceback.print_exc()
    
    # Log the full traceback for admins
    tb_str = ''.join(traceback.format_exception(exc_type, exc_value, exc_traceback))
    nautilus_print(f"Uncaught exception occurred:\n{tb_str}")
    
    # Reject with appropriate messages
    reject(
        player_message="An error occurred while validating your patch. This is likely caused by a mistake in your patch, so it has been rejected.",
        naut_message=f"Uncaught exception: {exc_type.__name__}: {exc_value}"
    )
    sys.stdout.flush()
    time.sleep(3)

# Set the global exception handler
sys.excepthook = handle_uncaught_exception

_quick_fail_messages = []

def load_patched_image() -> str:
    """
    Download and extract Docker layers based on environment variables.
    
    Returns:
        str: Path to the combined directory containing extracted files
    """
    global _last_deleted_files
    global _last_combined_dir

    if os.environ.get('POLLER_TESTING_CHANGED_FILES'):
        nautilus_print(f"WARNING: IN LOCAL TESTING MODE, USING CHANGED FILE DIR {_last_combined_dir}")
        return
    
    # Parse environment variables
    new_layers_str = os.environ.get('NEW_LAYERS')
    if not new_layers_str:
        nautilus_print("WARNING: NEW_LAYERS environment variable not set, using empty list (assuming no modifications)")
        new_layers_str = '[]'
    
    new_layers = json.loads(new_layers_str)
    new_layers = [layer.replace('sha256:', '') for layer in new_layers]
    nautilus_print(f"Going to download layers: {new_layers}")
    #if len(new_layers) == 0:
    #    return
        
    registry_user = os.environ.get('REGISTRY_USER')
    registry_pass = os.environ.get('REGISTRY_PASS')
    patch_image = os.environ.get('PATCH_IMAGE')
    
    if not patch_image:
        nautilus_print("WARNING: PATCH_IMAGE environment variable not set")
        return
    
    # Check if skopeo is available
    if not os.path.exists('/opt/tools/skopeo'):
        raise RuntimeError("skopeo not found at /opt/tools/skopeo")
    
    # Create policy.json file for skopeo
    _create_policy_json()
    
    # Determine output directory
    image_parts = patch_image.split(':')
    if len(image_parts) > 1 and image_parts[-1] != 'latest' and not 'test' in image_parts[-1]:
        tag = image_parts[-1]
        output_dir = f"/opt/patch-data/{tag}"
        os.makedirs(output_dir, exist_ok=True)
    else:
        # Create temp directory for skopeo - use /opt/patch-data-temp
        temp_id = ''.join(random.choices(string.ascii_lowercase + string.digits, k=8))
        output_dir = f"/opt/patch-data-temp/{temp_id}"
        # Ensure base directory exists
        os.makedirs("/opt/patch-data-temp", exist_ok=True)
    
    # File-based locking - use separate directory to avoid confusing skopeo
    lock_dir = f"{output_dir}.lock"
    os.makedirs(lock_dir, exist_ok=True)
    lock_file = os.path.join(lock_dir, "lock")
    finished_file = os.path.join(lock_dir, "finished")
    combined_dir = os.path.join(output_dir, "combined")

    def do_download():
        # Completely remove and recreate the directory for skopeo (clean slate)
        if os.path.exists(output_dir):
            shutil.rmtree(output_dir)
        os.makedirs(output_dir, exist_ok=True)
        
        # Download layers using skopeo
        layer_filter = ','.join([f"sha256:{layer.replace('sha256:', '')}" for layer in new_layers])
        if not layer_filter:
            layer_filter = '41414141414141414141414141'
        
        cmd = [
            '/opt/tools/skopeo', 'copy',
            f'docker://{patch_image}',
            f'dir://{output_dir}',
            '--src-tls-verify=false',
            '--dest-tls-verify=false',
            f'--layer-filter={layer_filter}'
        ]
        
        sanitized_cmds = cmd.copy()

        # Add authentication if provided
        if registry_user and registry_pass:
            cmd.extend(['--src-creds', f'{registry_user}:{registry_pass}'])
        
        # Log the command being executed
        nautilus_print(f"Running skopeo command: {' '.join(sanitized_cmds)}")
        
        result = subprocess.run(cmd, capture_output=True, text=True)
        
        # Log the result
        if result.returncode == 0:
            nautilus_print(f"Skopeo completed successfully")
            if result.stdout:
                nautilus_print(f"Skopeo stdout: {result.stdout}")
        else:
            nautilus_print(f"Skopeo failed with return code {result.returncode}")
            if result.stderr:
                nautilus_print(f"Skopeo stderr: {result.stderr}")
            if result.stdout:
                nautilus_print(f"Skopeo stdout: {result.stdout}")
            raise RuntimeError(f"skopeo failed: {result.stderr}")

        # Load config data
        cmd = [
            '/opt/tools/skopeo', 'inspect',
            f'docker://{patch_image}',
            '--tls-verify=false',
            '--config'
        ]

        sanitized_cmds = cmd.copy()

        # Add authentication if provided
        if registry_user and registry_pass:
            cmd.extend(['--creds', f'{registry_user}:{registry_pass}'])

        nautilus_print(f"Running skopeo command: {' '.join(sanitized_cmds)}")

        result = subprocess.run(cmd, capture_output=True, text=True)
        if result.returncode != 0:
            raise RuntimeError(f"skopeo inspect failed: {result.stderr}")
        
        config = json.loads(result.stdout)

        config_file = os.path.join(output_dir, "config.json")
        with open(config_file, 'w') as f:
            json.dump(config, f)
        
        # Extract layers
        deleted_files = _extract_layers(output_dir, new_layers, combined_dir)

        deleted_files_file = os.path.join(output_dir, "deleted_files.json")
        with open(deleted_files_file, 'w') as f:
            json.dump(deleted_files, f)

        # Mark as finished
        with open(finished_file, 'w') as finished:
            finished.write("done")

    deleted_files_file = os.path.join(output_dir, "deleted_files.json")
    error_file = os.path.join(output_dir, "error.json")

    start_time = time.time()

    did_quick_fail = False
    
    while True:

        # Try to acquire lock
        with open(lock_file, 'w') as f:
            try:
                fcntl.flock(f.fileno(), fcntl.LOCK_EX | fcntl.LOCK_NB)

                if os.path.exists(error_file):
                    with open(error_file, 'r') as f:
                        try:
                            error = json.load(f)
                        except json.JSONDecodeError:
                            pass
                    nautilus_print(f"DEBUG: Cached Error: {error}")
                    if error.get("quick_fail_messages"):
                        for message in error.get("quick_fail_messages"):
                            player_print(f"Failed: {message}")
                    did_quick_fail = True
                    raise RuntimeError(error.get("error"))
                
                # Check if already finished
                if os.path.exists(finished_file):
                    _last_combined_dir = combined_dir
                    with open(deleted_files_file, 'r') as f:
                        _last_deleted_files = json.load(f)
                    nautilus_print(f"DEBUG: Using cached image directory: {combined_dir}")
                    return combined_dir
                
                do_download()

                with open(deleted_files_file, 'r') as f:
                    deleted_files = json.load(f)

                # Store the combined directory path in the global variable
                _last_combined_dir = combined_dir
                _last_deleted_files = deleted_files
                return combined_dir
                
            except BlockingIOError:
                # Another process has the lock, wait for it to finish
                time.sleep(5)
                diff_time = time.time() - start_time
                nautilus_print(f"Waiting for lock to be released, {diff_time} seconds elapsed")
                continue

            except Exception as e:
                # don't re-overwrite the error file if we already did a quick fail
                if did_quick_fail:
                    raise e
                with open(error_file, 'w') as f:
                    json.dump({
                        "error": str(e),
                        "quick_fail_messages": _quick_fail_messages
                    }, f)
                raise e
        raise RuntimeError("Failed to acquire lock")

def get_image_config() -> dict:
    global _last_combined_dir

    if _last_combined_dir is None:
        raise RuntimeError("No patched image has been loaded yet. Call load_patched_image() first.")
    
    if not os.path.exists(_last_combined_dir):
        raise RuntimeError(f"Combined directory does not exist: {_last_combined_dir}")
    
    config_file = os.path.join(_last_combined_dir, "../config.json")
    with open(config_file, 'r') as f:
        config = json.load(f)

    return config

def get_image_entrypoint() -> str:
    """
    Get the entrypoint for the image.
    """
    config = get_image_config()
    return config.get('config', {}).get('Entrypoint', [])

def get_image_cmd() -> str:
    """
    Get the cmd for the image.
    """
    config = get_image_config()
    return config.get('config', {}).get('Cmd', [])

def get_image_env() -> str:
    """
    Get the env for the image.
    """
    config = get_image_config()
    return config.get('config', {}).get('Env', [])


def _create_policy_json() -> None:
    """Create policy.json file for skopeo."""
    policy_content = {
        "default": [
            {
                "type": "insecureAcceptAnything"
            }
        ],
        "transports": {
            "docker-daemon": {
                "": [{"type": "insecureAcceptAnything"}]
            }
        }
    }
    
    # Create directories
    os.makedirs("/root/.config/containers", exist_ok=True)
    os.makedirs("/etc/containers", exist_ok=True)
    
    # Write policy.json to both locations
    policy_paths = [
        "/root/.config/containers/policy.json",
        "/etc/containers/policy.json"
    ]
    
    for policy_path in policy_paths:
        with open(policy_path, 'w') as f:
            json.dump(policy_content, f, indent=4)

def safe_join(path1: str, path2: str) -> str:
    # Avoid any path traversal attacks
    path2 = path2.replace('\\', '/')
    path2 = path2.split('/')[-1]
    if path2 == '..':
        raise ValueError("Path traversal attack detected")

    abs_path1 = os.path.abspath(path1)
    abs_path2 = os.path.abspath(os.path.join(path1, path2))
    if not abs_path2.startswith(abs_path1):
        raise ValueError("Path traversal attack detected")

    return abs_path2


def _extract_layers(output_dir: str, layer_hashes: List[str], combined_dir: str) -> None:
    """Extract layers from manifest.json into combined directory."""
    manifest_path = os.path.join(output_dir, "manifest.json")
    
    if not os.path.exists(manifest_path):
        raise RuntimeError("manifest.json not found in output directory")
    
    with open(manifest_path, 'r') as f:
        manifest = json.load(f)
    
    # Create combined directory
    os.makedirs(combined_dir, exist_ok=True)

    deleted_files = []
    
    # Extract layers in order
    for layer_info in manifest.get('layers', []):
        digest = layer_info.get('digest', '')
        if digest.startswith('sha256:'):
            layer_hash = digest[7:]  # Remove 'sha256:' prefix
            
            if layer_hash in layer_hashes:
                layer_file = safe_join(output_dir, layer_hash)
                if os.path.exists(layer_file):
                    with tarfile.open(layer_file, 'r:gz') as tar:
                        tar.extractall(path=combined_dir)

                    nautilus_print(f"DEBUG: Extracted layer {layer_hash} to {combined_dir}")

                    # https://github.com/opencontainers/image-spec/blob/main/layer.md#whiteouts
                    # Iterate all files to look for any starting with .wh.
                    for root, dirs, filenames in os.walk(combined_dir):
                        for filename in filenames:
                            # check if symlink (not allowed)
                            if os.path.islink(safe_join(root, filename)):
                                player_print(f"Unsafe symlink detected at /{filename}")
                                _quick_fail_messages.append(f"Unsafe symlink detected at /{filename}")
                                raise RuntimeError("Unsafe symlink detected")

                            if not filename.startswith('.wh.'):
                                continue


                            if filename == '.wh..wh..opq':
                                player_print("Unsafe deletion detected in image layer, avoid recursive deletion of directories")
                                _quick_fail_messages.append("Unsafe deletion detected in image layer, avoid recursive deletion of directories")
                                raise RuntimeError("Unsafe deletion detected in image layer")
                                # Delete the parent directory
                                #filename = os.path.dirname(filename)

                            normal_path = filename[4:]

                            # remove .wh. files
                            os.remove(safe_join(root, filename))

                            # remove the file
                            full_path = safe_join(root, normal_path)

                            nautilus_print(f"DEBUG: Layer {layer_hash} found deleted file: {filename} -> {full_path}")

                            rel_path = os.path.relpath(full_path, combined_dir)
                            deleted_files.append(rel_path)

                            if os.path.exists(full_path):
                                if os.path.isdir(full_path):
                                    shutil.rmtree(full_path)
                                else:
                                    os.remove(full_path)

    return deleted_files


def get_modified_files() -> List[str]:
    """
    List all files in the combined directory from the last load_patched_image call.
    
    Returns:
        List[str]: List of file paths relative to the combined directory
    """
    global _last_combined_dir
    
    if _last_combined_dir is None:
        raise RuntimeError("No patched image has been loaded yet. Call load_patched_image() first.")
    
    if not os.path.exists(_last_combined_dir):
        raise RuntimeError(f"Combined directory does not exist: {_last_combined_dir}")
    
    nautilus_print(f"DEBUG: Using combined directory: {_last_combined_dir}")
    
    # List all files recursively
    files = []
    for root, dirs, filenames in os.walk(_last_combined_dir):
        for filename in filenames:
            full_path = safe_join(root, filename)
            rel_path = os.path.relpath(full_path, _last_combined_dir)
            files.append(rel_path)
    
    nautilus_print(f"DEBUG: Found {len(files)} files in combined directory")
    return sorted(files)

def get_deleted_files() -> List[str]:
    """
    List all files that were deleted from the last load_patched_image call.
    """
    global _last_deleted_files
    return _last_deleted_files

def player_print(*args, **kwargs):
    """These prints will be sent back to the players"""
    print(*args, **kwargs, file=sys.stdout)
    sys.stdout.flush()

def nautilus_print(*args, **kwargs):
    print(*args, **kwargs, file=sys.stderr)
    sys.stderr.flush()

def reject(player_message: Optional[str] = None, naut_message: Optional[str] = None) -> None:
    """
    Reject the request with a user-friendly message.
    
    Args:
        user_message (str, optional): Message to display to the teams. Try to limit the information leaked through this, keep it vague.
        naut_message (str, optional): Message to display to admins
    """
    if player_message:
        player_print(f'Failed: {player_message}')
    else:
        player_print('Failed: Your patch was rejected')
    if naut_message:
        nautilus_print(f'Failed: {naut_message}')
    elif player_message:
        nautilus_print(f'Failed: {player_message}')
    else:
        nautilus_print('Failed: The patch was rejected for an unspecified reason')
    os._exit(1)

def accept(player_message: Optional[str] = None, naut_message: Optional[str] = None) -> None:
    """
    Accept the request with a user-friendly message.
    """
    if player_message:
        player_print(f'Passed: {player_message}')
    else:
        player_print('Passed: Your patch was accepted')
    if naut_message:
        nautilus_print(f'Passed: {naut_message}')
    elif player_message:
        nautilus_print(f'Passed: {player_message}')
    else:
        nautilus_print('Passed: The patch was accepted for an unspecified reason')
    os._exit(0)

def get_flag() -> str:
    """
    Get the flag for the current patch.
    """
    if not os.environ.get('FLAG_PATH'):
        raise RuntimeError("FLAG_PATH environment variable not set")
    try:
        with open(os.environ.get('FLAG_PATH'), 'r') as f:
            return f.read().strip()
    except Exception as e:
        nautilus_print(f"Error reading flag file: {e}")
        reject(player_message="Admin error: Could not read flag file")

def enable_http_proxy(attack_host_name: str) -> Tuple[str, str]:
    HOST = os.environ.get('HOST')
    PORT = os.environ.get('PORT')

    PROXY_PATH = '/opt/mini-proxy'
    if not os.path.exists(PROXY_PATH):
        PROXY_PATH = '/opt/tools/mini-proxy'
        if not os.path.exists(PROXY_PATH):
            os.makedirs('/opt/tools', exist_ok=True)

    if os.path.exists(PROXY_PATH):
        subprocess.run([PROXY_PATH], check=True)
    else:
        nautilus_print("Downloading proxy binary...")
        subprocess.run(f'curl -L -o {PROXY_PATH} https://stackchk.fail/c41769741d11dc5ca8a4dede0b28d2ac/mini-proxy 1>&2', shell=True, check=True, stdout=sys.stderr)

    if os.path.exists(PROXY_PATH):
        nautilus_print(f"Proxy binary found at {PROXY_PATH}")
        return HOST, PORT

    os.environ['REAL_HOST'] = HOST
    os.environ['REAL_PORT'] = PORT

    if attack_host_name:
        os.environ['ATTACK_HOST_NAME'] = attack_host_name

    elif not os.environ.get('ATTACK_HOST_NAME'):
        os.environ['ATTACK_HOST_NAME'] = '10.10.1.1:21623'

    subprocess.Popen(f'while true; do {PROXY_PATH} 1>&2; done', shell=True, stdout=sys.stderr)

    os.environ['HOST'] = '127.0.0.1'
    os.environ['PORT'] = '8080'

    return '127.0.0.1', '8080'

    
