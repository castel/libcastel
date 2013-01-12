#include "castel/runtime/boxes/Bool.hh"
#include "castel/runtime/boxes/Number.hh"
#include "castel/runtime/helper/create.hh"
#include "castel/runtime/Box.hh"

using namespace castel;
using runtime::boxes::Number;

bool Number::operatorBool( void )
{
    return mValue != 0;
}

runtime::Box * Number::operatorNumericPlus( void )
{
    return runtime::helper::create< runtime::boxes::Number >( + mValue );
}

runtime::Box * Number::operatorNumericMinus( void )
{
    return runtime::helper::create< runtime::boxes::Number >( - mValue );
}

runtime::Box * Number::operatorNumericPreIncrementation( void )
{
    mValue += 1;

    return this;
}

runtime::Box * Number::operatorNumericPreDecrementation( void )
{
    mValue -= 1;

    return this;
}

runtime::Box * Number::operatorNumericPostIncrementation( void )
{
    return runtime::helper::create< runtime::boxes::Number >( mValue ++ );
}

runtime::Box * Number::operatorNumericPostDecrementation( void )
{
    return runtime::helper::create< runtime::boxes::Number >( mValue -- );
}

runtime::Box * Number::operatorNumericAddition( runtime::Box * operand )
{
    auto numberOperand = dynamic_cast< runtime::boxes::Number * >( operand );

    if ( ! numberOperand )
        return nullptr;

    return runtime::helper::create< runtime::boxes::Number >( mValue + numberOperand->mValue );
}

runtime::Box * Number::operatorNumericSubstraction( runtime::Box * operand )
{
    auto numberOperand = dynamic_cast< runtime::boxes::Number * >( operand );

    if ( ! numberOperand )
        return nullptr;

    return runtime::helper::create< runtime::boxes::Number >( mValue - numberOperand->mValue );
}

runtime::Box * Number::operatorNumericMultiplication( runtime::Box * operand )
{
    auto numberOperand = dynamic_cast< runtime::boxes::Number * >( operand );

    if ( ! numberOperand )
        return nullptr;

    return runtime::helper::create< runtime::boxes::Number >( mValue * numberOperand->mValue );
}

runtime::Box * Number::operatorNumericDivision( runtime::Box * operand )
{
    auto numberOperand = dynamic_cast< runtime::boxes::Number * >( operand );

    if ( ! numberOperand )
        return nullptr;

    return runtime::helper::create< runtime::boxes::Number >( mValue / numberOperand->mValue );
}

runtime::Box * Number::operatorNumericModulo( runtime::Box * operand )
{
    auto numberOperand = dynamic_cast< runtime::boxes::Number * >( operand );

    if ( ! numberOperand )
        return nullptr;

    auto aInt = static_cast< int >( mValue );
    auto bInt = static_cast< int >( numberOperand->mValue );

    return runtime::helper::create< runtime::boxes::Number >( static_cast< double >( aInt % bInt ) );
}

runtime::Box * Number::operatorNumericAssignmentAddition( runtime::Box * operand )
{
    auto numberOperand = dynamic_cast< runtime::boxes::Number * >( operand );

    if ( ! numberOperand )
        return nullptr;

    mValue += numberOperand->mValue;
    return this;
}

runtime::Box * Number::operatorNumericAssignmentSubstraction( runtime::Box * operand )
{
    auto numberOperand = dynamic_cast< runtime::boxes::Number * >( operand );

    if ( ! numberOperand )
        return nullptr;

    mValue -= numberOperand->mValue;
    return this;
}

runtime::Box * Number::operatorNumericAssignmentMultiplication( runtime::Box * operand )
{
    auto numberOperand = dynamic_cast< runtime::boxes::Number * >( operand );

    if ( ! numberOperand )
        return nullptr;

    mValue *= numberOperand->mValue;
    return this;
}

runtime::Box * Number::operatorNumericAssignmentDivision( runtime::Box * operand )
{
    auto numberOperand = dynamic_cast< runtime::boxes::Number * >( operand );

    if ( ! numberOperand )
        return nullptr;

    mValue /= numberOperand->mValue;
    return this;
}

runtime::Box * Number::operatorNumericAssignmentModulo( runtime::Box * operand )
{
    auto numberOperand = dynamic_cast< runtime::boxes::Number * >( operand );

    if ( ! numberOperand )
        return nullptr;

    auto aInt = static_cast< int >( mValue );
    auto bInt = static_cast< int >( numberOperand->mValue );

    mValue = static_cast< double >( aInt % bInt );
    return this;
}

runtime::Box * Number::operatorBinaryNot( void )
{
    int aInt = static_cast< int >( mValue );

    return runtime::helper::create< runtime::boxes::Number >( static_cast< double >( ~ aInt ) );
}

runtime::Box * Number::operatorBinaryAnd( runtime::Box * operand )
{
    auto numberOperand = dynamic_cast< runtime::boxes::Number * >( operand );

    if ( ! numberOperand )
        return nullptr;

    int aInt = static_cast< int >( mValue );
    int bInt = static_cast< int >( numberOperand->mValue );

    return runtime::helper::create< runtime::boxes::Number >( static_cast< double >( aInt & bInt ) );
}

runtime::Box * Number::operatorBinaryOr( runtime::Box * operand )
{
    auto numberOperand = dynamic_cast< runtime::boxes::Number * >( operand );

    if ( ! numberOperand )
        return nullptr;

    int aInt = static_cast< int >( mValue );
    int bInt = static_cast< int >( numberOperand->mValue );

    return runtime::helper::create< runtime::boxes::Number >( static_cast< double >( aInt | bInt ) );
}

runtime::Box * Number::operatorBinaryXOr( runtime::Box * operand )
{
    auto numberOperand = dynamic_cast< runtime::boxes::Number * >( operand );

    if ( ! numberOperand )
        return nullptr;

    int aInt = static_cast< int >( mValue );
    int bInt = static_cast< int >( numberOperand->mValue );

    return runtime::helper::create< runtime::boxes::Number >( static_cast< double >( aInt ^ bInt ) );
}

runtime::Box * Number::operatorBinaryLShift( runtime::Box * operand )
{
    auto numberOperand = dynamic_cast< runtime::boxes::Number * >( operand );

    if ( ! numberOperand )
        return nullptr;

    int aInt = static_cast< int >( mValue );
    int bInt = static_cast< int >( numberOperand->mValue );

    return runtime::helper::create< runtime::boxes::Number >( static_cast< double >( aInt << bInt ) );
}

runtime::Box * Number::operatorBinaryRShift( runtime::Box * operand )
{
    auto numberOperand = dynamic_cast< runtime::boxes::Number * >( operand );

    if ( ! numberOperand )
        return nullptr;

    int aInt = static_cast< int >( mValue );
    int bInt = static_cast< int >( numberOperand->mValue );

    return runtime::helper::create< runtime::boxes::Number >( static_cast< double >( aInt >> bInt ) );
}

runtime::Box * Number::operatorBinaryAssignmentAnd( runtime::Box * operand )
{
    auto numberOperand = dynamic_cast< runtime::boxes::Number * >( operand );

    if ( ! numberOperand )
        return nullptr;

    int aInt = static_cast< int >( mValue );
    int bInt = static_cast< int >( numberOperand->mValue );

    mValue = static_cast< double >( aInt & bInt );
    return this;
}

runtime::Box * Number::operatorBinaryAssignmentOr( runtime::Box * operand )
{
    auto numberOperand = dynamic_cast< runtime::boxes::Number * >( operand );

    if ( ! numberOperand )
        return nullptr;

    int aInt = static_cast< int >( mValue );
    int bInt = static_cast< int >( numberOperand->mValue );

    mValue = static_cast< double >( aInt | bInt );
    return this;
}

runtime::Box * Number::operatorBinaryAssignmentXOr( runtime::Box * operand )
{
    auto numberOperand = dynamic_cast< runtime::boxes::Number * >( operand );

    if ( ! numberOperand )
        return nullptr;

    int aInt = static_cast< int >( mValue );
    int bInt = static_cast< int >( numberOperand->mValue );

    mValue = static_cast< double >( aInt ^ bInt );
    return this;
}

runtime::Box * Number::operatorBinaryAssignmentLShift( runtime::Box * operand )
{
    auto numberOperand = dynamic_cast< runtime::boxes::Number * >( operand );

    if ( ! numberOperand )
        return nullptr;

    int aInt = static_cast< int >( mValue );
    int bInt = static_cast< int >( numberOperand->mValue );

    mValue = static_cast< double >( aInt << bInt );
    return this;
}

runtime::Box * Number::operatorBinaryAssignmentRShift( runtime::Box * operand )
{
    auto numberOperand = dynamic_cast< runtime::boxes::Number * >( operand );

    if ( ! numberOperand )
        return nullptr;

    int aInt = static_cast< int >( mValue );
    int bInt = static_cast< int >( numberOperand->mValue );

    mValue = static_cast< double >( aInt >> bInt );
    return this;
}

runtime::Box * Number::operatorComparisonLesser( runtime::Box * operand )
{
    auto numberOperand = dynamic_cast< runtime::boxes::Number * >( operand );

    if ( ! numberOperand )
        return nullptr;

    return runtime::helper::create< runtime::boxes::Bool >( mValue < numberOperand->mValue );
}

runtime::Box * Number::operatorComparisonGreater( runtime::Box * operand )
{
    auto numberOperand = dynamic_cast< runtime::boxes::Number * >( operand );

    if ( ! numberOperand )
        return nullptr;

    return runtime::helper::create< runtime::boxes::Bool >( mValue > numberOperand->mValue );
}

runtime::Box * Number::operatorComparisonLesserOrEqual( runtime::Box * operand )
{
    auto numberOperand = dynamic_cast< runtime::boxes::Number * >( operand );

    if ( ! numberOperand )
        return nullptr;

    return runtime::helper::create< runtime::boxes::Bool >( mValue <= numberOperand->mValue );
}

runtime::Box * Number::operatorComparisonGreaterOrEqual( runtime::Box * operand )
{
    auto numberOperand = dynamic_cast< runtime::boxes::Number * >( operand );

    if ( ! numberOperand )
        return nullptr;

    return runtime::helper::create< runtime::boxes::Bool >( mValue >= numberOperand->mValue );
}

runtime::Box * Number::operatorComparisonEqual( runtime::Box * operand )
{
    auto numberOperand = dynamic_cast< runtime::boxes::Number * >( operand );

    if ( ! numberOperand )
        return nullptr;

    return runtime::helper::create< runtime::boxes::Bool >( mValue == numberOperand->mValue );
}

runtime::Box * Number::operatorComparisonNotEqual( runtime::Box * operand )
{
    auto numberOperand = dynamic_cast< runtime::boxes::Number * >( operand );

    if ( ! numberOperand )
        return nullptr;

    return runtime::helper::create< runtime::boxes::Bool >( mValue != numberOperand->mValue );
}
