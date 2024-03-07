#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class Pion
{
private:
    sf::CircleShape shape; // Kszta�t piona (ko�o)
    int promien = 40;
    bool aktywny = false;
    bool exists;
    int gracz;
    float pozX, pozY;
    
public:
    Pion();
    void setData(float x, float y, int gracz);      //inicjalizacja zmiennych
    void paint(sf::Texture* red_tex, sf::Texture* blue_tex);       //kolowanie piona w zale�no�ci od posiadania przez gracza
    void draw(sf::RenderWindow& window);
    bool contains(sf::Vector2f point) const;
    void setAktywny(bool aktywny);  //ustalenie czy pion ma by� zaznaczony kursorem
    bool isAktywny() const;
    void setGracz(int gracz);   //zmiana gracza
    int zwrocGracz();
    void doExists(bool existance);      //ustalenie czy pion ma si� wy�wietla�
    bool isExisting();
    float coordX();
    float coordY();
    void porusz(float x, float y);
    void changePos(float x, float y);
};

