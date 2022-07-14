# Mad_Diggers

## Libraries

Made in C++ using SDL framework (and SDL modules).
In order to use the solution (and compile) you need to extract the zip **"SDL_package.zip"**.
It includes the required external dependences and binary files.

## Solution Errors

We may not use the same ***VS*** or same ***OS*** so if you encounter any error:

* **Windows SDK** version related (missing, etc)
* **Platform toolset** related (missing, etc)

Just right click `HolaSDL solution` **->** `properties`

* Choose your **Windows SDK** version
* hoose your **Platform toolset**

> Some errors may be caused by older version

## Gitignore

[.gitignore](.gitignore) file ignores:

* All directories `bin`, `debug`, `release`, `obj`, `ipch`...
* All files .`suo`, .`user`, .`ncb`, .`sbr`, .`log`...

```
# Libraries
SDL2_image-2.0.1/
SDL2_mixer-2.0.2/
SDL2_net-2.0.1/
SDL2_ttf-2.0.14/
SDL2-2.0.7/


# Generated data
bin/
.vs/

ipch/
obj/

Debug/
debug/
Release/
release/

*.suo
*.user
*.ncb
*.sbr

*.log
*.*log

```
