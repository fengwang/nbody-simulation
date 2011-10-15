/*
vg -- random variate generator library 
Copyright (C) 2010-2011  Feng Wang (wanng.fenng@gmail.com) 

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by 
the Free Software Foundation, either version 3 of the License, or 
(at your option) any later version. 

This program is distributed in the hope that it will be useful, 
but WITHOUT ANY WARRANTY; without even the implied warranty of 
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the 
GNU General Public License for more details. 

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#ifndef _DEFAULT_SEED_HPP_INCLUDED_SDFOIUJ4OIUASF8U3OIAUF983ILAUFSO8U34LIUFSDLIJ
#define _DEFAULT_SEED_HPP_INCLUDED_SDFOIUJ4OIUASF8U3OIAUF983ILAUFSO8U34LIUFSDLIJ

#include <cstddef>
#include <ctime>

namespace vg
{

    struct default_seed
    {

        typedef unsigned long long		seed_type;

        seed_type operator()() const
        {
            const seed_type  s = static_cast<seed_type>( time( 0 ) );
            int * i = new int;
            seed_type  ans = s + ( (seed_type)(i) | ((seed_type)(i) << 32) );
            ans = ( ans & 0x5555555555555555ULL ) <<  1 | ( ans & 0xAAAAAAAAAAAAAAAAULL ) >>  1;
            ans = ( ans & 0x3333333333333333ULL ) <<  2 | ( ans & 0xCCCCCCCCCCCCCCCCULL ) >>  2;
            ans = ( ans & 0x0F0F0F0F0F0F0F0FULL ) <<  4 | ( ans & 0xF0F0F0F0F0F0F0F0ULL ) >>  4;
            ans = ( ans & 0x00FF00FF00FF00FFULL ) <<  8 | ( ans & 0xFF00FF00FF00FF00ULL ) >>  8;
            ans = ( ans & 0x0000FFFF0000FFFFULL ) << 16 | ( ans & 0xFFFF0000FFFF0000ULL ) >> 16;
            ans = ( ans & 0x00000000FFFFFFFFULL ) << 32 | ( ans & 0xFFFFFFFF00000000ULL ) >> 32;
            ans |= s;
            delete i;
            return ans;
        }// end of operator ()

    }; // end of struct default_seed

}// end of namespace vg

#endif//_DEFAULT_SEED_HPP_INCLUDED_SDFOIUJ4OIUASF8U3OIAUF983ILAUFSO8U34LIUFSDLIJ

