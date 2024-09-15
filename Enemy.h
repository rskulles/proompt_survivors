#ifndef ENEMY_H
#define ENEMY_H

#include <SFML/Graphics.hpp>
#include <cmath>
#include "EnemyBullet.h"
class Enemy {
public:
    Enemy(sf::Vector2f position, sf::Vector2f targetPosition)
        : m_targetPosition(targetPosition), m_health(100), m_maxHealth(100) {
        m_shape.setRadius(25.0f);
        m_shape.setFillColor(sf::Color::Green);
        m_shape.setPosition(position);

        updateHealthBar();
    }

    void update(float deltaTime, sf::Vector2f playerPosition) {
        m_targetPosition = playerPosition;
        sf::Vector2f direction = normalize(m_targetPosition - m_shape.getPosition());
        m_shape.move(direction * m_speed * deltaTime);
        updateHealthBarPosition();
    }

    void draw(sf::RenderWindow& window) const {
        window.draw(m_shape);
        window.draw(m_healthBarBackground);
        window.draw(m_healthBar);
    }

    void takeDamage(int damage) {
        m_health -= damage;
        if (m_health < 0) {
            m_health = 0;
        }
        updateHealthBar();
    }

    bool isAlive() const {
        return m_health > 0;
    }

    const sf::CircleShape& getShape() const {
        return m_shape;
    }

    void shoot(std::vector<EnemyBullet>& enemyBullets, sf::Vector2f playerPosition) {
        if (m_shootClock.getElapsedTime().asSeconds() >= m_fireRate) {
            m_shootClock.restart();
            sf::Vector2f bulletDirection = normalize(playerPosition - m_shape.getPosition());
            sf::Vector2f bulletPosition = m_shape.getPosition() + m_shape.getRadius() * bulletDirection;
            enemyBullets.emplace_back(bulletPosition, bulletDirection);
        }
    }

private:
    sf::CircleShape m_shape;
    sf::Vector2f m_targetPosition;
    int m_health;
    int m_maxHealth;
    sf::RectangleShape m_healthBarBackground;
    sf::RectangleShape m_healthBar;
    sf::Clock m_shootClock;

    static constexpr float m_speed = 100.0f; // Speed of the enemy
    static constexpr float m_fireRate = 3.0f; // Enemy can shoot every 3 seconds

    void updateHealthBar() {
        float healthPercent = static_cast<float>(m_health) / m_maxHealth;
        m_healthBar.setSize(sf::Vector2f(50.0f * healthPercent, 5.0f));
    }

    void updateHealthBarPosition() {
        sf::Vector2f position = m_shape.getPosition();
        m_healthBarBackground.setPosition(position.x - 25.0f, position.y - 10.0f);
        m_healthBar.setPosition(position.x - 25.0f, position.y - 10.0f);
    }

    sf::Vector2f normalize(const sf::Vector2f& source) {
        float length = std::sqrt((source.x * source.x) + (source.y * source.y));
        if (length != 0)
            return sf::Vector2f(source.x / length, source.y / length);
        else
            return source;
    }
};

#endif // ENEMY_H