#ifndef BULLET_H
#define BULLET_H

#include <SFML/Graphics.hpp>

class Bullet {
public:
    Bullet(sf::Vector2f position, sf::Vector2f direction)
        : m_velocity(direction * m_speed) {
        m_shape.setRadius(5.0f);
        m_shape.setFillColor(sf::Color::Yellow);
        m_shape.setPosition(position);
    }

    void update(float deltaTime) {
        m_shape.move(m_velocity * deltaTime);
    }

    void draw(sf::RenderWindow& window) const {
        window.draw(m_shape);
    }

    const sf::CircleShape& getShape() const {
        return m_shape;
    }

private:
    sf::CircleShape m_shape;
    sf::Vector2f m_velocity;
    static constexpr float m_speed = 300.0f; // Speed of the bullet
};

#endif // BULLET_H