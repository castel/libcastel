#include <cstdlib>

#include <llvm/Support/Dwarf.h>

#include "castel/runtime/helper/LSDA.hh"

using namespace castel;
using runtime::helper::LSDA;
using runtime::helper::LSDACallsite;
using runtime::helper::LSDAAction;

static std::uintptr_t readULEB128( std::uint8_t const ** data )
{
    std::uintptr_t result = 0;
    std::uintptr_t shift = 0;
    std::uint8_t byte;

    std::uint8_t const * p = * data;

    do {

        byte = * p ++;
        result |= ( byte & 0x7f ) << shift;
        shift += 7;

    } while ( byte & 0x80 );

    * data = p;

    return result;
}

static std::uintptr_t readSLEB128( std::uint8_t const ** data )
{
    std::uintptr_t result = 0;
    std::uintptr_t shift = 0;
    std::uint8_t byte;

    std::uint8_t const * p = * data;

    do {
        byte = * p ++;
        result |= ( byte & 0x7f ) << shift;
        shift += 7;
    } while ( byte & 0x80 );

    *data = p;

    if ( ( byte & 0x40 ) && ( shift < ( sizeof ( result ) << 3 ) ) ) {
        result |= ( ~0 << shift );
    }

    return result;
}

static std::uintptr_t readEncodedPointer( std::uint8_t const ** data, uint8_t encoding )
{
    std::uintptr_t result = 0;
    std::uint8_t const * p = * data;

    if ( encoding == llvm::dwarf::DW_EH_PE_omit )
        return result;

    switch ( encoding & 0x0F ) {

        case llvm::dwarf::DW_EH_PE_absptr:
            result = * reinterpret_cast< uintptr_t const * >( p );
            p += sizeof ( std::uintptr_t );
        break ;

        case llvm::dwarf::DW_EH_PE_uleb128:
            result = readULEB128( & p );
        break ;

        case llvm::dwarf::DW_EH_PE_sleb128:
            result = readSLEB128( & p );
        break ;

        case llvm::dwarf::DW_EH_PE_udata2:
            result = * reinterpret_cast< std::uint16_t const * >( p );
            p += sizeof ( std::uint16_t );
        break ;

        case llvm::dwarf::DW_EH_PE_udata4:
            result = * reinterpret_cast< std::uint32_t const * >( p );
            p += sizeof ( std::uint32_t );
        break ;

        case llvm::dwarf::DW_EH_PE_udata8:
            result = * reinterpret_cast< std::uint64_t const * >( p );
            p += sizeof ( std::uint64_t );
        break ;

        case llvm::dwarf::DW_EH_PE_sdata2:
            result = * reinterpret_cast< std::int16_t const * >( p );
            p += sizeof ( std::int16_t );
        break ;

        case llvm::dwarf::DW_EH_PE_sdata4:
            result = * reinterpret_cast< std::int32_t const * >( p );
            p += sizeof ( std::int32_t );
        break ;

        case llvm::dwarf::DW_EH_PE_sdata8:
            result = * reinterpret_cast< std::int64_t const * >( p );
            p += sizeof ( std::int64_t );
        break ;

        default:
            std::abort( );
        break ;

    }

    switch ( encoding & 0x70 ) {

        case llvm::dwarf::DW_EH_PE_absptr:
            // do nothing
        break ;

        case llvm::dwarf::DW_EH_PE_pcrel:
            result += reinterpret_cast< std::uintptr_t >( * data );
        break ;

        default:
            // not supported
            std::abort( );
        break ;

    }

    if ( encoding & llvm::dwarf::DW_EH_PE_indirect ) {
        result = * reinterpret_cast< std::uintptr_t * >( result );
    }

    * data = p;

    return result;
}

LSDA & LSDA::fetch( void )
{
    std::uint8_t lpStartEncoding = * mRaw ++;

    if ( lpStartEncoding != llvm::dwarf::DW_EH_PE_omit ) {
        readEncodedPointer( & mRaw, lpStartEncoding );
    }

    std::uint8_t ttypeEncoding = * mRaw ++;

    if ( ttypeEncoding != llvm::dwarf::DW_EH_PE_omit ) {
        readULEB128( & mRaw );
    }

    mCallsiteEncoding = * mRaw ++;

    if ( true ) {
        std::uintptr_t length = readULEB128( & mRaw );
        mCallsiteTableStart = mRaw;
        mCallsiteTableEnd = mCallsiteTableStart + length;
        mActionTableStart = mCallsiteTableEnd;
    }

    return * this;
}

LSDACallsite & LSDACallsite::fetch( void )
{
    if ( mRaw == mLsda.callsiteTableEnd( ) )
        return * this;

    readEncodedPointer( & mRaw, mLsda.callsiteEncoding( ) );
    readEncodedPointer( & mRaw, mLsda.callsiteEncoding( ) );
    mLandingPad = readEncodedPointer( & mRaw, mLsda.callsiteEncoding( ) );
    mFirstAction = readULEB128( & mRaw );

    if ( mRaw > mLsda.callsiteTableEnd( ) )
        mRaw = mLsda.callsiteTableEnd( );

    return * this;
}

LSDAAction & LSDAAction::fetch( void )
{
    if ( mRaw == nullptr )
        return * this;

    mType = readSLEB128( & mRaw );

    std::uint8_t const * current = mRaw;
    std::uintptr_t next = readSLEB128( & mRaw );
    mNext = next != 0 ? current + next : nullptr;

    return * this;
}
