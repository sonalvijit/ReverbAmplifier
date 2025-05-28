#include <iostream>
#include <vector>
#include <cmath>
#include <sndfile.h>

// Simple comb filter reverb
void applyReverb(std::vector<float>& samples, int sampleRate) {
    int delaySamples = static_cast<int>(0.1f * sampleRate); // 100ms delay
    float decay = 0.5f;

    std::vector<float> delayed(samples.size(), 0.0f);

    for (size_t i = 0; i < samples.size(); ++i) {
        float wet = samples[i];
        if (i >= delaySamples) {
            wet += decay * delayed[i - delaySamples];
        }
        delayed[i] = wet;
    }

    // Mix wet back into original
    for (size_t i = 0; i < samples.size(); ++i) {
        samples[i] = 0.6f * samples[i] + 0.4f * delayed[i]; // Wet/dry mix
    }
}

int main() {
    const char* inputFile = "input.wav";
    const char* outputFile = "output_reverb.wav";

    SF_INFO sfInfo;
    SNDFILE* inFile = sf_open(inputFile, SFM_READ, &sfInfo);
    if (!inFile) {
        std::cerr << "Error opening input file\n";
        return 1;
    }

    std::vector<float> samples(sfInfo.frames * sfInfo.channels);
    sf_read_float(inFile, samples.data(), samples.size());
    sf_close(inFile);

    applyReverb(samples, sfInfo.samplerate);

    SNDFILE* outFile = sf_open(outputFile, SFM_WRITE, &sfInfo);
    if (!outFile) {
        std::cerr << "Error opening output file\n";
        return 1;
    }

    sf_write_float(outFile, samples.data(), samples.size());
    sf_close(outFile);

    std::cout << "Reverb applied. Output saved to " << outputFile << "\n";
    return 0;
}
