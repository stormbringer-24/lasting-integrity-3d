# Lasting Integrity — 3D OpenGL Rendering Engine

A 3D graphics rendering application developed in C++ using modern OpenGL (version 4.1 core profile). The project features dynamic camera management, custom GLSL shader compilation pipelines, lighting models, and procedural 3D mesh rendering.

Inspired by the ethereal landscape of *Shadesmar* and the iconic fortress of *Lasting Integrity*.

---

## Tech Stack & Dependencies

* **Language:** C++17
* **Graphics API:** OpenGL 4.1 Core Profile
* **Windowing & Context:** GLFW 3
* **Extension Wrangler:** GLEW 2.3[cite: 1]
* **Mathematics:** GLM (OpenGL Mathematics)
* **Target Platform:** macOS (Apple Silicon )

---

## Key Features

* **Custom Shader Pipeline:** Modular `Shader` class capable of reading, compiling, linking, and error-checking Vertex and Fragment shaders dynamically at runtime.
* **3D Transformation Pipeline:** Full implementation of Model, View, and Projection (MVP) matrices using GLM for perspective projection and camera movement.
* **Real-time Rendering & Lighting:** Dynamic uniform updates passing time parameters (`u_time`) and camera positions (`viewPos`) to shaders for animated lighting effects.
* **Optimized Buffer Management:** Manual management of Vertex Array Objects (VAO), Vertex Buffer Objects (VBO), and attribute pointers for efficient GPU data transfer.

---

## 📁 Project Structure

LastingIntegrity/
├── src/
│   └── main.cpp              # Application entry point & render loop
├── shaders/
│   ├── vertex_shader.glsl    # Core vertex transformations
│   ├── fragment_shader.glsl  # Surface shading & color calculations
│   ├── tower_vertex.glsl     # Specific transformations for tower meshes
│   └── tower_fragment.glsl   # Tower material & lighting properties
└── README.md


---

## Building & Running (macOS)

### Prerequisites
Ensure you have Homebrew installed along with the required graphics libraries:


brew install glfw glew glm

### Build via Terminal
Compile the project using `clang++` (linking GLFW, GLEW, and macOS native frameworks):


clang++ -std=c++17 src/main.cpp -o LastingIntegrity \
  -I/opt/homebrew/opt/glew/include \
  -I/opt/homebrew/opt/glfw/include \
  -L/opt/homebrew/opt/glew/lib -lGLEW \
  -L/opt/homebrew/opt/glfw/lib -lglfw \
  -framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo


### Run

./LastingIntegrity


---

## Preview
<h1 align="center">Lasting Integrity</h1>
<p align="center">3D OpenGL rendering engine in C++17</p>

<p align="center">
  <img src="https://img.shields.io/badge/C%2B%2B-17-blue?logo=cplusplus" />
  <img src="https://img.shields.io/badge/OpenGL-4.1_Core-5586A4?logo=opengl" />
  <img src="https://img.shields.io/badge/platform-macOS_(Apple_Silicon)-lightgrey?logo=apple" />
</p>

<p align="center">
  <img src="docs/preview.gif" alt="Preview" width="720" />
</p>

A 3D graphics application built with modern OpenGL 4.1 (core profile). It features a free camera, a custom GLSL shader pipeline, lighting, and procedural mesh rendering.

Inspired by the ethereal landscape of *Shadesmar* and the fortress of *Lasting Integrity*.

## Features

- **Custom shader pipeline:** a `Shader` class that reads, compiles, links, and error-checks vertex and fragment shaders at runtime.
- **MVP transformations:** Model/View/Projection matrices with GLM, perspective projection, camera movement.
- **Animated lighting:** `u_time` and `viewPos` uniforms updated every frame.
- **Manual buffer management:** VAO/VBO setup and attribute pointers.

## Tech Stack

| | |
|---|---|
| Language | C++17 |
| Graphics API | OpenGL 4.1 Core |
| Window/context | GLFW 3 |
| Extension loader | GLEW 2.3 |
| Math | GLM |
| Platform | macOS (Apple Silicon) |

## Project Structure

```text
LastingIntegrity/
├── src/
│   └── main.cpp              # Entry point & render loop
├── shaders/
│   ├── vertex_shader.glsl
│   ├── fragment_shader.glsl
│   ├── tower_vertex.glsl
│   └── tower_fragment.glsl
└── README.md
```

## Build & Run

**Prerequisites:** [Homebrew](https://brew.sh), then:

```bash
brew install glfw glew glm
```

**Build:**

```bash
clang++ -std=c++17 src/main.cpp -o LastingIntegrity \
  -I/opt/homebrew/opt/glew/include \
  -I/opt/homebrew/opt/glfw/include \
  -L/opt/homebrew/opt/glew/lib -lGLEW \
  -L/opt/homebrew/opt/glfw/lib -lglfw \
  -framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo
```

**Run** (from the project root, so the shaders are found):

```bash
./LastingIntegrity
```


