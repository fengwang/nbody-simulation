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
#ifndef _GAMMA_HPP_INCLUDED_2I8HJFASKJLNHVJMNXVUHNZVSJHWOIUHAP9I3LKJSOIUJ3OIJSIA
#define _GAMMA_HPP_INCLUDED_2I8HJFASKJLNHVJMNXVUHNZVSJHWOIUHAP9I3LKJSOIUJ3OIJSIA

#include <vg/distribution/normal.hpp>

#include <cmath>
#include <cassert>

namespace vg
{

    template <   typename Return_Type,
                 typename Engine
             >
    struct gamma : private normal<Return_Type, Engine>
    {
            typedef normal<Return_Type, Engine>                 normal_type;
            typedef Return_Type                         		return_type;
            typedef Engine                              		engine_type;
            typedef return_type                                 value_type;
            typedef typename engine_type::size_type          	size_type;
            typedef typename engine_type::final_type    	    final_type;
            typedef typename engine_type::seed_type     	    seed_type;

            value_type          a_;
            value_type          b_;
            engine_type         e_;

            explicit gamma(	const value_type a = value_type( 1 ),
                            const value_type b = value_type( 1 ),
                            const seed_type sd = 0 )
                : a_( a ), b_( b ), e_( sd )
            {
                assert( a > 0 );
                assert( b > 0 );
            }

            return_type
            operator()()
            {
                return do_generation( a_, b_ );
            }

        protected:
            return_type
            do_generation( const final_type A, const final_type B )
            {
                return marsaglia_tsang_method( A ) * B;
            }

            return_type
            do_generation( const final_type A )
            {
                return marsaglia_tsang_method( A );
            }

        private:
            //Marsaglia and Tsang, "A Simple Method for generating gamma variables",
            //ACM Transactions on Mathematical Software, Vol 26, No 3 (2000), p363-372.
            return_type
            marsaglia_tsang_method( const final_type A )
            {
                const final_type a = A < final_type( 1 ) ? A + final_type( 1 ) : A;
                const final_type d = a - final_type( 1 ) / final_type( 3 );
                const final_type c = final_type( 1 ) / final_type( 3 ) / std::sqrt( d );
                final_type u( 0 );
                final_type v( 0 );
                final_type x( 0 );

                for ( ;; )
                {
                    for ( ;; )
                    {
                        x = normal_type::do_generation(); //normal distribution
                        v = final_type( 1 ) + c * x;

                        if ( v > 0 )
                            { break; }
                    }

                    const final_type xx = x * x;

                    v *= v * v;

                    u = e_();

                    if ( u < final_type( 1 ) - final_type( 0.0331 ) * xx * xx )
                        { break; }

                    if ( std::log( u ) < 0.5 * xx + d *( final_type( 1 ) - v + std::log( v ) ) )
                        { break; }
                }

                final_type ans = d * v;

                if ( A < 1 )
                    { ans *= std::pow( e_(), final_type( 1 ) / A ); }

                return ans;
            }

    };
}//vg

#endif//_GAMMA_HPP_INCLUDED_2I8HJFASKJLNHVJMNXVUHNZVSJHWOIUHAP9I3LKJSOIUJ3OIJSIA




