#pragma once
#include <vector>
#include <iostream>
#include <array>
#include <string>
#include <utility>

using namespace std;


int rand_1_porte(int); //renvoye un nombre entre 1 et nbPorte
bool MontyHallXPorte(int); //va faure marcher le jeu pour x portes

// Nouvelle fonction pour récupérer les pourcentages de victoire
std::pair<double, double> GetMontyHallStats(double nombreIterance, int nbPortes);