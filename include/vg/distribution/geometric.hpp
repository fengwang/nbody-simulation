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
#ifndef _GEOMETRIC_HPP_INCLUDED_SO8IU298ALKJSDLKJCNO8UJA98Y3OLIAFDPOIHJSDALKJ344
#define _GEOMETRIC_HPP_INCLUDED_SO8IU298ALKJSDLKJCNO8UJA98Y3OLIAFDPOIHJSDALKJ344


#include <cassert>

namespace vg
{

    template <
                typename Return_Type ,
                typename Engine
             >
    struct geometric
    {
            typedef typename Engine::final_type     final_type;
            typedef Return_Type                     return_type;
            typedef Return_Type                     value_type;
            typedef typename Engine::seed_type      seed_type;

            final_type p_;
            Engine e_;

            explicit geometric( final_type p = final_type( 0.5 ),
                                const seed_type s = seed_type( 0 ) )
                : p_( p ), e_( s )
            {
                assert( p > final_type( 0 ) );
                assert( p < final_type( 1 ) );
            }

            return_type
            operator()()
            {
                return do_generation( p_ );
            }

        protected:
            return_type
            do_generation( const final_type P )
            {

                return polar_method( P );
            }

        private:
            return_type
            coin_flip_method( const final_type P )
            {
                value_type ans = 1;

                while ( e_() > P )
                    { ++ans; }

                return ans;
            }

            return_type
            polar_method( const final_type P )
            {
                const final_type u = e_();
                const final_type n = std::ceil( log( u ) / log( final_type( 1 ) - P ) );
                return n;
            }

    };

}//namespace vg



#endif//_GEOMETRIC_HPP_INCLUDED_SO8IU298ALKJSDLKJCNO8UJA98Y3OLIAFDPOIHJSDALKJ344


