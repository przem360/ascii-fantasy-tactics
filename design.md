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
  
## System
  
### Attack
  
To roll "to hit," the attacker rolls 1d20 and adds their attack bonus (AB), as shown on the Attack Bonus table, as well as Strength bonus (if performing a melee attack) or Dexterity bonus (if performing a missile attack) and any other adjustments required by the situation.  
If the total is equal to or greater than the opponent's Armor Class, the attack hits and damage is rolled. A natural "1" on the die roll is always a failure.  
A natural "20" is always a hit, if the opponent can be hit at all (for example, monsters that can only be hit by silver or magic weapons cannot be hit by normal weapons, so a natural "20" with a normal weapon will not hit such a monster).  
*(BF. 57)*

  
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