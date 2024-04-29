#pragma once
#include"Guy.h"

//Nombre d'obstacle sur la fenêtre
const int n_obstacle = 5;

class jeu{
    //Le Guy du jeu
    Guy guy;

    //On crée un tableau pour les premiers obstacles du jeu (Les triangles)
    obstacle_1 T[n_obstacle];

public:
    jeu();
    void dessin(int t) const;
    void action(int t);
};
