#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <sstream>
#include "Bullet.h"
#include "Enemy.h"
#include "EnemyBullet.h"
#include "Player.h"
#include "ScoreEntry.h" // Include ScoreEntry header
#include "HighScoreManager.h" // Include HighScoreManager header
#include "Utilities.h" // Include Utilities header for normalize and checkCollision functions

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

bool isEnteringName = false;
std::string playerName;
HighScoreManager highScoreManager("highscores.txt");

sf::Text leaderboardText;

void displayLeaderboard() {
    std::stringstream ss;
    ss << "Leaderboard\n";
    int rank = 1;
    for (const auto& entry : highScoreManager.getScores()) {
        ss << rank << ". " << entry.playerName << ": " << entry.score << "\n";
        rank++;
    }
    leaderboardText.setString(ss.str());
}

int main() {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Square Survivors");

    Player player(sf::Vector2f(375.0f, 275.0f)); // Initial position

    sf::Font font;
    if (!font.loadFromFile("Aerial.ttf")) {
        std::cerr << "Failed to load font!" << std::endl;
        return -1;
    }

    sf::Text livesText;
    livesText.setFont(font);
    livesText.setCharacterSize(20);
    livesText.setFillColor(sf::Color::White);
    livesText.setPosition(10.0f, 10.0f);

    sf::Text pointsText;
    pointsText.setFont(font);
    pointsText.setCharacterSize(20);
    pointsText.setFillColor(sf::Color::White);
    pointsText.setPosition(10.0f, 40.0f);

    sf::Text gameOverText;
    gameOverText.setFont(font);
    gameOverText.setCharacterSize(50);
    gameOverText.setFillColor(sf::Color::Red);
    gameOverText.setString("Game Over\nPress R to Restart");
    gameOverText.setPosition(200.0f, 250.0f);
    bool gameOver = false;

    bool showIntro = true;
    sf::Text introText;
    introText.setFont(font);
    introText.setCharacterSize(30);
    introText.setFillColor(sf::Color::White);
    introText.setString("Controls:\nW/Up: Move Up\nS/Down: Move Down\nA/Left: Move Left\nD/Right: Move Right\nSpace: Shoot\n\nPress Enter to Start");
    introText.setPosition(150.0f, 200.0f);

    sf::Clock invincibilityClock;
    bool isInvincible = false;
    const float invincibilityDuration = 3.0f; // 3 seconds of invincibility

    sf::Clock fireClock;
    float fireRate = 0.5f; // Player can shoot every 0.5 seconds

    sf::Clock enemySpawnClock;
    float enemySpawnRate = 2.0f; // Initial spawn rate (every 2 seconds)
    const float minEnemySpawnRate = 0.5f; // Minimum spawn rate (every 0.5 seconds)

    sf::Clock gameClock;

    std::vector<Bullet> bullets;
    std::vector<Enemy> enemies;
    std::vector<EnemyBullet> enemyBullets;

    int points = 0;

    // Load high scores on game start
    highScoreManager.loadScores();

    // Load font and set up leaderboard text
    leaderboardText.setFont(font);
    leaderboardText.setCharacterSize(20);
    leaderboardText.setFillColor(sf::Color::White);
    leaderboardText.setPosition(10.0f, 90.0f);

    while (window.isOpen()) {
        sf::Time elapsedTime = gameClock.restart();
        float deltaTime = elapsedTime.asSeconds();

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (showIntro && event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {
                showIntro = false;
                gameClock.restart();
            }

            if (!isEnteringName && gameOver && event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::R) {
                gameOver = false;
                player.reset();
                bullets.clear();
                enemies.clear();
                enemyBullets.clear();
                points = 0;
                enemySpawnRate = 2.0f;
                enemySpawnClock.restart();
                fireClock.restart();
                invincibilityClock.restart();
                gameClock.restart();
            }

            if (gameOver && isEnteringName) {
                if (event.type == sf::Event::TextEntered) {
                    if (event.text.unicode == '\b') { // Handle backspace
                        if (!playerName.empty()) {
                            playerName.pop_back();
                        }
                    } else if (event.text.unicode == '\r' || event.text.unicode == '\n') { // Handle Enter
                        if (!playerName.empty()) {
                            highScoreManager.addScore(playerName, points);
                            highScoreManager.saveScores();
                            displayLeaderboard();
                            isEnteringName = false;
                        }
                    } else { // Add character to name
                        playerName += static_cast<char>(event.text.unicode);
                    }
                }
            }
        }

        if (showIntro) {
            window.clear(sf::Color::Black);
            window.draw(introText);
            window.display();
            continue;
        }

        if (gameOver) {
            if (!isEnteringName) {
                window.clear(sf::Color::Black);
                window.draw(gameOverText);
                window.draw(leaderboardText);
                window.display();
            } else {
                window.clear(sf::Color::Black);
                sf::Text enterNameText("Enter your name: " + playerName, font, 20);
                enterNameText.setFillColor(sf::Color::White);
                enterNameText.setPosition(10.0f, 70.0f);
                window.draw(gameOverText);
                window.draw(leaderboardText);
                window.draw(enterNameText);
                window.display();
            }
            continue;
        }

        sf::Vector2f direction(0.0f, 0.0f);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            direction.y -= 1.0f;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            direction.y += 1.0f;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            direction.x -= 1.0f;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            direction.x += 1.0f;
        }

        if (direction != sf::Vector2f(0.0f, 0.0f)) {
            direction = normalize(direction);
        }

        player.move(direction, deltaTime);

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && fireClock.getElapsedTime().asSeconds() >= fireRate) {
            fireClock.restart();
            sf::Vector2f playerPosition = player.getShape().getPosition() + player.getShape().getSize() / 2.0f;
            std::vector<sf::Vector2f> directions = {
                { 0, -1 },  { 0, 1 },   { -1, 0 },  { 1, 0 },
                { -1, -1 }, { 1, -1 },  { -1, 1 },  { 1, 1 }
            };
            for (const sf::Vector2f& dir : directions) {
                bullets.push_back(Bullet(playerPosition, normalize(dir)));
            }
        }

        if (enemySpawnClock.getElapsedTime().asSeconds() >= enemySpawnRate) {
            enemySpawnClock.restart();

            if (enemySpawnRate > minEnemySpawnRate) {
                enemySpawnRate -= 0.05f; // Decrease spawn rate by 0.05 seconds
            }

            float x = 0.0f, y = 0.0f;
            int side = std::rand() % 4;

            switch (side) {
                case 0: // Left
                    x = -50.0f;
                    y = static_cast<float>(std::rand() % SCREEN_HEIGHT);
                    break;
                case 1: // Right
                    x = SCREEN_WIDTH + 50.0f;
                    y = static_cast<float>(std::rand() % SCREEN_HEIGHT);
                    break;
                case 2: // Top
                    x = static_cast<float>(std::rand() % SCREEN_WIDTH);
                    y = -50.0f;
                    break;
                case 3: // Bottom
                    x = static_cast<float>(std::rand() % SCREEN_WIDTH);
                    y = SCREEN_HEIGHT + 50.0f;
                    break;
            }

            sf::Vector2f enemyPosition(x, y);
            sf::Vector2f playerPosition = player.getShape().getPosition() + player.getShape().getSize() / 2.0f;
            enemies.push_back(Enemy(enemyPosition, playerPosition));
        }

        for (Bullet& bullet : bullets) {
            bullet.update(deltaTime);
        }

        for (EnemyBullet& enemyBullet : enemyBullets) {
            enemyBullet.update(deltaTime);
        }

        for (Enemy& enemy : enemies) {
            enemy.update(deltaTime, player.getShape().getPosition() + player.getShape().getSize() / 2.0f);
            enemy.shoot(enemyBullets, player.getShape().getPosition() + player.getShape().getSize() / 2.0f);
        }

        bullets.erase(
            std::remove_if(bullets.begin(), bullets.end(), [](const Bullet& bullet) {
                sf::Vector2f pos = bullet.getShape().getPosition();
                return pos.x < 0 || pos.x > SCREEN_WIDTH || pos.y < 0 || pos.y > SCREEN_HEIGHT;
            }),
            bullets.end()
        );

        enemyBullets.erase(
            std::remove_if(enemyBullets.begin(), enemyBullets.end(), [](const EnemyBullet& bullet) {
                sf::Vector2f pos = bullet.getShape().getPosition();
                return pos.x < 0 || pos.x > SCREEN_WIDTH || pos.y < 0 || pos.y > SCREEN_HEIGHT;
            }),
            enemyBullets.end()
        );

        for (auto bulletIt = bullets.begin(); bulletIt != bullets.end();) {
            bool bulletRemoved = false;

            for (auto enemyIt = enemies.begin(); enemyIt != enemies.end();) {
                if (checkCollision(bulletIt->getShape(), enemyIt->getShape())) {
                    enemyIt->takeDamage(50); // Deal 50 damage

                    if (!enemyIt->isAlive()) {
                        enemyIt = enemies.erase(enemyIt);
                        points += 100;
                    } else {
                        ++enemyIt;
                    }

                    bulletIt = bullets.erase(bulletIt);
                    bulletRemoved = true;
                    break;
                } else {
                    ++enemyIt;
                }
            }

            if (!bulletRemoved) {
                ++bulletIt;
            }
        }

        if (!isInvincible) {
            for (auto enemyIt = enemies.begin(); enemyIt != enemies.end();) {
                if (checkCollision(player.getShape(), enemyIt->getShape())) {
                    isInvincible = true; // Set player to invincible
                    invincibilityClock.restart();
                    player.takeDamage(20); // Deal 20 damage to player when colliding
                    if (!player.isAlive()) {
                        if (!player.loseLife()) {
                            gameOver = true;

                            // Check if high score
                            if (highScoreManager.isHighScore(points)) {
                                isEnteringName = true;
                                playerName.clear();
                            } else {
                                displayLeaderboard();
                            }

                            break;
                        } else {
                            player.resetHealth();
                        }
                    }

                    if (!enemyIt->isAlive()) {
                        enemyIt = enemies.erase(enemyIt);
                    } else {
                        ++enemyIt;
                    }
                } else {
                    ++enemyIt;
                }
            }
        } else {
            if (invincibilityClock.getElapsedTime().asSeconds() >= invincibilityDuration) {
                isInvincible = false;
            }
        }

        if (!isInvincible) {
            for (auto bulletIt = enemyBullets.begin(); bulletIt != enemyBullets.end();) {
                if (checkCollision(player.getShape(), bulletIt->getShape())) {
                    isInvincible = true; // Set player to invincible
                    invincibilityClock.restart();
                    player.takeDamage(40); // Deal 40 damage to player from enemy bullet
                    if (!player.isAlive()) {
                        if (!player.loseLife()) {
                            gameOver = true;

                            // Check if high score
                            if (highScoreManager.isHighScore(points)) {
                                isEnteringName = true;
                                playerName.clear();
                            } else {
                                displayLeaderboard();
                            }

                            break;
                        } else {
                            player.resetHealth();
                        }
                    }

                    bulletIt = enemyBullets.erase(bulletIt);
                } else {
                    ++bulletIt;
                }
            }
        } else {
            if (invincibilityClock.getElapsedTime().asSeconds() >= invincibilityDuration) {
                isInvincible = false;
            }
        }

        if (isInvincible) {
            if (static_cast<int>(invincibilityClock.getElapsedTime().asMilliseconds() / 200) % 2 == 0) {
                player.setFillColor(sf::Color::Transparent);
            } else {
                player.setFillColor(sf::Color::White);
            }
        } else {
            player.setFillColor(sf::Color::White);
        }

        livesText.setString("Lives: " + std::to_string(player.getLives()));
        pointsText.setString("Points: " + std::to_string(points));

        window.clear(sf::Color::Black);

        player.draw(window);

        for (const Bullet& bullet : bullets) {
            bullet.draw(window);
        }

        for (const EnemyBullet& enemyBullet : enemyBullets) {
            enemyBullet.draw(window);
        }

        for (const Enemy& enemy : enemies) {
            enemy.draw(window);
        }

        window.draw(livesText);
        window.draw(pointsText);

        if (gameOver) {
            window.draw(gameOverText);
            window.draw(leaderboardText);
        }

        window.display();
    }

    return 0;
}