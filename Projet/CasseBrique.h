#ifndef CASSE_BRIQUE_HEADER
#define CASSE_BRIQUE_HEADER
#include <string>
#include <vector>
#include "EcranASCII.h"

struct Balle{
public:
  float posXBalle = 1;
  float posYBalle = 1;
  float vDirX = 1;
  float vDirY = 1;  
};

struct Brique3x1
{
  int posXBrique;
  int posYBrique;
  int resistance = 1;

  Brique3x1(int posXB, int posYB)
  {
    posXBrique = posXB;
    posYBrique = posYB;
  };

  bool collision(Balle & b)
  {
    // Balle en dessous de Brique3x1
    if(b.posYBalle == posYBrique-1 && (b.posXBalle == posXBrique ||b.posXBalle == posXBrique-1 ||b.posXBalle == posXBrique+1 ||b.posXBalle == posXBrique+2||b.posXBalle == posXBrique-2))
    {
      return true;
    }
    // Balle au dessus de Brique3x1
    else if(b.posYBalle == posYBrique+1 && (b.posXBalle == posXBrique ||b.posXBalle == posXBrique-1 ||b.posXBalle == posXBrique+1 ||b.posXBalle == posXBrique+2||b.posXBalle == posXBrique-2))
    {
      return true;
    }
    else
    {
      return false;
    }
    
  };
};


class CasseBrique {

  std::vector <Brique3x1> monVectBriques;
  int posXJoueur = 3;
  int posYJoueur = 3;

  Balle balle;
  EcranASCII monEcran;
  
public:
  CasseBrique(const EcranASCII &unEcran);
  void miseAjour();
  void miseAjourVectVitesse(Balle & balle);
  void deplaceJoueurDroite();
  void deplaceJoueurGauche();
  void initJoueur();
  
private:
  int score = 0;
  
};



#endif

