#pragma once
#include <SFML/Graphics.hpp>

class Brick
{
private:
	sf::RectangleShape shape; 
	int bok = 40;
	float pozX, pozY;
	bool exists;
public:
    Brick();

    void setData(float x, float y);     
    void setTexture();
    bool contains(sf::Vector2f point) const;
    void draw(sf::RenderWindow& window);
    void doExists(bool existance);      
    bool isExisting();
    float coordX();
    float coordY();
};

