# Arbitrary Engine
The design of the Arbitrary(Phase Alpha) Game Engine. This will be a Modern OpenGL(glad version 3.30) based game engine. 

# Frameworks used(for now)
Rendering System:- OpenGL(glad version 3.30)

UI System:- Imgui

Logging System:- spdlog

Texture Loading System:- stbi_image(nothings)

3D Models/Assest Loading and Management System:- Assimp

Window Management System:- glfw

# How to clone and Build
Use "git --recursive" to clone this repository and necessary dependencies. 
After cloning, open the "Premake_Files" under "Engine/3rdPartyLibs/", and copy the .lua files and edit the names to premake.lua for all of the them.
Then run the GenerateProjectFiles_vs2019.bat and run the generated .sln files to open the project on Visual Studio. If you want to generate project files
for other versions of Visual Studio, open the .bat file and replace the "vs2019" with "vs2017" or "vs2022".

If you want to only run the application, go to Engine/binaries/Main run the .exe file. You can even re-build these files from visual studios if you want.

# Distant future Changes
->To try to make the Shaders loader under the Renderer3D serialized for faster loading

->To make the model loader serialized as well

->To make serialized texture loader
