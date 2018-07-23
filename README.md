Sniper, Guerilla, Shark, Razor et les autres
============================================

Cette pièce de Emmanuelle Grangier de la compagnie P.A.S. met en scène une
dizaine de petits robots mobiles ronds. Ce dépôt regroupe les codes et les
différentes procédures afin de lancer les robots ou les refaire.

[![Sniper](http://img.youtube.com/vi/KFx6Ewun1QE/0.jpg)](https://www.youtube.com/embed/KFx6Ewun1QE)

# procédure de lancement des robots

- Brancher le Router ASUS et attendre une bonne minute que le réseau wifi soit déployé.
- Allumer l'ordinateur central et le connecter au Wifi sniperAProbot ou sniperAProbot-5G (même mot de passe)
- Préparer le logiciel PureData de contrôle
- Insérer deux batteries par robot à l'arrière et les connecter aux petits connecteurs qui sortent du robot. Il n'y a pas besoin d'ouvrir le robot pour les brancher
- Allumer les deux interrupteurs du dessus et attendre quelques secondes que l'anneau de LED s'allume en bleu clignotant lent.
<p align="center">
  <img height="300" src="https://github.com/ThotAlion/Sniper/blob/master/branchement.jpg">
</p>
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
<p align="center">
  <img height="300" src="https://github.com/ThotAlion/Sniper/blob/master/test_batteries.jpg">
</p>

# L'architecture
<p align="center">
  <img height="300" src="https://github.com/ThotAlion/Sniper/blob/master/archi.png">
</p>

Chaque robot est autonome. A partir de ses capteurs, il va piloter ses deux moteurs et les composantes de son bandeau LED. Il possède d'abord en bas deux bumpers qui détectent la présence d'un obstacle direct, à gauche ou à droite. Sa réaction sera de faire immédiatement marche arrière pour se dégager de l'obstacle et faire un demi-tour pour repartir.
Il possède aussi une sonde à effet Hall dessous pour détecter une bande magnétique cachée sous le tapis de danse. Sa réaction sera équivalente au contact bumper.
Ensuite, il possède trois télémètres infrarouges à l'avant qui s'enclenchent à quelques centimètres du robot. La réaction sera de faire un quart de tour dans la direction opposée au télémètre qui a détecté l'obstacle. La vitesse du robot est aussi divisée par deux.
Pour chaque réaction capteur, l'anneau LED réagit avec l'activation aléatoire d'une LED en blanc.
Enfin, le dernier "capteur" est le module ESP8266 qui va recevoir des messages OSC sur l'adresse broadcast (192.168.10.255)
Le message OSC /ROBOT_1/CONF $i force la valeur de la vitesse nominale du robot
Les messages OSC /ROBOT_1/BUY|SELL|HOLD_UP|DOWN $i va influer sur l'anneau LED.
l'anneau LED est basé sur un modèle de battement:
puissance = sin(theta) 
avec theta = theta+omega*dt
La valeur du message va modifier la consigne omega avec un gain fort (la dispersion des valeurs d'ordre boursier étant faibles). Le type de message va juste déterminer la couleur. Ici BUY = BLANC, HOLD = BLEU et SELL = JAUNE.

Pour information, le robot possède des encodeurs magnétiques en quadrature qui permettraient l'asservissement en vitesse de chaque moteur. Cependant, ces codeurs ne sont pas câblés sur les broches à interruption, et le nombre de pas par tour de roues est très important.

Tout ceci est codé dans le robot via l'interface Arduino dans le fichier Sensor.h et dans la routine Algo(). Cette routine fait tourner un automate à état fini.

<p align="center">
  <img height="300" src="https://github.com/ThotAlion/Sniper/blob/master/Machine_etat.png">
</p>

# Le code embarqué dans les ESP8266
Le code de base dans les ESP8266 (commande AT) n'est pas suffisant pour transférer des trames OSC. Pour faire cela, il faut programmer l'ESP8266 avec le programme dans ce repo (OSC_bridge). L'ESP8266 peut se programmer via l'interface de programmation Arduino. Il faut que l'interface soit modifiée pour être compatible ESP. Ce lien explique comment faire : [Programmer un ESP8266](https://www.fais-le-toi-meme.fr/fr/electronique/tutoriel/programmes-arduino-executes-sur-esp8266-arduino-ide). Attention, dans ce lien, le montage final est trop complexe et faux (les RX et TX ne sont pas inversés...)
Il faut avoir un matériel minimum pour programmer ces puces et notamment un câble de conversion [FTDI de USB vers RS232 en 3.3V (Attention, pas le 5V](https://shop.clickandbuild.com/cnb/shop/ftdichip?productID=97&op=catalogue-product_info-null&prodCategoryID=293)
Pour placer l'ESP8266 en mode programmation, il faut faire le montage suivant :

- VCC ESP8266 -> 3.3V FTDI
- GND ESP8266 -> GND FTDI
- RX ESP8266 -> TX FTDI
- TX ESP8266 -> RX FTDI
- GPIO0 ESP8266 -> GND FTDI
- CH_PD ESP8266 -> 3.3V FTDI


# Le code de contrôle global


# Registre de traçabilité

## Numéro 1 (Analogique)
robot cannibalisé. Hors service.
## Numéro 2 (Analogique)
robot au comportement nominal.
## Numéro 3 (Analogique)
capteurs IR de droite et du milieu sont morts. Les bumpers et la sonde effet hall sont opérationnels. Impression de murs fantomes. Le robot a un comportement maladroit mais opérationnel.
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

