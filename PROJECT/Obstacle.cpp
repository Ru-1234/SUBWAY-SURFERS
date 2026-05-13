#include "Obstacle.h"
#include <cmath>
using namespace std;
using namespace sf;

Obstacle::Obstacle(int ln, float spd, const string& textureFile): lane(ln), speed(spd), active(true), baseScale(0.5f) {
    x = 140.0f + lane * 270.0f;
    y = 0.0f;                           // starting vertucal position
    if (!texture.loadFromFile(textureFile)){
        cout << "Failed to load texture: " << textureFile << endl;
    } else {
        sprite.setTexture(texture);
        sprite.setOrigin(texture.getSize().x / 2.0f, texture.getSize().y / 2.0f);
        sprite.setPosition(x, y);
    }
}

void Obstacle::update(float deltaTime) { //controls obstacle movoment
    y += speed * deltaTime;
    if (y > 700.0f) {
        active = false; 
    }
    
    float depth = (y + 100.0f) / 800.0f;  // 0.0 (far) to 1.0 (near) the way obstacles appears on screen fake        projecton
    if (depth < 0.2f) 
        depth = 0.2f;
    if (depth > 1.0f) 
        depth = 1.0f;
    
    float baseScale = getBaseScale();
    sprite.setScale(baseScale * depth, baseScale * depth);
    
    float centerX = 400.0f;  // Screen center
    float laneOffset = x - centerX;
    float perspectiveX = centerX + (laneOffset * (0.7f + depth * 0.3f)); //lanes are narrow near top
    
    sprite.setPosition(perspectiveX, y);
}

void Obstacle::render(RenderWindow& window) {
    if (active) {
        window.draw(sprite);
    }
}
//child class construtor 
Train::Train(int ln, float spd): Obstacle(ln, spd, "/home/maham/Downloads/OOP-project/Images/train.png") {
    baseScale = 0.8f;
}

Barrier::Barrier(int ln, float spd): Obstacle(ln, spd, "/home/maham/Downloads/OOP-project/Images/barrier.png") {
    baseScale = 0.55f;
}
Cone::Cone(int ln, float spd):Obstacle(ln, spd, "/home/maham/Downloads/OOP-project/Images/cone.png") {
    baseScale = 0.24f;
}

Fence::Fence(int ln, float spd) : Obstacle(ln, spd, "/home/maham/Downloads/OOP-project/Images/fence.png") {
    baseScale = 0.4f;
}

Policeman::Policeman(int ln, float spd): Obstacle(ln, spd, "/home/maham/Downloads/OOP-project/Images/policeman.png"){
    baseScale = 0.7f;
}
