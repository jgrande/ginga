#include "types.h"
#include <boost/algorithm/string.hpp>
#include <boost/filesystem.hpp>
#include <string.h>

namespace player {

namespace fs = boost::filesystem;

namespace schema {

typedef struct {
	schema::type type;
	const char *name;
} SchemaType;

#define DO_ENUM_SCHEMA_NAMES(n,v) { schema::n, #v },
static SchemaType schemas[] = {
	SCHEMA_TYPES_LIST(DO_ENUM_SCHEMA_NAMES)
	{ schema::LAST, NULL }
};
#undef DO_ENUM_SCHEMA_NAMES

static type find( const std::string &value ) {
	if (!value.empty()) {
		std::string sch=boost::to_lower_copy(value);
		int i=0;
		while (schemas[i].name) {
			if (sch == schemas[i].name) {
				return schemas[i].type;
			}
			i++;
		}
	}
	return schema::unknown;
}

const char *getName( type schType ) {
	if (schType > schema::LAST) {
		schType = schema::unknown;
	}
	return schemas[schType].name;
}

}	//	namespace schema


namespace type {

typedef struct {
	type playerType;
	const char *name;
} PlayerType;
	
#define DO_ENUM_PLAYER_NAMES(n) { n, #n },
static PlayerType playerNames[] = {
	{ unknown, "unknown" },
	PLAYER_TYPES_LIST(DO_ENUM_PLAYER_NAMES)
	{ LAST, NULL }
};
#undef DO_ENUM_PLAYER_NAMES

typedef struct {
	type _type;
	const char *ext;
	const char *mime;
} MimeToPlayers;
	
#define DO_ENUM_MIME_NAMES(t, e, n) { t, #e, #n },
static const MimeToPlayers names[] = {
	{ unknown, "UNKNOWN", "UNKNOWN" },
	MIME_TYPES_LIST(DO_ENUM_MIME_NAMES)
	{ LAST, NULL, NULL },
};
#undef DO_ENUM_MIME_NAMES

const char *getName( type player ) {
	if (player > LAST) {
		player=unknown;
	}
	return playerNames[player].name;
}

const char *getExtensionFromMime( const std::string &mimeType ) {
	if (!mimeType.empty()) {
		std::string mime=boost::to_upper_copy(mimeType);
		int i=0;
		while (names[i].mime) {
			if (mime == names[i].mime) {
				return names[i].ext;
			}
			i++;
		}
	}
 	return NULL;
}

type fromBody( const std::string &body ) {
	if (!body.empty()) {
		fs::path file(body);
		std::string ext=file.extension().string();
		if (!ext.empty()) {
			ext = ext.substr( 1 );		
			boost::to_lower(ext);
			int i=0;
			while (names[i].mime) {
				if (ext == names[i].ext) {
					return names[i]._type;
				}
				i++;
			}
		}
	}
 	return unknown;
}

type fromMime( const std::string &mimeType ) {
	if (!mimeType.empty()) {
		std::string mime=boost::to_upper_copy(mimeType);
		int i=0;
		while (names[i].mime) {
			if (mime == names[i].mime) {
				return names[i]._type;
			}
			i++;
		}
	}
 	return unknown;
}

type get( schema::type schema, const std::string &body, const std::string &mimeType ) {
	type tmp = unknown;
	//	Is mime correct?
	if (mimeType.empty()) {
		tmp=fromBody( body );
	}
	else {
		tmp=fromMime( mimeType );
	}

	if (tmp == unknown && (schema == schema::http || schema == schema::https)) {
		tmp = html;
	}
	return tmp;
}

}	//	namespace type

namespace url {

void parse( const std::string &url, schema::type &schema, std::string &body ) {
	//	scheme://params
	size_t pos=url.find( "://" );
	if (pos != std::string::npos) {
		schema = schema::find( url.substr( 0, pos ) );
		body= url.substr( pos+3 );
	}
	else {
		schema = schema::file;
		body = url;
	}
}

}	//	namespace url

}

