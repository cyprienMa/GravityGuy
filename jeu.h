#pragma once
#include"Guy.h"

class jeu{
    //Le Guy du jeu
    Guy guy;

    //On crée un tableau pour les obstacles
    obstacle T[n_obstacle*6];
    obstacle Rect_haut;

public:
    jeu();
    void dessin(int t) const;
    void action(int t);
    void menu();
    bool collision(int t) const;
};
