#include "MetasoundNodes/MetasoundVolumeNode.h"

#define LOCTEXT_NAMESPACE "MetasoundStandardNodes_VolumeNode"

namespace Metasound
{
    //------------------------------------------------------------------------------------
    // FVolumeOperator
    //------------------------------------------------------------------------------------
    FVolumeOperator::FVolumeOperator(const FOperatorSettings& InSettings, const FAudioBufferReadRef& InAudioInput, const FFloatReadRef& InAmplitude)
        : AudioInput(InAudioInput)
        , AudioOutput(FAudioBufferWriteRef::CreateNew(InSettings))
        , Amplitude(InAmplitude)
    {
        VolumeDSPProcessor.Init();
    }

    FDataReferenceCollection FVolumeOperator::GetInputs() const
    {
        using namespace VolumeNode;

        FDataReferenceCollection InputDataReferences;

        InputDataReferences.AddDataReadReference(METASOUND_GET_PARAM_NAME(InParamNameAudioInput), AudioInput);
        InputDataReferences.AddDataReadReference(METASOUND_GET_PARAM_NAME(InParamNameAmplitude), Amplitude);

        return InputDataReferences;
    }

    FDataReferenceCollection FVolumeOperator::GetOutputs() const
    {
        using namespace VolumeNode;

        FDataReferenceCollection OutputDataReferences;

        OutputDataReferences.AddDataReadReference(METASOUND_GET_PARAM_NAME(OutParamNameAudio), AudioOutput);

        return OutputDataReferences;
    }

    void FVolumeOperator::Execute()
    {
        const float* InputAudio = AudioInput->GetData();
        float* OutputAudio      = AudioOutput->GetData();

        const int32 NumSamples = AudioInput->Num();

        VolumeDSPProcessor.SetAmplitude(*Amplitude);

        VolumeDSPProcessor.ProcessAudioBuffer(InputAudio, OutputAudio, NumSamples);
    }

    const FVertexInterface& FVolumeOperator::GetVertexInterface()
    {
        using namespace VolumeNode;

        static const FVertexInterface Interface(
            FInputVertexInterface(
                TInputDataVertexModel<FAudioBuffer>(METASOUND_GET_PARAM_NAME_AND_METADATA(InParamNameAudioInput)),
                TInputDataVertexModel<float>(METASOUND_GET_PARAM_NAME_AND_METADATA(InParamNameAmplitude), 1.0f)
            ),

            FOutputVertexInterface(
                TOutputDataVertexModel<FAudioBuffer>(METASOUND_GET_PARAM_NAME_AND_METADATA(OutParamNameAudio))
            )
        );

        return Interface;
    }

    const FNodeClassMetadata& FVolumeOperator::GetNodeInfo()
    {
        auto InitNodeInfo = []() -> FNodeClassMetadata
        {
            FNodeClassMetadata Info;

            Info.ClassName        = { TEXT("UE"), TEXT("Volume"), TEXT("Audio") };
            Info.MajorVersion     = 1;
            Info.MinorVersion     = 0;
            Info.DisplayName      = LOCTEXT("Metasound_VolumeDisplayName", "Volume");
            Info.Description      = LOCTEXT("Metasound_VolumeNodeDescription", "Applies volume to the audio input.");
            Info.Author           = PluginAuthor;
            Info.PromptIfMissing  = PluginNodeMissingPrompt;
            Info.DefaultInterface = GetVertexInterface();
            Info.CategoryHierarchy = { LOCTEXT("Metasound_VolumeNodeCategory", "Utils") };

            return Info;
        };

        static const FNodeClassMetadata Info = InitNodeInfo();

        return Info;
    }

    TUniquePtr<IOperator> FVolumeOperator::CreateOperator(const FCreateOperatorParams& InParams, FBuildErrorArray& OutErrors)
    {
        using namespace VolumeNode;

        const FDataReferenceCollection& InputCollection = InParams.InputDataReferences;
        const FInputVertexInterface& InputInterface     = GetVertexInterface().GetInputInterface();

        FAudioBufferReadRef AudioIn = InputCollection.GetDataReadReferenceOrConstruct<FAudioBuffer>(METASOUND_GET_PARAM_NAME(InParamNameAudioInput), InParams.OperatorSettings);
        FFloatReadRef InAmplitude   = InputCollection.GetDataReadReferenceOrConstructWithVertexDefault<float>(InputInterface, METASOUND_GET_PARAM_NAME(InParamNameAmplitude), InParams.OperatorSettings);

        return MakeUnique<FVolumeOperator>(InParams.OperatorSettings, AudioIn, InAmplitude);
    }


    //------------------------------------------------------------------------------------
    // FVolumeNode
    //------------------------------------------------------------------------------------
    FVolumeNode::FVolumeNode(const FNodeInitData& InitData)
        : FNodeFacade(InitData.InstanceName, InitData.InstanceID, TFacadeOperatorClass<FVolumeOperator>())
    {
    
    }

    METASOUND_REGISTER_NODE(FVolumeNode)
}

#undef LOCTEXT_NAMESPACE
