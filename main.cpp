#include <SFML/Graphics.hpp>
#include<iostream>

struct Point
{
    int x;
    int y;
    Point(int x, int y){
        this->x = x;
        this->y = y;
    }
};




int main(){
    float resM = 2.f;
    Point res(500 * resM, 400 * resM);
    Point charPos(200 * resM, 200 * resM);

    int gameMode = 0;


    sf::RenderWindow window(sf::VideoMode(res.x, res.y), "Game");
    window.setFramerateLimit(60);

    sf::Texture tChar;
    tChar.loadFromFile("images/Knight/Knight.png");

    sf::Sprite sChar(tChar);
    sChar.setScale(resM, resM);
    sChar.setOrigin(8, 28);
    sChar.setPosition(charPos.x, charPos.y);

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
            window.display();
            window.clear();
            break;
        }
    }
}