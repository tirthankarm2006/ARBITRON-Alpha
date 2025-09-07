# ARBITRONIC Engine
The design of the Arbitronic(Phase Alpha) Graphics Engine. This will be a Modern OpenGL(glad version 3.30) based graphics engine. 

# Frameworks used(for now)
Rendering System:- OpenGL(glad version 3.30)

UI System:- Imgui

Logging System:- spdlog

Texture Loading System:- stbi_image(nothings)

3D Models/Assest Loading and Management System:- Assimp

Window Management System:- glfw

Mathematics:- glm

# How to clone and Build
Use "git --recursive" to clone this repository and necessary dependencies. 
After cloning, open the "Premake_Files" under "Engine/3rdPartyLibs/", and copy the .lua files and edit the names to premake.lua for all of the them.
Then run the GenerateProjectFiles_vs2019.bat and run the generated .sln files to open the project on Visual Studio. If you want to generate project files
for other versions of Visual Studio, open the .bat file and replace the "vs2019" with "vs2017" or "vs2022".

If you want to only run the application, go to Engine/binaries/Main run the .exe file. You can even re-build these files from visual studios if you want.

# Current Work
->Making a profiling system that runs before the engine starts where to create/load a profile

# Immediate future changes(not currently happening)
->To show a initial note to the user about "Loading models" when the engine is starting

->Making 2D Environment port of the Engine

->Incorporating, Multiple Scene System for one profile

->To log messages onto the Editor window using imgui

->To create a location for storing and loading Model Locations in our scene

->To write into Shader parameters file through the Editor window using imgui 

->Making a automated system to load Shader Parameters and pass it to OpenGL shader and setting up the default shaders

->Incorporating, Single Scene System and Entities, Components and Systems into the engine

# Distant future Changes
->To try to make the Shaders loader under the Renderer3D serialized for faster loading

->To make the model loader serialized as well

->To make serialized texture loader

->To implement Lighting, shadow and Post Processing
