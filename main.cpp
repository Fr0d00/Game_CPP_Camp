#include <SFML/Graphics.hpp>
#include<iostream>

struct Point
{
    float x;
    float y;
    Point(int x, int y){
        this->x = x;
        this->y = y;
    }
};





int main(){
    float resM = 2.f;
    float yVel = 0.f;
    Point res(500 * resM, 400 * resM);
    Point charPos(200 * resM, 200 * resM);

    int gameMode = 0;
    int earthPos = 200 * resM;


    sf::RenderWindow window(sf::VideoMode(res.x, res.y), "Game");
    window.setFramerateLimit(60);

    sf::Texture tChar, tSword;
    tChar.loadFromFile("images/Knight/Knight.png");
    tSword.loadFromFile("images/Sword/Sword.png");

    sf::Sprite sChar(tChar), sSword(tSword);
    sChar.setScale(resM, resM);
    sSword.setScale(resM, resM);

    sChar.setOrigin(8, 28);
    sSword.setOrigin(3, 29);

    sChar.setPosition(charPos.x, charPos.y);
    sSword.setPosition(charPos.x, charPos.y);

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
            }
            if(charPos.x < 0){
                charPos.x = 0;
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
                charPos.x += 5;
                sChar.setScale(resM, resM);
                sSword.setScale(resM, resM);
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
                charPos.x -= 5;
                sChar.setScale(-resM, resM);
                sSword.setScale(-resM, resM);
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && charPos.y == earthPos){
                yVel = -3.f;
            }


            charPos.y += yVel;
            yVel += 0.17;

            sChar.setPosition(charPos.x, charPos.y);
            sSword.setPosition(charPos.x, charPos.y);
            window.draw(sChar);
            window.draw(sSword);
            window.display();
            window.clear();
            break;
        }
    }
}