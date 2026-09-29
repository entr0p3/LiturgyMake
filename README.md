# LiturgyMake

> A small C++ project manager and build frontend powered by LScript.

LiturgyMake is an experimental C++ build/project management tool written in C++.

The idea is simple: keep CMake underneath, but provide a much simpler project description language and CLI on top of it.

Instead of writing and maintaining a large `CMakeLists.txt`, a project can be described using a small LScript configuration file.

## Why?

CMake is powerful, but its syntax can become unnecessarily complicated for small and medium-sized C++ projects.

LiturgyMake is an experiment to see how far a simpler developer experience can go.

The project is also being built as a **vibe-coded / experimental project** — features are designed, implemented, tested and improved along the way rather than following a fixed specification.

The goal is not to replace CMake overnight.

The goal is to build something better step by step.

---

## LScript

LiturgyMake uses its own small configuration language called **LScript**.

Example:

```lscript
using LScript

app "LiturgyTest"

cpp 23

src "src"
include "include"

define DEBUG
define MY_PROJECT

link user32
link d3d11
