#ifndef PARAMETER_H
#define PARAMETER_H

struct Parameters
{
    struct PlayerControl
    {
    private:
        static float move_speed;

    public:
        static const float& getMoveSpeed();
    };
};

#endif // PARAMETER_H
