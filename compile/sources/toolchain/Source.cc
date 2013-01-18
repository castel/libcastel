#include "castel/ast/Statement.hh"
#include "castel/lex/Lexer.hh"
#include "castel/parse/Parser.hh"
#include "castel/toolchain/Source.hh"

using namespace castel;
using toolchain::Source;

ast::Statement * Source::parse( void ) const
{
    lex::Lexer lexer( mCode.c_str( ), mCode.length( ) );
    return parse::Parser( lexer ).exec( );
}
