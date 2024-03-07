#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>
#include "Pion.h"
#include "Plansza.h"
#include "Game.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(1000, 700), "Ataxx Remastered");
    window.setFramerateLimit(120);
    
    
    Plansza plansza(window);
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (!plansza.GameOver())
            {
                // Obs³uga klikniêcia myszy
                if (event.type == sf::Event::MouseButtonPressed) {
                    if (event.mouseButton.button == sf::Mouse::Left) {
                        sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                      
                        plansza.handleClick(mousePos);
                    }
                    if (event.mouseButton.button == sf::Mouse::Right) {
                        sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                        plansza.handleAction(mousePos);
                    }
                }
            }
            // Obs³uga restartu
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::R) {
                    plansza.Restart();
                }
            }
           
        }
        window.clear();
        if (plansza.isStarted())
            plansza.draw(window);        // Rysowanie planszy
        else
        {
            sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
            plansza.ChooseMode(window, mousePos,0);
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                    plansza.ChooseMode(window, mousePos,1);
                }
            }
        }
            
       
        window.display();
    }
    return 0;
}