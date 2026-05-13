#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
using namespace std;
using namespace sf;

class Obstacle {
protected:
    int lane;
    float x, y;
    float speed; //downward speed 
    bool active;
    
    Texture texture;
    Sprite sprite;
    float baseScale;
    
public:
    Obstacle(int ln, float spd, const string& textureFile); //constructor
    virtual ~Obstacle() {}
    
    virtual void update(float deltaTime);
    void render(RenderWindow& window);
    
    bool isActive() const { return active; }
    void deactivate() { active = false; }
    
    int getLane() const { return lane; }
    FloatRect getBounds() const { return sprite.getGlobalBounds(); }
    
    float getBaseScale() const { return baseScale; }
    
    virtual bool canJumpOver() const { return true; }
    virtual bool canSlideUnder() const { return false; }
};
//child classes
class Train : public Obstacle {
public:
    Train(int ln, float spd);
    bool canJumpOver() const override { return false; } 
    bool canSlideUnder() const override { return true; }
};

class Barrier : public Obstacle {
public:
    Barrier(int ln, float spd);
    bool canJumpOver() const override { return true; }
};

class Cone : public Obstacle {
public:
    Cone(int ln, float spd);
    bool canJumpOver() const override { return true; }
};

class Fence : public Obstacle {
public:
    Fence(int ln, float spd);
    bool canSlideUnder() const override { return true; }
};

class Policeman : public Obstacle {
public:
    Policeman(int ln, float spd);
    bool canJumpOver() const override { return true; }
};

#endif
