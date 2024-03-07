#include "Brick.h"

Brick::Brick() {

}

void Brick::setData(float x, float y)
{
    this->pozX = x;
    this->pozY = y;

    shape.setSize(sf::Vector2f(100, 100)); 
    shape.setPosition(100 * x , 100 * y ); 

    this->exists = 0;
}

void Brick::setTexture()
{
    shape.setFillColor(sf::Color(36,43,43,255));
    
}

bool Brick::contains(sf::Vector2f point) const {
    return shape.getGlobalBounds().contains(point);
}
void Brick::draw(sf::RenderWindow& window) {
    window.draw(shape);
}
void Brick::doExists(bool existance)
{
    this->exists = existance;
}
bool Brick::isExisting()
{
    return this->exists;
}
float Brick::coordX()
{
    return this->pozX;
}
float Brick::coordY()
{
    return this->pozY;
}