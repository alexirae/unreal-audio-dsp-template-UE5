#include "MetasoundNodes/MetasoundVolumeNode.h"

#define LOCTEXT_NAMESPACE "MetasoundStandardNodes_VolumeNode"


METASOUND_REGISTER_NODE(FVolumeNode)


//------------------------------------------------------------------------------------
// FVolumeOperator
//------------------------------------------------------------------------------------
FVolumeOperator::FVolumeOperator(const Metasound::FOperatorSettings& InSettings, const Metasound::FAudioBufferReadRef& InAudioInput, const Metasound::FFloatReadRef& InAmplitude)
    : AudioInput(InAudioInput)
    , AudioOutput(Metasound::FAudioBufferWriteRef::CreateNew(InSettings))
    , Amplitude(InAmplitude)
{
    VolumeDSPProcessor.Init();
}

Metasound::FDataReferenceCollection FVolumeOperator::GetInputs() const
{
    Metasound::FDataReferenceCollection InputDataReferences;

    InputDataReferences.AddDataReadReference(VolumeNode::InParamNameAudioInput, AudioInput);
    InputDataReferences.AddDataReadReference(VolumeNode::InParamNameAmplitude, Amplitude);

    return InputDataReferences;
}

Metasound::FDataReferenceCollection FVolumeOperator::GetOutputs() const
{
    Metasound::FDataReferenceCollection OutputDataReferences;

    OutputDataReferences.AddDataReadReference(VolumeNode::OutParamNameAudio, AudioOutput);

    return OutputDataReferences;
}

void FVolumeOperator::Execute()
{
    const float* InputAudio = AudioInput->GetData();
    float* OutputAudio      = AudioOutput->GetData();

    const int32 NumFrames = AudioInput->Num();

    VolumeDSPProcessor.SetAmplitude(*Amplitude);

    VolumeDSPProcessor.ProcessAudioBuffer(InputAudio, OutputAudio, NumFrames);
}

const Metasound::FVertexInterface& FVolumeOperator::GetVertexInterface()
{
    static const Metasound::FVertexInterface Interface(
        Metasound::FInputVertexInterface(
            Metasound::TInputDataVertexModel<Metasound::FAudioBuffer>(VolumeNode::InParamNameAudioInput, LOCTEXT("AudioInputTT", "Audio input.")),
            Metasound::TInputDataVertexModel<float>(VolumeNode::InParamNameAmplitude, LOCTEXT("AmplitudeTT", "The amount of amplitude to apply to the signal."), 1.0f)
        ),
        Metasound::FOutputVertexInterface(
            Metasound::TOutputDataVertexModel<Metasound::FAudioBuffer>(VolumeNode::OutParamNameAudio, LOCTEXT("AudioOutputTT", "Audio output."))
        )
    );

    return Interface;
}

const Metasound::FNodeClassMetadata& FVolumeOperator::GetNodeInfo()
{
    auto InitNodeInfo = []() -> Metasound::FNodeClassMetadata
    {
        Metasound::FNodeClassMetadata Info;

        Info.ClassName        = { TEXT("UE"), TEXT("Volume"), TEXT("Audio") };
        Info.MajorVersion     = 1;
        Info.MinorVersion     = 0;
        Info.DisplayName      = LOCTEXT("Metasound_VolumeDisplayName", "Volume");
        Info.Description      = LOCTEXT("Metasound_VolumeNodeDescription", "Applies volume to the audio input.");
        Info.Author           = Metasound::PluginAuthor;
        Info.PromptIfMissing  = Metasound::PluginNodeMissingPrompt;
        Info.DefaultInterface = GetVertexInterface();

        return Info;
    };

    static const Metasound::FNodeClassMetadata Info = InitNodeInfo();

    return Info;
}

TUniquePtr<Metasound::IOperator> FVolumeOperator::CreateOperator(const Metasound::FCreateOperatorParams& InParams, Metasound::FBuildErrorArray& OutErrors)
{
    const Metasound::FDataReferenceCollection& InputCollection = InParams.InputDataReferences;
    const Metasound::FInputVertexInterface& InputInterface     = GetVertexInterface().GetInputInterface();

    Metasound::FAudioBufferReadRef AudioIn = InputCollection.GetDataReadReferenceOrConstruct<Metasound::FAudioBuffer>(VolumeNode::InParamNameAudioInput, InParams.OperatorSettings);
    Metasound::FFloatReadRef InAmplitude   = InputCollection.GetDataReadReferenceOrConstructWithVertexDefault<float>(InputInterface, VolumeNode::InParamNameAmplitude, InParams.OperatorSettings);

    return MakeUnique<FVolumeOperator>(InParams.OperatorSettings, AudioIn, InAmplitude);
}


//------------------------------------------------------------------------------------
// FVolumeNode
//------------------------------------------------------------------------------------
FVolumeNode::FVolumeNode(const Metasound::FNodeInitData& InitData)
    : Metasound::FNodeFacade(InitData.InstanceName, InitData.InstanceID, Metasound::TFacadeOperatorClass<FVolumeOperator>())
{
    
}

#undef LOCTEXT_NAMESPACE
