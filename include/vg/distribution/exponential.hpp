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
#ifndef _EXPONENTIAL_HPP_INCLUDED_98JKLJHWE8UHSFDWE98HSFDIUHEUHSAKUHAIUHWEIUHASF
#define _EXPONENTIAL_HPP_INCLUDED_98JKLJHWE8UHSFDWE98HSFDIUHEUHSAKUHAIUHWEIUHASF

#include <cmath>
#include <cassert>

namespace vg
{

    template <   typename Return_Type,
                 typename Engine
             >
    struct exponential
    {
            typedef Return_Type                         return_type;
            typedef Engine                              engine_type;

            typedef typename engine_type::final_type    final_type;
            typedef typename engine_type::seed_type     seed_type;

            return_type         lambda_;
            engine_type         e_;

            explicit exponential(	const return_type lambda = 1,
                                    const seed_type sd = 0 )
                : lambda_( lambda ), e_( sd )
            {
                assert( lambda_ > 0 );
            }

            return_type
            operator()()
            {
                return do_generation( lambda_ );
            }

        protected:
            return_type
            do_generation( const final_type Lambda )
            {
                return direct_exponential_impl( Lambda );
            }

        private:
            return_type
            direct_exponential_impl( const final_type Lambda )
            {
                const final_type u = e_();
                const final_type ans =  - std::log( u ) / Lambda;
                return ans;
            }

    };

}//vg


#endif//_EXPONENTIAL_HPP_INCLUDED_98JKLJHWE8UHSFDWE98HSFDIUHEUHSAKUHAIUHWEIUHASF


