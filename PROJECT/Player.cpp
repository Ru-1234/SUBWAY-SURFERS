#include "Player.h"
#include <iostream>
using namespace std;
using namespace sf;

float laneX(int lane) {  //calc horizontal position of player based on lanes 
    return 140.0f + lane * 270.0f;
}

Player::Player() {
    currentLane = 1;
    x = laneX(currentLane); //checks the current lane of players and then assigns poweruos etc 
    baseY = 450.0f;
    y = baseY;

    state = RUNNING;
    jumpVelocity = 0.0f;
    gravity = 1200.0f;

    // Power-up states
    hasShield = false;
    hasMagnet = false;
    hasJetpack = false;
    hasDoubleCoin = false;

    // Power-up timers
    shieldTimer = magnetTimer = jetpackTimer = doubleCoinTimer = 0.0f;

    // Animation
    animationFrame = 0;
    animationTimer = 0.0f;

    textureLoaded = playerTexture.loadFromFile("/home/maham/Downloads/OOP-project/Images/player.png");
    if (!textureLoaded) {
        cout << "ERROR: Could not load player.png. Using rectangle.\n";
        shape.setSize(Vector2f(40.0f, 60.0f));
        shape.setFillColor(Color::Yellow);
        shape.setPosition(x, y);
    } else {
        playerSprite.setTexture(playerTexture);
        playerSprite.setScale(0.35f, 0.35f);
        playerSprite.setPosition(x, y);
    }

//Shield
    shieldVisual.setRadius(45.0f);
    shieldVisual.setFillColor(Color(100, 200, 255, 100));
    shieldVisual.setOutlineThickness(3.0f);
    shieldVisual.setOutlineColor(Color(0, 150, 255, 200));
    shieldVisual.setOrigin(45.0f, 45.0f);
//Magnet
    magnetVisual.setRadius(30.0f);
    magnetVisual.setFillColor(Color(255, 0, 0, 50));
    magnetVisual.setOutlineThickness(2.0f);
    magnetVisual.setOutlineColor(Color(255, 0, 0, 150));
    magnetVisual.setOrigin(30.0f, 30.0f);
//Jetpack
    jetpackVisual.setRadius(35.0f);
    jetpackVisual.setFillColor(Color(255, 165, 0, 50));
    jetpackVisual.setOutlineThickness(2.0f);
    jetpackVisual.setOutlineColor(Color(255, 165, 0, 150));
    jetpackVisual.setOrigin(35.0f, 35.0f);
//Double coin
    doubleCoinVisual.setRadius(25.0f);
    doubleCoinVisual.setFillColor(Color(255, 255, 0, 50));
    doubleCoinVisual.setOutlineThickness(2.0f);
    doubleCoinVisual.setOutlineColor(Color(255, 255, 0, 150));
    doubleCoinVisual.setOrigin(25.0f, 25.0f);
}
//movement of players across lines 
void Player::moveLeft() {
    if (currentLane > 0) { currentLane--; x = laneX(currentLane); }
}

void Player::moveRight() {
    if (currentLane < 2) { currentLane++; x = laneX(currentLane); }
}

void Player::jump() {
    if (state == RUNNING) {state = JUMPING;jumpVelocity = -600.0f;}
}

void Player::slide() {
    if (state == RUNNING) {state = SLIDING;}
}

void Player::update(float deltaTime) {
    animationTimer += deltaTime; //updates power up timers when active then disables
    if (animationTimer >= 0.1f) {
        animationFrame = (animationFrame + 1) % 4;
        animationTimer = 0.0f;
    }

    // Update power-up timers
    if (hasShield) {
        shieldTimer -= deltaTime;
        if (shieldTimer <= 0.0f) hasShield = false;
    }
    if (hasMagnet) {
        magnetTimer -= deltaTime;
        if (magnetTimer <= 0.0f) hasMagnet = false;
    }
    if (hasJetpack) {
        jetpackTimer -= deltaTime;
        if (jetpackTimer <= 0.0f) hasJetpack = false;
    }
    if (hasDoubleCoin) {
        doubleCoinTimer -= deltaTime;
        if (doubleCoinTimer <= 0.0f) hasDoubleCoin = false;
    }

    if (hasJetpack && state == JUMPING) {
        // Reducing gravity for floating effect
        jumpVelocity += (gravity * 0.5f) * deltaTime; // 50% less
    } else if (state == JUMPING) {
        jumpVelocity += gravity * deltaTime;
    }

    if (state == JUMPING) {
        y += jumpVelocity * deltaTime;

        if (y >= baseY) {
            y = baseY;
            state = RUNNING;
            jumpVelocity = 0.0f;
        }
    }

    if (state == SLIDING) {
        if (animationFrame == 0 && animationTimer < 0.01f) {
            state = RUNNING;
        }
    }

    if (textureLoaded) {
        if (state == SLIDING)
            playerSprite.setScale(0.35f, 0.2f);
        else
            playerSprite.setScale(0.35f, 0.35f);

        playerSprite.setPosition(x - playerSprite.getGlobalBounds().width / 2, y);
    } else {
        shape.setPosition(x - shape.getSize().x / 2, y);
    }

    shieldVisual.setPosition(x, y);
    magnetVisual.setPosition(x, y);
    jetpackVisual.setPosition(x, y);
    doubleCoinVisual.setPosition(x, y);
}

void Player::render(RenderWindow& window) {
    if (textureLoaded)
        window.draw(playerSprite);
    else
        window.draw(shape);
    if (hasMagnet) {
        window.draw(magnetVisual);
    }
    if (hasJetpack) {
        window.draw(jetpackVisual);
    }
    if (hasDoubleCoin) {
        window.draw(doubleCoinVisual);
    }
    if (hasShield) {
        window.draw(shieldVisual);
    }
}

FloatRect Player::getBounds() const {
    if (textureLoaded)
        return playerSprite.getGlobalBounds();
    else
        return shape.getGlobalBounds();
}
void Player::reset() {
    currentLane = 1;
    x = laneX(currentLane);
    y = baseY;
    state = RUNNING;
    jumpVelocity = 0.0f;
    
    hasShield = hasMagnet = hasJetpack = hasDoubleCoin = false;
    shieldTimer = magnetTimer = jetpackTimer = doubleCoinTimer = 0.0f;
    
    animationFrame = 0;
    animationTimer = 0.0f;

    if (textureLoaded) {
        playerSprite.setPosition(x - playerSprite.getGlobalBounds().width / 2, y);
        playerSprite.setScale(0.35f, 0.35f);
    } else {
        shape.setPosition(x - shape.getSize().x / 2, y);
    }
    
    shieldVisual.setPosition(x - 5.0f, y - 5.0f);
}

void Player::activateShield() {
    hasShield = true;
    shieldTimer = 10.0f;
    //cout << "Shield activated for 10 seconds!" << endl;
}

void Player::activateMagnet() {
    hasMagnet = true;
    magnetTimer = 8.0f;
    //cout << "Magnet activated for 8 seconds!" << endl;
}

void Player::activateJetpack() {
    hasJetpack = true;
    jetpackTimer = 6.0f;
    //cout << "Jetpack activated for 6 seconds! Higher jumps!" << endl;
}

void Player::activateDoubleCoin() {
    hasDoubleCoin = true;
    doubleCoinTimer = 10.0f;
    //cout << "Double Coin activated for 10 seconds!" << endl;
}
