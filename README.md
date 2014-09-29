PirexPickleBlowfish
===================
Description
-----------

Permission to land.

Dependencies
------------

* svn (for gmock https://code.google.com/p/googlemock/)
http://subversion.apache.org/

* Qt5 (tested with Qt5.1.1):
http://qt-project.org/

* CMake (minimum 2.8.8):
http://www.cmake.org/

Preparing environment
---------------------

* Install all dependencies.
* Add path to Qt5 cmake files to `CMAKE_PREFIX_PATH`, for example add this to your ~/.bashrc file:
`export CMAKE_PREFIX_PATH=$CMAKE_PREFIX_PATH:$HOME/Qt5.1.1/5.1.1/gcc_64/lib/cmake`
* If you installed Qt5 library in a non-standard location (other than system's default /usr/lib/), create **qt5.1.conf** file in **/etc/ld.so.conf/** and put a single line there:
`[your_qt5_installation_directory]/lib`. 

For example, for home directory installation of x64 version of library:
`/home/[your_user_name]/Qt5.1.1/5.1.1/gcc_64/lib`

Then you need to run `ldconfig` to build the library cache. 


Building and installing
-----------------------

Prepare 'build' directory and create makefiles:

`mkdir build && cd build && cmake ..`

Build project (from the 'build' directory):

`make`

Install project (will be installed to 'bin' directory):

`make install`

Test project

`make test`

Running project
---------------

By default project is installed in PROJECT_DIRECTORY/bin. Main executable is `PirexPickleBlowfish`. You can also run all tests by executing `AllTests` program, or choose specific test for particular component. 


Building and running on MS Windows
==================================

Building project on Windows requires basically same dependencies and actions as on Linux systems. 

Additional dependencies
-----------------------

In order to build project on MS Windows, you need to install MinGw (http://www.mingw.org/) and add it's bin directory to your $PATH environment variable. You may also try to use different C++ compiler toolchain, but the project was tested only for this one. Remember to install boost libraries using this toolchain. Change to boost directory and run: 

`bootstrap.bat mingw`

and then 

`b2 toolset=gcc`

Building project
----------------
The easiest way to build it is to use cmake gui program, that comes with default cmake package. After specifying project directory, set some variables by choosing "Add entry" option and setting PATH as type. 

* CMAKE_PREFIX_PATH - set to your Qt5 installation, for example: C:/Qt/5.1.1/msvc2012_64_opengl

* CMAKE_INSTALL_PREFIX - set installation directory. Recommended way is to create bin directory inside project folder. 

* G - set type to string and value to "MinGW Makefiles"

After setting variables run Configure and then Generate.
When asked to choose generator, use MinGW (or another one of your choice, installed on your machine). 

To build project, open command line and go to build directory of your project. Then run `mingw32-make.exe` 