#include "FichierUtilisateur.h"
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

int estPresent(const char* nom)
{
  int fch, lenghtFile;
  UTILISATEUR user;

  fch = open(FICHIER_UTILISATEURS, O_RDONLY);
  if(fch == -1){
    return fch;
  }

  if((lenghtFile = lseek(fch, 0, SEEK_END)) == -1){
    close(fch);
    return lenghtFile;
  }
  lseek(fch, 0, SEEK_SET);

  int i, verif, index = -1;
  for(i = 1; i <= lenghtFile/24; i++){
    verif = read(fch, &user, sizeof(UTILISATEUR));
    if(verif == -1){i = lenghtFile + 1;}
    if(strcmp(user.nom, nom) == 0){
      index = i;
      i = lenghtFile + 1;
    }  
  }
  close(fch);
  if(index == -1){return 0;}
  return index;
}

////////////////////////////////////////////////////////////////////////////////////
int hash(const char* motDePasse)
{
  int i, somme = 0;
  for(i = 0; motDePasse[i] != '\0'; i++){
    somme = somme + motDePasse[i] * (i + 1);
  }
  somme = somme%97;
  return somme;
}

////////////////////////////////////////////////////////////////////////////////////
void ajouteUtilisateur(const char* nom, const char* motDePasse)
{
  int FICHIER;
  UTILISATEUR newUser;

  strcpy(newUser.nom, nom);
  newUser.hash = hash(motDePasse);

  FICHIER = open(FICHIER_UTILISATEURS, O_WRONLY | O_APPEND);
  if(FICHIER == -1){
    FICHIER = open(FICHIER_UTILISATEURS, O_CREAT | O_WRONLY, 0766);
  }
  write(FICHIER, &newUser, sizeof(UTILISATEUR));
  close(FICHIER);
}

////////////////////////////////////////////////////////////////////////////////////
int verifieMotDePasse(int pos, const char* motDePasse)
{
  int fch, numHash, verif;
  UTILISATEUR user;

  fch = open(FICHIER_UTILISATEURS, O_RDONLY);
  if(fch == -1){
    return fch;
  }
  numHash = hash(motDePasse);
  lseek(fch, pos*sizeof(UTILISATEUR),SEEK_SET);
  verif = read(fch, &user, sizeof(UTILISATEUR));
  if(verif == -1){return verif;}
  printf("%d %d", numHash, user.hash);
  if(user.hash == numHash){
    return 1;
  }
  else{
    return 0;
  }
}

////////////////////////////////////////////////////////////////////////////////////
int listeUtilisateurs(UTILISATEUR *vecteur) // le vecteur doit etre suffisamment grand
{
  int fch, lenghtFile;
  UTILISATEUR user;

  fch = open(FICHIER_UTILISATEURS, O_RDONLY);
  if(fch == -1){
    return fch;
  }

  if((lenghtFile = lseek(fch, 0, SEEK_END)) == -1){
    close(fch);
    return lenghtFile;
  }
  lseek(fch, 0, SEEK_SET);

  int i, verif;
  for(i = 0; i < lenghtFile/24; i++){
    verif = read(fch, &vecteur[i], sizeof(UTILISATEUR));
    if(verif == -1){i = lenghtFile + 1;}
  }
  close(fch);
  return lenghtFile/sizeof(UTILISATEUR);
}
