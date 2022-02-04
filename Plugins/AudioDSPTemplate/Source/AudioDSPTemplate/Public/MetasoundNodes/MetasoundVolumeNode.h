#include "DSPProcessing/Volume.h"
#include "MetasoundEnumRegistrationMacro.h"


namespace VolumeNode
{
    static const TCHAR* InParamNameAudioInput = TEXT("In");
    static const TCHAR* InParamNameAmplitude  = TEXT("Amplitude");
    static const TCHAR* OutParamNameAudio     = TEXT("Out");
}

//////////////////////////////////////////////////////////////////////////////////////

class FVolumeOperator : public Metasound::TExecutableOperator<FVolumeOperator>
{
public:
    static const Metasound::FNodeClassMetadata& GetNodeInfo();
    static const Metasound::FVertexInterface& GetVertexInterface();
    static TUniquePtr<Metasound::IOperator> CreateOperator(const Metasound::FCreateOperatorParams& InParams, Metasound::FBuildErrorArray& OutErrors);

    FVolumeOperator(const Metasound::FOperatorSettings& InSettings, const Metasound::FAudioBufferReadRef& InAudioInput, const Metasound::FFloatReadRef& InAmplitude);

    virtual Metasound::FDataReferenceCollection GetInputs()  const override;
    virtual Metasound::FDataReferenceCollection GetOutputs() const override;

    void Execute();

private:
    Metasound::FAudioBufferReadRef  AudioInput;
    Metasound::FAudioBufferWriteRef AudioOutput;

    DSPProcessing::FVolume VolumeDSPProcessor;

    Metasound::FFloatReadRef Amplitude;
};

//////////////////////////////////////////////////////////////////////////////////////

class FVolumeNode : public Metasound::FNodeFacade
{
public:
    // Constructor used by the Metasound Frontend.
    FVolumeNode(const Metasound::FNodeInitData& InitData);
};

//////////////////////////////////////////////////////////////////////////////////////
