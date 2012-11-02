#pragma once

#include <memory>

#include "castel/ast/Statement.hh"

namespace castel
{

    namespace ast
    {

        namespace tools
        {

            class Visitor;

        }

        class Expression;

        namespace stmt
        {

            namespace decl
            {

                class Variables : public ast::Statement
                {

                public:

                    class Variable;

                public:

                    inline Variables( ast::stmt::decl::Variables::Variable * variables );

                public:

                    inline ast::stmt::decl::Variables::Variable * variables( void ) const;

                    inline Variables & variables( ast::stmt::decl::Variables::Variable * variables );

                    inline ast::stmt::decl::Variables::Variable * takeVariables( void );

                public:

                    virtual inline void accept( ast::tools::Visitor & visitor );

                private:

                    std::unique_ptr< ast::stmt::decl::Variables::Variable > mVariables;

                };

                class Variables::Variable : public utils::Linked< Variable >
                {

                public:

                    inline Variable( std::string const & name, ast::Expression * initializer = nullptr );

                public:

                    inline std::string const & name( void ) const;

                    inline Variable & name( std::string const & name );

                public:

                    inline ast::Expression * initializer( void ) const;

                    inline Variable & initializer( ast::Expression * initializer );

                    inline ast::Expression * takeInitializer( void );

                private:

                    std::string mName;

                    std::unique_ptr< ast::Expression > mInitializer;

                };

            }

        }

    }

}

#include "castel/ast/tools/Visitor.hh"

namespace castel
{

    namespace ast
    {

        namespace stmt
        {

            namespace decl
            {

                Variables::Variable::Variable( std::string const & name, ast::Expression * initializer )
                    : mName( name )
                    , mInitializer( initializer )
                {
                }

                std::string const & Variables::Variable::name( void ) const
                {
                    return mName;
                }

                Variables::Variable & Variables::Variable::name( std::string const & name )
                {
                    mName = name;

                    return * this;
                }

                ast::Expression * Variables::Variable::initializer( void ) const
                {
                    return mInitializer.get( );
                }

                Variables::Variable & Variables::Variable::initializer( ast::Expression * initializer )
                {
                    mInitializer.reset( initializer );

                    return * this;
                }

                ast::Expression * Variables::Variable::takeInitializer( void )
                {
                    return mInitializer.release( );
                }

                Variables::Variables( ast::stmt::decl::Variables::Variable * variables )
                    : mVariables( variables )
                {
                }

                ast::stmt::decl::Variables::Variable * Variables::variables( void ) const
                {
                    return mVariables.get( );
                }

                Variables & Variables::variables( ast::stmt::decl::Variables::Variable * variables )
                {
                    mVariables.reset( variables );

                    return * this;
                }

                ast::stmt::decl::Variables::Variable * Variables::takeVariables( void )
                {
                    return mVariables.release( );
                }

                void Variables::accept( ast::tools::Visitor & visitor )
                {
                    visitor.visit( * this );
                }

            }

        }

    }

}
