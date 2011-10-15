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
#ifndef _BINOMIAL_HPP_INCLUDED_OIJSI83LKJA091LKAJFOIMNVLKNDOIUHJ3LKJAFSL7ALKDIE8
#define _BINOMIAL_HPP_INCLUDED_OIJSI83LKJA091LKAJFOIMNVLKNDOIUHJ3LKJAFSL7ALKDIE8

#if 0
COMMENT:
the binomial distribution is the discrete probability distribution of the number
of successes in a sequence of n independent yes / no experiments, each of which
yields success with probability  p. Such a success / failure experiment is also
called a Bernoulli experiment or Bernoulli trial.
#endif

#include <vg/distribution/beta.hpp>

#include <cassert>
#include <cstddef>
#include <cmath>


namespace vg
{

    template <
                typename Return_Type,
                typename Engine
             >
    struct binomial : private beta<typename Engine::final_type, Engine>
    {
            typedef beta<typename Engine::final_type, Engine> beta_type;
            typedef typename Engine::final_type     final_type;
            typedef Return_Type                     return_type;
            typedef Return_Type                     value_type;
            typedef typename Engine::seed_type      seed_type;
            typedef std::size_t                     size_type;
            typedef Engine                          engine_type;

            size_type           n_;
            final_type          p_;
            engine_type         e_;

            explicit binomial( size_type n = size_type( 1 ),
                               final_type p = final_type( 0.5 ),
                               const seed_type s = seed_type( 0 ) )
                : n_( n ), p_( p ), e_( s )
            {
                assert( n_ != size_type( 0 ) );
                assert( p_ > final_type( 0 ) );
                assert( p_ < final_type( 1 ) );
            }

            return_type
            operator()()
            {
                return do_generation( n_, p_ );
            }

        protected:
            return_type
            do_generation( const size_type N, const final_type P )
            {
                if ( 0 == N )
                    return 0;
                if ( N < 8 )
                    { return coin_flip_method( N, P ); }

                if ( N * P < 16 )
                    { return second_waiting_time_method( N, P ); }

                return rejection_method( N, P );
            }

#if 0
            X < - 0
        FOR i :
            = 0 TO n DO
              Generate a random bit B( B is 1 with probability p, and can be obtained
                      by generating a uniform [0, 1] random variate U and setting B = 1 when U < p )
              X < - X + B
              RETURN X
#endif
        private:
            return_type
            coin_flip_method( const size_type N, const final_type P )
            {
                value_type ans = 0;

                for ( size_type i = 0; i < N; ++i )
                    if ( e_() < P )
                        { ++ans; }

                return ans;
            }//coin_flip_method

#if 0
            q < - -log( 1 - p )
            ANS < - 0
            SUM < - 0
            REPEAT
            Generate an exponential random variate E( -log( U ) )
            SUM < - SUM + E / ( n - ANS )
            ANS < - ANS + 1
            UNTIL SUM > q
            RETURN ANS < - ANS - 1
#endif
        protected:
            return_type
            second_waiting_time_method( const size_type N, const final_type P )
            {
                const final_type p  = P > 0.5 ? 1 - P : P;
                const final_type q  = -std::log( 1.0 - p );
                return_type ans     = 0;
                final_type sum      = 0;

                for ( ;; )
                {
                    const final_type e = -std::log( e_() );
                    sum += e / ( N - ans );

                    if ( sum > q )
                        { break; }

                    ++ans;
                }

                return p_ > 0.5 ? N - ans : ans;
            }//second_waiting_time_method

        protected:
            return_type
            rejection_method( const size_type N, const final_type P )
            {
                size_type   n   =   N;
                final_type  p   =   P;
                size_type   ans = 0;

                while ( n > 8 )
                {
                    const size_type a = 1 + ( n / 2 );
                    const size_type b = 1 + n - a;
                    const final_type X = beta_type::do_generation( final_type( a ), final_type( b ) );

                    if ( X >= p )
                    {
                        n = a - 1;
                        p /= X;
                    }
                    else
                    {
                        ans += a;
                        n = b - 1;
                        p = ( p - X ) / ( final_type( 1 ) - X );
                    }
                }

                ans += coin_flip_method( n, p );
                return ans;
            }//rejection_method

#if 0
            /*
                    [SETUP]
                    q <- 1-p
                    \sigma_1 <-\lower{ MAX(1,sqrt{npq \log(\frac{128np}{81\pi q})} ) }
                    \sigma_2 <- \lower{ MAX(1,sqrt{npq \log(\frac{128nq}{\pi p})} }

                    \delta_1 <- \sqrt{npq}(1+\frac{\sigma_1}{4np})
                    \delta_2 <- \sqrt{npq}(1+\frac{\sigma_2}{4nq})

                    c <- \frac{2\sigma_1}{np}

                    a_1 <- \frac{1}{2} e^{c} \delta_1 \sqrt{2 \pi}
                    a_2 <- \frac{1}{2} \delta_2 sqrt{2 \pi}
                    a_3 <- e^{\frac{\sigma_1}{npq}} \frac{2\delta_1^2}{\sigma_1} e^{- \frac{\sigma_1^2}{2\delta_1^2}}
                    a_4 <- \frac{2\delta_2^2}{\sigma_2} e^{-\frac{\sigma_2^2}{2\delta_2^2}}

                    s <- a_1 + a_2 + a_3 + a_4

                    [GENERATOR]
                    REPEAT
                        Generate a uniform [0,s] random variate U
                        CASE
                            U <= a_1:
                                Generate a normal random variate N;
                                Y <- \delta_1 |N|
                                Reject <- [Y >= \sigma_1]
                                IF NOT Reject THEN
                                    X <- \low{Y}
                                    V <- -E-\frac{N^2}{2}+c where E is an exponential random variate
                            a_1 < U <= a_1+a_2
                                Generate a normal random variate N;
                                Y <- \delta_2 |N|
                                Reject <- [Y >= \sigma_2]
                                IF NOT Reject THEN
                                    X <- \lower{-Y}
                                    V <- -E-\frac{N^2}{2} where E is an exponential random variate
                            a_1+a_2 < U <= a_1+a_2+a_3
                                Generate iid exponential random variates E_1 E_2
                                Y <- \sigma_1 + 2 \dleta_1 \frac{E_1}{\sigma_1}
                                X <- \lower{Y}
                                V <- -E_2-\sigma_1 \frac{Y}{2\delta_1^2} + \frac{\sigma_1}{nq}
                                Reject <- False
                            a_1+a_2+a_3 < U
                                Generate two iid exponential random variate E_1 E_2
                                Y <- \sigma_2 + 2 \delta_2^2 \frac{E_1}{\sigma_2}
                                X <- \lower{-Y}
                                V <- -E_2-\sigma_2\frac{Y}{2\delta_2^2}
                                Reject <- False


                        Reject <- Reject OR [X<-np} OR [X >nq]
                        Reject <- Reject OR [V>log(b_{np}+\frac{X}{b_{np}}]
                    UNTIL NOT Reject
                    RETURN X
            */
        protected:
            return_type
            rejection_method()
            {
                const final_type n = n_;
                const final_type p = ( p_ > 0.5 ) ? p_ : ( 1.0 - p_ );
                const final_type np = std::floor( n * p );
                const final_type q = 1.0 - p;
                const final_type pi = 3.1415926535897932384626433L;
                const final_type sigma_1 = std::round( std::max( final_type( 1 ), std::sqrt( n * p * q * std::log( 128.0 * n * p / 81.0 * pi * q ) ) ) );
                const final_type sigma_2 = std::round( std::max( final_type( 1 ), std::sqrt( n * p * q * std::log( 128.0 * n * q / pi * p ) ) ) );
                const final_type delta_1 = std::sqrt( n * p * q ) * ( 1.0 + sigma_1 ) / ( 4.0 * n * p );
                const final_type delta_2 = std::sqrt( n * p * q ) * ( 1.0 + sigma_2 ) / ( 4.0 * n * q );
                const final_type c = ( sigma_1 + sigma_1 ) / ( n * p );
                const final_type a_1 = 0.5 * std::exp( c ) * delta_1 * std::sqrt( pi + pi );
                const final_type a_2 = 0.5 * delta_2 * std::sqrt( pi + pi );
                const final_type a_3 = std::exp( sigma_1 / ( n * p * q ) ) * ( 2 * delta_1 * delta_1 ) / sigma_1 * std::exp( -sigma_1 / ( 2 * delta_1 * delta_1 ) );
                const final_type a_4 = 2 * delta_2 * delta_2 * std::exp( -sigma_1 * sigma_1 / ( 2 * delta_2 * delta_2 ) );
                const final_type s = a_1 + a_2 + a_3 + a_4;
                bool reject;
                return_type ans;

                for ( ;; )
                {
                    const final_type U = e_() * s;
                    const final_type E_1 = make_exponential();
                    const final_type E_2 = make_exponential();
                    const final_type N = make_normal();
                    final_type X( 0 );
                    final_type Y( 0 );
                    final_type V( 0 );

                    if ( U <= a_1 )
                    {
                        Y = delta_1 * std::abs( N );
                        reject = Y > sigma_1;

                        if ( !reject )
                        {
                            X = std::floor( Y );
                            V = -E_1 - N * N / 2 + c;
                        }
                    }
                    else
                        if ( U <= ( a_1 + a_2 ) )
                        {
                            Y = delta_2 * std::abs( N );
                            reject = Y > sigma_2;

                            if ( !reject )
                            {
                                X = std::floor( -Y );
                                V = -E_1 - 0.5 * N * N;
                            }
                        }
                        else
                            if ( U <= ( a_1 + a_2 + a_3 ) )
                            {
                                Y = sigma_1 + 2 * delta_1 * E_1 / sigma_1;
                                X = std::floor( Y );
                                V = -E_2 - sigma_1 * 0.5 * Y / ( delta_1 * delta_1 ) + sigma_1 / ( n * q );
                                reject = false;
                            }
                            else
                            {
                                Y = sigma_2 + 2 * delta_2 * delta_2 * E_1 / sigma_2;
                                X = std::floor( -Y );
                                V = -E_2 - sigma_2 * 0.5 * Y / ( delta_2 * delta_2 );
                                reject = false;
                            }

                    reject |= ( X < -n * p ) || ( X > n * q );
                    reject |= V > ( std::lgamma( np + 1 ) + std::lgamma( n - np + 1 ) - std::lgamma( np + X + 1 ) - std::lgamma( n - np - X + 1 ) + X * std::log( np / ( n - np ) ) );

                    if ( !reject )
                    {
                        ans = static_cast<return_type>( X );
                        break;
                    }
                }

                return ( p_ > 0.5 ) ? ( n - ans ) : ans;
            }//rejection_method

#endif

    };

}//namespace vg



#endif//_BINOMIAL_HPP_INCLUDED_OIJSI83LKJA091LKAJFOIMNVLKNDOIUHJ3LKJAFSL7ALKDIE8


