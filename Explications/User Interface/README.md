# User Interface 

Le programme graphique d'affichage doit pouvoir 

* charger une [TimeLine](../TimeLine)
* afficher l'[état](../State) à un temps donné obtenu en trouvant l'état pertinent dans la TimeLine, puis en faisant avancer les robots du temps manquant.
* Jouer l'animation de cette TimeLine en temps réel ou accéléré
* Afficher le total des scores des robots. 

Le programme doit afficher tout l'[état](../State) de worldOrigin à worldEnd, à la taille la plus grande possible mais sans en changer l'aspect ratio, comme illustré à la vidéo [https://youtu.be/VQNM30xSMLg](https://youtu.be/VQNM30xSMLg). 

A part cela, toute le reste de la logique du programme doit être localisée dans un programme en ligne de commande 
qui lit un état et fabrique la TimeLine correspondante. 

Pour la partie graphique, nous vous demandons d'utiliser [Qt](https://www.qt.io) et vous conseillons de vous inspirer de l'example 
[2D Painting Example](https://doc.qt.io/qt-6/qtopengl-2dpainting-example.html) également disponible depuis Qt Creator. 

[![](https://doc.qt.io/qt-6/images/2dpainting-example.png)](https://doc.qt.io/qt-6/qtopengl-2dpainting-example.html)
