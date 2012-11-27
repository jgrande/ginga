#pragma once

#include "size.h"
#include <util/types.h>
#include <util/id/ident.h>
#include <util/keydefs.h>
#include <boost/function.hpp>

namespace canvas {

class System;
class Rect;
class Point;
class Canvas;
class Color;
class Surface;
typedef Surface * SurfacePtr;
struct ImageDataType {
	Size size;
	unsigned char *data;
	int length;
	int bitsPerPixel;
	int bytesPerPixel;
	int stride;
	int dataOffset;
};
typedef struct ImageDataType ImageData;

//	Video
class Window;

#ifdef _WIN32
typedef HANDLE VideoDescription;
#else
typedef struct {
  void *display;
  int   screenID;
  unsigned long winID;
} VideoDescription;
#endif
class VideoOverlay;
typedef VideoOverlay *VideoOverlayPtr;

//	Player
typedef long Volume;
class Player;
class MediaPlayer;
typedef MediaPlayer *MediaPlayerPtr;

//	HTML
class WebViewer;

//	Keys
typedef boost::function<void (util::key::type, bool)> KeyCallback;

//	Notify events callback
typedef boost::function<void (void)> NotifyCallback;

//	Events
template<typename T> class Event;
typedef boost::function<void (util::id::Ident &id)> EventCallback;

namespace composition {

enum mode {
	source_over,
	destination_over,
	clear,
	source,
	destination,
	source_in,
	destination_in,
	source_out,
	destination_out,
	source_atop,
	destination_atop,
	x_or,
	plus,
	multiply,
	screen,
	overlay,
	darken,
	lighten,
	color_dodge,
	color_burn,
	hard_light,
	soft_light,
	difference,
	exclusion
};

}	//namespace composition

namespace charset {

enum encoding {
	ISO_8859_1,
	ISO_8859_2,
	ISO_8859_3,
	ISO_8859_4,
	ISO_8859_5,
	ISO_8859_6,
	ISO_8859_7,
	ISO_8859_8,
	ISO_8859_9,
	ISO_8859_10,
	ISO_8859_11,
	ISO_8859_13,
	ISO_8859_14,
	ISO_8859_15,
	ISO_8859_16 
};

}	//namespace charset

}

