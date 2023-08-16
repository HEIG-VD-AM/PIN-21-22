# Décontamination 

Pour qu'un [robot](../Robot) puisse décontaminer une [particule](../Particule), i.e. la faire disparaitre, il faut que 

* robot et particule se touchent, i.e. que la distance entre les 2 centres soit comprise entre la somme des 2 rayons et cette somme plus
`std::numeric_limits<float>::epsilon()`. 
* l'angle de capture soit plus grand ou égal à l'angle entre 
  * la droite reliant les centres des robots et particule 
  * la droite reliant le centre du robot et l'avant de celui-ci

L'angle de capture est une caractéristique qui peut varier d'un robot à l'autre et est stockée dans l'attribut `RobotInfo::captureAngle`. Un angle de 
capture de 180 degrés permettrait à un robot de toujours pouvoir décontaminer quelque soit l'angle de collision. 

L'orientation de la droite reliant le centre du robot et l'avant de celui-ci est une caractéristique qui dépend 
du déplacement du robot. A tout moment, elle est stockée dans l'attribut `RobotInfo::angle`.

L'orientation de la droite reliant les centres des robot et particule doit être calculée à partir des `RobotInfo::position` et `ParticleInfo::position`

Lorsque qu'une décontamination a lieu, 2 choses se passent :
* la particule disparait. 
* le robot augmente son `RobotInfo::score` d'un nombre égal à la surface de la particule décontaminée. 

Le but du jeu est d'obtenir le plus grand total possible pour la somme des scores de tous les robots. 

Il y a 2 scénarii possible pour qu'une décontamination aie lieu.
* un robot entre en collision avec une particule et est dans la bonne orientation lors de cette collision. Il la décontamine et poursuit sur sa trajectoire
* un robot entré précédemment en collision avec une particule sans la décontaminer tourne sur lui-même jusqu'à ce que son orientation permette une décontamination

Ces 2 possibilités sont illustrées dans la vidéo ci-dessous, produite à partir de la TimeLine [decontaminationDemo.tlin](./decontaminationDemo.tlin), 
elle même générée à partir de l'état [decontaminationDemo.stat](decontaminationDemo.stat).

[![](https://yt-embed.herokuapp.com/embed?v=MegSWge7F-c)](https://youtu.be/MegSWge7F-c)
