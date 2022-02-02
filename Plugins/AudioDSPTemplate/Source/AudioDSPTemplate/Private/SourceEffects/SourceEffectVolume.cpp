#include "SourceEffects/SourceEffectVolume.h"


//------------------------------------------------------------------------------------
// FSourceEffectVolume
//------------------------------------------------------------------------------------
void FSourceEffectVolume::Init(const FSoundEffectSourceInitData& InitData)
{
    bIsActive   = true;
    NumChannels = InitData.NumSourceChannels;
}

void FSourceEffectVolume::OnPresetChanged()
{
    GET_EFFECT_SETTINGS(SourceEffectVolume);

    VolumeDSPProcessor.SetAmplitude(Settings.Amplitude);
}

void FSourceEffectVolume::ProcessAudio(const FSoundEffectSourceInputData& InData, float* OutAudioBufferData)
{
    //TRACE_CPUPROFILER_EVENT_SCOPE(TEXT("FSourceEffectVolume::ProcessAudio"))

    const float* InAudioBuffer = InData.InputSourceEffectBufferPtr;
    float* OutAudioBuffer      = OutAudioBufferData;

    const int32 NumSamples = InData.NumSamples;

    VolumeDSPProcessor.ProcessAudioBuffer(InAudioBuffer, OutAudioBuffer, NumSamples);
}


//------------------------------------------------------------------------------------
// USourceEffectVolumePreset
//------------------------------------------------------------------------------------
void USourceEffectVolumePreset::SetSettings(const FSourceEffectVolumeSettings& InSettings)
{
    UpdateSettings(InSettings);
}
