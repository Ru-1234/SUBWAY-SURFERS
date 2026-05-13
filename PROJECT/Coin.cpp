#include "Coin.h"
#include <iostream>
#include <cmath>
using namespace std;
using namespace sf;

Coin::Coin(int ln, float spd):lane(ln), speed(spd), active(true), rotationAngle(0.0f){ //constructor
    float startScale = 0.08f; //starting size of coin
    
    // Lane positions: lane 0=140, lane 1=410, lane 2=680
    x = 140.0f + lane * 270.0f; //270 is step bw lanes
    y = -50.0f; // y inc downward so that coin will be visible in screen

    if (!texture.loadFromFile("/home/maham/Downloads/OOP-project/Images/coin.png")){
        cout << "ERROR: Could not load coin.png" << endl;
    }
    sprite.setTexture(texture);
    sprite.setScale(startScale, startScale);
    sprite.setPosition(x, y);
    sprite.setOrigin(texture.getSize().x / 2.0f, texture.getSize().y / 2.0f);
}

void Coin::update(float deltaTime){ //movement,rotation,scaling
    y += (speed * deltaTime);
    rotationAngle += 200.0f * deltaTime;        // 200 degrees per second
    if (rotationAngle >= 360.0f)
        rotationAngle -= 360.0f;         //rotation angle should be bw 0 to 360
    
    float progress = (y + 50.0f) / 700.0f; // it is value that tells how much coin is far from player and its
    //bw 0 and 1

    if (progress < 0.0f) progress = 0.0f;
    if (progress > 1.0f) progress = 1.0f;
    
    float currentScale = 0.08f + progress * (0.25f - 0.08f); //start+t*(end-start) t=progress.
    float horizontalDrift = sin(y * 0.01f) * 10.0f;
    float currentX = x + horizontalDrift;  //apne image ki scaling
    
    // Apply transformations
    sprite.setScale(currentScale, currentScale);
    sprite.setPosition(currentX, y);
    sprite.setRotation(rotationAngle);
    
    if (y > 700.0f)  // Screen height active=false
        active = false;
}

void Coin::render(RenderWindow& window) {
    if (active)
        window.draw(sprite);
}
