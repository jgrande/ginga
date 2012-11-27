#pragma once

#include <string>

namespace util {
namespace cfg {

class TreePath {
public:
	explicit TreePath( const std::string &str );
	virtual ~TreePath();

	const std::string property() const;
	const std::string root() const;
	const std::string withoutRoot() const;
	const std::string path() const;
	const std::string &string() const;
	bool walkable() const;

private:
	std::string _path;

};

}
}
