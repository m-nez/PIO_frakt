#Testing
All .cpp files in this directory must be tests.  
Build and run the tests by executig `make run` in this directory.  

#Dependencies
[Google Test](https://github.com/google/googletest)

#Setting up Google Test on Ubuntu
`sudo apt-get install libgtest-dev` # Install the headers and source  
`cd /usr/src/gtest` # Go to the source directory  
`sudo cmake -DBUILD_SHARED_LIBS=ON CMakeLists.txt` # Build shared libraries  
`sudo make` # Compile  
`sudo cp *.so /usr/lib` # Copy shared libraries to a directory where the can be found by the linker
