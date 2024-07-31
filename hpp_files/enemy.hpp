#include <SFML/Graphics.hpp>

class Enemy
{
private:
    int health, damage, speed, vector;
    sf::Sprite sprite;

public:
    Enemy(int health = 3, int damage = 1, int speed = 5)
    {
        this->health = health;
        this->damage = damage;
        this->speed = speed;
        sprite.setOrigin(16, 34);
    }
    void setTexture(sf::Texture *text)
    {
        sprite.setTexture(*text, true);
    }
    void setPosition(int X, int Y)
    {
        sprite.setPosition(X, Y);
    }
    void setDamage(int dmg)
    {
        damage = dmg;
    }
    void setHealth(int hp)
    {
        health = hp;
    }
    void setScale(int mult)
    {
        sprite.setScale(mult, mult);
    }
    void setSpeed(int speed){
        this->speed = speed;
    }
    int getHealth()
    {
        return health;
    }
    int getDamage()
    {
        return damage;
    }
    int getSpeed(){
        return speed;
    }
    sf::Vector2f getPosition()
    {
        return sprite.getPosition();
    }
    sf::Sprite *getSprite()
    {
        return &sprite;
    }
    void searchChar(int charPosX, int mult)
    {
        if (sprite.getPosition().x < charPosX - 30)
        {
            sprite.setPosition(sprite.getPosition().x + speed, sprite.getPosition().y);
            sprite.setScale(mult, mult);
            vector = 1;
        }
        else if (sprite.getPosition().x > charPosX + 30)
        {
            sprite.setPosition(sprite.getPosition().x - speed, sprite.getPosition().y);
            sprite.setScale(-mult, mult);
            vector = -1;
        }

    }
    int getVector(){
        return vector;
    }
};