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
#ifndef _CHI_SQUARE_HPP_INCLUDED_MBSDLKJ98USIJEIJHFD984KJHSDFIOUHJS98E3D8EOIUHS9
#define _CHI_SQUARE_HPP_INCLUDED_MBSDLKJ98USIJEIJHFD984KJHSDFIOUHJS98E3D8EOIUHS9

#if 0

COMMENT:
The chi - square distribution with k degrees of freedom is the distribution of
a sum of the squares of k independent standard normal random variables.

#endif

#include <vg/distribution/gamma.hpp>

namespace vg
{

    template <   typename Return_Type,
                 typename Engine
             >
    struct chi_square : private gamma<Return_Type, Engine>
    {
            typedef Return_Type                         return_type;
            typedef Engine                              engine_type;
            typedef gamma<Return_Type, Engine>          gamma_type;

            typedef typename engine_type::final_type    final_type;
            typedef typename engine_type::seed_type     seed_type;
            typedef typename engine_type::size_type     size_type;

            size_type       k_;
            engine_type     e_;

            explicit chi_square( const size_type k = 10,
                                 const seed_type sd = 0 )
                : k_( k ), e_( sd )
            {}

            return_type
            operator()()
            {
                return do_generation( k_ );
            }

        protected:
            return_type
            do_generation( const size_type K )
            {
                return chi_square_direct_impl( K );
            }

        private:
            return_type
            chi_square_direct_impl( const size_type K )
            {
                const final_type ans = gamma_type::do_generation( final_type( K ) / final_type( 2 ) );
                return ans + ans;
            }

    };

}//vg


#endif//_CHI_SQUARE_HPP_INCLUDED_MBSDLKJ98USIJEIJHFD984KJHSDFIOUHJS98E3D8EOIUHS9


