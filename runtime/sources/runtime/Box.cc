#include "castel/runtime/boxes/Class.hh"
#include "castel/runtime/Box.hh"

using namespace castel;
using runtime::Box;

bool Box::operatorBoolCast( void )
{
    return false;
}

runtime::Box * Box::operatorPositive( void )
{
    return nullptr;
}

runtime::Box * Box::operatorNegative( void )
{
    return nullptr;
}

runtime::Box * Box::operatorPreIncrementation( void )
{
    return nullptr;
}

runtime::Box * Box::operatorPreDecrementation( void )
{
    return nullptr;
}

runtime::Box * Box::operatorPostIncrementation( void )
{
    return nullptr;
}

runtime::Box * Box::operatorPostDecrementation( void )
{
    return nullptr;
}

runtime::Box * Box::operatorAddition( runtime::Box * )
{
    return nullptr;
}

runtime::Box * Box::operatorSubstraction( runtime::Box * )
{
    return nullptr;
}

runtime::Box * Box::operatorMultiplication( runtime::Box * )
{
    return nullptr;
}

runtime::Box * Box::operatorDivision( runtime::Box * )
{
    return nullptr;
}

runtime::Box * Box::operatorModulo( runtime::Box * )
{
    return nullptr;
}

runtime::Box * Box::operatorBitwiseNot( void )
{
    return nullptr;
}

runtime::Box * Box::operatorBitwiseAnd( runtime::Box * )
{
    return nullptr;
}

runtime::Box * Box::operatorBitwiseOr( runtime::Box * )
{
    return nullptr;
}

runtime::Box * Box::operatorBitwiseXOr( runtime::Box * )
{
    return nullptr;
}

runtime::Box * Box::operatorLeftShift( runtime::Box * )
{
    return nullptr;
}

runtime::Box * Box::operatorRightShift( runtime::Box * )
{
    return nullptr;
}

runtime::Box * Box::operatorLesser( runtime::Box * )
{
    return nullptr;
}

runtime::Box * Box::operatorGreater( runtime::Box * )
{
    return nullptr;
}

runtime::Box * Box::operatorLesserOrEqual( runtime::Box * )
{
    return nullptr;
}

runtime::Box * Box::operatorGreaterOrEqual( runtime::Box * )
{
    return nullptr;
}

runtime::Box * Box::operatorEqual( runtime::Box * )
{
    return nullptr;
}

runtime::Box * Box::operatorNotEqual( runtime::Box * )
{
    return nullptr;
}

runtime::Box * Box::operatorSubscript( unsigned int, runtime::Box ** )
{
    return nullptr;
}

runtime::Box * Box::operatorCall( unsigned int, runtime::Box ** )
{
    return nullptr;
}

runtime::Box * Box::operatorNew( unsigned int, runtime::Box ** )
{
    return nullptr;
}

runtime::Box * Box::operatorRequire( unsigned int, runtime::Box ** )
{
    return nullptr;
}
