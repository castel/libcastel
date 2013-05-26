#pragma once

#include <cstdint>

namespace castel
{

    namespace runtime
    {

        namespace helper
        {

            class LSDAAction;

            class LSDACallsite;

            class LSDA;

        }

    }

}
#include <iostream>
namespace castel
{

    namespace runtime
    {

        namespace helper
        {

            class LSDAAction
            {

            public:

                inline LSDAAction( LSDACallsite const & lsdaCallsite, std::uint8_t const * raw );

            public:

                inline bool operator==( LSDAAction const & other ) const;

                inline bool operator!=( LSDAAction const & other ) const;

                inline LSDAAction & operator++( void );

            public:

                inline std::uint64_t type( void ) const;

            private:

                LSDAAction & fetch( void );

            private:

                LSDACallsite const & mLsdaCallsite;

                std::uint8_t const * mRaw;

                std::uint8_t const * mNext;

            private:

                std::uint64_t mType;

            };

            class LSDACallsite
            {

            public:

                using const_iterator = LSDAAction;

            public:

                inline LSDACallsite( LSDA const & lsda, std::uint8_t const * raw );

            public:

                inline LSDACallsite::const_iterator begin( void ) const;

                inline LSDACallsite::const_iterator end( void ) const;

            public:

                inline bool operator==( LSDACallsite const & other ) const;

                inline bool operator!=( LSDACallsite const & other ) const;

                inline LSDACallsite & operator++( void );

            public:

                inline std::uint64_t landingPad( void ) const;

            private:

                LSDACallsite & fetch( void );

            private:

                LSDA const & mLsda;

                std::uint8_t const * mRaw;

                std::uint64_t mFirstAction;

            private:

                std::uint64_t mLandingPad;

            };

            class LSDA
            {

            public:

                using const_iterator = LSDACallsite;

            public:

                inline LSDA( std::uint8_t const * raw );

            public:

                inline LSDA::const_iterator begin( void ) const;

                inline LSDA::const_iterator end( void ) const;

            public:

                inline std::uint8_t callsiteEncoding( void ) const;

                inline std::uint8_t const * callsiteTableStart( void ) const;

                inline std::uint8_t const * callsiteTableEnd( void ) const;

            public:

                inline std::uint8_t const * actionTableStart( void ) const;

            private:

                LSDA & fetch( void );

            private:

                std::uint8_t const * mRaw;

            private:

                std::uint8_t mCallsiteEncoding;

                std::uint8_t const * mCallsiteTableStart;

                std::uint8_t const * mCallsiteTableEnd;

            private:

                std::uint8_t const * mActionTableStart;

            };

        }

    }

}

namespace castel
{

    namespace runtime
    {

        namespace helper
        {

            LSDAAction::LSDAAction( LSDACallsite const & lsdaCallsite, std::uint8_t const * raw )
                : mLsdaCallsite( lsdaCallsite )
                , mRaw( raw )
            {
                this->fetch( );
            }

            bool LSDAAction::operator==( LSDAAction const & other ) const
            {
                return mRaw == other.mRaw;
            }

            bool LSDAAction::operator!=( LSDAAction const & other ) const
            {
                return mRaw != other.mRaw;
            }

            LSDAAction & LSDAAction::operator++( void )
            {
                mRaw = mNext;

                return this->fetch( );
            }

            std::uint64_t LSDAAction::type( void ) const
            {
                return mType;
            }

            LSDACallsite::LSDACallsite( LSDA const & lsda, std::uint8_t const * raw )
                : mLsda( lsda )
                , mRaw( raw )
            {
                this->fetch( );
            }

            LSDACallsite::const_iterator LSDACallsite::begin( void ) const
            {
                if ( mFirstAction == 0 )
                    return this->end( );

                return LSDACallsite::const_iterator( * this, mLsda.actionTableStart( ) + mFirstAction - 1 );
            }

            LSDACallsite::const_iterator LSDACallsite::end( void ) const
            {
                return LSDACallsite::const_iterator( * this, nullptr );
            }

            bool LSDACallsite::operator==( LSDACallsite const & other ) const
            {
                return mRaw == other.mRaw;
            }

            bool LSDACallsite::operator!=( LSDACallsite const & other ) const
            {
                return mRaw != other.mRaw;
            }

            LSDACallsite & LSDACallsite::operator++( void )
            {
                return this->fetch( );
            }

            std::uint64_t LSDACallsite::landingPad( void ) const
            {
                return mLandingPad;
            }

            LSDA::LSDA( std::uint8_t const * raw )
                : mRaw( raw )
            {
                this->fetch( );
            }

            LSDA::const_iterator LSDA::begin( void ) const
            {
                return LSDA::const_iterator( * this, mCallsiteTableStart );
            }

            LSDA::const_iterator LSDA::end( void ) const
            {
                return LSDA::const_iterator( * this, mCallsiteTableEnd );
            }

            std::uint8_t LSDA::callsiteEncoding( void ) const
            {
                return mCallsiteEncoding;
            }

            std::uint8_t const * LSDA::callsiteTableStart( void ) const
            {
                return mCallsiteTableStart;
            }

            std::uint8_t const * LSDA::callsiteTableEnd( void ) const
            {
                return mCallsiteTableEnd;
            }

            std::uint8_t const * LSDA::actionTableStart( void ) const
            {
                return mActionTableStart;
            }

        }

    }

}
