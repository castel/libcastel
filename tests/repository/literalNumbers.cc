#include <memory>

#include <p9/ast/Token.hh>

#include "P9Tests.hh"

using namespace p9;

void P9Tests::literalNumbers( void )
{
    this->initParser( &fromString, "0+1" );

    std::auto_ptr< ast::Token > root( this->parser( ).exec( ) );
}
