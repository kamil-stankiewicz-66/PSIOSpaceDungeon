#ifndef SLIDER_H
#define SLIDER_H

#include "engine/object/Object.h"

class Slider : public Object
{

private:
    float valueMax;
    float value;
    float offset;

    SpriteObject* background = nullptr;
    SpriteObject* slider = nullptr;

    //engine
    virtual void onAwake() override;

    //update
    void refresh();

public:

    ///
    /// \brief init
    /// \param rect True - init as UI Object, False - init as GameObject
    ///

    void init(bool rect);


    //setter
    void setValue(const float&);
    void setValueMax(const float&);
    void setFillColor(const sf::Color&);
    void setBackgroundColor(const sf::Color&);
    void scaleWidth(const float&);
    void scaleHeight(const float&);

    //getter
    const float& getValue() const;
    const float& getValueMax() const;
    const float getWidth() const;
    const float getHeight() const;
};

#endif // SLIDER_H
