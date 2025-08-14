#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <chrono>
#include <set>

// Bare-metal DP implementation (O(n*m))
int lcs_bare_metal(const std::string& str1, const std::string& str2) {
    const int m = str1.size();
    const int n = str2.size();
    if (m == 0 || n == 0) return 0;

    int* prev_row = new int[n + 1]();  // Zero-initialized
    int* curr_row = new int[n + 1];
    const char* s1 = str1.data();
    const char* s2 = str2.data();

    for (int i = 0; i < m; ++i) {
        curr_row[0] = 0;
        for (int j = 0; j < n; ++j) {
            curr_row[j + 1] = (s1[i] == s2[j])
                ? prev_row[j] + 1
                : std::max(prev_row[j + 1], curr_row[j]);
        }
        std::swap(prev_row, curr_row);
    }

    int result = prev_row[n];
    delete[] curr_row;
    delete[] prev_row;
    return result;
}

// Hunt-Szymanski algorithm (O(n log n))
int lcs_hunt_szymanski(const std::string& a, const std::string& b) {
    const int m = a.size();
    const int n = b.size();
    if (m == 0 || n == 0) return 0;
    
    // Preprocess positions of characters in b
    std::vector<std::vector<int>> positions(256);
    for (int i = 0; i < n; ++i) {
        positions[static_cast<unsigned char>(b[i])].push_back(i);
    }
    
    std::vector<int> dp;
    dp.reserve(n);
    
    for (char c : a) {
        auto& char_pos = positions[static_cast<unsigned char>(c)];
        // Process in reverse to maintain increasing order in dp
        for (auto it = char_pos.rbegin(); it != char_pos.rend(); ++it) {
            int idx = *it;
            auto pos = std::lower_bound(dp.begin(), dp.end(), idx);
            if (pos == dp.end()) {
                dp.push_back(idx);
            } else {
                *pos = idx;
            }
        }
    }
    return dp.size();
}

// Test function with timing
void run_lcs_tests(const std::string& a, const std::string& b) {
    std::cout << "String lengths: " << a.size() << " and " << b.size() << "\n";
    
    // Test bare-metal DP
    auto start1 = std::chrono::high_resolution_clock::now();
    int result1 = lcs_bare_metal(a, b);
    auto end1 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed1 = end1 - start1;
    
    // Test Hunt-Szymanski
    auto start2 = std::chrono::high_resolution_clock::now();
    int result2 = lcs_hunt_szymanski(a, b);
    auto end2 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed2 = end2 - start2;
    
    std::cout << "\n=== Results ===\n";
    std::cout << "Bare-Metal DP: " << result1 
              << " in " << elapsed1.count() * 1000 << " ms\n";
    std::cout << "Hunt-Szymanski: " << result2 
              << " in " << elapsed2.count() * 1000 << " ms\n";
    std::cout << "Results " << (result1 == result2 ? "AGREE" : "DISAGREE!") << "\n";
    
    // Relative speed comparison
    double ratio = elapsed1.count() / elapsed2.count();
    std::cout << "\nSpeed ratio (DP/HS): " << ratio;
    if (ratio > 1.2) std::cout << " - Hunt-Szymanski faster";
    else if (ratio < 0.8) std::cout << " - DP faster";
    else std::cout << " - Comparable speed";
    std::cout << "\n\n";
}

int main() {
    // Small strings test
    std::cout << "==== Small Strings Test ====\n";
    run_lcs_tests("AGGTAB", "GXTXAYB");
    
    // Medium DNA sequences
    std::cout << "==== Medium DNA Sequences Test ====\n";
    std::string dna1 = "ACCGGTCGAGTGCGCGGAAGCCGGCCGAA";
    std::string dna2 = "GTCGTTCGGAATGCCGTTGCTCTGTAAA";
    run_lcs_tests(dna1, dna2);
    
    // Large sequence test (real-world scale)
    std::cout << "==== Large Sequence Test ====\n";
    std::string large1(50000, 'A');
    std::string large2(50000, 'A');
    for (int i = 0; i < 50000; i += 5) {
        large1[i] = 'C';
        large2[i] = 'G';
    }
    run_lcs_tests(large1, large2);
    
    return 0;
}