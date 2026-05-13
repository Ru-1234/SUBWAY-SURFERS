#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp> 
#include "Player.h"
#include "TrackManager.h"
#include "ScoreManager.h"
using namespace std;
using namespace sf;

enum GameState {START_SCREEN, MENU, NAME_INPUT, PLAYING, LEADERBOARD, INSTRUCTIONS, GAME_OVER};

class GameEngine {
private:
    //creating objects
    RenderWindow window;
    Player player;
    TrackManager trackManager;
    ScoreManager scoreManager;
    GameState state;
    Clock clock;
    Font font;

    int choice = 0;                         //Currently at Startting Screen
    float survivalTimer;
    float speedIncreaseTimer;
    bool fontLoaded;
    
    string playerNameInput;                 //name during input
    bool showCursor;                        //For blinking cursor
    float cursorTimer;                      //Timer for cursor blink

    Texture startBgTexture;    // For start
    Sprite startBgSprite;
    Texture menuBgTexture;     // For menu
    Sprite menuBgSprite;
    
    Music backgroundMusic; 
    
    RectangleShape lanes[3];
    RectangleShape background;
    float backgroundScrollOffset;
    
    void handleInput();
    void update(float deltaTime);
    void render();
    void checkCollisions();

    //Displayer functions
    void renderStartScreen();
    void renderMenu();
    void renderNameInput();
    void renderGame();
    void renderLeaderBoard();
    void renderInstructions();
    void renderGameOver();

    void initializeBackground();

public:
    GameEngine();
    void run();
};

#endif