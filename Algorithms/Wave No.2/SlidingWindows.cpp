#include <cstdio>

#define MAX_WINDOW_SIZE 1023
#define DEQUE_CAPACITY 1024  // Power of two >= MAX_WINDOW_SIZE + 1

void slidingWindowMaximum(const int* inputArray, int totalElements, int windowSize, int* outputArray) {
    if (windowSize <= 0 || windowSize > totalElements) return;
    if (windowSize > MAX_WINDOW_SIZE) return;  // Handle oversized window

    int dequeIndices[DEQUE_CAPACITY];
    int front = 0, back = 0;

    for (int currentIndex = 0; currentIndex < totalElements; ++currentIndex) {
        // Remove from back while current element is greater than or equal to the last deque element
        while (front != back && inputArray[currentIndex] >= inputArray[dequeIndices[(back - 1) & (DEQUE_CAPACITY - 1)]]) {
            back = (back - 1) & (DEQUE_CAPACITY - 1);
        }

        // Add current index to the back
        dequeIndices[back] = currentIndex;
        back = (back + 1) & (DEQUE_CAPACITY - 1);

        // Remove front index if it's outside the current window
        if (front != back && dequeIndices[front] <= currentIndex - windowSize) {
            front = (front + 1) & (DEQUE_CAPACITY - 1);
        }

        // Record the maximum once the first window is filled
        if (currentIndex >= windowSize - 1) {
            outputArray[currentIndex - windowSize + 1] = inputArray[dequeIndices[front]];
        }
    }
}

int main() {
    int totalElements, windowSize;
    std::scanf("%d %d", &totalElements, &windowSize);

    int* inputArray = new int[totalElements];
    for (int i = 0; i < totalElements; ++i) {
        std::scanf("%d", &inputArray[i]);
    }

    int outputLength = totalElements - windowSize + 1;
    int* outputArray = new int[outputLength];

    slidingWindowMaximum(inputArray, totalElements, windowSize, outputArray);

    for (int i = 0; i < outputLength; ++i) {
        std::printf("%d ", outputArray[i]);
    }
    std::printf("\n");

    delete[] inputArray;
    delete[] outputArray;
    return 0;
}