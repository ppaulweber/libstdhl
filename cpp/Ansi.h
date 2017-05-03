//
//  Copyright (c) 2014-2017 Philipp Paulweber
//  All rights reserved.
//
//  Developed by: Philipp Paulweber
//                Emmanuel Pescosta
//                https://github.com/ppaulweber/libstdhl
//
//  This file is part of libstdhl.
//
//  libstdhl is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//
//  libstdhl is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with libstdhl. If not, see <http://www.gnu.org/licenses/>.
//

#ifndef _LIB_STDHL_CPP_ANSI_H_
#define _LIB_STDHL_CPP_ANSI_H_

#include "Default.h"
#include "Type.h"

/**
   @brief    TODO

   TODO
*/

namespace libstdhl
{
    /**
       @extends Stdhl
    */
    namespace Ansi
    {
        enum class Style
        {
            BOLD = 0,
            FAINT = 1,
            ITALIC = 2,
            UNTERLINE = 3,
            BLINK = 4,
        };

        enum class Color
        {
            BLACK = 0,
            RED = 1,
            GREEN = 2,
            YELLOW = 3,
            BLUE = 4,
            MAGENTA = 5,
            CYAN = 6,
            WHITE = 7,
        };

        enum class SGR
        {
            RESET = 0,

            BOLD_ON = 1,
            FAINT_ON = 2,
            ITALIC_ON = 3,
            UNTERLINE_ON = 4,
            BLINK_ON = 5,

            RESERVED_6 = 6,

            IMAGE_NEGATIVE = 7,
            CONCEAL = 8,
            CROSSEDOUT = 9,

            FONT_DEFAULT = 10,
            FONT_ALTERNATE_1 = 11,
            FONT_ALTERNATE_2 = 12,
            FONT_ALTERNATE_3 = 13,
            FONT_ALTERNATE_4 = 14,
            FONT_ALTERNATE_5 = 15,
            FONT_ALTERNATE_6 = 16,
            FONT_ALTERNATE_7 = 17,
            FONT_ALTERNATE_8 = 18,
            FONT_ALTERNATE_9 = 19,

            FONT_FRAKTUR = 20,

            BOLD_OFF = 21,
            FAINT_OFF = 22,
            ITALIC_OFF = 23,
            UNTERLINE_OFF = 24,
            BLINK_OFF = 25,

            RESERVED_26 = 26,

            IMAGE_POSITIVE = 27,
            CONCEAL_OFF = 28,
            CROSSEDOUT_OFF = 29,

            FOREGROUND_BLACK = 30,
            FOREGROUND_RED = 31,
            FOREGROUND_GREEN = 32,
            FOREGROUND_YELLOW = 33,
            FOREGROUND_BLUE = 34,
            FOREGROUND_MAGENTA = 35,
            FOREGROUND_CYAN = 36,
            FOREGROUND_WHITE = 37,
            FOREGROUND_EXTENSION = 38,
            FOREGROUND_DEFAULT = 39,

            BACKGROUND_BLACK = 40,
            BACKGROUND_RED = 41,
            BACKGROUND_GREEN = 42,
            BACKGROUND_YELLOW = 43,
            BACKGROUND_BLUE = 44,
            BACKGROUND_MAGENTA = 45,
            BACKGROUND_CYAN = 46,
            BACKGROUND_WHITE = 47,
            BACKGROUND_EXTENSION = 48,
            BACKGROUND_DEFAULT = 49,

            RESERVED_50 = 50,

            FRAMED_ON = 51,
            ENCIRCLED_ON = 52,
            OVERLINED_ON = 53,

            FRAMED_OFF = 54,
            OVERLINED_OFF = 55,
        };

        std::string CSI( SGR command, const std::string& option = "" );

        template < const SGR ENABLE, const SGR DISABLE >
        std::string format( const std::string& text )
        {
            return CSI( ENABLE ) + text + CSI( DISABLE );
        }

        template < const Style STYLE >
        std::string format( const std::string& text )
        {
            const auto enable
                = ( SGR )( (std::size_t)SGR::BOLD_ON + (std::size_t)STYLE );

            const auto disable
                = ( SGR )( (std::size_t)SGR::BOLD_OFF + (std::size_t)STYLE );

            return format< enable, disable >( text );
        }

        template < const Color COLOR >
        std::string format(
            const std::string& text, const u1 background = false )
        {
            if( not background )
            {
                const auto color = ( SGR )(
                    (std::size_t)SGR::FOREGROUND_BLACK + (std::size_t)COLOR );

                return format< color, SGR::FOREGROUND_DEFAULT >( text );
            }
            else
            {
                const auto color = ( SGR )(
                    (std::size_t)SGR::BACKGROUND_BLACK + (std::size_t)COLOR );

                return format< color, SGR::BACKGROUND_DEFAULT >( text );
            }
        }

        // 24bit RGB -- ISO/IEC 8613-6 : 1994 (E) -- ITU-T Rec. T.416 (1993 E)
        template < const u8 R, const u8 G, const u8 B >
        std::string format(
            const std::string& text, const u1 background = false )
        {
            const auto option = ";2;" + std::to_string( R ) + ";"
                                + std::to_string( G ) + ";"
                                + std::to_string( B );

            if( not background )
            {
                return CSI( SGR::FOREGROUND_EXTENSION, option ) + text
                       + CSI( SGR::FOREGROUND_DEFAULT );
            }
            else
            {
                return CSI( SGR::BACKGROUND_EXTENSION, option ) + text
                       + CSI( SGR::BACKGROUND_DEFAULT );
            }
        }

        // 32bit CMYK -- ISO/IEC 8613-6 : 1994 (E) -- ITU-T Rec. T.416 (1993 E)
        template < const u8 C, const u8 M, const u8 Y, const u8 K >
        std::string format(
            const std::string& text, const u1 background = false )
        {
            const auto option
                = ";4;" + std::to_string( C ) + ";" + std::to_string( M ) + ";"
                  + std::to_string( Y ) + ";" + std::to_string( K );

            if( not background )
            {
                return CSI( SGR::FOREGROUND_EXTENSION, option ) + text
                       + CSI( SGR::FOREGROUND_DEFAULT );
            }
            else
            {
                return CSI( SGR::BACKGROUND_EXTENSION, option ) + text
                       + CSI( SGR::BACKGROUND_DEFAULT );
            }
        }
    };
}

#endif // _LIB_STDHL_CPP_ANSI_H_

//
//  Local variables:
//  mode: c++
//  indent-tabs-mode: nil
//  c-basic-offset: 4
//  tab-width: 4
//  End:
//  vim:noexpandtab:sw=4:ts=4:
//