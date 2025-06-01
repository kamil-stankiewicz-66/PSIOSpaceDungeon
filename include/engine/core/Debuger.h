#ifndef DEBUGER_H
#define DEBUGER_H

#include <iostream>

class VDebuger {
public:

    ///
    /// \brief Method that prints the given sequence of variables to the console.
    /// \tparam Args Types compatible with std::ostream.
    /// \param args Variables/words.
    ///

    template<typename... Args>
    static void print(Args... args)
    {
#ifndef NDEBUG

        logHelper(args...);

#endif
    }


private:
    template <typename T, typename... Args>
    static void logHelper(T first, Args... rest)
    {
        try
        {
            std::cout << first << " ";
        }
        catch (...)
        {
            std::cout << "%DEBUG_ERROR%" << " ";
        }

        logHelper(rest...);
    }

    static void logHelper() {
        std::cout << std::endl;
    }
};

#endif // DEBUGER_H
