Modified by: Maythas Wangcharoenwong 20240722
# N-body-simulator
----------
This project aims to Simulate interactions of N-bodies in using Particle-Particle Method implemented with `OpenGL` and `C++`. The project provides option to use either Compute Shaders written in `glsl` or simple CPU implementation.

### Features:
- Velocity-Verlet and Euler Integrator
- Spawning cluster of bodies into shape such as discs and globular clusters.
- Although the project does not support taking arguments yet, setups can be done after launching the program.

![](images/default_12.gif)
<div align="center">
Default Test 12 
</div>

----------
### Build and Run
Simply use the scripts provided in `./QOL_Snippets` to build and run the program.

----------
### Setting up a simulation
Setting up a simulation is simple, you can either use one of the pre-written default tests or setting up the simulation manually. The steps are as follow.
1. run the run script
2. Answer the prompt accordingly <br>
    The input will be formatted in the following form. Each input value must be separated with the a space.
    ```
    Prompt here....
    <variable_1> <variable_2>
    :<your input value 1> <your input value 2> 
    ```
    After you finished writing down the values without `<>`, simply press enter.<br>
    In the case that the input is invalid, the prompt will be shown again.
    
3. Adding particles
   1. If you choose the manual setup, simply follow step 2 since the input format stays the same.
   2. If you choose default tests, you can simply pick the valid test based on the following. 
        
    ```
        Default test 0-4   : Test cases for CPU based setup (~1k particles)
        Default test 5-13  : Test cases for GPU based setup (~10k particles)
        Default test 14-22  : Test cases for GPU based setup (~20k-30k particles)
        Default test 5-13  : Test cases for GPU based setup (~40k+ particles)
    ```
4. The simulation will then being in a paused state, simply press `p` to begin

----------
### Controls
Please refer to the `"Window Controls"` when running the program.

|Controls|Action|
|-------------------------------|-------------------------------------------------------------------------------------------------------|
|esc                            | exit simulation                                                                                       |
|h                              | display controls on the console.                                                                      |
|p                              | pause / continue the simulation.                                                                      |
|i                              | display setup log.                                                                                    |
|o                              | toggle orbit / free-flying mode.                                                                      |
|middle mouse drag + left shift | pan the camera in the mouse drag direction.                                                           |
|middle mouse drag + left ctrl  | zoom in/out by dragging mouse forward and vice versa. (free-flying mode: move forward / backwards.)   |
|middle mouse drag              | orbit the camera about the center in the mouse drag direction. (free-flying mode: rotate the center.) |
|middle mouse scroll            | same action as middle mouse drag.                                                                     |
----------
### Known Issues
Please don't minimize the simulation screen or it will blow up. 😂

----------
### Examples 

![](images/default_24.gif)
<div align="center">
Default Test 24 
</div>
<br>

![](images/default_25.gif)
<div align="center">
Default Test 25
</div>
<br>

![](images/default_30.gif)
<div align="center">
Default Test 30 
</div>