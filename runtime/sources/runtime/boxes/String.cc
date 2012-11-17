#include <cstring>

#include "castel/runtime/boxes/Bool.hh"
#include "castel/runtime/boxes/String.hh"
#include "castel/runtime/capi.hh"

using namespace castel;
using runtime::boxes::String;

bool String::operatorBool( runtime::Context * )
{
    return mLength > 0;
}

runtime::Box * String::operatorNumericAddition( runtime::Context * context, runtime::Box * operand )
{
    auto stringOperand = dynamic_cast< runtime::boxes::String * >( operand );

    if ( stringOperand == nullptr )
        return nullptr;

    unsigned int newLength = mLength + stringOperand->mLength;

    if ( newLength < mLength )
        context->fatal( "New string size will underflow." );

    char * data = context->createArray< char >( newLength + 1 );

    std::strncpy( data + 0, mValue, mLength );
    std::strncpy( data + mLength, stringOperand->mValue, stringOperand->mLength );

    return context->create< runtime::boxes::String >( data, newLength );
}

runtime::Box * String::operatorComparisonEqual( runtime::Context * context, runtime::Box * operand )
{
    auto stringOperand = dynamic_cast< runtime::boxes::String * >( operand );

    if ( stringOperand == nullptr )
        return nullptr;

    bool areStringsEqual = mLength == stringOperand->mLength && std::strcmp( mValue, stringOperand->mValue ) == 0;
    return context->create< runtime::boxes::Bool >( areStringsEqual );
}

runtime::Box * String::operatorComparisonNotEqual( runtime::Context * context, runtime::Box * operand )
{
    auto stringOperand = dynamic_cast< runtime::boxes::String * >( operand );

    if ( stringOperand == nullptr )
        return nullptr;

    bool areStringsNotEqual = mLength != stringOperand->mLength || std::strcmp( mValue, stringOperand->mValue ) != 0;
    return context->create< runtime::boxes::Bool >( areStringsNotEqual );
}
