#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>

class Player {
public:
    Player(sf::Vector2f position)
        : m_initialPosition(position), m_health(100), m_maxHealth(100), m_lives(3) {
        m_shape.setSize(sf::Vector2f(50.0f, 50.0f));
        m_shape.setFillColor(sf::Color::Red);
        m_shape.setPosition(position);

        updateHealthBar();
    }

    void draw(sf::RenderWindow& window) const {
        window.draw(m_shape);
        window.draw(m_healthBarBackground);
        window.draw(m_healthBar);
    }

    void move(sf::Vector2f direction, float deltaTime) {
        m_shape.move(direction * m_speed * deltaTime);
        updateHealthBarPosition();
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

    bool loseLife() {
        --m_lives;
        return m_lives > 0;
    }

    int getLives() const {
        return m_lives;
    }

    void resetHealth() {
        m_health = m_maxHealth;
        updateHealthBar();
    }

    const sf::RectangleShape& getShape() const {
        return m_shape;
    }

    void setFillColor(const sf::Color& color) {
        m_shape.setFillColor(color);
    }

    void reset() {
        m_health = m_maxHealth;
        m_lives = 3;
        m_shape.setPosition(m_initialPosition);
        updateHealthBar();
    }

private:
    sf::RectangleShape m_shape;
    sf::Vector2f m_initialPosition;
    int m_health;
    int m_maxHealth;
    int m_lives;
    sf::RectangleShape m_healthBarBackground;
    sf::RectangleShape m_healthBar;
    static constexpr float m_speed = 200.0f; // Speed of the player

    void updateHealthBar() {
        float healthPercent = static_cast<float>(m_health) / m_maxHealth;
        m_healthBar.setSize(sf::Vector2f(50.0f * healthPercent, 5.0f));
    }

    void updateHealthBarPosition() {
        sf::Vector2f position = m_shape.getPosition();
        m_healthBarBackground.setPosition(position.x, position.y - 10.0f);
        m_healthBar.setPosition(position.x, position.y - 10.0f);
    }
};

#endif // PLAYER_H