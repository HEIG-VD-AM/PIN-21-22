# TimeLine

Une ligne de temps est simplement une séquence d'[états](../State) successifs. 
Elle est représentée via la structure suivante :

~~~cpp
struct TimeLine {
   std::vector<State> states;
};
~~~

C'est cette stucture, stockée dans un fichier au format [JSON](../JSON), qui sert de support à la communication 
entre le programme de simulation/planification et le programme d'affichage, ainsi qu'entre votre groupe et 
les assistants/professeurs. 

Pour ce faire, il faut que l'on puisse interpoler entre deux états successifs en se contentant simplement de
[déplacer](../Robot) les robots à vitesse constante. Tout autre changement doit être stocké explicitement dans la TimeLine
sous la forme d'un état. Cela inclut 

* [désintégration](../Particule) d'une particule
* [collision](../Collisions) entre 2 robots
* [collision](../Collisions) entre robot et particule
* [décontamination](../Decontamination) d'une particule par un robot
* [changement de vitesse](../Command) d'1 ou plusieurs robots

Le fichier [decontamination.tlin](./decontamination.tlin) inclut la simulation complète de la décontamination
de 8 particules originales par 2 robots, comme illustré ci-dessous à vitesse double. On y observe les différents 
types d'événements ci-dessus. 

[![](https://yt-embed.herokuapp.com/embed?v=nVcqsTWvftE)](https://youtu.be/nVcqsTWvftE)