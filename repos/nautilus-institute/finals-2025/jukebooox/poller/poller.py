#!/usr/bin/env python3

import os
import sys
import nautpolling
from nautpolling import player_print, nautilus_print, accept, reject
from nautpolling import nautilus_print as print

import soundfile as sf
import numpy as np
import acoustid
import audioread
import pyrubberband as pyrb
import io
import wave

import tempfile

import x

from pwn import *

HOST = os.environ.get('HOST', '127.0.0.1')
PORT = os.environ.get('PORT', 9000)

# context.log_level = 'DEBUG'

ECHO_CHECKS = [
    ("/opt/adamd-simon-says.wav", -2, 8, "hello to the world"),
    ("/opt/wow-this-is-cool-say-hello-tts.wav", -8, 11, "hello"),
]

LAPTOP_CHECKS = [
    "/opt/gregorquendel__scarlatti-sonata-in-d-minor-k-10-sec.wav",
    "/opt/364987__adnova__paino.wav",
    "/opt/444271__mahammed__guitar-with-pieno-melody-v2-10sec.wav",
    "/opt/595860__szegvari__africa-safari-love-world-ethnic-modern-soundtrack-music-drum-flute-piano-snare-contemporary-eq-mastered-1.wav",
    "/opt/595860__szegvari__africa-safari-love-world-ethnic-modern-soundtrack-music-drum-flute-piano-snare-contemporary-eq-mastered-2.wav",
    "/opt/595860__szegvari__africa-safari-love-world-ethnic-modern-soundtrack-music-drum-flute-piano-snare-contemporary-eq-mastered-3.wav",
    "/opt/679186__bainmack__punk_rock_short31.wav",
    "/opt/50741__rutgermuller__metal-band-jam-5-thrash.wav",
    "/opt/669104__seth_makes_sounds__free-edm-song-2-1.wav",
    "/opt/669104__seth_makes_sounds__free-edm-song-2-2.wav",
    "/opt/669104__seth_makes_sounds__free-edm-song-2-3.wav",
]

PRODIGI_CHECKS = [
    ("/opt/364987__adnova__paino.wav", "E Minor", False),
    ("/opt/444271__mahammed__guitar-with-pieno-melody-v2-10sec.wav", "E Minor", False),
    ("/opt/595860__szegvari__africa-safari-love-world-ethnic-modern-soundtrack-music-drum-flute-piano-snare-contemporary-eq-mastered-1.wav", "A Major", False),
    ("/opt/595860__szegvari__africa-safari-love-world-ethnic-modern-soundtrack-music-drum-flute-piano-snare-contemporary-eq-mastered-2.wav", "E Major", False),
    ("/opt/595860__szegvari__africa-safari-love-world-ethnic-modern-soundtrack-music-drum-flute-piano-snare-contemporary-eq-mastered-3.wav", "D Major", False),
    ("/opt/679186__bainmack__punk_rock_short31.wav", "D Major", False),
    ("/opt/50741__rutgermuller__metal-band-jam-5-thrash.wav", "E Minor", False),
    ("/opt/669104__seth_makes_sounds__free-edm-song-2-1.wav", "E Minor", False),
    ("/opt/669104__seth_makes_sounds__free-edm-song-2-2.wav", "E Minor", False),
    ("/opt/669104__seth_makes_sounds__free-edm-song-2-3.wav", "E Minor", False),
]

PRODIGI_KEYS = ["C Major","C# Major","D Major","Eb Major","E Major","F Major","F# Major", "G Major","Ab Major","A Major","Bb Major","B Major", "C Minor","C# Minor","D Minor","Eb Minor","E Minor","F Minor","F# Minor","G Minor","Ab Minor","A Minor","Bb Minor","B Minor"]


def connect():
    try:
        return remote(HOST, PORT)
    except Exception as e:
        reject(f"Connection failed")

def check_files():
    patched_dir = nautpolling.load_patched_image()
    deleted_files = nautpolling.get_deleted_files()
    if deleted_files and len(deleted_files) != 0:
        reject(player_message="Cannot delete files")

    changed_files = nautpolling.get_modified_files()
    print(f"{changed_files=}")
    if not changed_files:        
        return
    if len(changed_files) == 0:
        return
    
    if len(changed_files) != 1:
        reject(player_message="Can only change filters.txt")

    if not 'app/filters.txt' in changed_files:
        reject(player_message="Can only change filters.txt")

def pitch_shift(y, sr, n_steps):
    # Convert to mono if stereo
    if len(y.shape) > 1:
        y = np.mean(y, axis=1)
    
    # Calculate the pitch shift ratio (2^(n_steps/12))
    shift_ratio = 2 ** (n_steps / 12.0)
    
    # Apply rubber band pitch shifting (maintains duration)
    y_shifted = pyrb.pitch_shift(y, sr, n_steps)
    
    return y_shifted, sr


def upload_play_and_check(p, song_name, wav_data, song_id, check, file_path=None, pitch=None):
    """Helper function to upload a song, play it, and check for expected output"""
    x.upload_song(p, song_name, wav_data)
    result = x.play_song(p, song_id)
    if not check in result.decode('utf-8').lower():

        # check to see if our debug output is here:
        start = b'START_DEBUG_WAV\n'
        end = b'END_DEBUG_WAV'
        if start in result and end in result:
            # todo: get between b'START_DEBUG_WAV' and b'END_DEBUG_WAV' in result
            wav = result[result.find(start) + len(start) : result.find(end)]
            nautilus_print(f"DEBUG_TEST_FAILURE_WAV={wav.decode('utf-8')}")
        if pitch is not None:
            nautilus_print(f"failed on {file_path=}, pitch shift {pitch=}, {check=} {result=}")
        else:
            nautilus_print(f"failed on normal {file_path=} {check=}")
        reject("echooo is broken")

def test_echooo():
    # go through each of the checks in ECHO_CHECKS (file, start_pitch,
    # end_pitch, check) , try the normal one, verify the check, then
    # do a pitch shift from start_pitch to end_pitch
    nautilus_print("Going to test echooo")
    p = connect()
    # turn on the echooo
    x.toggle_device(p, 1)

    start_new_file_num = 1
    for (file_path, start_pitch, end_pitch, check) in ECHO_CHECKS:
        assert(start_pitch < end_pitch)
        data, samplerate = sf.read(file_path)
        with io.BytesIO() as wav_buffer:
            sf.write(wav_buffer, data, samplerate, format='WAV', subtype='PCM_16')
            wav_data = wav_buffer.getvalue()

        upload_play_and_check(p, f"test-{start_new_file_num}".encode(), wav_data, start_new_file_num, check, file_path)
        start_new_file_num += 1

        for i in range(start_pitch, end_pitch):
            if i == 0:
                continue

            # PERF HACK: skip odd pitch shifts
            if i % 2 == 1:
                continue

            y_shifted, sr = pitch_shift(data, samplerate, i)
            with io.BytesIO() as wav_buffer:
                sf.write(wav_buffer, y_shifted, sr, format='WAV', subtype='PCM_16')
                wav_data = wav_buffer.getvalue()

            upload_play_and_check(p, f"test-{start_new_file_num}".encode(), wav_data, start_new_file_num, check, file_path, i)
            start_new_file_num += 1

    x.quit(p)
    nautilus_print("echooo test success")

def load_mono_from_bytes(b):
    buf = io.BytesIO(b)
    return load_mono(buf)

def load_mono(path):
    x, sr = sf.read(path)
    if x.ndim > 1:
        x = x.mean(axis=1)          # mix to mono
    return x.astype(np.float64), sr

def fingerprint_from_bytes(b):
    with tempfile.NamedTemporaryFile(delete_on_close=False) as fp:
        fp.write(b)
        fp.close()

        return acoustid.fingerprint_file(fp.name)

def test_laptooop():
    nautilus_print("Going to test laptooop")

    # just check that we can properly send this song

    p = connect()
    x.toggle_device(p, 2)
    x.set_volume(p, 0)

    high_rate_clip = open("/opt/gregorquendel__scarlatti-sonata-in-d-minor-k-clip-192-32.wav", "rb").read()

    x.upload_song(p, b"high-rate-clip", high_rate_clip)
    x.play_song(p, 1)
    recorded_wav = x.laptop_download(p)

    hr_clip_data, sr1 = load_mono_from_bytes(high_rate_clip)
    recorded_wav_data, sr2 = load_mono_from_bytes(recorded_wav)
    if sr1 != sr2:
        nautilus_print(f"Shouldn't happen: {sr1=} {sr2=} of high rate clip gregorquendel__scarlatti-sonata-in-d-minor-k-clip-192-32.wav should be equal\n")
        reject("Laptooop failed to record properly")

    if len(hr_clip_data) != len(recorded_wav_data):
        nautilus_print(f"Shouldn't happen: {len(hr_clip_data)=} {len(recorded_wav_data)=} of high rate clip gregorquendel__scarlatti-sonata-in-d-minor-k-clip-192-32.wav should be equal\n")
        reject("Laptooop failed to record properly")

    x.quit(p)

    nautilus_print("Passed high rate file check")
    
    p = connect()
    x.toggle_device(p, 2)
    x.set_volume(p, 0)
    i = 1
    for song_path in LAPTOP_CHECKS:
        data = open(song_path, "rb").read()
        x.upload_song(p, f"test-laptooop-{i}".encode(), data)

        x.play_song(p, i)

        recorded_wav = x.laptop_download(p)

        x.laptop_clear(p)

        # TODO: delete the following for production
        # nautilus_print(f"REMOVE ME BEFORE PRODUCTION")
        # basename = os.path.basename(song_path)
        # tmp_storage = f"/tmp/recorded-{basename}"

        # open(tmp_storage, "wb").write(recorded_wav)

        # nautilus_print(f"Saving {song_path} to {tmp_storage=}")

        original_fp = fingerprint_from_bytes(data)
        recorded_fp = fingerprint_from_bytes(recorded_wav)

        diff = acoustid.compare_fingerprints(recorded_fp, original_fp)
        
        nautilus_print(f"{diff=}")
        if diff >= .80:
            nautilus_print(f"The same {song_path=} {original_fp=} {recorded_fp=}")
        else:
            nautilus_print(f"FAIL DIFFERENT {diff=} {song_path=}")
            reject("My laptooop must be broken, the recording doesn't sound right")
        i += 1

    nautilus_print("Laptooop test success")

def test_prooodigi():
    p = connect()
    x.toggle_device(p, 3)
    i = 1
    for key in PRODIGI_KEYS:
        data = x.wav_key_demo(key, 5, 44100)
        x.upload_song(p, f"test-key-{i}".encode(), data)
        x.play_song(p, i)
        x.prooodigi_validate_master(p)
        result = p.readuntil(b"jukebooox")
        if not key.encode() in result:
            reject("Key detection is no longer working")
        else:
            nautilus_print(f"{key=} passed")
        i += 1    
    x.quit(p)

    p = connect()
    x.toggle_device(p, 3)
    i = 1
    for filename, key, is_valid in PRODIGI_CHECKS:
        data = open(filename, "rb").read()
        x.upload_song(p, f"test-real-file-{i}".encode(), data)
        x.play_song(p, i)
        x.prooodigi_validate_master(p)
        result = p.readuntil(b"jukebooox")

        recorded_raw_master = x.prooodigi_download_master(p)


        # Collect data from the original
        with wave.open(filename, 'rb') as wf:
            sample_rate = wf.getframerate()
            num_channels = wf.getnchannels()
            sample_width = wf.getsampwidth()

        buffer = io.BytesIO()
        with wave.open(buffer, 'wb') as wf:
            wf.setnchannels(num_channels)
            wf.setsampwidth(sample_width) 
            wf.setframerate(sample_rate)
            wf.writeframes(recorded_raw_master)
            recorded_wav = buffer.getvalue()


        original_fp = fingerprint_from_bytes(data)
        recorded_fp = fingerprint_from_bytes(recorded_wav)

        diff = acoustid.compare_fingerprints(recorded_fp, original_fp)
        if diff >= .80:
            nautilus_print(f"The same {filename=} {original_fp=} {recorded_fp=}")
        else:
            nautilus_print(f"FAIL DIFFERENT {diff=} {filename=}")
            reject("The prooodigi must be broken, this isn't the recording I want to master")

        if not key.encode() in result:
            nautilus_print(f"{filename=} expected {key=} but got {result=}")
            reject("Key detection is no longer working")
        else:
            nautilus_print(f"{filename=} {key=} passed")
        result_is_valid = b"is valid" in result
        if result_is_valid and is_valid:
            nautilus_print(f"Alright {filename=} still valid")
        elif not result_is_valid and is_valid:
            nautilus_print(f"{filename=} used to be valid, but isn't now {result=}, likely filters added vinyl pops")
            reject("My song that used to be valid isn't anymore...")
        

        i += 1


def main():
    check_files()

    p = connect()
    _, _, _, devices = x.list_devices(p)
    x.quit(p)

    nautilus_print(f"Available devices: {devices.keys()=}")

    # Only test the devices that we have
    if 1 in devices:
        test_echooo()

    if 2 in devices:
        test_laptooop()

    if 3 in devices:
        test_prooodigi()

    # another connection
    p = connect()

    nautilus_print("Successfully connected")

    p.readuntil(b"Would you like to play a song")

    x.quit(p)

    accept("All good")

if __name__ == '__main__':
    main()
