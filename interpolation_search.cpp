#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <algorithm>
#include <ratio>

using namespace std;
using namespace std::chrono;

/**
 * @brief Performs interpolation search on a sorted array to find the target value.
 *
 * Interpolation search is an improved variant of binary search for instances where the keys are uniformly distributed.
 * It estimates the position of the target value based on the value range and the target.
 *
 * @param arr The sorted array in which to search for the target.
 * @param target The value to search for.
 * @return The index of the target if found; otherwise, -1.
 */
int interpolationSearch(const vector<int> &arr, int target)
{
    // Initialize the lower bound to the start of the array
    int low = 0;
    // Initialize the upper bound to the end of the array
    int high = arr.size() - 1;

    // Continue searching while the lower index is less than or equal to the upper index
    // and the target is within the range of the current low and high elements
    while (low <= high && target >= arr[low] && target <= arr[high])
    {
        // If the high and low elements are the same, check if it's the target
        if (arr[high] == arr[low])
        {
            return (arr[low] == target) ? low : -1;
        }

        // Estimate the probable position of the target using the interpolation formula
        int pos = low + (((double)(high - low) / (arr[high] - arr[low])) * (target - arr[low]));
        // Clamp the estimated position to ensure it stays within the bounds of the array
        pos = clamp(pos, low, high);

        // If the element at the estimated position is the target, return its index
        if (arr[pos] == target)
            return pos;
        // If the target is greater, adjust the lower bound to search in the upper sub-array
        else if (arr[pos] < target)
            low = pos + 1;
        // If the target is smaller, adjust the upper bound to search in the lower sub-array
        else
            high = pos - 1;
    }
    // Return -1 if the target is not found in the array
    return -1;
}

/**
 * @brief Generates a sorted array of specified size with random integer values.
 *
 * This function creates a vector of integers with random values, then sorts it in ascending order.
 *
 * @param size The number of elements in the array.
 * @return A sorted vector of integers.
 */
vector<int> generateSortedArray(int size)
{
    // Initialize a vector with the specified size
    vector<int> arr(size);
    // Create a random device to seed the random number generator
    random_device rd;
    // Initialize the Mersenne Twister random number generator
    mt19937 gen(rd());
    // Define a uniform distribution range for the random numbers
    uniform_int_distribution<> dist(1, size * 10);

    // Populate the array with random numbers
    for (int i = 0; i < size; i++)
        arr[i] = dist(gen);
    // Sort the array in ascending order
    sort(arr.begin(), arr.end());
    return arr;
}

/**
 * @brief Tests and displays the performance of the interpolation search algorithm.
 *
 * This function measures the time taken to perform interpolation search on arrays of varying sizes.
 * It outputs the target value, the index where it's found, and the time taken in microseconds and nanoseconds.
 */
void testPerformance()
{
    // Seed the random number generator with the current time
    srand(time(0));
    // Define a list of input sizes to test
    vector<int> inputSizes = {10, 100, 1000, 10000, 100000};
    // Display the header for the performance analysis
    cout << "Performance Analysis:" << endl;
    cout << "|Input Size |   | Microseconds |        | Nanoseconds |" << endl;

    // Iterate over each input size
    for (int size : inputSizes)
    {
        // Generate a sorted array of the current size
        vector<int> arr = generateSortedArray(size);
        // Select a random target element from the array
        int target = arr[rand() % size];

        // Record the starting time of the search
        auto start = high_resolution_clock::now();
        // Perform interpolation search for the target
        int result = interpolationSearch(arr, target);
        // Record the ending time of the search
        auto stop = high_resolution_clock::now();

        // Calculate the duration of the search in microseconds
        auto micro = duration_cast<microseconds>(stop - start);
        // Calculate the duration of the search in nanoseconds
        auto nano = duration_cast<nanoseconds>(stop - start);

        // Display the target value
        cout << size << "\t\t       " << micro.count() << "\t\t       " << nano.count() << endl;
    }
}

/**
 * @brief The main function demonstrating the interpolation search and running performance tests.
 *
 * It first performs an example search on a predefined array, then runs performance tests on arrays of varying sizes.
 *
 * @return Exit status of the program.
 */
int main()
{

    // Example usage of interpolation search
    vector<int> arr = {10, 20, 30, 40, 50};
    int target = 40;
    // Perform interpolation search for the target in the example array
    int result = interpolationSearch(arr, target);
    // Display the result of the example search
    cout << "\n\nExample test:\n\nArray = [10, 20, 30, 40, 50]\nTarget = 40 \nElement found at index: " << result << endl
         << endl;

    // Run the performance tests
    testPerformance();
    return 0;
}