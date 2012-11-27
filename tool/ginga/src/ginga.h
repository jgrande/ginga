#pragma once
#include <util/tool.h>

class Ginga : public util::Tool {
public:
	Ginga(const std::string &name, const std::string &desc, const std::string &version, const std::string &build);
	virtual ~Ginga();

protected:
	virtual int run( util::cfg::cmd::CommandLine &cmd );

	//Configuration
	virtual void registerProperties( util::cfg::cmd::CommandLine &cmd );

	virtual void printVersion() const;
};