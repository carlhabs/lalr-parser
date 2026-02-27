#pragma once

#include <vector>
#include <iostream>
#include "lexer.h"

class Automate;

class Etat {
public:
   virtual ~Etat() {}
   virtual bool transition(Automate& automate, Symbole* s) = 0;
};

class Automate {
public:
   explicit Automate(Lexer& l);
   ~Automate();

   bool analyser();
   int resultat() const;

   void decalage(Symbole* s, Etat* e);  // SHIFT
   void empiler(Symbole* s, Etat* e);   // GOTO (sur EXPR)
   void reduire(int regle);
   void accepter() { accepte = true; }

   void erreur(const char* msg) {
      std::cerr << "Erreur: " << msg << std::endl;
   }

private:
   Lexer& lex;
   bool accepte;

   std::vector<Etat*> pileEtats;
   std::vector<Symbole*> pileSymboles;

   void pop(int n, std::vector<Symbole*>& out);
   bool gotoExpr(Symbole* e);
   void deleteSymbols(std::vector<Symbole*>& v);

   Automate(const Automate&);
   Automate& operator=(const Automate&);
};