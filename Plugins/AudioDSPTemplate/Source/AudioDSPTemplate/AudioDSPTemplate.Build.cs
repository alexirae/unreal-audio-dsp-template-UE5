using UnrealBuildTool;

public class AudioDSPTemplate : ModuleRules
{
	public AudioDSPTemplate(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
        bUseUnity = false;

        PublicIncludePaths.AddRange(
			new string[]
			{
				// ... add public include paths required here ...

			}
		);
				
		
		PrivateIncludePaths.AddRange(
			new string[]
			{
				// ... add private include paths required here ...

			}
		);
			
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				// ... add public dependencies that you statically link with here ...
				"Core",
				"MetasoundFrontend",
				"MetasoundGraphCore",
			}
		);
			
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				// ... add private dependencies that you statically link with here ...	
				"CoreUObject",
				"Engine",
				"SignalProcessing",
			}
		);
		
		
		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
				// ... add any modules that your module loads dynamically here ...

			}
		);

        PrivateDefinitions.Add("METASOUND_PLUGIN=AudioDSPTemplate");
        PrivateDefinitions.Add("METASOUND_MODULE=AudioDSPTemplate");
    }
}
