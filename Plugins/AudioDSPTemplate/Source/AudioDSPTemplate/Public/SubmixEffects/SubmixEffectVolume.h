#pragma once

#include "Sound/SoundEffectSubmix.h"
#include "DSPProcessing/Volume.h"
#include "SubmixEffectVolume.generated.h"


//////////////////////////////////////////////////////////////////////////////////////

class AUDIODSPTEMPLATE_API FSubmixEffectVolume : public FSoundEffectSubmix
{
public:
	virtual ~FSubmixEffectVolume() = default;

	// Called on an audio effect at initialization on main thread before audio processing begins.
	virtual void Init(const FSoundEffectSubmixInitData& InitData) override;

	// Called when an audio effect preset is changed
	virtual void OnPresetChanged() override;

	// Process the input block of audio. Called on audio thread.
	virtual void OnProcessAudio(const FSoundEffectSubmixInputData& InData, FSoundEffectSubmixOutputData& OutData) override;

protected:
	DSPProcessing::FVolume VolumeDSPProcessor;
};

//////////////////////////////////////////////////////////////////////////////////////

USTRUCT(BlueprintType)
struct AUDIODSPTEMPLATE_API FSubmixEffectVolumeSettings
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SubmixEffect|Preset", meta = (ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0"))
	float Amplitude = 1.0f;
};

//////////////////////////////////////////////////////////////////////////////////////

UCLASS(ClassGroup = AudioSourceEffect, meta = (BlueprintSpawnableComponent))
class AUDIODSPTEMPLATE_API USubmixEffectVolumePreset : public USoundEffectSubmixPreset
{
	GENERATED_BODY()

public:
	EFFECT_PRESET_METHODS(SubmixEffectVolume)

	UFUNCTION(BlueprintCallable, Category = "Audio|Effects|Volume")
	void SetSettings(const FSubmixEffectVolumeSettings& InSettings);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SubmixEffect|Preset", Meta = (ShowOnlyInnerProperties))
	FSubmixEffectVolumeSettings Settings;
};

//////////////////////////////////////////////////////////////////////////////////////
