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
#ifndef _POLYA_AEPPLI_HPP_INCLUDED_DSKL4EOIUJSARIGHHEREFORYOUTHEEOIJSFLKJSFLKJASLKJSFLKJSFDLKJSDDFLKJSFLKJDJFLKJSFLKJSFLD
#define _POLYA_AEPPLI_HPP_INCLUDED_DSKL4EOIUJSARIGHHEREFORYOUTHEEOIJSFLKJSFLKJASLKJSFLKJSFDLKJSDDFLKJSFLKJDJFLKJSFLKJSFLD

#include <vg/utility.hpp>
#include <vg/distribution/poisson.hpp>
#include <vg/distribution/gamma.hpp>

#include <cmath>
#include <cassert>

namespace vg
{

    template <   typename Return_Type,
                 typename Engine
             >
    struct polya_aeppli : private proxy<poisson<Return_Type, Engine>, 1>, 
                       private proxy<gamma<Return_Type, Engine>, 2>
    {
            typedef proxy<poisson<Return_Type, Engine>, 1> poisson_type;
            typedef proxy<gamma<Return_Type, Engine>, 2>   gamma_type;
            typedef Return_Type                            return_type;
            typedef Engine                                 engine_type;
            typedef typename poisson_type::final_type      final_type;
            typedef typename poisson_type::seed_type       seed_type;

            return_type beta_;
            return_type theta_;
            return_type lambda_;
            engine_type e_;

            explicit polya_aeppli( const return_type beta = 1,
                                const return_type theta = 1,
                                const return_type lambda = 1,
                                const seed_type sd = 0 )
                : beta_( beta ), theta_( theta ), lambda_( lambda ), e_( sd )
            {
                assert( beta > 0 );
                assert( theta > 0 );
                assert( lambda > 0 );
            }

            return_type
            operator()()
            {
                return do_generation( beta_, theta_, lambda_ );
            }

        protected:
            return_type
            do_generation( const final_type Beta, const final_type Theta, const final_type Lambda )
            {
                return polya_aeppli_direct_impl( Beta, Theta, Lambda );
            }
        private:
            return_type
            polya_aeppli_direct_impl(  const final_type Beta, const final_type Theta, const final_type Lambda )
            {
                const final_type z = poisson_type::do_generation( Beta * Beta / ( 4.0 * Theta ) );
                const final_type g = gamma_type::do_generation( z + Lambda );
                const final_type ans = g / Theta;
                return ans;
            }
    };

}//vg


#endif//_POLYA_AEPPLI_HPP_INCLUDED_DSKL4EOIUJSARIGHHEREFORYOUTHEEOIJSFLKJSFLKJASLKJSFLKJSFDLKJSDDFLKJSFLKJDJFLKJSFLKJSFLD

