#pragma once

#include <algorithm>
#include "A2DPVolumeControl.h"
#include "esp_log.h"

class A2DPVolumeControlStub : public A2DPVolumeControl {
public:
    void update_audio_data(uint8_t* data, uint16_t byteCount) override {}
    void update_audio_data(Frame* data, uint16_t frameCount) override {}

    // provides a factor in the range of 0.0f to 1.0f
    float get_normalized_volume_factor() { return normalizedVolumeFactor; }

    void set_volume(uint8_t volume) override {
        constexpr float A = 0.3456789; // Here we adjust the curve startup sector from "0" point.
        constexpr float B = 7.5;       // Here we adjust the curve middle sector.
        constexpr float C = 6.75E-13;  // Here we adjust the curve final point "4096"
        constexpr float kNorm = 1.0 / (127 * A + powf(127, B) * C);

        float volumeFactorFloat = std::min((unsigned)volume, 127u);
        volumeFactorFloat = volumeFactorFloat * A + powf(volumeFactorFloat, B) * C;
        volumeFactor = std::min((unsigned)volumeFactorFloat, 4095u);
        normalizedVolumeFactor = volumeFactorFloat * kNorm;
    }

protected:
    float normalizedVolumeFactor;
};
