#include "catch2/catch_test_macros.hpp"

#include "generator.h"
#include "generatorFactory.h"

TEST_CASE("Generator Factory creates correct generator type")
{
    SECTION("Flat terrain")
    {
        Generator createdGenerator = GeneratorFactory::createGenerator(GeneratorType::FLAT);
        REQUIRE(createdGenerator.getGeneratorType() == GeneratorType::FLAT);
    }

    SECTION("Perlin")
    {
        Generator createdGenerator = GeneratorFactory::createGenerator(GeneratorType::PERLIN);
        REQUIRE(createdGenerator.getGeneratorType() == GeneratorType::PERLIN);
    }
}
