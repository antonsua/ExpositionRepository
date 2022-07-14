@echo off

:: Poner vuestra direccion de destino dentro del proyecto dependencias
echo ---------------------------------------------------
echo Add CMake al proyecto
echo Darle la opcion de directorio "D"
echo ---------------------------------------------------
xcopy ..\cmake-3.17.0-rc1-win64-x64 ..\WeirdEngine\Dependencias\cmake /E

echo ---------------------------------------------------
echo Creando la carpetas "Build" en Ogre y Ois
echo ---------------------------------------------------
MD ..\WeirdEngine\Dependencias\ogre-1.12.5\Build
MD ..\WeirdEngine\Dependencias\OIS\Build

echo ---------------------------------------------------
echo Creando la carpeta "Build" en cegui y cegui/dependencies
echo ---------------------------------------------------
MD ..\WeirdEngine\Dependencias\cegui-0.8.7\dependencies\Build
MD ..\WeirdEngine\Dependencias\cegui-0.8.7\Build

echo ---------------------------------------------------
echo ejecucion del exe de CMake
echo Generar Ogre en su carpeta Build
echo ...
echo Si os da problema al hacer el "generate" - buscar "imgui" desmarcarlo y volver a generar
echo Generar Ois en su carpeta Build (Descargar desde Github/OIS)
echo ...
echo Generar las dependencias de cegui (cegui-0.8.7\dependencies)en la carpeta "cegui-0.8.7\dependencies\Build"
echo DESMARCAR los EFECTOS en las opciones de cmake
echo Para hacer la build de cegui, en las opciones cambiar el directorio de dependencias a "cegui-0.8.7\dependencies\Build"
echo Después, generar cegui en su carpeta Build
echo ---------------------------------------------------
start ..\WeirdEngine\Dependencias\cmake\bin\cmake-gui.exe

PAUSE