#include "fichier.h"

/**
 * Fonction utilitaire pour lire un entier de manière sécurisée
 */
int lire_entier(const char *message) {
    int valeur;
    printf("%s", message);
    while (scanf("%d", &valeur) != 1) {
        printf("Erreur : veuillez entrer un nombre entier valide.\n");
        printf("%s", message);
        // Vider le buffer d'entrée
        while (getchar() != '\n');
    }
    // Vider le buffer d'entrée
    while (getchar() != '\n');
    return valeur;
}

/**
 * Fonction utilitaire pour lire un flottant de manière sécurisée
 */
float lire_flottant(const char *message) {
    float valeur;
    printf("%s", message);
    while (scanf("%f", &valeur) != 1) {
        printf("Erreur : veuillez entrer un nombre décimal valide.\n");
        printf("%s", message);
        // Vider le buffer d'entrée
        while (getchar() != '\n');
    }
    // Vider le buffer d'entrée
    while (getchar() != '\n');
    return valeur;
}

/**
 * Fonction utilitaire pour lire une chaîne de caractères de manière sécurisée
 */
void lire_chaine(const char *message, char *buffer, int taille) {
    printf("%s", message);
    if (fgets(buffer, taille, stdin) != NULL) {
        // Supprimer le '\n' à la fin si présent
        size_t len = strlen(buffer);
        if (len > 0 && buffer[len - 1] == '\n') {
            buffer[len - 1] = '\0';
        }
    }
}

/**
 * Vérifie si un fichier existe
 */
int fichier_existe(const char *nom_fichier) {
    FILE *fp = fopen(nom_fichier, "r");
    if (fp) {
        fclose(fp);
        return 1;
    }
    return 0;
}

/**
 * Crée un fichier avec l'en-tête s'il n'existe pas
 */
void creer_fichier_avec_entete(const char *nom_fichier) {
    if (!fichier_existe(nom_fichier)) {
        FILE *fp = fopen(nom_fichier, "w");
        if (fp == NULL) {
            printf("Erreur : impossible de créer le fichier %s\n", nom_fichier);
            exit(1);
        }
        fprintf(fp, "ID\tNOM\tAGE\tADRESSE\tPOINT\tTAILLE\n");
        fclose(fp);
        printf("Fichier %s créé avec succès.\n", nom_fichier);
    }
}

/**
 * Ajoute une nouvelle personne au fichier
 */
void ajouter_personne(const char *nom_fichier) {
    Personne p;
    int dernier_id = 0;
    char ligne[MAX_LIGNE];

    // Lire le dernier ID utilisé
    FILE *fp = fopen(nom_fichier, "r");
    if (fp == NULL) {
        printf("Erreur : impossible d'ouvrir le fichier %s\n", nom_fichier);
        return;
    }

    // Ignorer la première ligne (en-tête)
    fgets(ligne, sizeof(ligne), fp);

    while (fgets(ligne, sizeof(ligne), fp)) {
        int id_temp;
        if (sscanf(ligne, "%d", &id_temp) == 1) {
            dernier_id = id_temp;
        }
    }
    fclose(fp);

    // Saisie des informations de la personne
    printf("\n=== Ajout d'une nouvelle personne ===\n");
    lire_chaine("Nom : ", p.nom, MAX_NOM);
    lire_chaine("Adresse : ", p.adresse, MAX_ADRESSE);
    p.age = lire_entier("Âge : ");
    p.point = lire_flottant("Points : ");
    p.taille = lire_flottant("Taille (en mètres) : ");

    // Attribuer un nouvel ID
    p.id = dernier_id + 1;

    // Ajouter au fichier
    fp = fopen(nom_fichier, "a");
    if (fp == NULL) {
        printf("Erreur : impossible d'ouvrir le fichier %s en écriture\n", nom_fichier);
        return;
    }

    fprintf(fp, "%d\t%s\t%d\t%s\t%.2f\t%.2f\n",
            p.id, p.nom, p.age, p.adresse, p.point, p.taille);
    fclose(fp);

    printf("Personne ajoutée avec succès (ID: %d)\n", p.id);
}

/**
 * Supprime une personne du fichier
 */
void supprimer_personne(const char *nom_fichier) {
    int id, id_temp;
    char ligne[MAX_LIGNE];
    int trouve = 0;

    id = lire_entier("ID de la personne à supprimer : ");

    FILE *fp_source = fopen(nom_fichier, "r");
    FILE *fp_temp = fopen("temp_suppression.txt", "w");

    if (fp_source == NULL || fp_temp == NULL) {
        printf("Erreur : impossible d'ouvrir les fichiers\n");
        if (fp_source) fclose(fp_source);
        if (fp_temp) fclose(fp_temp);
        return;
    }

    while (fgets(ligne, sizeof(ligne), fp_source) != NULL) {
        if (sscanf(ligne, "%d", &id_temp) == 1 && id_temp == id) {
            trouve = 1;
            continue; // Ignorer cette ligne
        }
        fputs(ligne, fp_temp);
    }

    fclose(fp_source);
    fclose(fp_temp);

    if (trouve) {
        remove(nom_fichier);
        rename("temp_suppression.txt", nom_fichier);
        printf("Personne avec ID %d supprimée avec succès.\n", id);
    } else {
        remove("temp_suppression.txt");
        printf("Aucune personne trouvée avec l'ID %d.\n", id);
    }
}

/**
 * Cherche et affiche une personne par son ID
 */
void chercher_personne(const char *nom_fichier) {
    char ligne[MAX_LIGNE];
    int id, id_temp;
    int trouve = 0;

    FILE *fp = fopen(nom_fichier, "r");
    if (fp == NULL) {
        printf("Erreur : impossible d'ouvrir le fichier %s\n", nom_fichier);
        return;
    }

    id = lire_entier("ID de la personne à chercher : ");

    // Afficher l'en-tête
    fgets(ligne, sizeof(ligne), fp);
    printf("\n%s", ligne);
    printf("----------------------------------------\n");

    while (fgets(ligne, sizeof(ligne), fp) != NULL) {
        if (sscanf(ligne, "%d", &id_temp) == 1 && id_temp == id) {
            printf("%s", ligne);
            trouve = 1;
            break;
        }
    }

    fclose(fp);

    if (!trouve) {
        printf("Aucune personne trouvée avec l'ID %d.\n", id);
    }
}

/**
 * Modifie les informations d'une personne
 */
void modifier_enregistrement(const char *nom_fichier) {
    int id_temp, id;
    char ligne[MAX_LIGNE];
    Personne p;
    int trouve = 0;

    FILE *fp = fopen(nom_fichier, "r");
    FILE *temp = fopen("temp_modification.txt", "w");

    if (fp == NULL || temp == NULL) {
        printf("Erreur : impossible d'ouvrir les fichiers\n");
        if (fp) fclose(fp);
        if (temp) fclose(temp);
        return;
    }

    id = lire_entier("ID de la personne à modifier : ");

    while (fgets(ligne, sizeof(ligne), fp) != NULL) {
        if (sscanf(ligne, "%d", &id_temp) == 1 && id_temp == id) {
            printf("\n=== Modification des informations ===\n");
            lire_chaine("Nouveau nom : ", p.nom, MAX_NOM);
            lire_chaine("Nouvelle adresse : ", p.adresse, MAX_ADRESSE);
            p.age = lire_entier("Nouvel âge : ");
            p.point = lire_flottant("Nouveaux points : ");
            p.taille = lire_flottant("Nouvelle taille (en mètres) : ");

            p.id = id;
            fprintf(temp, "%d\t%s\t%d\t%s\t%.2f\t%.2f\n",
                    p.id, p.nom, p.age, p.adresse, p.point, p.taille);
            trouve = 1;
            continue;
        }
        fputs(ligne, temp);
    }

    fclose(fp);
    fclose(temp);

    if (trouve) {
        remove(nom_fichier);
        rename("temp_modification.txt", nom_fichier);
        printf("Informations modifiées avec succès.\n");
    } else {
        remove("temp_modification.txt");
        printf("Aucune personne trouvée avec l'ID %d.\n", id);
    }
}

/**
 * Affiche toutes les personnes du fichier
 */
void afficher_toutes_personnes(const char *nom_fichier) {
    char ligne[MAX_LIGNE];
    FILE *fp = fopen(nom_fichier, "r");

    if (fp == NULL) {
        printf("Erreur : impossible d'ouvrir le fichier %s\n", nom_fichier);
        return;
    }

    printf("\n=== Liste de toutes les personnes ===\n");
    while (fgets(ligne, sizeof(ligne), fp) != NULL) {
        printf("%s", ligne);
    }
    printf("=====================================\n");

    fclose(fp);
}

/**
 * Affiche le menu principal et gère les choix
 */
void menu(void) {
    int choix;
    const char *nom_fichier = "fichier_personne.txt";

    // Créer le fichier avec en-tête s'il n'existe pas
    creer_fichier_avec_entete(nom_fichier);

    do {
        printf("\n========== MENU PRINCIPAL ==========\n");
        printf("1. Ajouter une personne\n");
        printf("2. Supprimer une personne\n");
        printf("3. Chercher une personne\n");
        printf("4. Modifier un enregistrement\n");
        printf("5. Afficher toutes les personnes\n");
        printf("6. Quitter\n");
        printf("====================================\n");

        choix = lire_entier("Votre choix (1-6) : ");

        switch (choix) {
            case 1:
                ajouter_personne(nom_fichier);
                break;
            case 2:
                supprimer_personne(nom_fichier);
                break;
            case 3:
                chercher_personne(nom_fichier);
                break;
            case 4:
                modifier_enregistrement(nom_fichier);
                break;
            case 5:
                afficher_toutes_personnes(nom_fichier);
                break;
            case 6:
                printf("Au revoir !\n");
                break;
            default:
                printf("Choix invalide. Veuillez choisir entre 1 et 6.\n");
        }
    } while (choix != 6);
}
