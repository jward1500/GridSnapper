<img width="1600" height="600" alt="Grid Snapper Title Screen" src="https://github.com/user-attachments/assets/2110e50c-1621-41cc-9277-9906800f0390" />

# Grid Snapper

Test out your muscle memory with this speedrunning-focused arcade game. Practice the levels to improve your time and fight against <strong>Snap</strong> and <strong>Croc</strong> to get on the leaderboard.

If you're simply interested in playing the game, check out this [Grid Snapper Webpage](https://jward1500.github.io/GridSnapperWebsite/). If you're curious about how the game was made, the code for the game is public with a project setup guide below.

## About the Project and Developer

What started out as a quick summer project to experiment with [SDL](https://www.libsdl.org/) turned into a quirky arcade game that I became proud of. The basic gameplay and UI functionality were created first and the storyline and theme followed. The goal of this project was not to make a full game engine or even to utilize game software design patterns, but to simply see what it took to make a game with C++. In the process of working on this project, I learned much about graphics programming, organizing game logic and UI logic, and working on larger projects in general.

The code isn't perfect, and there are many things I would have designed better in retrospect. The code in "core.cpp" certainly turned more messy than intended due to additions I added on after designing the initial game. Still, I chose to make this a project with personality with a tradeoff of messier design. The goal is to apply what I learned from mistakes made in this project to future projects.

## Project Setup Guide

The following instructions are for setting up a Visual Studio project on Windows. This is my first time creating a public Visual Studio repository like this with extra assets, so the setup is pretty involved. But with enough perseverance, you can run this in Visual Studio too!

### Get GridSnapper and SDL 3.0

- Clone the repository. This will provide you with the solution and the code for the project.

- Download [SDL 3.0](https://github.com/libsdl-org/SDL/releases/tag/release-3.2.22) and unzip the folder, remember where you unzipped SDL to.

### Connecting the project to SDL 3.0 (the fun part)

- Set an *environment variable* called SDL_DIR to the path SDL 3.0 is located on your computer. This can be done by accessing the “Advanced System Settings” on your windows computer -> selecting the “Advanced” tab -> clicking the “environment variables” button -> then creating a new variable. This environment variable is important for the GridSnapper project to find important SDL files.

- Open the unzipped SDL 3.0 folder and navigate to VisualC -> SDL.sln, open this in Visual Studio and build the project. You don’t need to run the SDL project itself, you only need the .dll and .lib files it produces. It’s normal that SDL can’t be executed directly, since it’s a library, not an application.

- In the same way, open the GridSnapper Visual Studio Solution from the repository you cloned and build it in Debug and Release mode. *If you had Visual Studio open before you set the environment variable, you will need to restart it.* If you try to run it, it will fail. This is normal because it isn't set up quite yet.

- In SDL's build output directory (VisualC -> x64 -> Debug and Release), copy and paste <code>SDL.dll</code> into GridSnapper’s build output directory (x64 -> Debug and Release). You will need to grab and place the Release dll and the Debug dll. 

Now, the Grid Snapper Visual Studio project should be able to find and use SDL.

### Getting the resources

- Download the latest release from GridSnapper repository, and unzip the folder.

- In the folder, navigate to Release->resources. Copy the entire contents of the folder. This folder contains all images and sounds for the game.

- In the GridSnapper repository folder, navigate to the x64 directory, and in both the Release and Debug folders, create a new "resource" folder and paste all of the project resources in it.

- Then, go back to the root directory of the release folder, and copy the <code>snap_speak.ico</code> file. Go to the repository folder, navigate to the x64 folder again, and outside of the Release and Debug folder, paste the icon file.

The final folder hierarchy in the repository should be something like:

- x64 contains Debug/ and Release/ and <code>snap_speak.ico</code>.
- Release/ contains a resources/ directory that has all of the game's assets in it.
- Debug/ also contains a resources/ directory that has all of the game's assets in it.

*After all that, you should be able to run the project in Debug and Release mode!*


