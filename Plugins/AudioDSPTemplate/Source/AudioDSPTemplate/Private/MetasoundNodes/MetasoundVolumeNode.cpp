#include "MetasoundNodes/MetasoundVolumeNode.h"

#define LOCTEXT_NAMESPACE "DSPTemplate_MetasoundVolumeNode"

namespace DSPTemplate
{
	using namespace Metasound;

	namespace VolumeNode
	{
		// Input params
		METASOUND_PARAM(InParamNameAudioInput, "In",        "Audio input.")
		METASOUND_PARAM(InParamNameAmplitude,  "Amplitude", "The amount of amplitude to apply to the input signal.")
		
		// Output params
		METASOUND_PARAM(OutParamNameAudio, "Out", "Audio output.")
	}

	//------------------------------------------------------------------------------------
	// FVolumeOperator
	//------------------------------------------------------------------------------------
	FVolumeOperator::FVolumeOperator(const FOperatorSettings& InSettings, const FAudioBufferReadRef& InAudioInput, const FFloatReadRef& InAmplitude)
		: AudioInput(InAudioInput)
		, AudioOutput(FAudioBufferWriteRef::CreateNew(InSettings))
		, Amplitude(InAmplitude)
	{
		
	}

	const FNodeClassMetadata& FVolumeOperator::GetNodeInfo()
	{
		auto InitNodeInfo = []() -> FNodeClassMetadata
		{
			FNodeClassMetadata Info;

			Info.ClassName         = { TEXT("UE"), TEXT("Volume"), TEXT("Audio") };
			Info.MajorVersion      = 1;
			Info.MinorVersion      = 0;
			Info.DisplayName       = LOCTEXT("DSPTemplate_VolumeDisplayName", "Volume");
			Info.Description       = LOCTEXT("DSPTemplate_VolumeNodeDescription", "Applies volume to the audio input.");
			Info.Author            = "Put your name here!.";
			Info.PromptIfMissing   = PluginNodeMissingPrompt;
			Info.DefaultInterface  = GetVertexInterface();
			Info.CategoryHierarchy = { LOCTEXT("DSPTemplate_VolumeNodeCategory", "Utils") };

			return Info;
		};

		static const FNodeClassMetadata Info = InitNodeInfo();

		return Info;
	}

	void FVolumeOperator::BindInputs(FInputVertexInterfaceData& InOutVertexData)
	{
		using namespace VolumeNode;

		InOutVertexData.BindReadVertex(METASOUND_GET_PARAM_NAME(InParamNameAudioInput), AudioInput);
		InOutVertexData.BindReadVertex(METASOUND_GET_PARAM_NAME(InParamNameAmplitude),  Amplitude);
	}

	void FVolumeOperator::BindOutputs(FOutputVertexInterfaceData& InOutVertexData)
	{
		using namespace VolumeNode;

		InOutVertexData.BindReadVertex(METASOUND_GET_PARAM_NAME(OutParamNameAudio), AudioOutput);
	}

	const FVertexInterface& FVolumeOperator::GetVertexInterface()
	{
		using namespace VolumeNode;

		static const FVertexInterface Interface(
			FInputVertexInterface(
				TInputDataVertex<FAudioBuffer>(METASOUND_GET_PARAM_NAME_AND_METADATA(InParamNameAudioInput)),
				TInputDataVertex<float>(METASOUND_GET_PARAM_NAME_AND_METADATA(InParamNameAmplitude), 1.0f)
			),

			FOutputVertexInterface(
				TOutputDataVertex<FAudioBuffer>(METASOUND_GET_PARAM_NAME_AND_METADATA(OutParamNameAudio))
			)
		);

		return Interface;
	}

	TUniquePtr<IOperator> FVolumeOperator::CreateOperator(const FBuildOperatorParams& InParams, FBuildResults& OutResults)
	{
		using namespace VolumeNode;

		FAudioBufferReadRef AudioIn = InParams.InputData.GetOrConstructDataReadReference<FAudioBuffer>(METASOUND_GET_PARAM_NAME(InParamNameAudioInput), InParams.OperatorSettings);
		FFloatReadRef InAmplitude   = InParams.InputData.GetOrCreateDefaultDataReadReference<float>   (METASOUND_GET_PARAM_NAME(InParamNameAmplitude),  InParams.OperatorSettings);

		return MakeUnique<FVolumeOperator>(InParams.OperatorSettings, AudioIn, InAmplitude);
	}

	void FVolumeOperator::Execute()
	{
		const float* InputAudio = AudioInput->GetData();
		float* OutputAudio      = AudioOutput->GetData();

		const int32 NumSamples = AudioInput->Num();

		VolumeDSPProcessor.SetAmplitude(*Amplitude);
		VolumeDSPProcessor.ProcessAudioBuffer(InputAudio, OutputAudio, NumSamples);
	}

	METASOUND_REGISTER_NODE(FVolumeNode)
}

#undef LOCTEXT_NAMESPACE
