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
#ifndef _HYPERBOLIC_SECANT_HPP_INCLUDED_SOFDIJKOI43UJKLGJKLDIUJDFGOIU4598UDGOIUDFGJKDFKLJGLKJSDLKJDOIVLKJVLIDFOIUR5IIOGDU
#define _HYPERBOLIC_SECANT_HPP_INCLUDED_SOFDIJKOI43UJKLGJKLDIUJDFGOIU4598UDGOIUDFGJKDFKLJGLKJSDLKJDOIVLKJVLIDFOIUR5IIOGDU

#include <cmath>

namespace vg
{

    template <   typename Return_Type,
                 typename Engine
             >
    struct hyperbolic_secant
    {
            typedef typename Engine::final_type     final_type;
            typedef Return_Type                     return_type;
            typedef typename Engine::seed_type      seed_type;
            typedef Engine                          engine_type;

            engine_type e_;

            explicit hyperbolic_secant( const seed_type sd = 0 ) : e_( sd )
            {}

            return_type
            operator()()
            {
                return do_generation();
            }

        protected:
            return_type
            do_generation()
            {
                return direct_impl_method();
            }

        private:
            return_type
            direct_impl_method()
            {
                const final_type u = e_();
                const final_type pi_2 = 3.1415926535897932384626433L / 2.0L;
                const final_type ans = std::log( std::tan( u * pi_2 ) );
                return ans;
            }

    };

}//namespace vg

#endif//_HYPERBOLIC_SECANT_HPP_INCLUDED_SOFDIJKOI43UJKLGJKLDIUJDFGOIU4598UDGOIUDFGJKDFKLJGLKJSDLKJDOIVLKJVLIDFOIUR5IIOGDU

