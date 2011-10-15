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
#ifndef _YULE_HPP_INCLUDED_DSOIJH328YASDIK398YASFDL3UHSDFLOIAFSDKJHNVJFSDSDIJ34KJHSFDJKLH349IAOSDFLKJR4ALFKSDJ3U890ASFOD
#define _YULE_HPP_INCLUDED_DSOIJH328YASDIK398YASFDL3UHSDFLOIAFSDKJHNVJFSDSDIJ34KJHSFDJKLH349IAOSDFLKJR4ALFKSDJ3U890ASFOD 

#include <vg/distribution/exponential.hpp>
#include <vg/utility.hpp>

#include <cassert>
#include <cmath>

namespace vg
{

    template <   typename Return_Type,
                 typename Engine
             >
    struct yule : private exponential<Return_Type, Engine>
    {
            typedef exponential<Return_Type, Engine>    exponential_type;
            typedef typename Engine::final_type         final_type;
            typedef Return_Type                         return_type;
            typedef typename Engine::seed_type          seed_type;
            typedef Engine                              engine_type;

            final_type  a_;
            engine_type e_;

            explicit yule( const final_type a = 2, const seed_type sd = 0 ) : a_( a ), e_( sd ) 
            {
                assert( a > final_type(1) );
            }

            return_type
            operator()()
            {
                return do_generation( a_ );
            }

        protected:
            return_type
            do_generation( const final_type a )
            {
                return exponential_impl( a );
            }

        private:
            /*
             *   X <- - \frac{E}{ \log{ 1 - e^{-\frac{E^{*}}{a-1} } } }  
             */
            // H. A. Simon, "Some futher notes on a class of skew distribution functions", Information and Control, vol. 3, pp.90-98, 1960.
            return_type
            exponential_impl( const final_type a )
            {
                const final_type e1 = - exponential_type::do_generation( final_type(1) );
                const final_type e2 = - exponential_type::do_generation( final_type(1) );
                const final_type a1 = a - final_type(1);
                const final_type a2 = - std::exp( e1 / a1 );
                const final_type a3 = final_type(1) + a2;
                const final_type a4 = std::log( a3 );
                const final_type ans = e2 / a4;
                return ans;
            }

    }; // yule 




}//namespace vg


#endif//_YULE_HPP_INCLUDED_DSOIJH328YASDIK398YASFDL3UHSDFLOIAFSDKJHNVJFSDSDIJ34KJHSFDJKLH349IAOSDFLKJR4ALFKSDJ3U890ASFOD 

