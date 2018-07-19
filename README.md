Sniper, Guerilla, Shark, Razor et les autres
============================================

Cette pièce de Emmanuelle Grangier de la compagnie P.A.S. met en scène une
dizaine de petits robots mobiles ronds. Ce dépôt regroupe les codes et les
différentes procédures afin de lancer les robots ou les refaire.

[video](https://www.youtube.com/watch?v=KFx6Ewun1QE)

# procédure de lancement des robots

- Brancher le Router ASUS et attendre une bonne minute que le réseau wifi soit déployé.
- Allumer l'ordinateur central et le connecter au Wifi sniperAProbot ou sniperAProbot-5G (même mot de passe)
- Préparer le logiciel PureData de contrôle
- Insérer deux batteries par robot à l'arrière et les connecter aux petits connecteurs qui sortent du robot. Il n'y a pas besoin d'ouvrir le robot pour les brancher
- Allumer les deux interrupteurs du dessus et attendre quelques secondes que l'anneau de LED s'allume en bleu clignotant lent.
![Branchement](https://github.com/ThotAlion/Sniper/blob/master/IMG_20180719_160841.jpg?raw=true)
- Votre robot est prêt à recevoir les ordres boursiers. En considerant le robot 5 on a
- /ROBOT_5/CONF $i qui commande une vitesse (ne pas dépasser 150)
- /ROBOT_5/SELL_UP $i LED allumée jaune et augmente le rythme
- /ROBOT_5/SELL_DOWN $i LED allumée jaune et diminue le rythme
- /ROBOT_5/HOLD_UP $i LED allumée bleu et augmente le rythme
- /ROBOT_5/HOLD_DOWN $i LED allumée bleu et diminue le rythme
- /ROBOT_5/BUY_UP $i LED allumée blanc et augmente le rythme
- /ROBOT_5/BUY_DOWN $i LED allumée blanc et diminue le rythme

Si le robot ne fonctionne pas :
- Vérifiez que le connecteur de batterie est bien enfoncé
- Eteindre et rallumer juste la partie puissance (interrupteur PUISS)
- Vérifier la tension de la batterie

# IMPORTANT : LES BATTERIES
Le robot ne possède pas de protection contre la décharge de batterie. Si jamais la batterie se décharge trop, la batterie meurt et ne peut plus être chargée. Cela peut être onéreux (surtout sur 24 batteries).
Les batteries utilisées sont la mise en série de deux cellules LiPo. Une cellule a une tension de 3.7V. Cela fait donc 7.4V au total.
Une cellule complètement chargée a une tension de 4.2V. Si la tension de la cellule passe en dessous de 3.3V, la laisser reposer une nuit dans l'espoir qu'elle remonte. Si la tension passe en dessous de 3V, la cellule est perdue.
Dans le kit, une boite en carton (contenant par ailleurs la bande magnétique) permettra d'entreposer les batteries utilisées afin de les recharger. Dans cette boite est aussi entreposé le testeur de batteries à brancher comme sur la photo.
![Test batteries](https://github.com/ThotAlion/Sniper/blob/master/IMG_20180719_163603.jpg)


#L'architecture


#Le code embarqué dans les robots


#Le code embarqué dans les ESP8266


#Le code de contrôle global


#Registre de traçabilité

## Numéro 1 (Analogique)
robot cannibalisé. Hors service.
## Numéro 2 (Analogique)
robot au comportement nominal.
## Numéro 3 (Analogique)
capteurs IR de droite et du milieu sont morts. Les bumpers et la sonde effet hall sont opérationnels. Impression de murs fantomes.
robot au comportement nominal.
## Numéro 4 (Digital)
robot au comportement nominal.
## Numéro 5 (Digital)
robot au comportement nominal.
## Numéro 6 (Digital)
robot au comportement nominal.
## Numéro 7 (Digital)
robot au comportement nominal.
## Numéro 8 (Digital)
robot au comportement nominal.
## Numéro 9 (Digital)
robot au comportement nominal.
## Numéro 10 (Digital)
robot au comportement nominal.
## Numéro 11 (Digital)
robot au comportement nominal.

