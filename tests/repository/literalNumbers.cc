#include <memory>

#include <castel/ast/Token.hh>

#include "P9Tests.hh"

using namespace castel;

void P9Tests::literalNumbers( void )
{
    this->initParser( &fromString, "0+1" );

    std::unique_ptr< ast::Token > root( this->parser( ).exec( ) );
}
