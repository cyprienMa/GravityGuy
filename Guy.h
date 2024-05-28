#pragma once
#include <random>
int const w = 1000;
int const h = 600;

// Dimensions et position du Guy
const int wGuy = 60;
const int hGuy = 60;
const int xGuy = 25;

//Durée du saut
const int t_saut = 20;
//Hauteur du saut
const int h_saut_facile = 4*hGuy;
const int h_saut = 3*hGuy;
//Durée du changement de gravité
const int t_gravity = 20;

//Vitesse du jeu
const int vitesse = 8;
const int v2 = 1.10*vitesse;
const int v3 = 1.25*vitesse;

//Vitesse du jeu pour le niveau 2
const int vitesse_2 = 14;
const int v2_2 = 1.10*vitesse_2;
const int v3_2 = 1.25*vitesse_2;

//Hauteur d'un obstacle
const int h_obstacle =  60;
//Nombre d'obstacle sur la fenêtre
const int n_obstacle = 3;

//Epaisseur du haut et du bas
const int e_h = 20;
const int e_b = 20;


class obstacle{
    int tInit, xInit;
public:
    obstacle();
    void set(int t, int x);
    int center_1(int t) const;
    int center_2(int t) const;
    int center_3(int t) const;

    int center_1_2(int t) const;
    int center_2_2(int t) const;
    int center_3_2(int t) const;
};

class Guy{
    int t; //Date du début du dernier saut du Guy
    int ts; //Date du début du dernier switch de gravité du Guy
    bool state; //Indique si le Guy est au sol ou pas
    bool previous_state;
public:
    Guy();
    void saut(int t0);
    void switch_gravity(int t0);

    bool check_saut(int t0) const;
    bool check_gravity(int t0) const;
    bool check_state(int t0) const;

    float hauteur_1(int t0) const;
    float hauteur_2(int t0) const;
    bool collision(const obstacle t[], int t0) const;
    bool collision2(const obstacle t[], int t0) const;
};
