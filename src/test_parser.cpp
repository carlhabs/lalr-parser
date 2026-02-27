// FICHIER GENERE AVEC IA

#include "lexer.h"
#include "automate.h"
#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct TestCase
{
  string input;
  bool shouldPass;
  int expectedResult;
};

int main()
{
  vector<TestCase> tests = {
      {"1+2", true, 3},
      {"4*5", true, 20},
      {"1+2*3", true, 7},
      {"(1+2)*3", true, 9},
      {"7", true, 7},
      {"((2+3)*4)+5", true, 25},
      {"8*(2+2*2)", true, 48},
      {"((1))", true, 1},
      {"1+2+3+4", true, 10},
      {"2*3*4", true, 24},
      {"1++2", false, 0},
      {"*3+2", false, 0},
      {"1+", false, 0},
      {"(1+2", false, 0},
      {"1+2)", false, 0},
      {"a+1", false, 0},
      {"()", false, 0},
      {"1 2", false, 0},
      {"1+*2", false, 0},
      {"((3+4)*2", false, 0}};
  int ok = 0;
  for (size_t i = 0; i < tests.size(); ++i)
  {
    Lexer lexer(tests[i].input);
    Automate automate(lexer);
    bool res = automate.analyser();
    if (res && tests[i].shouldPass)
    {
      int val = automate.resultat();
      if (val == tests[i].expectedResult)
      {
        cout << "Test " << i + 1 << " OK: " << tests[i].input << " = " << val << endl;
        ++ok;
      }
      else
      {
        cout << "Test " << i + 1 << " FAIL (bad result): " << tests[i].input << " attendu " << tests[i].expectedResult << ", obtenu " << val << endl;
      }
    }
    else if (!res && !tests[i].shouldPass)
    {
      cout << "Test " << i + 1 << " OK (erreur attendue): " << tests[i].input << endl;
      ++ok;
    }
    else if (!res && tests[i].shouldPass)
    {
      cout << "Test " << i + 1 << " FAIL (erreur inattendue): " << tests[i].input << endl;
    }
    else
    {
      cout << "Test " << i + 1 << " FAIL (devait échouer): " << tests[i].input << endl;
    }
    cout << endl;
  }
  cout << ok << "/" << tests.size() << " tests réussis." << endl;
  return 0;
}
