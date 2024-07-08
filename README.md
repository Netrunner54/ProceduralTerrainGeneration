# Procedural Terrain Generation
This project was created for learnig purposes. It uses compute shaders to generate random terrain and tesselation shader to render it in high resolution.

## Controls
`W` `A` `S` `D` to move along x/z axis. <br>
`SPACE` `LCTRL` to move along y axis. <br>
`LSHIFT` to move faster. <br> 
`MOUSE` to look around. <br>
`R` to generate new random terrain. <br>
`F` to render in wireframe mode. <br>
`H` To switch between "rendering in high quality" and "optimized rendering". <br>
`ESC` to exit. <br>

## Screenshots
![1](https://github.com/Netrunner54/ProceduralTerrainGeneration/assets/81921482/72347309-8bde-4fa8-8478-35307d060a0a)
![2](https://github.com/Netrunner54/ProceduralTerrainGeneration/assets/81921482/93f5e4c7-82d5-4c41-b9eb-26471a784d41)

## Terrain Generations
Terrain is generated in compute shaders for efficiency. 3 textures are used to describe the terrain.
Firstly height map is generated from perlin noise, than normal and diffuse maps are generated from height map.






## Rendering
#### Tesselation
If optimize rendering is allowed terrain closer to the camera will be more tesselated than terrain further away.
Normal mode | Wireframe mode
-------| ---------
![normal_mode](https://github.com/Netrunner54/ProceduralTerrainGeneration/assets/81921482/fdb99769-6567-4614-be4f-224b499ac44e) | ![wireframe_mode](https://github.com/Netrunner54/ProceduralTerrainGeneration/assets/81921482/70361087-4521-4f95-a2fd-f3a9286e96fc)
![normal mode_2](https://github.com/Netrunner54/ProceduralTerrainGeneration/assets/81921482/d0b20157-cd37-470a-8335-7d7d411952bc) | ![wireframe mode_2](https://github.com/Netrunner54/ProceduralTerrainGeneration/assets/81921482/617bb742-40d0-4aaa-874f-ce98ba2236bc)

#### Normal mapping
For realistic lighting normal maps are used. Below you may see the difference between rendering with normal maps (on the left) and without them (on the right).
![with_and_without_normal_mapping](https://github.com/Netrunner54/ProceduralTerrainGeneration/assets/81921482/93221f4f-abf0-44b3-b392-c670dad75508) 



## Build on Windows
Run `premake.exe vs2022` to generate Visual Studio 2022 solution.

## Dependencies
<details>
<summary>Used libraries</summary>
 - glad <br>
 - glfw <br>
 - glm <br>
</details>
