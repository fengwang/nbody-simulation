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
#ifndef _TEICHROEW_HPP_INCLUDED_SDOIJ3OIUSAFKLJ498YASFDKJH49IY8AFSDKLJH4IUYASFDKLJHWEIUHYWREIUY487YSFIUSFKJHCVXJHSDFKJHSF
#define _TEICHROEW_HPP_INCLUDED_SDOIJ3OIUSAFKLJ498YASFDKJH49IY8AFSDKLJH4IUYASFDKLJHWEIUHYWREIUY487YSFIUSFKJHCVXJHSDFKJHSF

#include <vg/utility.hpp>
#include <vg/distribution/normal.hpp>
#include <vg/distribution/gamma.hpp>

#include <cmath>
#include <cassert>

namespace vg
{

    template <   typename Return_Type,
                 typename Engine
             >
    struct teichroew : private proxy<normal<Return_Type, Engine>, 1>, 
                       private proxy<gamma<Return_Type, Engine>, 2>
    {
            typedef proxy<normal<Return_Type, Engine>, 1> normal_type;
            typedef proxy<gamma<Return_Type, Engine>, 2>  gamma_type;
            typedef Return_Type                           return_type;
            typedef Engine                                engine_type;
            typedef typename normal_type::final_type      final_type;
            typedef typename normal_type::seed_type       seed_type;

            return_type alpha_;
            engine_type e_;

            explicit teichroew( const return_type alpha = 1,
                                const seed_type sd = 0 )
                : alpha_( alpha ), e_( sd )
            {
                assert( alpha > 0 );
            }

            return_type
            operator()()
            {
                return do_generation( alpha_ );
            }

        protected:
            return_type
            do_generation( const final_type Alpha )
            {
                return teichroew_direct_impl( Alpha );
            }
        private:
            return_type
            teichroew_direct_impl(  const final_type Alpha )
            {
                const final_type n = normal_type::do_generation();
                const final_type g = gamma_type::do_generation( Alpha );
                const final_type ans = n * std::sqrt( g + g );
                return ans;
            }
    };

}//vg


#endif//_TEICHROEW_HPP_INCLUDED_SDOIJ3OIUSAFKLJ498YASFDKJH49IY8AFSDKLJH4IUYASFDKLJHWEIUHYWREIUY487YSFIUSFKJHCVXJHSDFKJHSF


