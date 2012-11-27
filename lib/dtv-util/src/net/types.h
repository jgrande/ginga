#pragma once

#include "../types.h"

namespace util {
namespace net {

namespace family { 
	enum type { ipv4=2, ipv6=28 };
}

namespace type {
	enum type { stream=0x1, dgram=0x2, raw=0x3 };
}

namespace fd {
	enum type { read=0x1, write=0x2, close=0x20, accept=0x08 };
}

namespace sd {
	enum type { recv=0x0, snd=0x1, both=0x2 };
}

}
}

