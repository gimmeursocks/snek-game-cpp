#pragma once

#include "game.h"
#include <vector>

class Point {
public:
    int x, y;
    bool operator==(const Point &) const;
    static Point randomPoint();
};

class Food {
public:
    Point position;
    bool isCollided = false;
};

class Snake {
private:
    void moveBody(Point);

public:
    void init();
    void reset();
    void grow();
    void move(Direction);
    void spawnFood();
    bool checkSelfCollision();
    bool checkFoodCollision();
    Point head;
    std::vector<Point> segments;
    Food food;
};