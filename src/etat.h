#pragma once

class Automate;
class Symbole;

class Etat
{
public:
  virtual bool transition(Automate &a, Symbole *s) = 0;
  virtual ~Etat() {}
};