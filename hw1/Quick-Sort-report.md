# 41125243 
# 41043146

作業二 Quick Sort

## 解題說明

### 問題描述

本題要求使用 Quick Sort 針對指定數量的整數進行排序，並分析其效能。

### 解題策略

1. 使用隨機排列產生器（程式 7.20）產生測試資料。
2. 使用快速排序（Quick Sort）方法進行排序：
   每次選取最後一個元素作為 pivot。
   將小於等於 pivot 的元素移到左邊，大於 pivot 的移到右邊。
   分別對左右子陣列遞迴排序。
3. 在排序過程前後顯示數列內容，確認排序正確性。
4. 使用 chrono 函式庫測量 Quick Sort 執行所需的時間，並輸出效能結果。
## 程式實作

以下為主要程式碼：

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <Windows.h>
#include <Psapi.h>

using namespace std;
using namespace chrono;

// ---------- 記憶體使用測量 ----------
void printMemoryUsage() {
    PROCESS_MEMORY_COUNTERS memInfo;
    GetProcessMemoryInfo(GetCurrentProcess(), &memInfo, sizeof(memInfo));
    cout << "------------------------" << endl;
    cout << "Memory Usage:" << endl;
    cout << "Working Set Size: " << memInfo.WorkingSetSize / 1024 << " KB" << endl;
    cout << "Peak Working Set Size: " << memInfo.PeakWorkingSetSize / 1024 << " KB" << endl;
    cout << "Pagefile Usage: " << memInfo.PagefileUsage / 1024 << " KB" << endl;
    cout << "------------------------" << endl;
}

// ---------- 排列資料產生 ----------
void permute(vector<int>& a) {
    int n = a.size();
    for (int i = n - 1; i >= 1; --i) {
        int j = rand() % (i + 1);
        swap(a[i], a[j]);
    }
}

// ---------- Quick Sort ----------
int medianOfThree(vector<int>& arr, int low, int high) {
    int mid = low + (high - low) / 2;
    if (arr[high] < arr[low]) swap(arr[low], arr[high]);
    if (arr[mid] < arr[low]) swap(arr[mid], arr[low]);
    if (arr[high] < arr[mid]) swap(arr[high], arr[mid]);
    swap(arr[mid], arr[high - 1]);
    return arr[high - 1];
}
int partition(vector<int>& arr, int low, int high) {
    int pivot = medianOfThree(arr, low, high);
    int i = low, j = high - 1;
    while (true) {
        while (arr[++i] < pivot) {}
        while (arr[--j] > pivot) {}
        if (i < j) swap(arr[i], arr[j]); else break;
    }
    swap(arr[i], arr[high - 1]);
    return i;
}
void quick_sort_recursive(vector<int>& arr, int low, int high) {
    if (low + 10 <= high) {
        int pivotIndex = partition(arr, low, high);
        quick_sort_recursive(arr, low, pivotIndex - 1);
        quick_sort_recursive(arr, pivotIndex + 1, high);
    }
    else {
        for (int p = low + 1; p <= high; p++) {
            int tmp = arr[p], j = p;
            while (j > low && arr[j - 1] > tmp) {
                arr[j] = arr[j - 1];
                j--;
            }
            arr[j] = tmp;
        }
    }
}
void quick_sort(vector<int> arr) {
    quick_sort_recursive(arr, 0, arr.size() - 1);
}

// ---------- 主控制區 ----------
int main() {
    srand(time(0));
    int n = 10, trials = 30;

    vector<int> arr(n), best_input(n), temp(n);
    double total_time = 0, max_time = 0;

    // 測試時間精度
    auto start = high_resolution_clock::now();
    auto end = high_resolution_clock::now();
    double duration = duration_cast<nanoseconds>(end - start).count();
    cout << "Timer: " << duration << " ns" << endl;

    // Average + Worst-case 測試（同一批資料）
    for (int t = 0; t < trials; t++) {
        for (int i = 0; i < n; i++) arr[i] = i;
        permute(arr);
        vector<int> test = arr;

        start = high_resolution_clock::now();
        if (sort_method == "insertion") insertion_sort(test);
        else if (sort_method == "merge") merge_sort(test);
        else if (sort_method == "heap") heap_sort(test);
        else if (sort_method == "quick") quick_sort(test);
        else if (sort_method == "composite") composite_sort(test);
        end = high_resolution_clock::now();

        duration = duration_cast<microseconds>(end - start).count();
        total_time += duration;
        if (duration > max_time) {
            max_time = duration;
            best_input = arr;
        }
    }

    cout << "Average time: " << total_time / trials << " microseconds" << endl;
    cout << "Worst-case time (within average): " << max_time << " microseconds" << endl;

    printMemoryUsage();
    return 0;
}

```

## 效能分析

1. 時間複雜度：最佳情況 $O(nlogn)$、最壞情況 $O(n^2)$、平均情況 $O(nlogn)$
2. 空間複雜度：空間複雜度為 $O(logn)$ ~ $O(n)$。

## 測試與驗證

### 平均情況測試案例

執行30次排序再把所有時間取平均值。
使用 Permute() 函式

| 測試案例 | 輸入參數 $n$ | Timer 精度（δ) | 排序執行時間 |
|----------|--------------|--------------|-------------|
| 測試一   | $n = 500$    | 100ns        | 71ms        |
| 測試二   | $n = 1000$   | 100ns        | 154ms       |
| 測試三   | $n = 2000$   | 100ns        | 321ms       |
| 測試四   | $n = 3000$   | 100ns        | 469ms       |
| 測試五   | $n = 4000$   | 100ns        | 726ms       | 
| 測試六   | $n = 5000$   | 100ns        | 848ms       | 

### 最壞情況測試案例

每個資料筆數都執行30次找排序時間最長的一次來估計最壞情況時間。
用平均情況測試同一筆資料來找執行最久的來當作最壞情況測試時間。
使用 Permute() 函式

| 測試案例 | 輸入參數 $n$ | Timer 精度（δ) | 排序執行時間 |
|----------|--------------|--------------|-------------|
| 測試一   | $n = 500$    | 100ns        | 124ms       |
| 測試二   | $n = 1000$   | 100ns        | 218ms       |
| 測試三   | $n = 2000$   | 100ns        | 562ms       |
| 測試四   | $n = 3000$   | 200ns        | 589ms       |
| 測試五   | $n = 4000$   | 100ns        | 857ms       | 
| 測試六   | $n = 5000$   | 100ns        | 1127ms      | 

### 圖表（x 軸為 n，y 軸為時間）

![image](https://github.com/user-attachments/assets/816ac6b1-d72a-4a33-902c-8615724ec0a0)

### 編譯與執行指令

```shell
g++ quicksort.cpp -o quicksort
./quicksort
```

### 結論

1. Quick Sort 能有效率地將亂序的整數數列進行排序。
2. 使用遞迴及分割策略，使得大部分情況下排序時間接近 O(n log n)。
3. 透過 chrono 測量顯示，排序的時間隨著資料量大小變化，但在小型資料下仍能快速完成。

## 申論及開發報告

### 使用 Quick Sort 的理由：

1. Quick Sort 平均時間複雜度為 O(n log n)，在實際應用中表現優異。
2. 實作簡單，且能直接就地排序（in-place），不需額外大量記憶體空間。
3. 對隨機排列的資料（本題使用 Permute 隨機排列）排序效果特別好，符合本題要求。


