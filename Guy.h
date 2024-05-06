#pragma once
#include <random>
int const w = 500;
int const h = 300;

// Dimensions et position du Guy
const int wGuy = 20;
const int hGuy = 30;
const int xGuy = 25;

//Durée du saut
const int t_saut = 20;
//Hauteur du saut
const int h_saut = 3*hGuy;

//Vitesse du jeu
const int vitesse = 8;
const int v2 = 1.10*vitesse;
const int v3 = 1.25*vitesse;

//Hauteur d'un obstacle
const int h_obstacle = 3*hGuy/4;


class Guy{
    int t; //Date du début du dernier saut du Guy
    int ts; //Date du début du dernier switch de gravité du Guy
public:
    Guy();
    void saut(int t0);
    void switch_gravity(int t0);
    bool check_saut(int t0) const;
    int hauteur(int t0) const;
};

class obstacle{
    int tInit, xInit;
public:
    obstacle();
    void set(int t, int x);
    int center_1(int t) const;
    int center_2(int t) const;
    int center_3(int t) const;
};
