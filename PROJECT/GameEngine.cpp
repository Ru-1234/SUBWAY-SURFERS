#include "GameEngine.h"
#include <iostream>
#include <sstream>
using namespace std;
using namespace sf;

GameEngine::GameEngine(): window(VideoMode(800, 600), "SUBWAY SURFERS"), state(START_SCREEN), survivalTimer(0.0f), speedIncreaseTimer(0.0f), 
      backgroundScrollOffset(0.0f), fontLoaded(false), showCursor(true), cursorTimer(0.0f) {
    window.setFramerateLimit(60);

    if (font.loadFromFile("/home/maham/Downloads/OOP-project/arial.ttf")) {
        fontLoaded = true;
    }
    
    if (!startBgTexture.loadFromFile("/home/maham/Downloads/OOP-project/Images/bgg.png")) {
        cout << "ERROR: Could not load bgg.png" << endl;
    }
    startBgSprite.setTexture(startBgTexture);
    startBgSprite.setScale(800.0f / startBgTexture.getSize().x, 600.0f / startBgTexture.getSize().y);

    if (!menuBgTexture.loadFromFile("/home/maham/Downloads/OOP-project/Images/bg.png")) {
        cout << "ERROR: Could not load bg.png" << endl;
    }
    menuBgSprite.setTexture(menuBgTexture); //GAME STARTING SCREEN
    menuBgSprite.setScale(800.0f / menuBgTexture.getSize().x, 600.0f / menuBgTexture.getSize().y);

    if (backgroundMusic.openFromFile("/home/maham/Downloads/OOP-project/assets/subway_music.ogg")) {
        backgroundMusic.setLoop(true);
        backgroundMusic.setVolume(30);
        backgroundMusic.play();
    }

    initializeBackground();
}

void GameEngine::initializeBackground() {
    background.setSize(Vector2f(800.0f, 600.0f));
    background.setFillColor(Color(40, 40, 60));

    for (int i = 0; i < 3; i++) {
        lanes[i].setSize(Vector2f(180.0f, 600.0f));
        lanes[i].setPosition(110.0f + i * 200.0f, 0.0f);
        lanes[i].setFillColor(Color(0, 0, 0, 0)); //transparant lanes 
    }
}

void GameEngine::handleInput() {
    Event event;
    while (window.pollEvent(event)) {
        if (event.type == Event::Closed) {
            backgroundMusic.stop();
            window.close();
        }

        if (state == START_SCREEN && event.type == Event::KeyPressed){
            if (event.key.code == Keyboard::Enter) {
                state = MENU;
            }
            else if (event.key.code == Keyboard::Escape) {
                backgroundMusic.stop();
                window.close();
            }
        }

        if (state == MENU && event.type == Event::KeyPressed) {
            if (event.key.code == Keyboard::Num1) {
                state = NAME_INPUT;
                playerNameInput = "";
                choice = 1;
            }
            else if (event.key.code == Keyboard::Num2) {
                if (scoreManager.getPlayerName()[0] == '\0') {
                    state = NAME_INPUT;
                    choice = 2;
                } else {
                    state = PLAYING;
                    choice = 2;
                    trackManager.reset();
                    player.reset();
                    survivalTimer = 0.0f;
                    speedIncreaseTimer = 0.0f;
                }
            }
            else if (event.key.code == Keyboard::Num3) {
                choice = 3;
                state = LEADERBOARD;
            }
            else if (event.key.code == Keyboard::Num4) {
                choice = 4;
                state = INSTRUCTIONS;
            }
            else if (event.key.code == Keyboard::Num5) {
                backgroundMusic.stop();
                window.close();
            }
        }

        // Name input -  backspace
        if (state == NAME_INPUT && event.type == Event::TextEntered) {
            // Backspace 
            if (event.text.unicode == 8) {
                if (playerNameInput.length() > 0) {
                    // make string shorter by 1 character
                    int len = playerNameInput.length();
                    playerNameInput = playerNameInput.substr(0, len - 1);
                }
            }
            // Enter key
            else if (event.text.unicode == 13) {
                if (playerNameInput == "") {
                    playerNameInput = "Player";
                }
                
                scoreManager.setPlayerName(playerNameInput.c_str());
                
                if (choice == 1) {
                    state = PLAYING;
                    trackManager.reset();
                    scoreManager.reset();
                    player.reset();
                    survivalTimer = 0.0f;
                    speedIncreaseTimer = 0.0f;
                }
                else if (choice == 2) {
                    state = PLAYING;
                    trackManager.reset();
                    player.reset();
                    survivalTimer = 0.0f;
                    speedIncreaseTimer = 0.0f;
                }
            }
            else if (event.text.unicode >= 32 && event.text.unicode < 128) {
                if (playerNameInput.length() < 20) {
                    playerNameInput = playerNameInput + (char)event.text.unicode;
                }
            }
        }

        if (state == NAME_INPUT && event.type == Event::KeyPressed) {
            if (event.key.code == Keyboard::Escape) {
                state = MENU;
                playerNameInput = "";
            }
        }

        if (state == PLAYING && event.type == Event::KeyPressed) {
            if (event.key.code == Keyboard::A)  player.moveLeft();
            if (event.key.code == Keyboard::D)  player.moveRight();
            if (event.key.code == Keyboard::W)  player.jump();
            if (event.key.code == Keyboard::S)  player.slide();
            
            if (event.key.code == Keyboard::Escape) {
                state = MENU;
            }
        }

        if ((state == GAME_OVER || state == INSTRUCTIONS || state == LEADERBOARD) && event.type == Event::KeyPressed) {
            if (event.key.code == Keyboard::Space || event.key.code == Keyboard::Escape) {
                state = MENU; 
                choice = 0;
            }
        }
    }
}

void GameEngine::update(float deltaTime) {
    if (state == START_SCREEN || state == NAME_INPUT) {
        if (state == NAME_INPUT) {
            cursorTimer += deltaTime;
            if (cursorTimer >= 0.5f) {
                showCursor = !showCursor;
                cursorTimer = 0.0f;
            }
        }
        return;
    }
    
    if (state == PLAYING) {
        player.update(deltaTime);
        trackManager.update(deltaTime);

        survivalTimer += deltaTime;
        if (survivalTimer >= 1.0f) {
            scoreManager.addPoints(10);
            survivalTimer = 0.0f;
        }

        speedIncreaseTimer += deltaTime;
        if (speedIncreaseTimer >= 10.0f) {
            trackManager.increaseSpeed(20.0f);
            speedIncreaseTimer = 0.0f;
        }

        backgroundScrollOffset += trackManager.getCurrentSpeed() * deltaTime * 0.5f;
        if (backgroundScrollOffset >= 600.0f) {
            backgroundScrollOffset = 0.0f;
        }

        checkCollisions();
    }
}

void GameEngine::checkCollisions() {
    FloatRect playerBounds = player.getBounds();

    int obsCount = trackManager.getObstacles().getSize();
    for (int i = obsCount - 1; i >= 0; i--) {
        Obstacle* obs = trackManager.getObstacles().get(i);
        if (obs && obs->isActive() && obs->getLane() == player.getLane()) {
            if (playerBounds.intersects(obs->getBounds())) {
                bool avoided = false;

                if (player.getState() == JUMPING && obs->canJumpOver())
                    avoided = true;
                if (player.getState() == SLIDING && obs->canSlideUnder())
                    avoided = true;

                if (!avoided) {
                    if (player.isShielded()) {
                        obs->deactivate();
                    } else {
                        state = GAME_OVER;
                        return;
                    }
                }
            }
        }
    }

    // Check coins
    int coinCount = trackManager.getCoins().getSize();
    for (int i = coinCount - 1; i >= 0; i--) {
        Coin* coin = trackManager.getCoins().get(i);
        if (coin && coin->isActive()) {
            FloatRect coinBounds = coin->getBounds();

            if (player.hasActiveMagnet()) {
                float dx = playerBounds.left - coinBounds.left;
                if (dx < 100.0f && dx > -100.0f) {
                    coin->deactivate();
                    scoreManager.addPoints(player.hasActiveDoubleCoin() ? 100 : 50);
                }
            }

            if (coin->getLane() == player.getLane() && playerBounds.intersects(coinBounds)) {
                coin->deactivate();
                scoreManager.addPoints(player.hasActiveDoubleCoin() ? 100 : 50);
            }
        }
    }
    
    // Check power-ups
    int powerCount = trackManager.getPowerUps().getSize();
    for (int i = powerCount - 1; i >= 0; i--) {
        PowerUp* pw = trackManager.getPowerUps().get(i);
        if (pw && pw->isActive()) {
            FloatRect powerUpBounds = pw->getBounds();
            
            if (playerBounds.intersects(powerUpBounds)) {
                pw->applyEffect(&player);
                scoreManager.addPoints(100);
                pw->deactivate();
            }
        }
    }
}

void GameEngine::render() {
    window.clear();

    switch (state) {
        case START_SCREEN: renderStartScreen(); break;
        case MENU:         renderMenu(); break;
        case NAME_INPUT:   renderNameInput(); break;
        case PLAYING:      renderGame(); break;
        case LEADERBOARD:  renderLeaderBoard(); break;
        case INSTRUCTIONS: renderInstructions(); break;
        case GAME_OVER:    renderGameOver(); break;
    }
    window.display();
}

void GameEngine::renderStartScreen() {
    window.draw(startBgSprite);
    
    if (fontLoaded) {
        Text startText("PRESS ENTER TO START", font, 30);
        startText.setStyle(Text::Bold);
        startText.setFillColor(Color::Black);
        
        FloatRect textBounds = startText.getLocalBounds();
        startText.setPosition(400.0f - textBounds.width / 2.0f,500.0f);
        window.draw(startText);
        
        Text exitText("Press ESC to Exit", font, 20);
        exitText.setFillColor(Color::Black);
        exitText.setPosition(10.0f, 570.0f);
        window.draw(exitText);
    }
}

void GameEngine::renderMenu() {
    window.draw(menuBgSprite);
    
    if (fontLoaded) {
        Text title("SUBWAY SURFERS", font, 50);
        title.setFillColor(Color::Yellow);
        title.setPosition(225.0f, 130.0f);

        RectangleShape box;
        box.setFillColor(Color(0, 0, 0, 180));
        box.setSize(Vector2f(title.getLocalBounds().width + 40, title.getLocalBounds().height + 40));
        box.setPosition(title.getPosition().x - 20, title.getPosition().y - 20);

        window.draw(box);
        window.draw(title);

        Text menu("1- Start Game\n2- Continue\n3- LeaderBoard\n4- Instructions\n5- Exit", font, 35);
        menu.setFillColor(Color::White);
        menu.setPosition(280.0f, 200.0f);
        window.draw(menu);
    }
}

void GameEngine::renderNameInput() {
    window.clear(Color(173, 216, 230));
    
    RectangleShape titleBox(Vector2f(500.0f, 400.0f));
    titleBox.setFillColor(Color(255, 255, 255, 200));
    titleBox.setOutlineThickness(3.0f);
    titleBox.setOutlineColor(Color(30, 144, 255));
    titleBox.setPosition(150.0f, 100.0f);
    window.draw(titleBox);
    
    if (fontLoaded) {
        Text title("ENTER YOUR NAME", font, 40);
        title.setStyle(Text::Bold);
        title.setFillColor(Color(30, 144, 255));
        FloatRect titleBounds = title.getLocalBounds();
        title.setPosition(400.0f - titleBounds.width / 2.0f, 130.0f);
        window.draw(title);
        
        RectangleShape inputBox(Vector2f(400.0f, 50.0f));
        inputBox.setFillColor(Color(240, 248, 255));
        inputBox.setOutlineThickness(2.0f);
        inputBox.setOutlineColor(Color(30, 144, 255));
        inputBox.setPosition(200.0f, 220.0f);
        window.draw(inputBox);
        
        Text nameText(playerNameInput, font, 30);
        nameText.setFillColor(Color::Black);
        FloatRect nameBounds = nameText.getLocalBounds();
        nameText.setPosition(200.0f + 10.0f, 225.0f);
        
        if (nameBounds.width > 380.0f) {
            nameText.setPosition(580.0f - nameBounds.width, 225.0f);
        }
        window.draw(nameText);
        
        if (showCursor) {
            RectangleShape cursor(Vector2f(2.0f, 30.0f));
            cursor.setFillColor(Color::Black);
            float cursorX = 200.0f + 10.0f + nameBounds.width;
            cursor.setPosition(cursorX, 225.0f);
            window.draw(cursor);
        }
        
        Text instruction1("Type your name and press ENTER to confirm", font, 20);
        instruction1.setFillColor(Color(70, 130, 180));
        FloatRect instr1Bounds = instruction1.getLocalBounds();
        instruction1.setPosition(400.0f - instr1Bounds.width / 2.0f, 290.0f);
        window.draw(instruction1);
        
        Text instruction2("Press ESC to return to menu", font, 18);
        instruction2.setFillColor(Color(119, 136, 153));
        FloatRect instr2Bounds = instruction2.getLocalBounds();
        instruction2.setPosition(400.0f - instr2Bounds.width / 2.0f, 320.0f);
        window.draw(instruction2);
        
        Text charLimit("Max 20 characters", font, 16);
        charLimit.setFillColor(Color(169, 169, 169));
        charLimit.setPosition(400.0f - charLimit.getLocalBounds().width / 2.0f, 360.0f);
        window.draw(charLimit);
        
        if (choice == 1) {
            Text modeText("Starting New Game", font, 18);
            modeText.setFillColor(Color(50, 205, 50));
            modeText.setPosition(400.0f - modeText.getLocalBounds().width / 2.0f, 400.0f);
            window.draw(modeText);
        }
        else if (choice == 2) {
            Text modeText("Continuing Game", font, 18);
            modeText.setFillColor(Color(255, 140, 0));
            modeText.setPosition(400.0f - modeText.getLocalBounds().width / 2.0f, 400.0f);
            window.draw(modeText);
        }
    }
}

void GameEngine::renderLeaderBoard() {
    window.draw(menuBgSprite);

    Text title("LEADER BOARD", font, 35);
    title.setFillColor(Color::Yellow);
    title.setPosition(220.0f, 130.0f);
    window.draw(title);
    
    Text currentPlayer("Current Player: " + string(scoreManager.getPlayerName()), font, 25);
    currentPlayer.setFillColor(Color::Cyan);
    currentPlayer.setPosition(250.0f, 200.0f);
    window.draw(currentPlayer);
    
    Text currentScore("Current Score: " + to_string(scoreManager.getCurrentScore()), font, 25);
    currentScore.setFillColor(Color::White);
    currentScore.setPosition(250.0f, 240.0f);
    window.draw(currentScore);

    ostringstream hss;
    hss << "High Score: " << scoreManager.getHighScore();
    Text highScore(hss.str(), font, 30);
    highScore.setFillColor(Color::Green);
    highScore.setPosition(250.0f, 300.0f);
    window.draw(highScore);
    
    if (scoreManager.getHighScoreName()[0] != '\0') {
        Text highScoreName("By: " + string(scoreManager.getHighScoreName()), font, 25);
        highScoreName.setFillColor(Color::Magenta);
        highScoreName.setPosition(250.0f, 350.0f);
        window.draw(highScoreName);
    }
    
    Text instruction("Press SPACE or ESC to return to menu", font, 20);
    instruction.setFillColor(Color::White);
    instruction.setPosition(230.0f, 450.0f);
    window.draw(instruction);
}

void GameEngine::renderInstructions() {
    window.draw(menuBgSprite);

    Text title("INSTRUCTIONS", font, 35);
    title.setStyle(Text::Bold);
    title.setFillColor(Color::Yellow);
    title.setPosition(220.0f, 130.0f);
    window.draw(title);

    Text instructions("A/D - Left/Right\nW/S - Jump/Slide", font, 25);
    instructions.setFillColor(Color::Magenta);
    instructions.setPosition(200.0f, 200.0f);
    window.draw(instructions);
}

void GameEngine::renderGame() {
    window.draw(menuBgSprite);
    
    trackManager.renderBackground(window, backgroundScrollOffset);

    for (int i = 0; i < trackManager.getCoins().getSize(); i++) {
        Coin* coin = trackManager.getCoins().get(i);
        if (coin) coin->render(window);
    }

    for (int i = 0; i < trackManager.getPowerUps().getSize(); i++) {
        PowerUp* pw = trackManager.getPowerUps().get(i);
        if (pw) pw->render(window);
    }

    for (int i = 0; i < trackManager.getObstacles().getSize(); i++) {
        Obstacle* obs = trackManager.getObstacles().get(i);
        if (obs) obs->render(window);
    }

    player.render(window);

    if (fontLoaded) {
        ostringstream oss;
        oss << "Score: " << scoreManager.getCurrentScore();
        Text scoreText(oss.str(), font, 25);
        scoreText.setFillColor(Color::White);
        scoreText.setPosition(10.0f, 10.0f);
        window.draw(scoreText);

        ostringstream speedOss;
        speedOss << "Speed: " << (int)(trackManager.getCurrentSpeed());
        Text speedText(speedOss.str(), font, 20);
        speedText.setFillColor(Color::Cyan);
        speedText.setPosition(10.0f, 45.0f);
        window.draw(speedText);
    }
}

void GameEngine::renderGameOver() {
    renderGame();

    RectangleShape overlay(Vector2f(800.0f, 600.0f));
    overlay.setFillColor(Color(0, 0, 0, 180));
    window.draw(overlay);

    if (fontLoaded) {
        Text gameOver("GAME OVER", font, 60);
        gameOver.setFillColor(Color::Red);
        gameOver.setPosition(220.0f, 150.0f);
        window.draw(gameOver);
        
        Text playerNameText("Player: " + string(scoreManager.getPlayerName()), font, 25);
        playerNameText.setFillColor(Color::Cyan);
        playerNameText.setPosition(280.0f, 240.0f);
        window.draw(playerNameText);

        ostringstream oss;
        oss << "Final Score: " << scoreManager.getCurrentScore();
        Text finalScore(oss.str(), font, 30);
        finalScore.setFillColor(Color::Yellow);
        finalScore.setPosition(250.0f, 280.0f);
        window.draw(finalScore);

        ostringstream hss;
        hss << "High Score: " << scoreManager.getHighScore();
        Text highScore(hss.str(), font, 25);
        highScore.setFillColor(Color::Green);
        highScore.setPosition(270.0f, 330.0f);
        window.draw(highScore);
        
        if (scoreManager.getHighScoreName()[0] != '\0') {
            Text highScoreHolder("Holder: " + string(scoreManager.getHighScoreName()), font, 20);
            highScoreHolder.setFillColor(Color::Magenta);
            highScoreHolder.setPosition(280.0f, 370.0f);
            window.draw(highScoreHolder);
        }

        Text restart("Press SPACE or ESC to return to menu", font, 20);
        restart.setFillColor(Color::White);
        restart.setPosition(230.0f, 450.0f);
        window.draw(restart);
    }
}

void GameEngine::run() {
    while (window.isOpen()) {
        float deltaTime = clock.restart().asSeconds();
        if (deltaTime > 0.1f) deltaTime = 0.1f;

        update(deltaTime);
        handleInput();
        render();
    }
}
