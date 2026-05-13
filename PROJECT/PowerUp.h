#ifndef POWERUP_H
#define POWERUP_H

#include <SFML/Graphics.hpp>
#include <string>
using namespace std;
using namespace sf;

class PowerUp {
protected:
    float x, y;
    int lane;
    float speed;
    bool active;
    
    CircleShape collisionShape;
    Texture texture;
    Sprite sprite;
    
public:
    PowerUp(int ln, float spd);
    virtual ~PowerUp() {}
    
    virtual void update(float deltaTime);
    virtual void render(RenderWindow& window);
    virtual void applyEffect(class Player* player) = 0;
    
    bool isActive() const { return active; }
    void deactivate() { active = false; }
    
    FloatRect getBounds() const { return collisionShape.getGlobalBounds(); }
    int getLane() const { return lane; }
};

class MagnetPower : public PowerUp {
public:
    MagnetPower(int ln, float spd);
    void applyEffect(class Player* player) override;
};

class JetpackPower : public PowerUp {
public:
    JetpackPower(int ln, float spd);
    void applyEffect(class Player* player) override;
};

class ShieldPower : public PowerUp {
public:
    ShieldPower(int ln, float spd);
    void applyEffect(class Player* player) override;
};

class DoubleCoinPower : public PowerUp {
public:
    DoubleCoinPower(int ln, float spd);
    void applyEffect(class Player* player) override;
};

#endif