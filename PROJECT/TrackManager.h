#ifndef TRACKMANAGER_H
#define TRACKMANAGER_H

#include "GameList.h"
#include "Obstacle.h"
#include "PowerUp.h"
#include "Coin.h"
#include <cstdlib>
#include <ctime>
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

class TrackManager {
private:
    GameList<Obstacle> obstacles;           // List of active obstacles on track
    GameList<PowerUp> powerUps;
    GameList<Coin> coins;
    float obstacleSpawnTimer;
    float powerUpSpawnTimer;
    float coinSpawnTimer;
    float currentSpeed;
    
    Texture backgroundTexture;
    Sprite backgroundSprite;
    
    int getRandomLane();
    
public:
    TrackManager();
    
    void update(float deltaTime);
    void spawnObstacle();
    void spawnPowerUp();
    void spawnCoin();
    void increaseSpeed(float amount);
    void reset();
    
    void renderBackground(RenderWindow& window, float scrollOffset) const;
    
    const Sprite& getBackground() const { return backgroundSprite; }
    
    GameList<Obstacle>& getObstacles() { return obstacles; }
    GameList<PowerUp>& getPowerUps() { return powerUps; }
    GameList<Coin>& getCoins() { return coins; }
    
    float getCurrentSpeed() const { return currentSpeed; }
};

#endif