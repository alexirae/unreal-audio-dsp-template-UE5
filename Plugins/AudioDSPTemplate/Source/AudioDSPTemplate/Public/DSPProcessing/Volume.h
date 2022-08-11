#pragma once

#include "CoreMinimal.h"

namespace DSPProcessing
{
    class FVolume
    {
    public:
        FVolume();
        virtual ~FVolume();

        void Init();
        void SetAmplitude(const float InAmount);
        void ProcessAudioBuffer(const float* InBuffer, float* OutBuffer, int32 NumSamples);

    private:
        float Amplitude;
    };
}
