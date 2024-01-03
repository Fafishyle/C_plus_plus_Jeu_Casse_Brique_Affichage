#include "CasseBrique.h"
#include <string>
#include <iostream>
#include <vector>

CasseBrique::CasseBrique(const EcranASCII &unEcran): monEcran(unEcran){
  initJoueur();
  // Initialisation Brique
  for (int x = 2 ; x< monEcran.monLargeur-1 ; x=x+4)
  {
    for(int y = monEcran.monHauteur-2 ; y >= monEcran.monHauteur*5/6 ; y=y-2)
    {
      Brique3x1 uneBrique(x,y);
      monVectBriques.push_back(uneBrique);
    }
  }
}


void
CasseBrique::initJoueur(){
  // Initialisation Joueur
  posXJoueur = monEcran.monLargeur/2;
  posYJoueur = 1;
  // Initialisation Balle
  balle.posXBalle = monEcran.monLargeur/2;
  balle.posYBalle = monEcran.monHauteur/2; ;
  balle.vDirX = 1 ;
  balle.vDirY = -1 ;
}

void
CasseBrique::deplaceJoueurDroite(){
  posXJoueur = (posXJoueur + 1)%monEcran.monLargeur;
}

void
CasseBrique::deplaceJoueurGauche(){
  posXJoueur --;
  if(posXJoueur<0)
  {
    posXJoueur=monEcran.monLargeur-1;
  }
}


void
CasseBrique::miseAjour(){
  std::cout<<"Joueur :  X : " << posXJoueur<<"  | Y : " << posYJoueur;
  std::cout<<"  | Balle :  X : " << balle.posXBalle<<"  | Y : " << balle.posYBalle;
  //std::cout<<" Vecteur :  X : " << balle.vDirX<<"  | Y : " << balle.vDirX;
  std::cout<<" BriqueLast :  Resist : " << monVectBriques.back().resistance;

  monEcran.efface();

  // Affichage Joueur
  monEcran.reglePixel(posYJoueur,posXJoueur,EcranASCII::TypePixels::Joueur);
  // Affichage Balle
  monEcran.reglePixel(balle.posYBalle,balle.posXBalle,EcranASCII::TypePixels::Balle);
  // Affichage Brique 3x1
  for(auto uneBrique : monVectBriques)
  {
    if (uneBrique.resistance == 1)
    {
      monEcran.reglePixel(uneBrique.posYBrique,uneBrique.posXBrique,EcranASCII::TypePixels::Brique3x1);
      monEcran.reglePixel(uneBrique.posYBrique,uneBrique.posXBrique+1,EcranASCII::TypePixels::Brique3x1);
      monEcran.reglePixel(uneBrique.posYBrique,uneBrique.posXBrique-1,EcranASCII::TypePixels::Brique3x1);
    }
    
  }
  monEcran.rafraichir();
  //monEcran.reglePixel(posYJoueur,posXJoueur,EcranASCII::TypePixels::Fond);
  //monEcran.reglePixel(balle.posYBalle,balle.posXBalle,EcranASCII::TypePixels::Fond);
  // mis a jour position balle avec vitesse
  miseAjourVectVitesse(balle);
  balle.posXBalle += balle.vDirX;
  balle.posYBalle += balle.vDirY;
}

void
CasseBrique::miseAjourVectVitesse(Balle & b)
{

  //______GESTION DES COLLISIONS COINS______________
  //si diagonal bas-gauche
  if(b.posYBalle == 0 && b.posXBalle == 0)
  {
    b.vDirY = balle.vDirY * -1 ;
    b.vDirX = balle.vDirX * -1 ;
  }
  //si diagonal bas-droite
  else if(b.posYBalle == 0 && b.posXBalle == monEcran.monLargeur-1)
  {
    b.vDirY = balle.vDirY * -1 ;
    b.vDirX = balle.vDirX * -1 ;
  }
  //si diagonal haut-gauche
  else if(b.posYBalle == monEcran.monHauteur-1 && b.posXBalle == 0)
  {
    b.vDirY = balle.vDirY * -1 ;
    b.vDirX = balle.vDirX * -1 ;
  }
  //si diagonal haut-droite
  else if(b.posYBalle == monEcran.monHauteur-1 && b.posXBalle == monEcran.monLargeur-1)
  {
    b.vDirY = balle.vDirY * -1 ;
    b.vDirX = balle.vDirX * -1 ;
  }
  //______GESTION DES BORDS_________________________
  //si bord est OK
  else if(b.posXBalle > monEcran.monLargeur-2)
  {
    b.vDirX *= -1 ;
    //std::cout<<"bord est";
  }
  //si bord ouest OK
  else if(b.posXBalle <= 0)
  {
    b.vDirX *= -1 ;
    //std::cout<<"bord ouest";
  }
  //si bord nord OK
  else if(b.posYBalle > monEcran.monHauteur-2)
  {
    b.vDirY *= -1 ;
    //std::cout<<"bord nord";
  }
  //si bord sud OK
  else if(b.posYBalle <= 0)
  {
    b.vDirY = balle.vDirY * -1 ;
    //std::cout<<"bord sud";
  }
  
  //______GESTION DES COLLISIONS JOUEURS_________________
  //si touche le joueur en dessous
  else if(b.posYBalle-1 == posYJoueur && b.posXBalle == posXJoueur)
  {
    b.vDirY = balle.vDirY * -1 ;
  }
  //si touche le joueur au dessus
  else if(b.posYBalle+1 == posYJoueur && b.posXBalle == posXJoueur)
  {
    b.vDirY = balle.vDirY * -1 ;
  }
  //si touche le joueur en diagonal droite 
  else if(b.posYBalle-1 == posYJoueur && b.posXBalle-1 == posXJoueur)
  {
    b.vDirY = balle.vDirY * -1 ;
  }
  //si touche le joueur en diagonal gauche
  else if(b.posYBalle-1 == posYJoueur && b.posXBalle+1 == posXJoueur)
  {
    b.vDirY = balle.vDirY * -1 ;
  }
  
  //______GESTION DES COLLISIONS BRIQUES_________________
  else
  {
    int compteur = 0;
    for (int i = 0 ; i<monVectBriques.size() ; i++)
    {
      if(monVectBriques[i].collision(b) && monVectBriques[i].resistance == 1)
      {
        monVectBriques[i].resistance = 0;
        b.vDirY = b.vDirY * -1 ;
      }
    }
  }

}