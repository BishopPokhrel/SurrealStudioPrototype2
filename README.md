# Surreal Studio 

This is a simple prototype, not a final engine. Please follow the procedures to build **Surreal Studio**.

## Prerequisites 

- Windows 11 
- [Microsoft Visual Studio 2022](https://visualstudio.microsoft.com/downloads)
- Dear ImGui
- GLFW & GLAD for OpenGL

**Note:** C++ 20 is required for this project to build. 

---

This project does not use any build system, and requires MSVC and Visual Studio to build. 

## Procedure

- First, clone the GitHub repository. 
```bash
git clone https://github.com/pokhrelbishop-debug/SurrealStudioPrototype2.git
```

- Open the file location in Windows Explorer
- Open the .sln file
- Right click the project -> Properties -> C/C++ -> General -> Additional Include Directories
- Add this in Additonal Include Directories
```bash
$(ProjectDir)\Source
```
- **Note:** If the Additional Include Directories are already set, verify that it contains the above setting.
- Build the solution

**If the Additional Include Directories are set properly (see Procedure) and you have the required libaries, the project should build successfully.**