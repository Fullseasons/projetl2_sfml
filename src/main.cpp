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


void drawPieChart(sf::RenderWindow &window, float stayPercentage, float switchPercentage) { //* Va creer un camembert
    const float radius = 200.f; //? Rayon du graphique
    const sf::Vector2f center(400, 300); //? Centre du graphique

    // *Partie "Stay" (verte)
    sf::VertexArray staySlice(sf::TriangleFan);
    staySlice.append(sf::Vertex(center, sf::Color::Green)); // *Ajouter le centre

    float endAngle = stayPercentage * 360.f;
    for (float angle = 0.f; angle <= endAngle; angle += 1.f) {
        float rad = angle * (M_PI / 180.f);
        sf::Vector2f point(center.x + radius * cos(rad), center.y + radius * sin(rad));
        staySlice.append(sf::Vertex(point, sf::Color::Green));
    }
    staySlice.append(sf::Vertex(sf::Vector2f(
        center.x + radius * cos(endAngle * (M_PI / 180.f)),
        center.y + radius * sin(endAngle * (M_PI / 180.f))
    ), sf::Color::Green));
    window.draw(staySlice);

    // Partie "Switch" (rouge)
    sf::VertexArray switchSlice(sf::TriangleFan);
    switchSlice.append(sf::Vertex(center, sf::Color::Red)); // *Ajouter le centre

    float startAngle = endAngle;
    float totalAngle = startAngle + (switchPercentage * 360.f);
    for (float angle = startAngle; angle <= totalAngle; angle += 1.f) {
        float rad = angle * (M_PI / 180.f);
        sf::Vector2f point(center.x + radius * cos(rad), center.y + radius * sin(rad));
        switchSlice.append(sf::Vertex(point, sf::Color::Red));
    }
    switchSlice.append(sf::Vertex(sf::Vector2f(
        center.x + radius * cos(totalAngle * (M_PI / 180.f)),
        center.y + radius * sin(totalAngle * (M_PI / 180.f))
    ), sf::Color::Red));
    window.draw(switchSlice);
}



int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Monty Hall Simulation");

    sf::Font font;
    if (!font.loadFromFile("../assets/fonts/arial.ttf")) {
        cerr << "Erreur lors du chargement de la police." << endl;
        return -1;
    }

    sf::Text title("Monty Hall Simulation", font, 30);
    title.setPosition(250, 10);

    sf::Text seedText("Seed:", font, 20);
    seedText.setPosition(50, 50);

    sf::Text iterText("Iterations:", font, 20);
    iterText.setPosition(50, 100);

    sf::Text doorsText("Nombre de portes:", font, 20);
    doorsText.setPosition(50, 150);

    sf::String seedInput, iterInput, doorsInput;

    sf::Text seedDisplay("", font, 20);
    seedDisplay.setPosition(250, 50);

    sf::Text iterDisplay("", font, 20);
    iterDisplay.setPosition(250, 100);

    sf::Text doorsDisplay("", font, 20);
    doorsDisplay.setPosition(250, 150);

    sf::Text startText("Appuyez sur Entrer pour commencer", font, 30);
    startText.setPosition(50, 200);
    

    bool showResults = false;
    double stayPercentage = 0, switchPercentage = 0;
    int activeField = 0;



    while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();

        if (event.type == sf::Event::TextEntered) {
            if (event.text.unicode == '\b') { // Backspace
                if (activeField == 0 && !seedInput.isEmpty()) {
                    seedInput.erase(seedInput.getSize() - 1, 1);
                } else if (activeField == 1 && !iterInput.isEmpty()) {
                    iterInput.erase(iterInput.getSize() - 1, 1);
                } else if (activeField == 2 && !doorsInput.isEmpty()) {
                    doorsInput.erase(doorsInput.getSize() - 1, 1);
                }
            } else if (event.text.unicode < 128) { // Characters
                char inputChar = static_cast<char>(event.text.unicode);
                if (isdigit(inputChar)) { // Only accept digits
                    if (activeField == 0) seedInput += inputChar;
                    if (activeField == 1) iterInput += inputChar;
                    if (activeField == 2) doorsInput += inputChar;
                }
            }
        }

        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Enter) {
                // When Enter is pressed, parse inputs and start the simulation
                if (!seedInput.isEmpty() && !iterInput.isEmpty() && !doorsInput.isEmpty()) {
                    int seed = stoi(seedInput.toAnsiString());
                    int iterations = stoi(iterInput.toAnsiString());
                    int doors = stoi(doorsInput.toAnsiString());
                    srand(seed);

                    // Calculate stats
                    auto results = GetMontyHallStats(iterations, doors);
                    stayPercentage = results.first;
                    switchPercentage = results.second;

                    showResults = true; // Switch to results display
                } else {
                    activeField = (activeField + 1) % 3;
                }
            }else if (event.key.code == sf::Keyboard::Tab) {
                activeField = (activeField + 1) % 3; // Passer au champ suivant
            }
        }
    }

    window.clear();

    if (!showResults) {
        // Draw input fields
        seedDisplay.setString(seedInput);
        iterDisplay.setString(iterInput);
        doorsDisplay.setString(doorsInput);

        // Highlight active field
        if (activeField == 0) seedDisplay.setFillColor(sf::Color::Yellow);
        else seedDisplay.setFillColor(sf::Color::White);

        if (activeField == 1) iterDisplay.setFillColor(sf::Color::Yellow);
        else iterDisplay.setFillColor(sf::Color::White);

        if (activeField == 2) doorsDisplay.setFillColor(sf::Color::Yellow);
        else doorsDisplay.setFillColor(sf::Color::White);

        window.draw(seedText);
        window.draw(iterText);
        window.draw(doorsText);

        window.draw(seedDisplay);
        window.draw(iterDisplay);
        window.draw(doorsDisplay);
        window.draw(startText);

        // Rectangle pour Seed
        sf::RectangleShape seedBox(sf::Vector2f(400, 30));
        seedBox.setPosition(250, 50);
        seedBox.setOutlineThickness(2);
        seedBox.setOutlineColor(activeField == 0 ? sf::Color::Yellow : sf::Color::White);
        seedBox.setFillColor(sf::Color::Black);
        window.draw(seedBox);

        // Rectangle pour Iterations
        sf::RectangleShape iterBox(sf::Vector2f(400, 30));
        iterBox.setPosition(250, 100);
        iterBox.setOutlineThickness(2);
        iterBox.setOutlineColor(activeField == 1 ? sf::Color::Yellow : sf::Color::White);
        iterBox.setFillColor(sf::Color::Black);
        window.draw(iterBox);

        // Rectangle pour Doors
        sf::RectangleShape doorsBox(sf::Vector2f(400, 30));
        doorsBox.setPosition(250, 150);
        doorsBox.setOutlineThickness(2);
        doorsBox.setOutlineColor(activeField == 2 ? sf::Color::Yellow : sf::Color::White);
        doorsBox.setFillColor(sf::Color::Black);
        window.draw(doorsBox);

        seedDisplay.setString(seedInput);
        seedDisplay.setPosition(260, 50);
        window.draw(seedDisplay);

        iterDisplay.setString(iterInput);
        iterDisplay.setPosition(260, 100);
        window.draw(iterDisplay);

        doorsDisplay.setString(doorsInput);
        doorsDisplay.setPosition(260, 150);
        window.draw(doorsDisplay);

    } else {
        // Draw the pie chart and results
        drawPieChart(window, stayPercentage, switchPercentage);

        sf::Text stayText("Rester: " + to_string(stayPercentage * 100) + "%", font, 20);
        stayText.setFillColor(sf::Color::Green);
        stayText.setPosition(50, 500);

        sf::Text switchText("Changer: " + to_string(switchPercentage * 100) + "%", font, 20);
        switchText.setFillColor(sf::Color::Red);
        switchText.setPosition(400, 500);

        window.draw(stayText);
        window.draw(switchText);
    }

    window.display();
}


    return 0;
}