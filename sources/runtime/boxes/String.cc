#include <cstring>

#include "castel/runtime/boxes/Bool.hh"
#include "castel/runtime/boxes/String.hh"
#include "castel/runtime/capi.hh"

using namespace castel;
using runtime::boxes::String;

bool String::operatorBool( void )
{
    return mLength > 0;
}

runtime::Box * String::operatorNumericAddition( runtime::Box * operand )
{
    auto stringOperand = dynamic_cast< runtime::boxes::String * >( operand );

    if ( stringOperand == nullptr )
        return nullptr;

    unsigned int newLength = mLength + stringOperand->mLength;

    if ( newLength < mLength )
        ::castel_fatal( "New string size will underflow." );

    char * data = reinterpret_cast< char * >( ::castel_malloc( sizeof( char ), newLength + 1 ) );

    std::strcpy( data + 0, mValue );
    std::strcpy( data + mLength, stringOperand->mValue );

    return runtime::boxes::String::create( data, newLength );
}

runtime::Box * String::operatorComparisonEqual( runtime::Box * operand )
{
    auto stringOperand = dynamic_cast< runtime::boxes::String * >( operand );

    if ( stringOperand == nullptr )
        return nullptr;

    return runtime::boxes::Bool::create( mLength == stringOperand->mLength && std::strcmp( mValue, stringOperand->mValue ) == 0 );
}

runtime::Box * String::operatorComparisonNotEqual( runtime::Box * operand )
{
    auto stringOperand = dynamic_cast< runtime::boxes::String * >( operand );

    if ( stringOperand == nullptr )
        return nullptr;

    return runtime::boxes::Bool::create( mLength != stringOperand->mLength || std::strcmp( mValue, stringOperand->mValue ) != 0 );
}
