#pragma once

#include <cstdint>

namespace p9
{

    namespace engine
    {

        struct Value
        {

            enum class Type : std::int32_t {

                Double,
                Function,

            };

            Value::Type type;

            union {

                struct {

                    std::int32_t arity;
                    void * function;

                } functionData;

                struct {

                    double value;

                } doubleData;

            };

        };

    }

}
