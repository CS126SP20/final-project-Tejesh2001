# Final Project

# [CS126 Final Project - Firebending trials]

Author: [Tejesh Bhaumik]






**Desciption**

Based loosely on the TV show Avatar : The Last Airbender. 
You play as Avatar Aang, and you have to fight firebenders who shoot fireballs from the top of the screen. 
You can shoot airballs to deflect these fireballs, or you may dodge them
If you deflect these fireballs though, they might ricochet off the walls and hit you and kill you
You can fire a maximum of five airballs at a time, and each fireball you hit scores you a point
The aim of the game is to last the longest and score the highest points

**Dependencies**

* CMake
* MSVC 2015
* clang/clang++

**Libraries used**

* Cinder
* Box2D
* Cinder :: OpenGL

To Build It :

* Download Cinder and set it up 

1) You can download the latest version Cinder for your platform at https://libcinder.org/download. The latest version is v0.9.2.

2) Here is a basic tutorial on how to develop Cinder projects: https://libcinder.org/docs/guides/tour/hello_cinder_chapter1.html.

3)Extract the downloaded Cinder zip folder into a folder. We’ll call this folder ~/Cinder throughout the instructions

4) Open the ~/Cinder folder in CLion and click the green build button. This will build libcinder. You only need to do this once per          machine. This build might take a while.

You're done setting up Cinder! 

To use the CinderBlock Box2D

* Open your CMakeLists.txt/src
* Under ci_make_library, there is a heading named BLOCKS.
* Write Box2D next to that heading.
* Reload CMakeLists.

You're done setting up!


Control | Actions
-----|--------------------
  W / Up arrow key   | Go up one unit      
  S / Down arrow key | Go down one unit                
  A / Left arrow key | Go left one unit                   
  D / Right arrow key | Go right one unit                    
  Return key /Mouse press | Shoot airball
  
