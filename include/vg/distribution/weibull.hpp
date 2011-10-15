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
#ifndef _WEIBULL_HPP_INCLUDED_OIJH98HUSFA98UHJALKJQ1PH9IAFOIUJWKLJNALKJSDIOUH3D
#define _WEIBULL_HPP_INCLUDED_OIJH98HUSFA98UHJALKJQ1PH9IAFOIUJWKLJNALKJSDIOUH3D

#include <cmath>

#include <cassert>

namespace vg
{

    template <   typename Return_Type,
                 typename Engine
             >
    struct weibull
    {
            typedef Return_Type                         return_type;
            typedef Engine                              engine_type;

            typedef typename engine_type::final_type    final_type;
            typedef typename engine_type::seed_type     seed_type;

            return_type lambda_;
            return_type k_;
            engine_type e_;

            explicit weibull(	const return_type lambda = 1,
                                const return_type k = 1,
                                const seed_type sd = 0 )
                : lambda_( lambda ), k_( k ), e_( sd )
            {
                assert( lambda_ > 0 );
                assert( k_ > 0 );
            }

            return_type
            operator()()
            {
                return do_generation( lambda_, k_ );
            }

        protected:
            return_type
            do_generation( const return_type lambda, const return_type k )
            {
                return direct_impl( lambda, k );
            }

        private:
            return_type
            direct_impl( const return_type lambda, const return_type k )
            {
                const final_type tmp1   =   e_();
                const final_type tmp2   =   - std::log( - tmp1 + final_type( 1 ) ) / k;
                const final_type tmp3   =   final_type( 1 ) / lambda;
                const final_type ans    =   std::pow( tmp2, tmp3 );
                return ans;
            }

    };

}//vg


#endif//_WEIBULL_HPP_INCLUDED_OIJH98HUSFA98UHJALKJQ1PH9IAFOIUJWKLJNALKJSDIOUH3D


