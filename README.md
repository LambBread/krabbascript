# Krabbascript 1.3.3-prototype
Krabbascript is a statically typed, AOT compiled, high level programming language designed to be easy to write and read.

> [!CAUTION]
> This project is still in its early stages, so expect a lot of unfinished stuff. Check-out our [Discord](https://discord.gg/MQT4YgEYvn) for news and progress on Krabbascript!

Krabbascript mixes C, Lua, and Python together to form simple, and easy to learn syntax.

# Getting started
## Prerequisites

### Git (optional)
Git is for cloning Krabbascript's source code.
You can check if Git is installed with
```git --version```

### Make
To build Krabbascript, you got to use GNU Make or a compatible tool.

### C compiler
Krabbascript is written in C, and requires a C compiler do build. I genuinely recommend that you use gcc to build the compiler, because its set as default in the Makefile. If you cant use gcc for some reason, you can edit CC variable to the compiler you want in the Makefile.

### Building Krabbascript
```make && sudo make install```
This creates the final binary in the project's directory and copies the compiler to /usr/bin/kscript.