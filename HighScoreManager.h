#ifndef HIGHSCOREMANAGER_H
#define HIGHSCOREMANAGER_H

#include <vector>
#include <string>
#include "ScoreEntry.h"

class HighScoreManager {
public:
    HighScoreManager(const std::string& filename);

    void loadScores();
    void saveScores() const;
    bool isHighScore(int score) const;
    void addScore(const std::string& playerName, int score);
    const std::vector<ScoreEntry>& getScores() const;

private:
    std::string m_filename;
    std::vector<ScoreEntry> m_scores;
    static constexpr int m_maxScores = 10; // Top 10 scores
};

#endif // HIGHSCOREMANAGER_H