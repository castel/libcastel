#pragma once

#include <string>

#include <llvm/Value.h>

#include "castel/ast/expr/Class.hh"
#include "castel/ast/tools/Visitor.hh"
#include "castel/builder/Context.hh"
#include "castel/builder/Scope.hh"

namespace castel
{

    namespace builder
    {

        /**
         * An helper class building a runtime class box from an AST.
         */

        class ClassBuilder
        {

        public:

            inline ClassBuilder( std::string const & name = "", llvm::Value * parent = nullptr, ast::expr::Class::Member * members = nullptr );

        public:

            /**
             * @return Class name
             */

            inline std::string const & name( void ) const;

            /**
             * @param name Class name
             */

            inline ClassBuilder & name( std::string const & name );

        public:

            /**
             * @return LLVM value of the parent class
             */

            inline llvm::Value * parent( void ) const;

            /**
             * @param name LLVM value of the parent class
             */

            inline ClassBuilder & parent( llvm::Value * parent );

        public:

            /**
             * @return Member list
             */

            inline ast::expr::Class::Member * members( void ) const;

            /**
             * @param members Member list
             *
             * The member list will not be owned by the ClassBuilder. You have to delete it explicitely when
             * you don't need the ClassBuilder instance anymore (except if another object is owning the member
             * list, such as an AST node).
             */

            inline ClassBuilder & members( ast::expr::Class::Member * members );

        public:

            /**
             * @param context Related context
             *
             * Compile the AST elements into a llvm value containing a top-level runtime::boxes::Class*
             */

            inline llvm::Value * create( builder::Context & context ) const;

            /**
             * @param scope Parent scope
             *
             * Compile the AST elements into a llvm value containing a scope runtime::boxes::Class* (this class
             * will have r/w access on each variable of the parent scopes).
             */

            inline llvm::Value * create( builder::Scope & scope ) const;

        private:

            /**
             * @param context Related context
             * @param scope Parent scope (if applicable)
             *
             * Compile the AST elements into a llvm value containing a runtime::boxes::Class*.
             */

            llvm::Value * create( builder::Context & context, builder::Scope * scope ) const;

        private:

            /**
             * @param context Related context
             * @param scope Parent scope (if applicable)
             *
             * Compile the AST elements into a llvm value containing a function pointer which, when called, will
             * initialize the attributes belonging to the class instance.
             */

            llvm::Value * createInitializer( builder::Context & context, builder::Scope * scope ) const;

        private:

            std::string mName;
            llvm::Value * mParent;
            ast::expr::Class::Member * mMembers;

        };

    }

}

#include <string>

#include <llvm/Value.h>

#include "castel/ast/expr/Class.hh"
#include "castel/builder/Context.hh"
#include "castel/builder/Scope.hh"

namespace castel
{

    namespace builder
    {

        ClassBuilder::ClassBuilder( std::string const & name, llvm::Value * parent, ast::expr::Class::Member * members )
            : mName( name )
            , mParent( parent )
            , mMembers( members )
        {
        }

        std::string const & ClassBuilder::name( void ) const
        {
            return mName;
        }

        ClassBuilder & ClassBuilder::name( std::string const & name )
        {
            mName = name;

            return * this;
        }

        llvm::Value * ClassBuilder::parent( void ) const
        {
            return mParent;
        }

        ClassBuilder & ClassBuilder::parent( llvm::Value * parent )
        {
            mParent = parent;

            return * this;
        }

        ast::expr::Class::Member * ClassBuilder::members( void ) const
        {
            return mMembers;
        }

        ClassBuilder & ClassBuilder::members( ast::expr::Class::Member * members )
        {
            mMembers = members;

            return * this;
        }

        llvm::Value * ClassBuilder::create( builder::Context & context ) const
        {
            return this->create( context, nullptr );
        }

        llvm::Value * ClassBuilder::create( builder::Scope & scope ) const
        {
            return this->create( scope.context( ), & scope );
        }

    }

}
