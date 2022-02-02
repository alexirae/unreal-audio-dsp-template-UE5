#pragma once

#include "CoreMinimal.h"

namespace DSPProcessing
{
    class AUDIODSPTEMPLATE_API FVolume
    {
    public:
        FVolume();
        virtual ~FVolume();

        void Init();
        void SetAmplitude(const float InAmount);
        void ProcessAudioBuffer(const float* InBuffer, float* OutBuffer, int32 NumFrames);

    private:
        float Amplitude;
    };
}
