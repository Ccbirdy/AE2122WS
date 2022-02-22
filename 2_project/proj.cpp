#include <iostream>
#include <fstream>
#include <vector>


//g++  proj.cpp -o proj

using namespace std;


int main(){
    ifstream openFile("out.ppm");
    char pic;
    while(!openFile.eof()){
        openFile.get(pic);
        cout<< pic;
    }
    openFile.close();


}


