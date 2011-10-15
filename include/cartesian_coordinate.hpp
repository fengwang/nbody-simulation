#ifndef _COORDINATE_HPP_INCLUDED_SOIJ348YAFOKJ3O8IUWOIUJASFLKJ438UYAFIJFSDOIUJEK
#define _COORDINATE_HPP_INCLUDED_SOIJ348YAFOKJ3O8IUWOIUJASFLKJ438UYAFIJFSDOIUJEK

#include <iostream>
#include <cmath>

namespace feng
{

    template< typename T = double >
    struct cartesian_coordinate
    {
            typedef T                       value_type;
            typedef cartesian_coordinate    self_type;
            typedef T&                      reference_type;
            //typedef const reference_type    const_reference_type;
            typedef const value_type        const_reference_type;

            value_type x_;
            value_type y_;
            value_type z_;
        public:
            self_type& 
            operator += ( const self_type& other )
            {
                x_ += other.x_;
                y_ += other.y_;
                z_ += other.z_;
                return *this;
            }

            self_type& 
            operator -= ( const self_type& other )
            {
                x_ -= other.x_;
                y_ -= other.y_;
                z_ -= other.z_;
                return *this;
            }

            template<typename U>
            self_type& 
            operator *= ( const U& other )
            {
                x_ *= other;
                y_ *= other;
                z_ *= other;
                return *this;
            }

            template<typename U>
            self_type& 
            operator /= ( const U& other )
            {
                x_ /= other;
                y_ /= other;
                z_ /= other;
                return *this;
            }

        public:
            explicit cartesian_coordinate(  const value_type& x = value_type( 0 ),
                                    const value_type& y = value_type( 0 ),
                                    const value_type& z = value_type( 0 )
                               ) : x_( x ), y_( y ), z_( z )
            {}

            cartesian_coordinate( const self_type& other )
                : x_( other.x_ ), y_( other.y_ ), z_( other.z_ )
            {}

            template< typename U >
            cartesian_coordinate( const cartesian_coordinate<U>& other )
                :   x_( static_cast<T>( other.x_ ) ),
                    y_( static_cast<T>( other.y_ ) ),
                    z_( static_cast<T>( other.z_ ) )
            {}

            const self_type&
            operator = ( const self_type& other )
            {
                x_ = other.x_;
                y_ = other.y_;
                z_ = other.z_;

                return *this;
            }

            template< typename U>
            const self_type&
            operator = ( const cartesian_coordinate<U>& other )
            {
                x_ = static_cast<U>( other.x_ );
                y_ = static_cast<U>( other.y_ );
                z_ = static_cast<U>( other.z_ );

                return *this;
            }

        public:
            reference_type
            x()
            {
                return x_;
            }

            reference_type
            y()
            {
                return y_;
            }

            reference_type
            z()
            {
                return z_;
            }

            const_reference_type
            x() const
            {
                return x_;
            }

            const_reference_type
            y() const
            {
                return y_;
            }

            const_reference_type
            z() const
            {
                return z_;
            }

    };//struct cartesian_coordinate

    template< typename T>
    const cartesian_coordinate<T>
    operator + ( const cartesian_coordinate<T>& lhs, const cartesian_coordinate<T>& rhs )
    {
        cartesian_coordinate<T> ans( lhs );
        ans += rhs;
        return ans;
    }

    template< typename T>
    const cartesian_coordinate<T>
    operator - ( const cartesian_coordinate<T>& lhs, const cartesian_coordinate<T>& rhs )
    {
        cartesian_coordinate<T> ans( lhs );
        ans -= rhs;
        return ans;
    }

    template< typename T, typename U >
    const cartesian_coordinate<T>
    operator * ( const cartesian_coordinate<T>& lhs, const U& rhs )
    {
        cartesian_coordinate<T> ans( lhs );
        ans *= rhs;
        return ans;
    }

    template< typename T, typename U >
    const cartesian_coordinate<T>
    operator * ( const U lhs, const cartesian_coordinate<T>& rhs )
    {
        cartesian_coordinate<T> ans( rhs );
        ans *= lhs;
        return ans;
    }

    template< typename T, typename U >
    const cartesian_coordinate<T>
    operator / ( const cartesian_coordinate<T>& lhs, const U& rhs )
    {
        cartesian_coordinate<T> ans( lhs );
        ans /= rhs;
        return ans;
    }

    template< typename T >
    std::ostream&
    operator << ( std::ostream& lhs, const cartesian_coordinate<T>& rhs )
    {
        lhs << "(" 
            << rhs.x() << ", " 
            << rhs.y() << ", " 
            << rhs.z() 
            << ")";
        return lhs;
    }

    template< typename T>
    T
    square_distance( const cartesian_coordinate<T>& lhs, const cartesian_coordinate<T>& rhs )
    {
        const T x_diff = lhs.x() - rhs.x();
        const T y_diff = lhs.y() - rhs.y();
        const T z_diff = lhs.z() - rhs.z();
        const T ans = x_diff * x_diff + y_diff * y_diff + z_diff * z_diff;
        return ans;
    }

    template< typename T>
    T
    distance( const cartesian_coordinate<T>& lhs, const cartesian_coordinate<T>& rhs )
    {
        const T sd = square_distance( lhs, rhs );
        return sqrt( sd );
    }

    template< typename T>
    bool
    operator == ( const cartesian_coordinate<T>& lhs, const cartesian_coordinate<T>& rhs )
    {
        return  lhs.x() == rhs.x() &&
                lhs.y() == rhs.y() &&
                lhs.z() == rhs.z();
    }

    template< typename T>
    bool
    operator != ( const cartesian_coordinate<T>& lhs, const cartesian_coordinate<T>& rhs )
    {
        return !(lhs==rhs);
    }

}//namespace feng

#endif//_COORDINATE_HPP_INCLUDED_SOIJ348YAFOKJ3O8IUWOIUJASFLKJ438UYAFIJFSDOIUJEK

