using UnrealBuildTool;
using System.Collections.Generic;

public class UEAudioDSPTemplateTarget : TargetRules
{
	public UEAudioDSPTemplateTarget( TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		IncludeOrderVersion	 = EngineIncludeOrderVersion.Latest;
		DefaultBuildSettings = BuildSettingsVersion.V2;
		ExtraModuleNames.AddRange( new string[] { "UEAudioDSPTemplate" } );
	}
}
