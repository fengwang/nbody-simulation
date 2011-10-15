#ifndef _PARTICLE_HPP_INCLUDED_SFD894387FSDIUVKJCXFDIUOSEOIWRU43897FSUIDOVJKXCVNDKFRWEUIO4389SFDVCXKFSHFEIUR38989RWSFHVFH
#define _PARTICLE_HPP_INCLUDED_SFD894387FSDIUVKJCXFDIUOSEOIWRU43897FSUIDOVJKXCVNDKFRWEUIO4389SFDVCXKFSHFEIUR38989RWSFHVFH

#include <cartesian_coordinate.hpp>
#include <tri_array.hpp>

#include <iostream>

namespace feng
{
    template< typename T >
    struct particle
    {
        typedef T                                   value_type;
        typedef cartesian_coordinate<value_type>    position_type;
        typedef tri_array<value_type>               velocity_type;
        typedef velocity_type                       force_type;

        T               m_;
        position_type   p_;
        velocity_type   v_;

        particle( const value_type m = 0 , const position_type& p = position_type(), const velocity_type& v = velocity_type() )
            : m_(m), p_(p), v_(v)
        {}
        
        particle( const particle& p ) 
            : m_(p.m_), p_(p.p_), v_(p.v_)
        {}

        value_type& 
        m()
        { return m_; }

        const value_type
        m() const 
        { return m_; }

        position_type& 
        p()
        { return p_; }

        const position_type 
        p() const 
        { return p_; }

        velocity_type& 
        v()
        { return v_; }

        const velocity_type
        v() const 
        { return v_; }

        const force_type
        gravity( const particle& p ) const 
        {
            const value_type dd = square_distance( p_, p.p_ );
            //const value_type G = 1.0; 
            const value_type G = 6.67e-11; 
            const value_type f = m_ * p.m_ * G / dd;
            if ( isinf(f) || isnan(f) ) return force_type();
            force_type F( p.p_, p_ );
            F.to_unit();
            F *= f;
            return F;
        }

    };//struct particle

    template<typename T>
    const typename particle<T>::force_type 
    gravity( const particle<T>& host, const particle<T>& source )
    { return host.gravity(source); }

    template<typename T>
    std::ostream& 
    operator << ( std::ostream& lhs, const particle<T>& rhs )
    {
        lhs << rhs.m() << "|" << rhs.p() << rhs.v();
        return lhs;
    }

}//namespace feng

#endif//_PARTICLE_HPP_INCLUDED_SFD894387FSDIUVKJCXFDIUOSEOIWRU43897FSUIDOVJKXCVNDKFRWEUIO4389SFDVCXKFSHFEIUR38989RWSFHVFH

