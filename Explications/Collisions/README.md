# Collisions

Les divers objets présents dans notre monde ne peuvent à aucun moment se superposer. Il faut
donc qu'à tout moment la distance entre 2 objets circulaires soit supérieure ou égale à la 
somme des 2 rayons de ces objets. 

Les robots se déplaçant, ils peuvent entrer en collision avec d'autres robots ou particules. 
Dans ce cas, vous devez calculer l'instant exact de cette collision, i.e. un instant tel qu'à 
ce moment la distance entre les 2 centres soit comprise entre la somme des 2 rayons et cette somme plus
`std::numeric_limits<float>::epsilon()`. Ce calcul peut se faire analytiquement (bonne chance) ou numériquement (c'est beaucoup plus simple) 
par recherche dichotomique entre un instant avant collision et un instant après collision. 

Lors d'une collision entre 2 robots, la vitesse de ces 2 robots tombe instantanément à zéro, et 
y reste jusqu'à la prochaine opportunité de [modifier leurs vitesses volontairement](../Command). 

Lors d'une collision entre 1 robot et une particule, le robot s'arrête également si cette 
collision ne permet pas de [décontamination](../Decontamination). Par contre, il continue
sur sa trajectoire originale si la particule est décontaminée. 

Par exemple, à partir de l'état initial [collisionDemo.stat](./collisionDemo.stat), on 
calcule que la première collision a lieu au temps 4.25s et permet au robot 3 de 
décontaminer la particule 1. La deuxième collision a lieu au temps 4.58s et bloque 
le robot 2 qui ne peut décontaminer la particule 0 étant mal orienté. Enfin, au temps
6.33s, les robots 0 et 1 entrent en collision. La simulation s'arrête au temps 10 lorsque
la particule 0 se désintègre. La TimeLine [collisionDemo.tlin](./collisionDemo.tlin) 
correspond à la vidéo ci-dessous. 

[![](https://yt-embed.herokuapp.com/embed?v=4hbsNZMQ-TE)](https://youtu.be/4hbsNZMQ-TE)
