#include <string>
#include <sstream>

#include "p9/ast/Numeric.hh"

using namespace p9;
using namespace p9::ast;

Numeric Numeric::fromString( std::string const & str )
{
	double numeric;
	
	std::stringstream sstream( str );
	sstream >> numeric;
	
	Numeric token;
	token.setNumeric( numeric );
	
	return token;
}

std::string Numeric::toString( void ) const
{
	std::stringstream sstream;
	sstream << mNumeric;
	return sstream.str( );
}
