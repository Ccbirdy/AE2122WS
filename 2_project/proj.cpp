#include <iostream>
#include <fstream>
#include <vector>
#include <memory>

//g++  proj.cpp -o proj

using namespace std;


int main(){
    std::ifstream in( "out.ppm", std::ios::binary);
    std::ofstream out( "output.ppm", std::ios::binary);

    in.seekg(0, std::ios::end);
    auto size = in.tellg();
    in.seekg( 0 );

    std::unique_ptr<char[]> buffer(new char[size]);

    in.read( buffer.get(), size);
    
    out.write( buffer.get(), size);

    in.close();
    out.close();

    return 0;


}


