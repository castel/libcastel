#pragma once

#include <string>

#include "castel/ast/Expression.hh"

namespace castel
{

    namespace ast
    {

        namespace expr
        {

            class String : public ast::Expression
            {

            private:

                static inline std::string rawToLiteral( std::string const & rawValue );

                static inline std::string literalToRaw( std::string const & literalValue );

            public:

                static inline String * createFromRaw( std::string const & rawValue );

                static inline String * createFromLiteral( std::string const & literalValue );

            public:

                inline String( void );

            public:

                inline std::string const & rawValue( void ) const;

                inline String & rawValue( std::string const & rawValue );

            public:

                inline std::string const & literalValue( void ) const;

                inline String & literalValue( std::string const & literalValue );

            public:

                virtual inline void accept( ast::tools::Visitor & visitor );

            private:

                std::string mRawValue;

                std::string mLiteralValue;

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

            std::string String::rawToLiteral( std::string const & rawValue )
            {
                std::string result;

                std::string::const_iterator it;
                for ( it = rawValue.begin( ); it != rawValue.end( ); ++ it ) {
                    char c = * it;
                    if ( c < ' ' || c > '~' ) {
                        switch ( c ) {
                        case '\r': result += "\\r"; break;
                        case '\n': result += "\\n"; break;
                        case '\t': result += "\\t"; break;
                        default:   result += '?';
                        }
                    } else {
                        result += c;
                    }
                }

                return result;
            }

            std::string String::literalToRaw( std::string const & literalValue )
            {
                std::string result;

                std::string::const_iterator it;
                for ( it = literalValue.begin( ); it != literalValue.end( ); ++ it ) {
                    if ( * it == '\\' ) {
                        char c = * ++it;
                        switch ( c ) {
                        case 't': result += '\t'; break;
                        case 'n': result += '\n'; break;
                        default:  result += c;    break;
                        }
                    } else {
                        result += * it;
                    }
                }

                return result;
            }

            String * String::createFromRaw( std::string const & rawValue )
            {
                String * instance = new String( );
                instance->rawValue( rawValue );
                return instance;
            }

            String * String::createFromLiteral( std::string const & literalValue )
            {
                String * instance = new String( );
                instance->literalValue( literalValue );
                return instance;
            }

            String::String( void )
            {
            }

            std::string const & String::rawValue( void ) const
            {
                return mRawValue;
            }

            String & String::rawValue( std::string const & rawValue )
            {
                mRawValue = rawValue;
                mLiteralValue = ast::expr::String::rawToLiteral( rawValue );

                return * this;
            }

            std::string const & String::literalValue( void ) const
            {
                return mLiteralValue;
            }

            String & String::literalValue( std::string const & literalValue )
            {
                mRawValue = ast::expr::String::literalToRaw( literalValue );
                mLiteralValue = literalValue;

                return * this;
            }

            void String::accept( ast::tools::Visitor & visitor )
            {
                visitor.visit( * this );
            }

        }

    }

}
