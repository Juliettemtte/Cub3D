<h1 align="center">
	Cub3D
</h1>
<p align="center">
	<b><i>Building a 3D engine, one ray at a time... </i></b><br>
</p>

### The Challenge
The goal of this project was to develop a 3D game engine from scratch using the raycasting technique. This engine simulates a 3D environment, allowing the player to navigate through a maze-like world. We were tasked with implementing core functionalities like handling textures, player movement, and proper rendering of the environment.

Key features implemented in this project include:

Rendering:
- Raycasting for rendering a 3D world from 2D map data.
- Handling textures for walls, floors, and ceilings.
- Color mapping for walls, floors, and ceilings.
- Creating a basic camera system to simulate player view.

Player Movement:
- Implementing player movement using the arrow keys and WASD.
- Smooth rotation to change the player’s view of the world.
- Collision detection to prevent the player from walking through walls.

User Interface:
- Displaying the 3D environment with textures and colors.
- Handling basic input for player control.
- Providing real-time updates of the game state.

The project was built entirely in C with MLX42, focusing on core game engine concepts and low-level programming techniques.

### Installation
#### Clone the repository:
``` 
git clone https://github.com/YourUsername/Cub3D.git
cd Cub3D
make
```
#### Run the game
```
./cub3d <map_file>
```
### Map file
The map files used in Cub3D follow a specific format that describes the environment layout, including walls, floors, ceilings, and the player's starting position. Each map is made up of several components, and the format must adhere to the following structure:

1. Configuration:
```
NO [texture_path]        # North wall texture (path to image file)
SO [texture_path]        # South wall texture (path to image file)
WE [texture_path]        # West wall texture (path to image file)
EA [texture_path]        # East wall texture (path to image file)
F [r] [g] [b]           # Floor color in RGB (e.g., F 255 255 255)
C [r] [g] [b]           # Ceiling color in RGB (e.g., C 0 0 0)
```

2. Map:
   
The map consists of a grid made of characters that represent walls and empty spaces. The walls are indicated by 1, while empty spaces are represented by 0.
The player's starting position is indicated by N, S, E, or W, representing North, South, East, or West respectively. Each row should be separated by a newline.


*Note : There must be a valid closed map (i.e., the walls must completely surround the playable area). The player must always start in a valid position, inside the map, and facing one of the four cardinal directions (N, S, E, W).*
  
### Controls
- Move Forward: W
- Move Backward: S
- Move Left: A
- Move Right: D
- Turn Left: Left Arrow
- Turn Right: Right Arrow
- Quit: ESC

Once the game is running, you can explore the 3D world using the movement keys. The game will continuously render the environment in real-time, updating the player's view as they move around.

------
<p align="center">
	Made by Helena Utzig (@hutzig) and Juliette Mouette (@jmouette) <br>
</p>
