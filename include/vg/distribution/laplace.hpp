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
#ifndef _LAPLACE_HPP_INCLUDED_9URHFADSKJHSAFUHE9U8HDFUJHDUIHEUHFDUJHDSUI893U7FSDK
#define _LAPLACE_HPP_INCLUDED_9URHFADSKJHSAFUHE9U8HDFUJHDUIHEUHFDUJHDSUI893U7FSDK

#include <cmath>

namespace vg
{

    template <   typename Return_Type,
                 typename Engine
             >
    struct laplace
    {
            typedef typename Engine::final_type     final_type;
            typedef Return_Type                     return_type;
            typedef typename Engine::seed_type      seed_type;
            typedef Engine                          engine_type;

            return_type mu_;
            return_type b_;
            engine_type e_;

            explicit laplace( const return_type mu = 1, const return_type b = 1, const seed_type sd = 0 )
                : mu_( mu ), b_( b ), e_( sd )
            {}

            return_type
            operator()()
            {
                return do_generation( mu_, b_ );
            }

        protected:
            return_type
            do_generation( const return_type mu, const return_type b )
            {
                return direct_invertion_method( mu, b );
            }

        private:
            return_type
            direct_invertion_method( const return_type mu, const return_type b )
            {
                for ( ;; )
                {
                    const final_type u = e_() - final_type( 0.5 );

                    if ( final_type( 0 ) == u )
                        { continue; }

                    const final_type ans =  u > final_type( 0 ) ?
                                            mu - b * std::log( 1 - u - u ) :
                                            mu + b * std::log( 1 + u + u );

                    return static_cast<return_type>( ans );
                }
            }
    };


}//namespace vg




#endif//_LAPLACE_HPP_INCLUDED_9URHFADSKJHSAFUHE9U8HDFUJHDUIHEUHFDUJHDSUI893U7FSDK



