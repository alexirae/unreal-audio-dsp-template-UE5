#include "DSPProcessing/Volume.h"
#include "MetasoundEnumRegistrationMacro.h"
#include "MetasoundParamHelper.h"

namespace Metasound
{
	//------------------------------------------------------------------------------------
	// FVolumeOperator
	//------------------------------------------------------------------------------------
	class FVolumeOperator : public TExecutableOperator<FVolumeOperator>
	{
	public:
		static const FNodeClassMetadata& GetNodeInfo();
		static const FVertexInterface& GetVertexInterface();
		static TUniquePtr<IOperator> CreateOperator(const FCreateOperatorParams& InParams, FBuildErrorArray& OutErrors);

		FVolumeOperator(const FOperatorSettings& InSettings, const FAudioBufferReadRef& InAudioInput, const FFloatReadRef& InAmplitude);

		virtual FDataReferenceCollection GetInputs()  const override;
		virtual FDataReferenceCollection GetOutputs() const override;

		void Execute();

	private:
		FAudioBufferReadRef	 AudioInput;
		FAudioBufferWriteRef AudioOutput;

		DSPProcessing::FVolume VolumeDSPProcessor;

		FFloatReadRef Amplitude;
	};

	//------------------------------------------------------------------------------------
	// FVolumeNode
	//------------------------------------------------------------------------------------
	class FVolumeNode : public FNodeFacade
	{
	public:
		// Constructor used by the Metasound Frontend.
		FVolumeNode(const FNodeInitData& InitData)
			: FNodeFacade(InitData.InstanceName, InitData.InstanceID, TFacadeOperatorClass<FVolumeOperator>())
		{

		}
	};
}
