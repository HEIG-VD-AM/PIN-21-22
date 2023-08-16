# Commande des robots

Une fois la gestion des désintégrations, déplacements, collisions, décontaminations, ... effectuée, vous 
pourrez enfin écrire le code qui dirige vos robots pour leur faire décontaminer le plus de surface de particules
possible. 

La commande des robots se fait sous contraintes, qui vous seront fournies sous la forme d'un fichier .json tel que 

~~~json
{
    "CommandTimeInterval": 1.0,
    "maxBackwardSpeed": 5.0,
    "maxForwardSpeed": 20.0
}
~~~

D'une part, les robots ne peuvent dépasser `maxForwardSpeed` en marche avant, ni `maxBackwardSpeed` en marche arrière, et
ce tant à droite qu'à gauche.

D'autre part, vous ne pouvez modifier volontairement la vitesse des robots qu'en des temps de simulation multiples 
de `CommandTimeInterval`. Par exemple, avec le `CommandTimeInterval` d'une seconde ci-dessus, vous avez le droit de modifier
la vitesse de tous les robots aux temps 0.0s, 1.0s, 2.0s, ...  mais pas au temps 1.3s. Par contre, il est évidemment 
possible que des vitesses de robots soient modifiées à d'autres temps lors de collisions. 

Une modification volontaire de la vitesse d'un ou plusieurs robots doit évidemment être stockée dans un état de la TimeLine. 

Un exemple réalisé avec une première version du code des professeurs est disponible ci-dessous et dans le fichier 
[decontamination.tlin](./decontamination.tlin). Il est évident que la coordination des mouvements des robots n'est 
pas suffisante dans cet exemple. 

[![](https://yt-embed.herokuapp.com/embed?v=nVcqsTWvftE)](https://youtu.be/nVcqsTWvftE) 


