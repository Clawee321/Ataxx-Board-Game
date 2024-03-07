#include "Pion.h"
#include <SFML/Graphics.hpp>
#include <iostream>


Pion::Pion() {

    
}

void Pion::setData(float x, float y, int gracz)
{
    this->pozX = x;
    this->pozY = y;
    setGracz(gracz);
    shape.setRadius(promien); // Rozmiar piona
    shape.setPosition(100 * x + 10, 100 * y + 10); // Pozycja piona na planszy
    this->exists = 0;
}

void Pion::paint(sf::Texture* red_tex, sf::Texture* blue_tex)
{
   if (this->gracz == 1) {
      
      shape.setTexture(red_tex);
   }
   else
   {
      
      shape.setTexture(blue_tex);
   }
}


void Pion::draw(sf::RenderWindow& window) {
    
    window.draw(shape);
}

bool Pion::contains(sf::Vector2f point) const {
    return shape.getGlobalBounds().contains(point);
}

void Pion::setAktywny(bool aktywny) {   //podœwietlenie piona gdy jest zaznaczony
    this->aktywny = aktywny;
    if (aktywny == true) {
        shape.setOutlineThickness(5);
        shape.setOutlineColor(sf::Color::Yellow);
    }
    else
    {
        shape.setOutlineThickness(0);
    }
}

bool Pion::isAktywny() const {
    return aktywny;
}

void Pion::setGracz(int gracz)
{
    this->gracz = gracz;
}
int Pion::zwrocGracz()
{
    return this->gracz;
}

void Pion::doExists(bool existance)
{
    this->exists = existance;
}

bool Pion::isExisting()
{
    return this->exists;
}
float Pion::coordX()
{
    return this->pozX;
}
float Pion::coordY()
{
    return this->pozY;
}
void Pion::porusz(float x, float y)
{
    shape.move(x,y);
    
}
void Pion::changePos(float x, float y)
{
    shape.setPosition(100 * x + 10, 100 * y + 10);
}