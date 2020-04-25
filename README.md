# Final Project

# [CS126 Final Project - Firebending trials]

Author: [Tejesh Bhaumik]

**Desciption**

My project will be a modified tower defense game where the tower is replaced by a movable player (Within a certain space). Incoming enemies come in from every direction. You can either dodge them or attack them with bullets. But there's a catch. The bullets will get kill the enemies but might ricochet and hit you.

**Background knowledge and motivation**

The background knowldege I require for this project stems from a personal project I had made which implemented 2D shooting. Thereby I know how to implement a firing mechanism. I also am heavily reliant one the knowldege I gained from the coursework of CS 126.

My motivation for doing this project lies in the fact that such a game hasn't been made before, and there it would allow me to use my imagination to the full extent. It also involves a physics library and I am excited to see how my playable objects interact with each other.


**External Libraries required**

* I will need the BOX2d library for my Game Engine
* I might use the imGUI library to handle my GUI.
* Following are the links to the respective libraries:
    * https://github.com/erincatto/Box2D
    * https://github.com/ocornut/imgui

**Tentative Timeline**

The work is to be split up into three categories : Game Engine, UI, and graphics

WEEK | Game Engine | UI | Graphics
-----|--------|----|--------
1    |Implement tracking of incoming enemies.Implement shooting bullets for player |Game Screen displays moving circles for enemies|No interaction available                 
2    |Implement different types of enemies with differences in skill level. Implement player movement| Game screen displays  circles for enemies and a movable player | The player can be moved using WASD keys.  
3    |Implement richocheting of bullets on colliding with the enemy once and then vanishing if it hits the walls | Game screen displayes player, enemies and bullets | The player can be moved using WASD keys and bullets can be fired using the Enter key

I will be following graybox testing throughout this project.

**Extras**

* I would like to implement player movement throughout the game
* I would like to implement some sort of powerup and a health bar/so the player doesn't die on the first hit
* I would try and render some graphics in 3D
