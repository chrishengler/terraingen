#include <exception>
#include "generator.h"

Generator::Generator(unsigned int seed, GeneratorType type): seed(seed), type(type){};

Heightmap Generator::generate(Vector2<int> dimensions){
    throw std::exception(); //not implemented. TODO: add specific exception
}