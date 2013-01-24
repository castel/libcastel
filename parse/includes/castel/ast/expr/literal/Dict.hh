#pragma once

#include <memory>
#include <string>

#include "castel/ast/tools/Linked.hh"
#include "castel/ast/Expression.hh"

namespace castel
{

    namespace ast
    {

        namespace expr
        {

            namespace literal
            {

                class Dict : public ast::Expression
                {

                public:

                    class Item;

                public:

                    inline Dict( ast::expr::literal::Dict::Item * items );

                public:

                    inline ast::expr::literal::Dict::Item * items( void ) const;

                    inline Dict & items( ast::expr::literal::Dict::Item * items );

                    inline ast::expr::literal::Dict::Item * takeItems( void );

                public:

                    virtual inline void accept( ast::tools::Visitor & visitor );

                private:

                    std::unique_ptr< ast::expr::literal::Dict::Item > mItems;

                };

                class Dict::Item : public ast::tools::Linked< Dict::Item >
                {

                public:

                    inline Item( std::string const & name, ast::Expression * value );

                public:

                    inline std::string const & name( void ) const;

                    inline Item & name( std::string const & name );

                public:

                    inline ast::Expression * value( void ) const;

                    inline Item & value( ast::Expression * value );

                    inline ast::Expression * takeValue( void );

                private:

                    std::string mName;

                    std::unique_ptr< ast::Expression > mValue;

                };

            }

        }

    }

}

#include <string>

#include "castel/ast/tools/Visitor.hh"

namespace castel
{

    namespace ast
    {

        namespace expr
        {

            namespace literal
            {

                Dict::Item::Item( std::string const & name, ast::Expression * value )
                    : mName( name )
                    , mValue( value )
                {
                }

                std::string const & Dict::Item::name( void ) const
                {
                    return mName;
                }

                Dict::Item & Dict::Item::name( std::string const & name )
                {
                    mName = name;

                    return * this;
                }

                ast::Expression * Dict::Item::value( void ) const
                {
                    return mValue.get( );
                }

                Dict::Item & Dict::Item::value( ast::Expression * value )
                {
                    mValue.reset( value );

                    return * this;
                }

                ast::Expression * Dict::Item::takeValue( void )
                {
                    return mValue.release( );
                }

                Dict::Dict( ast::expr::literal::Dict::Item * items )
                    : mItems( items )
                {
                }

                ast::expr::literal::Dict::Item * Dict::items( void ) const
                {
                    return mItems.get( );
                }

                Dict & Dict::items( ast::expr::literal::Dict::Item * items )
                {
                    mItems.reset( items );

                    return * this;
                }

                ast::expr::literal::Dict::Item * Dict::takeItems( void )
                {
                    return mItems.release( );
                }

                void Dict::accept( ast::tools::Visitor & visitor )
                {
                    visitor.visit( * this );
                }

            }

        }

    }

}
