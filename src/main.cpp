#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include <iostream>
#include <cstdlib>
#include <sstream>
#include <time.h>
#include <vector>
#include <cmath>
#include <array>

#include "basic_function.cpp"

using namespace std;


void drawPieChart(sf::RenderWindow &window, float stayPercentage, float switchPercentage) { //? Va creer un camembert
    const float radius = 200.f; //? Rayon du graphique
    const sf::Vector2f center(400, 300); //? Centre du graphique

    // *Partie "Rester" (verte)
    sf::VertexArray staySlice(sf::TriangleFan); //* Part du centre et rejoins tout les points
    staySlice.append(sf::Vertex(center, sf::Color::Green)); // *Ajouter le centre

    
    float endAngle = stayPercentage * 360.f;  //* angle * pourcentage pour avoir la taille voulue
    for (float angle = 0.f; angle <= endAngle; angle += 1.f) { //* Va parcourir tout les angles et prendre les coords
        float rad = angle * (M_PI / 180.f);
        sf::Vector2f point(center.x + radius * cos(rad), center.y + radius * sin(rad)); //* cos et sin pour les coords x et y
        staySlice.append(sf::Vertex(point, sf::Color::Green)); //* Ajout du point pour toute coordonnée
    }
    staySlice.append(sf::Vertex(sf::Vector2f( //* Ajout du dernier point 
        center.x + radius * cos(endAngle * (M_PI / 180.f)),
        center.y + radius * sin(endAngle * (M_PI / 180.f))
    ), sf::Color::Green));
    window.draw(staySlice); //* Dessin de la partie voulue

    //! Partie "Changer" (rouge)
    sf::VertexArray switchSlice(sf::TriangleFan);
    switchSlice.append(sf::Vertex(center, sf::Color::Red)); // !Ajouter le centre

    float startAngle = endAngle; //! commence à la fin de stay et fini au début
    float totalAngle = startAngle + (switchPercentage * 360.f);
    for (float angle = startAngle; angle <= totalAngle; angle += 1.f) { //! ajout tout les points de tout les angles
        float rad = angle * (M_PI / 180.f);
        sf::Vector2f point(center.x + radius * cos(rad), center.y + radius * sin(rad));
        switchSlice.append(sf::Vertex(point, sf::Color::Red));
    }
    switchSlice.append(sf::Vertex(sf::Vector2f( //!dernier point
        center.x + radius * cos(totalAngle * (M_PI / 180.f)),
        center.y + radius * sin(totalAngle * (M_PI / 180.f))
    ), sf::Color::Red));
    window.draw(switchSlice); //! Dessin
}




int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Monty Hall Simulation"); //? Creation de la fenetre

    sf::Font font; //? Chargement de la police
    if (!font.loadFromFile("../assets/fonts/Arial.ttf")) {
        cerr << "Erreur lors du chargement de la police." << endl;
        return -1;
    }

    sf::Image icon;
    if(!icon.loadFromFile("../assets/images/icon.png")){
        cerr << "Erreure lors du chargement de l'icon"<<endl;
        return -1;
    }

    window.setIcon(icon.getSize().x, icon.getSize().y,icon.getPixelsPtr());


    //? Partie des textes pour choix seed, porte, interation
    sf::Text title("Monty Hall Simulation", font, 30); 
    title.setPosition(250, 10);

    sf::Text titleText("Simulateur de Monty Hall", font, 30);
    titleText.setStyle(sf::Text::Bold | sf::Text::Underlined);
    titleText.setPosition(50,50);

    sf::Text seedText("Seed:", font, 20);
    seedText.setPosition(50, 100);

    sf::Text iterText("Iterations:", font, 20);
    iterText.setPosition(50, 150);

    sf::Text doorsText("Nombre de portes:", font, 20);
    doorsText.setPosition(50, 200);

    sf::String seedInput, iterInput, doorsInput; //? String pour recup les valeurs


    //? Rectangle de texte
    sf::Text seedDisplay("", font, 20);
    seedDisplay.setPosition(250, 100);

    sf::Text iterDisplay("", font, 20);
    iterDisplay.setPosition(250, 150);

    sf::Text doorsDisplay("", font, 20);
    doorsDisplay.setPosition(250, 200);

    sf::Text startText("Appuyez sur Entrer pour commencer", font, 30);
    startText.setPosition(50, 250);
    

    bool showResults = false; //? Choix entre affichage resultat et choix variable
    double stayPercentage = 0, switchPercentage = 0; //? Pourcentage
    int activeField = 0; //? 0 = seed, 1= interance, 2 = nb portes



    while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();

        if (event.type == sf::Event::TextEntered) { //* Check si tu textes est écrit
            if (event.text.unicode == '\b') { //* Permet d'effacer avec la touche retour
                if (activeField == 0 && !seedInput.isEmpty()) { 
                    seedInput.erase(seedInput.getSize() - 1, 1); 
                } else if (activeField == 1 && !iterInput.isEmpty()) {
                    iterInput.erase(iterInput.getSize() - 1, 1); 
                } else if (activeField == 2 && !doorsInput.isEmpty()) {
                    doorsInput.erase(doorsInput.getSize() - 1, 1); 
                }
            } else if (event.text.unicode < 128) { //* Regarde si du texte est écrit
                char inputChar = static_cast<char>(event.text.unicode); //* Converti en Ascii
                if (isdigit(inputChar)) { //* prend que des chiffres
                    if (activeField == 0) seedInput += inputChar; //*Recup seed
                    if (activeField == 1) iterInput += inputChar; //*Recup iteration
                    if (activeField == 2) doorsInput += inputChar; //*Recup nb Portes
                }
            }
        }

        if (event.type == sf::Event::KeyPressed) { 
            if (event.key.code == sf::Keyboard::Enter) { //* Touche entrée appuyée
                if (!seedInput.isEmpty() && !iterInput.isEmpty() && !doorsInput.isEmpty()) { //* Check si tout les champs sont plein
                    int seed = stoi(seedInput.toAnsiString()); //* Conv string to int et attribu a seed
                    int iterations = stoi(iterInput.toAnsiString()); //* De meme pour iter
                    int doors = stoi(doorsInput.toAnsiString()); //* De meme pour Doors
                    srand(seed); //* Attribution de la seed

                    //? Calcul des Stats
                    auto results = GetMontyHallStats(iterations, doors); //? Recup une pair (auto s'addapte au format return) de resultat
                    stayPercentage = results.first; //? Check Basic_fonction.h
                    switchPercentage = results.second;//? Check Basic_fonction.h

                    showResults = true; //? Lance le resultat (camembert)
                } else {
                    activeField = (activeField + 1) % 3; //! Si enter cliqué et une imput est pas remplie, passe a la suivante
                }
            }else if (event.key.code == sf::Keyboard::Tab) { //! Si tab cliqué et une imput est pas remplie, passe a la suivante
                activeField = (activeField + 1) % 3; // Passer au champ suivant
            }
        }
    }

    window.clear(sf::Color(30,10,50)); //* Clear l'écran
    
    if (!showResults) {
        //* Display le texte a recup
        seedDisplay.setString(seedInput);
        iterDisplay.setString(iterInput);
        doorsDisplay.setString(doorsInput);

        //* Couleur du texte si selec
        if (activeField == 0) seedDisplay.setFillColor(sf::Color::Yellow);
        else seedDisplay.setFillColor(sf::Color::White);

        if (activeField == 1) iterDisplay.setFillColor(sf::Color::Yellow);
        else iterDisplay.setFillColor(sf::Color::White);

        if (activeField == 2) doorsDisplay.setFillColor(sf::Color::Yellow);
        else doorsDisplay.setFillColor(sf::Color::White);

        //* Dessine les texte
        window.draw(titleText);
        window.draw(seedText);
        window.draw(iterText);
        window.draw(doorsText);

        window.draw(seedDisplay);
        window.draw(iterDisplay);
        window.draw(doorsDisplay);
        window.draw(startText);

        //? Rectangle pour Seed
        sf::RectangleShape seedBox(sf::Vector2f(400, 30));
        seedBox.setPosition(250, 100);
        seedBox.setOutlineThickness(2);
        seedBox.setOutlineColor(activeField == 0 ? sf::Color::Yellow : sf::Color::White);
        seedBox.setFillColor(sf::Color::Black);
        window.draw(seedBox);

        //? Rectangle pour Iterations
        sf::RectangleShape iterBox(sf::Vector2f(400, 30));
        iterBox.setPosition(250, 150);
        iterBox.setOutlineThickness(2);
        iterBox.setOutlineColor(activeField == 1 ? sf::Color::Yellow : sf::Color::White);
        iterBox.setFillColor(sf::Color::Black);
        window.draw(iterBox);

        //? Rectangle pour Doors
        sf::RectangleShape doorsBox(sf::Vector2f(400, 30));
        doorsBox.setPosition(250, 200);
        doorsBox.setOutlineThickness(2);
        doorsBox.setOutlineColor(activeField == 2 ? sf::Color::Yellow : sf::Color::White);
        doorsBox.setFillColor(sf::Color::Black);
        window.draw(doorsBox);

        seedDisplay.setString(seedInput);
        seedDisplay.setPosition(260, 100);
        window.draw(seedDisplay);

        iterDisplay.setString(iterInput);
        iterDisplay.setPosition(260, 150);
        window.draw(iterDisplay);

        doorsDisplay.setString(doorsInput);
        doorsDisplay.setPosition(260, 200);
        window.draw(doorsDisplay);

    } else {
        //! Dessine le graph et les resultat
        drawPieChart(window, stayPercentage, switchPercentage);

        sf::Text titleText("Pourcentage de victoire en :", font, 30);
        titleText.setStyle(sf::Text::Bold | sf::Text::Underlined);
        titleText.setFillColor(sf::Color::White);
        titleText.setPosition(200,50);

        sf::Text stayText("Rester sur la porte : \n" + to_string(stayPercentage * 100) + "%", font, 20);
        stayText.setFillColor(sf::Color::Green);
        stayText.setStyle(sf::Text::Bold);
        stayText.setPosition(50, 500);

        sf::Text switchText("Changer de porte : \n" + to_string(switchPercentage * 100) + "%", font, 20);
        switchText.setFillColor(sf::Color::Red);
        switchText.setStyle(sf::Text::Bold);
        switchText.setPosition(550, 500);
        
        window.draw(titleText);
        window.draw(stayText);
        window.draw(switchText);
    }

    
    window.display();
}


    return 0;
}