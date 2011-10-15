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
#ifndef _LINEAR_CONGRUENTIAL_HPP_INCLUDED_3UHSFKJHNSAIFUNVCJMNZKJHDEIUHE3IUHSIKUJHEE8
#define _LINEAR_CONGRUENTIAL_HPP_INCLUDED_3UHSFKJHNSAIFUNVCJMNZKJHDEIUHE3IUHSIKUJHEE8

#include <vg/engine/default_seed.hpp>
#include <cstddef>

namespace vg
{
    struct linear_congruential
    {
            typedef linear_congruential		self_type;
            typedef long double				final_type;
            typedef unsigned long long		value_type;
            typedef value_type				seed_type;
            typedef std::size_t             size_type;

        private:
			static const value_type a_ = 6364136223846793005ULL;
			static const value_type c_ = 1442695040888963407ULL;
			value_type x_;

        public:
            linear_congruential( const seed_type s = 0 )
            {
                x_ = s ? s : default_seed()();
            }

            final_type operator()()
            {
				x_ *= a_;
				x_ += c_;
                const final_type ans = static_cast<final_type>( x_ ) /
                                       static_cast<final_type>( value_type(-1) );
                return ans;
            } // end of operator()

        private://not to be implemented
            linear_congruential( const self_type& );
            linear_congruential& operator = ( const self_type& );
    };// end of struct linear_congruential
}//namespace vg

#endif//_LINEAR_CONGRUENTIAL_HPP_INCLUDED_3UHSFKJHNSAIFUNVCJMNZKJHDEIUHE3IUHSIKUJHEE8



