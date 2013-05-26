#include <cstdint>
#include <cstdlib>

#include <unwind.h>

#include "castel/runtime/helper/LSDA.hh"
#include "castel/runtime/interface.hh"

using namespace castel;

static std::uint64_t const Castel_exceptionClass = ( ( ( ( ( ( ( (
    ( std::uint64_t ) 'A' ) << 8 |
    ( std::uint64_t ) 'R' ) << 8 |
    ( std::uint64_t ) 'C' ) << 8 |
    ( std::uint64_t ) 'A' ) << 8 |
    ( std::uint64_t ) 'C' ) << 8 |
    ( std::uint64_t ) 'S' ) << 8 |
    ( std::uint64_t ) 'T' ) << 8 |
    ( std::uint64_t ) 'L' );

static void Castel_exceptionCleanup( _Unwind_Reason_Code code, _Unwind_Exception * exception )
{
    delete exception;
}

void Castel_throw( runtime::Box * exception )
{
    _Unwind_Exception * unwindHeader = static_cast< _Unwind_Exception * >( std::malloc( sizeof( _Unwind_Exception ) ) );
    unwindHeader->exception_class = Castel_exceptionClass;
    unwindHeader->exception_cleanup = Castel_exceptionCleanup;

    _Unwind_RaiseException( unwindHeader );
    std::terminate( );
}

_Unwind_Reason_Code Castel_personality( int version, _Unwind_Action request, std::uint64_t exceptionClass, _Unwind_Exception * exception, _Unwind_Context * context )
{
    if ( version != 1 )
        return _URC_FATAL_PHASE1_ERROR;

    std::uint64_t throwIP = _Unwind_GetIP( context ) - 1;
    std::uint64_t functionStart = _Unwind_GetRegionStart( context );

    std::uint8_t const * rawLsda = reinterpret_cast< std::uint8_t const * >( _Unwind_GetLanguageSpecificData( context ) );

    runtime::helper::LSDA lsda( rawLsda );

    for ( auto callsite : lsda ) {

        for ( auto action : callsite ) {

            // "The Castel exception handler always gets his exception"
            if ( false ) continue ;

            if ( request & _UA_SEARCH_PHASE )
                return _URC_HANDLER_FOUND;

            _Unwind_SetGR( context, __builtin_eh_return_data_regno( 0 ), reinterpret_cast< std::uintptr_t >( exception ) );
            _Unwind_SetGR( context, __builtin_eh_return_data_regno( 1 ), action.type( ) );
            _Unwind_SetIP( context, functionStart + callsite.landingPad( ) );

            return _URC_INSTALL_CONTEXT;

        }

    }

    return _URC_CONTINUE_UNWIND;
}
