#include "Polygons.hpp"
#include <iostream>

Polygon* getHexa(char* name, float radius) {
    return new Hexagon(name, radius);
}

int main() {
    // create an Hexagon, call its perimeter method
    Polygon *hexa = getHexa((char*)"hexa", 1.0);
    std::cout << "Hexa : perimeter = " << hexa->computePerimeter()
              << std::endl << std::endl;

    // memory deallocation
    delete hexa;
}
