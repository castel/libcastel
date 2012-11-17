#pragma once

#include <map>
#include <memory>
#include <string>

namespace castel
{

    namespace runtime
    {

        class Allocator;

        class Loader;

        /**
         */

        class Context
        {

        public:

            /**
             */

            inline Context( runtime::Allocator * allocator );

        public:

            /**
             */

            inline runtime::Allocator * allocator( void ) const;

        public:

            /**
             */

            inline runtime::Loader * loader( std::string const & name ) const;

            /**
             */

            inline Context & loader( std::string const & name, runtime::Loader * loader );

        public:

            /**
             */

            template < typename Type, typename ... Args >
            inline Type * create( Args ... args );

            /**
             */

            template < typename Type, typename ... Args >
            inline Type * createArray( unsigned int count, Args ... args );

        public:

            /**
             */

            inline runtime::Box * load( std::string const & locator );

        public:

            /**
             */

            void fatal( std::string const & error );

        private:

            std::shared_ptr< runtime::Allocator > mAllocator;

            std::map< std::string, std::shared_ptr< runtime::Loader > > mLoaders;

        };

    }

}

#include "castel/runtime/Allocator.hh"
#include "castel/runtime/Loader.hh"

namespace castel
{

    namespace runtime
    {

        Context::Context( runtime::Allocator * allocator )
            : mAllocator( allocator->sharedPointer( ) )
        {
        }

        runtime::Allocator * Context::allocator( void ) const
        {
            return mAllocator.get( );
        }

        runtime::Loader * Context::loader( std::string const & name ) const
        {
            auto it = mLoaders.find( name );

            return it != mLoaders.end( ) ? it->second.get( ) : nullptr;
        }

        Context & Context::loader( std::string const & name, runtime::Loader * loader )
        {
            if ( loader == nullptr ) {
                mLoaders.erase( name );
            } else {
                mLoaders[ name ] = loader->sharedPointer( );
            }

            return * this;
        }

        template < typename Type, typename ... Args >
        Type * Context::create( Args ... args )
        {
            return this->createArray< Type >( 1, args ... );
        }

        template < typename Type, typename ... Args >
        Type * Context::createArray( unsigned int count, Args ... args )
        {
            void * memory = mAllocator->alloc( sizeof ( Type ), count );

            for ( unsigned int t = 0; t < count; ++ t )
                new ( static_cast< char * >( memory ) + t * sizeof ( Type ) ) Type( args ... );

            return static_cast< Type * >( memory );
        }

    }

}
