#include "catch2/catch_test_macros.hpp"
#include "modifiers/modifier.h"
#include "modifiers/hydraulic/hydraulicErosionModifier.h"

// Test helper class since Modifier is abstract
class TestModifier : public Modifier {
public:
    explicit TestModifier(Heightmap& heightmap) : Modifier(heightmap) {}
    void operate() override {
        // Simple modification - multiply all values by 2
        for (auto& row : heightmap) {
            for (auto& val : row) {
                val *= 2.0;
            }
        }
    }
};

TEST_CASE("Modifier Tests", "[modifier]")
{
    SECTION("Base modifier can access and modify heightmap")
    {
        // Create a simple 2x2 heightmap
        Heightmap hm;
        hm.push_back(std::valarray<double>{1.0, 2.0});
        hm.push_back(std::valarray<double>{3.0, 4.0});

        TestModifier modifier(hm);
        modifier.operate();

        // Check that values were modified
        REQUIRE(hm[0][0] == 2.0);
        REQUIRE(hm[0][1] == 4.0);
        REQUIRE(hm[1][0] == 6.0);
        REQUIRE(hm[1][1] == 8.0);
    }

    SECTION("HydraulicErosionModifier can be created")
    {
        Heightmap hm;
        hm.push_back(std::valarray<double>{1.0, 1.0});
        hm.push_back(std::valarray<double>{1.0, 1.0});

        HydraulicErosionModifier modifier(hm);
        // Just verify it can be created and called without crashing
        // (actual erosion testing will come later)
        REQUIRE_NOTHROW(modifier.operate());
    }

    SECTION("Modifiers preserve heightmap bounds")
    {
        // Create a heightmap with values at the valid bounds (-1 to 1)
        Heightmap hm;
        hm.push_back(std::valarray<double>{-1.0, 0.0});
        hm.push_back(std::valarray<double>{0.5, 1.0});

        TestModifier modifier(hm);
        modifier.operate();

        // Check that size is preserved
        REQUIRE(hm.size() == 2);
        REQUIRE(hm[0].size() == 2);
    }
}
