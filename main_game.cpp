#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <cmath>
#include <sstream>
#include <string>
#include <cstdlib>

#define START 0
#define RUNNING 2
#define PAUSE 3
#define GAMEOVER 4
#define MENU 5
const int inPlay = 1;
const int inAbout = 2;
const int inInstruction = 3;

float width = 20.0, height = 100.0;
int ScreenWidth = 700, ScreenHeight = 600;
float velocity = 2.0;
float ballVelocity =0.05 * 0.01;
float y_dir = 0.5 * sin(((ScreenHeight / 2) - 30) * 3.14 / 180);
float x_dir = 0.5 * cos(((ScreenWidth / 2) -30) * 3.14 / 180 );
float ballx, bally, padle1x, padle1y, padle2x, padle2y;
int points1 = 0, points2 = 0;

int gameState = 0, menuKaState = -1;

int main(){
    sf::RenderWindow window(sf::VideoMode(ScreenWidth, ScreenHeight), "PING PONG");

    /* All Texts */
    sf::Font f;
    f.loadFromFile("tahoma.ttf");

    // Game Heading
    sf::Text gameHeading;
    gameHeading.setFont(f);
    gameHeading.setString("Ping Pong");
    gameHeading.setPosition(ScreenWidth/10, ScreenHeight/2 - 100);
    gameHeading.setColor(sf::Color::Yellow);
    gameHeading.setCharacterSize(65);

    // Menu Text
    sf::Text menuText;
    menuText.setFont(f);
    menuText.setString("Press Accordingly\n[P] - Play\n[I] - Instruction\n[A] - About\n[ESC] - Exit the Game.");
    menuText.setColor(sf::Color::Black);
    menuText.setPosition(sf::Vector2f(30,ScreenHeight/20));
    menuText.setCharacterSize(30);

    // in MENU - About us
    sf:: Text aboutUs;
    aboutUs.setFont(f);
    aboutUs.setPosition(sf::Vector2f(ScreenWidth/2-ScreenWidth/3, ScreenHeight/2-ScreenHeight/3));
    aboutUs.setCharacterSize(30);
    aboutUs.setColor(sf::Color::Blue);
    aboutUs.setString("-----------------------------------\nCoded By :\n \tPriyash Yagnik\nGame Version : 1.0\nAll Rights Reserved\n-----------------------------------");

    // Showing points
    std::stringstream pstore1, pstore2;
    sf::Text point1, point2;
    point1.setFont(f);
    point2.setFont(f);
    point1.setPosition(sf::Vector2f(ScreenWidth/5, 5));
    point2.setPosition(sf::Vector2f(ScreenWidth - ScreenWidth/5, 5));
    point1.setColor(sf::Color::Yellow);
    point2.setColor(sf::Color::Yellow);
    point1.setCharacterSize(30);
    point2.setCharacterSize(30);

    // Pause text
    sf::Text pauseText;
    pauseText.setFont(f);
    pauseText.setString("The Game Has been Paused !");
    pauseText.setPosition(ScreenWidth/10, ScreenHeight/2);
    pauseText.setColor(sf::Color(120, 50, 240));

    // To start text
    sf::Text toStart;
    toStart.setFont(f);
    toStart.setString("Press any KEY to start the Game .");
    toStart.setPosition(ScreenWidth/10, ScreenHeight/2);
    toStart.setColor(sf::Color(255,150,250));

    // Winner
    sf::Text winnerText;
    winnerText.setFont(f);
    winnerText.setPosition(sf::Vector2f(20,ScreenHeight/10));
    winnerText.setCharacterSize(55);
    winnerText.setColor(sf::Color::Black);

    // Gameover's instruction
    sf::Text lastInstruction;
    lastInstruction.setFont(f);
    lastInstruction.setColor(sf::Color::Blue);
    lastInstruction.setPosition(sf::Vector2f(20,ScreenHeight - ScreenHeight/10));
    lastInstruction.setCharacterSize(17);

    /* All texts end */

    /* Textures */

    // Staring textures
    sf::Texture gameStartTexture;
    gameStartTexture.loadFromFile("game_start.png");
    sf::Sprite gameStartSprite;
    gameStartSprite.setTexture(gameStartTexture);
    gameStartSprite.setScale(5, 5);
    gameStartSprite.setOrigin(sf::Vector2f(300,300));

    // Instructions.
    sf::Texture inst;
    inst.loadFromFile("instructions.png");
    sf::Sprite instruct;
    instruct.setTexture(inst);
    instruct.setScale(0.80f, 1.32f);

    /* Texture end . */

    /* playing objects. */
    // this is padle 1
    sf::RectangleShape padle(sf::Vector2f(width, height));
    padle.setFillColor(sf::Color::Cyan);
    padle.setPosition(5, 240);


    // this is padle 2.
    sf::RectangleShape padle2(sf::Vector2f(width, height));
    padle2.setFillColor(sf::Color::Cyan);
    padle2.setPosition(ScreenWidth - 25 , 240);

    // this is the ball.
    sf::CircleShape ball(7);
    ball.setFillColor(sf::Color(255, 255, 255));
    ball.setPosition( ScreenWidth/2, (ScreenHeight - 10)/2 );
    /* playing objects end */

    while(window.isOpen()){

        sf::Event event;

        while(window.pollEvent(event)){
            if(event.type == sf::Event::Closed)
                window.close();

            /* Check for game of state */
            if(event.type == sf::Event::KeyPressed){
                switch(gameState){

                  case START:
                    gameState = MENU;
                    break;

                  case MENU:
                    if(event.key.code == sf::Keyboard::Escape){
                        if(menuKaState != -1)
                          menuKaState = -1;
                        else
                          window.close();
                    }else if(event.key.code == sf::Keyboard::P){
                        menuKaState = inPlay;
                    }else if(event.key.code == sf::Keyboard::A){
                        menuKaState = inAbout;
                    }else if(event.key.code == sf::Keyboard::I){
                        menuKaState = inInstruction;
                    }
                    break;

                  case RUNNING:
                    if(event.key.code == sf::Keyboard::Escape){
                        gameState = PAUSE;
                    }
                    break;

                  case PAUSE:
                    if(event.key.code == sf::Keyboard::Escape){
                        gameState = RUNNING;
                    }else if(event.key.code == sf::Keyboard::R){
                        gameState = MENU;
                    }
                    break;

                  case GAMEOVER:
                    if(event.key.code == sf::Keyboard::Escape)
                        window.close();
                    else if(event.key.code == sf::Keyboard::R){
                        points1 = points2 = 0;
                        gameState = MENU;
                    }
                    break;
                }




                /*
                if(gameState == START){
                    gameState = MENU;
                    break;
                }
                if(event.key.code == sf::Keyboard::Escape){
                    if(gameState == RUNNING)
                        gameState = PAUSE;
                    else if(gameState == PAUSE)
                        gameState = RUNNING;
                    else if(gameState == GAMEOVER)
                        window.close();
                    else if(gameState == MENU && menuKaState != -1){
                        menuKaState = -1;
                    }
                }

                if(event.key.code == sf::Keyboard::R){
                    if(gameState == GAMEOVER){
                        points1 = points2 = 0;
                        gameState = START;
                    }
                }
                if(gameState == MENU){
                    if(event.key.code == sf::Keyboard::P){
                        menuKaState = inPlay;
                    }else if(event.key.code == sf::Keyboard::A){
                        menuKaState = inAbout;
                    }else if(event.key.code == sf::Keyboard::I){
                        menuKaState = inInstruction;
                    }

                }*/

            }


            /*switch(gameState){
              case RUNNING:
                if(event.key.code == sf::Keyboard::Escape)
                    gameState = PAUSE;
                break;
              case PAUSE:
                if(event.key.code == sf::Keyboard::Escape)
                    gameState = RUNNING;
                break;

              case START:
                gameState = RUNNING;
                break;
            }*/
            /* Check for game of state end */
        }

        point1.setString(pstore1.str());
        point2.setString(pstore2.str());

        switch(gameState){

          case START:
            int a,b,c;
            a = 154 + rand()%100;
            b = 128 + rand()%127;
            c = rand()%256;
            window.clear(sf::Color::Black);
            window.draw(gameStartSprite);
            window.draw(gameHeading);
            window.draw(toStart);
            window.display();
            toStart.setColor(sf::Color(a, b, c));
            gameStartSprite.rotate(0.02);
            break;

          case MENU:
            switch(menuKaState){
              case inPlay:
                menuKaState = -1;
                gameState = RUNNING;
                break;
              case inAbout:
                window.clear(sf::Color::White);
                window.draw(aboutUs);
                lastInstruction.setString("Press [ESC] to go back to menu.");
                window.draw(lastInstruction);
                window.display();
                break;
              case inInstruction:
                window.clear();
                window.draw(instruct);
                window.display();
                break;
              default:
                window.clear(sf::Color(255, 158, 80));
                window.draw(menuText);
                window.display();
            }
            break;

          /*case INSTRUCTIONS:
            window.clear();
            window.draw(instruct);
            window.display();
         //   sf::sleep(sf::seconds(5));
         //   gameState = RUNNING;
            break;*/

          case RUNNING:

            if(points1 > 6){
                winnerText.setString("Player 1 is the winner !!");
                gameState = GAMEOVER;
            }else if(points2 > 6){
                winnerText.setString("Player 2 is the winner !!");
                gameState = GAMEOVER;
            }

            /* Game Logic */
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && padle2.getPosition().y >= 15){
                padle2.move(sf::Vector2f(0, velocity * -0.4));
                padle2.setFillColor(sf::Color::Black);
            }else if(sf::Keyboard::isKeyPressed(sf::Keyboard::W) && padle.getPosition().y >=15){
                padle.move(sf::Vector2f(0, velocity * -0.4));
                padle.setFillColor(sf::Color::Black);
            }else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && padle2.getPosition().y <= ScreenHeight - height -15){
                padle2.move(sf::Vector2f(0, velocity * 0.4));
                padle2.setFillColor(sf::Color::Black);
            }else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S) && padle.getPosition().y <= ScreenHeight - height -15){
                padle.move(sf::Vector2f(0, velocity * 0.4));
                padle.setFillColor(sf::Color::Black);
            }

            if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                padle.setFillColor(sf::Color::Blue);
                padle2.setFillColor(sf::Color::Blue);
            }else{
                padle.setFillColor(sf::Color::Cyan);
                padle2.setFillColor(sf::Color::Cyan);
            }

            // Collision
            ballx = ball.getPosition().x;
            bally = ball.getPosition().y;
            padle1x = padle.getPosition().x;
            padle1y = padle.getPosition().y;
            padle2x = padle2.getPosition().x;
            padle2y = padle2.getPosition().y;

            if(bally > padle1y && bally < padle1y+height && ballx <= padle1x+width){
                x_dir = cos(ballVelocity * ballx * (3.14 / 180));
                y_dir = sin( padle1y - (ballVelocity * bally * (3.14 / 180)) );
            }
            if((bally > padle2y && bally < padle2y+height && ballx >= padle2x-width)){
                x_dir = -1 * cos( ballVelocity * ballx * (3.14 / 180) );
                y_dir = -1 * sin( padle2y - (ballVelocity * bally * (3.14 / 180)) );
            }

            // Points
            if(ballx < 0){
                points2++;
                ball.setPosition( ScreenWidth/2, (ScreenHeight - 10)/2 );
            }else if(ballx > ScreenWidth){
                points1++;
                ball.setPosition( ScreenWidth/2, (ScreenHeight - 10)/2 );
            }

            pstore1.str(std::string());
            pstore1.clear();
            pstore2.str(std::string());
            pstore2.clear();
            pstore1 << points1;
            pstore2 << points2;

            // Collision with wall.
            if(bally < 15 || bally > ScreenHeight - 15){
                y_dir = -1* y_dir;
            }

            // Movement of the ball
            ball.move(sf::Vector2f(0.5 * x_dir, 0.5 * y_dir));
            /* Game Logic end. */

            /* Display Each Frame */
            window.clear(sf::Color(100,150,100));
            window.draw(padle);
            window.draw(padle2);
            window.draw(ball);
            window.draw(point1);
            window.draw(point2);
            window.display();
            /* Display Each Frame */
            break;

          case PAUSE :
            window.draw(pauseText);
            lastInstruction.setString("Press [R] to restart.");
            window.draw(lastInstruction);
            window.display();
            break;

          case GAMEOVER:
            window.clear(sf::Color::White);
            window.draw(winnerText);
            lastInstruction.setString("Press [ESC] to exit and [R] to restart.");
            window.draw(lastInstruction);
            window.display();
            break;
        }
    }
    return 0;
}
