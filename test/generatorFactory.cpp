#include "catch2/catch_test_macros.hpp"

#include "generator.h"
#include "generatorFactory.h"

TEST_CASE("Generator Factory creates correct generator type")
{
    unsigned int seed = 42;
    Vector2<int> cell_sizes(16, 16);

    SECTION("Flat terrain")
    {
        auto createdGenerator = GeneratorFactory::createGenerator(seed, GeneratorType::FLAT, cell_sizes);
        REQUIRE(createdGenerator->getGeneratorType() == GeneratorType::FLAT);
    }

    SECTION("Perlin")
    {
        auto createdGenerator = GeneratorFactory::createGenerator(seed, GeneratorType::PERLIN, cell_sizes);
        REQUIRE(createdGenerator->getGeneratorType() == GeneratorType::PERLIN);
    }

    SECTION("Diamond Square")
    {
        auto createdGenerator = GeneratorFactory::createGenerator(seed, GeneratorType::DIAMOND_SQUARE, cell_sizes);
        REQUIRE(createdGenerator->getGeneratorType() == GeneratorType::DIAMOND_SQUARE);
    }
}
