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
#ifndef _MT19937_HPP_INCLUDED28903RUAFSLDKJASFDOIJ4890UAFOPSI1209AFLKJ34OIUFJKDS
#define _MT19937_HPP_INCLUDED28903RUAFSLDKJASFDOIJ4890UAFOPSI1209AFLKJ34OIUFJKDS

#include <vg/engine/default_seed.hpp>
#include <cstddef>

namespace vg
{

    struct mt19937
    {
            typedef mt19937					self_type;
            typedef long double 			final_type;
            typedef unsigned long long 		value_type;
            typedef value_type 				seed_type;
            typedef std::size_t 			size_type;

        private:
            value_type mt[312];
            value_type mag01[2];
            size_type mti;

        public:
            mt19937( const seed_type s = 0 )
            {
                init( s );
            }

        private:
            void init( const seed_type s )
            {
                mt[0] = s ? s : default_seed()();
                mag01[0] = 0ULL;
                mag01[1] = 0xB5026F5AA96619E9ULL;

                for ( mti = 1; mti < 312; ++mti )
                {
                    mt[mti] =  6364136223846793005ULL * ( mt[mti-1] ^( mt[mti-1] >> 62 ) );
                    mt[mti] += mti;
                }
            }

        public:
            final_type operator()()
            {
                value_type x;

                if ( mti > 311 )
                {
                    for ( size_type i = 0; i < 156; ++i )
                    {
                        x = ( mt[i] & 0xFFFFFFFF80000000ULL ) | ( mt[i+1] & 0x7FFFFFFFULL );
                        mt[i] = mt[i+156] ^( x >> 1 ) ^ mag01[x&1];
                    }

                    for ( size_type i = 156; i < 311; ++i )
                    {
                        x = ( mt[i] & 0xFFFFFFFF80000000ULL ) | ( mt[i+1] & 0x7FFFFFFFULL );
                        mt[i] = mt[i-156] ^( x >> 1 ) ^ mag01[x&1];
                    }

                    x = ( mt[311] & 0xFFFFFFFF80000000ULL ) | ( mt[0] & 0x7FFFFFFFULL );
                    mt[311] = mt[155] ^( x >> 1 ) ^ mag01[x&1];
                    mti = 0;
                }

                x = mt[mti++];
                x ^= ( x >> 29 ) & 0x5555555555555555ULL;
                x ^= ( x << 17 ) & 0x71D67FFFEDA60000ULL;
                x ^= ( x << 37 ) & 0xFFF7EEE000000000ULL;
                x ^= ( x >> 43 );
                const final_type ans =	static_cast<final_type>( static_cast<final_type>( x ) )  /
                                        static_cast<final_type>( static_cast<value_type>( -1 ) );
                return ans;
            }

        private://not to be implemented
            mt19937( const self_type& );
            mt19937& operator = ( const self_type& );
    };

}//namespace vg

#endif//_MT19937_HPP_INCLUDED28903RUAFSLDKJASFDOIJ4890UAFOPSI1209AFLKJ34OIUFJKDS

