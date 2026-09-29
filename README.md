# LiturgyMake

<p align="center">
  <img src="https://img.shields.io/badge/C%2B%2B-23-00599C?style=for-the-badge&logo=cplusplus&logoColor=white" alt="C++23">
  <img src="https://img.shields.io/badge/CMake-4.3+-064F8C?style=for-the-badge&logo=cmake&logoColor=white" alt="CMake">
  <img src="https://img.shields.io/badge/MSVC-supported-5C2D91?style=for-the-badge&logo=visualstudio&logoColor=white" alt="MSVC">
  <img src="https://img.shields.io/badge/Status-Experimental-orange?style=for-the-badge" alt="Experimental">
  <img src="https://img.shields.io/badge/Vibe--Coded-8A2BE2?style=for-the-badge" alt="Vibe Coded">
</p>

<p align="center">
  <b>A simple C++ project manager powered by LScript.</b>
  <br>
  <sub>Less boilerplate. More C++.</sub>
</p>

<p align="center">
  <a href="#features">Features</a>
  •
  <a href="#lscript">LScript</a>
  •
  <a href="#cli">CLI</a>
  •
  <a href="#roadmap">Roadmap</a>
  •
  <a href="#building">Building</a>
</p>

---

## ⚡ What is LiturgyMake?

**LiturgyMake** is an experimental C++ project manager and build frontend.

It introduces **LScript**, a small configuration language designed to make C++ project configuration simple, readable and fast to write.

Instead of manually maintaining a large `CMakeLists.txt`, you describe your project using a small `liturgy.ls` file.

LiturgyMake generates the required CMake configuration and then uses **CMake + MSBuild** to build the project.

```text
┌─────────────┐
│  liturgy.ls │
└──────┬──────┘
       │
       ▼
┌─────────────┐
│   LScript   │
└──────┬──────┘
       │
       ▼
┌─────────────┐
│ LiturgyMake │
└──────┬──────┘
       │
       ▼
┌─────────────┐
│    CMake    │
└──────┬──────┘
       │
       ▼
┌─────────────┐
│   MSBuild   │
└──────┬──────┘
       │
       ▼
    program.exe
