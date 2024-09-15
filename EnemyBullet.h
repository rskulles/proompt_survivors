#ifndef ENEMYBULLET_H
#define ENEMYBULLET_H

#include <SFML/Graphics.hpp>

class EnemyBullet {
public:
    EnemyBullet(sf::Vector2f position, sf::Vector2f direction)
        : m_direction(direction) {
        m_shape.setRadius(5.0f);
        m_shape.setFillColor(sf::Color::Yellow);
        m_shape.setPosition(position);
    }

    void update(float deltaTime) {
        m_shape.move(m_direction * m_speed * deltaTime);
    }

    void draw(sf::RenderWindow& window) const {
        window.draw(m_shape);
    }

    const sf::CircleShape& getShape() const {
        return m_shape;
    }

private:
    sf::CircleShape m_shape;
    sf::Vector2f m_direction;
    static constexpr float m_speed = 300.0f; // Speed of the enemy bullet
};

#endif // ENEMYBULLET_H