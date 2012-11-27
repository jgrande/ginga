
SET( ${PROJECT_NAME}_HEADER_FILES
	src/types.h
	src/system.h
	src/color.h
	src/canvas.h
	src/types.h
	src/rect.h
	src/size.h
	src/font.h
	src/point.h
	src/surface.h
	src/alignment.h
	src/webviewer.h
	src/window.h
	src/input.h
	src/player.h
	src/mediaplayer.h
	src/mediaplayerimpl.h
)

SET ( ${PROJECT_NAME}_SOURCE_FILES
  ${${PROJECT_NAME}_HEADER_FILES}
    src/system.cpp
	src/surface.cpp
	src/canvas.cpp
	src/color.cpp
	src/point.cpp
	src/rect.cpp
	src/size.cpp
	src/font.cpp
	src/player.cpp
	src/mediaplayer.cpp
	src/mediaplayerimpl.cpp
	src/videooverlay.cpp
	src/input.cpp
	src/dummy/window.cpp
	src/dummy/canvas.cpp
	src/dummy/surface.cpp
	src/dummy/player.cpp
	src/dummy/mediaplayer.cpp
	src/dummy/dummywebviewer.cpp
	src/custom/system.cpp
	src/webviewer.cpp
	src/window.cpp
)

