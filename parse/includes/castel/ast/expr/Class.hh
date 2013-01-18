#pragma once

#include <memory>
#include <string>

#include "castel/ast/tools/Linked.hh"
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

            class Function;

            class Class : public ast::Expression
            {

            public:

                class Member;

                class Attribute;

                class Method;

            public:

                inline Class( ast::expr::Class::Member * members, ast::Expression * parent = nullptr );

            public:

                inline ast::Expression * parent( void ) const;

                inline Class & parent( ast::Expression * parent );

                inline ast::Expression * takeParent( void );

            public:

                inline ast::expr::Class::Member * members( void ) const;

                inline Class & members( ast::expr::Class::Member * members );

                inline ast::expr::Class::Member * takeMembers( void );

            public:

                virtual inline void accept( ast::tools::Visitor & visitor );

            private:

                std::unique_ptr< ast::Expression > mParent;

                std::unique_ptr< ast::expr::Class::Member > mMembers;

            };

            class Class::Member : public ast::tools::Linked< Class::Member >
            {

            public:

                enum class Visibility {
                    Public,
                    Protected,
                    Private,
                };

                enum class Type {
                    Static,
                    Binded,
                };

            public:

                class Visitor;

            protected:

                inline Member( ast::expr::Class::Member::Visibility visibility, ast::expr::Class::Member::Type type, std::string const & name );

            public:

                virtual ~Member( void ) { }

            public:

                inline ast::expr::Class::Member::Visibility visibility( void ) const;

                inline Member & visibility( ast::expr::Class::Member::Visibility visibility );

            public:

                inline ast::expr::Class::Member::Type type( void ) const;

                inline Member & type( ast::expr::Class::Member::Type type );

            public:

                inline std::string const & name( void ) const;

                inline Member & name( std::string const & );

            private:

                ast::expr::Class::Member::Visibility mVisibility;

                ast::expr::Class::Member::Type mType;

                std::string mName;

            };

            class Class::Attribute : public Class::Member
            {

            public:

                inline Attribute( ast::expr::Class::Member::Visibility visibility, ast::expr::Class::Member::Type type, std::string const & name, ast::Expression * initializer = nullptr );

            public:

                inline ast::Expression * initializer( void ) const;

                inline Attribute & initializer( ast::Expression * initializer );

                inline ast::Expression * takeInitializer( void );

            private:

                std::unique_ptr< ast::Expression > mInitializer;

            };

            class Class::Method : public Class::Member
            {

            public:

                inline Method( ast::expr::Class::Member::Visibility visibility, ast::expr::Class::Member::Type type, std::string const & name, ast::expr::Function * function );

            public:

                inline ast::expr::Function * function( void ) const;

                inline Method & function( ast::expr::Function * function );

                inline ast::expr::Function * takeFunction( void );

            private:

                std::unique_ptr< ast::expr::Function > mFunction;

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

            Class::Member::Member( ast::expr::Class::Member::Visibility visibility, ast::expr::Class::Member::Type type, std::string const & name )
                : mVisibility( visibility )
                , mType( type )
                , mName( name )
            {
            }

            ast::expr::Class::Member::Type Class::Member::type( void ) const
            {
                return mType;
            }

            Class::Member & Class::Member::type( ast::expr::Class::Member::Type type )
            {
                mType = type;

                return * this;
            }

            ast::expr::Class::Member::Visibility Class::Member::visibility( void ) const
            {
                return mVisibility;
            }

            Class::Member & Class::Member::visibility( ast::expr::Class::Member::Visibility visibility )
            {
                mVisibility = visibility;

                return * this;
            }

            std::string const & Class::Member::name( void ) const
            {
                return mName;
            }

            Class::Member & Class::Member::name( std::string const & name )
            {
                mName = name;

                return * this;
            }

            Class::Attribute::Attribute( ast::expr::Class::Member::Visibility visibility, ast::expr::Class::Member::Type type, std::string const & name, ast::Expression * initializer )
                : Member( visibility, type, name )
                , mInitializer( initializer )
            {
            }

            ast::Expression * Class::Attribute::initializer( void ) const
            {
                return mInitializer.get( );
            }

            Class::Attribute & Class::Attribute::initializer( ast::Expression * initializer )
            {
                mInitializer.reset( initializer );

                return * this;
            }

            ast::Expression * Class::Attribute::takeInitializer( void )
            {
                return mInitializer.release( );
            }

            Class::Method::Method( ast::expr::Class::Member::Visibility visibility, ast::expr::Class::Member::Type type, std::string const & name, ast::expr::Function * function )
                : Member( visibility, type, name )
                , mFunction( function )
            {
            }

            ast::expr::Function * Class::Method::function( void ) const
            {
                return mFunction.get( );
            }

            Class::Method & Class::Method::function( ast::expr::Function * function )
            {
                mFunction.reset( function );

                return * this;
            }

            ast::expr::Function * Class::Method::takeFunction( void )
            {
                return mFunction.release( );
            }

            Class::Class( ast::expr::Class::Member * members, ast::Expression * parent )
                : mParent( parent )
                , mMembers( members )
            {
            }

            ast::Expression * Class::parent( void ) const
            {
                return mParent.get( );
            }

            Class & Class::parent( ast::Expression * parent )
            {
                mParent.reset( parent );

                return * this;
            }

            ast::Expression * Class::takeParent( void )
            {
                return mParent.release( );
            }

            ast::expr::Class::Member * Class::members( void ) const
            {
                return mMembers.get( );
            }

            Class & Class::members( ast::expr::Class::Member * members )
            {
                mMembers.reset( members );

                return * this;
            }

            ast::expr::Class::Member * Class::takeMembers( void )
            {
                return mMembers.release( );
            }

            void Class::accept( ast::tools::Visitor & visitor )
            {
                visitor.visit( * this );
            }

        }

    }

}
