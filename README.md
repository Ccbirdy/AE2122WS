# AE2122WS
#### Chengcheng Guo 183090 <br>
this repository stores my homework and project of Algorithm Engineering ws21/22 <br>
it include 3 parts:
  - :black_nib: [answer](1_answers)  : answers to the Exam Assignments and solutions to some small coding exercises
  - :test_tube: [project](2_project) : Enhancer for Scanned Images
  - :scroll: [paper](3_paper)   : paper about the project


## :bulb: please notice: <br>
1. in [2_project](2_project), there are 3 parts <br>
   - [plain_version](2_project/plain_version) is the version of **code + CMakeLists.txt** 
   - [using_my_lib](2_project/using_my_lib) is the version I try to write a **library**
   - [python_code.ipynb](2_project/python_code.ipynb) is the **python** code 

2. in [3_paper](3_paper), there are 2 pdf files, <br> 
 	:hourglass_flowing_sand: the one with **(light)** is a compressed version of the other one, for easier/fast online preview
  
## :monocle_face: How to use the scanned image enhancer?
0. 
> convert in.jpg -compress none out.ppm 

- If you want to use [plain_version](2_project/plain_version)  <br>
  1. put **out.ppm** in this folder 
  3. mkdir -p build
  4. cmake -DCMAKE_CXX_COMPOLER=g++ -DCMAKE_BUILD_TYPR=Release ..
  5. cmake --build .

- If you want to use [using_my_lib](2_project/using_my_lib) version
  1. mkdir build
  2. cd build
  3. put **out.ppm** in this folder 
  4. cmake ..
  5. make
  6. ./proj


