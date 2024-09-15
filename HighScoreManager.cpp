#include "HighScoreManager.h"
#include <fstream>
#include <algorithm>
#include <iostream>

HighScoreManager::HighScoreManager(const std::string& filename) : m_filename(filename) {}

void HighScoreManager::loadScores() {
    m_scores.clear();
    std::ifstream file(m_filename);

    if (file.is_open()) {
        ScoreEntry entry;
        while (file >> entry.playerName >> entry.score) {
            m_scores.push_back(entry);
        }
        file.close();
    }
}

void HighScoreManager::saveScores() const {
    std::ofstream file(m_filename);

    if (file.is_open()) {
        for (const auto& entry : m_scores) {
            file << entry.playerName << " " << entry.score << "\n";
        }
        file.close();
    }
}

bool HighScoreManager::isHighScore(int score) const {
    if (m_scores.size() < m_maxScores) {
        return true;
    }

    return score > m_scores.back().score;
}

void HighScoreManager::addScore(const std::string& playerName, int score) {
    m_scores.push_back({playerName, score});
    std::sort(m_scores.begin(), m_scores.end(), [](const ScoreEntry& a, const ScoreEntry& b) {
        return a.score > b.score;
    });

    if (m_scores.size() > m_maxScores) {
        m_scores.pop_back();
    }
}

const std::vector<ScoreEntry>& HighScoreManager::getScores() const {
    return m_scores;
}