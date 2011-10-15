#ifndef _SINGLETON_HPP_INCLUDED_SOIJ3908UASFLI3J98UAFSLK3UJ908UAFSLIU398UAFLI2U8
#define _SINGLETON_HPP_INCLUDED_SOIJ3908UASFLI3J98UAFSLK3UJ908UAFSLIU398UAFLI2U8

/*
 * Warning:
 *          this method of singleton implementation is nice and neat,
 *          the shortcomming is, if in anther compile unit,
 *          a global variable refers here when initializing,
 *          everything would happen.
 *
 *          example:
 *
 *          //xx1.cc
 *          int global_xx1 = singleton<int>::instance();
 *
 *          As this assignment is invoked before runtime,
 *          Nothing here promises instance_ being initialized before global_xx1.
 */

namespace feng
{
    template< typename T >
    struct singleton
    {
            typedef T value_type;
            typedef singleton self_type;

        private://not to be implemented
            singleton( const self_type& );
            self_type& operator = ( const self_type& );
            singleton();

        private:    
            struct creator
            {
                creator()
                {
                    self_type::instance();
                }
                inline void 
                null_action() const 
                {
                    //empty
                }
            };

            static creator creator_;

        public:
            static value_type&
            instance()
            {
                static value_type instance_;
                creator_.null_action();
                return instance_;
            }
    };

    template<typename T>
    typename singleton<T>::creator singleton<T>::creator_;    

}//namespace feng

#endif//_SINGLETON_HPP_INCLUDED_SOIJ3908UASFLI3J98UAFSLK3UJ908UAFSLIU398UAFLI2U8

