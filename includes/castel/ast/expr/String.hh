#pragma once

#include <string>

#include "castel/ast/Expression.hh"
#include "castel/lexer/Lexeme.hh"
#include "castel/utils/Visitor.hh"

namespace castel
{

    namespace ast
    {

        namespace expr
        {

            class String : public ast::Expression
            {

            public:

                String     ( void )
                : mContent ( "" )
                {
                }

                String     ( std::string const & content )
                : mContent ( "" )
                {
                    this->parse( content );
                }

                String     ( lexer::Lexeme const & lexeme )
                : mContent ( "" )
                {
                    std::string str = lexeme.as< std::string >( );
                    this->parse( str.substr( 1, str.length( ) - 2 ) );
                }

            public:

                String & parse( std::string const & string )
                {
                    mContent = "";

                    std::string::const_iterator it;
                    for ( it = string.begin( ); it != string.end( ); ++ it ) {
                        if ( * it == '\\' ) {
                            char c = * ++it;
                            switch ( c ) {
                                case 't': mContent += '\t'; break;
                                case 'n': mContent += '\n'; break;
                                default:  mContent += c;    break;
                            }
                        } else {
                            mContent += * it;
                        }
                    }

                    return * this;
                }

            public:

                std::string const & content( void ) const
                {
                    return mContent;
                }

                String & value( std::string const & content )
                {
                    mContent = content;

                    return * this;
                }

            public:

                virtual void accept( utils::Visitor & visitor )
                {
                    visitor.visit( * this );
                }

            private:

                std::string mContent;

            };

        }

    }

}
