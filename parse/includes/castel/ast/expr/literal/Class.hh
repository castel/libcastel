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

            namespace literal
            {

                class Function;

                class Class : public ast::Expression
                {

                public:

                    class Member;

                    class Attribute;

                    class Method;

                public:

                    inline Class( ast::expr::literal::Class::Member * members, ast::Expression * parent = nullptr );

                public:

                    inline ast::Expression * parent( void ) const;

                    inline Class & parent( ast::Expression * parent );

                    inline ast::Expression * takeParent( void );

                public:

                    inline ast::expr::literal::Class::Member * members( void ) const;

                    inline Class & members( ast::expr::literal::Class::Member * members );

                    inline ast::expr::literal::Class::Member * takeMembers( void );

                public:

                    virtual inline void accept( ast::tools::Visitor & visitor );

                private:

                    std::unique_ptr< ast::Expression > mParent;

                    std::unique_ptr< ast::expr::literal::Class::Member > mMembers;

                };

                class Class::Member : public ast::tools::Linked< Class::Member >
                {

                public:

                    enum class Visibility {
                        Public,
                        Protected,
                        Private,
                    };

                    enum class Host {
                        Class,
                        Instance,
                    };

                public:

                    class Visitor;

                protected:

                    inline Member( ast::expr::literal::Class::Member::Visibility visibility, ast::expr::literal::Class::Member::Host type, std::string const & name );

                public:

                    virtual ~Member( void ) { }

                public:

                    inline ast::expr::literal::Class::Member::Visibility visibility( void ) const;

                    inline Member & visibility( ast::expr::literal::Class::Member::Visibility visibility );

                public:

                    inline ast::expr::literal::Class::Member::Host host( void ) const;

                    inline Member & host( ast::expr::literal::Class::Member::Host type );

                public:

                    inline std::string const & name( void ) const;

                    inline Member & name( std::string const & );

                private:

                    ast::expr::literal::Class::Member::Visibility mVisibility;

                    ast::expr::literal::Class::Member::Host mHost;

                    std::string mName;

                };

                class Class::Attribute : public Class::Member
                {

                public:

                    inline Attribute( ast::expr::literal::Class::Member::Visibility visibility, ast::expr::literal::Class::Member::Host host, std::string const & name, ast::Expression * initializer = nullptr );

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

                    inline Method( ast::expr::literal::Class::Member::Visibility visibility, ast::expr::literal::Class::Member::Host host, std::string const & name, ast::expr::literal::Function * function );

                public:

                    inline ast::expr::literal::Function * function( void ) const;

                    inline Method & function( ast::expr::literal::Function * function );

                    inline ast::expr::literal::Function * takeFunction( void );

                private:

                    std::unique_ptr< ast::expr::literal::Function > mFunction;

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

        namespace expr
        {

            namespace literal
            {

                Class::Member::Member( ast::expr::literal::Class::Member::Visibility visibility, ast::expr::literal::Class::Member::Host host, std::string const & name )
                    : mVisibility( visibility )
                    , mHost( host )
                    , mName( name )
                {
                }

                ast::expr::literal::Class::Member::Host Class::Member::host( void ) const
                {
                    return mHost;
                }

                Class::Member & Class::Member::host( ast::expr::literal::Class::Member::Host host )
                {
                    mHost = host;

                    return * this;
                }

                ast::expr::literal::Class::Member::Visibility Class::Member::visibility( void ) const
                {
                    return mVisibility;
                }

                Class::Member & Class::Member::visibility( ast::expr::literal::Class::Member::Visibility visibility )
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

                Class::Attribute::Attribute( ast::expr::literal::Class::Member::Visibility visibility, ast::expr::literal::Class::Member::Host host, std::string const & name, ast::Expression * initializer )
                    : Member( visibility, host, name )
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

                Class::Method::Method( ast::expr::literal::Class::Member::Visibility visibility, ast::expr::literal::Class::Member::Host host, std::string const & name, ast::expr::literal::Function * function )
                    : Member( visibility, host, name )
                    , mFunction( function )
                {
                }

                ast::expr::literal::Function * Class::Method::function( void ) const
                {
                    return mFunction.get( );
                }

                Class::Method & Class::Method::function( ast::expr::literal::Function * function )
                {
                    mFunction.reset( function );

                    return * this;
                }

                ast::expr::literal::Function * Class::Method::takeFunction( void )
                {
                    return mFunction.release( );
                }

                Class::Class( ast::expr::literal::Class::Member * members, ast::Expression * parent )
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

                ast::expr::literal::Class::Member * Class::members( void ) const
                {
                    return mMembers.get( );
                }

                Class & Class::members( ast::expr::literal::Class::Member * members )
                {
                    mMembers.reset( members );

                    return * this;
                }

                ast::expr::literal::Class::Member * Class::takeMembers( void )
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

}
