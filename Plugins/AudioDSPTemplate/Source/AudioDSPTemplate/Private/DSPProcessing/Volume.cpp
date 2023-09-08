#include "DSPProcessing/Volume.h"

namespace DSPProcessing
{
	void FVolume::Init()
	{

	}

	void FVolume::SetAmplitude(const float InAmount)
	{
		Amplitude = InAmount;
	}

	void FVolume::ProcessAudioBuffer(const float* InBuffer, float* OutBuffer, const int32 InNumSamples)
	{
		// Uncomment to profile the cost of this DSP processing in Unreal Insights
		//TRACE_CPUPROFILER_EVENT_SCOPE(TEXT("FVolume::ProcessAudioBuffer"))

		// Naive version (and without parameter smoothing)
		for (int32 Index = 0; Index < InNumSamples; ++Index)
		{
			OutBuffer[Index] = Amplitude * InBuffer[Index];
		}
	}
}
