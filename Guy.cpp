#include "Guy.h"
#include <Imagine/Graphics.h>
#include <algorithm>
using namespace Imagine;

//On initialise un Guy au sol
Guy::Guy() {
    t = -t_saut;
}

//On actualise la valeur de t quand le Guy saute
void Guy::saut(int t0) {
    t = t0;
}

//On vérifie si le Guy est en train de sauter
bool Guy::check_saut(int t0) const {
    return t<=t0 && t0<=t+t_saut;
}

void Guy::switch_gravity(int t0) {
    ts = t0;
    state = !state;
}

bool Guy::check_gravity(int t0) const {
    return ts<=t0 && t0<=ts+t_gravity;
}

//Si le Guy est en train de sauter, alors on calcule sa hauteur
int Guy::hauteur(int t0) const {
    float H = 0;
    if(check_saut(t0)) {
        float x = 1-2*(t0-t)/(float)t_saut;  //La trajectoire du Guy suit une parabole ce qui nous donne sa hauteur
        H=h_saut*(1-x*x);
    }

    if(state){
        if(check_gravity(t0)){

    }
    return H;
}

void obstacle::set(int t, int x) {
    tInit=t;
    xInit=x;
}
//On initialise les paramètres de l'obstacle: t=0 et x=10001
obstacle::obstacle() {
    set(0, 1000);
}

//Renvoie le centre de l'obstacle de la première phase
int obstacle::center_1(int t) const {
    return xInit-(t-tInit)*vitesse;
}

//Renvoie le centre de l'obstacle de la seconde phase
int obstacle::center_2(int t) const {
    return xInit-(t-tInit)*v2;
}

//Renvoie le centre de l'obstacle de la troisième phase
int obstacle::center_3(int t) const {
    return xInit-(t-tInit)*v3;
}

