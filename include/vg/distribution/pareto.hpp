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
#ifndef _PARETO_HPP_INCLUDED_ASFLDKJO3RUI9LASFIKJ38U9ALFISFJOIUWERLKJFSDLKJASFLK
#define _PARETO_HPP_INCLUDED_ASFLDKJO3RUI9LASFIKJ38U9ALFISFJOIUWERLKJFSDLKJASFLK

#include <cmath>
#include <cassert>

namespace vg
{

    template <   typename Return_Type,
                 typename Engine
             >
    struct pareto
    {
            typedef Return_Type                         return_type;
            typedef Engine                              engine_type;

            typedef typename engine_type::final_type    final_type;
            typedef typename engine_type::seed_type     seed_type;

            return_type a_;
            return_type b_;
            engine_type e_;

            explicit pareto(	const return_type a = 1,
                                const return_type b = 2,
                                const seed_type sd = 0 )
                : a_( a ), b_( b ), e_( sd )
            {
                assert( a_ > 0 );
            }

            return_type
            operator()()
            {
                return do_generation( a_, b_ );
            }

        protected:
            return_type
            do_generation( const return_type A, const return_type B )
            {
                return direct_impl( A, B );
            }

        private:
            return_type
            direct_impl( const return_type A, const return_type B )
            {
                const final_type u = e_();
                const final_type tmp = std::pow( u, final_type( 1 ) / A );
                const final_type ans = B / tmp;
                return static_cast<return_type>( ans );
            }
    };

}//vg


#endif//_PARETO_HPP_INCLUDED_ASFLDKJO3RUI9LASFIKJ38U9ALFISFJOIUWERLKJFSDLKJASFLK

