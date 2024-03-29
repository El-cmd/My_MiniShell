# Documentation du Projet Minishell
L’objectif de ce projet est de créer un shell minimaliste.
Ça sera votre petit bash à vous.
Vous en apprendrez beaucoup sur les processus et les descripteurs de fichier.

## Introduction:
- ⚙️ Instalation
- 💻 Fonctionnalités
- 📜 Sources

## ⚙️ Instalation:
- cloner le repo: `git clone git@github.com:El-cmd/My_MiniShell.git`
- Asurez-vous d'avoir la bibliotheque `readline` d'inclus sur votre apapreil ou intallez la. ⚠️ Si vous etes sur IOS abandonner cette idee. Elle n'est ni inclus ni installable sur cet OS.
- Compiler le: `make`
- Et enfin lancez le: `./minishell`

## 💻 Fonctionnalités:
<a href="https://zupimages.net/viewer.php?id=23/37/f6hq.png"><img src="https://zupimages.net/up/23/37/f6hq.png" alt="" /></a>
1. Gere les signaux: `Ctrl-C`, `Ctrl-D` et `Ctrl-\`:
- `Ctrl-C` = affiche un nouveau prompt sur une nouvelle ligne.
- `Ctrl-D` = quitte le shell.
- `Ctrl-\` = ne fait rien.

2. Gere les builtins: `echo`, `pwd`, `cd`, `env`, `export`, `unset`, `exit`:
- `echo` = avec l’option -n et sans.
- `pwd` = Affiche le repertoire courant.
- `cd` = change de repertoire.
- `env` = Affiche les variables d'environnements.
- `export` = Ajoute une nouvelle variable d'environnement, sans arguments: affiche toute les variables dans l'ordre alpha-numerique.
- `unset` = Supprime une variable d'environnement.
- `exit` = Quitte le programme avec un retour 0 par defaut, ou un retour de l'argument donné, exemple `exit 5` retourne 5.

3. Gere les pipes `|`.
-  Les pipes, sont des opérateurs essentiels dans le shell Unix/Linux. Ils permettent de chaîner plusieurs commandes ensemble, permettant ainsi de traiter les données de manière fluide et efficace.
-  Exemple: `cat donnees.txt | grep "important" | wc -l`

4. Gere les redirections `>`, `<`, `>>` et `<<`.
-  Les redirections sont des techniques permettant de manipuler le flux d'entrée et de sortie des commandes dans un shell Unix/Linux.
-  Exemple: `commande > fichier_de_sortie.txt`

 ## 📜 Sources

-  Toute la playlist de Code Vault sur les proccesus, et les pipe: [Lien Youtube](https://www.youtube.com/watch?v=5fnVr-zH-SE)
-  Le manuel du veritable Bash: [Lien De la doc](https://www.gnu.org/software/bash/manual/bash.html)
-  Et un grand merci a [Vietdu91](https://github.com/vietdu91) pour ca fiche de debug: [lien de la fiche](https://docs.google.com/spreadsheets/d/1uJHQu0VPsjjBkR4hxOeCMEt3AOM1Hp_SmUzPFhAH-nA/edit#gid=0)   
