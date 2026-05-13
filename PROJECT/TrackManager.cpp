#include "TrackManager.h"
#include <iostream>
#include <cstdlib>    // For rand(), srand()
#include <ctime>      // For time()
using namespace std;
using namespace sf;

TrackManager::TrackManager() : currentSpeed(200.0f), obstacleSpawnTimer(0.0f), powerUpSpawnTimer(0.0f), coinSpawnTimer(0.0f) {
    srand(time(0));  // Seed random number generator
    
    if (!backgroundTexture.loadFromFile("/home/maham/Downloads/OOP-project/Images/track.png")) {
        cout << "ERROR: Could not load track.png" << endl;
    } else {
        backgroundSprite.setTexture(backgroundTexture);
        backgroundSprite.setScale(2.0f, 2.0f);
    }
}

void TrackManager::reset() {
    obstacles.clear();
    powerUps.clear();
    coins.clear();
    
    obstacleSpawnTimer = 0.0f;
    powerUpSpawnTimer = 0.0f;
    coinSpawnTimer = 0.0f;
    
    currentSpeed = 200.0f;
}

int TrackManager::getRandomLane() {
    return rand() % 3; 
}

void TrackManager::update(float deltaTime) {
    obstacleSpawnTimer += deltaTime;
    powerUpSpawnTimer += deltaTime;
    coinSpawnTimer += deltaTime;
    
    // Spawn obstacles - interval decreases as speed increases
    float obstacleInterval = 2.5f - (currentSpeed - 200.0f) / 200.0f;
    if (obstacleInterval < 1.0f) {
        obstacleInterval = 1.0f;  //min 1 second b/w obstacles
    }   //moves based on speed
    
    if (obstacleSpawnTimer >= obstacleInterval) {
        spawnObstacle();
        obstacleSpawnTimer = 0.0f;
    }
    
    // Spawn power-ups every 8 seconds
    if (powerUpSpawnTimer >= 8.0f) {
        spawnPowerUp();
        powerUpSpawnTimer = 0.0f;
    }
    
    // Spawn coins every 0.8 seconds
    if (coinSpawnTimer >= 0.8f) {
        spawnCoin();
        coinSpawnTimer = 0.0f;
    }
    
    // Update obstacles
    for (int i = obstacles.getSize() - 1; i >= 0; i--) {
        Obstacle* obs = obstacles.get(i);
        if (obs) {
            obs->update(deltaTime);
            if (!obs->isActive()) {
                obstacles.removeAt(i);
            }
        }
    }
    
    // Update power-ups
    for (int i = powerUps.getSize() - 1; i >= 0; i--) {
        PowerUp* pw = powerUps.get(i);
        if (pw) {
            pw->update(deltaTime);
            if (!pw->isActive()) {
                powerUps.removeAt(i);
            }
        }
    }
    
    // Update coins
    for (int i = coins.getSize() - 1; i >= 0; i--) {
        Coin* coin = coins.get(i);
        if (coin) {
            coin->update(deltaTime);
            if (!coin->isActive()) {
                coins.removeAt(i);
            }
        }
    }
}

void TrackManager::spawnObstacle() {
    int lane = getRandomLane();
    int type = rand() % 5;  // 5 obstacle types (0-4)
    
    Obstacle* obs = nullptr;
    
    switch (type) {
        case 0: obs = new Train(lane, currentSpeed); break;
        case 1: obs = new Barrier(lane, currentSpeed); break;
        case 2: obs = new Cone(lane, currentSpeed); break;
        case 3: obs = new Fence(lane, currentSpeed); break;
        case 4: obs = new Policeman(lane, currentSpeed); break;
    }
    
    if (obs != NULL) {
        obstacles.add(obs);
    }
}

void TrackManager::spawnPowerUp() {
    int lane = getRandomLane();
    int type = rand() % 4;
    
    PowerUp* pw = NULL;
    
    switch (type) {
        case 0: pw = new MagnetPower(lane, currentSpeed); break;
        case 1: pw = new JetpackPower(lane, currentSpeed); break;
        case 2: pw = new ShieldPower(lane, currentSpeed); break;
        case 3: pw = new DoubleCoinPower(lane, currentSpeed); break;
    }
    
    if (pw != NULL) {
        powerUps.add(pw);
    }
}
//random lane and random type select hota hai.
//Naye object dynamically create hote hain aur list me add hote hain
void TrackManager::spawnCoin() {
    int lane = getRandomLane();
    Coin* coin = new Coin(lane, currentSpeed);
    coins.add(coin);
}

void TrackManager::increaseSpeed(float amount) {
    currentSpeed += amount;
    if (currentSpeed > 500.0f) {
        currentSpeed = 500.0f;  // Maximum speed
    }
}

void TrackManager::renderBackground(RenderWindow& window, float scrollOffset) const {
    Sprite bg1 = backgroundSprite;
    Sprite bg2 = backgroundSprite;
    
    float y1 = scrollOffset;
    float y2 = scrollOffset - 600.0f;  // 600 = window height
    
    bg1.setPosition(0.0f, y1);
    bg2.setPosition(0.0f, y2);
    
    window.draw(bg1);
    window.draw(bg2);

}
