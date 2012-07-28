#pragma once

#include <cstdint>

namespace p9
{

    namespace engine
    {

        struct Value
        {

            enum class Type : std::int32_t {

                Double

            };

            Value::Type type;

            union {

                struct {

                    double value;

                } doubleData;

            };

        };

    }

}
