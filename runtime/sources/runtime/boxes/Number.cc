#include "castel/runtime/boxes/Number.hh"

using namespace castel;
using runtime::boxes::Number;

bool Number::operatorBool( runtime::Context * )
{
    return mValue != 0;
}

runtime::Box * Number::operatorNumericPlus( runtime::Context * context )
{
    return context->create< runtime::boxes::Number >( + mValue );
}

runtime::Box * Number::operatorNumericMinus( runtime::Context * context )
{
    return context->create< runtime::boxes::Number >( - mValue );
}

runtime::Box * Number::operatorNumericPreIncrementation( runtime::Context * )
{
    mValue += 1;

    return this;
}

runtime::Box * Number::operatorNumericPreDecrementation( runtime::Context * )
{
    mValue -= 1;

    return this;
}

runtime::Box * Number::operatorNumericPostIncrementation( runtime::Context * context )
{
    return context->create< runtime::boxes::Number >( mValue ++ );
}

runtime::Box * Number::operatorNumericPostDecrementation( runtime::Context * context )
{
    return context->create< runtime::boxes::Number >( mValue -- );
}

runtime::Box * Number::operatorNumericAddition( runtime::Context * context, runtime::Box * operand )
{
    auto numberOperand = dynamic_cast< runtime::boxes::Number * >( operand );

    if ( ! numberOperand )
        return nullptr;

    return context->create< runtime::boxes::Number >( mValue + numberOperand->mValue );
}

runtime::Box * Number::operatorNumericSubstraction( runtime::Context * context, runtime::Box * operand )
{
    auto numberOperand = dynamic_cast< runtime::boxes::Number * >( operand );

    if ( ! numberOperand )
        return nullptr;

    return context->create< runtime::boxes::Number >( mValue - numberOperand->mValue );
}

runtime::Box * Number::operatorNumericMultiplication( runtime::Context * context, runtime::Box * operand )
{
    auto numberOperand = dynamic_cast< runtime::boxes::Number * >( operand );

    if ( ! numberOperand )
        return nullptr;

    return context->create< runtime::boxes::Number >( mValue * numberOperand->mValue );
}

runtime::Box * Number::operatorNumericDivision( runtime::Context * context, runtime::Box * operand )
{
    auto numberOperand = dynamic_cast< runtime::boxes::Number * >( operand );

    if ( ! numberOperand )
        return nullptr;

    return context->create< runtime::boxes::Number >( mValue / numberOperand->mValue );
}

runtime::Box * Number::operatorNumericModulo( runtime::Context * context, runtime::Box * operand )
{
    auto numberOperand = dynamic_cast< runtime::boxes::Number * >( operand );

    if ( ! numberOperand )
        return nullptr;

    auto aInt = static_cast< int >( mValue );
    auto bInt = static_cast< int >( numberOperand->mValue );

    return context->create< runtime::boxes::Number >( static_cast< double >( aInt % bInt ) );
}

runtime::Box * Number::operatorNumericAssignmentAddition( runtime::Context *, runtime::Box * operand )
{
    auto numberOperand = dynamic_cast< runtime::boxes::Number * >( operand );

    if ( ! numberOperand )
        return nullptr;

    mValue += numberOperand->mValue;
    return this;
}

runtime::Box * Number::operatorNumericAssignmentSubstraction( runtime::Context *, runtime::Box * operand )
{
    auto numberOperand = dynamic_cast< runtime::boxes::Number * >( operand );

    if ( ! numberOperand )
        return nullptr;

    mValue -= numberOperand->mValue;
    return this;
}

runtime::Box * Number::operatorNumericAssignmentMultiplication( runtime::Context *, runtime::Box * operand )
{
    auto numberOperand = dynamic_cast< runtime::boxes::Number * >( operand );

    if ( ! numberOperand )
        return nullptr;

    mValue *= numberOperand->mValue;
    return this;
}

runtime::Box * Number::operatorNumericAssignmentDivision( runtime::Context *, runtime::Box * operand )
{
    auto numberOperand = dynamic_cast< runtime::boxes::Number * >( operand );

    if ( ! numberOperand )
        return nullptr;

    mValue /= numberOperand->mValue;
    return this;
}

runtime::Box * Number::operatorNumericAssignmentModulo( runtime::Context *, runtime::Box * operand )
{
    auto numberOperand = dynamic_cast< runtime::boxes::Number * >( operand );

    if ( ! numberOperand )
        return nullptr;

    auto aInt = static_cast< int >( mValue );
    auto bInt = static_cast< int >( numberOperand->mValue );

    mValue = static_cast< double >( aInt % bInt );
    return this;
}

runtime::Box * Number::operatorBinaryNot( runtime::Context * context )
{
    int aInt = static_cast< int >( mValue );

    return context->create< runtime::boxes::Number >( static_cast< double >( ~ aInt ) );
}

runtime::Box * Number::operatorBinaryAnd( runtime::Context * context, runtime::Box * operand )
{
    auto numberOperand = dynamic_cast< runtime::boxes::Number * >( operand );

    if ( ! numberOperand )
        return nullptr;

    int aInt = static_cast< int >( mValue );
    int bInt = static_cast< int >( numberOperand->mValue );

    return context->create< runtime::boxes::Number >( static_cast< double >( aInt & bInt ) );
}

runtime::Box * Number::operatorBinaryOr( runtime::Context * context, runtime::Box * operand )
{
    auto numberOperand = dynamic_cast< runtime::boxes::Number * >( operand );

    if ( ! numberOperand )
        return nullptr;

    int aInt = static_cast< int >( mValue );
    int bInt = static_cast< int >( numberOperand->mValue );

    return context->create< runtime::boxes::Number >( static_cast< double >( aInt | bInt ) );
}

runtime::Box * Number::operatorBinaryXOr( runtime::Context * context, runtime::Box * operand )
{
    auto numberOperand = dynamic_cast< runtime::boxes::Number * >( operand );

    if ( ! numberOperand )
        return nullptr;

    int aInt = static_cast< int >( mValue );
    int bInt = static_cast< int >( numberOperand->mValue );

    return context->create< runtime::boxes::Number >( static_cast< double >( aInt ^ bInt ) );
}

runtime::Box * Number::operatorBinaryLShift( runtime::Context * context, runtime::Box * operand )
{
    auto numberOperand = dynamic_cast< runtime::boxes::Number * >( operand );

    if ( ! numberOperand )
        return nullptr;

    int aInt = static_cast< int >( mValue );
    int bInt = static_cast< int >( numberOperand->mValue );

    return context->create< runtime::boxes::Number >( static_cast< double >( aInt << bInt ) );
}

runtime::Box * Number::operatorBinaryRShift( runtime::Context * context, runtime::Box * operand )
{
    auto numberOperand = dynamic_cast< runtime::boxes::Number * >( operand );

    if ( ! numberOperand )
        return nullptr;

    int aInt = static_cast< int >( mValue );
    int bInt = static_cast< int >( numberOperand->mValue );

    return context->create< runtime::boxes::Number >( static_cast< double >( aInt >> bInt ) );
}

runtime::Box * Number::operatorBinaryAssignmentAnd( runtime::Context * context, runtime::Box * operand )
{
    auto numberOperand = dynamic_cast< runtime::boxes::Number * >( operand );

    if ( ! numberOperand )
        return nullptr;

    int aInt = static_cast< int >( mValue );
    int bInt = static_cast< int >( numberOperand->mValue );

    mValue = static_cast< double >( aInt & bInt );
    return this;
}

runtime::Box * Number::operatorBinaryAssignmentOr( runtime::Context * context, runtime::Box * operand )
{
    auto numberOperand = dynamic_cast< runtime::boxes::Number * >( operand );

    if ( ! numberOperand )
        return nullptr;

    int aInt = static_cast< int >( mValue );
    int bInt = static_cast< int >( numberOperand->mValue );

    mValue = static_cast< double >( aInt | bInt );
    return this;
}

runtime::Box * Number::operatorBinaryAssignmentXOr( runtime::Context * context, runtime::Box * operand )
{
    auto numberOperand = dynamic_cast< runtime::boxes::Number * >( operand );

    if ( ! numberOperand )
        return nullptr;

    int aInt = static_cast< int >( mValue );
    int bInt = static_cast< int >( numberOperand->mValue );

    mValue = static_cast< double >( aInt ^ bInt );
    return this;
}

runtime::Box * Number::operatorBinaryAssignmentLShift( runtime::Context * context, runtime::Box * operand )
{
    auto numberOperand = dynamic_cast< runtime::boxes::Number * >( operand );

    if ( ! numberOperand )
        return nullptr;

    int aInt = static_cast< int >( mValue );
    int bInt = static_cast< int >( numberOperand->mValue );

    mValue = static_cast< double >( aInt << bInt );
    return this;
}

runtime::Box * Number::operatorBinaryAssignmentRShift( runtime::Context * context, runtime::Box * operand )
{
    auto numberOperand = dynamic_cast< runtime::boxes::Number * >( operand );

    if ( ! numberOperand )
        return nullptr;

    int aInt = static_cast< int >( mValue );
    int bInt = static_cast< int >( numberOperand->mValue );

    mValue = static_cast< double >( aInt >> bInt );
    return this;
}

runtime::Box * Number::operatorComparisonLesser( runtime::Context * context, runtime::Box * operand )
{
    auto numberOperand = dynamic_cast< runtime::boxes::Number * >( operand );

    if ( ! numberOperand )
        return nullptr;

    return context->create< runtime::boxes::Number >( mValue < numberOperand->mValue );
}

runtime::Box * Number::operatorComparisonGreater( runtime::Context * context, runtime::Box * operand )
{
    auto numberOperand = dynamic_cast< runtime::boxes::Number * >( operand );

    if ( ! numberOperand )
        return nullptr;

    return context->create< runtime::boxes::Number >( mValue > numberOperand->mValue );
}

runtime::Box * Number::operatorComparisonLesserOrEqual( runtime::Context * context, runtime::Box * operand )
{
    auto numberOperand = dynamic_cast< runtime::boxes::Number * >( operand );

    if ( ! numberOperand )
        return nullptr;

    return context->create< runtime::boxes::Number >( mValue <= numberOperand->mValue );
}

runtime::Box * Number::operatorComparisonGreaterOrEqual( runtime::Context * context, runtime::Box * operand )
{
    auto numberOperand = dynamic_cast< runtime::boxes::Number * >( operand );

    if ( ! numberOperand )
        return nullptr;

    return context->create< runtime::boxes::Number >( mValue >= numberOperand->mValue );
}

runtime::Box * Number::operatorComparisonEqual( runtime::Context * context, runtime::Box * operand )
{
    auto numberOperand = dynamic_cast< runtime::boxes::Number * >( operand );

    if ( ! numberOperand )
        return nullptr;

    return context->create< runtime::boxes::Number >( mValue == numberOperand->mValue );
}

runtime::Box * Number::operatorComparisonNotEqual( runtime::Context * context, runtime::Box * operand )
{
    auto numberOperand = dynamic_cast< runtime::boxes::Number * >( operand );

    if ( ! numberOperand )
        return nullptr;

    return context->create< runtime::boxes::Number >( mValue != numberOperand->mValue );
}
