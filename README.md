# libp9

## Description

La libp9 est une bibliothèque permettant de lexer, parser et interpréter le langage p9.

Ce langage est en cours de conception par moi-même ([arcanis](http://www.arcastel.com)) à partir d'une grammaire globalement inspirée de celle de l'ecmascript.

Un aperçu non exaustif des fonctionnalités souhaitées à terme sur le langage peut être vu dans les diverses pages du [wiki](https://github.com/arcanin/libp9/wiki/_pages) de ce repository : n'hésitez pas à poster des issues pour les commenter, critiquer, et en proposer de nouvelles.

## A noter

Je travaille ce projet sur mon temps libre, et je n'ai aucune connaissance particulière en théorie des langages.

En conséquence, il est plus que possible que :

* ce projet n'aboutisse jamais
* la vitesse d'exécution soit ignoble
* certaines fonctions soient drop
* le langage ne soit pas viable

Mais l'un dans l'autre, je vais faire tout ce qui est en mon pouvoir pour que le résultat final soit satisfaisant.
S'il peut finalement arriver à paver la voie d'un nouveau langage web, plus cohérent et adapté que Javascript, j'aurais alors amplement réussi !

## Outils utilisés

La libp9 est conçue avec les outils suivants :

- [ragel](http://www.complang.org/ragel/) (lexer)
- [lemon](http://www.hwaci.com/sw/lemon/) (parser)

Notez que lemon est distribué et compilée directement avec la libp9, vous n'avez pas à la récupérer.

## Licence

**Nombre de pizzas / bières reçues :** 0

La libp9 est développée par [Maël Nison](mailto:nison.mael@gmail.com), et est distribuée sous la licence BIERE/PIZZA-Restrict. Tant que vous conservez cette mention, vous pouvez librement partager cette bibliothèque. En cas de modification, la bibliothèque doit être renommée pour refléter les changements.

Si nous nous rencontrons un jour, ou si vous aimez faire des surprises*, vous pouvez toujours m'apporter une bière ou une pizza en récompense.
Quoi qu'il en soit, merci d'avoir lu !

*Envoyez tout de même un mail pour prévenir de la surprise, que je ne dise pas non au livreur ! ;)*
