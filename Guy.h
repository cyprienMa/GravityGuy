#pragma once
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

//Hauteur d'un obstacle
const int h_obstacle = 3*hGuy/4;


class Guy{
    int t; //Date du début du dernier saut du Guy
public:
    Guy();
    void saut(int t0);
    bool check_saut(int t0) const;
    int hauteur(int t0) const;
};

class obstacle_1{
    int tInit, xInit;
public:
    obstacle_1();
    void set(int t, int x);
    int center(int t) const;
    bool reInit(int t, int xBase);
};
