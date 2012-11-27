#pragma once

namespace canvas {

namespace alignment {
	const int None    = 0;
	const int vTop    = 1 << 1;
	const int vCenter = 1 << 2;
	const int vBottom = 1 << 3;
	const int hLeft   = 1 << 4;
	const int hCenter = 1 << 5;
	const int hRight  = 1 << 6;
}
typedef int Alignment;

}
