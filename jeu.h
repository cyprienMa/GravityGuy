#pragma once
#include"Guy.h"

class jeu{
    //Le Guy du jeu
    Guy guy;

    //On crée un tableau pour les premiers obstacles du jeu (Les triangles)
    obstacle T[n_obstacle*4];

public:
    jeu();
    void dessin(int t) const;
    void action(int t);
    void menu();
    bool collision(int t) const;
};
