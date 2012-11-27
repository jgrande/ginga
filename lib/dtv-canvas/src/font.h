#pragma once

#include <string>
#include <vector>

#define DEFAULT_FONT "Tiresias"

namespace canvas {

class Font
{
public:
	Font();
	Font( const std::vector<std::string> &families, size_t size, bool bold=false, bool italic=false, bool smallCaps=false );
	Font( const char *familySeparetedByComa, size_t size, bool bold=false, bool italic=false, bool smallCaps=false );	
	virtual ~Font();
	
	void families( const std::vector<std::string> &families );
	std::string familiesAsString() const;
	void size( size_t size );
	void bold( bool enable );
	void italic( bool enable );
	void smallCaps( bool enable );

	const std::vector<std::string>& families() const;
	size_t size() const;
	bool bold() const;
	bool italic() const;
	bool smallCaps() const;

protected:
	void addDefault();
	
private:
	std::vector<std::string> _families;
	size_t _size;
	bool _bold;
	bool _italic;
	bool _smallCaps;
};

}

