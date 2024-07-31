#include <SFML/Graphics.hpp>

class Crate{
private:
    sf::Sprite box;
    int posX, posY;
public:

    Crate(/*sf::Texture *text = nullptr,*/ int posX = 0, int posY = 0, int mult = 1){
        //box.setTexture(*text, true);
        box.setPosition(posX, posY);
        box.setOrigin(8, 16);
        box.setScale(mult, mult);
        this->posX = posX;
        this->posY = posY;
    }
    void setScale(int mult = 0){
        box.setScale(mult, mult);
    }
    void setTexture(sf::Texture *text){
        box.setTexture(*text, true);        
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