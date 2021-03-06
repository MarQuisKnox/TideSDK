/**
 * Copyright (c) 2012 - 2014 TideSDK contributors
 * http://www.tidesdk.org
 * Includes modified sources under the Apache 2 License
 * Copyright (c) 2008 - 2012 Appcelerator Inc
 * Refer to LICENSE for details of distribution and use.
 **/

#include <tideutils/file_utils.h>
using namespace TideUtils;

#include "app_module.h"
#include "app_config.h"
#include "app_binding.h"
#include "properties_binding.h"
#include <Poco/File.h>

namespace ti
{
	TIDE_MODULE(AppModule, STRING(MODULE_NAME), STRING(MODULE_VERSION));

	static Logger* GetLogger()
	{
		static Logger* logger = Logger::Get("App");
		return logger;
	}

	void AppModule::Initialize()
	{
		// Nudge the creation of the first app config instance.
		AppConfig* config = AppConfig::Instance();
		if (config)
			GetLogger()->Debug("Loaded config file successfully");

		TiObjectRef global(host->GetGlobalObject());
		TiObjectRef binding = new AppBinding(host, host->GetGlobalObject());
		host->GetGlobalObject()->SetObject("App", binding);

		// Create the data directory for the app, if it doesn't exist.
		std::string dataPath(host->GetApplication()->GetDataPath());
		Poco::File dataPathFile(dataPath);
		if (!dataPathFile.exists())
			dataPathFile.createDirectories();

		std::string propFilename(FileUtils::Join(
			dataPath.c_str(), "application.properties", 0));

		// @tiapi(property=True,type=App.Properties,name=App.Properties,since=0.2)
		// @tiapi The application's private Properties object
		binding->SetObject("Properties", new PropertiesBinding(propFilename));
	}

	void AppModule::Stop()
	{
		host->GetGlobalObject()->SetNull("App");
	}
}
