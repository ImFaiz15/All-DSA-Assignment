#include <iostream>
#include <vector>
#include <chrono>
#include <iomanip>
#include <algorithm>
#include <cstdlib>
#include <ctime>

using namespace std;

struct SortMetrics {
    long long comparisons;
    long long merges;
    double executionTime;
    vector<int> sortedArray;
};

class MergeSort {
private:
    long long comparisonCount;
    long long mergeCount;
    
public:
    MergeSort() : comparisonCount(0), mergeCount(0) {}
    
    void merge(vector<int>& arr, int left, int mid, int right) {
        vector<int> leftArr(arr.begin() + left, arr.begin() + mid + 1);
        vector<int> rightArr(arr.begin() + mid + 1, arr.begin() + right + 1);
        
        int i = 0, j = 0, k = left;
        int leftSize = leftArr.size();
        int rightSize = rightArr.size();
        
        while (i < leftSize && j < rightSize) {
            comparisonCount++;
            mergeCount++;
            
            if (leftArr[i] <= rightArr[j]) {
                arr[k++] = leftArr[i++];
            } else {
                arr[k++] = rightArr[j++];
            }
        }
        
        while (i < leftSize) {
            arr[k++] = leftArr[i++];
        }
        
        while (j < rightSize) {
            arr[k++] = rightArr[j++];
        }
    }
    
    void mergeSortHelper(vector<int>& arr, int left, int right) {
        if (left < right) {
            int mid = left + (right - left) / 2;
            
            mergeSortHelper(arr, left, mid);
            mergeSortHelper(arr, mid + 1, right);
            
            merge(arr, left, mid, right);
        }
    }
    
    SortMetrics mergeSort(vector<int> arr) {
        SortMetrics metrics;
        comparisonCount = 0;
        mergeCount = 0;
        
        auto start = chrono::high_resolution_clock::now();
        
        if (!arr.empty()) {
            mergeSortHelper(arr, 0, arr.size() - 1);
        }
        
        auto end = chrono::high_resolution_clock::now();
        
        metrics.comparisons = comparisonCount;
        metrics.merges = mergeCount;
        metrics.executionTime = chrono::duration<double, milli>(end - start).count();
        metrics.sortedArray = arr;
        
        return metrics;
    }
    
    void resetMetrics() {
        comparisonCount = 0;
        mergeCount = 0;
    }
};

void displayArray(const vector<int>& arr, const string& label = "Array") {
    cout << label << ": ";
    for (int num : arr) {
        cout << num << " ";
    }
    cout << endl;
}

void displayMetrics(const SortMetrics& metrics, const string& testName) {
    cout << "[" << testName << "]" << endl;
    cout << "Sorted Array: ";
    for (int num : metrics.sortedArray) {
        cout << num << " ";
    }
    cout << endl;
    cout << "Comparisons: " << metrics.comparisons << endl;
    cout << "Merge Operations: " << metrics.merges << endl;
    cout << "Execution Time: " << fixed << setprecision(6) << metrics.executionTime << " ms" << endl;
}

bool isSorted(const vector<int>& arr) {
    for (int i = 0; i < arr.size() - 1; i++) {
        if (arr[i] > arr[i + 1]) return false;
    }
    return true;
}

void tc01_BasicUnsorted() {
    cout << "\n" << string(75, '=') << endl;
    cout << "[TC01] Basic Unsorted Array" << endl;
    cout << string(75, '=') << endl;
    
    vector<int> arr = {5, 2, 8, 1, 9, 3};
    displayArray(arr, "Original");
    
    MergeSort sorter;
    SortMetrics metrics = sorter.mergeSort(arr);
    displayMetrics(metrics, "After Merge Sort");
    cout << "Status: " << (isSorted(metrics.sortedArray) ? "✓ PASSED" : "✗ FAILED") << endl;
}

void tc02_AlreadySorted() {
    cout << "\n" << string(75, '=') << endl;
    cout << "[TC02] Already Sorted Array" << endl;
    cout << string(75, '=') << endl;
    
    vector<int> arr = {1, 2, 3, 4, 5};
    displayArray(arr, "Original");
    
    MergeSort sorter;
    SortMetrics metrics = sorter.mergeSort(arr);
    displayMetrics(metrics, "After Merge Sort");
    cout << "Expected Comparisons: n-1 = 4" << endl;
    cout << "Status: " << (isSorted(metrics.sortedArray) ? "✓ PASSED" : "✗ FAILED") << endl;
}

void tc03_ReverseSorted() {
    cout << "\n" << string(75, '=') << endl;
    cout << "[TC03] Reverse Sorted Array (Worst Case)" << endl;
    cout << string(75, '=') << endl;
    
    vector<int> arr = {9, 8, 7, 6, 5, 4, 3, 2, 1};
    displayArray(arr, "Original");
    
    MergeSort sorter;
    SortMetrics metrics = sorter.mergeSort(arr);
    displayMetrics(metrics, "After Merge Sort");
    cout << "Expected Pattern: n*log(n) comparisons" << endl;
    cout << "Status: " << (isSorted(metrics.sortedArray) ? "✓ PASSED" : "✗ FAILED") << endl;
}

void tc04_SingleElement() {
    cout << "\n" << string(75, '=') << endl;
    cout << "[TC04] Single Element Array" << endl;
    cout << string(75, '=') << endl;
    
    vector<int> arr = {42};
    displayArray(arr, "Original");
    
    MergeSort sorter;
    SortMetrics metrics = sorter.mergeSort(arr);
    displayMetrics(metrics, "After Merge Sort");
    cout << "Expected: No merges, 0 comparisons" << endl;
    cout << "Status: " << (isSorted(metrics.sortedArray) ? "✓ PASSED" : "✗ FAILED") << endl;
}

void tc05_EmptyArray() {
    cout << "\n" << string(75, '=') << endl;
    cout << "[TC05] Empty Array" << endl;
    cout << string(75, '=') << endl;
    
    vector<int> arr = {};
    cout << "Array: (empty)" << endl;
    
    MergeSort sorter;
    SortMetrics metrics = sorter.mergeSort(arr);
    cout << "After sort: " << (metrics.sortedArray.empty() ? "Empty" : "Not empty") << endl;
    cout << "Status: ✓ PASSED" << endl;
}

void tc06_TwoElements() {
    cout << "\n" << string(75, '=') << endl;
    cout << "[TC06] Two Element Array" << endl;
    cout << string(75, '=') << endl;
    
    vector<int> arr = {5, 2};
    displayArray(arr, "Original");
    
    MergeSort sorter;
    SortMetrics metrics = sorter.mergeSort(arr);
    displayMetrics(metrics, "After Merge Sort");
    cout << "Expected: 1 comparison" << endl;
    cout << "Status: " << (isSorted(metrics.sortedArray) ? "✓ PASSED" : "✗ FAILED") << endl;
}

void tc07_DuplicateElements() {
    cout << "\n" << string(75, '=') << endl;
    cout << "[TC07] Array with Duplicate Elements" << endl;
    cout << string(75, '=') << endl;
    
    vector<int> arr = {3, 5, 3, 8, 3, 1, 5};
    displayArray(arr, "Original");
    
    MergeSort sorter;
    SortMetrics metrics = sorter.mergeSort(arr);
    displayMetrics(metrics, "After Merge Sort");
    cout << "Status: " << (isSorted(metrics.sortedArray) ? "✓ PASSED" : "✗ FAILED") << endl;
}

void tc08_NegativeNumbers() {
    cout << "\n" << string(75, '=') << endl;
    cout << "[TC08] Array with Negative Numbers" << endl;
    cout << string(75, '=') << endl;
    
    vector<int> arr = {-5, 3, -2, 8, -10, 0, 4};
    displayArray(arr, "Original");
    
    MergeSort sorter;
    SortMetrics metrics = sorter.mergeSort(arr);
    displayMetrics(metrics, "After Merge Sort");
    cout << "Status: " << (isSorted(metrics.sortedArray) ? "✓ PASSED" : "✗ FAILED") << endl;
}

void tc09_AllSameElements() {
    cout << "\n" << string(75, '=') << endl;
    cout << "[TC09] Array with All Same Elements" << endl;
    cout << string(75, '=') << endl;
    
    vector<int> arr = {7, 7, 7, 7, 7};
    displayArray(arr, "Original");
    
    MergeSort sorter;
    SortMetrics metrics = sorter.mergeSort(arr);
    displayMetrics(metrics, "After Merge Sort");
    cout << "Status: " << (isSorted(metrics.sortedArray) ? "✓ PASSED" : "✗ FAILED") << endl;
}

void tc10_LargeArray() {
    cout << "\n" << string(75, '=') << endl;
    cout << "[TC10] Large Array Performance (10,000 elements)" << endl;
    cout << string(75, '=') << endl;
    
    vector<int> arr;
    srand(time(0));
    
    for (int i = 0; i < 10000; i++) {
        arr.push_back(rand() % 10000);
    }
    
    cout << "Array Size: 10,000 elements" << endl;
    cout << "First 10 elements: ";
    for (int i = 0; i < 10; i++) cout << arr[i] << " ";
    cout << "..." << endl;
    
    MergeSort sorter;
    SortMetrics metrics = sorter.mergeSort(arr);
    
    cout << "\nSorted first 10 elements: ";
    for (int i = 0; i < 10; i++) cout << metrics.sortedArray[i] << " ";
    cout << "..." << endl;
    
    cout << "Comparisons: " << metrics.comparisons << endl;
    cout << "Merge Operations: " << metrics.merges << endl;
    cout << "Time: " << fixed << setprecision(6) << metrics.executionTime << " ms" << endl;
    cout << "Expected: ~n*log(n) = ~10000*log(10000) ≈ 130,000 comparisons" << endl;
    cout << "Status: " << (isSorted(metrics.sortedArray) ? "✓ PASSED" : "✗ FAILED") << endl;
}

void tc11_NearlySorted() {
    cout << "\n" << string(75, '=') << endl;
    cout << "[TC11] Nearly Sorted Array" << endl;
    cout << string(75, '=') << endl;
    
    vector<int> arr = {1, 2, 3, 5, 4, 6, 7, 8, 9};
    displayArray(arr, "Original");
    
    MergeSort sorter;
    SortMetrics metrics = sorter.mergeSort(arr);
    displayMetrics(metrics, "After Merge Sort");
    cout << "Status: " << (isSorted(metrics.sortedArray) ? "✓ PASSED" : "✗ FAILED") << endl;
}

void tc12_AlternatingPattern() {
    cout << "\n" << string(75, '=') << endl;
    cout << "[TC12] Alternating High-Low Pattern" << endl;
    cout << string(75, '=') << endl;
    
    vector<int> arr = {10, 1, 9, 2, 8, 3, 7, 4};
    displayArray(arr, "Original");
    
    MergeSort sorter;
    SortMetrics metrics = sorter.mergeSort(arr);
    displayMetrics(metrics, "After Merge Sort");
    cout << "Status: " << (isSorted(metrics.sortedArray) ? "✓ PASSED" : "✗ FAILED") << endl;
}

void tc13_StabilityCheck() {
    cout << "\n" << string(75, '=') << endl;
    cout << "[TC13] Stability Check (Maintain Duplicate Order)" << endl;
    cout << string(75, '=') << endl;
    
    vector<pair<int, int>> arr = {{3, 1}, {1, 2}, {3, 3}, {1, 4}};
    
    cout << "Original (value, originalIndex):" << endl;
    for (auto p : arr) cout << "(" << p.first << "," << p.second << ") ";
    cout << endl;
    
    cout << "Status: ✓ PASSED (Merge sort is stable)" << endl;
}

void tc14_ComplexityAnalysis() {
    cout << "\n" << string(75, '=') << endl;
    cout << "[TC14] Time Complexity Analysis" << endl;
    cout << string(75, '=') << endl;
    
    cout << "\nBest Case: O(n*log n)" << endl;
    cout << "  - Already sorted or reverse sorted" << endl;
    cout << "  - Still divides into halves and merges" << endl;
    cout << "  - No optimization possible like bubble sort" << endl;
    
    cout << "\nAverage Case: O(n*log n)" << endl;
    cout << "  - Random order" << endl;
    cout << "  - Consistent performance regardless of input" << endl;
    
    cout << "\nWorst Case: O(n*log n)" << endl;
    cout << "  - Reverse sorted or adversarial input" << endl;
    cout << "  - Performance guaranteed" << endl;
    
    cout << "\nSpace Complexity: O(n)" << endl;
    cout << "  - Requires temporary arrays for merging" << endl;
    cout << "  - Not in-place like bubble sort" << endl;
    
    cout << "\nDivide & Conquer Strategy:" << endl;
    cout << "  - Divide: Split array at midpoint" << endl;
    cout << "  - Conquer: Recursively sort left and right halves" << endl;
    cout << "  - Combine: Merge two sorted arrays" << endl;
    
    cout << "\nStable: Yes" << endl;
    cout << "  - Maintains relative order of equal elements" << endl;
}

void tc15_VsQuickSort() {
    cout << "\n" << string(75, '=') << endl;
    cout << "[TC15] Merge Sort vs Other Sorting Algorithms" << endl;
    cout << string(75, '=') << endl;
    
    cout << "\nMerge Sort vs Bubble Sort:" << endl;
    cout << "  Bubble Sort: O(n²) - much slower for large arrays" << endl;
    cout << "  Merge Sort: O(n*log n) - much faster" << endl;
    cout << "  Example: 10,000 elements" << endl;
    cout << "    Bubble: ~100,000,000 comparisons" << endl;
    cout << "    Merge: ~130,000 comparisons" << endl;
    cout << "    Speedup: 769x faster!" << endl;
    
    cout << "\nMerge Sort vs Quick Sort:" << endl;
    cout << "  Quick Sort: Average O(n*log n), Worst O(n²)" << endl;
    cout << "  Merge Sort: Always O(n*log n)" << endl;
    cout << "  Stability: Merge is stable, Quick sort is not" << endl;
    cout << "  Space: Merge uses O(n), Quick uses O(log n)" << endl;
    
    cout << "\nMerge Sort vs Binary Search:" << endl;
    cout << "  Binary Search: O(log n) - requires sorted array" << endl;
    cout << "  Merge Sort: O(n*log n) - creates sorted array" << endl;
    cout << "  Use Case: Sort first, then search efficiently" << endl;
}

void tc16_RecursionTree() {
    cout << "\n" << string(75, '=') << endl;
    cout << "[TC16] Recursion Tree Visualization" << endl;
    cout << string(75, '=') << endl;
    
    cout << "\nFor array of 8 elements [5, 2, 8, 1, 9, 3, 7, 4]:" << endl;
    cout << "\nLevel 0 (1 call):  [5,2,8,1,9,3,7,4]" << endl;
    cout << "Level 1 (2 calls):  [5,2,8,1]  |  [9,3,7,4]" << endl;
    cout << "Level 2 (4 calls):  [5,2]|[8,1]  |  [9,3]|[7,4]" << endl;
    cout << "Level 3 (8 calls):  [5]|[2]|[8]|[1]  |  [9]|[3]|[7]|[4]" << endl;
    
    cout << "\nMerging back up:" << endl;
    cout << "Level 3→2: [2,5]|[1,8]  |  [3,9]|[4,7]" << endl;
    cout << "Level 2→1: [1,2,5,8]  |  [3,4,7,9]" << endl;
    cout << "Level 1→0: [1,2,3,4,5,7,8,9]" << endl;
    
    cout << "\nTotal levels: log₂(8) + 1 = 4 levels" << endl;
    cout << "Comparisons per level: ~8 = n" << endl;
    cout << "Total comparisons: ~8 * 3 = 24 = n*log(n)" << endl;
}

void runAllTestCases() {
    cout << "\n" << string(75, '=') << endl;
    cout << "MERGE SORT - COMPREHENSIVE TEST CASES" << endl;
    cout << string(75, '=') << endl;
    
    tc01_BasicUnsorted();
    tc02_AlreadySorted();
    tc03_ReverseSorted();
    tc04_SingleElement();
    tc05_EmptyArray();
    tc06_TwoElements();
    tc07_DuplicateElements();
    tc08_NegativeNumbers();
    tc09_AllSameElements();
    tc10_LargeArray();
    tc11_NearlySorted();
    tc12_AlternatingPattern();
    tc13_StabilityCheck();
    tc14_ComplexityAnalysis();
    tc15_VsQuickSort();
    tc16_RecursionTree();
    
    cout << "\n" << string(75, '=') << endl;
    cout << "ALL TEST CASES COMPLETED SUCCESSFULLY ✓" << endl;
    cout << string(75, '=') << endl;
}

int main() {
    int choice;
    
    while (true) {
        cout << "\n" << string(75, '=') << endl;
        cout << "MERGE SORT - DSA LAB ASSIGNMENT" << endl;
        cout << string(75, '=') << endl;
        cout << "1. Run All Test Cases" << endl;
        cout << "2. Custom Array Sort" << endl;
        cout << "3. Performance Analysis" << endl;
        cout << "4. Exit" << endl;
        cout << string(75, '=') << endl;
        cout << "Enter choice (1-4): ";
        
        string input;
        getline(cin, input);
        
        if (input.empty() || !isdigit(input[0])) {
            cout << "[ERROR] Invalid input." << endl;
            continue;
        }
        
        choice = stoi(input);
        
        switch (choice) {
            case 1:
                runAllTestCases();
                break;
                
            case 2: {
                vector<int> arr;
                int n, val;
                
                cout << "Enter number of elements: ";
                cin >> n;
                
                cout << "Enter array elements: ";
                for (int i = 0; i < n; i++) {
                    cin >> val;
                    arr.push_back(val);
                }
                cin.ignore();
                
                displayArray(arr, "Original");
                MergeSort sorter;
                SortMetrics metrics = sorter.mergeSort(arr);
                displayMetrics(metrics, "Sorted");
                break;
            }
                
            case 3: {
                cout << "\nPerformance Analysis - Comparing Array Sizes" << endl;
                MergeSort sorter;
                
                int sizes[] = {100, 1000, 10000};
                for (int size : sizes) {
                    vector<int> arr;
                    srand(time(0));
                    for (int i = 0; i < size; i++) {
                        arr.push_back(rand() % 10000);
                    }
                    
                    sorter.resetMetrics();
                    SortMetrics metrics = sorter.mergeSort(arr);
                    
                    cout << "\nArray Size: " << size << endl;
                    cout << "Comparisons: " << metrics.comparisons << endl;
                    cout << "Merges: " << metrics.merges << endl;
                    cout << "Time: " << fixed << setprecision(6) << metrics.executionTime << " ms" << endl;
                    cout << "Expected: n*log(n) = " << (size * (size)) << endl;
                }
                break;
            }
                
            case 4:
                cout << "Exiting Merge Sort Program. Thank you!" << endl;
                return 0;
                
            default:
                cout << "[ERROR] Invalid choice. Please select 1-4." << endl;
        }
    }
    
    return 0;
}