#include <exception>
#include <sys/types.h>
#include "generator.h"

Generator::Generator(GeneratorType type): type(type){};

Heightmap Generator::generate(const Vector2<uint>&, const uint&) const{
    throw std::exception(); //not implemented. TODO: add specific exception
}

std::unique_ptr<std::vector<float>> Generator::generate_flat(const uint&, const uint&, const uint&) const {
    // it would be great to just implement this here, but rust cxx bridge won't see it
    // so we have to implement it in each derived class
    throw std::exception(); //not implemented. TODO: add specific exception
}