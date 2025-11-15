using UnrealBuildTool;
using System.Collections.Generic;

public class UEAudioDSPTemplateTarget : TargetRules
{
	public UEAudioDSPTemplateTarget( TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.Latest;
		IncludeOrderVersion	 = EngineIncludeOrderVersion.Latest;
		ExtraModuleNames.AddRange( new string[] { "UEAudioDSPTemplate" } );
	}
}
