#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <ctime>
#include "Pion.h"
#include "Game.h"
#include "Brick.h"
#include <vector>


class Plansza
{
private:
    static const int rozmiarPlanszy = 7;
    Pion pion[rozmiarPlanszy][rozmiarPlanszy];  //inicjalizacja na ca³ej szachownicy obiektów pionów i widm (na razie ¿adne nie istniej¹)
    Brick brick[rozmiarPlanszy][rozmiarPlanszy];
    sf::Text title;
    sf::Text tura;
    sf::Text red;
    sf::Text blue;
    sf::Text redPoints;
    sf::Text bluePoints;
    sf::Text restart;
    sf::Text restart2;
    sf::Text red_turn;
    sf::Text blue_turn;

    sf::Text mode;
    sf::Text sp;
    sf::Text mp;


    sf::Font font;
    int blockControl;   //zmienna kontroluj¹ca czy gra siê koñczy przedwczeœnie
    int lastLvl=0;
    sf::Texture red_tex;
    sf::Texture blue_tex;
    
    sf::Texture org_tex;
    sf::Texture gr_tex;

    

    bool gameStarted = 0;
    bool gameMode;
    
public:
    sf::RenderWindow& window;
    Game gra;
    Plansza(sf::RenderWindow& window);
    ~Plansza();
    void draw(sf::RenderWindow& window);
    void handleClick(sf::Vector2f mousePos);    //obs³uga LPM
    void handleAction(sf::Vector2f mousePos);   //obs³uga PPM
    void capture(Pion pionek);  //przechwycenie pionów enemy
    void UpdatePoints();
    bool GameOver();    //czy gra siê koñczy przedwczeœnie - zwraca bool
    void Restart();
    void skok(Pion* pionek, Pion* nowe_pole);
    void klonowanie(Pion pionek, Pion* nowe_pole);
    void setTexts();    //zarz¹dzanie tekstem interfejsu
    void level1();
    void level2();
    void level3();
    void level4();
    void level5();
    void ChooseMode(sf::RenderWindow& window, sf::Vector2f point,bool click);
    bool isStarted();
    void bot();
};

