#include "DSPProcessing/Volume.h"
#include "DSP/Dsp.h"

namespace DSPProcessing
{
    FVolume::FVolume()
        : Amplitude(0.0f)
    {
        
    }

    FVolume::~FVolume()
    {
        
    }

    void FVolume::Init()
    {
        
    }

    void FVolume::SetAmplitude(const float InAmount)
    {
        Amplitude = InAmount;
    }

    void FVolume::ProcessAudioBuffer(const float* InBuffer, float* OutBuffer, int32 NumFrames)
    {
        //TRACE_CPUPROFILER_EVENT_SCOPE(TEXT("FVolume::ProcessAudioBuffer"))

        // Naive version (and without parameter smoothing)
        for (int32 i = 0; i < NumFrames; ++i)
        {
            OutBuffer[i] = Amplitude * InBuffer[i];
        }
    }
}
