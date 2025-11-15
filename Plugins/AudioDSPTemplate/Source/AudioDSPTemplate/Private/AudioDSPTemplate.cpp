#include "AudioDSPTemplate.h"
#include "MetasoundFrontendModuleRegistrationMacros.h"

#define LOCTEXT_NAMESPACE "FAudioDSPTemplateModule"

void FAudioDSPTemplateModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	METASOUND_REGISTER_ITEMS_IN_MODULE
}

void FAudioDSPTemplateModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.	 For modules that support dynamic reloading,
	// we call this function before unloading the module.
	METASOUND_UNREGISTER_ITEMS_IN_MODULE
}

#undef LOCTEXT_NAMESPACE

METASOUND_IMPLEMENT_MODULE_REGISTRATION_LIST

IMPLEMENT_MODULE(FAudioDSPTemplateModule, AudioDSPTemplate)
