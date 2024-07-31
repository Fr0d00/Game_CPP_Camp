#include <SFML/Graphics.hpp>
#include <iostream>
#include "hpp_files/crate.hpp"
#include "hpp_files/wall.hpp"

struct Point
{
    float x;
    float y;
    Point(int x = 0, int y = 0){
        this->x = x;
        this->y = y;
    }
};


bool checkHitSide(int charPosX, int charPosY, int posX, int posY, int scaleX, int scaleY){
    if((charPosX > posX - scaleX / 2 && charPosX < posX + scaleX / 2) && charPosY > posY - scaleY){
        return true;
    }
}


int main(){


    float resM = 2.f;
    float yVel = 0.f;
    float yVel2 = 0.f;
    Point res(576 * resM, 256 * resM);
    Point charPos(200 * resM, 256 * resM);

    int gameMode = 0;
    int earthPos = 256 * resM;
    int charVec = 1;

    bool gettingDamage = 0;


    sf::RenderWindow window(sf::VideoMode(res.x, res.y), "Game");
    window.setFramerateLimit(60);

    sf::RectangleShape dmgZone(sf::Vector2f(60, 60));


    sf::Texture tChar, tSword, tBox, tWallDown, tWallUp, tWallDoor, tDark;
    tChar.loadFromFile("images/Knight/Knight.png");
    tSword.loadFromFile("images/Sword/Sword.png");
    tBox.loadFromFile("images/Box/Box.png");
    tWallDown.loadFromFile("images/Walls/WallDown.png");
    tWallUp.loadFromFile("images/Walls/WallUp.png");
    tWallDoor.loadFromFile("images/Walls/WallDownDoorClosed.png");
    tDark.loadFromFile("images/Darkness/Darkness.png");

    sf::Sprite sChar(tChar), sSword(tSword), sDark(tDark);
    sChar.setScale(resM, resM);
    sSword.setScale(resM, resM);
    dmgZone.setScale(resM, resM);
    sDark.setScale(resM, resM);

    sChar.setOrigin(8, 28);
    sSword.setOrigin(3, 29);
    dmgZone.setOrigin(30, 30);

    sSword.setRotation(0);

    //Crate box(&tBox, 300 * resM, 256 * resM, resM); 
    Crate* boxes[3];
    for(int i = 0; i < 3; i++){
        boxes[i] = new Crate;
        boxes[i]->setTexture(&tBox);
        boxes[i]->setScale(resM);
        boxes[i]->setPosition((300 + i * 16) * resM, 256 * resM);
    }
    Walls wallDown(&tWallDown, 0, 0, resM);
    Walls wallUp(&tWallUp, 0, 0, resM);

    sChar.setPosition(charPos.x, charPos.y);
    sSword.setPosition(charPos.x, charPos.y);
    dmgZone.setPosition(charPos.x, charPos.y);
    //sBox.setPosition(300 * resM, 200 * resM);

    while(window.isOpen()){
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            {
                window.close();
            }
        }
        switch (gameMode)
        {
        case 0:
            if(charPos.y > earthPos){
                charPos.y = earthPos;
                yVel = 0.f;
                yVel2 = 0.f;
            }

            for(int i = 0; i < 3; i++){
                for(int j = 0; j < 6; j++){
                    wallDown.setPosition((0 + j * 96) * resM, (256 - i * 64) * resM);
                    window.draw(*wallDown.getSprite());
                }             
            }
            for(int j = 0; j < 6; j++){
                wallUp.setPosition((0 + j * 96) * resM, 64 * resM);
                window.draw(*wallUp.getSprite());
            }              

            for(int i = 0; i < 3; i++){
                if(boxes[i] != nullptr){
                    window.draw(*boxes[i]->getSprite());
                    //if(boxes[i]->getPosition().x <)
                    if(checkHitSide(charPos.x, charPos.y, boxes[i]->getPosition().x, boxes[i]->getPosition().y, 32, 31)){
                        charPos.x -= 5 * charVec;
                        //earthPos = 200 * resM;
                    }
                    if(checkHitSide(boxes[i]->getPosition().x, boxes[i]->getPosition().y, dmgZone.getPosition().x, dmgZone.getPosition().y, 120, 120) && gettingDamage){
                        delete boxes[i];
                        boxes[i] = nullptr;
                    }        
                }            
            }

      
            if(charPos.x < 0){
                charPos.x = 0;
            }

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
                charPos.x += 5;
                charVec = 1;
                sChar.setScale(resM, resM);
                sSword.setScale(resM, resM);
            }
            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
                charPos.x -= 5;
                charVec = -1;
                sChar.setScale(-resM, resM);
                sSword.setScale(-resM, resM);
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && charPos.y == earthPos){
                yVel = -4.f;
            }

            if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                if(sChar.getScale().x > 0){
                    sSword.setRotation(sSword.getRotation() + 15);
                }
                else{
                    sSword.setRotation(sSword.getRotation() - 15);
                }
                //window.draw(dmgZone);
                gettingDamage = 1;
            }
            else{
                sSword.setRotation(0);
                gettingDamage = 0;
            }

            charPos.y += yVel;
            yVel += 0.14;

            sChar.setPosition(charPos.x, charPos.y);
            sSword.setPosition(charPos.x, charPos.y);
            dmgZone.setPosition(charPos.x, charPos.y);
            window.draw(sChar);
            window.draw(sSword);
            window.draw(sDark);
            window.display();
            window.clear();
            break;
        }
    }
}