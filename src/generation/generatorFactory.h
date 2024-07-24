#include "generator.h"
#include "generatorTypes.h"

class GeneratorFactory{
    Generator createGenerator(GeneratorType type);
};