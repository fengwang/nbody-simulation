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
#ifndef _BURR_HPP_INCLUDED_SJSDFLKJ4OIFGLKJDLKJSDFGLDIU45OIUDGLKJDFLKJDGKLJDLKJFOI4LKJDOIRJLKDJGLKJVDKJHVDDKJHFJGKDKJDSGL
#define _BURR_HPP_INCLUDED_SJSDFLKJ4OIFGLKJDLKJSDFGLDIU45OIUDGLKJDFLKJDGKLJDLKJFOI4LKJDOIRJLKDJGLKJVDKJHVDDKJHFJGKDKJDSGL

#include <vg/numeric/newton_raphson.hpp>

#include <functional>
#include <cmath>
#include <cassert>

namespace vg
{

    template <   typename Return_Type,
                 typename Engine
             >
    struct burr
    {
            typedef Return_Type                         		return_type;
            typedef Engine                              		engine_type;
            typedef return_type                                 value_type;
            typedef typename engine_type::size_type          	size_type;
            typedef typename engine_type::final_type    	    final_type;
            typedef typename engine_type::seed_type     	    seed_type;

            size_type           n_;
            final_type          c_;
            final_type          k_;
            final_type          r_;
            engine_type         e_;

            explicit burr(  const size_type  n = size_type(12),	
                            const final_type c = final_type(1),
                            const final_type k = final_type(1),
                            const final_type r = final_type(1),
                            const seed_type sd = 0 )
                : n_(n), c_( c ), k_( k ), r_( r ), e_( sd )
            {
                assert( n > 0 );
                assert( n < 13 );
                assert( c > 0 );
                assert( k > 0 );
            }

            return_type
            operator()()
            {
                return do_generation( n_, c_, k_, r_ );
            }

        protected:
            final_type
            do_generation( const size_type N, const final_type C, const final_type K, const final_type R )
            {
                return direct_burr_impl( N, C, K, R );
            }

        private:
            final_type
            direct_burr_impl( const size_type N, const final_type C, const final_type K, const final_type R )
            {
                const final_type u = e_();
                static const final_type l(1);
                static const final_type ll(2);
                
                // Note: c++0x support required here
                //                                  u           c            k           r
                const std::function< final_type( final_type, final_type, final_type, final_type ) > inverse_function[12] = 
                {
                    // all wrong!
                    // F1(x) = x
                    []( const final_type u, const final_type c, const final_type k, const final_type r ) -> final_type
                    { return u; },
                    // F2(x) = (1+e^{-x})^{-r}
                    []( const final_type u, const final_type c, const final_type k, const final_type r ) -> final_type
                    { return - std::log( -l + std::pow(u, -l/r) ); },
                    // F3(x) = (1+x^{-k})^{-r}
                    []( const final_type u, const final_type c, const final_type k, const final_type r ) -> final_type
                    { return std::pow( (std::pow( u, -l/r ) - l ), -l/k); },
                    // F4(x) = (1+((c-x)/x)^(1/c))^(-r)
                    []( const final_type u, const final_type c, const final_type k, const final_type r ) -> final_type
                    { return c / ( l + std::pow(std::pow(u, -l/r) - l, c) ); },
                    // F5(x) = ( 1 + k e^{-tan(x)} )^r    
                    []( const final_type u, const final_type c, const final_type k, const final_type r ) -> final_type
                    { return std::atan( - std::log( (std::pow(u, -l/r)-l ) / k ) );},
                    // F6(x) = ( 1 + k e^{-sinh(x)} )^r    
                    []( const final_type u, const final_type c, const final_type k, const final_type r ) -> final_type
                    { return std::asinh( - std::log( (std::pow(u, -l/r)-l ) / k ) );},
                    // F7(x) = 2^{-r}(1+tanh(x))^{r}    
                    []( const final_type u, const final_type c, const final_type k, const final_type r ) -> final_type
                    { return std::atanh( std::pow(std::pow(ll, r)*u, l/r) - l);},
                    // F8(x) = \frac{2}{pi} arctan(e^x)   
                    []( const final_type u, const final_type c, const final_type k, const final_type r ) -> final_type
                    { const final_type pi_2 = 1.5707963267948966142313216L; return std::log(std::tan(pi_2*std::pow(u, l/r)));},
                    // F9(x) = 1-\frac{2}{1+k((1+e^x)^r-1)}
                    []( const final_type u, const final_type c, const final_type k, const final_type r ) -> final_type
                    { return std::log(std::pow(l+(ll/(l-u)-l)/k, l/r)-l);},
                    // F10(x) = (1+e^{-x^2})^r
                    []( const final_type u, const final_type c, const final_type k, const final_type r ) -> final_type
                    { return std::sqrt(-std::log(std::pow(u,l/r)-l));},
                    // F11(x) = ( x - \frac{\sin 2 \pi x}{2\pi})^r
                    []( const final_type u, const final_type c, const final_type k, const final_type r ) -> final_type
                    {
                        const final_type two_pi = final_type(2) * 3.1415926535897932384626433;
                        std::function<final_type(final_type)> f = [&](final_type x) { return std::pow( x - std::sin(two_pi*x)/two_pi ,r); };
                        std::function<final_type(final_type)> df =[&](final_type x) {return std::pow( x - std::sin(two_pi*x)/two_pi ,r-l) * ( l - std::cos(two_pi*x) ); };
                        const final_type ans = (newton_raphson<final_type>(final_type(0), final_type(1), f, df))();
                        return ans;
                    },
                    // F12(x) = 1 - ( 1 + x^c ) ^ {-k}
                    []( const final_type u, const final_type c, const final_type k, const final_type r ) -> final_type
                    { return std::pow( std::pow(l-u, l/k)-l, l/c);}
                };
                return inverse_function[N-1]( u, C, K, R );
            }
    };

}//vg

#endif//_BURR_HPP_INCLUDED_SJSDFLKJ4OIFGLKJDLKJSDFGLDIU45OIUDGLKJDFLKJDGKLJDLKJFOI4LKJDOIRJLKDJGLKJVDKJHVDDKJHFJGKDKJDSGL

