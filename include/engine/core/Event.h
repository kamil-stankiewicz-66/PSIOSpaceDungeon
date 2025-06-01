#ifndef EVENT_H
#define EVENT_H

#include <functional>
using namespace std;

///
/// \brief Class representing an event.
///

class VEvent
{
private:
    vector<function<void()>> listeners;

public:

    ///
    /// \brief Adds a function that will be executed when the invoke() method is called.
    /// \param newListener
    ///

    void addListener(const std::function<void()>& newListener);


    ///
    /// \brief Clears the listeners collection.
    ///

    void dispose();


    ///
    /// \brief Executes all functions in the listeners collection.
    ///

    void invoke();
};

#endif // EVENT_H
