#include "ScoreManager.h"
#include <cstring>
using namespace std;

ScoreManager::ScoreManager() : currentScore(0), highScore(0), filename("highscore.txt") {
    playerName[0] = '\0';
    highScoreName[0] = '\0';
    loadHighScore();//read highscore from file
}

void ScoreManager::addPoints(int points) {
    currentScore += points;
    if (currentScore > highScore) {
        highScore = currentScore;
        strcpy(highScoreName, playerName); //writes new high core to file 
        saveHighScore();
    }
}

void ScoreManager::loadHighScore() {
    ifstream file(filename);
    if (file.is_open()) {
        file >> highScore;   //reads high score
        file.ignore();       // new line
        file.getline(highScoreName, 50); //name
        file.close();
    }
}

void ScoreManager::saveHighScore() {
    ofstream file(filename);
    if (file.is_open()) {
        file << highScore << std::endl;
        file << highScoreName << std::endl;   //writes name and score
        file.close();
    }
}

void ScoreManager::setPlayerName(const char* name) {
    strcpy(playerName, name);
}

void ScoreManager::reset() {
    currentScore = 0;  //reset score for new game 
}
