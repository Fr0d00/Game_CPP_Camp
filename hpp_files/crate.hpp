#include <SFML/Graphics.hpp>

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