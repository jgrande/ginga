#include "ginga.h"
#include "generated/config.h"
#include <ncl30-presenter/presentationenginemanager.h>
#include <gingaplayer/system.h>
#include <gingaplayer/device.h>
#include <util/log.h>
#include <util/cfg/cfg.h>
#include <util/cfg/cmd/commandline.h>
#include <boost/filesystem/operations.hpp>
#include <string.h>
#include <stdio.h>

namespace fs = boost::filesystem;
namespace bptgn = br::pucrio::telemidia::ginga::ncl;

CREATE_TOOL(Ginga,GINGA)

Ginga::Ginga(const std::string &name, const std::string &desc, const std::string &version, const std::string &build)
	: Tool(name, desc, version, build) {
}
Ginga::~Ginga() {
}

//Configuration
void Ginga::registerProperties( util::cfg::cmd::CommandLine &cmd ) {
	Tool::registerProperties( cmd );

	registerToolProp("ncl","Start ncl file", std::string(""), cmd);
	registerToolProp("baseId", 'i', "Set the BaseId name", std::string("-1"), cmd);	
}

int Ginga::run( util::cfg::cmd::CommandLine &cmd ) {
	printf("\n   --------------------------| Ginga.ar %s |--------------------------\n", version().c_str());

	//	Set windows title
	util::cfg::setValue("gui.window.title", "Ginga");

	fs::path url( getCfg<std::string> ("ncl") );

	if (!url.is_absolute()) {
		url = fs::current_path() / url;
	}

	if (exists(url) && is_regular_file(url)) {
		player::System *sys = new player::System();
		player::Device *dev = NULL;

		UNUSED(cmd);
		dev = new player::Device( sys );		
		assert(dev);

		//	Initialize device and add to system
		if (dev->initialize()) {
			sys->addDevice( dev );

			//	Create presentation engine manager
			bptgn::PresentationEngineManager *pem = new bptgn::PresentationEngineManager(sys);
			pem->setBaseId( getCfg<std::string> ("baseId") );
			if (pem->startDocument( url.string() )) {
				pem->run();
			}
			delete pem;
		} else {
			LERROR( "Ginga", "Cannot initialize device" );
		}

		sys->destroy();
		delete sys;
	} else {
		LERROR( "Ginga", "invalid ncl file path: url=%s", url.string().c_str());
	}

	LINFO("Ginga", "Process finished.");
	return 0;
}

void Ginga::printVersion() const {
	printf("Ginga.ar %s by LIFIA\n\
Based on Ginga 0.11.2\n\
Copyright 2002-2010 The TeleMidia PUC-Rio Team.\n\
Copyright 2010 LIFIA - Facultad de Informática - Univ. Nacional de La Plata\n", version().c_str());
}
