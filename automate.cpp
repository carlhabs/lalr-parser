#include "automate.h"
#include "symbole.h"

using namespace std;

// -------------------------------------------------------------- Automate

Automate::Automate(Lexer &l) : lex(l), accepte(false) {}

Automate::~Automate()
{
   for (size_t i = 0; i < pileSymboles.size(); i++)
      delete pileSymboles[i];
   for (size_t i = 0; i < pileEtats.size(); i++)
      delete pileEtats[i];
}

bool Automate::analyser()
{
   pileEtats.push_back(new Etat0());

   while (!accepte)
   {
      Symbole *s = lex.Consulter();
      if (!s)
      {
         erreur("symbole null");
         return false;
      }
      if (*(s) == ERREUR)
      {
         erreur("lexer erreur");
         return false;
      }

      Etat *e = pileEtats.back();
      if (!e->transition(*this, s))
         return false;
   }
   return true;
}

int Automate::resultat() const
{
   if (pileSymboles.empty())
      return 0;
   Expr *e = dynamic_cast<Expr *>(pileSymboles.back());
   return e ? e->GetValeur() : 0;
}

void Automate::decalage(Symbole *s, Etat *e)
{
   pileSymboles.push_back(s);
   pileEtats.push_back(e);
   lex.Avancer();
}

void Automate::empiler(Symbole *s, Etat *e)
{
   pileSymboles.push_back(s);
   pileEtats.push_back(e);
}

void Automate::pop(int n, vector<Symbole *> &out)
{
   out.clear();
   for (int i = 0; i < n; i++)
   {
      Etat *et = pileEtats.back();
      pileEtats.pop_back();
      delete et;

      Symbole *sy = pileSymboles.back();
      pileSymboles.pop_back();
      out.push_back(sy);
   }
}

void Automate::deleteSymbols(vector<Symbole *> &v)
{
   for (size_t i = 0; i < v.size(); i++)
      delete v[i];
   v.clear();
}

bool Automate::gotoExpr(Symbole *e)
{
   Etat *top = pileEtats.back();
   return top->transition(*this, e);
}

// -------------------------------------------------------------- Réductions
void Automate::reduire(int regle)
{
   vector<Symbole *> popped;
   Expr *newE = nullptr;

   if (regle == 5) // E -> INT
   {
      pop(1, popped);
      Entier *v = dynamic_cast<Entier *>(popped[0]);
      if (!v)
      {
         erreur("r5");
         deleteSymbols(popped);
         return;
      }
      newE = new Expr(v->GetValeur());
   }
   else if (regle == 4) // E -> ( E )
   {
      pop(3, popped); // ) E (
      Expr *e = dynamic_cast<Expr *>(popped[1]);
      if (!e)
      {
         erreur("r4");
         deleteSymbols(popped);
         return;
      }
      newE = new Expr(e->GetValeur());
   }
   else if (regle == 3) // E -> E * E
   {
      pop(3, popped); // E2 * E1
      Expr *e2 = dynamic_cast<Expr *>(popped[0]);
      Expr *e1 = dynamic_cast<Expr *>(popped[2]);
      if (!e1 || !e2)
      {
         erreur("r3");
         deleteSymbols(popped);
         return;
      }
      newE = new Expr(e1->GetValeur() * e2->GetValeur());
   }
   else if (regle == 2) // E -> E + E
   {
      pop(3, popped); // E2 + E1
      Expr *e2 = dynamic_cast<Expr *>(popped[0]);
      Expr *e1 = dynamic_cast<Expr *>(popped[2]);
      if (!e1 || !e2)
      {
         erreur("r2");
         deleteSymbols(popped);
         return;
      }
      newE = new Expr(e1->GetValeur() + e2->GetValeur());
   }
   else
   {
      erreur("regle inconnue");
      return;
   }

   deleteSymbols(popped);

   if (!gotoExpr(newE))
   {
      delete newE;
   }
}

// -------------------------------------------------------------- Table LALR

bool Etat0::transition(Automate &a, Symbole *s)
{
   if (*s == INT)
   {
      a.decalage(s, new Etat3());
      return true;
   }
   if (*s == OPENPAR)
   {
      a.decalage(s, new Etat2());
      return true;
   }
   if (*s == EXPR)
   {
      a.empiler(s, new Etat1());
      return true;
   }
   a.erreur("etat0");
   return false;
}

bool Etat1::transition(Automate &a, Symbole *s)
{
   if (*s == PLUS)
   {
      a.decalage(s, new Etat4());
      return true;
   }
   if (*s == MULT)
   {
      a.decalage(s, new Etat5());
      return true;
   }
   if (*s == FIN)
   {
      delete s;
      a.accepter();
      return true;
   }
   a.erreur("etat1");
   return false;
}

bool Etat2::transition(Automate &a, Symbole *s)
{
   if (*s == INT)
   {
      a.decalage(s, new Etat3());
      return true;
   }
   if (*s == OPENPAR)
   {
      a.decalage(s, new Etat2());
      return true;
   }
   if (*s == EXPR)
   {
      a.empiler(s, new Etat6());
      return true;
   }
   a.erreur("etat2");
   return false;
}

bool Etat3::transition(Automate &a, Symbole *s)
{
   if (*s == PLUS || *s == MULT || *s == CLOSEPAR || *s == FIN)
   {
      a.reduire(5);
      return true;
   }
   a.erreur("etat3");
   return false;
}

bool Etat4::transition(Automate &a, Symbole *s)
{
   if (*s == INT)
   {
      a.decalage(s, new Etat3());
      return true;
   }
   if (*s == OPENPAR)
   {
      a.decalage(s, new Etat2());
      return true;
   }
   if (*s == EXPR)
   {
      a.empiler(s, new Etat7());
      return true;
   }
   a.erreur("etat4");
   return false;
}

bool Etat5::transition(Automate &a, Symbole *s)
{
   if (*s == INT)
   {
      a.decalage(s, new Etat3());
      return true;
   }
   if (*s == OPENPAR)
   {
      a.decalage(s, new Etat2());
      return true;
   }
   if (*s == EXPR)
   {
      a.empiler(s, new Etat8());
      return true;
   }
   a.erreur("etat5");
   return false;
}

bool Etat6::transition(Automate &a, Symbole *s)
{
   if (*s == PLUS)
   {
      a.decalage(s, new Etat4());
      return true;
   }
   if (*s == MULT)
   {
      a.decalage(s, new Etat5());
      return true;
   }
   if (*s == CLOSEPAR)
   {
      a.decalage(s, new Etat9());
      return true;
   }
   a.erreur("etat6");
   return false;
}

bool Etat7::transition(Automate &a, Symbole *s)
{
   if (*s == MULT)
   {
      a.decalage(s, new Etat5());
      return true;
   }
   if (*s == PLUS || *s == CLOSEPAR || *s == FIN)
   {
      a.reduire(2);
      return true;
   }
   a.erreur("etat7");
   return false;
}

bool Etat8::transition(Automate &a, Symbole *s)
{
   if (*s == PLUS || *s == MULT || *s == CLOSEPAR || *s == FIN)
   {
      a.reduire(3);
      return true;
   }
   a.erreur("etat8");
   return false;
}

bool Etat9::transition(Automate &a, Symbole *s)
{
   if (*s == PLUS || *s == MULT || *s == CLOSEPAR || *s == FIN)
   {
      a.reduire(4);
      return true;
   }
   a.erreur("etat9");
   return false;
}