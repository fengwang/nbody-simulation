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
#ifndef _GAUSSIAN_TAIL_HPP_INCLUDED_OIHJ3LKJAFS98UYH3KJHFAS9I8UHY2QR3OIUHFSIOUHEIUHY3
#define _GAUSSIAN_TAIL_HPP_INCLUDED_OIHJ3LKJAFS98UYH3KJHFAS9I8UHY2QR3OIUHFSIOUHEIUHY3

#include <vg/distribution/normal.hpp>

#include <cassert>

namespace vg
{

    template <   typename Return_Type,
                 typename Engine
             >
    struct gaussian_tail : private normal<Return_Type, Engine>
    {
            typedef Return_Type                         return_type;
            typedef Engine                              engine_type;

            typedef normal<return_type, engine_type>    normal_type;

            typedef typename normal_type::final_type    final_type;
            typedef typename normal_type::seed_type     seed_type;

            return_type a_;
            return_type variance_;
            engine_type e_;

            explicit gaussian_tail( const return_type a = 0,
                                    const return_type variance = 1,
                                    const seed_type sd = 0 )
                : a_( a ), variance_( variance ), e_( sd )
            {
                assert( variance > 0 );
            }

            return_type
            operator()()
            {
                return do_generation( a_, variance_ );
            }

        protected:
            return_type
            do_generation( const final_type A, const final_type Variance )
            {
                if ( Variance > A )
                    { return gaussian_tail_direct_impl( A, Variance ); }

                return rectangle_wedge_tail_method( A, Variance );
            }

        private:
            return_type
            rectangle_wedge_tail_method( const final_type A, const final_type Variance )
            {
                const final_type s = A / Variance;

                for ( ;; )
                {
                    const final_type u = e_();
                    const final_type v = e_();

                    if ( final_type( 0 ) == u || final_type( 0 ) == v )
                        { continue; }

                    const final_type x = std::sqrt( s * s - std::log( v ) );

                    if ( s >= x * u )
                        { return static_cast<return_type>( x * Variance ); }
                }
            }

            return_type
            gaussian_tail_direct_impl( const final_type A, const final_type Variance )
            {
                const final_type s = A / Variance;

                for ( ;; )
                {
                    const final_type ans = normal<Return_Type, Engine>:: do_generation();

                    if ( ans >= s )
                        { return ans; }
                }
            }
    };

}//vg


#endif//_GAUSSIAN_TAIL_HPP_INCLUDED_OIHJ3LKJAFS98UYH3KJHFAS9I8UHY2QR3OIUHFSIOUHEIUHY3


