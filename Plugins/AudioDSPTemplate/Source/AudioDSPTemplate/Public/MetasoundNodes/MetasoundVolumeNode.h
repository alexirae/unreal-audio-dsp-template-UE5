#pragma once

#include "DSPProcessing/Volume.h"
#include "MetasoundEnumRegistrationMacro.h"
#include "MetasoundParamHelper.h"

namespace DSPTemplate
{
	//------------------------------------------------------------------------------------
	// FVolumeOperator
	//------------------------------------------------------------------------------------
	class FVolumeOperator : public Metasound::TExecutableOperator<FVolumeOperator>
	{
	public:
		static const Metasound::FNodeClassMetadata& GetNodeInfo();
		static const Metasound::FVertexInterface& GetVertexInterface();
		static TUniquePtr<Metasound::IOperator> CreateOperator(const Metasound::FBuildOperatorParams& InParams, Metasound::FBuildResults& OutResults);

		FVolumeOperator(const Metasound::FOperatorSettings& InSettings, const Metasound::FAudioBufferReadRef& InAudioInput, const Metasound::FFloatReadRef& InAmplitude);

		virtual void BindInputs(Metasound::FInputVertexInterfaceData& InOutVertexData) override;
		virtual void BindOutputs(Metasound::FOutputVertexInterfaceData& InOutVertexData) override;

		void Execute();

	private:
		Metasound::FAudioBufferReadRef	AudioInput;
		Metasound::FAudioBufferWriteRef AudioOutput;

		DSPProcessing::FVolume VolumeDSPProcessor;

		Metasound::FFloatReadRef Amplitude;
	};

	//------------------------------------------------------------------------------------
	// FVolumeNode
	//------------------------------------------------------------------------------------
	class FVolumeNode : public Metasound::FNodeFacade
	{
	public:
		// Constructor used by the Metasound Frontend.
		FVolumeNode(const Metasound::FNodeInitData& InitData)
			: Metasound::FNodeFacade(InitData.InstanceName, InitData.InstanceID, Metasound::TFacadeOperatorClass<FVolumeOperator>())
		{

		}
	};
}
