#include <iostream>
#include "lexer.h"
#include "automate.h"

using namespace std;

int main()
{
   string chaine;
   cout << "Expression: ";
   getline(cin, chaine);

   Lexer l(chaine);
   Automate a(l);

   if (!a.analyser())
   {
      cout << "Analyse: ECHEC\n";
      return 1;
   }

   cout << "Analyse: OK\n";
   cout << "Valeur = " << a.resultat() << "\n";
   return 0;
}