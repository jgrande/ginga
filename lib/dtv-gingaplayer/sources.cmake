
SET( ${PROJECT_NAME}_HEADER_FILES
	src/types.h
	src/player.h
	src/property/property.h
	src/property/types.h
	src/player/settings.h
	src/player/lua/event/types.h
	src/device.h
	src/system.h
	src/input/input.h
)

SET ( ${PROJECT_NAME}_SOURCE_FILES
  ${${PROJECT_NAME}_HEADER_FILES}
	src/types.cpp
	src/device.cpp
	src/system.cpp
	src/player.cpp
	src/player/timelinetimer.cpp
	src/player/graphicplayer.cpp
	src/player/surfaceproperties.cpp
	src/player/soundproperties.cpp
	src/player/graphicproperties.cpp
	src/player/focusproperties.cpp
	src/player/imageplayer.cpp
	src/player/animeplayer.cpp
	src/player/textplayer.cpp
	src/player/settings.cpp
	src/player/soundplayer.cpp
	src/player/videoplayer.cpp
	src/player/htmlplayer.cpp
	src/player/luaplayer.cpp
	src/player/lua/lua.cpp
	src/player/lua/event/types.cpp
	src/player/lua/event/event.cpp
	src/player/lua/event/class/key.cpp
	src/player/lua/event/class/ncl.cpp
	src/player/lua/event/class/user.cpp
	src/player/lua/event/class/tcp.cpp
	src/player/lua/canvas/canvas.cpp
	src/player/lua/canvas/surfacewrapper.cpp
	src/player/lua/settings/settings.cpp
	src/input/input.h
	src/input/manager.cpp
	src/property/types.cpp
	src/property/property.cpp
	src/property/compositeproperty.cpp
)


