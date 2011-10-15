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
#ifndef _F_HPP_INCLUDED_SOIFJ34LIJAFSPOIJ4398AFSOHSOIJ4LKJASFLKJ3LKJASFDLKJ3IFAK
#define _F_HPP_INCLUDED_SOIFJ34LIJAFSPOIJ4398AFSOHSOIJ4LKJASFLKJ3LKJASFDLKJ3IFAK

#include <vg/distribution/gamma.hpp>

#include <cassert>

namespace vg
{

    template <   typename Return_Type,
                 typename Engine
             >
    struct f :  private gamma<Return_Type, Engine>
    {
            typedef gamma<Return_Type, Engine>      gamma_type;
            typedef typename Engine::final_type     final_type;
            typedef Return_Type                     return_type;
            typedef typename Engine::seed_type      seed_type;
            typedef typename Engine::size_type      size_type;
            typedef Engine                          engine_type;

            final_type  mu1_;
            final_type  mu2_;
            engine_type e_;

            explicit f( const return_type mu1 = 2, const return_type mu2 = 2, const seed_type sd = 0 )
                : mu1_( mu1 ), mu2_( mu2 ), e_( sd )
            {
                assert( mu1 > 0 );
                assert( mu2 > 0 );
            }

            return_type
            operator()()
            {
                return do_generation( mu1_, mu2_ );
            }

        protected:
            return_type
            do_generation( const return_type mu1, const return_type mu2 )
            {
                return direct_impl( mu1, mu2 );
            }

        private:
            return_type
            direct_impl( const return_type mu1, const return_type mu2 )
            {
                const final_type y1 = gamma_type::do_generation( mu1 / final_type( 2 ), final_type( 2 ) );
                const final_type y2 = gamma_type::do_generation( mu2 / final_type( 2 ), final_type( 2 ) );
                const final_type ans = y1 * mu2 / ( y2 * mu1 );
                return ans;
            }

    };

}//namespace vg

#endif//_F_HPP_INCLUDED_SOIFJ34LIJAFSPOIJ4398AFSOHSOIJ4LKJASFLKJ3LKJASFDLKJ3IFAK

