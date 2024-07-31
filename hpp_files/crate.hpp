#include <SFML/Graphics.hpp>

class Crate
{
private:
    sf::Sprite box;
    int health;
    bool isBrakeable;

public:
    Crate(int posX = 0, int posY = 0, int mult = 1, int health = 3, bool isBreak = 1)
    {
        box.setPosition(posX, posY);
        box.setOrigin(8, 16);
        box.setScale(mult, mult);
        this->health = health;
        isBrakeable = isBreak;
    }
    void setScale(int mult = 0)
    {
        box.setScale(mult, mult);
    }
    void setTexture(sf::Texture *text)
    {
        box.setTexture(*text, true);
    }
    void setPosition(int X, int Y)
    {
        box.setPosition(X, Y);
    }
    void setHealth(int health)
    {
        this->health = health;
    }
    sf::Vector2f getPosition()
    {
        return box.getPosition();
    }
    sf::Sprite *getSprite()
    {
        return &box;
    }
    int getHealth()
    {
        return health;
    }
    bool isBreakable()
    {
        return isBrakeable;
    }
};