# Final Project

# [CS126 Final Project - Firebending trials]

 **Author: [Tejesh Bhaumik]**
 
**Desciption**

Based loosely on the TV show Avatar : The Last Airbender. 
You play as either Avatar Aang or Katara, and you have to fight firebenders who shoot fireballs from the top of the screen. 
You can shoot waterballs to deflect these fireballs, or you may dodge them
If you deflect these fireballs though, they might ricochet off the walls and hit you and kill you
You can fire a maximum of three airballs at a time, and each fireball you hit scores you a point
The aim of the game is to last the longest and score the highest points

**Game Screenshots**

**Start Screen**


![ text](https://github.com/CS126SP20/final-project-Tejesh2001/blob/master/assets/StartScreenshot.png?raw=true)

**Game Screen**


![play](https://github.com/CS126SP20/final-project-Tejesh2001/blob/master/assets/play.png?raw=true)

**End Screen**

![end](https://github.com/CS126SP20/final-project-Tejesh2001/blob/master/assets/end_screenshot.png?raw=true)

**Project Structure**

Please read this to understand the project structure :

https://cliutils.gitlab.io/modern-cmake/chapters/basics/structure.html
 
**Dependencies**

* CMake
* MSVC 2015
* clang/clang++

*For Windows*

You must have MSVC 2015 installed on your device

**Libraries used**

* Cinder
* Box2D
* Cinder :: OpenGL

To Build It :

* Download Cinder and set it up 

1) You can download the latest version Cinder for your platform at https://libcinder.org/download. The latest version is v0.9.2.

2) Here is a basic tutorial on how to develop Cinder projects: https://libcinder.org/docs/guides/tour/hello_cinder_chapter1.html.

3) Extract the downloaded Cinder zip folder into a folder. We’ll call this folder ~/Cinder throughout the instructions

4) Open the ~/Cinder folder in CLion and click the green build button. This will build libcinder. You only need to do this once per          machine. This build might take a while.

You're done setting up Cinder! 

To use the CinderBlock Box2D

* Open your CMakeLists.txt/src
* Under ci_make_library, there is a heading named BLOCKS.
* Write Box2D next to that heading.
* Reload CMakeLists.

You're done setting up!

**About Cinder**

Cinder is a free and open source library which allows creative coding.If you want to know more, here is a link to the official website :

https://libcinder.org/

**About Box2D**

Box2D is a physics library which allows us to simulate Newtonian mechanics with objects that follow Newtownian physics in a world that we set up. It allows for realistic action in my game. If you want to know more, here is a link to the official website :

https://box2d.org/

**GAMEPLAY CONTROLS**

Key | Actions
-----|--------------------
  W / Up arrow key   | Go up one unit      
  S / Down arrow key | Go down one unit                
  A / Left arrow key | Go left one unit                   
  D / Right arrow key | Go right one unit                    
  Return key /Mouse press | Shoot airball
  M key | Mutes the background music
  Spacebar | Starts the game
  Right shift | Restarts the game
  
