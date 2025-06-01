#ifndef BASICBUTTONS_H
#define BASICBUTTONS_H

#include "engine/object/Button.h"

///
/// \brief A standard rectangular button for the menu.
///

class MenuButton : public Button
{
protected:
    virtual void onAwake() override;
};

#endif // BASICBUTTONS_H
