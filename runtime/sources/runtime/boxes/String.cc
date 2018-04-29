#include <cstddef>
#include <cstring>

#include "castel/runtime/boxes/Boolean.hh"
#include "castel/runtime/boxes/String.hh"
#include "castel/runtime/helper/Fatal.hh"
#include "castel/runtime/helper/create.hh"
#include "castel/runtime/helper/malloc.hh"
#include "castel/runtime/Box.hh"

using namespace castel;
using runtime::boxes::String;

bool String::operatorBoolCast( void )
{
    return mLength > 0;
}

runtime::Box * String::operatorAddition( runtime::Box * operand )
{
    auto stringOperand = dynamic_cast< runtime::boxes::String * >( operand );

    if ( stringOperand == nullptr )
        return nullptr;

    unsigned int newLength = mLength + stringOperand->mLength;

    if ( newLength < mLength )
        runtime::helper::Fatal( ) << "New string size will underflow." << std::endl;

    std::uint8_t * data = runtime::helper::malloc< std::uint8_t >( newLength );

    std::memcpy( data + 0, mValue, mLength );
    std::memcpy( data + mLength, stringOperand->mValue, stringOperand->mLength );

    return runtime::helper::create< runtime::boxes::String >( data, newLength );
}

runtime::Box * String::operatorEqual( runtime::Box * operand )
{
    auto stringOperand = dynamic_cast< runtime::boxes::String * >( operand );

    if ( stringOperand == nullptr )
        return nullptr;

    bool areStringsEqual = mLength == stringOperand->mLength && std::memcmp( mValue, stringOperand->mValue, mLength ) == 0;
    return runtime::helper::create< runtime::boxes::Boolean >( areStringsEqual );
}

runtime::Box * String::operatorNotEqual( runtime::Box * operand )
{
    auto stringOperand = dynamic_cast< runtime::boxes::String * >( operand );

    if ( stringOperand == nullptr )
        return nullptr;

    bool areStringsNotEqual = mLength != stringOperand->mLength || std::memcmp( mValue, stringOperand->mValue, mLength ) != 0;
    return runtime::helper::create< runtime::boxes::Boolean >( areStringsNotEqual );
}
