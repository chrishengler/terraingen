#include "catch2/catch_test_macros.hpp"
#include "modifiers/hydraulic/hydraulicErosionModifier.h"


TEST_CASE("Modifier Tests", "[modifier]")
{
    SECTION("HydraulicErosionModifier can be created")
    {
        Heightmap hm;
        hm.push_back(std::valarray<double>{1.0, 1.0});
        hm.push_back(std::valarray<double>{1.0, 1.0});

        tg::modify::HydraulicErosionModifier modifier(hm);
        // Just verify it can be created and called without crashing
        // (actual erosion testing will come later)
        REQUIRE_NOTHROW(modifier.operate());
    }
}
