# JEU DE LA VIE (GAME-OF-LIFE):

**Le Jeu de la Vie (ou Game of Life)** est en realitée un automate cellulaire défini en 1970 par le mathematicien anglais John Conway afin de tenter de résoudre un problème soulevé par un mathematicien, père de l’informatique, John Von Neumann.
Ce projet rentre dans le cadre de l'UE Techniques de Développement. 

# Guide d'utilisation du programme :

![Screenshot](/game_html_doc/jeu.png)

## ==> Compilation du programme avec l'interface graphique


La compilation du programme ce fait par un make, le programme est compilé par défaut en mode graphique ( en utilisant le logiciel graphique CAIRO). 

~~~{.sh}
make
~~~

## ==> Compilation du programme en mode texte 

Supposons que vous ne disposez pas du logiciel Cairo et que vous souhaitez compiler le programme sur le terminal pour le tester. Cela est possible cela est possible en en nettoyant les artefacts de compilation d'abord et en tapant ensuite cette commande make **MODE=TEXTE**.

~~~{.sh}
make clean
~~~

**Ensuite :** 

~~~{.sh}
make MODE=TEXTE
~~~


## ==> Exécution du programme

**Exemple :** éxecuter le programme avec la 4ème grille

~~~{.sh}
./bin/main 4
~~~

## ==> Autheur 


**_KABBADJ Youness_**



