#pragma once

#include <string>

#include "castel/ast/Expression.hh"

namespace castel
{

    namespace ast
    {

        namespace tools
        {

            class ConstVisitor;

            class Visitor;

        }

        namespace expr
        {

            namespace literal
            {

                class String : public ast::Expression
                {

                public:

                    static inline std::string parse( std::string const & literalValue );

                    static inline std::string stringify( std::string const & rawValue );

                public:

                    inline String( std::string const & value );

                public:

                    inline std::string const & value( void ) const;

                    inline String & value( std::string const & value );

                public:

                    virtual inline void accept( ast::tools::ConstVisitor & visitor ) const;

                    virtual inline void accept( ast::tools::Visitor & visitor );

                private:

                    std::string mValue;

                };

            }

        }

    }

}

#include "castel/ast/tools/ConstVisitor.hh"
#include "castel/ast/tools/Visitor.hh"

namespace castel
{

    namespace ast
    {

        namespace expr
        {

            namespace literal
            {

                std::string String::parse( std::string const & literal )
                {
                    std::string result;

                    std::string::const_iterator it;
                    for ( it = literal.begin( ); it != literal.end( ); ++ it ) {
                        if ( * it == '\\' ) {
                            char c = * ++it;
                            switch ( c ) {
                            case '\\': result += '\\'; break;
                            case 't':  result += '\t'; break;
                            case 'n':  result += '\n'; break;
                            default:                   break;
                            }
                        } else {
                            result += * it;
                        }
                    }

                    return result;
                }

                std::string String::stringify( std::string const & raw )
                {
                    std::string result;

                    std::string::const_iterator it;
                    for ( it = raw.begin( ); it != raw.end( ); ++ it ) {
                        char c = * it;
                        if ( c < ' ' || c > '~' ) {
                            switch ( c ) {
                            case '\\': result += "\\\\"; break;
                            case '\r': result += "\\r";  break;
                            case '\n': result += "\\n";  break;
                            case '\t': result += "\\t";  break;
                            case '"':  result += "\\\""; break;
                            default:   result += '?';
                            }
                        } else {
                            result += c;
                        }
                    }

                    return result;
                }

                String::String( std::string const & value )
                    : mValue( value )
                {
                }

                std::string const & String::value( void ) const
                {
                    return mValue;
                }

                String & String::value( std::string const & value )
                {
                    mValue = value;

                    return * this;
                }

                void String::accept( ast::tools::ConstVisitor & visitor ) const
                {
                    visitor.visit( * this );
                }

                void String::accept( ast::tools::Visitor & visitor )
                {
                    visitor.visit( * this );
                }

            }

        }

    }

}
