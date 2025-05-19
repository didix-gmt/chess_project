# Projet Échecs en C++

**Nom** : GAMIETTE Didier 

---

## Présentation du projet

Ce projet implémente un moteur de jeu d’échecs en C++ fonctionnant dans un terminal. Il permet à deux joueurs de s’affronter avec toutes les règles officielles du jeu d’échecs : déplacements classiques, roque (court et long), promotion, prise en passant, détection d’échec, échec et mat, ainsi que pat.

Le code est structuré en classes orientées objet : une classe de base `Piece` et des classes dérivées pour chaque type de pièce (`Pawn`, `King`, `Queen`, etc.), une classe `Board` pour représenter l’échiquier et gérer les mouvements, et une classe `Game` pour gérer l’interaction avec l’utilisateur.

Parmi les difficultés rencontrées :

- La gestion correcte du roque avec vérification de tous les prérequis (absence de menace, déplacement antérieur, etc.).
- La détection correcte et complete de l’échec et mat
- L’implémentation de la prise en passant, spécifique aux pions.
- Fonctions `isValidMovement` et `wouldCauseCheck` incorrectes
- De nombreuses erreurs de segmentation dû à l'accès au plateau. (suppressions, ajouts de pièces, parcours de celles ci...)

---

## Compilation et exécution

### Compilation

Utilisez simplement la commande suivante à la racine du projet :

```bash
make
```

Lancez le jeu avec :

```bash
./echecs
```

Générez la documentation avec :

```bash
make doc
```

---

## Tests

Tout les tests réussissent.