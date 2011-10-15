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
#ifndef _BETA_PASCAL_HPP_INCLUDED_SDFLKJSDL3897SDFKIUSIU23UIAS8904987SDF98SDFKJHASKLJCLZKJXCOIUJEOIUADSFOIUJ4OISAFLSDJHASFD
#define _BETA_PASCAL_HPP_INCLUDED_SDFLKJSDL3897SDFKIUSIU23UIAS8904987SDF98SDFKJHASKLJCLZKJXCOIUJEOIUADSFOIUJ4OISAFLSDJHASFD 

#include <vg/distribution/generalized_hypergeometric_b3.hpp>

#include <cassert>

namespace vg
{

    template <
                typename Return_Type,
                typename Engine
             >
    struct beta_pascal : private generalized_hypergeometric_b3<Return_Type, Engine>
    {
        typedef generalized_hypergeometric_b3< Return_Type, Engine> GHgB3_type;
        typedef typename Engine::final_type     final_type;
        typedef Return_Type                     return_type;
        typedef Return_Type                     value_type;
        typedef typename Engine::seed_type      seed_type;
        typedef std::size_t                     size_type;
        typedef Engine                          engine_type;

        value_type           k_; 
        value_type           r_; 
        engine_type          e_;

        explicit beta_pascal(value_type k = 3, value_type r = 3, seed_type s = 0 ) : k_( k ), r_( r ), e_( s ) 
        {
            assert( k >= 2 );
            assert( r >= k );
        }

        return_type
        operator()()
        {
            return do_generation( k_, r_ );
        }

    protected:
        return_type
        do_generation( const value_type k, const value_type r )
        {
            return direct_impl( k, r );
        }

    private:
        return_type
        direct_impl( const value_type k, const value_type r )
        {
            const final_type r_1 = r - final_type(1);
            const final_type ans = GHgB3_type::do_generation( final_type(1), k - r_1, r_1 );
            return ans;
        }
    };

}//namespace vg

#endif//_BETA_PASCAL_HPP_INCLUDED_SDFLKJSDL3897SDFKIUSIU23UIAS8904987SDF98SDFKJHASKLJCLZKJXCOIUJEOIUADSFOIUJ4OISAFLSDJHASFD 

