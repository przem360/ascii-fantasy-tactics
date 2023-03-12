ASCII FANTASY TACTICS
---------------------

## Screen

```
		ASCII FANTASY TACTICS 

    ABCDEFGHIJKLMNOPQRST
   ###################### > [g] Fred (Goblin) HP:4       
 1 #..grth..............#   [r] Rogue (Human) HP:5       
 2 #....................#   [t] Ted (Tentacle_Worm) HP:14
 3 #..##................#   [h] BadBoy (Hell_Hound) HP:18
 4 #..##................#                                
 5 #....................#                                
 6 #....................#                                
 7 #....................#                                
 8 #.............##.....# > [A] Avery (Fighter) HP:8     
 9 #.............##.....#   [K] Koko (Bl__Mage) HP:6     
10 #....................#   [M] Marsh (Archer) HP:6      
11 #....................#   [Z] Zok (Wh__Mage) HP:8      
12 #..AKMZ..............#
   ######################
   #                    #
   #Player's turn       #
Command > 

```
  
## Basic AI idea

Does monster have target? If not, choose.
Walk towards target.
Is target in attack range?
If yes - attack, if no, pass turn.

Every next turn.
Does monster have a target?
How far this monster is from its target?
Is there some Fighter closer (first found is enough)?
If there is 60/40:
60: take closer fighter as a new target.
40: keep following original target.

That's it. Not every fighter has to be targeted.