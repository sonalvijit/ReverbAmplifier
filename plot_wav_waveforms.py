import matplotlib.pyplot as plt
import numpy as np
import soundfile as sf

def plot_waveform(file_path, title, subplot_position):
    data, samplerate = sf.read(file_path)
    
    # If stereo, just take one channel for simplicity
    if len(data.shape) == 2:
        data = data[:, 0]
    
    time = np.linspace(0, len(data) / samplerate, num=len(data))
    
    plt.subplot(1, 2, subplot_position)
    plt.plot(time, data)
    plt.title(title)
    plt.xlabel("Time [s]")
    plt.ylabel("Amplitude")

def main():
    input_file = "input.wav"
    output_file = "output_reverb.wav"

    plt.figure(figsize=(14, 5))

    plot_waveform(input_file, "Original Audio", 1)
    plot_waveform(output_file, "Reverb Applied", 2)

    plt.tight_layout()
    plt.show()

if __name__ == "__main__":
    main()
