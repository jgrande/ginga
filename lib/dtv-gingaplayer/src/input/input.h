#pragma once

#include <util/keydefs.h>
#include <boost/function.hpp>
#include <boost/bind.hpp>

namespace player {
namespace input {

//	Input keys
typedef boost::function<void (::util::key::type key, bool isUp )> InputCallback;
typedef boost::function<void (::util::key::Keys keys)> ReservedKeysCallback;
typedef void* ListenerId;

}
}

