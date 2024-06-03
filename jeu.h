#pragma once
#include"Guy.h"
#include <Imagine/Graphics.h>
#include <Imagine/Images.h>
#include <iostream>
#include <algorithm>
using namespace Imagine;
using namespace std;
class jeu{
    //Le Guy du jeu
    Guy guy;

    //On crée un tableau pour les obstacles
    obstacle T[n_obstacle*5 + 5];
    obstacle Rect_haut;

    //On charge les images
    NativeBitmap my_native_bitmap_ville;
    NativeBitmap my_native_bitmap_triangle;
    NativeBitmap my_native_bitmap_rect;
    NativeBitmap my_native_bitmap_lava;
    NativeBitmap my_native_bitmap_sol;
    Image<AlphaColor> Img_guy;
    Image<AlphaColor> Img_guy_upside;
    Image<AlphaColor> Img_boom;
    NativeBitmap my_native_bitmap_losange;
    NativeBitmap my_native_bitmap_rond;

public:
    jeu();
    int init();

    void dessin(int t) const;
    void dessin2(int t) const; //Pour le niveau 2

    void action(int t);
    int menu();

    bool collision(int t) const;
    bool collision2(int t) const;//Pour le niveau 2
};


void makeBackgroundTransparent(Image<AlphaColor>& img, AlphaColor backgroundColor);
