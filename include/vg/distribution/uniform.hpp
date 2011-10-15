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
#ifndef _UNIFORM_HPP_INCLUDED_98U3LKJFASD98IHJ3WLKJNASF98YU12LAKFJ289UJAWOIJUW2I
#define _UNIFORM_HPP_INCLUDED_98U3LKJFASD98IHJ3WLKJNASF98YU12LAKFJ289UJAWOIJUW2I

#include <cassert>

namespace vg
{

    template <
                typename Return_Type,
                typename Engine
             >
    struct uniform
    {
            typedef typename Engine::final_type     final_type;
            typedef Return_Type                     return_type;
            typedef Return_Type                     value_type;
            typedef typename Engine::seed_type      seed_type;

            value_type      lower_;
            value_type      upper_;
            Engine          e_;

            explicit uniform( const value_type lower = value_type( 0 ),
                              const value_type upper = value_type( 1 ),
                              const seed_type s = seed_type( 0 ) )
                : lower_( lower ), upper_( upper ), e_( s )
            {
                assert( upper > lower );
            }

            return_type
            operator()()
            {
                return do_generation( lower_, upper_ );
            }

        protected:
            return_type
            do_generation( const value_type lower, const value_type upper )
            {
                return direct_impl( lower, upper );
            }

        private:
            return_type
            direct_impl( const value_type lower, const value_type upper )
            {
                const final_type lower_f    =   static_cast<final_type>( lower );
                const final_type upper_f    =   static_cast<final_type>( upper );
                const final_type ans        =   lower_f + e_() * ( upper_f - lower_f );
                return ans;
            }
    };

}//namespace vg

#endif//_UNIFORM_HPP_INCLUDED_98U3LKJFASD98IHJ3WLKJNASF98YU12LAKFJ289UJAWOIJUW2I

