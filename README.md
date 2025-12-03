### Kandidatnr: 10076

# Tank game
Exam for i Object orientate programmering.

This project is a simple 3D tank game, created using the threepp libary,
The player controls a tank that can move around an arena, shoot bullets, collect power-ups and fight enemis.

- You drive around in an arena
- Collect power-ups that is speed boost and ammo
-Level 1 you need to shoot down all the trees to unlock level 2.
- A portal take you to level 2
-In Level 2 you need to destroy all enemy turrets to win the game.
- You only have 10 HP, if you get hit 10 times you lose the game.
- If you drive into an enemy turrent you also lose the game.

How to play the game and rules:
---------------------------------

The controls for the tanks are as follows:
- W - Move Forwards
- S - Move Backwards
- A - Turn Left
- D - Turn Right
- Space - Boost
- E - Shooting bullets
- R - reload the game in case of bugs

Pickup items:
- Speed boost: Each boost give 5 seconds. It's possible to stack up to max 30 sec.  Yellow sphere to collect.
- Ammo: Refill your ammo. Green sphere to collect. Get 4 bullets per pickup.

Good luck and have fun!

<p align="center">
  <img src="./GIF/GIF_quike_gameplay.GIF" alt="Gameplay Demo" width="900">
  <br>
  <i>Level 1: Shooting trees and collecting power-ups</i>
</p>



### Own evaluation:

#### What is good:
- What I'm most proud of in this project is the shooting mechanic and the reloading of ammo.
- I also like that it's possible to stack the boost.
- That the program even works at all!
- The auto aim on the enemy turrets is also something I'm happy with. Makes it more challenging




#### What can be improved:
- The tank movement could be smoother and more responsive. Also inmport bullet physics to make it more realistic.
- The level design could be more varied and interesting, with different themes and challenges.
- Adding sound effects enhance the gaming experience.
- Have a better 3D model for the tank. One that actually can have rotations on the belt, so that it would look more realstic.
- More detailed textures and enviroment to make the game more immersive
- Have a diffrent type of look on the enemies turrents.
- More obsticals in level 2
- Overall I wish that I had planed this more properly from the start, so that I could have had more time to implement more features and polish the game. - That would also help me have a better structerd code



#### Soruces used:

-3D moddel Tank license: Tank by Nico _ [CC-BY] (https://creativecommons.org/licenses/by/3.0/) via Poly Pizza (https://poly.pizza/m/41Tq_Kf0Tui)
-Three.js library: https://threejs.org/
- Used exampels from threepp: https://github.com/markaren/threepp#
- To create Git hub. actions I used the one threpp examples as a guide: https://github.com/markaren/threepp/blob/master/.github/workflows/config.yml
- Used AI for help with writing some funcitons, helpiing me with bug fixes and help explaining concepts I struggled with. Claud, ChatGPT and GitHub Copilot.
- Used the ImGui libary for creating a simple in game UI: https://github.com/ocornut/imgui. 
- Used the examepl https://github.com/ocornut/imgui/tree/master/examples/example_glfw_opengl3


