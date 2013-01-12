#include <cstring>

#include "castel/runtime/boxes/Bool.hh"
#include "castel/runtime/boxes/String.hh"
#include "castel/runtime/helper/Fatal.hh"
#include "castel/runtime/helper/create.hh"
#include "castel/runtime/helper/malloc.hh"
#include "castel/runtime/Box.hh"

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
        runtime::helper::Fatal( ) << "New string size will underflow." << std::endl;

    char * data = runtime::helper::malloc< char >( newLength + 1 );

    std::strncpy( data + 0, mValue, mLength );
    std::strncpy( data + mLength, stringOperand->mValue, stringOperand->mLength );

    return runtime::helper::create< runtime::boxes::String >( data, newLength );
}

runtime::Box * String::operatorComparisonEqual( runtime::Box * operand )
{
    auto stringOperand = dynamic_cast< runtime::boxes::String * >( operand );

    if ( stringOperand == nullptr )
        return nullptr;

    bool areStringsEqual = mLength == stringOperand->mLength && std::strcmp( mValue, stringOperand->mValue ) == 0;
    return runtime::helper::create< runtime::boxes::Bool >( areStringsEqual );
}

runtime::Box * String::operatorComparisonNotEqual( runtime::Box * operand )
{
    auto stringOperand = dynamic_cast< runtime::boxes::String * >( operand );

    if ( stringOperand == nullptr )
        return nullptr;

    bool areStringsNotEqual = mLength != stringOperand->mLength || std::strcmp( mValue, stringOperand->mValue ) != 0;
    return runtime::helper::create< runtime::boxes::Bool >( areStringsNotEqual );
}
