#pragma once
#include <vector>
#include <iostream>
#include <array>
#include <string>
#include <utility>

using namespace std;


int rand_1_3(); //renvoie un nombre aleatoire entre 1 et 3
bool MontyHall(); //fait marcher le jeu pour 3 portes (return 1 si win en restant, 0 en changeant)
void SuiviStat(double); //va permettre de stocker le nombre win/lose
int rand_1_porte(int); //renvoye un nombre entre 1 et nbPorte
bool MontyHallXPorte(int); //va faure marcher le jeu pour x portes
void SuiviStatXPortes(double, int); //meme que suivitstat mais pour X portes

// Nouvelle fonction pour récupérer les pourcentages de victoire
std::pair<double, double> GetMontyHallStats(double nombreIterance, int nbPortes);