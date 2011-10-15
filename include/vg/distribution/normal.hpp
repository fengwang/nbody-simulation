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
#ifndef _NORMAL_HPP_INCLUDED_9URHFADSKJHSAFUHE9U8HDFUJHDUIHEUHFDUJHDSUI893U7FSDK
#define _NORMAL_HPP_INCLUDED_9URHFADSKJHSAFUHE9U8HDFUJHDUIHEUHFDUJHDSUI893U7FSDK

#include <cmath>


namespace vg
{

    template <   typename Return_Type,
                 typename Engine
             >
    struct normal
    {
            typedef typename Engine::final_type     final_type;
            typedef Return_Type                     return_type;
            typedef typename Engine::seed_type      seed_type;
            typedef Engine                          engine_type;

            engine_type e_;

            explicit normal( const seed_type sd = 0 ) : e_( sd )
            {}

            return_type
            operator()()
            {
                return do_generation();
            }

        protected:
            return_type
            do_generation()
            {
                return kinderman_monahan_method();
            }

        private:
            //A. J. Kinderman and J. F. Monahan (1977)
            //"Computer Generation of Random Variables Using the Ratio of Uniform Deviates,"
            //ACM Transactions on Mathematical Software 3: 257-260.
            return_type
            kinderman_monahan_method()
            {
                const final_type u = e_();
                const final_type v = ( e_() - 0.5L ) * 4.0L * u * std::sqrt( - std::log( u ) );
                return static_cast<return_type>( v / u );
            }

            //G. E. P. Box and Mervin E. Muller,
            //A Note on the Generation of Random Normal Deviates,
            //The Annals of Mathematical Statistics (1958), Vol. 29, No. 2 pp. 610¨C611
            return_type
            box_muller_method()
            {
                final_type u1, u2;
                final_type v1, v2;
                final_type s( 2 );

                while ( s > final_type( 1 ) )
                {
                    u1 = e_();
                    u2 = e_();
                    v1 = u1 + u1 - final_type( 1 );
                    v2 = u2 + u2 - final_type( 1 );
                    s = v1 * v1 + v2 * v2;
                }

                const final_type tmp = -std::log( s );

                const final_type ans = v1 * std::sqrt(( tmp + tmp ) / s );

                return static_cast<return_type>( ans );
            }

    };




}//namespace vg




#endif//_NORMAL_HPP_INCLUDED_9URHFADSKJHSAFUHE9U8HDFUJHDUIHEUHFDUJHDSUI893U7FSDK



