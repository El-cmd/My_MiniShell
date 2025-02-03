# 🚀 MiniShell - Un Shell Minimaliste

## 📖 À propos du projet
MiniShell est une implémentation simplifiée d'un shell Unix, inspirée de Bash. Ce projet a été développé dans le cadre du cursus de l'école 42, avec pour objectif de comprendre en profondeur le fonctionnement des processus Unix et la gestion des descripteurs de fichiers.

## 🔧 Prérequis
- Système Unix/Linux
- Bibliothèque `readline` installée
- Compilateur GCC
- Make

⚠️ Note : Ce projet n'est pas compatible avec macOS en raison des limitations de la bibliothèque `readline`.

## ⚙️ Installation

1. Clonez le dépôt :
```bash
git clone git@github.com:El-cmd/My_MiniShell.git
cd My_MiniShell
```

2. Compilez le projet :
```bash
make
```

3. Lancez MiniShell :
```bash
./minishell
```

## 💻 Fonctionnalités

<a href="https://zupimages.net/viewer.php?id=23/37/f6hq.png"><img src="https://zupimages.net/up/23/37/f6hq.png" alt="" /></a>

### 1. Gestion des Signaux
- `Ctrl-C` : Interrompt la commande en cours et affiche un nouveau prompt
- `Ctrl-D` : Quitte proprement le shell
- `Ctrl-\` : Ne produit aucun effet (comportement personnalisé)

### 2. Commandes Intégrées (Builtins)
| Commande | Description |
|----------|-------------|
| `echo [-n]` | Affiche du texte (option -n pour supprimer le retour à la ligne) |
| `pwd` | Affiche le chemin du répertoire courant |
| `cd [dossier]` | Change le répertoire de travail |
| `env` | Affiche les variables d'environnement |
| `export` | Définit ou modifie une variable d'environnement |
| `unset` | Supprime une variable d'environnement |
| `exit [code]` | Quitte le shell avec le code de retour spécifié (0 par défaut) |

### 3. Gestion des Pipes ( | )
Permet de chaîner plusieurs commandes en redirigeant la sortie d'une commande vers l'entrée de la suivante.

Exemple :
```bash
ls -l | grep ".txt" | wc -l
```

### 4. Redirections
| Opérateur | Description |
|-----------|-------------|
| `>` | Redirection de sortie (écrase) |
| `>>` | Redirection de sortie (ajoute) |
| `<` | Redirection d'entrée |
| `<<` | Here-document (heredoc) |

## � Ressources et Références

- [Tutoriels Code Vault sur les processus et pipes](https://www.youtube.com/watch?v=5fnVr-zH-SE)
- [Documentation officielle de Bash](https://www.gnu.org/software/bash/manual/bash.html)
- [Guide de débogage par Vietdu91](https://docs.google.com/spreadsheets/d/1uJHQu0VPsjjBkR4hxOeCMEt3AOM1Hp_SmUzPFhAH-nA/edit#gid=0)

## 🤝 Remerciements
Un grand merci à [Vietdu91](https://github.com/vietdu91) pour son précieux guide de débogage qui a grandement facilité le développement de ce projet.
