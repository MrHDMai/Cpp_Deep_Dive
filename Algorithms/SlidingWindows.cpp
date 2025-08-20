#include <cstdio>
#include <cstdlib>

// Sliding window maximum using raw pointers + manual deque
void slidingWindowMaximum(const int* inputArray, int totalElements, int windowSize, int* outputArray) {
    if (windowSize <= 0 || windowSize > totalElements) return;

    // Deque will store indices of candidates for maximum
    int* dequeIndices = (int*) std::malloc(sizeof(int) * totalElements);
    int dequeFront = 0;   // points to the front of deque
    int dequeBack  = 0;   // points to the position AFTER the last element (like [front, back) )

    for (int currentIndex = 0; currentIndex < totalElements; ++currentIndex) {
        // 1. Remove indices from the back while current element is larger or equal
        while (dequeFront < dequeBack && inputArray[currentIndex] >= inputArray[dequeIndices[dequeBack - 1]]) {
            --dequeBack;
        }

        // 2. Insert current index at the back
        dequeIndices[dequeBack++] = currentIndex;

        // 3. Remove front index if it is outside the current window
        if (dequeIndices[dequeFront] <= currentIndex - windowSize) {
            ++dequeFront;
        }

        // 4. Once we’ve filled at least one full window, record the maximum
        if (currentIndex >= windowSize - 1) {
            int outputPosition = currentIndex - windowSize + 1;
            outputArray[outputPosition] = inputArray[dequeIndices[dequeFront]];
        }
    }

    std::free(dequeIndices);
}

int main() {
    int totalElements, windowSize;
    std::scanf("%d %d", &totalElements, &windowSize);

    // Allocate input array
    int* inputArray = (int*) std::malloc(sizeof(int) * totalElements);
    for (int i = 0; i < totalElements; ++i) {
        std::scanf("%d", &inputArray[i]);
    }

    // Allocate output array (length = totalElements - windowSize + 1)
    int outputLength = totalElements - windowSize + 1;
    int* outputArray = (int*) std::malloc(sizeof(int) * outputLength);

    slidingWindowMaximum(inputArray, totalElements, windowSize, outputArray);

    // Print results
    for (int i = 0; i < outputLength; ++i) {
        std::printf("%d ", outputArray[i]);
    }
    std::printf("\n");

    std::free(inputArray);
    std::free(outputArray);
    return 0;
}
