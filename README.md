
<i>This is a personal work in progress project that was started with the goal of using everything I've learned to create my own framework and eventually a fully fleshed-out game using it. All code has been written by me, aside from Interface classes (UI).</i>


<h1><u>Game Design Document: Planet Jamlo</u></h1>


<p align=center>
<img src="https://github.com/VigilantChap/Planet-Jamlo/assets/31937008/a906861b-56e3-4adb-8f77-84c610e73107" />
</p>

<h3>Development Team</h3>
Project Lead, Programmer : Andi (Arielle) Vachon<br>
UI Programmer : John Dennison<br>
Artist : Eric Beer

<h3>Overview</h3>
Planet Jamlo is a futuristic-themed roguelike that takes place on an alien planet that is overrun with
hostile robots. The goal is to survive as long as possible defeating an endless wave of enemies and
acquiring upgrades to grow in power. 

<h3>Story</h3>
Little Astronaut is on a mission to explore Planet Jamlo and return with scientific findings that will
help save their civilisation. As it turns out, there are a seemingly infinite amount of robots on this
planet that want to kill Little Astronaut. In order to suvive, they must fend off these robots long
enough for their computer to record the important data from the planet.


<h3>Gameplay Mechanics</h3>

<h4>Shooting</h4>
Little Astronaut has a weapon that fires projectiles of energy in a desired direction which damages
and kills the robots. 

<h4>Running</h4>
Movement is smooth and unrestricted to allow the ability to manoeuvre around enemy attacks in thefast-paced environment. Dodging
Little Astronaut can roll to dodge enemy attacks that would otherwise be difficult to avoid. The roll
provides a brief period of invincibility during the animation and has a short cooldown after being
performed. 

<h4>Health</h4>
If hurt, Little Astronaut can heal from small health orbs which occasionally drop fromthe defeatedenemies. 

<h4>Upgrades</h4>
Enemies occasionally drop upgrade modules to help Little Astronaut stay alive and grow in power as
the enemies get stronger. These modules can improve things like fire rate, critical chance, block
chance, and movement speed. They can also modify things such as adding additional projectiles per
shot, shields, “personal space” damage aura, and many more. 


<h3>Artstyle</h3>
Theme: Flat, pastel colours. Furturistic and cute. Pixel-style. 

<h4>Reference art:</h4>

![image](https://github.com/VigilantChap/Planet-Jamlo/assets/31937008/6e2fd680-fc95-45c3-9e69-c4ce1fd76f91)
![image](https://github.com/VigilantChap/Planet-Jamlo/assets/31937008/948fc953-86a3-4d49-9cf5-5ef08703dbc6)
![image](https://github.com/VigilantChap/Planet-Jamlo/assets/31937008/9d8e25cd-5491-4b05-832e-aa570a5a0605)

<br>
<br>
<br>
<br>

<h1>Technical Design Document</h1>

<h3>Elevator Pitch</h3>

In this WIP Roguelike, you will try to survive as long as possible by killing enemies & obtaining the
upgrades/modifiers that drop from them. Enemies are killed by shooting projectiles at them, but
watch out for their own attacks! With a bird’s eye view, you can see all the enemies around you. Jumping and dodging will help keep you alive. Ever so often, a boss will spawn which has special
attacks and much more health. Enemies will continue to spawn endlessly until you can’t survive any
longer. 

<h3>Core Systems</h3>
<h4>Player Input</h4>

![image](https://github.com/VigilantChap/Planet-Jamlo/assets/31937008/2755a59b-7ab7-4a62-843b-6a06f5edcd0f)
![image](https://github.com/VigilantChap/Planet-Jamlo/assets/31937008/fef05b67-224d-4ad3-aa1e-c7cc8a9c340d)

<h4>Game Loop & Events</h4>

![image](https://github.com/VigilantChap/Planet-Jamlo/assets/31937008/5db63491-3e30-4a00-a095-649a24066d68)

<h4>Gameplay Functionality and Enemy AI</h4>

![image](https://github.com/VigilantChap/Planet-Jamlo/assets/31937008/88f6056d-f452-4e69-acec-536ce2cd159d)
![image](https://github.com/VigilantChap/Planet-Jamlo/assets/31937008/1a47f887-dca0-4a61-882c-1d8b7482db2b)

<h4>Game Scene Components</h4>

![image](https://github.com/VigilantChap/Planet-Jamlo/assets/31937008/9d937fad-d7b2-49b6-9a6a-3d0e0c9d57d1)

<h4>Engine Framework</h4>

![image](https://github.com/VigilantChap/Planet-Jamlo/assets/31937008/7502d63a-f0d5-4253-9ec6-6040ea0b42f1)

<h4>Miscellaneous Information</h4>

The project uses the following tools to accomplish these goals: <br>
- C++ <br>
- Visual Studio <br>
- SFML <br>
- GitHub <br>
<br>

Upcoming features: <br>
- Physics Engine <br>
- Smart Map Tile Generation <br>
- Particle Effects System <br>
- Additional Levels and Game Modes <br>

