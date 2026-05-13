#ifndef COIN_H
#define COIN_H
#include <SFML/Graphics.hpp>
using namespace sf;
using namespace std;

class Coin {
  private:
      float x, y;                    // x and y coordinates of coin
      int lane;                      // lane of coin
      float speed;                   // coin's vertical speed
      bool active;                  // if coin is collectable??????????
      float rotationAngle;          // for rotating coin effect
    //sfml
      Texture texture;
      Sprite sprite;
public:
    Coin(int ln, float spd);
//updates coin position and state
    void update(float deltaTime);
  //draws coin on window
    void render(RenderWindow& window);                  //Draws coin
    // Getters and setters
    bool isActive() const { return active; }
    void deactivate() { active = false; }
    FloatRect getBounds() const { return sprite.getGlobalBounds(); }
    int getLane() const { return lane; }
};

#endif

