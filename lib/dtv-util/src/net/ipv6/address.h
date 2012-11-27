#pragma once

#include "../types.h"
#include <string>

namespace util {
namespace net {
namespace ipv6 {

class Address {
public:
	Address( void );
	~Address( void );

	std::string asString() const;
};

}
}
}

