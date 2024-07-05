#include "snake.h"
#include "logger.h"
#include <algorithm>
#include <format>
#include <random>

std::random_device rd;
std::mt19937 mt(rd());

bool Point::operator==(const Point &other) const {
    return (this->x == other.x && this->y == other.y);
}

Point Point::randomPoint() {

    int maxX = collider.w / GRID_WIDTH;
    int maxY = collider.h / GRID_HEIGHT;

    std::uniform_int_distribution<int> distributionX(0, maxX - 1);
    std::uniform_int_distribution<int> distributionY(0, maxY - 1);

    int fx = distributionX(mt);
    int fy = distributionY(mt);

    return {fx * GRID_WIDTH + RLPADDING, fy * GRID_HEIGHT + TBPADDING};
}

void Snake::spawnFood() {
    Point temp;
    do {
        temp = Point::randomPoint();
    } while (std::find(this->segments.begin(), this->segments.end(), temp) != this->segments.end() || temp == this->head);

    this->food.position = temp;
    this->food.isCollided = false;
}

bool Snake::checkSelfCollision() {
    return (std::find(this->segments.begin(), this->segments.end(), this->head) != this->segments.end());
}

bool Snake::checkFoodCollision() {
    if (this->food.isCollided == false && this->food.position == this->head) {
        Logger::Log(std::format("Slayed the fruit at ({}, {})", this->food.position.x, this->food.position.y));
        this->food.isCollided = true;
        this->spawnFood();
        return true;
    }
    return false;
}

void Snake::init() {
    segments.clear();
    spawnFood();

    head = Point::randomPoint();
    while (head == food.position)
        head = Point::randomPoint();
}

void Snake::reset() {
    init();
}

void Snake::grow() {
    Logger::Log("one more");
    segments.push_back({WINDOW_WIDTH, WINDOW_HEIGHT});
}

void Snake::move(Direction currentDirection) {
    Point oldMove = {head.x, head.y};
    switch (currentDirection) {
        case UP:
            this->head.y -= GRID_HEIGHT;
            break;
        case DOWN:
            this->head.y += GRID_HEIGHT;
            break;
        case LEFT:
            this->head.x -= GRID_WIDTH;
            break;
        case RIGHT:
            this->head.x += GRID_WIDTH;
            break;
        default:
            break;
    }

    moveBody(oldMove);
}

void Snake::moveBody(Point headPos) {
    Point old = headPos;
    Point curr;
    for (auto it = segments.begin(); it != segments.end(); it++) {
        curr = *it;
        *it = old;
        old = curr;
    }
}
