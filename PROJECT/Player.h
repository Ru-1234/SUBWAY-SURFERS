#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;
using namespace sf;

enum PlayerState { RUNNING, JUMPING, SLIDING };

class Player {
private:
    int currentLane;                
    float x, y, baseY;                          // baseY: ground level Y position
    
    PlayerState state;                          // can be RUNNING, JUMPING, SLIDING
    float jumpVelocity;
    float gravity;
    
    bool hasShield, hasMagnet, hasJetpack, hasDoubleCoin;
    float shieldTimer, magnetTimer, jetpackTimer, doubleCoinTimer;
    
    int animationFrame;
    float animationTimer;
    
    //Graphics
    Texture playerTexture;
    Sprite playerSprite;
    RectangleShape shape;
    bool textureLoaded;
    
    // Power-up 
    CircleShape shieldVisual;
    CircleShape magnetVisual;
    CircleShape jetpackVisual;
    CircleShape doubleCoinVisual;
    
    RectangleShape shadowShape;
    
public:
    Player();
    
    void reset();
    void moveLeft();
    void moveRight();
    void jump();
    void slide();
    
    void update(float deltaTime);
    void render(RenderWindow& window);
    
    FloatRect getBounds() const;
    
    int getLane() const { return currentLane; }
    PlayerState getState() const { return state; }
    
    bool isShielded() const { return hasShield; }
    bool hasActiveMagnet() const { return hasMagnet; }
    bool hasActiveDoubleCoin() const { return hasDoubleCoin; }
    
    void activateShield();
    void activateMagnet();
    void activateJetpack();
    void activateDoubleCoin();
};

#endif
