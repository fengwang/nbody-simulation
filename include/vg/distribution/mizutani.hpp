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
#ifndef _MIZUTANI_HPP_INCLUDED904KLDJA1Q2W3E4RLKJFIUJ682LI4SAF89D8HFAIUYERIKASFDUIOH4AFSD98ASDFNVSSSSSSSSSSOIJWER
#define _MIZUTANI_HPP_INCLUDED904KLDJA1Q2W3E4RLKJFIUJ682LI4SAF89D8HFAIUYERIKASFDUIOH4AFSD98ASDFNVSSSSSSSSSSOIJWER 

#include <vg/distribution/generalized_hypergeometric_b3.hpp>

#include <cassert>

namespace vg
{

    template <
                typename Return_Type,
                typename Engine
             >
    struct mizutani : private generalized_hypergeometric_b3<Return_Type, Engine>
    {
        typedef generalized_hypergeometric_b3< Return_Type, Engine> GHgB3_type;
        typedef typename Engine::final_type     final_type;
        typedef Return_Type                     return_type;
        typedef Return_Type                     value_type;
        typedef typename Engine::seed_type      seed_type;
        typedef std::size_t                     size_type;
        typedef Engine                          engine_type;

        value_type           a_; 
        engine_type          e_;

        explicit mizutani(value_type a = 1 , seed_type s = 0 ) : a_( a ), e_( s ) 
        {
            assert( a > 0 );
        }

        return_type
        operator()()
        {
            return do_generation( a_ );
        }

    protected:
        return_type
        do_generation( const value_type a )
        {
            return direct_impl( a );
        }

    private:
        // S. Mizutani, Vocabulary in women's magazines, Kokken-Hokoku, National Language Research Institute, Tokyo, 1953.
        return_type
        direct_impl( const value_type a )
        {
            const final_type ans = GHgB3_type::do_generation( a, final_type(1), final_type(1) );
            return ans;
        }
    };

}//namespace vg

#endif//_MIZUTANI_HPP_INCLUDED904KLDJA1Q2W3E4RLKJFIUJ682LI4SAF89D8HFAIUYERIKASFDUIOH4AFSD98ASDFNVSSSSSSSSSSOIJWER 

