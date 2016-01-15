# CppGameEngine3D

My first attempt at writing a from-scratch OpenGL game engine in C++, humbly called the "Bengine." The [Qt GUI Framework](http://www.qt.io/) is used extensively to provide OpenGL Widgets and make up the GUI for the Bengine Editor (learn more about the Bengine Editor [here](#the-editor)). The entire engine was programmed using Test-Driven Development strategies, utilizing the [Google Test Framework](https://github.com/google/googletest) to swiftly implement unit tests (learn more about the Bengine Tests [here](#the-tests)).

## Demo Video

A demonstration of the latest capabilities of the engine and the editor:

[![Engine Demo](http://img.youtube.com/vi/y3qQZIfqHEo/0.jpg)](http://www.youtube.com/watch?v=y3qQZIfqHEo)

## Overview

After transitioning from a Windows to a Macbook, I aborted this C++ version of my game engine for a revamped Java version (see https://github.com/BGR360/JavaGameEngine3D). However, I then discovered that that was a silly decision and have stopped working on the Java version. I have not put any work into this engine for a while and will probably restart from scratch if I want to continue working on it.

## Why do I do this?
When I tell people about this project, I often hear them say, "You know, you could always just download Unity or UDK and use that to make games... Why you gotta go and write your own?" So really, why the hell am I doing this?

I'm not making a game engine so that I can make games. Sure, once it's done, I'll be able to do that if I want, but that's not what it's about. It's about the learning experience and the sense of accomplishment that comes with being able to write something from scratch. Sure, it'll never ever be the most efficient or groundbreaking or innovative game engine, but it'll be mine. I think that's pretty damn cool.

## Acknowledgements

I owe many thanks to Jamie King and Benny Bobaganoosh for their great tutorials and learning resources on C++, OpenGL, and Game Engine programming. These guys do great work and you should check them out.

Jamie King:  [YouTube](https://m.youtube.com/user/1kingja?) -- [Website](http://www.computersciencevideos.com)

Bennybox:  [YouTube](https://m.youtube.com/user/thebennybox?) -- [GitHub](https://github.com/BennyQBD?tab=repositories)

## The Core Engine

The Core engine functionality was written entirely by me in standard C++11.

See Also: [Core Engine Source Code](GameEngine/src)

#### Dynamic DLL

The Engine is implemented as a DLL, which at times led to some annoying problems with DLL-boundaries and memory allocation, but was ultimately meant to make the engine more robust and easy to use.

#### OpenGL

Access to OpenGL function calls was provided by [GLEW (OpenGL Extension Wrangler)](http://glew.sourceforge.net/). A rendering context and surface upon which to render was provided by Qt's `QOpenGLWidget` class. Aside from this, all rendering code in my engine is pure OpenGL function calls, no high-level garbage.

See Also: [Include folder](GameEngine/include)

#### Homemade Math Library

See Also: [Math Library Source Code](GameEngine/src/math)

#### GameObject API

See Also: [GameObject API](GameEngine/src/core/GameObject.h)

#### Rendering

See Also: [Rendering Source Code](GameEngine/src/rendering)

#### Resources

See Also: [Resources Source Code](GameEngine/src/resources)

## The Editor

See Also: [Editor Source Code](GameEngineEditor)

#### Qt Framework

See Also: [Qt Home Page](http://qt.io)

#### Data-Driven Design

See Also: [Example Game and Scene Files](TestGame/res/game)

## The Tests

#### Google Test

See Also: [Google Test Framework](https://github.com/google/googletest)

#### Believing in Test-Driven Development

See Also: [All of the Testing Code](GameEngineTests/src/tests)
