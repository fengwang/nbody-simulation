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
#ifndef _GAUSSIAN_HPP_INCLUDED_OIHJ3LKJAFS98UYH3KJHFAS9I8UHY2QR3OIUHFSIOUHEIUHY3
#define _GAUSSIAN_HPP_INCLUDED_OIHJ3LKJAFS98UYH3KJHFAS9I8UHY2QR3OIUHFSIOUHEIUHY3

#include <vg/distribution/normal.hpp>

#include <cassert>

namespace vg
{

    template <   typename Return_Type,
                 typename Engine
             >
    struct gaussian : private normal<Return_Type, Engine>
    {
            typedef normal<Return_Type, Engine>         normal_type;
            typedef Return_Type                         return_type;
            typedef Engine                              engine_type;
            typedef typename normal_type::final_type    final_type;
            typedef typename normal_type::seed_type     seed_type;

            return_type mean_;
            return_type variance_;
            normal_type n_;

            explicit gaussian( const return_type mean = 0,
                               const return_type variance = 1,
                               const seed_type sd = 0 )
                : mean_( mean ), variance_( variance ), n_( sd )
            {
                assert( variance > 0 );
            }

            return_type
            operator()()
            {
                return do_generation( variance_, mean_ );
            }

        protected:
            return_type
            do_generation( const final_type Variance, const final_type Mean )
            {
                return gaussian_direct_impl( Variance, Mean );
            }
        private:
            return_type
            gaussian_direct_impl( const final_type Variance, const final_type Mean )
            {
                const final_type ans =  normal_type::do_generation() * Variance + Mean;
                return ans;
            }
    };

}//vg


#endif//_GAUSSIAN_HPP_INCLUDED_OIHJ3LKJAFS98UYH3KJHFAS9I8UHY2QR3OIUHFSIOUHEIUHY3


