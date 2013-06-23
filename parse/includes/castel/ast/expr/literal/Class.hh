#pragma once

#include <string>
#include <utility>

#include "castel/ast/tools/Hold.hh"
#include "castel/ast/tools/List.hh"
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

                class Function;

                class Class : public ast::Expression
                {

                public:

                    class Member;

                    class Attribute;

                    class Method;

                    class Constructor;

                    class Operator;

                public:

                    inline Class( ast::tools::List< ast::expr::literal::Class::Member > && members );

                    inline Class( ast::tools::List< ast::expr::literal::Class::Member > && members, ast::tools::Hold< ast::Expression > && parent );

                public:

                    inline ast::tools::Hold< ast::Expression > const & parent( void ) const;

                    inline ast::tools::Hold< ast::Expression > & parent( void );

                    inline Class & parent( ast::tools::Hold< ast::Expression > && parent );

                public:

                    inline ast::tools::List< ast::expr::literal::Class::Member > const & members( void ) const;

                    inline ast::tools::List< ast::expr::literal::Class::Member > & members( void );

                    inline Class & members( ast::tools::List< ast::expr::literal::Class::Member > && members );

                public:

                    virtual inline void accept( ast::tools::ConstVisitor & visitor ) const;

                    virtual inline void accept( ast::tools::Visitor & visitor );

                private:

                    ast::tools::Hold< ast::Expression > mParent;

                    ast::tools::List< ast::expr::literal::Class::Member > mMembers;

                };

                class Class::Member
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

                    inline Attribute( ast::expr::literal::Class::Member::Visibility visibility, ast::expr::literal::Class::Member::Host host, std::string const & name, ast::tools::Hold< ast::Expression > && initializer = ast::tools::Hold< ast::Expression >( ) );

                public:

                    inline ast::tools::Hold< ast::Expression > const & initializer( void ) const;

                    inline ast::tools::Hold< ast::Expression > & initialize( void );

                    inline Attribute & initializer( ast::tools::Hold< ast::Expression > && initializer );

                private:

                    ast::tools::Hold< ast::Expression > mInitializer;

                };

                class Class::Method : public Class::Member
                {

                public:

                    inline Method( ast::expr::literal::Class::Member::Visibility visibility, ast::expr::literal::Class::Member::Host host, std::string const & name, ast::tools::Hold< ast::expr::literal::Function > && function );

                public:

                    inline ast::tools::Hold< ast::expr::literal::Function > const & function( void ) const;

                    inline ast::tools::Hold< ast::expr::literal::Function > & function( void );

                    inline Method & function( ast::tools::Hold< ast::expr::literal::Function > && function );

                private:

                    ast::tools::Hold< ast::expr::literal::Function > mFunction;

                };

                class Class::Constructor : public Class::Member
                {

                public:

                    inline Constructor( ast::expr::literal::Class::Member::Visibility visibility, ast::tools::Hold< ast::expr::literal::Function > && function );

                public:

                    inline ast::tools::Hold< ast::expr::literal::Function > const & function( void ) const;

                    inline ast::tools::Hold< ast::expr::literal::Function > & function( void );

                    inline Constructor & function( ast::tools::Hold< ast::expr::literal::Function > && function );

                private:

                    ast::tools::Hold< ast::expr::literal::Function > mFunction;

                };

                class Class::Operator : public Class::Member
                {

                public:

                    inline Operator( ast::expr::literal::Class::Member::Visibility visibility, int type, ast::tools::Hold< ast::expr::literal::Function > && function );

                public:

                    inline int type( void ) const;

                    inline Operator & type( int type );

                public:

                    inline ast::tools::Hold< ast::expr::literal::Function > const & function( void ) const;

                    inline ast::tools::Hold< ast::expr::literal::Function > & function( void );

                    inline Operator & function( ast::tools::Hold< ast::expr::literal::Function > && function );

                private:

                    int mType;

                    ast::tools::Hold< ast::expr::literal::Function > mFunction;

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

                Class::Attribute::Attribute( ast::expr::literal::Class::Member::Visibility visibility, ast::expr::literal::Class::Member::Host host, std::string const & name, ast::tools::Hold< ast::Expression > && initializer )
                    : Member( visibility, host, name )
                    , mInitializer( std::move( initializer ) )
                {
                }

                ast::tools::Hold< ast::Expression > const & Class::Attribute::initializer( void ) const
                {
                    return mInitializer;
                }

                ast::tools::Hold< ast::Expression > & Class::Attribute::initialize( void )
                {
                    return mInitializer;
                }

                Class::Attribute & Class::Attribute::initializer( ast::tools::Hold< ast::Expression > && initializer )
                {
                    mInitializer = std::move( initializer );

                    return * this;
                }

                Class::Method::Method( ast::expr::literal::Class::Member::Visibility visibility, ast::expr::literal::Class::Member::Host host, std::string const & name, ast::tools::Hold< ast::expr::literal::Function > && function )
                    : Member( visibility, host, name )
                    , mFunction( std::move( function ) )
                {
                }

                ast::tools::Hold< ast::expr::literal::Function > const & Class::Method::function( void ) const
                {
                    return mFunction;
                }

                ast::tools::Hold< ast::expr::literal::Function > & Class::Method::function( void )
                {
                    return mFunction;
                }

                Class::Method & Class::Method::function( ast::tools::Hold< ast::expr::literal::Function > && function )
                {
                    mFunction = std::move( function );

                    return * this;
                }

                Class::Constructor::Constructor( ast::expr::literal::Class::Member::Visibility visibility, ast::tools::Hold< ast::expr::literal::Function > && function )
                    : Member( visibility, ast::expr::literal::Class::Member::Host::Class, "constructor" )
                    , mFunction( std::move( function ) )
                {
                }

                ast::tools::Hold< ast::expr::literal::Function > const & Class::Constructor::function( void ) const
                {
                    return mFunction;
                }

                ast::tools::Hold< ast::expr::literal::Function > & Class::Constructor::function( void )
                {
                    return mFunction;
                }

                Class::Constructor & Class::Constructor::function( ast::tools::Hold< ast::expr::literal::Function > && function )
                {
                    mFunction = std::move( function );

                    return * this;
                }

                Class::Operator::Operator( ast::expr::literal::Class::Member::Visibility visibility, int type, ast::tools::Hold< ast::expr::literal::Function > && function )
                    : Member( visibility, ast::expr::literal::Class::Member::Host::Class, "operator" )
                    , mType( type )
                    , mFunction( std::move( function ) )
                {
                }

                int Class::Operator::type( void ) const
                {
                    return mType;
                }

                Class::Operator & Class::Operator::type( int type )
                {
                    mType = type;

                    return * this;
                }

                ast::tools::Hold< ast::expr::literal::Function > const & Class::Operator::function( void ) const
                {
                    return mFunction;
                }

                ast::tools::Hold< ast::expr::literal::Function > & Class::Operator::function( void )
                {
                    return mFunction;
                }

                Class::Operator & Class::Operator::function( ast::tools::Hold< ast::expr::literal::Function > && function )
                {
                    mFunction = std::move( function );

                    return * this;
                }

                Class::Class( ast::tools::List< ast::expr::literal::Class::Member > && members )
                    : mMembers( std::move( members ) )
                {
                }

                Class::Class( ast::tools::List< ast::expr::literal::Class::Member > && members, ast::tools::Hold< ast::Expression > && parent )
                    : mParent( std::move( parent ) )
                    , mMembers( std::move( members ) )
                {
                }

                ast::tools::Hold< ast::Expression > const & Class::parent( void ) const
                {
                    return mParent;
                }

                ast::tools::Hold< ast::Expression > & Class::parent( void )
                {
                    return mParent;
                }

                Class & Class::parent( ast::tools::Hold< ast::Expression > && parent )
                {
                    mParent = std::move( parent );

                    return * this;
                }

                ast::tools::List< ast::expr::literal::Class::Member > const & Class::members( void ) const
                {
                    return mMembers;
                }

                ast::tools::List< ast::expr::literal::Class::Member > & Class::members( void )
                {
                    return mMembers;
                }

                Class & Class::members( ast::tools::List< ast::expr::literal::Class::Member > && members )
                {
                    mMembers = std::move( members );

                    return * this;
                }

                void Class::accept( ast::tools::ConstVisitor & visitor ) const
                {
                    visitor.visit( * this );
                }

                void Class::accept( ast::tools::Visitor & visitor )
                {
                    visitor.visit( * this );
                }

            }

        }

    }

}
