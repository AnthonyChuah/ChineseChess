# Chinese Chess

## Introduction

Chinese Chess (also known as Elephant Chess) is a game similar to chess. The objective is to place your opponent's general in checkmate.
The rules are written here: http://www.chessvariants.com/xiangqi.html

## Compilation

This builds only on a Linux machine with SDL2, SDL2_image, and SDL2_ttf libraries installed. To install those libraries:

* sudo apt-get install libsdl2-dev
* sudo apt-get install libsdl2-image-dev
* sudo apt-get install libsdl2-ttf-dev

With those installed, type 'make' at the top-level directory of the repo to create an executable 'game'.

Execute with './game gui' and the game will launch.

## Board Layout

Black pieces, signified by underscores around the unit letter, e.g. \_R\_ for the Black ChaRiot.

```
+---=---=---=---=---=---=---=---=---+
|_R_|_H_|_E_|_M_|_G_|_M_|_E_|_H_|_R_|
+-----------=---\---/---=-----------+
|   |   |   |   |   |   |   |   |   |
+-----------=---/---\---=-----------+
|   |_C_|   |   |   |   |   |_C_|   |
+-----------=---=---=---=-----------+
|_S_|   |_S_|   |_S_|   |_S_|   |_S_|
+-----------------------------------+
|   |   |   |   |   |   |   |   |   |
+~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~+
|   |   |   |   |   |   |   |   |   |
+-----------------------------------+
|*S*|   |*S*|   |*S*|   |*S*|   |*S*|
+-----------=---=---=---=-----------+
|   |*C*|   |   |   |   |   |*C*|   |
+-----------=---\---/---=-----------+
|   |   |   |   |   |   |   |   |   |
+-----------=---/---\---=-----------+
|*R*|*H*|*E*|*M*|*G*|*M*|*E*|*H*|*R*|
+---=---=---=---=---=---=---=---=---+
```

Red pieces, signified by asterisks around the unit letter.

The wavy horizontal line in the middle is the River, which the Elephant cannot cross.
Soldiers can only advance forward by one step per turn, until they cross the River.
After the crossing, they can also step sideways by one step per turn, but not backwards.

The 3-by-3 square containing the General and two Mandarins is the Palace. They cannot leave the Palace.

## Units

* R: Chariot
* H: Horseman
* E: Elephant
* M: Mandarin
* G: General
* C: Cannon
* S: Soldier
