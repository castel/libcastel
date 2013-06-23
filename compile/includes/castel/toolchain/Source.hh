#pragma once

#include <fstream>
#include <iosfwd>
#include <string>

#include "castel/ast/tools/List.hh"

namespace castel
{

    namespace ast
    {

        class Statement;

    }

    namespace toolchain
    {

        class Source
        {

        public:

            static inline Source fromString( std::string const & code );

            static inline Source fromFile( std::string const & filePath );

            static inline Source fromStream( std::istream & stream );

        protected:

            inline Source( std::string const & name, std::string const & code );

        public:

            inline std::string const & name( void ) const;

            inline Source & name( std::string const & name );

        public:

            inline bool isSafe( void ) const;

            inline Source & isSafe( bool safeFlag );

        public:

            ast::tools::List< ast::Statement > parse( void ) const;

        private:

            std::string mName;

            std::string mCode;

            bool mSafeFlag;

        };

    }

}

#include "castel/ast/Statement.hh"

namespace castel
{

    namespace toolchain
    {

        Source Source::fromString( std::string const & code )
        {
            return Source( "*inline*", code );
        }

        Source Source::fromFile( std::string const & filePath )
        {
            std::ifstream stream( filePath );

            std::string::size_type position = filePath.rfind( '/' );
            std::string fileName = position != std::string::npos ? filePath.substr( position ) : filePath;

            std::istreambuf_iterator< char > eos;
            std::string code( std::istreambuf_iterator< char >( stream ), eos );

            return Source( fileName, code );
        }

        Source Source::fromStream( std::istream & stream )
        {
            std::istreambuf_iterator< char > eos;
            std::string code( std::istreambuf_iterator< char >( stream ), eos );

            return Source( "*stream*", code );
        }

        Source::Source( std::string const & name, std::string const & code )
            : mName( name )
            , mCode( code )
        {
        }

        std::string const & Source::name( void ) const
        {
            return mName;
        }

        Source & Source::name( std::string const & name )
        {
            mName = name;

            return * this;
        }

        bool Source::isSafe( void ) const
        {
            return mSafeFlag;
        }

        Source & Source::isSafe( bool safeFlag )
        {
            mSafeFlag = safeFlag;

            return * this;
        }

    }

}
