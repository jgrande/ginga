SET( ${PROJECT_NAME}_HEADER_FILES
	src/functions.h
	src/string.h
	src/singleton.h
	src/debugging_aids.h
	src/buffer.h
	src/any.h
	src/types.h
	src/mcr.h
	src/fs.h
	src/resourcepool.h
	src/keydefs.h
	src/task.h
	src/taskqueue.h
	src/tool.h
	src/registrator.h
	src/cfg/cfg.h
	src/cfg/propertynode.h
	src/cfg/propertyvalue.h
	src/cfg/treepath.h
	src/cfg/configregistrator.h
	src/cfg/cmd/commandline.h
	src/cfg/cmd/option.h
	src/id/ident.h
	src/id/pool.h
	src/io/dispatcher.h
	src/log.h
	src/log/api.h
	src/log/const.h
	src/process/process.h
	src/process/types.h
	src/net/types.h
	src/net/socket.h
	src/net/sockaddr.h
	src/net/ipv4/address.h
	src/net/ipv4/sockaddr.h
	src/net/ipv6/address.h
	src/net/ipv6/sockaddr.h
)

SET( ${PROJECT_NAME}_SOURCE_FILES
	${${PROJECT_NAME}_HEADER_FILES}
	src/keydefs.cpp
	src/functions.cpp
	src/resourcepool.cpp
	src/buffer.cpp
	src/fs.cpp
	src/string.cpp
	src/taskqueue.cpp
	src/tool.cpp
	src/registrator.cpp
	src/cfg/propertyvalue.cpp
	src/cfg/propertynode.cpp
	src/cfg/treepath.cpp
	src/cfg/cfg.cpp
	src/cfg/configregistrator.cpp
	src/cfg/xmlparser.cpp
	src/cfg/cmd/commandline.cpp
	src/cfg/cmd/option.cpp
	src/log.cpp
	src/io/dispatcher.cpp
	src/id/ident.cpp
	src/id/pool.cpp
	src/process/process.cpp
	src/net/socket.cpp
	src/net/sockaddr.cpp
	src/net/ipv4/address.cpp
	src/net/ipv4/sockaddr.cpp
	src/net/ipv6/address.cpp
	src/net/ipv6/sockaddr.cpp
)