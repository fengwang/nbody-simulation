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
#ifndef _CAUCHY_HPP_INCLUDED_SDOIFJ32OIJASF0O9UI34LIAFSO0U340U9AFSLIUJRLIJDFSLKJ
#define _CAUCHY_HPP_INCLUDED_SDOIFJ32OIJASF0O9UI34LIAFSO0U340U9AFSLIUJRLIJDFSLKJ

#if 0
The Cauchy distribution, also called the Lorentzian distribution or Lorentz distribution,
    is a continuous distribution describing resonance behavior. It also describes the distribution
    of horizontal distances at which a line segment tilted at a random angle  cuts the x - axis.
#endif

#include <cmath>
#include <cassert>

namespace vg
{
    template <   typename Return_Type,
                 typename Engine
             >
    struct cauchy
    {
            typedef Return_Type                         return_type;
            typedef Engine                              engine_type;

            typedef typename engine_type::final_type    final_type;
            typedef typename engine_type::seed_type     seed_type;

            return_type delta_;
            engine_type e_;

            explicit cauchy( const return_type delta = 1,
                             const seed_type sd = 0 )
                : delta_( delta ), e_( sd )
            {
                assert( delta_ > 0 );
            }

            return_type
            operator()()
            {
                return do_generation( delta_ );
            }

        protected:
            return_type
            do_generation( const final_type Delta )
            {
                return cauchy_direct_impl( delta_ );
            }

        private:
            return_type
            cauchy_direct_impl( const final_type Delta )
            {
                const final_type pi = 3.1415926535897932384626433L;

                for ( ;; )
                {
                    const final_type u = e_();

                    if ( u != final_type( 0.5 ) )
                    {
                        return static_cast<return_type>( Delta * std::tan( pi * u ) );
                    }
                }
            }

    };

}//vg

#endif//_CAUCHY_HPP_INCLUDED_SDOIFJ32OIJASF0O9UI34LIAFSO0U340U9AFSLIUJRLIJDFSLKJ



