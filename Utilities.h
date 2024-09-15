#ifndef UTILITIES_H
#define UTILITIES_H

#include <SFML/Graphics.hpp>
#include <cmath>

// Function to normalize a vector
sf::Vector2f normalize(const sf::Vector2f& source) {
    float length = std::sqrt((source.x * source.x) + (source.y * source.y));
    if (length != 0)
        return sf::Vector2f(source.x / length, source.y / length);
    else
        return source;
}

// Function to check collision between two rectangle shapes
bool checkCollision(const sf::RectangleShape& shape1, const sf::RectangleShape& shape2) {
    return shape1.getGlobalBounds().intersects(shape2.getGlobalBounds());
}

// Function to check collision between two circle shapes
bool checkCollision(const sf::CircleShape& shape1, const sf::CircleShape& shape2) {
    float distance = std::sqrt(std::pow(shape1.getPosition().x - shape2.getPosition().x, 2) +
                               std::pow(shape1.getPosition().y - shape2.getPosition().y, 2));
    return distance < (shape1.getRadius() + shape2.getRadius());
}

// Function to check collision between a rectangle and a circle shape
bool checkCollision(const sf::RectangleShape& rect, const sf::CircleShape& circle) {
    sf::FloatRect rectBounds = rect.getGlobalBounds();
    sf::Vector2f circleCenter = circle.getPosition() + sf::Vector2f(circle.getRadius(), circle.getRadius());
    float closestX = std::clamp(circleCenter.x, rectBounds.left, rectBounds.left + rectBounds.width);
    float closestY = std::clamp(circleCenter.y, rectBounds.top, rectBounds.top + rectBounds.height);

    float distance = std::sqrt((circleCenter.x - closestX) * (circleCenter.x - closestX) +
                               (circleCenter.y - closestY) * (circleCenter.y - closestY));

    return distance < circle.getRadius();
}

#endif // UTILITIES_H