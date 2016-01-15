# CppGameEngine3D

My first attempt at writing a from-scratch OpenGL game engine in C++, humbly called the "Bengine." The [Qt GUI Framework](http://www.qt.io/) is used extensively to provide OpenGL Widgets and make up the GUI for the Bengine Editor (learn more about the Bengine Editor [here](#the-editor)). The entire engine was programmed using Test-Driven Development strategies, utilizing the [Google Test Framework](https://github.com/google/googletest) to swiftly implement unit tests (learn more about the Bengine Tests [here](#the-tests)).

## Demo Video

A demonstration of the latest capabilities of the engine and the editor:

[![Engine Demo](http://img.youtube.com/vi/y3qQZIfqHEo/0.jpg)](http://www.youtube.com/watch?v=y3qQZIfqHEo)

### Jump To:

1. [Overview](#overview)
2. [The Core Engine](#the-core-engine)
  1. [Dynamic DLL](#dynamic-dll)
  2. [OpenGL](#opengl)
  3. [Math Library](#homemade-math-library)
  4. [GameObject API](#gameobject-api)
  5. [Resource Management](#resources)
  6. [Rendering Engine](#rendering)
3. [The Editor](#the-editor)
  1. [Qt Framework](#qt-framework)
  2. [Data-Driven Design](#data-driven-design)
4. [The Tests](#the-tests)
  1. [Google Test](#google-test)
  2. [Believing in Test-Driven Development](#believing-in-test-driven-development)

## Overview

After transitioning from a Windows to a Macbook, I aborted this C++ version of my game engine for a revamped Java version (see https://github.com/BGR360/JavaGameEngine3D). However, I then discovered that that was a silly decision and have stopped working on the Java version. I have not put any work into this engine for a while and will probably restart from scratch if I want to continue working on it.

#### Why do I do this?
When I tell people about this project, I often hear them say, "You know, you could always just download Unity or UDK and use that to make games... Why you gotta go and write your own?" So really, why the hell am I doing this?

I'm not making a game engine so that I can make games. Sure, once it's done, I'll be able to do that if I want, but that's not what it's about. It's about the learning experience and the sense of accomplishment that comes with being able to write something from scratch. Sure, it'll never ever be the most efficient or groundbreaking or innovative game engine, but it'll be mine. I think that's pretty damn cool.

#### Acknowledgements

I owe many thanks to Jamie King and Benny Bobaganoosh for their great tutorials and learning resources on C++, OpenGL, and Game Engine programming. These guys do great work and you should check them out.

Jamie King:  [YouTube](https://m.youtube.com/user/1kingja?) -- [Website](http://www.computersciencevideos.com)

Bennybox:  [YouTube](https://m.youtube.com/user/thebennybox?) -- [GitHub](https://github.com/BennyQBD?tab=repositories)

## The Core Engine

The Core engine functionality was written entirely by me in standard C++11.

**See Also:** [Core Engine Source Code](GameEngine/src)

#### Dynamic DLL

The Engine is implemented as a DLL, which at times led to some annoying problems with DLL-boundaries and memory allocation, but was ultimately meant to make the engine more robust and easy to use.

#### OpenGL

Access to OpenGL function calls was provided by [GLEW (OpenGL Extension Wrangler)](http://glew.sourceforge.net/). A rendering context and surface upon which to render was provided by Qt's `QOpenGLWidget` class. Aside from this, all rendering code in my engine is pure OpenGL function calls, no high-level garbage.

**See Also:** [Include folder](GameEngine/include)

#### Homemade Math Library

One of the most important things required for a 3D game engine is a solid Vector and Matrix math library so that Matrix-Vector transformations in 3D space can be made easily. All of the common Vector and Matrix operations were coded by hand by me. I'm not going to say it was fun.

See Also: [Math Library Source Code](GameEngine/src/math)

#### GameObject API

The overall design of the Bengine external API is the GameObject. The GameObject API that I wrote is *very* similar to the structure of the Unity game engine.

##### Composition over Inheritance

Inheritance and polymorphism is great, but it certainly has its limitations, especially in the game world. For instance, you might define a class of objects that is `Movable` and one that is `Static`, and another class of objects that is `Renderable`. The problem is that a `GameObject` (for instance, a `NonPlayerCharacter`) may be `Movable` *and* `Renderable`. This leads to a diamond-shaped inheritance tree, which is a problem.

```
             GameObject
             /        \
            /          \
      Renderable      Movable
            \          /
             \        /
         NonPlayerCharacter
```

The solution is **Composition**. Instead of using multiple inheritance, a `GameObject` is comprised of multiple `GameComponents` which define its behavior. This leads to a much safer sort of inheritance tree:

```
                GameComponent                                   GameObject
              /               \                                     |
             /                 \                       +------------|-----------+
      PhysicalComponent       RenderableComponent      |   NonPlayerCharacter   |
       /            \                                  +------------------------+
      /              \                                 | - MovableComponent     |
StaticComponent   MovableComponent                     | - RenderableComponent  |
                                                       +------------------------+
```

In the Bengine, every `GameObject` has a list of `GameComponents` which can be dynamically assigned. The GameComponents define the GameObject's behavior at runtime by specifying a custom `update()` function. For example:

```c++
// Create GameObject and add Components
GameObject go;
go.addComponent(new MeshRenderer);
go.addComponent(new PhysicsComponent);

// Get Component and modify properties
MeshRenderer* renderingComp = go.getComponent<MeshRenderer>();
renderingComp.setMesh(aMesh);
renderingComp.setMaterial(aMaterial);
```

##### Parenting GameObjects



**See Also:** [GameObject API](GameEngine/src/core/GameObject.h)

#### Resources

For any game to function well, there needs to be a centralized way to manage the assets (or Resources) in a scene. This is done through the `ResourceManager` class. In hindsight, the design of `ResourceManager` is pretty poor and hardly object-oriented, but it worked.

The `ResourceManager` stores all resource-like object (Images, Textures, Materials, Meshes, Shaders) in maps so that each resource is mapped to a name (a string). To obtain a reference to a resource in-game, call one of the `get()` functions with the name of the resource.

```c++
// Load resources
ResourceManager res;
res.loadMesh("res/meshes/monkey.obj", "monkey");
res.loadShader("res/shaders/basic_shader.vs", "basic_shader");
res.loadTexture("res/textures/bricks.jpg", "bricks", 0);

// Create a material
res.createMaterial("bricks", res.getShader("basic_shader"), res.getTexture("bricks"));

// Create a Monkey GameObject
GameObject monkey;
monkey.addComponent(
    new MeshRenderer(
        res.getMesh("monkey"),
        res.getMaterial("bricks")
    )
);
```

**See Also:** [Resources Source Code](GameEngine/src/resources)

#### Rendering

Designing the Rendering Engine was one of the most difficult parts of the whole project. I really struggled with finding my own way to make a robust object-oriented system. What I ended up with definitely worked but was far from elegant (at least in my eyes).

##### RenderingEngine

The `RenderingEngine` class is responsible for rendering the `Game`'s current `Scene`. Each `Scene` has its own `ResourceManager` and root `GameObject`. The `RenderingEngine` traverses through the `GameObject` tree and calls `render()` on any `GameObjects` which have `RenderingComponents`.

The strange thing is that `RenderingEngine` inherits from Qt's `QOpenGLWidget`. This is what throws off much of the system's object-orientedness. I had to do this because of how Qt works with OpenGL. When using Qt, any calls to OpenGL functions *must* occur within the `QOpenGLWidget`'s `paintGL()` function.

##### MeshRenderer

Any `GameObject` which can be rendered has a `RenderingComponent`. Currently, the only known `RenderingComponent` in the Bengine is the `MeshRenderer`. The `MeshRenderer` stores a pointer to a `Mesh` and a `Material`, which is all that it needs to properly render a mesh (because a Material has a pointer to a `ShaderProgram`).

##### Meshes

A `Mesh` is defined by a set of verices, normals, and UV coordinates. `Meshes` are also *indexed* to help save space. Currently, only `.obj` files can be loaded to create `Meshes`. You can view the new-and-improved obj parsing algorithm [here](GameEngine/src/resources/ObjFile.cpp#L305).

##### Shaders and Uniform Variables

The compilation and loading of GLSL Shaders in the Bengine is done through the `Shader` ([.h](GameEngine/src/rendering/Shader.h) [.cpp](GameEngine/src/rendering/Shader.cpp)) and `ShaderProgram` ([.h](GameEngine/src/rendering/ShaderProgram.h) [.cpp](GameEngine/src/rendering/ShaderProgram.cpp)) classes. Just like in OpenGL, a `ShaderProgram` is comprised of multiple `Shaders` at different stages (the Vertex Shader, Fragment Shader, Geometry Shader, etc.).

The system I created for shader uniform variables, I think, was a good one. The whole `UniformVariable` class ([.h](GameEngine/src/rendering/UniformVariable.h) [.inl](GameEngine/src/rendering/UniformVariable.inl) [.cpp](GameEngine/src/rendering/UniformVariable.cpp)) was templated so that different datatypes could specify how they are `bind()`ed to the shader program.

One really cool thing is that Uniform Variables are **automatically detected** while parsing the GLSL source code. Seriously, [check it out](GameEngine/src/rendering/ShaderProgram.cpp#L153-L219)!

##### Materials

In the Bengine, a `Material` is defined by a `Texture` and a `ShaderProgram` which is used to render it. The creation of `Materials` is done by the `ResourceManager` (see [here](#resources)).

**See Also:** [Rendering Source Code](GameEngine/src/rendering)

## The Editor

**See Also:** [Editor Source Code](GameEngineEditor)

#### Qt Framework

**See Also:** [Qt Home Page](http://qt.io)

#### Data-Driven Design

**See Also:** [Example Game and Scene Files](TestGame/res/game)

## The Tests

#### Google Test

**See Also:** [Google Test Framework](https://github.com/google/googletest)

#### Believing in Test-Driven Development

**See Also:** [All of the Testing Code](GameEngineTests/src/tests)
