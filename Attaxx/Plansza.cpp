#include "Plansza.h"
#include <SFML/Graphics.hpp>
#include <iostream>

Plansza::Plansza(sf::RenderWindow& window) : window(window) {
    
    
    if (!blue_tex.loadFromFile("blue_tex.jpg")) {
        // Obs³u¿ b³¹d wczytywania tekstury
        std::cout << "blad";
    }
    if (!red_tex.loadFromFile("red_tex.jpg")) {
        // Obs³u¿ b³¹d wczytywania tekstury
        std::cout << "blad";
    }
   
    
    Restart();
}

Plansza::~Plansza() {
    
}

void Plansza::draw(sf::RenderWindow& window) {
    this->setTexts();
    window.draw(this->title);   //rysowanie tekstu
    window.draw(this->tura);
    window.draw(this->red);
    window.draw(this->blue);
    window.draw(this->redPoints);
    window.draw(this->bluePoints);
    window.draw(restart);
    window.draw(restart2);
    window.draw(red_turn);
    window.draw(blue_turn);

    // Rysowanie planszy
    for (int i = 0; i < rozmiarPlanszy; ++i) {
        for (int j = 0; j < rozmiarPlanszy; ++j) {
            // Rysowanie prostok¹ta reprezentuj¹cego pole planszy
            sf::RectangleShape rectangle(sf::Vector2f(100, 100));
            rectangle.setPosition(i * 100, j * 100);
            // Ustawienie koloru pola na czarny lub bia³y w zale¿noœci od pozycji
            if ((i + j) % 2 == 0) {
                rectangle.setFillColor(sf::Color(23, 135, 93, 255));
            }
            else {
                rectangle.setFillColor(sf::Color(31, 180, 135, 255));
            }
            window.draw(rectangle);
        }
    }
    for (int i = 0; i < rozmiarPlanszy; ++i) {
        for (int j = 0; j < rozmiarPlanszy; ++j) {
            // Rysowanie piona, jeœli istnieje na danym polu
            if (pion[i][j].isExisting()) {
                pion[i][j].paint(&red_tex,&blue_tex);
                pion[i][j].draw(window);
            }
            
            
            if (brick[i][j].isExisting()) {
                brick[i][j].setTexture();
                brick[i][j].draw(window);
            }
        }
    }
}



void Plansza::handleClick(sf::Vector2f mousePos) {
    // Sprawdzenie, czy pion na danej pozycji zosta³ zaznaczony
    for (int i = 0; i < rozmiarPlanszy; ++i) {
        for (int j = 0; j < rozmiarPlanszy; ++j) {
            if (pion[i][j].isExisting() == 1) {
                if (gra.WhoseTurn() == pion[i][j].zwrocGracz()) //SprawdŸ czy kolor piona zgadza siê z kolejk¹ gracza
                {
                    bool czyZaznaczony = pion[i][j].contains(mousePos);
                    pion[i][j].setAktywny(czyZaznaczony);
                    
                }
            }
        }
    }
}

void Plansza::handleAction(sf::Vector2f mousePos) {
    
    
        for (int i = 0; i < rozmiarPlanszy; ++i) {
            for (int j = 0; j < rozmiarPlanszy; ++j) {
                if (pion[i][j].isExisting() == 1 && pion[i][j].isAktywny()) {

                    int x = pion[i][j].coordX();
                    int y = pion[i][j].coordY();

                    for (int k = -2; k <= 2; ++k) {
                        for (int l = -2; l <= 2; ++l) {
                            int newX = x + k;
                            int newY = y + l;

                            // SprawdŸ, czy nowe indeksy s¹ w zakresie planszy
                            if (newX >= 0 && newX < 7 && newY >= 0 && newY < 7) {
                                // SprawdŸ, czy pion wykonuje akcjê
                                if (pion[newX][newY].isExisting() == 0 && brick[newX][newY].isExisting() == 0 && pion[newX][newY].contains(mousePos)) {
                                    if (abs(k) <= 1 && abs(l) <= 1)
                                    {
                                        // Wykonanie akcji klonowania
                                        pion[x][y].setAktywny(0);
                                        klonowanie(pion[x][y], &pion[newX][newY]);
                                        gra.ChangeTurn();

                                        if (GameOver() == 0)
                                        {
                                            if (gameMode == 0)
                                                bot();
                                        }
                                        
                                    }
                                    else
                                    {
                                        // Wykonanie akcji skoku
                                        pion[x][y].setAktywny(0);
                                        skok(&pion[x][y], &pion[newX][newY]);
                                        gra.ChangeTurn();


                                        if (GameOver() == 0)
                                        {
                                            if (gameMode == 0)
                                                bot();
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    
    
}

void Plansza::bot()
{
    bool akcja;
    int maxKillCounter = 0;
    int idPiona_x;
    int idPiona_y;
    int idPola_x;
    int idPola_y;
    int extraX;
    int extraY;
    int lista[50][3];   //x,y, ilosc akcji
    int dlugosc=0;


    for (int i = 0; i < rozmiarPlanszy; ++i) {
        for (int j = 0; j < rozmiarPlanszy; ++j) {
            if (pion[i][j].isExisting() == 1 && pion[i][j].zwrocGracz()==0) {
                lista[dlugosc][0] = i;
                lista[dlugosc][1] = j;
                lista[dlugosc][2] = 0;

                

                int x = pion[i][j].coordX();
                int y = pion[i][j].coordY();

                for (int k = -2; k <= 2; ++k) {
                    for (int l = -2; l <= 2; ++l) {
                        int newX = x + k;
                        int newY = y + l;

                        // SprawdŸ, czy nowe indeksy s¹ w zakresie planszy
                        if (newX >= 0 && newX < 7 && newY >= 0 && newY < 7) {
                            // SprawdŸ, czy pion wykonuje akcjê
                            if (pion[newX][newY].isExisting() == 0 && brick[newX][newY].isExisting()==0) {
                                int killCounter = 0;

                                

                                if (abs(k) <= 1 && abs(l) <= 1)
                                {
                                    lista[dlugosc][2]++;

                                }
                                

                                for (int m = -1; m <= 1; m++)
                                {
                                    for (int n = -1; n <= 1; n++)
                                    {
                                        extraX = newX + m;
                                        extraY = newY + n;
                                        if (extraX >= 0 && extraX < 7 && extraY >= 0 && extraY < 7)
                                        {
                                            if (pion[extraX][extraY].isExisting() && pion[extraX][extraY].zwrocGracz() == 1)
                                            {
                                                killCounter++;
                                            }
                                        }
                                    }
                                }
                                if (killCounter > maxKillCounter || (killCounter==maxKillCounter && (abs(k) <= 1 && abs(l) <= 1)))
                                {
                                    maxKillCounter = killCounter;
                                    idPiona_x = i;
                                    idPiona_y = j;
                                    idPola_x = newX;
                                    idPola_y = newY;

                                    if (abs(k) <= 1 && abs(l) <= 1)
                                    {
                                        // Wykonanie akcji klonowania
                                        akcja = 0;
                                    }
                                    else
                                    {
                                        // Wykonanie akcji skoku
                                        akcja = 1;
                                    }
                                }
                                
                            }
                        }
                    }
                }
                dlugosc++;
            }
        }
    }
    if (maxKillCounter == 0)
    {
        int los = rand() % dlugosc;
        while (lista[los][2] == 0)
        {
            los = rand() % dlugosc;
            
        }

        int los_akcja = rand() % lista[los][2]+1;
        int x = lista[los][0];
        int y = lista[los][1];



        for (int k = -1; k <= 1; ++k) {
            for (int l = -1; l <= 1; ++l) {
                
                int newX = x + k;
                int newY = y + l;

                // SprawdŸ, czy nowe indeksy s¹ w zakresie planszy
                if (newX >= 0 && newX < 7 && newY >= 0 && newY < 7) {
                    // SprawdŸ, czy pion wykonuje akcjê
                    if (pion[newX][newY].isExisting() == 0 && brick[newX][newY].isExisting() == 0) {
                        los_akcja--;
                        if (los_akcja == 0)
                        {
                            klonowanie(pion[x][y], &pion[newX][newY]);
                        }



                    }
                }
            }
        }
        
    }
    else
    {
        if (akcja == 0)
            klonowanie(pion[idPiona_x][idPiona_y], &pion[idPola_x][idPola_y]);
        else
            skok(&pion[idPiona_x][idPiona_y], &pion[idPola_x][idPola_y]);
    }
    
    gra.ChangeTurn();
}



void Plansza::capture(Pion pionek)
{
    int gracz = pionek.zwrocGracz();
    int x = pionek.coordX();
    int y = pionek.coordY();

    for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
            int newX = x + i;
            int newY = y + j;

            // SprawdŸ, czy nowe indeksy s¹ w zakresie planszy
            if (newX >= 0 && newX < 7 && newY >= 0 && newY < 7) {
                // SprawdŸ, czy pole zawiera pion innego gracza
                if (pion[newX][newY].isExisting() == 1 && pion[newX][newY].zwrocGracz() != gracz) {
                    // Przechwycenie piona na swoja strone
                    pion[newX][newY].setGracz(gracz);
                }
            }
        }
    }
}

void Plansza::UpdatePoints()    //liczenie punktów dla graczy
{
    int redP = 0;
    int blueP = 0;
    for (int i = 0; i < rozmiarPlanszy; ++i) {
        for (int j = 0; j < rozmiarPlanszy; ++j) {
            if (pion[i][j].isExisting()) {
                if (pion[i][j].zwrocGracz() == 0)
                    blueP++;
                else
                    redP++;
            }
        }
    }
    gra.BlueSetPoints(blueP);
    gra.RedSetPoints(redP);
}

bool Plansza::GameOver() //metoda sprawdza czy obecny gracz ma ruch
{
    blockControl = 0;
    for (int i = 0; i < rozmiarPlanszy; ++i) {
        for (int j = 0; j < rozmiarPlanszy; ++j) {
            if (pion[i][j].isExisting()) {
                if (pion[i][j].zwrocGracz() == gra.WhoseTurn())
                {
                    for (int k = -2; k <= 2; ++k) { //SprawdŸ, czy s¹ wolne pola w promieniu 2
                        for (int l = -2; l <= 2; ++l) {
                            int newX = k + i;
                            int newY = l + j;

                            if (newX >= 0 && newX < 7 && newY >= 0 && newY < 7) {
                                // SprawdŸ, czy pole jest puste
                                if (pion[newX][newY].isExisting() == 0 && brick[newX][newY].isExisting() == 0) {

                                    blockControl++;

                                }
                            }
                        }
                    }
                }
            }
        }
    }
    if (blockControl == 0)
        return 1;   //gra sie konczy
    else
        return 0;   //gra trwa dalej
}

void Plansza::Restart()

{   
    
    // Inicjalizacja planszy 7x7
    for (int i = 0; i < rozmiarPlanszy; ++i) {
        for (int j = 0; j < rozmiarPlanszy; ++j) {
            pion[i][j].setData(i, j, 0);
            
            brick[i][j].setData(i, j);
        }
    }

    srand((unsigned)time(0));
    int l = rand()%5+1;
    while (l == lastLvl)
    {
        l = rand() % 5 + 1;
    }
    
    switch (l)
    {
    case 1:
        level1();
        break;
    case 2:
        level2();
        break;
    case 3:
        level3();
        break;

    case 4:
        level4();
        break;

    case 5:
        level5();
        break;
    default:
        level3();
        break;
    }
    lastLvl = l;
    
}



void Plansza::skok(Pion* pionek, Pion* nowe_pole)
{
    
    int gracz = pionek->zwrocGracz();
    nowe_pole->doExists(true);
    nowe_pole->setGracz(gracz);
    float vector_x = nowe_pole->coordX() - pionek->coordX();
    float vector_y = nowe_pole->coordY() - pionek->coordY();
    nowe_pole->changePos(pionek->coordX(), pionek->coordY());
    pionek->doExists(false);
    for (int i = 0; i < 100; i++)
    {
        nowe_pole->porusz(vector_x, vector_y);
        window.clear();
        draw(window);
        window.display();
    }
    capture(*nowe_pole);    //przechwycenie po akcji
    UpdatePoints();
}

void Plansza::klonowanie(Pion pionek, Pion* nowe_pole)
{
    
    int gracz = pionek.zwrocGracz();
    nowe_pole->doExists(true);
    nowe_pole->setGracz(gracz);
    float vector_x = nowe_pole->coordX() - pionek.coordX();
    float vector_y = nowe_pole->coordY() - pionek.coordY();
    nowe_pole->changePos(pionek.coordX(), pionek.coordY());
    for (int i = 0; i < 100; i++)
    {
        nowe_pole->porusz(vector_x, vector_y);
        window.clear();
        draw(window);
        window.display();
    }
    capture(*nowe_pole);     //przechwycenie po akcji
    UpdatePoints();
}
void Plansza::setTexts()
{
    if (!font.loadFromFile("RAVIE.TTF"))
    {
        // error...
    }

    this->title.setFont(font);
    this->title.setCharacterSize(40);
    this->title.setFillColor(sf::Color(169, 33, 225, 255));
    this->title.setPosition(760, 50);
    this->title.setString("ATAXX");


    red_turn.setFont(font);
    red_turn.setCharacterSize(40);
    red_turn.setPosition(800, 250);
    

    blue_turn.setFont(font);
    blue_turn.setCharacterSize(40);
    blue_turn.setPosition(790, 250);
    

    if (this->gra.WhoseTurn() == 0)
    {         
        blue_turn.setFillColor(sf::Color(33, 165, 225, 255));   //kolorowanie napisu w zale¿noœci od kolejki gracza
        blue_turn.setString("BLUE");
        red_turn.setString("");
        
    }
        
    else
    {
        red_turn.setFillColor(sf::Color(225, 33, 95, 255));
        red_turn.setString("RED");
        blue_turn.setString("");
        
    }


    this->tura.setFont(font);
    this->tura.setCharacterSize(40);  
    this->tura.setPosition(780, 150);
    this->tura.setString("TURN");
    tura.setFillColor(sf::Color::White);


    this->red.setFont(font);
    this->red.setCharacterSize(40);
    this->red.setFillColor(sf::Color(225, 33, 95, 255));
    this->red.setPosition(760, 500);
    this->red.setString("R");

    this->blue.setFont(font);
    this->blue.setCharacterSize(40);
    this->blue.setFillColor(sf::Color(33, 165, 225, 255));
    this->blue.setPosition(890, 500);
    this->blue.setString("B");


    this->redPoints.setFont(font);
    this->redPoints.setCharacterSize(40);
    this->redPoints.setFillColor(sf::Color(255, 255, 255, 255));
    this->redPoints.setPosition(760, 600);
    this->redPoints.setString(std::to_string(this->gra.RedPoints()));

    this->bluePoints.setFont(font);
    this->bluePoints.setCharacterSize(40);
    this->bluePoints.setFillColor(sf::Color(255, 255, 255, 255));
    this->bluePoints.setPosition(890, 600);
    this->bluePoints.setString(std::to_string(this->gra.BluePoints()));


    this->restart.setFont(font);    //Pojawia siê propozycja restartu
    this->restart.setCharacterSize(25);
    this->restart.setFillColor(sf::Color(255, 255, 255, 255));
    this->restart.setPosition(750, 380);
    this->restart.setString("Press R");

    this->restart2.setFont(font);
    this->restart2.setCharacterSize(25);
    this->restart2.setFillColor(sf::Color(255, 255, 255, 255));
    this->restart2.setPosition(750, 430);
    this->restart2.setString("to restart...");

    if (gra.RedPoints() > gra.BluePoints())
        this->redPoints.setFillColor(sf::Color::Yellow);
    else if (gra.RedPoints() < gra.BluePoints())
        this->bluePoints.setFillColor(sf::Color::Yellow);

    if (GameOver())    //napis TURN zmienia siê na WINNER
    {
        this->tura.setPosition(740, 150);
        this->tura.setString("WINNER");
        if (gra.Winner() == 0)
        {
            blue_turn.setFillColor(sf::Color(33, 165, 225, 255));   //kolorowanie napisu w zale¿noœci od kolejki gracza
            blue_turn.setString("BLUE");
            red_turn.setString("");
        }
            
        else
        {
            red_turn.setFillColor(sf::Color(225, 33, 95, 255));
            red_turn.setString("RED");
            blue_turn.setString("");
        }
            


       
    }
    
}
void Plansza::level1()
{
    //Przywrócenie pionów do stanu pocz¹tkowego

    for (int i = 0; i < rozmiarPlanszy; ++i) {
        for (int j = 0; j < rozmiarPlanszy; ++j) {

            pion[i][j].doExists(0);
        }
    }
    pion[0][0].doExists(1);
    pion[0][0].setGracz(1);

    pion[6][0].doExists(1);
    pion[6][0].setGracz(0);

    pion[0][6].doExists(1);
    pion[0][6].setGracz(0);


    pion[6][6].doExists(1);
    pion[6][6].setGracz(1);


    brick[2][2].doExists(1);
    brick[4][2].doExists(1);
    brick[2][4].doExists(1);
    brick[4][4].doExists(1);

    UpdatePoints();     //reset punktow

    if (gra.WhoseTurn() == 0)
        gra.ChangeTurn();
}
void Plansza::level2()
{
    //Przywrócenie pionów do stanu pocz¹tkowego

    for (int i = 0; i < rozmiarPlanszy; ++i) {
        for (int j = 0; j < rozmiarPlanszy; ++j) {

            pion[i][j].doExists(0);
        }
    }
    pion[0][0].doExists(1);
    pion[0][0].setGracz(1);

    pion[6][0].doExists(1);
    pion[6][0].setGracz(0);

    pion[0][6].doExists(1);
    pion[0][6].setGracz(0);


    pion[6][6].doExists(1);
    pion[6][6].setGracz(1);


    brick[3][4].doExists(1);
    brick[3][2].doExists(1);
    brick[2][3].doExists(1);
    brick[4][3].doExists(1);

    UpdatePoints();     //reset punktow

    if (gra.WhoseTurn() == 0)
        gra.ChangeTurn();
}
void Plansza::level3()
{
    //Przywrócenie pionów do stanu pocz¹tkowego

    for (int i = 0; i < rozmiarPlanszy; ++i) {
        for (int j = 0; j < rozmiarPlanszy; ++j) {

            pion[i][j].doExists(0);
        }
    }
    pion[0][0].doExists(1);
    pion[0][0].setGracz(1);

    pion[6][0].doExists(1);
    pion[6][0].setGracz(0);

    pion[0][6].doExists(1);
    pion[0][6].setGracz(0);


    pion[6][6].doExists(1);
    pion[6][6].setGracz(1);


    brick[3][4].doExists(1);
    brick[3][2].doExists(1);
    brick[2][3].doExists(1);
    brick[4][3].doExists(1);
    brick[3][3].doExists(1);


    UpdatePoints();     //reset punktow

    if (gra.WhoseTurn() == 0)
        gra.ChangeTurn();
}
void Plansza::level4()
{
    //Przywrócenie pionów do stanu pocz¹tkowego

    for (int i = 0; i < rozmiarPlanszy; ++i) {
        for (int j = 0; j < rozmiarPlanszy; ++j) {

            pion[i][j].doExists(0);
        }
    }
    pion[0][0].doExists(1);
    pion[0][0].setGracz(1);

    pion[6][0].doExists(1);
    pion[6][0].setGracz(0);

    pion[0][6].doExists(1);
    pion[0][6].setGracz(0);


    pion[6][6].doExists(1);
    pion[6][6].setGracz(1);


    brick[2][2].doExists(1);
    brick[4][2].doExists(1);
    brick[2][4].doExists(1);
    brick[4][4].doExists(1);
    brick[3][3].doExists(1);

    UpdatePoints();     //reset punktow

    if (gra.WhoseTurn() == 0)
        gra.ChangeTurn();
}
void Plansza::level5()
{
    //Przywrócenie pionów do stanu pocz¹tkowego

    for (int i = 0; i < rozmiarPlanszy; ++i) {
        for (int j = 0; j < rozmiarPlanszy; ++j) {

            pion[i][j].doExists(0);
        }
    }
    pion[0][0].doExists(1);
    pion[0][0].setGracz(1);

    pion[6][0].doExists(1);
    pion[6][0].setGracz(0);

    pion[0][6].doExists(1);
    pion[0][6].setGracz(0);


    pion[6][6].doExists(1);
    pion[6][6].setGracz(1);


    brick[1][1].doExists(1);
    brick[5][1].doExists(1);
    brick[1][5].doExists(1);
    brick[5][5].doExists(1);

    UpdatePoints();     //reset punktow

    if (gra.WhoseTurn() == 0)
        gra.ChangeTurn();
}

void Plansza::ChooseMode(sf::RenderWindow& window, sf::Vector2f point,bool click)
{

    if (!font.loadFromFile("RAVIE.TTF"))
    {
        // error...
    }
    mode.setFont(font);
    sp.setFont(font);
    mp.setFont(font);

    mode.setPosition(330, 200);
    mode.setCharacterSize(40);
    mode.setFillColor(sf::Color(255, 255, 255, 255));
    mode.setString("Choose Mode:");

    sp.setPosition(330, 330);
    sp.setCharacterSize(40);
    sp.setFillColor(sf::Color(255, 255, 255, 255));
    sp.setString("1 Player");

    mp.setPosition(330, 430);
    mp.setCharacterSize(40);
    mp.setFillColor(sf::Color(255, 255, 255, 255));
    mp.setString("2 Players");

    if (sp.getGlobalBounds().contains(point))
    {
        sp.setFillColor(sf::Color::Yellow);
        if (click == 1)
        {
            gameMode = 0;
            gameStarted = 1;
        }
    }
    if (mp.getGlobalBounds().contains(point))
    {
        mp.setFillColor(sf::Color::Yellow);
        if (click == 1)
        {
            gameMode = 1;
            gameStarted = 1;
        }
    }

    window.draw(mode);
    window.draw(sp);
    window.draw(mp);

}

bool Plansza::isStarted()
{
    return gameStarted;
}