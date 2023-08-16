# Particules

Les particules que nous allons décontaminer se désintègrent au cours du temps, comme illustré 
dans la vidéo suivante, générée à partir des données ci-dessous.

[![](https://yt-embed.herokuapp.com/embed?v=GtQ8q9i-ZgQ)](https://youtu.be/GtQ8q9i-ZgQ)

Les particules sont définies par les structures suivantes 

~~~cpp
struct Position {
   double x; // horizontal coordinate 
   double y; // vertical coordinate
};

struct ParticleInfo {
   int id;             // unique identifier
   Position position;  // (x,y) coordinates of the particle 
   double radius;      // radius of the circular particle
   std::vector<std::vector<double>> explosionTimes;
};
~~~

Le fichier [particleDemo.part](./particleDemo.part) contient version JSON d'une telle particule d'indentifiant 0,
centrée en (300,200) et de rayon 150. Elle se désintègre après 8.625 secondes en 4 sous-particules, qui se désintègrent
elles-même aux temps 17.625s, 11.875s, 11.25s, et 14.625s respectivement, qui elles-même se désintégreront encore 2 fois
en 16 puis 64 particules avant de disparaitre. 

Lors d'une désintégration, une particule est remplacée par 4 particles circulaires inscrites dans le 
disque de la particule originale dont les centres sont orientés à 45, 135, -45 et -135 degrés par
rapport au centre original. Leurs rayons sont donc de `1/(1+sqrt(2))*R` avec `R` le rayon original.

Le vecteur `explosionTimes` contient la liste des temps de désintégration classés par génération. `explosionTimes.at(0)` 
contient une seule valeur : le temps auquel se produira la prochaine désintégration. `explosionTimes.at(1)`
contient les 4 valeurs des temps auquels se produiront les désintégrations des 4 particules résultant de cette
désintégration. A chaque génération il y a 4 fois plus de particules qu'à la génération précédente. 
La désintégration des particules de dernière génération entraine leur disparition complète plutôt que
leur division en 4. 

Le fichier [particleDemo.stat](./particleDemo.stat) contient une [état](../State) du monde dans un espace de
taille (600x400), au temps 0, contenant cette particule et aucun robot. 

Le fichier [particleDemo.tlin](./particleDemo.tlin) contient la [timeLine](../TimeLine) des états successifs du monde lorsque 
cette particule et ses enfants se désintègrent. 
