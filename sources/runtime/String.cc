#include <cstring>

#include "castel/runtime/Boolean.hh"
#include "castel/runtime/Box.hh"
#include "castel/runtime/String.hh"
#include "castel/runtime/api.hh"

using namespace castel;
using runtime::String;

String & String::string( char const * string, int length, bool copy )
{
    if ( string ) {
        mLength = length == -1 ? std::strlen( string ) : length;
        mString = copy ? std::strcpy( reinterpret_cast< char * >( castel_allocate( mLength + 1, 1 ) ), string ) : string;
    } else {
        mString = std::strcpy( reinterpret_cast< char * >( castel_allocate( 1, 1 ) ), "" );
        mLength = 0;
    }

    return * this;
}


runtime::Box * String::positiveOperator( void )
{
    return nullptr;
}

runtime::Box * String::negativeOperator( void )
{
    return nullptr;
}

runtime::Box * String::preIncrementationOperator( void )
{
    return nullptr;
}

runtime::Box * String::postIncrementationOperator( void )
{
    return nullptr;
}

runtime::Box * String::preDecrementationOperator( void )
{
    return nullptr;
}

runtime::Box * String::postDecrementationOperator( void )
{
    return nullptr;
}

runtime::Box * String::additionOperator( runtime::Box * operand )
{
    runtime::String * stringOperand = dynamic_cast< runtime::String * >( operand );

    if ( ! stringOperand )
        return nullptr;

    int length = mLength + stringOperand->mLength;
    char * string = reinterpret_cast< char * >( castel_allocate( length + 1, sizeof( char ) ) );

    std::strcpy( string, mString );
    std::strcpy( string + mLength, stringOperand->mString );
    string[ length ] = '\0';

    return runtime::String::create( string, length, false );
}

runtime::Box * String::substractionOperator( runtime::Box * )
{
    return nullptr;
}

runtime::Box * String::multiplicationOperator( runtime::Box * )
{
    return nullptr;
}

runtime::Box * String::divisionOperator( runtime::Box * )
{
    return nullptr;
}

runtime::Box * String::moduloOperator( runtime::Box * )
{
    return nullptr;
}

runtime::Box * String::lesserOperator( runtime::Box * )
{
    return nullptr;
}

runtime::Box * String::greaterOperator( runtime::Box * )
{
    return nullptr;
}

runtime::Box * String::lesserOrEqualOperator( runtime::Box * )
{
    return nullptr;
}

runtime::Box * String::greaterOrEqualOperator( runtime::Box * )
{
    return nullptr;
}

runtime::Box * String::equalOperator( runtime::Box * operand )
{
    runtime::String * stringOperand = dynamic_cast< runtime::String * >( operand );

    if ( ! stringOperand )
        return nullptr;

    return runtime::Boolean::create( mLength == stringOperand->mLength && std::strcmp( mString, stringOperand->mString ) == 0 );
}

runtime::Box * String::notEqualOperator( runtime::Box * operand )
{
    runtime::String * stringOperand = dynamic_cast< runtime::String * >( operand );

    if ( ! stringOperand )
        return nullptr;

    return runtime::Boolean::create( mLength != stringOperand->mLength || std::strcmp( mString, stringOperand->mString ) != 0 );
}

runtime::Box * String::additionAssignmentOperator( runtime::Box * operand )
{
    runtime::String * stringOperand = dynamic_cast< runtime::String * >( operand );

    if ( ! stringOperand )
        return nullptr;

    int length = mLength + stringOperand->mLength;
    char * string = reinterpret_cast< char * >( castel_allocate( length + 1, sizeof( char ) ) );

    std::strcpy( string, mString );
    std::strcpy( string + mLength, stringOperand->mString );
    string[ length ] = '\0';

    this->string( string, length, false );

    return this;
}

runtime::Box * String::substractionAssignmentOperator( runtime::Box * )
{
    return nullptr;
}

runtime::Box * String::multiplicationAssignmentOperator( runtime::Box * )
{
    return nullptr;
}

runtime::Box * String::divisionAssignmentOperator( runtime::Box * )
{
    return nullptr;
}

runtime::Box * String::moduloAssignmentOperator( runtime::Box * )
{
    return nullptr;
}

runtime::Box * String::callOperator( unsigned int, runtime::Box ** )
{
    return nullptr;
}

runtime::Box * String::subscriptOperator( unsigned int, runtime::Box ** )
{
    return nullptr;
}

bool String::booleanOperator( void )
{
    return false;
}
