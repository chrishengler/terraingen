#include <exception>
#include "generator.h"

Generator::Generator(unsigned int seed, GeneratorType type): seed(seed), type(type){};

Heightmap Generator::generate(unsigned int size_x, unsigned int size_y){
    throw std::exception(); //not implemented. TODO: add specific exception
}