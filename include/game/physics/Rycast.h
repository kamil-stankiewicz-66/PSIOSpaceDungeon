#ifndef RYCAST_H
#define RYCAST_H

#include "game/level/Tilemap.h"
using namespace std;

///
/// \brief Checks if the line intersects an empty tile
///

class Rycast
{
private:
    //Bresenhams algorithm.
    inline static vector<pair<int, int>> getLine(Tilemap* tilemap, const Vector2& v1, const Vector2& v2);

public:
    //Checks if there is an empty tile (tile == nullptr) along the path between (x0, y0) and (x1, y1).
    static bool hit(Tilemap* tilemap, const Vector2& v1, const Vector2& v2);
};

#endif // RYCAST_H
