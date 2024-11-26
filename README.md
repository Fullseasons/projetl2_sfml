# Simulation de Monty Hall avec SFML

Ce projet propose une simulation graphique du problème de Monty Hall, réalisée en C++ avec la bibliothèque [SFML](https://www.sfml-dev.org/). L'utilisateur peut configurer les paramètres de simulation (seed, nombre d'itérations, nombre de portes) et visualiser les résultats sous forme de graphique en camembert.

## Fonctionnalités

- **Interface interactive** :
  - Permet de définir la seed, le nombre d'itérations et le nombre de portes.
  - Navigation entre les champs avec la touche Entrer.
  - Mise en surbrillance du champ actif.

- **Simulation** :
  - Simulation du problème de Monty Hall avec 3 portes ou un nombre personnalisé de portes.
  - Compare les taux de succès entre "Rester" et "Changer".

- **Visualisation des résultats** :
  - Affichage d'un graphique en camembert représentant les taux de succès.
  - Affichage des pourcentages numériques pour "Rester" et "Changer".

## Prérequis

- Un compilateur compatible avec C++17.
- [SFML 2.5.1+](https://www.sfml-dev.org/) installée sur votre système.

## Installation

1. Clonez le dépôt :

   ```bash
   git clone https://github.com/votreutilisateur/simulation-monty-hall.git
   cd simulation-monty-hall
  
