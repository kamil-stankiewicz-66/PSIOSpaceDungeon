#ifndef BASICBUTTONS_H
#define BASICBUTTONS_H

#include "engine/object/Button.h"

///
/// \brief A standard rectangular button for the menu.
///

class MenuButton : public Button
{
    TextObject* textObj;

protected:
    virtual void onAwake() override;

public:
    void setText(const string&);
};

#endif // BASICBUTTONS_H
