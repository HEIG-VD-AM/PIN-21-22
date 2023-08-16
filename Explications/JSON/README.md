# JSON

Les données qui vous sont fournies et celles que vous devez produire sont stockées sur disque 
au format [JSON](https://fr.wikipedia.org/wiki/JavaScript_Object_Notation) qui nous vient de 
javascript.

Pour nous simplifier la vie, nous utiliserons la librairie "JSON for Modern C++" de Niels
Lohmann disponible via [GitHub](https://github.com/nlohmann/json) et [https://json.nlohmann.me](https://json.nlohmann.me). 

Cette librairie est disponible sous la forme d'un seul fichier header disponible à l'adresse 
[https://github.com/nlohmann/json/tree/develop/single_include/nlohmann](https://github.com/nlohmann/json/tree/develop/single_include/nlohmann). 

Vous pouvez en lire la documentation, mais l'essentiel de ce dont vous aurez besoin est illustré dans 
l'exemple fourni dans le sous-répertoire [src](./src). 

Essentiellement, il utilise 

* la macro [NLOHMANN_DEFINE_TYPE_INTRUSIVE](https://json.nlohmann.me/api/macros/nlohmann_define_type_intrusive/)
* le type [nlohmann::json](https://json.nlohmann.me/api/json/)
  * son [constructeur](https://json.nlohmann.me/api/basic_json/basic_json/) de conversion depuis un type compatible
  * sa méthode générique [get&lt;T&gt;()](https://json.nlohmann.me/api/basic_json/get/) de conversion vers un type compatible
  * ses opérateurs de [sérialisation](https://json.nlohmann.me/api/basic_json/operator_ltlt/) et de [désérialisation](https://json.nlohmann.me/api/basic_json/operator_gtgt/)

