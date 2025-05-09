// test_boost_example.cpp
#define BOOST_TEST_MODULE BoostTestExample
#include <boost/test/included/unit_test.hpp>
#include <vector>
#include <numeric>

// Function to test
int sum_vector(const std::vector<int>& v) {
    return std::accumulate(v.begin(), v.end(), 0);
}

// Test cases
BOOST_AUTO_TEST_CASE(test_sum_vector) {
    // Test empty vector
    std::vector<int> empty;
    BOOST_TEST(sum_vector(empty) == 0);
    
    // Test normal case
    std::vector<int> numbers{1, 2, 3, 4, 5};
    BOOST_TEST(sum_vector(numbers) == 15);
    
    // Test with negative numbers
    std::vector<int> negatives{-1, -2, 3};
    BOOST_TEST(sum_vector(negatives) == 0);
}

BOOST_AUTO_TEST_CASE(test_failure_example) {
    // This test will fail intentionally to show output
    BOOST_TEST(1 + 1 == 3);
}