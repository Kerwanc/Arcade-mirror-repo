
Ce projet a été effectué avec des architectures communes aux étudiants suivants :
benoit.thomas@epitech.eu
swann.grandin@epitech.eu
pierre.pruvost@epitech.eu

Notre projet reproduit le fonctionnement d’une borne d’arcade. Pour la faire fonctionner, nous fournissons un Core, qui est l’équivalent de la borne en elle-même. Elle doit être accompagnée d’une ou plus bibliothèque graphique afin d’être capable d’afficher vos jeux et votre menu. Une fois fait, il vous faudra ajouter les jeux que vous souhaitez vous y jouer

`Tree`
```bash
.
├── assets/                 # Ressources de base pour le menu ou les libs
├── doc/                    # Diagrammes UML et documentations
├── include/                # Interfaces, outils, et types communs
│   ├── data/               # Événements, entités, updates
│   └── interfaces/         # ICore, IGame, IGraphic
├── lib/                    # Dossier pour les .so des jeux/libs graphiques
│   └── assets/             # Ressources spécifiques aux jeux (ex: minesweeper)
├── src/                    # Code source du projet
│   ├── core/               # Gestion du cœur, des loaders dynamiques
│   ├── error/              # Classe d'erreur
│   ├── games/              # Jeux (ex: Snake, Minesweeper, Menu)
│   └── graphic/            # Implémentations graphiques (Ncurses, SDL, SFML)
├── main.cpp                # Point d’entrée du projet
└── Makefile
```

Notre projet se base sur trois interfaces dont l’architecture a été établie.

`ICore`
Le Core permet la communication entre les deux autres parties :

- une [partie graphique] qui affiche les éléments du jeu

- une [partie jeu] qui gère les règles

```cpp
class ICore {
    public:
		    virtual ~ICore() = default;
		    virtual int run(std::string graphPath) = 0;
		    virtual int load(std::string gamePath, std::string graphPath) = 0;
    private:
};
```

Il permet de lancer un jeu en utilisant une bibliothèque graphique définie. Il fait ensuite transiter les informations de l’un à autre, sans que chacun n’ait à connaître l’autre.

`IGame`
La partie jeu du projet est dédiée à créer les jeux en eux-mêmes, dans leur ensemble. Il contient donc les informations pour chaque élément du jeu, sa position, sa direction, ça taille, ou quelle image il faut utiliser. A partir de ces informations, il peut également calculer les règles du jeu, sa physique, ou sa réaction à certains éléments de jeu.

```cpp
class IGame {

        public:
            virtual ~IGame() = default;
            virtual void handleEvent(event_t) = 0;
            virtual data_t update(void) = 0;

        private:

    };
```

`IGraphic`
La partie graphique du projet est principalement dédiée à l’affichage d’éléments visuels.
Elle permet aussi de prendre en compte les entrées utilisateurs, afin de savoir quelle touche a été appuyée ou relachée.

```cpp
    class IGraphic {

        public:
            virtual ~IGraphic() = default;
            virtual event_t getEvent(void) = 0;
            virtual void display(data_t) = 0;

        private:

    };
```