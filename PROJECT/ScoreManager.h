#ifndef SCOREMANAGER_H
#define SCOREMANAGER_H

#include <fstream>
#include <string>

class ScoreManager {
private:
    int currentScore;
    int highScore;
    char playerName[50];
    char highScoreName[50];
    const char* filename;

public:
    ScoreManager();
    
    void addPoints(int points);
    void loadHighScore();
    void saveHighScore();
    
    int getCurrentScore() const { return currentScore; }
    int getHighScore() const { return highScore; }
    const char* getPlayerName() const { return playerName; }
    const char* getHighScoreName() const { return highScoreName; }
    
    void setPlayerName(const char* name);
    void reset();
};

#endif