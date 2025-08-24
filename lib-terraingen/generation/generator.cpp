#include <exception>
#include "generator.h"

Generator::Generator(unsigned int seed, GeneratorType type): seed(seed), type(type){};

Heightmap Generator::generate(const Vec2i &dimensions){
    throw std::exception(); //not implemented. TODO: add specific exception
}

std::unique_ptr<Heightmap> Generator::generate_as_unique_ptr(const Vec2i &dimensions) {
    // it would be great to just implement this here, but rust cxx bridge won't see it
    // so we have to implement it in each derived class
    throw std::exception(); //not implemented. TODO: add specific exception
}