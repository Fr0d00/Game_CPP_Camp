#include <SFML/Graphics.hpp>
#include<iostream>

struct Point
{
    float x;
    float y;
    Point(int x = 0, int y = 0){
        this->x = x;
        this->y = y;
    }
};

class Crate{
private:
    sf::Sprite box;
    int posX, posY;
public:
    Crate(sf::Texture *text, int posX, int posY, int mult){
        box.setTexture(*text, true);
        box.setPosition(posX, posY);
        box.setOrigin(8, 16);
        box.setScale(mult, mult);
        this->posX = posX;
        this->posY = posY;
    }
    void setPosition(int X, int Y){
        posX = X;
        posY = Y;
        box.setPosition(posX, posY);
    }
    int getPositionX(){
        return posX;
    }
    int getPositionY(){
        return posY;
    }
    sf::Sprite *getSprite(){
        return &box;
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
    Point res(500 * resM, 400 * resM);
    Point charPos(200 * resM, 200 * resM);

    int gameMode = 0;
    int earthPos = 200 * resM;
    int charVec = 1;


    sf::RenderWindow window(sf::VideoMode(res.x, res.y), "Game");
    window.setFramerateLimit(60);

    sf::RectangleShape dmgZone(sf::Vector2f(60, 60));


    sf::Texture tChar, tSword, tBox;
    tChar.loadFromFile("images/Knight/Knight.png");
    tSword.loadFromFile("images/Sword/Sword.png");
    tBox.loadFromFile("images/Box/Box.png");

    sf::Sprite sChar(tChar), sSword(tSword); //sBox(tBox);
    sChar.setScale(resM, resM);
    sSword.setScale(resM, resM);
    dmgZone.setScale(resM, resM);
    //sBox.setScale(resM, resM);

    sChar.setOrigin(8, 28);
    sSword.setOrigin(3, 29);
    dmgZone.setOrigin(30, 30);
    //sBox.setOrigin(8, 16);

    sSword.setRotation(0);

    Crate box(&tBox, 300 * resM, 200 * resM, resM);
    //box.setPosition();    

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

            // if(checkHitUp(charPos.x, charPos.y, sBox.getPosition().x, sBox.getPosition().y, 32, 31)){
            //     if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
            //         yVel2 = -4.f;
            //     }
            //     charPos.y -= yVel;
            //     //yVel2 += 0.14;
            //     if(charPos.y > earthPos + 35){
            //         if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
            //             yVel2 = -4.f;
            //         }
            //         else{
            //             yVel2 = 0.f;
            //         }
            //     }
            // }

            if(checkHitSide(charPos.x, charPos.y, box.getPositionX(), box.getPositionY(), 32, 31)){
                charPos.x -= 5 * charVec;
                earthPos = 200 * resM;
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
                window.draw(dmgZone);
            }
            else{
                sSword.setRotation(0);
            }

            charPos.y += yVel;
            yVel += 0.14;

            sChar.setPosition(charPos.x, charPos.y);
            sSword.setPosition(charPos.x, charPos.y);
            dmgZone.setPosition(charPos.x, charPos.y);
            window.draw(*box.getSprite());
            window.draw(sChar);
            window.draw(sSword);
            window.display();
            window.clear();
            break;
        }
    }
}