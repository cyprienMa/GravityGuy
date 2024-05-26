#pragma once
#include"Guy.h"

//Nombre d'obstacle sur la fenêtre
const int n_obstacle = 15;

class jeu{
    //Le Guy du jeu
    Guy guy;

    //On crée un tableau pour les premiers obstacles du jeu (Les triangles)
    obstacle T[n_obstacle*3];

public:
    jeu();
    void dessin(int t) const;
    void action(int t);
    void menu();
};
