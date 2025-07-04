#ifndef SERIALIZER_H
#define SERIALIZER_H
#include "engine/core/Debuger.h"
#include <fstream>
#include <type_traits>
#include <string>

class Serializer {
public:
    template<typename T>
    static typename std::enable_if<std::is_trivially_copyable<T>::value, void>::type
    serializeToFile(const T& obj, const std::string& filename)
    {
        std::ofstream out(filename, std::ios::binary);

        if (out)
        {
            out.write(reinterpret_cast<const char*>(&obj), sizeof(obj));
        }
        else
        {
            VDebuger::print("<ERROR> SERIALIZER :: Failed to open file for writing.");
        }
    }

    template<typename T>
    static typename std::enable_if<std::is_trivially_copyable<T>::value, void>::type
    deserializeFromFile(T& obj, const std::string& filename)
    {
        std::ifstream in(filename, std::ios::binary);

        if (in)
        {
            in.read(reinterpret_cast<char*>(&obj), sizeof(obj));
        }
    }
};
#endif // SERIALIZER_H
