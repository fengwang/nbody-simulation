#ifndef _TRI_ARY_HPP_INCLUDED_SOIJ349I8AFDSKLJ3OIUAFS98Y34UIOWRE98Y34IOUYHFASDUJ
#define _TRI_ARY_HPP_INCLUDED_SOIJ349I8AFDSKLJ3OIUAFS98Y34UIOWRE98Y34IOUYHFASDUJ

#include <cartesian_coordinate.hpp>

#include <iostream>
#include <cmath>

namespace feng
{

    template < typename T = double >
    struct tri_array
    {
            typedef T                       value_type;
            typedef tri_array                 self_type;
            typedef value_type&             value_reference;
            typedef const value_reference   const_value_reference;

        private:
            value_type x_;
            value_type y_;
            value_type z_;

        public:
            explicit tri_array( const value_type& x = value_type(),
                                const value_type& y = value_type(),
                                const value_type& z = value_type()
                            ) : x_( x ), y_( y ), z_( z )
            {}

            template< typename U >
            tri_array( const tri_array<U>& other ) :
                x_( static_cast<value_type>( other.x_ ) ),
                y_( static_cast<value_type>( other.y_ ) ),
                z_( static_cast<value_type>( other.z_ )
                  )
            {}

            tri_array( const cartesian_coordinate<T>& from,
                       const cartesian_coordinate<T>& to )
                : x_( from.x() - to.x() ),
                  y_( from.y() - to.y() ),
                  z_( from.z() - to.z() )
            {}

            template< typename U >
            const self_type&
            operator = ( const tri_array<U>& other )
            {
                x_ = static_cast<value_type>( other.x_ );
                y_ = static_cast<value_type>( other.y_ );
                z_ = static_cast<value_type>( other.z_ );

                return *this;
            }

            template< typename U >
            const self_type&
            operator *=( const U& v )
            {
                x_ *= static_cast<value_type>( v );
                y_ *= static_cast<value_type>( v );
                z_ *= static_cast<value_type>( v );

                return *this;
            }

            template< typename U >
            const self_type&
            operator /=( const U& v )
            {
                x_ /= static_cast<value_type>( v );
                y_ /= static_cast<value_type>( v );
                z_ /= static_cast<value_type>( v );

                return *this;
            }

            const self_type&
            operator += ( const self_type& other )
            {
                x_ += other.x_;
                y_ += other.y_;
                z_ += other.z_;

                return *this;
            }

            const self_type&
            operator -= ( const self_type& other )
            {
                x_ -= other.x_;
                y_ -= other.y_;
                z_ -= other.z_;

                return *this;
            }

        public:
            value_reference
            x()
            { return x_; }

            value_reference
            y()
            { return y_; }

            value_reference
            z()
            { return z_; }

        public:
            value_type
            x() const
            { return x_; }

            value_type
            y() const
            { return y_; }

            value_type
            z() const
            { return z_; }

        public:
            value_type
            det() const
            {
                const value_type  x = x_ * x_;
                const value_type  y = y_ * y_;
                const value_type  z = z_ * z_;
                const value_type  ans = ::std::sqrt( x + y + z );

                return ans;
            }

        public:
            const self_type
            to_unit() const
            {
                const value_type d = det();

                if ( value_type() == d )
                {
                    return self_type();
                }

                self_type ans( *this );
                ans /= d;

                return ans;
            }
    };


    //overloading + - * /
    //
    template< typename T >
    const tri_array<T>
    operator + ( const tri_array<T>& lhs, const tri_array<T>& rhs )
    {
        tri_array<T> ans( lhs );
        ans += rhs;
        return ans;
    }

    template< typename T >
    const tri_array<T>
    operator - ( const tri_array<T>& lhs, const tri_array<T>& rhs )
    {
        tri_array<T> ans( lhs );
        ans -= rhs;
        return ans;
    }

    template< typename T, typename U >
    const tri_array<T>
    operator *( const tri_array<T>& lhs, const U& rhs )
    {
        tri_array<T> ans( lhs );
        ans *= rhs;
        return ans;
    }

    template< typename T, typename U >
    const tri_array<T>
    operator *( const U& rhs, const tri_array<T>& lhs )
    {
        tri_array<T> ans( lhs );
        ans *= rhs;
        return ans;
    }

    template< typename T, typename U >
    const tri_array<T>
    operator / ( const tri_array<T>& lhs, const U& rhs )
    {
        tri_array<T> ans( lhs );
        ans /= rhs;
        return ans;
    }

    template<typename T>
    std::ostream&
    operator << ( std::ostream& lhs, const tri_array<T>& rhs )
    {
        const char* const tagy = rhs.y() < 0 ? " " : " +";
        const char* const tagz = rhs.z() < 0 ? " " : " +";
        lhs << rhs.x() << "<i>" << tagy << rhs.y() << "<j>" << tagz << rhs.z() << "<k>";
        return lhs;
    }

    template<typename T>
    bool
    operator == ( const tri_array<T>& lhs, const tri_array<T>& rhs )
    {
        return  ( lhs.x() == rhs.x() ) &&
                ( lhs.y() == rhs.y() ) &&
                ( lhs.z() == rhs.z() );
    }


    template<typename T>
    T
    dot_product( const tri_array<T>& lhs, const tri_array<T>& rhs )
    {
        const T x = lhs.x() * rhs.x();
        const T y = lhs.y() * rhs.y();
        const T z = lhs.z() * rhs.z();
        const T ans = x + y + z;

        return ans;
    }

    template<typename T>
    T
    inner_product( const tri_array<T>& lhs, const tri_array<T>& rhs )
    {
        return dot_product( lhs, rhs );
    }

    template<typename T>
    T
    scalar_product( const tri_array<T>& lhs, const tri_array<T>& rhs )
    {
        return dot_product( lhs, rhs );
    }

    template<typename T>
    const tri_array<T>
    cross_product( const tri_array<T>& lhs, const tri_array<T>& rhs )
    {
        const T x = lhs.y() * rhs.z() - rhs.y() * lhs.z();
        const T y = -lhs.x() * rhs.z() + rhs.x() * lhs.z();
        const T z = lhs.x() * rhs.y() - rhs.x() * lhs.y();

        const tri_array<T> ans( x, y, z );
        return ans;
    }

    template<typename T>
    T
    included_angle( const tri_array<T>& lhs, const tri_array<T>& rhs )
    {
        const T lhs_det = lhs.det();
        const T rhs_det = rhs.det();
        const T dot = dot_product( lhs, rhs );

        if ( T() == dot )
        {
            return T();
        }

        const T ans = ::std::acos( dot / ( lhs_det * rhs_det ) );

        return ans;
    }

}//namespace feng

#endif//_TRI_ARY_HPP_INCLUDED_SOIJ349I8AFDSKLJ3OIUAFS98Y34UIOWRE98Y34IOUYHFASDUJ

