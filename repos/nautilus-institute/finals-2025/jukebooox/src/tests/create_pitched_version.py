import argparse
import soundfile as sf
import numpy as np
import pyrubberband as pyrb
import sys

def pitch_shift(input_wav, n_steps):
    # Load the audio file
    y, sr = sf.read(input_wav)
    
    # Convert to mono if stereo
    if len(y.shape) > 1:
        y = np.mean(y, axis=1)
    
    # Calculate the pitch shift ratio (2^(n_steps/12))
    shift_ratio = 2 ** (n_steps / 12.0)
    
    # Apply rubber band pitch shifting (maintains duration)
    y_shifted = pyrb.pitch_shift(y, sr, n_steps)
    
    return y_shifted, sr

def main():
    parser = argparse.ArgumentParser(description="Pitch shift a WAV file using librosa.")
    parser.add_argument("input_wav", help="Path to the input WAV file")
    parser.add_argument("n_steps", type=float, help="Number of semitones to shift (+/-)")
    parser.add_argument("output_wav", help="Path to the output WAV file (or '-' for stdout)")
    args = parser.parse_args()

    y_shifted, sr = pitch_shift(args.input_wav, args.n_steps)

    if args.output_wav == "-":
        # Write WAV to stdout in binary mode
        sf.write(sys.stdout.buffer, y_shifted, sr, format="WAV")
    else:
        sf.write(args.output_wav, y_shifted, sr)
        print(f"Saved pitch-shifted audio to {args.output_wav}")

if __name__ == "__main__":
    main()

