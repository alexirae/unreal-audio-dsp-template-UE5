using UnrealBuildTool;
using System.Collections.Generic;

public class UEAudioDSPTemplateEditorTarget : TargetRules
{
	public UEAudioDSPTemplateEditorTarget( TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		IncludeOrderVersion	 = EngineIncludeOrderVersion.Latest;
		DefaultBuildSettings = BuildSettingsVersion.V4;
		ExtraModuleNames.AddRange( new string[] { "UEAudioDSPTemplate" } );
	}
}
