# iVoxely

Voxel-based game in C++ and OpenGL.

### Compilation instructions

Before attempting to compile and run, please make sure you have the required dependencies installed (see below). Once you have satisfied those requirements, then you should be able to compile it. I'm building this using the Clang/LLVM 3.2 compiler because it has a number of significant advantages over GCC. If you'd to do the same, be sure that Clang 3.2 is installed (see below). Then navigate to the Source directory and run "./ClangCompileRun.sh" to point some environmental variables to Clang, compile the code, and then execute the application. If you prefer GCC, run "./compileRun.sh" which will use GCC and then execute the application. The CMakeClean.sh script will remove all build files, producing a clean compilation environment, which is especially useful when preparing to push to git.

##### Dependencies and prerequisites

This project uses C++11, Glew, Freeglut, GLM, and cmake. This C++11 code relies on the GLEW and Freeglut libraries to create the window, OpenGL for rendering, the GLM library for OpenGL mathematics, and cmake for generating platform-independent compilation instructions (such as makefiles). The build-essential package is needed for linking cmake to the compiler. If you do not have Glew, Freeglut, GLM, cmake, or build-essential installed, these libraries can be installed from the Mint/Ubuntu repos with the following command:

sudo apt-get install libglew-dev freeglut3-dev libglm-dev cmake build-essential

##### Clang/LLVM

I build this code using the Clang/LLVM 3.2 compiler. There are many ways to install Clang 3.2, but the following method should work in Linux Mint 14 or Ubuntu Quantal Quetzal:

sudo add-apt-repository ppa:kxstudio-team/builds<br>
sudo apt-get update<br>
sudo apt-get install clang<br>

Be sure to run the ./initClang.sh executable as described above.

### Origin

This project is based on the framework developed in the https://github.com/Jesse-V/CS5400_Final_Project repo from which https://github.com/Jesse-V/OpenGL_Texture_Mapping was based.
