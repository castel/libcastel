#pragma once

namespace p9
{

    namespace engine
    {

        struct Value
        {

            enum Type {

                DOUBLE

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
