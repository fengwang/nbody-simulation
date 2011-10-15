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
#ifndef _BETA_HPP_INCLUDED_SODFIJ34LKJASFODIJ3498UAFSLKJ4398UAFSLKJ498UAFSLKJ34D
#define _BETA_HPP_INCLUDED_SODFIJ34LKJASFODIJ3498UAFSLKJ4398UAFSLKJ498UAFSLKJ34D

#include <vg/distribution/gamma.hpp>

#include <cmath>
#include <cassert>

namespace vg
{

    template <   typename Return_Type,
                 typename Engine
             >
    struct beta : private gamma<Return_Type, Engine>
    {
            typedef gamma<Return_Type, Engine>                  gamma_type;
            typedef Return_Type                         		return_type;
            typedef Engine                              		engine_type;
            typedef return_type                                 value_type;
            typedef typename engine_type::size_type          	size_type;
            typedef typename engine_type::final_type    	    final_type;
            typedef typename engine_type::seed_type     	    seed_type;

            value_type          a_;
            value_type          b_;
            engine_type         e_;

            explicit beta(	const value_type a = value_type( 1 ),
                            const value_type b = value_type( 1 ),
                            const seed_type sd = 0 )
                : a_( a ), b_( b ), e_( sd )
            {
                assert( a_ > 0 );
                assert( b_ > 0 );
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
                return direct_beta_impl( A, B );
            }

        private:
            return_type
            direct_beta_impl( const final_type A, const final_type B )
            {
                const final_type a =  gamma_type::do_generation( A );
                const final_type b =  gamma_type::do_generation( B );
                return  a / ( a + b );
            }
    };

}//vg

#endif//_BETA_HPP_INCLUDED_SODFIJ34LKJASFODIJ3498UAFSLKJ4398UAFSLKJ498UAFSLKJ34D


