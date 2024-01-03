/*
Voilà comment compiler et lier les libraires :

g++ -c library.cpp -o library.o    # Compile la bibliothèque en un fichier objet
g++ -c main_prog.cpp -o main_prog.o  # Compile le programme principal en un fichier objet

g++ library.o main_prog.o -o mon_programme  # Lie les fichiers objets pour créer l'exécutable
*/

#include "CasseBrique.h"
#include "EcranASCII.h"
#include <unistd.h>
#include <iostream>
#include <sys/ioctl.h>
#include <termios.h>



void enable_raw_mode()
{
    termios term;
    tcgetattr(0, &term);
    term.c_lflag &= ~(ICANON | ECHO); // Disable echo as well
    tcsetattr(0, TCSANOW, &term);
}

void disable_raw_mode()
{
    termios term;
    tcgetattr(0, &term);
    term.c_lflag |= ICANON | ECHO;
    tcsetattr(0, TCSANOW, &term);
}

bool kbhit()
{
    int byteswaiting;
    ioctl(0, FIONREAD, &byteswaiting);
    return byteswaiting > 0;
}


void
jeuBouclePrincipale(CasseBrique & monCasseBrique)
{
//__________Partie I________________
//__________Partie II_______________
   enable_raw_mode();
   unsigned char a;
   if(kbhit())
   {
    a = getchar();
   }

   while (a != 'x'){
     //rax mode : mode brut =  sans mise en mémoire tampon ni traitement spécial
    enable_raw_mode();
    if(kbhit()) //kbhit : frappe de clavier en attente?
    {
      a = getchar();
      if(a == 'a')
      {
        //std:: cout << "touche tapé: a" << std::endl;
        monCasseBrique.deplaceJoueurGauche();
      }
       else if(a == 'z')
      {
        //std::cout << "touche tapé: z" << std::endl;
        monCasseBrique.deplaceJoueurDroite();
      }
      else{
        //sortie;
      }
      monCasseBrique.miseAjour();
      disable_raw_mode();
      tcflush(0, TCIFLUSH); //vide le tampon d'entrée.
    }
    usleep(10000); 
  }
  disable_raw_mode();
  tcflush(0, TCIFLUSH);
}


void testEcran()
{
  EcranASCII monEcran(20,30);
  monEcran.reglePixel(1,1,EcranASCII::TypePixels::Balle);
  monEcran.reglePixel(3,1,EcranASCII::TypePixels::Balle);
  monEcran.reglePixel(3,3,EcranASCII::TypePixels::Balle);
  monEcran.reglePixel(1,3,EcranASCII::TypePixels::Balle);
  monEcran.reglePixel(4,4,EcranASCII::TypePixels::Joueur);

  monEcran.reglePixel(monEcran.monHauteur/2,monEcran.monLargeur/2,EcranASCII::TypePixels::Balle);
  monEcran.rafraichir();
  /*
  // Faire deplacer un pixel horizentalement de 50 pixels
  int retour_debut_ligne = monEcran.monLargeur -2 ;
  for (int j = 0; j < 51 ; j++)
  {
    monEcran.efface();
    monEcran.reglePixel(1,(j%retour_debut_ligne)+1,EcranASCII::TypePixels::Balle);
    monEcran.rafraichir();
    usleep(100000);
  }
  */
}

int main(int argc, char * argv[])
{
//__________Partie I________________
  //testEcran();
  //jeuBouclePrincipale();

//__________Partie II________________
  EcranASCII unEcran(20,10);
  CasseBrique unCasseBrique(unEcran);
  /*
  for(int i=0;i<10;i++)
  {
    unCasseBrique.deplaceJoueurGauche();
    unCasseBrique.miseAjour();
    usleep(300000);
  }
  */
  unCasseBrique.miseAjour();
  jeuBouclePrincipale(unCasseBrique);

  return EXIT_SUCCESS;
}






