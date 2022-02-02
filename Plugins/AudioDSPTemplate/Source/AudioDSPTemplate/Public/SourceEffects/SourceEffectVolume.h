#pragma once

#include "Sound/SoundEffectSource.h"
#include "DSPProcessing/Volume.h"
#include "SourceEffectVolume.generated.h"


//////////////////////////////////////////////////////////////////////////////////////

class AUDIODSPTEMPLATE_API FSourceEffectVolume : public FSoundEffectSource
{
public:
    virtual ~FSourceEffectVolume() = default;

    // Called on an audio effect at initialization on main thread before audio processing begins.
    virtual void Init(const FSoundEffectSourceInitData& InitData) override;

    // Called when an audio effect preset is changed
    virtual void OnPresetChanged() override;

    // Process the input block of audio. Called on audio thread.
    virtual void ProcessAudio(const FSoundEffectSourceInputData& InData, float* OutAudioBufferData) override;

protected:
    DSPProcessing::FVolume VolumeDSPProcessor;
    int32 NumChannels = 0;
};

//////////////////////////////////////////////////////////////////////////////////////

USTRUCT(BlueprintType)
struct AUDIODSPTEMPLATE_API FSourceEffectVolumeSettings
{
    GENERATED_USTRUCT_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SourceEffect|Preset", meta = (ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0"))
    float Amplitude = 1.0f;
};

//////////////////////////////////////////////////////////////////////////////////////

UCLASS(ClassGroup = AudioSourceEffect, meta = (BlueprintSpawnableComponent))
class AUDIODSPTEMPLATE_API USourceEffectVolumePreset : public USoundEffectSourcePreset
{
    GENERATED_BODY()

public:
    EFFECT_PRESET_METHODS(SourceEffectVolume)

    UFUNCTION(BlueprintCallable, Category = "Audio|Effects|Volume")
    void SetSettings(const FSourceEffectVolumeSettings& InSettings);

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "SourceEffect|Preset", Meta = (ShowOnlyInnerProperties))
    FSourceEffectVolumeSettings Settings;
};

//////////////////////////////////////////////////////////////////////////////////////
