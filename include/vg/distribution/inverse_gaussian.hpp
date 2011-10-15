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
#ifndef _INVERSE_GAUSSIAN_HPP_INCLUDED_DSOIJ3LKJSF8U4LKJDFLKCMSOIJ34OISFLKJ4OIJFSLKJSLFK34IJSLFDKJ4OIJSLKJ4OIJSLKJSOFDIJLFKJ4IJLSFKDSKLJFSJFKLOE
#define _INVERSE_GAUSSIAN_HPP_INCLUDED_DSOIJ3LKJSF8U4LKJDFLKCMSOIJ34OISFLKJ4OIJFSLKJSLFK34IJSLFDKJ4OIJSLKJ4OIJSLKJSOFDIJLFKJ4IJLSFKDSKLJFSJFKLOE

#include <vg/distribution/normal.hpp>

#include <cassert>

namespace vg
{

    template <   typename Return_Type,
                 typename Engine
             >
    struct inverse_gaussian : private normal<Return_Type, Engine>
    {
            typedef normal<Return_Type, Engine>         normal_type;
            typedef Return_Type                         return_type;
            typedef Engine                              engine_type;
            typedef typename normal_type::final_type    final_type;
            typedef typename normal_type::seed_type     seed_type;

            return_type mu_;
            return_type lambda_;
            engine_type e_;

            explicit inverse_gaussian( const return_type mu = 1,
                               const return_type lambda = 1,
                               const seed_type sd = 0 )
                : mu_( mu ), lambda_( lambda ), e_( sd )
            {
                assert( mu > 0 );
                assert( lambda > 0 );
            }

            return_type
            operator()()
            {
                return do_generation( lambda_, mu_ );
            }

        protected:
            return_type
            do_generation( const final_type Lambda, const final_type Mu )
            {
                return michael_schucany_haas_impl( Lambda, Mu );
            }
        private:
            //Luc Devroye (1986). Non-Uniform Random Variate Generation. New York: Springer-Verlag, p. 163.
            return_type
            michael_schucany_haas_impl( const final_type Lambda, const final_type Mu )
            {
                const final_type N = normal_type::do_generation();
                const final_type Y = N * N ;
                const final_type MY = Mu * Y;
                const final_type X = Mu + ( MY - std::sqrt( MY * ( Lambda * final_type( 4 ) + MY ) ) ) * Mu / ( Lambda + Lambda );
                const final_type U = e_();
                const final_type ans = ( Mu >= ( Mu + X ) * U ) ? X : ( Mu * Mu / X );
                return ans;
            }
    };

}//vg


#endif//_INVERSE_GAUSSIAN_HPP_INCLUDED_DSOIJ3LKJSF8U4LKJDFLKCMSOIJ34OISFLKJ4OIJFSLKJSLFK34IJSLFDKJ4OIJSLKJ4OIJSLKJSOFDIJLFKJ4IJLSFKDSKLJFSJFKLOE



