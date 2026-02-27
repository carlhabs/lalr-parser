#pragma once

#include <vector>
#include <iostream>
#include "lexer.h"

using namespace std;

class Automate;

class Etat
{
public:
   virtual ~Etat() {}
   virtual bool transition(Automate &automate, Symbole *s) = 0;
};

class Automate
{
public:
   explicit Automate(Lexer &l);
   ~Automate();

   bool analyser();
   int resultat() const;

   void decalage(Symbole *s, Etat *e);
   void empiler(Symbole *s, Etat *e);
   void reduire(int regle);
   void accepter() { accepte = true; }

   void erreur(const char *msg)
   {
      cerr << "Erreur: " << msg << endl;
   }

private:
   Lexer &lex;
   bool accepte;

   vector<Etat *> pileEtats;
   vector<Symbole *> pileSymboles;

   void pop(int n, vector<Symbole *> &out);
   bool gotoExpr(Symbole *e);
   void deleteSymbols(vector<Symbole *> &v);

   Automate(const Automate &);
   Automate &operator=(const Automate &);
};