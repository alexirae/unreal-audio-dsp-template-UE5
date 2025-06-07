#pragma once

#include "DSPProcessing/Volume.h"
#include "MetasoundEnumRegistrationMacro.h"
#include "MetasoundParamHelper.h"

namespace DSPTemplate
{
	class FVolumeOperator : public Metasound::TExecutableOperator<FVolumeOperator>
	{
	public:
		FVolumeOperator(const Metasound::FOperatorSettings& InSettings, const Metasound::FAudioBufferReadRef& InAudioInput, const Metasound::FFloatReadRef& InAmplitude);

		static const Metasound::FNodeClassMetadata& GetNodeInfo();

		virtual void BindInputs(Metasound::FInputVertexInterfaceData& InOutVertexData) override;
		virtual void BindOutputs(Metasound::FOutputVertexInterfaceData& InOutVertexData) override;

		static const Metasound::FVertexInterface& GetVertexInterface();
		static TUniquePtr<Metasound::IOperator> CreateOperator(const Metasound::FBuildOperatorParams& InParams, Metasound::FBuildResults& OutResults);

		void Execute();

		void Reset(const IOperator::FResetParams& InParams);

	private:
		Metasound::FAudioBufferReadRef	AudioInput;
		Metasound::FAudioBufferWriteRef AudioOutput;

		DSPProcessing::FVolume VolumeDSPProcessor;

		Metasound::FFloatReadRef Amplitude;
	};

	using FVolumeNode = Metasound::TNodeFacade<FVolumeOperator>;
}
