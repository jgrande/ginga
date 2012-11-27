#include "log.h"
#include "log/api.h"
#include "cfg/configregistrator.h"
#include "cfg/propertynode.h"
#include "generated/config.h"
#include <boost/filesystem.hpp>


#if LOG_USE_LOG
// LOG_LEVELS: none, error, warn, info, debug, trace, all
REGISTER_INIT_CONFIG( log ) {
	std::string bType(BUILD_TYPE);
	std::string level = (bType=="Release") ? "warn" : "info";
	boost::filesystem::path path( DATA_PREFIX_PATH );
	path /= "tool.log";

	root().addNode("log")
		.addValue("enabled", "Logging is enabled/disabled", true);

	root()("log").addNode("filter").addNode("all")
		.addValue("all", "Level to log for all categories in this group", level );

	root()("log").addNode("output").addNode("stdout")
		.addValue("use", "Log to cout?", true );

	root()("log.output").addNode("file")
		.addValue("use", "Log to file?", false )
		.addValue("filename", "Full name of the file where the log will be directed", path.string());
}
#endif //LOG_USE_LOG

namespace util {
namespace log {

#if LOG_USE_LOG
static bool _logEnabled;

static void addOutputs() {
	bool useCout = util::cfg::getValue<bool>("log.output.stdout.use");
	bool useFile = util::cfg::getValue<bool>("log.output.file.use");
	if (useCout) {
		addStdout();
	}
	if (useFile) {
		std::string file = util::cfg::getValue<std::string>("log.output.file.filename");
		addLogFile(file);
	}
}

typedef std::pair<std::string, std::string> Category;
struct Visitor {
	std::map<std::string, std::string> _categories;
	void operator()( cfg::PropertyNode *p ) {
		p->visitValues(*this);
		BOOST_FOREACH(  Category c, _categories ) {
			setLevel(p->name().c_str(), c.first.c_str(), c.second.c_str());
		}
		_categories.clear();
	}
	void operator()( cfg::PropertyValue *v ) {
		_categories[v->name()] = v->get<std::string>();
	}
};
static void loadLevels() {
	Visitor nodeVisitor;

	cfg::PropertyNode &groups = cfg::get(std::string("log.filter"));
	groups.visitNodes(nodeVisitor);
}

void init() {
	_logEnabled = cfg::getValue<bool>("log.enabled");
	if (_logEnabled) {
		initialize( cfg::getValue<std::string>("log.filter.all.all") );
		addOutputs();
		loadLevels();
	}
}

void flush() {
	if (_logEnabled) {
		flushMessages();
	}
}

void fin() {
	if (_logEnabled) {
		finalize();
	}
}

#else //LOG_USE_LOG

void init() {}
void flush() {}
void fin() {}

#endif //LOG_USE_LOG

}
}
