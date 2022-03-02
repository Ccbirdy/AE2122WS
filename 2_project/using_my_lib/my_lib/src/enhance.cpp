#include "enhance.h"

int to_gray(int red, int green, int blue){
    return int(0.2989 * red + 0.5870 * green + 0.1140 * blue);
}