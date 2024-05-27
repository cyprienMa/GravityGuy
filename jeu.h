#pragma once
#include"Guy.h"

class jeu{
    //Le Guy du jeu
    Guy guy;

    //On crée un tableau pour les obstacles
    obstacle T[n_obstacle*5 + 1];
    obstacle Rect_haut;

public:
    jeu();
    void dessin(int t) const;
    void dessin2(int t) const; //Pour le niveau 2
    void action(int t);
    int menu();
    bool collision(int t) const;
    bool collision2(int t) const;//Pour le niveau 2
};
