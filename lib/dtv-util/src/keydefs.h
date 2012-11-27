/*******************************************************************************

  Copyright (C) 2010, 2011 LIFIA - Facultad de Informatica - Univ. Nacional de La Plata

********************************************************************************

  This file is part of DTV-util implementation.

    DTV-util is free software: you can redistribute it and/or modify it
  under the terms of the GNU Lesser General Public License as published by the Free
  Software Foundation, either version 2 of the License.

    DTV-util is distributed in the hope that it will be useful, but WITHOUT ANY
  WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
  A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License along with
  this program. If not, see <http://www.gnu.org/licenses/>.

********************************************************************************

  Este archivo es parte de la implementación de DTV-util.

    DTV-util es Software Libre: Ud. puede redistribuirlo y/o modificarlo
  bajo los términos de la Licencia Pública General Reducida GNU como es publicada por la
  Free Software Foundation, según la versión 2 de la licencia.

    DTV-util se distribuye esperando que resulte de utilidad, pero SIN NINGUNA
  GARANTÍA; ni siquiera la garantía implícita de COMERCIALIZACIÓN o ADECUACIÓN
  PARA ALGÚN PROPÓSITO PARTICULAR. Para más detalles, revise la Licencia Pública
  General Reducida GNU.

    Ud. debería haber recibido una copia de la Licencia Pública General Reducida GNU
  junto a este programa. Si no, puede verla en <http://www.gnu.org/licenses/>.

*******************************************************************************/
#ifndef KEYDEFS_H
#define KEYDEFS_H

#include <set>

#define UTIL_KEY_LIST(fnc)					             \
		fnc( number_0          , NUMBER_0          ) \
		fnc( number_1          , NUMBER_1          ) \
		fnc( number_2          , NUMBER_2          ) \
		fnc( number_3          , NUMBER_3          ) \
		fnc( number_4          , NUMBER_4          ) \
		fnc( number_5          , NUMBER_5          ) \
		fnc( number_6          , NUMBER_6          ) \
		fnc( number_7          , NUMBER_7          ) \
		fnc( number_8          , NUMBER_8          ) \
		fnc( number_9          , NUMBER_9          ) \
		fnc( small_a           , SMALL_A           ) \
		fnc( small_b           , SMALL_B           ) \
		fnc( small_c           , SMALL_C           ) \
		fnc( small_d           , SMALL_D           ) \
		fnc( small_e           , SMALL_E           ) \
		fnc( small_f           , SMALL_F           ) \
		fnc( small_g           , SMALL_G           ) \
		fnc( small_h           , SMALL_H           ) \
		fnc( small_i           , SMALL_I           ) \
		fnc( small_j           , SMALL_J           ) \
		fnc( small_k           , SMALL_K           ) \
		fnc( small_l           , SMALL_L           ) \
		fnc( small_m           , SMALL_M           ) \
		fnc( small_n           , SMALL_N           ) \
		fnc( small_o           , SMALL_O           ) \
		fnc( small_p           , SMALL_P           ) \
		fnc( small_q           , SMALL_Q           ) \
		fnc( small_r           , SMALL_R           ) \
		fnc( small_s           , SMALL_S           ) \
		fnc( small_t           , SMALL_T           ) \
		fnc( small_u           , SMALL_U           ) \
		fnc( small_v           , SMALL_V           ) \
		fnc( small_w           , SMALL_W           ) \
		fnc( small_x           , SMALL_X           ) \
		fnc( small_y           , SMALL_Y           ) \
		fnc( small_z           , SMALL_Z           ) \
		fnc( capital_a         , CAPITAL_A         ) \
		fnc( capital_b         , CAPITAL_B         ) \
		fnc( capital_c         , CAPITAL_C         ) \
		fnc( capital_d         , CAPITAL_D         ) \
		fnc( capital_e         , CAPITAL_E         ) \
		fnc( capital_f         , CAPITAL_F         ) \
		fnc( capital_g         , CAPITAL_G         ) \
		fnc( capital_h         , CAPITAL_H         ) \
		fnc( capital_i         , CAPITAL_I         ) \
		fnc( capital_j         , CAPITAL_J         ) \
		fnc( capital_k         , CAPITAL_K         ) \
		fnc( capital_l         , CAPITAL_L         ) \
		fnc( capital_m         , CAPITAL_M         ) \
		fnc( capital_n         , CAPITAL_N         ) \
		fnc( capital_o         , CAPITAL_O         ) \
		fnc( capital_p         , CAPITAL_P         ) \
		fnc( capital_q         , CAPITAL_Q         ) \
		fnc( capital_r         , CAPITAL_R         ) \
		fnc( capital_s         , CAPITAL_S         ) \
		fnc( capital_t         , CAPITAL_T         ) \
		fnc( capital_u         , CAPITAL_U         ) \
		fnc( capital_v         , CAPITAL_V         ) \
		fnc( capital_w         , CAPITAL_W         ) \
		fnc( capital_x         , CAPITAL_X         ) \
		fnc( capital_y         , CAPITAL_Y         ) \
		fnc( capital_z         , CAPITAL_Z         ) \
		fnc( page_down         , PAGE_DOWN         ) \
		fnc( page_up           , PAGE_UP           ) \
		fnc( f1                , F1                ) \
		fnc( f2                , F2                ) \
		fnc( f3                , F3                ) \
		fnc( f4                , F4                ) \
		fnc( f5                , F5                ) \
		fnc( f6                , F6                ) \
		fnc( f7                , F7                ) \
		fnc( f8                , F8                ) \
		fnc( f9                , F9                ) \
		fnc( f10               , F10               ) \
		fnc( f11               , F11               ) \
		fnc( f12               , F12               ) \
		fnc( plus_sign         , PLUS_SIGN         ) \
		fnc( minus_sign        , MINUS_SIGN        ) \
		fnc( asterisk          , ASTERISK          ) \
		fnc( number_sign       , NUMBER_SIGN       ) \
		fnc( period            , PERIOD            ) \
		fnc( super             , SUPER             ) \
		fnc( printscreen       , PRINTSCREEN       ) \
		fnc( menu              , MENU              ) \
		fnc( info              , INFO              ) \
		fnc( epg               , EPG               ) \
		fnc( cursor_down       , CURSOR_DOWN       ) \
		fnc( cursor_left       , CURSOR_LEFT       ) \
		fnc( cursor_right      , CURSOR_RIGHT      ) \
		fnc( cursor_up         , CURSOR_UP         ) \
		fnc( channel_down      , CHANNEL_DOWN      ) \
		fnc( channel_up        , CHANNEL_UP        ) \
		fnc( volume_down       , VOLUME_DOWN       ) \
		fnc( volume_up         , VOLUME_UP         ) \
		fnc( enter             , ENTER             ) \
		fnc( ok                , OK                ) \
		fnc( red               , RED               ) \
		fnc( green             , GREEN             ) \
		fnc( yellow            , YELLOW            ) \
		fnc( blue              , BLUE              ) \
		fnc( backspace         , BACKSPACE         ) \
		fnc( back              , BACK              ) \
		fnc( escape            , ESCAPE            ) \
		fnc( exit              , EXIT              ) \
		fnc( power             , POWER             ) \
		fnc( rewind            , REWIND            ) \
		fnc( stop              , STOP              ) \
		fnc( eject             , EJECT             ) \
		fnc( play              , PLAY              ) \
		fnc( record            , RECORD            ) \
		fnc( pause             , PAUSE             ) \
		fnc( greater_than_sign , GREATER_THAN_SIGN ) \
		fnc( less_than_sign    , LESS_THAN_SIGN    ) \
		fnc( tap               , TAP               ) \
		fnc( mute              , MUTE              ) \
		fnc( audio             , AUDIO             ) \
		fnc( channel           , CHANNEL           ) \
		fnc( favorites         , FAVORITES         ) \
		fnc( subtitle          , SUBTITLE          ) \
		fnc( aspect            , ASPECT            ) \
		fnc( ch34              , CH34              ) \
		fnc( video             , VIDEO             ) \


namespace util {
namespace key {

/**
* @brief Enumeration for key identification.
*/

#define DO_ENUM_KEY( c, n ) c,
enum type {
	null = 0,
	UTIL_KEY_LIST(DO_ENUM_KEY)
	LAST
};
#undef DO_ENUM_KEY

typedef std::set<type> Keys;

//	Returns key name
const char *getKeyName( type kValue );
type getKey( const char *keyName );

}
}

#endif /* KEYDEFS_H */

