#ifndef FICHIER_H
#define FICHIER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NOM 50
#define MAX_ADRESSE 100
#define MAX_LIGNE 256

// Structure pour représenter une personne
typedef struct {
    int id;
    char nom[MAX_NOM];
    int age;
    char adresse[MAX_ADRESSE];
    float point;
    float taille;
} Personne;

// Déclarations des fonctions
void ajouter_personne(const char *nom_fichier);
void supprimer_personne(const char *nom_fichier);
void chercher_personne(const char *nom_fichier);
void modifier_enregistrement(const char *nom_fichier);
void afficher_toutes_personnes(const char *nom_fichier);
void menu(void);
int lire_entier(const char *message);
float lire_flottant(const char *message);
void lire_chaine(const char *message, char *buffer, int taille);
int fichier_existe(const char *nom_fichier);
void creer_fichier_avec_entete(const char *nom_fichier);

#endif
