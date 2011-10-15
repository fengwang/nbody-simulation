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
#ifndef _NEWTON_RAPHSON_HPP_INCLUDED_SDFLKJSDFKLJCVMNSFUIO4KJHSDFKJHSFKJHSKJHSAFIUHIUYWIERUYSKFJDHSFDKJHXVJKFHSKJFHASKJFH
#define _NEWTON_RAPHSON_HPP_INCLUDED_SDFLKJSDFKLJCVMNSFUIO4KJHSDFKJHSFKJHSKJHSAFIUHIUYWIERUYSKFJDHSFDKJHXVJKFHSKJFHASKJFH

#include <cassert>
#include <cstddef>
#include <functional>

namespace vg
{

template <typename T>
struct newton_raphson
{
    typedef std::size_t size_type;
    typedef T value_type;
    typedef std::function<value_type(value_type)> function_type;

    value_type first_;
    value_type last_;
    function_type f_;
    function_type df_;
    const size_type times_;

    newton_raphson( const value_type first,    // x1
                    const value_type last,     // x2
                    const function_type f,     // f(x)
                    const function_type df,    // f'(x)
                    const size_type times = 20 ) :
        first_(first), last_(last), f_(f), df_(df), times_(times) 
    {}

    value_type 
    operator()() const 
    {
        value_type ans = ( first_ + last_ ) / value_type(2);

        for ( size_type i = 0; i < times_; ++i )
        {
            assert( (ans-first_)*(ans-last_) < value_type(0) );
            ans -= f(ans) / df(ans);
        }

        return ans;
    }

};

}//namespace vg

#endif//_NEWTON_RAPHSON_HPP_INCLUDED_SDFLKJSDFKLJCVMNSFUIO4KJHSDFKJHSFKJHSKJHSAFIUHIUYWIERUYSKFJDHSFDKJHXVJKFHSKJFHASKJFH

