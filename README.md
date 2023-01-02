# Flappy Jack (-o-lantern)

This game follows the rules and gameplay of the popular game *Flappy Bird*. Try to last as long as you can without hitting the top, bottom, or spawning wooden posts that appear from the right. You gain points for successfully passing through two wooden posts.

Made with Unreal Engine 5.1

## Controls

**[SPACE]** OR **[LEFT MOUSE CLICK]** - The jack-o-lantern jumps a short distance

**[ESC]** - Exit the game

## Development
All base classes (except the Widget used for HUD) were written in C++ first. Once I had the my basic classes and function working, I used blueprints to quickly prototype gameplay and then converted the majority of their code to C++.

## Features Done
- effect when hitting top or bottom of the screen
  - Screen Shake
- Better End Game Score Highlighting
- Sound: Hit Something
- Sound: Passing Through Gate
- Codify my GameMode blueprints
- save high score
- effect when you get a new high score
- every 10 seconds play a sound and effect to signal progress
- unbind mouse to screen

## Features that could be Cool to Add
- effects when flapping
- music
- projectiles you have to dodge

## What I am still working on
- post in comments of (Game Makers Toolkit)(https://www.youtube.com/watch?v=XtQMytORBmM)
