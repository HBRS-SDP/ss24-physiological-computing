#include <gtest/gtest.h>
#include "../src/processing/hilbert_transform.h"
#include <vector>
#include <cmath>

class HilbertTransformTest : public ::testing::Test {
protected:
    void SetUp() override {}

    // Helper function to compare vectors with a tolerance
    void ExpectNearVector(const std::vector<double>& expected, const std::vector<double>& actual, double tolerance) {
        ASSERT_EQ(expected.size(), actual.size());
        for (size_t i = 0; i < expected.size(); ++i) {
            EXPECT_NEAR(expected[i], actual[i], tolerance) << "Vectors differ at index " << i;
        }
    }
};

TEST_F(HilbertTransformTest, ConstructorTest) {
    EXPECT_NO_THROW({
        HilbertTransform ht(100);
    });
}

TEST_F(HilbertTransformTest, ResizeTest) {
    HilbertTransform ht(100);
    EXPECT_NO_THROW({
        ht.resize(200);
    });
}

TEST_F(HilbertTransformTest, ProcessZeroInput) {
    const size_t num_samples = 100;
    HilbertTransform ht(num_samples);
    
    std::vector<double> input(num_samples, 0.0);
    std::vector<double> output(num_samples);
    
    ht.process(input, output);
    
    // Zero input should result in zero output
    std::vector<double> expected(num_samples, 0.0);
    ExpectNearVector(expected, output, 1e-10);
}

TEST_F(HilbertTransformTest, ProcessDifferentSizes) {
    HilbertTransform ht(100);
    
    std::vector<double> input(200, 1.0);
    std::vector<double> output;
    
    EXPECT_NO_THROW({
        ht.process(input, output);
    });
    
    EXPECT_EQ(input.size(), output.size());
}