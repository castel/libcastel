#include "castel/runtime/boxes/Boolean.hh"
#include "castel/runtime/boxes/Number.hh"
#include "castel/runtime/helper/create.hh"
#include "castel/runtime/Box.hh"

using namespace castel;
using runtime::boxes::Number;

bool Number::operatorBoolCast( void )
{
    return mValue != 0;
}

runtime::Box * Number::operatorPositive( void )
{
    return runtime::helper::create< runtime::boxes::Number >( + mValue );
}

runtime::Box * Number::operatorNegative( void )
{
    return runtime::helper::create< runtime::boxes::Number >( - mValue );
}

runtime::Box * Number::operatorPreIncrementation( void )
{
    mValue += 1;

    return this;
}

runtime::Box * Number::operatorPreDecrementation( void )
{
    mValue -= 1;

    return this;
}

runtime::Box * Number::operatorPostIncrementation( void )
{
    return runtime::helper::create< runtime::boxes::Number >( mValue ++ );
}

runtime::Box * Number::operatorPostDecrementation( void )
{
    return runtime::helper::create< runtime::boxes::Number >( mValue -- );
}

runtime::Box * Number::operatorAddition( runtime::Box * operand )
{
    auto numberOperand = dynamic_cast< runtime::boxes::Number * >( operand );

    if ( ! numberOperand )
        return nullptr;

    return runtime::helper::create< runtime::boxes::Number >( mValue + numberOperand->mValue );
}

runtime::Box * Number::operatorSubstraction( runtime::Box * operand )
{
    auto numberOperand = dynamic_cast< runtime::boxes::Number * >( operand );

    if ( ! numberOperand )
        return nullptr;

    return runtime::helper::create< runtime::boxes::Number >( mValue - numberOperand->mValue );
}

runtime::Box * Number::operatorMultiplication( runtime::Box * operand )
{
    auto numberOperand = dynamic_cast< runtime::boxes::Number * >( operand );

    if ( ! numberOperand )
        return nullptr;

    return runtime::helper::create< runtime::boxes::Number >( mValue * numberOperand->mValue );
}

runtime::Box * Number::operatorDivision( runtime::Box * operand )
{
    auto numberOperand = dynamic_cast< runtime::boxes::Number * >( operand );

    if ( ! numberOperand )
        return nullptr;

    return runtime::helper::create< runtime::boxes::Number >( mValue / numberOperand->mValue );
}

runtime::Box * Number::operatorModulo( runtime::Box * operand )
{
    auto numberOperand = dynamic_cast< runtime::boxes::Number * >( operand );

    if ( ! numberOperand )
        return nullptr;

    auto aInt = static_cast< int >( mValue );
    auto bInt = static_cast< int >( numberOperand->mValue );

    return runtime::helper::create< runtime::boxes::Number >( static_cast< double >( aInt % bInt ) );
}

runtime::Box * Number::operatorBitwiseNot( void )
{
    int aInt = static_cast< int >( mValue );

    return runtime::helper::create< runtime::boxes::Number >( static_cast< double >( ~ aInt ) );
}

runtime::Box * Number::operatorBitwiseAnd( runtime::Box * operand )
{
    auto numberOperand = dynamic_cast< runtime::boxes::Number * >( operand );

    if ( ! numberOperand )
        return nullptr;

    int aInt = static_cast< int >( mValue );
    int bInt = static_cast< int >( numberOperand->mValue );

    return runtime::helper::create< runtime::boxes::Number >( static_cast< double >( aInt & bInt ) );
}

runtime::Box * Number::operatorBitwiseOr( runtime::Box * operand )
{
    auto numberOperand = dynamic_cast< runtime::boxes::Number * >( operand );

    if ( ! numberOperand )
        return nullptr;

    int aInt = static_cast< int >( mValue );
    int bInt = static_cast< int >( numberOperand->mValue );

    return runtime::helper::create< runtime::boxes::Number >( static_cast< double >( aInt | bInt ) );
}

runtime::Box * Number::operatorBitwiseXOr( runtime::Box * operand )
{
    auto numberOperand = dynamic_cast< runtime::boxes::Number * >( operand );

    if ( ! numberOperand )
        return nullptr;

    int aInt = static_cast< int >( mValue );
    int bInt = static_cast< int >( numberOperand->mValue );

    return runtime::helper::create< runtime::boxes::Number >( static_cast< double >( aInt ^ bInt ) );
}

runtime::Box * Number::operatorLeftShift( runtime::Box * operand )
{
    auto numberOperand = dynamic_cast< runtime::boxes::Number * >( operand );

    if ( ! numberOperand )
        return nullptr;

    int aInt = static_cast< int >( mValue );
    int bInt = static_cast< int >( numberOperand->mValue );

    return runtime::helper::create< runtime::boxes::Number >( static_cast< double >( aInt << bInt ) );
}

runtime::Box * Number::operatorRightShift( runtime::Box * operand )
{
    auto numberOperand = dynamic_cast< runtime::boxes::Number * >( operand );

    if ( ! numberOperand )
        return nullptr;

    int aInt = static_cast< int >( mValue );
    int bInt = static_cast< int >( numberOperand->mValue );

    return runtime::helper::create< runtime::boxes::Number >( static_cast< double >( aInt >> bInt ) );
}

runtime::Box * Number::operatorLesser( runtime::Box * operand )
{
    auto numberOperand = dynamic_cast< runtime::boxes::Number * >( operand );

    if ( ! numberOperand )
        return nullptr;

    return runtime::helper::create< runtime::boxes::Boolean >( mValue < numberOperand->mValue );
}

runtime::Box * Number::operatorGreater( runtime::Box * operand )
{
    auto numberOperand = dynamic_cast< runtime::boxes::Number * >( operand );

    if ( ! numberOperand )
        return nullptr;

    return runtime::helper::create< runtime::boxes::Boolean >( mValue > numberOperand->mValue );
}

runtime::Box * Number::operatorLesserOrEqual( runtime::Box * operand )
{
    auto numberOperand = dynamic_cast< runtime::boxes::Number * >( operand );

    if ( ! numberOperand )
        return nullptr;

    return runtime::helper::create< runtime::boxes::Boolean >( mValue <= numberOperand->mValue );
}

runtime::Box * Number::operatorGreaterOrEqual( runtime::Box * operand )
{
    auto numberOperand = dynamic_cast< runtime::boxes::Number * >( operand );

    if ( ! numberOperand )
        return nullptr;

    return runtime::helper::create< runtime::boxes::Boolean >( mValue >= numberOperand->mValue );
}

runtime::Box * Number::operatorEqual( runtime::Box * operand )
{
    auto numberOperand = dynamic_cast< runtime::boxes::Number * >( operand );

    if ( ! numberOperand )
        return nullptr;

    return runtime::helper::create< runtime::boxes::Boolean >( mValue == numberOperand->mValue );
}

runtime::Box * Number::operatorNotEqual( runtime::Box * operand )
{
    auto numberOperand = dynamic_cast< runtime::boxes::Number * >( operand );

    if ( ! numberOperand )
        return nullptr;

    return runtime::helper::create< runtime::boxes::Boolean >( mValue != numberOperand->mValue );
}
