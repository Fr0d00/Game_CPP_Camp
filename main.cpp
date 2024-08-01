#include <SFML/Graphics.hpp>
#include <iostream>
#include "hpp_files/wall.hpp"
#include <unistd.h>
#include "hpp_files/enemy.hpp"

//coordinates structure
struct Point
{
    float x;
    float y;
    Point(int x = 0, int y = 0)
    {
        this->x = x;
        this->y = y;
    }
};

//cheking hit side for boxes (i don't use it)
bool checkHitSide(int charPosX, int charPosY, int posX, int posY, int scaleX, int scaleY)
{
    if ((charPosX > posX - scaleX / 2 && charPosX < posX + scaleX / 2) && charPosY > posY - scaleY)
    {
        return true;
    }
    else
    {
        return false;
    }
}

//main
int main()
{

    //variables
    float resM = 2.f;
    float yVel = 0.f;
    float yVel2 = 0.f;

    Point res(576 * resM, 256 * resM);
    Point charPos(200 * resM, 256 * resM);

    // gameMode 0 - game, gameMode 1 - menu, gameMode 2 - death, gameMode 3 - win
    int gameMode = 1;
    int earthPos = 256 * resM;
    int charVec = 1;
    int charHealth;
    int goblinsNum = 5; // + rand() % 3;
    int killsCounter = 0;

    bool gettingDamage = 0;

    //creating window
    sf::RenderWindow window(sf::VideoMode(res.x, res.y), "Game");
    window.setFramerateLimit(60);

    //damage zone
    sf::RectangleShape dmgZone(sf::Vector2f(60, 60));

    //creating textures
    sf::Texture tChar, tSword, tBox, tWallDown, tWallUp, tWallDoor, tDark, tHealth, tGoblin, tHell, tGameOver, tStart, tWon;
    tChar.loadFromFile("images/Knight/Knight.png");
    tSword.loadFromFile("images/Sword/Sword.png");
    tBox.loadFromFile("images/Box/Box.png");
    tWallDown.loadFromFile("images/Walls/WallDown.png");
    tWallUp.loadFromFile("images/Walls/WallUp.png");
    tWallDoor.loadFromFile("images/Walls/WallDownDoorClosed.png");
    tDark.loadFromFile("images/Darkness/Darkness.png");
    tHealth.loadFromFile("images/Health/HP.png");
    tGoblin.loadFromFile("images/Enemies/Goblin.png");
    tHell.loadFromFile("images/Enemies/Hell.png");
    tGameOver.loadFromFile("images/UI/YouDied.png");
    tStart.loadFromFile("images/UI/StartMenu.png");
    tWon.loadFromFile("images/UI/YouWon.png");

    //creating sprites
    sf::Sprite sChar(tChar), sSword(tSword), sDark(tDark), sHealth(tHealth), sGameOver(tGameOver), sStart(tStart), sWon(tWon);
    sChar.setScale(resM, resM);
    sSword.setScale(resM, resM);
    dmgZone.setScale(resM, resM);
    sDark.setScale(resM, resM);
    sHealth.setScale(resM / 2, resM / 2);
    sGameOver.setScale(resM, resM);
    sWon.setScale(resM, resM);
    sStart.setScale(resM, resM);

    //setting origins
    sChar.setOrigin(8, 28);
    sSword.setOrigin(3, 29);
    dmgZone.setOrigin(30, 30);

    //setting sword's rotation
    sSword.setRotation(0);

    //setting positions
    sChar.setPosition(charPos.x, charPos.y);
    sSword.setPosition(charPos.x, charPos.y);
    dmgZone.setPosition(charPos.x, charPos.y);
    sGameOver.setPosition(144 * resM, 0);
    sWon.setPosition(144 * resM, 0);
    sStart.setPosition(144 * resM, 0);

    //creating enemies
    Enemy *goblins[1];
    for (int i = 0; i < goblinsNum; i++)
    {
        goblins[i] = new Enemy;
        if (rand() % 2 == 1)
        {
            goblins[i]->setTexture(&tGoblin);
            goblins[i]->setSpeed(3 - rand() % 3);
            goblins[i]->setHealth(5 + rand() % 4);
            goblins[i]->setDamage(1 + rand() % 2);
        }
        else
        {
            goblins[i]->setTexture(&tHell);
            goblins[i]->setSpeed(3 + rand() % 4);
            goblins[i]->setHealth(5 - rand() % 3);
            goblins[i]->setDamage(1);
        }
        goblins[i]->setScale(resM);
        goblins[i]->setPosition((rand() % 576) * resM, 256 * resM);
    }

    //creating walls
    Walls wallDown(&tWallDown, 0, 0, resM);
    Walls wallUp(&tWallUp, 0, 0, resM);

    //creating clocks
    sf::Clock clock, clock2, clock3;
    sf::Time elapsed1 = clock.getElapsedTime();
    sf::Time elapsed2 = clock2.getElapsedTime();
    sf::Time elapsed3 = clock3.getElapsedTime();

    //main loop
    while (window.isOpen())
    {
        //exit 
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            {
                window.close();
            }
        }

        //drawing walls
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 6; j++)
            {
                wallDown.setPosition((0 + j * 96) * resM, (256 - i * 64) * resM);
                window.draw(*wallDown.getSprite());
            }
        }
        for (int j = 0; j < 6; j++)
        {
            wallUp.setPosition((0 + j * 96) * resM, 64 * resM);
            window.draw(*wallUp.getSprite());
        }

        //game mode switch
        switch (gameMode)
        {
        case 0:

            //checking earthPos
            if (charPos.y > earthPos)
            {
                charPos.y = earthPos;
                yVel = 0.f;
                yVel2 = 0.f;
            }

            //getting elapsed time 1
            elapsed3 = clock3.getElapsedTime();

            //goblins logic
            for (int i = 0; i < goblinsNum; i++)
            {
                if (goblins[i] != nullptr)
                {
                    window.draw(*goblins[i]->getSprite());
                    goblins[i]->searchChar(sChar.getPosition().x, sChar.getPosition().y, resM);

                    if (goblins[i]->sendDamage() && elapsed3 > sf::seconds(1) && charHealth > 0 && goblins[i] != nullptr)
                    {
                        charHealth--;
                        clock3.restart();
                        if (charHealth <= 0)
                        {
                            gameMode = 2;
                        }
                    }
                    if (checkHitSide(goblins[i]->getPosition().x, goblins[i]->getPosition().y, dmgZone.getPosition().x, dmgZone.getPosition().y, 120, 120) && gettingDamage)

                    {

                        goblins[i]->setHealth(goblins[i]->getHealth() - 1);
                        if (goblins[i]->getHealth() <= 0 && goblins[i] != nullptr)
                        {
                            delete goblins[i];
                            goblins[i] = nullptr;
                        }
                    }
                }
                else
                {
                    killsCounter++;
                }
            }

            //checing is all goblins are dead
            if (killsCounter == goblinsNum)
            {
                gameMode = 3;
            }
            killsCounter = 0;

            //checking map sides
            if (charPos.x < 0)
            {
                charPos.x = 0;
            }
            else if(charPos.x > 576 * resM)
            {
                charPos.x = 576 * resM;
            }

            //character movement 
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            {
                charPos.x += 5;
                charVec = 1;
                sChar.setScale(resM, resM);
                sSword.setScale(resM, resM);
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            {
                charPos.x -= 5;
                charVec = -1;
                sChar.setScale(-resM, resM);
                sSword.setScale(-resM, resM);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && charPos.y == earthPos)
            {
                yVel = -5.f;
            }

            //gettig elapsed time 1 and 2
            elapsed1 = clock.getElapsedTime();
            elapsed2 = clock2.getElapsedTime();

            //attack
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && elapsed1 > sf::seconds(0.2) && charHealth > 0)
            {
                for (int i = 0; i < 12; i++)
                {
                    // if();
                    if (sChar.getScale().x > 0)
                    {

                        sSword.setRotation(90);
                    }
                    else
                    {
                        sSword.setRotation(-90);
                    }
                }
                gettingDamage = 1;
                clock.restart();
                // charHealth--;
            }
            else
            {
                sSword.setRotation(0);
                gettingDamage = 0;
            }

            //drawing character's HP
            for (int i = 0; i < charHealth; i++)
            {
                sHealth.setPosition(((540 - (charHealth * 16)) + i * 16) * resM, 10 * resM);
                window.draw(sHealth);
            }

            //checking character's HP
            if (charHealth <= 0)
            {
                gameMode = 2;
            }

            //gravitation
            charPos.y += yVel;
            yVel += 0.15;

            //setting position for the character
            sChar.setPosition(charPos.x, charPos.y);
            sSword.setPosition(charPos.x, charPos.y - 5);
            dmgZone.setPosition(charPos.x, charPos.y);
            window.draw(sChar);
            window.draw(sSword);
            // window.draw(sDark);
            window.display();
            window.clear();
            break;
        case 1:
            // main menu
            //choosing health
            if (sf::Mouse::getPosition(window).x > 144 * resM + 68 && sf::Mouse::getPosition(window).x < 144 * resM + 192 && sf::Mouse::getPosition(window).y > 178 && sf::Mouse::getPosition(window).y < 264 && sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                charHealth = 3;
                gameMode = 0;
            }
            else if (sf::Mouse::getPosition(window).x > 144 * resM + 192 && sf::Mouse::getPosition(window).x < 144 * resM + 322 && sf::Mouse::getPosition(window).y > 178 && sf::Mouse::getPosition(window).y < 264 && sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                charHealth = 6;
                gameMode = 0;
            }
            else if (sf::Mouse::getPosition(window).x > 144 * resM + 322 && sf::Mouse::getPosition(window).x < 144 * resM + 456 && sf::Mouse::getPosition(window).y > 178 && sf::Mouse::getPosition(window).y < 264 && sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                charHealth = 9;
                gameMode = 0;
            }
            window.draw(sStart);
            // window.draw(sDark);
            window.display();
            window.clear();

            break;
        case 2:
            // game over
            window.draw(sGameOver);
            // window.draw(sDark);
            window.display();
            window.clear();
            break;
        case 3:
            // win
            window.draw(sWon);
            // window.draw(sDark);
            window.display();
            window.clear();
        }
    }
}