#pragma once

namespace p9
{

    namespace engine
    {

        struct Value
        {

            enum Type {

                DoubleTy

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
