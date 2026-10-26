#include "FichierUtilisateur.h"
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

int estPresent(const char* nom)
{
  int FICHIER;
  UTILISATEUR User;

  FICHIER = open(FICHIER_UTILISATEURS, O_RDONLY);
  if(FICHIER == -1){
    perror("erreur fichier");
    return FICHIER;
  }
  read(FICHIER, &User, sizeof(UTILISATEUR)); //lseek pour le déplacement

  printf("Affichage de la lecture");
  printf("%d\n", User.hash);
  puts(User.nom);

  close(FICHIER);
  return 1;
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
  UTILISATEUR NewUser;
  strcpy(NewUser.nom, nom);
  NewUser.hash = hash(motDePasse);
  printf("Verification copie dans NewUser: \n");
  puts(NewUser.nom);
  printf("%d\n", NewUser.hash);
  FICHIER = open(FICHIER_UTILISATEURS, O_WRONLY | O_APPEND, 0750);
  if(FICHIER == -1){
    FICHIER = open(FICHIER_UTILISATEURS, O_CREAT | O_WRONLY, 0750);
  }
  write(FICHIER, &NewUser, sizeof(UTILISATEUR));
  printf("Retour close : %d \n",close(FICHIER));
}

////////////////////////////////////////////////////////////////////////////////////
int verifieMotDePasse(int pos, const char* motDePasse)
{
  // TO DO
  return 0;
}

////////////////////////////////////////////////////////////////////////////////////
int listeUtilisateurs(UTILISATEUR *vecteur) // le vecteur doit etre suffisamment grand
{
  // TO DO
  return 0;
}
