# lalr-parser

Parser LALR pour expressions arithmétiques (addition, multiplication, parenthèses seulement).

## Prérequis

- GNU Make
- g++ (supportant C++11)

## Compilation

Depuis la racine du projet :

```bash
make
```

Le makefile produit l'exécutable `tp`.

Si vous souhaitez compiler avec d'autres options :

```bash
make CXXFLAGS="-std=c++11 -Wall -Wextra -O0"
```

## Exécution

L'exécutable lit une expression sur une ligne depuis l'entrée standard.

Exemples :

Exécution interactive :

```bash
./tp
# puis saisir, par exemple :
# Expression: 1+2*3 ou 1 +2*3 (les espaces sont ignorés)
```

Via canalisation (pipe) :

```bash
echo "1+2*3" | ./tp
```

Le programme affiche si l'analyse a réussi et la valeur de l'expression.

## Nettoyage

```bash
make clean
```

## Remarques

- Le parser attend une expression sur une seule ligne.
- Nous avons généré les tests ainsi que les fichiers README et Makefile avec IA, et clean la majeure partie de notre code avec l'outil copilot de vscode ainsi que l'extension prettier.
