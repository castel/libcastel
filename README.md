# libp9

## Description

La libp9 est une bibliothèque permettant de lexer, parser et interpréter le langage p9.

Ce langage est en cours de conception par moi-même ([arcanis](http://www.arcastel.com)), et ne possède de ce fait aucune documentation ni aucune norme.
Il se base sur la syntaxe de base du javascript, mais a pour but d'offrir un certain nombre de fonctionnalités avancées, telles que la visibilité de méthodes au sein de classes, ou la possibilité d'utiliser un système de module unique entre toute les implémentations (chose qui manque hélas au javascript moderne, en dépit des nouvelles normes).

## A noter

Je travaille ce projet sur mon temps libre, et je n'ai aucune connaissance particulière en théorie des langages.

En conséquence, il est fort possible que les caractéristiques souhaitées pour ce projet n'apparaissent jamais, ou qu'elles ne soient pas particulièrement performantes. En revanche, je serais plus qu'heureux d'obtenir des pair reviews de la part de personnes maitrisant ces techniques !

## Outils utilisés

La libp9 est conçue avec les outils suivants :

- ragel
- lemon
