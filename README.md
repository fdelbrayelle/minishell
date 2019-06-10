# minishell - Interpréteur en lignes de commande

Ce programme a été réalisé en novembre 2006 dans le cadre d'un projet individuel de DUT informatique.

Le programme est constitué d'un fichier en C, le langage avec lequel sont développés les systèmes UNIX. L'outil propose de lancer un petit interpréteur de commandes au sein même d'un terminal : il s'agit donc d'un mini shell qui propose d'évaluer les commandes entrées par l'utilisateur. Cela m'a permis de mieux comprendre certains fondements de la programmation système tels que l'allocation dynamique, les processus ou encore les tubes.

Vous pouvez récupérer librement le code source de l'interpréteur de commandes.

Il est peut-être nécessaire d'installer le package suivant si vous êtes sur Debian ou Ubuntu : `sudo apt install build-essential`.
Pour compiler tapez `gcc -o minishell minishell.c` dans le dossier où se trouve la source puis lancer `./minishell` pour exécuter le minishell (après avoir donné les droits en exécution sur le fichier). Pour quitter le mini shell tapez `exit` ou faites Ctrl + C.
