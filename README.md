# Gestionnaire de Personnes

Un programme simple en C pour gérer une base de données de personnes dans un fichier texte.

## Fonctionnalités

- Ajouter une personne
- Supprimer une personne par ID
- Chercher une personne par ID
- Modifier les informations d'une personne
- Afficher toutes les personnes

## Compilation et Exécution

```bash
# Compiler
gcc main.c -o gestionnaire

# Exécuter
./gestionnaire
```

## Utilisation

Le programme affiche un menu avec 6 options :
1. Ajouter une personne
2. Supprimer une personne
3. Chercher une personne
4. Modifier un enregistrement
5. Afficher toutes les personnes
6. Quitter

Tapez le numéro de votre choix et suivez les instructions.

## Structure des données

Chaque personne contient :
- ID (automatique)
- Nom
- Âge
- Adresse
- Points
- Taille

Les données sont sauvegardées dans `fichier_personne.txt`.

## Technologies

- Langage : C
- Stockage : Fichier texte
- Interface : Console
