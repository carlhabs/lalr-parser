#include <iostream>
#include "lexer.h"
#include "automate.h"

int main()
{
   std::string chaine;
   std::cout << "Expression: ";
   std::getline(std::cin, chaine);

   Lexer l(chaine);
   Automate a(l);

   if (!a.analyser())
   {
      std::cout << "Analyse: ECHEC\n";
      return 1;
   }

   std::cout << "Analyse: OK\n";
   std::cout << "Valeur = " << a.resultat() << "\n";
   return 0;
}