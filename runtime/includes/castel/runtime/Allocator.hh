#pragma once

#include <memory>

namespace castel
{

    namespace runtime
    {

        /**
         */

        class Allocator : public std::enable_shared_from_this< Allocator >
        {

        public:

            /**
             */

            virtual inline ~Allocator( void );

        public:

            /**
             */

            inline std::shared_ptr< Allocator > sharedPointer( void );

        public:

            /**
             */

            virtual void * alloc( unsigned int size, unsigned int count ) = 0;

            /**
             */

            template < typename Type >
            inline Type * alloc( unsigned int count );

        };

    }

}

namespace castel
{

    namespace runtime
    {

        Allocator::~Allocator( void )
        {
        }

        std::shared_ptr< Allocator > Allocator::sharedPointer( void )
        {
            return this->shared_from_this( );
        }

        template < typename Type >
        Type * Allocator::alloc( unsigned int count )
        {
            return reinterpret_cast< Type * >( this->alloc( sizeof ( Type ), count ) );
        }

    }

}
