#pragma once

#include <cstdint>

namespace castel
{

    namespace engine
    {

        struct Box
        {

            enum class Type : std::int32_t {

                Double,
                Function,

            };

            engine::Box::Type type;

            union {

                struct {

                    std::int32_t arity;
                    void * parentEnvironment;
                    void * function;

                } functionData;

                struct {

                    double value;

                } doubleData;

            };

        };

    }

}
