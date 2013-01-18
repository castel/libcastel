#pragma once

#include <string>

#include "castel/ast/Expression.hh"

namespace castel
{

    namespace ast
    {

        namespace tools
        {

            class Visitor;

        }

        namespace expr
        {

            class External : public ast::Expression
            {

            private:

                static inline std::string rawToLiteral( std::string const & rawValue );

                static inline std::string literalToRaw( std::string const & literalValue );

            public:

                static inline External * createFromRaw( std::string const & rawValue );

                static inline External * createFromLiteral( std::string const & literalValue );

            private:

                inline External( void );

            public:

                inline std::string const & rawName( void ) const;

                inline External & rawName( std::string const & rawName );

            public:

                inline std::string const & literalName( void ) const;

                inline External & literalName( std::string const & literalName );

            public:

                virtual inline void accept( ast::tools::Visitor & visitor );

            private:

                std::string mRawName;

                std::string mLiteralName;

            };

        }

    }

}

#include "castel/ast/tools/Visitor.hh"

namespace castel
{

    namespace ast
    {

        namespace expr
        {

            std::string External::rawToLiteral( std::string const & rawName )
            {
                return "%" + rawName;
            }

            std::string External::literalToRaw( std::string const & literalName )
            {
                return literalName.substr( 1 );
            }

            External * External::createFromRaw( std::string const & rawName )
            {
                External * instance = new External( );
                instance->rawName( rawName );
                return instance;
            }

            External * External::createFromLiteral( std::string const & literalName )
            {
                External * instance = new External( );
                instance->literalName( literalName );
                return instance;
            }

            External::External( void )
            {
            }

            std::string const & External::rawName( void ) const
            {
                return mRawName;
            }

            External & External::rawName( std::string const & rawName )
            {
                mRawName = rawName;
                mLiteralName = ast::expr::External::rawToLiteral( rawName );

                return * this;
            }

            std::string const & External::literalName( void ) const
            {
                return mLiteralName;
            }

            External & External::literalName( std::string const & literalName )
            {
                mRawName = ast::expr::External::literalToRaw( literalName );
                mLiteralName = literalName;

                return * this;
            }

            void External::accept( ast::tools::Visitor & visitor )
            {
                visitor.visit( * this );
            }

        }

    }

}
