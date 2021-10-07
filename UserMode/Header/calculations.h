#pragma once

#include "Player.h"

float getDistance(const Player p1, const Player p2)
{
    return sqrt(
        pow((p2.get_Position().x - p1.get_Position().x), 2) +
        pow((p2.get_Position().y - p1.get_Position().y), 2) +
        pow((p2.get_Position().z - p1.get_Position().z), 2)
    );
}

float getAngleX(const Player p1, const Player p2)
{
    float deltaX = p2.get_Position().x - p1.get_Position().x;
    float deltaY = p1.get_Position().y - p2.get_Position().y;

    if (p2.get_Position().x > p1.get_Position().x && p2.get_Position().y < p1.get_Position().y) {
        return atanf(deltaX / deltaY) * 180.0f / (3.14159);
    }
    else if (p2.get_Position().x > p1.get_Position().x && p2.get_Position().y > p1.get_Position().y) {
        return atanf(deltaX / deltaY) * 180.0f / (3.14159) + 180.0f;
    }
    else if (p2.get_Position().x < p1.get_Position().x && p2.get_Position().y > p1.get_Position().y) {
        return atanf(deltaX / deltaY) * 180.0f / (3.14159) - 180.0f;
    }
    else {
        return atanf(deltaX / deltaY) * 180.0f / (3.14159) + 360.0f;
    }

    return 0;
}

float getAngleY(const Player p1, const Player p2) {
    float deltaZ = p2.get_Position().z - p1.get_Position().z;
    float dist = getDistance(p1, p2);
    return asinf(deltaZ / dist) * 180.0f / (3.14159);
}

::std::ptrdiff_t getClosestPlayer(const Player player, std::vector<Player*>& players)
{
    float currentDistance = 0,
        distance = 0;

    int index = 0;

    currentDistance = getDistance(player, *players[0]);

    for (unsigned int i = 1; i < players.size(); i++)
    {
        distance = getDistance(player, *players[i]);

        if (distance < currentDistance)
        {
            currentDistance = distance;
            index = i;
        }

    }
    return players[index]->get_Address();
}