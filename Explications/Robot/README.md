# Robots

Les robots se déplacent en ligne droite ou en cercle. On les contrôle via les vitesses de leurs 
côtés droits et gauche respectivement. Dans la vidéo ci-dessous, le robot démarre en 
position (150,150) orienté à 30 degrés. Il voyage pendant 3 secondes en ligne droite avec 
`vg=vd=20`, puis se mets à tourner. Les 3 secondes suivantes avec `vg=20, vd=10`, puis 
3 secondes avec `vg=20, vd=0`, 3 secondes en tournant dans l'autre sens avec `vg=0, vd=20` et enfin 3 secondes de rotation
en place avec `vg=-20, vd=20`. 

[![](https://yt-embed.herokuapp.com/embed?v=LfpYF8NqJb8)](https://youtu.be/LfpYF8NqJb8)

Les robots sont définis via les structures suivantes

~~~cpp
struct Position {
   double x; // horizontal coordinate 
   double y; // vertical coordinate
};

struct RobotInfo {
   int id;              // unique identifier
   Position position;   // (x,y) coordinates of the robot in the world (in pixels)
   double radius;       // radius of the circular robot. (pixels)
   double angle;        // direction in which the robot moves. [0,360[ in degrees. 0 = 3 o'clock, 90 = noon
   double captureAngle; // c.f. décontamination
   double leftSpeed;    // linear speed of the leftmost part of the robot in pixels/sec
   double rightSpeed;   // linear speed of the rightmost part of the robot in pixels/sec
   double score;        // c.f. décontamination
};
~~~

Les fichiers [robotDemo.rbot](./robotDemo.rbot), [robotDemo.stat](./robotDemo.stat),
et [robotDemo.tlin](./robotDemo.tlin) contiennent le robot, l'[état](../State) et la [timeLine](../TimeLine) 
complète de cette démo. 
