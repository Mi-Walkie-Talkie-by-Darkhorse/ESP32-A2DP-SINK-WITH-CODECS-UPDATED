#pragma once

#include <algorithm>
#include "A2DPVolumeControl.h"

class A2DPVolumeControlStub : public A2DPVolumeControl {
public:
    void update_audio_data(uint8_t* data, uint16_t byteCount) override {}
    void update_audio_data(Frame* data, uint16_t frameCount) override {}

    // provides a factor in the range of 0.0f to 1.0f
    float get_normalized_volume_factor() { return normalizedVolumeFactor; }

    void set_volume(uint8_t volume) override {
        constexpr unsigned maxVolume = 127u;
        constexpr unsigned maxVolumeFactor = 4095u;

        constexpr float kSlope = 4.0f;
        constexpr float kInput = kSlope / maxVolume;
        constexpr float kNorm = 1.0 / expm1f(kSlope);
        constexpr float kVolumeFactor = (maxVolumeFactor + 1.0f) / expm1f(kSlope);

        float volumeFactorFloat = std::min((unsigned)volume, 127u);
        volumeFactorFloat = expm1f(volumeFactorFloat * kInput);
        normalizedVolumeFactor = volumeFactorFloat * kNorm;
        volumeFactor = std::min((unsigned)(volumeFactorFloat * kVolumeFactor), maxVolumeFactor);
    }

protected:
    float normalizedVolumeFactor;
};
