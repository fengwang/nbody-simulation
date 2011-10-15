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
#ifndef _GUMBEL_2_HPP_INCLUDED_DSOIUJ3498AFSLKJH4938UYAFKLJI34OIUAFSLKJ3OIJFSDLK
#define _GUMBEL_2_HPP_INCLUDED_DSOIUJ3498AFSLKJH4938UYAFKLJI34OIUAFSLKJ3OIJFSDLK

#include <cmath>
#include <cassert>

namespace vg
{

#if 0
    f( x | a, b ) = a b x ^ { -a - 1} e ^ { -b x ^ { -a}}\,

    for 0 < x < \infty.
#endif

template <   typename Return_Type,
             typename Engine
         >
struct gumbel_2
{
        typedef typename Engine::final_type     final_type;
        typedef Return_Type                     return_type;
        typedef typename Engine::seed_type      seed_type;
        typedef typename Engine::size_type      size_type;
        typedef Engine                          engine_type;

        final_type  a_;
        final_type  b_;
        engine_type e_;

        explicit gumbel_2( const return_type a = 1, const return_type b = 1, const seed_type sd = 0 )
                : a_( a ), b_( b ), e_( sd )
            {
                assert( b > 0 );
            }

            return_type
            operator()()
            {
                return do_generation( a_, b_ );
            }

        protected:
            return_type
            do_generation( const return_type a, const return_type b )
            {
                return direct_impl( a, b );
            }

        private:
            return_type
            direct_impl( const return_type a, const return_type b )
            {
                final_type x = e_();

                while ( final_type( 0 ) == x )
                {
                    x = e_();
                }

                const final_type ans = std::pow( -b / std::log( x ), final_type( 1 ) / a );

                return ans;
            }

    };

}//namespace vg

#endif//_GUMBEL_2_HPP_INCLUDED_DSOIUJ3498AFSLKJH4938UYAFKLJI34OIUAFSLKJ3OIJFSDLK

