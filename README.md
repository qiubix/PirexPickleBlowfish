PirexPickleBlowfish
===================
Description
-----------

Permission to land.

Dependencies
------------

* gmock:
https://code.google.com/p/googlemock/

* Qt5 (tested with Qt5.1.1):
http://qt-project.org/

* CMake (minimum 2.8.8):
http://www.cmake.org/

//REVIEW: have you tested it on Windows?
Preparing environment
---------------------

* Install all dependencies. 
* Add directory, where gmock source files have been extracted as `GMOCK_ROOT` to your environment variables.  
* Add path to Qt5 cmake files to `CMAKE_PREFIX_PATH`, for example add this to your ~/.bashrc file:
`export CMAKE_PREFIX_PATH=$CMAKE_PREFIX_PATH:$HOME/Qt5.1.1/5.1.1/gcc_64/lib/cmake`
* If you installed Qt5 library in a non-standard location (other than system's default /usr/lib/), create **qt5.1.conf** file in **/etc/ld.so.conf/** and put a single line there:
`[your_qt5_installation_directory]/lib`. 

For example, for home directory installation of x64 version of library:
`/home/[your_user_name]/Qt5.1.1/5.1.1/gcc_64/lib`

//REVIEW: when I run GuiTest or PirexPickleBlowfish from bin directory i get:
//./GuiTest: error while loading shared libraries: libQt5Test.so.5: cannot open shared object file: No such file or directory
//so there is some problem with linking Qt Libraries
Building and installing
-----------------------

Prepare 'build' directory and create makefiles:

`mkdir build && cd build && cmake ..`

Build project (from the 'build' directory):

`make`

Install project (will be installed to 'bin' directory):

`make install`

