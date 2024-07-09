# [Snake](https://github.com/NemGam/Snake/releases/download/v1.1.0/Snake.zip)
The Snake game recreated with C++ and SDL2

![Snake](https://github.com/NemGam/Snake/assets/56624736/9c2a8aa6-c934-4b44-b85a-ed74a6cf24d8)


# Getting Started (Linux)
## Dependencies
- CMake (version 3.10 or higher recommended)
- C++ Compiler: Compatible with C++17 standard
- SDL2
- SDL2-ttf

## Downloading
### Clone the repository:
	git clone https://github.com/NemGam/Snake.git
### Navigate to the project directory:
	cd Snake

## Building the Project
From the project root directory, generate the build system:

	cmake -S . -B build

Compile and install the project:

    cmake --build build && cmake --install build

### Running the Application
Execute the compiled application:

	./dist/bin/snake
