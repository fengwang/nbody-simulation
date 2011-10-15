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

namespace vg
{

    template <
				typename Return_Type,
             	template<class, class> class Distribution,
             	typename Engine
             >
    struct variate_generator<Return_Type, Distribution, Engine>::iterator
    {
    public:
        typedef iterator                                        self_type;
        typedef typename variate_generator::distribution_type   distribution_type;
        typedef typename variate_generator::return_type         return_type;
        typedef typename variate_generator::seed_type           seed_type;
        typedef typename variate_generator::return_type         value_type;
        typedef void                                            pointer;
        typedef void                                            reference;
        typedef std::size_t                                     size_type;
        typedef std::ptrdiff_t                                  difference_type;
        typedef std::input_iterator_tag                         iterator_category;

    private:
        distribution_type* dt_;
        size_type counter_;

    public:
        iterator( distribution_type* dt = 0 ) : dt_( dt ), counter_( 0 ) {}

        iterator( const self_type& other )
        {
            operator = ( other );
        }

        self_type& 
		operator = ( const self_type& other )
        {
            dt_ = other.dt_;
            counter_ = other.counter_;
            return *this;
        }

        self_type& 
		operator ++ ()
        {
            ++counter_;
            return *this;
        }

        const self_type 
		operator ++( int )
        {
            self_type ans( *this );
            ++( *this );
            return ans;
        }

        self_type& 
		operator -- ()
        {
            --counter_;
            return *this;
        }

        const self_type 
		operator --( int )
        {
            self_type ans( *this );
            --( *this );
            return ans;
        }

        value_type 
		operator* ()
        {
            return ( *dt_ )();
        }

        friend
        const self_type 
		operator + ( const self_type& lhs, const size_type& rhs )
        {
            self_type ans( lhs );
            ans.counter_ += rhs;
            return ans;
        }

        friend
        const self_type 
		operator + ( const size_type& lhs, const self_type& rhs )
        {
            return rhs + lhs;
        }

        friend
        const self_type 
		operator - ( const self_type& lhs, const size_type& rhs )
        {
            self_type ans( lhs );
            ans.counter_ -= rhs;
            return ans;
        }

        friend
        bool 
		operator != ( const self_type& lhs, const self_type& rhs )
        {
            return lhs.counter_ != rhs.counter_;
        }

        friend
        bool 
		operator == ( const self_type& lhs, const self_type& rhs )
        {
            return lhs.counter_ == rhs.counter_;
        }
    };

}//namespace vg


