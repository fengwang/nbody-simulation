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
#ifndef _DIGAMMA_HPP_INCLUDED_SDOIJSDL3IOUSDFLKJASFLSSSSSSSSSSSSSSIMNDALKFJALSDKFJASDLFKJDLKJFOIJ4LKJSDFLKJASFSSSSSSSSOIJ4D89U4LKJDF
#define _DIGAMMA_HPP_INCLUDED_SDOIJSDL3IOUSDFLKJASFLSSSSSSSSSSSSSSIMNDALKFJALSDKFJASDLFKJDLKJFOIJ4LKJSDFLKJASFSSSSSSSSOIJ4D89U4LKJDF

#include <vg/distribution/generalized_hypergeometric_b3.hpp>
#include <vg/special_function/digamma.hpp>

#include <cmath>
#include <algorithm>
#include <cassert>

namespace vg
{

    template <
                typename Return_Type,
                typename Engine
             >
    struct digamma : private generalized_hypergeometric_b3<Return_Type, Engine>
    {
            typedef generalized_hypergeometric_b3< Return_Type, Engine> GHgB3_type;
            typedef typename Engine::final_type     final_type;
            typedef Return_Type                     return_type;
            typedef Return_Type                     value_type;
            typedef typename Engine::seed_type      seed_type;
            typedef std::size_t                     size_type;
            typedef Engine                          engine_type;

            value_type           a_;
            value_type           c_;
            engine_type          e_;

            explicit digamma( value_type a = 3, value_type c = 3, seed_type s = 0 ) : a_( a ), c_( c ), e_( s )
            {
                assert( a > 0 );
                assert( c > 0 );
            }

            return_type
            operator()()
            {
                return do_generation( a_, c_ );
            }

        protected:
            //L. Devroye, Random variate generation for the digamma and trigamma distributions,
            //Journal of Statistical Computation and Simulation, vol. 43, pp. 197-216, 1992.
            return_type
            do_generation( const value_type a, const value_type c )
            {
                if ( c > final_type(1) && a < final_type(1) )
                    return sibuya_rejection_impl( a, c );
                if ( a > c + final_type(1) && a > final_type(2) )
                    return joint_rejection_impl( a, c );
                if ( a < final_type( 0.125 ) && c > final_type( 0.25 ) ) 
                    return sibuya_rejection_1979_impl( a, c );
                return simple_rejection_impl( a, c );
            }

        private:
            // M. Sibuya, "Generalized hypergeometric, digamma and trigamma distributions," Annals of the
            // Institute of Statistical Mathematics. vol. 32, pp. 25-36, 1980
            return_type
            sibuya_rejection_impl( const value_type a, const value_type c )
            {
                for ( ;; )
                    {
                        const final_type x = final_type( 1 ) + GHgB3_type::do_generation( final_type( 1 ), a + final_type( 1 ), c - final_type( 1 ) );
                        const final_type u = e_();

                        if ( x * u < final_type( 1 ) )
                            { return x; }
                    }
            }

            return_type
            simple_rejection_impl( const value_type a, const value_type c )
            {
                for ( ;; )
                    {
                        const final_type x = final_type( 1 ) + GHgB3_type::do_generation( a, final_type( 1 ), c );
                        const final_type u = e_();

                        final_type xu = x * u;
                        xu = a > final_type(1) ? a * xu : xu;
                        if ( xu + final_type(1) < a + x )
                            { return x; }
                    }
            }

            return_type
            joint_rejection_impl( const value_type a, const value_type c )
            {
                const final_type t = ( a - final_type( 1 ) ) / c;
                const final_type u = std::ceil( std::log( t ) / std::log( final_type( 2 ) ) );
                const final_type n = std::pow( final_type( 2 ), u + final_type( 1 ) ) - final_type( 1 ) ;
                const final_type delta = vg::special_function::digamma()( a + c ) - vg::special_function::digamma()( c );
                const final_type w = ( u + final_type( 1 ) ) / delta;
                const final_type z = ( a + n ) / ( c * delta * ( n + final_type( 1 ) ) );
                const final_type threshold = w / ( w + z );

                for ( ;; )
                    {
                        const final_type U = e_();

                        if ( U < threshold )
                            {
                                const final_type y = std::floor( u * e_() );
                                const final_type py = std::pow( final_type( 2 ), y );
                                const final_type x = py * ( final_type( 1 ) + e_() );
                                const final_type px = std::exp( std::lgamma( a + x ) + std::lgamma( a + c ) - std::lgamma( a ) - std::lgamma( a + c + x ) ) / x / delta ;
                                const final_type v = e_();

                                if ( px >  v * delta * std::pow( final_type( 2 ), y ) )
                                    { return x; }
                            }
                        else
                            {
                                const final_type y = GHgB3_type::do_generation( a, final_type( 1 ), c );
                                const final_type x = y + final_type( 1 );
                                const final_type v = e_();

                                if ( x > n && ( a + x - final_type( 1 ) ) > v * z * c * delta * x )
                                    { return x; }
                            }
                    }
            }

            return_type
            special_method_rejection_impl( const value_type a, const value_type c )
            {
                const final_type delta = special_function::digamma()( a + c ) - special_function::digamma()( c );
                const final_type d = std::max( a / delta / c, std::exp( ( final_type( 6 ) * a + final_type( 7 ) ) * c / final_type( 12 ) / ( final_type( 1 ) + a ) + std::lgamma( a + c ) - std::lgamma( c ) ) / delta );

                for ( ;; )
                    {
                        const final_type u = e_();
                        const final_type v = e_();
                        const final_type y = std::pow( ( final_type( 1 ) - u ), -final_type( 1 ) / c );
                        const final_type x = std::ceil( y );
                        const final_type w = v * std::pow( final_type( 2 ) / y, c + final_type( 1 ) ) * d;
                        const final_type px = std::exp( std::lgamma( a + x ) + std::lgamma( a + c ) - std::lgamma( a ) - std::lgamma( a + c + x ) ) / x / delta ;

                        if ( px > w )
                            { return x; }
                    }
            }

            return_type
            sibuya_rejection_1979_impl( const value_type a, const value_type c )
            {
                const final_type delta = special_function::digamma()( a + c ) - special_function::digamma()( c );
                final_type p = a / ( c - final_type( 1 ) ) / delta;
                final_type s = p;
                final_type x = final_type( 1 );

                while ( s < e_() )
                    {
                        p *= x * ( a + x );
                        p /= ( x + final_type( 1 ) ) * ( a + c + x );
                        s += p;
                        ++x;
                    }

                return x;
            }


    };

}//namespace vg

#endif//_DIGAMMA_HPP_INCLUDED_SDOIJSDL3IOUSDFLKJASFLSSSSSSSSSSSSSSIMNDALKFJALSDKFJASDLFKJDLKJFOIJ4LKJSDFLKJASFSSSSSSSSOIJ4D89U4LKJDF 















