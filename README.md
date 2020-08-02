# TodoList app

A simple pet-projected i learn C++ with.

## How to build

You need to have Qt5 installed. CMAKE_PREFIX_PATH env variable 
should be set to Qt's installation location.

Just run CMake's "TodoList" target.

### Building on Windows

If you want to build the app in Debug mode - you need to have following
directories in your PATH env variable:
- &lt;Qt install dir>/bin
- &lt;Qt install dir>/plugins/platforms

In Release mode you don't need that since all necessary dependencies 
will be copied into the build directory automatically.

You can compile an NSIS installer for this application:
- you have to have NSIS installed
- NSIS_PATH env variable should be set pointing to the NSIS's installation location
- you have to compile the app in the Release mode

When you compile the app in Release mode with NSIS_PATH env variable set -
the installer will be located in the output subdirectory of CMake's build
directory.

## How to build Android version

Don't waste your time with plain old CMake. 

Import the project into Qt Creator and build it there however you want:
- multiple small apks
- one fat apk
- aab
- debug