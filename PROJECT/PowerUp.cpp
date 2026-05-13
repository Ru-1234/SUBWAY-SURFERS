#include "PowerUp.h"
#include "Player.h"
#include <iostream>
using namespace std;
using namespace sf;

PowerUp::PowerUp(int ln, float spd) : lane(ln), speed(spd), active(true) {
    const float COLLISION_RADIUS = 30.0f;
    x = 140.0f + lane * 270.0f;
    y = -50.0f;

    collisionShape.setRadius(COLLISION_RADIUS);
    collisionShape.setFillColor(Color::Transparent);
    collisionShape.setOutlineColor(Color::Red);
    collisionShape.setOutlineThickness(2.0f);
    collisionShape.setOrigin(COLLISION_RADIUS, COLLISION_RADIUS);
    collisionShape.setPosition(x, y);
    
    sprite.setPosition(x, y);
}

void PowerUp::update(float deltaTime) {
    y += speed * deltaTime;
    
    collisionShape.setPosition(x, y);
    sprite.setPosition(x, y);
    
    if (y > 700.0f) {
        active = false;
    }
}

void PowerUp::render(RenderWindow& window) {
    if (active) {
        window.draw(sprite);
    }
}

MagnetPower::MagnetPower(int ln, float spd) : PowerUp(ln, spd) {
    if (!texture.loadFromFile("/home/maham/Downloads/OOP-project/Images/magnet.png")) {
        cout << "ERROR: cannot load magnet.png" << endl;
    } else {
        sprite.setTexture(texture);
        sprite.setOrigin(texture.getSize().x / 2.0f, texture.getSize().y / 2.0f);

        sprite.setScale(0.15f, 0.10f);
    }
}

JetpackPower::JetpackPower(int ln, float spd) : PowerUp(ln, spd) {
    if (!texture.loadFromFile("/home/maham/Downloads/OOP-project/Images/jetpack.png")) {
        cout << "ERROR: cannot load jetpack.png" << endl;
    } else {
        sprite.setTexture(texture);
        sprite.setOrigin(texture.getSize().x / 2.0f, texture.getSize().y / 2.0f);
        
        sprite.setScale(0.18f, 0.18f);
    }
}

ShieldPower::ShieldPower(int ln, float spd) : PowerUp(ln, spd) {
    if (!texture.loadFromFile("/home/maham/Downloads/OOP-project/Images/shield.png")) {
        cout << "ERROR: cannot load shield.png" << endl;
    } else {
        sprite.setTexture(texture);
        sprite.setOrigin(texture.getSize().x / 2.0f, texture.getSize().y / 2.0f);
        
        sprite.setScale(0.18f, 0.18f);
    }
}

DoubleCoinPower::DoubleCoinPower(int ln, float spd) : PowerUp(ln, spd) {
    if (!texture.loadFromFile("/home/maham/Downloads/OOP-project/Images/doublecoin.png")) {
        cout << "ERROR: cannot load doublecoin.png" << endl;
    } else {
        sprite.setTexture(texture);
        sprite.setOrigin(texture.getSize().x / 2.0f, texture.getSize().y / 2.0f);
        sprite.setScale(0.25f, 0.25f);
    }
}
//it Calls the corresponding Player method.
//This is polymorphism  can store a bunch of PowerUp* in a list and call applyEffect

void MagnetPower::applyEffect(Player* player) {
    player->activateMagnet();
    //cout << "MAGNET collected - 8 seconds!" << endl;
}

void JetpackPower::applyEffect(Player* player) {
    player->activateJetpack();
    //cout << "JETPACK collected - 6 seconds!" << endl;
}

void ShieldPower::applyEffect(Player* player) {
    player->activateShield();
    //cout << "SHIELD collected - 10 seconds!" << endl;
}

void DoubleCoinPower::applyEffect(Player* player) {
    player->activateDoubleCoin();
    //cout << "DOUBLE COIN collected! 2x points for 10 seconds!" << endl;
}
