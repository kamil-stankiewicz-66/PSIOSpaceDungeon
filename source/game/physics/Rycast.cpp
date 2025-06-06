#include "game/physics/Rycast.h"
#include <cmath>

vector<pair<int, int>> Rycast::getLine(Tilemap* tilemap, const Vector2& v1, const Vector2& v2)
{
    vector<pair<int, int>> line;

    //Convert float coordinates to integer grid coordinates
    pair<int, int> v1i = tilemap->real2tilePos(v1.x, v1.y);
    pair<int, int> v2i = tilemap->real2tilePos(v2.x, v2.y);

    int x1 = v1i.first;
    int y1 = v1i.second;
    int x2 = v2i.first;
    int y2 = v2i.second;

    //Bresenhams line algorithm
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);

    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;
    int err = dx - dy;

    while (true)
    {
        line.emplace_back(x1, y1);

        if (x1 == x2 && y1 == y2) {
            break;
        }

        int e2 = 2 * err;

        if (e2 > -dy)
        {
            err -= dy;
            x1 += sx;
        }

        if (e2 < dx)
        {
            err += dx;
            y1 += sy;
        }
    }

    return line;
}

bool Rycast::hit(Tilemap* tilemap, const Vector2& v1, const Vector2& v2)
{
    if (!tilemap) {
        return false;
    }

    for (const auto& [x, y] : getLine(tilemap, v1, v2))
    {
        const Tile* tile = tilemap->getTile(x, y);

        if (!tile) {
            return true;
        }
    }

    return false;
}
