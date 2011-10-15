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
#ifndef _LOGNORMAL_HPP_INCLUDED_SODIJASOI84U98AU7FSKLJ349P8AFSLIU3498UAFSLIU34OI
#define _LOGNORMAL_HPP_INCLUDED_SODIJASOI84U98AU7FSKLJ349P8AFSLIU3498UAFSLIU34OI

#include <cmath>
#include <cstddef>
#include <limits>
#include <cassert>

namespace vg
{

    template <   typename Return_Type,
                 typename Engine
             >
    struct lognormal
    {
            typedef typename Engine::final_type     final_type;
            typedef Return_Type                     return_type;
            typedef typename Engine::seed_type      seed_type;
            typedef typename Engine::size_type      size_type;
            typedef Engine                          engine_type;

            final_type  zeta_;
            final_type  sigma_;
            engine_type e_;

            explicit lognormal( const return_type zeta = 1, const return_type sigma = 1, const seed_type sd = 0 )
                : zeta_( zeta ), sigma_( sigma ), e_( sd )
            {
            }

            return_type
            operator()()
            {
                return do_generation( zeta_, sigma_ );
            }

        protected:
            return_type
            do_generation( const return_type zeta, const return_type sigma )
            {
                return direct_impl( zeta, sigma );
            }

        private:
            return_type
            direct_impl( const return_type zeta, const return_type sigma )
            {
                for ( ;; )
                {
                    const final_type u = e_() * final_type( 2 ) - final_type( 1 );
                    const final_type v = e_() * final_type( 2 ) - final_type( 1 );
                    const final_type r = u * u + v * v;

                    if ( r <= final_type( 1 ) && r != final_type( 0 ) )
                    {
                        const final_type normal = u * std::sqrt( final_type( -2 ) * std::log( r ) / r );
                        const final_type ans = std::exp( sigma * normal + zeta );
                        return ans;
                    }
                }
            }

    };

}//namespace vg

#endif//_LOGNORMAL_HPP_INCLUDED_SODIJASOI84U98AU7FSKLJ349P8AFSLIU3498UAFSLIU34OI

