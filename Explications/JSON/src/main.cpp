#include "json.hpp"
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <list>

using namespace std;

struct Foo {
   int entier;
   double reel;
   string chaine;
   vector<int> vecteur;
   list<double> liste;
   float autreChose; // pas stocké dans le json

   NLOHMANN_DEFINE_TYPE_INTRUSIVE(Foo, entier, reel, chaine, vecteur, liste)
};

struct Bar {
   int entier;
   Foo foo1;
   Foo foo2;

   NLOHMANN_DEFINE_TYPE_INTRUSIVE(Bar, entier, foo1, foo2)
};

int main() {

   Foo foo1 { 1, 2., "hello", { 1, 2, 3 }, { 3.14, 6.28 }, 42.f };

   nlohmann::json json_foo1 = foo1;
   cout << "JSON compact : " << json_foo1 << endl;
   cout << "JSON lisible : " << setw(4) << json_foo1 << endl;

   string json_foo2_as_string = R"({"chaine":"world","entier":5,"vecteur":[4,5,6],"liste":[1.61,4.2,16.1,42.0],"reel":3.14})";
   nlohmann::json json_foo2;
   stringstream(json_foo2_as_string) >> json_foo2;
   Foo foo2 = json_foo2.get<Foo>();

   Bar bar { 7, foo1, foo2 };

   nlohmann::json json_bar = bar;
   cout << "JSON compact : " << json_bar << endl;
   cout << "JSON lisible : " << setw(4) << json_bar << endl;
};