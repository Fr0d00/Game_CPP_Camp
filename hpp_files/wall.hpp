#include <SFML/Graphics.hpp>

class Walls
{
private:
    sf::Sprite wall;

public:
    Walls(sf::Texture *text, int posX, int posY, int mult)
    {
        wall.setTexture(*text, true);
        wall.setPosition(posX, posY);
        wall.setScale(mult / 2, mult / 2);
        wall.setOrigin(0, 128);
    }
    void setPosition(int posX, int posY)
    {
        wall.setPosition(posX, posY);
    }
    sf::Sprite *getSprite()
    {
        return &wall;
    }
};