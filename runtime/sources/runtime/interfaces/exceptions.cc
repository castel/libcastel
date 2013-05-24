#include <cstdint>
#include <cstdlib>
#include <unwind.h>

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

_Unwind_Reason_Code Castel_personality( int version, _Unwind_Action actions, std::uint64_t exceptionClass, _Unwind_Exception * exception, _Unwind_Context * context )
{
    if ( version != 1 )
        return _URC_FATAL_PHASE1_ERROR;

    if ( actions & _UA_SEARCH_PHASE ) {
        return _URC_HANDLER_FOUND;
    }

    if ( actions & _UA_CLEANUP_PHASE ) {
        return _URC_INSTALL_CONTEXT;
    }

    return _URC_FATAL_PHASE1_ERROR;
}
