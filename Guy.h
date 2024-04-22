#pragma once
int const w = 500;
int const h = 300;

// Dimensions et position du Guy
const int wGuy=20;
const int hGuy=30;
const int xGuy=25;

const int t_saut=20; //Durée du saut
const int h_saut=3*hGuy;

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

};
