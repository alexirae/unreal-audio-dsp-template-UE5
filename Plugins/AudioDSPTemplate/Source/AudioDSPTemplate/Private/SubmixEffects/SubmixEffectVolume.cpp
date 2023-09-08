#include "SubmixEffects/SubmixEffectVolume.h"


//------------------------------------------------------------------------------------
// FSubmixEffectVolume
//------------------------------------------------------------------------------------
void FSubmixEffectVolume::Init(const FSoundEffectSubmixInitData& InitData)
{
	VolumeDSPProcessor.Init();
}

void FSubmixEffectVolume::OnPresetChanged()
{
	GET_EFFECT_SETTINGS(SubmixEffectVolume);

	VolumeDSPProcessor.SetAmplitude(Settings.Amplitude);
}

void FSubmixEffectVolume::OnProcessAudio(const FSoundEffectSubmixInputData& InData, FSoundEffectSubmixOutputData& OutData)
{
	const float* InAudioBuffer = InData.AudioBuffer->GetData();
	float* OutAudioBuffer      = OutData.AudioBuffer->GetData();

	const int32 NumChannels = InData.NumChannels;
	const int32 NumSamples  = InData.NumFrames * NumChannels;

	VolumeDSPProcessor.ProcessAudioBuffer(InAudioBuffer, OutAudioBuffer, NumSamples);
}


//------------------------------------------------------------------------------------
// USubmixEffectVolumePreset
//------------------------------------------------------------------------------------
void USubmixEffectVolumePreset::SetSettings(const FSubmixEffectVolumeSettings& InSettings)
{
	UpdateSettings(InSettings);
}
