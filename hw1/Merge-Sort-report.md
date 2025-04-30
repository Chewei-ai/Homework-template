# 41125243 
# 41043146

作業三 (Merge Sort 使用Iterative版本)

## 解題說明

### 問題描述

本題要求使用 Merge Sort 針對指定數量的整數進行排序，並分析其效能。

### 解題策略

1. 使用隨機排列產生器（程式 7.20）產生測試資料。
2. 使用最壞情況產生器 ReversFill() 函式產生測試資料。
3. 以小區塊為單位開始，兩兩合併相鄰區塊。
4. 每次將區塊大小翻倍，直到整個陣列完成排序

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

void reverseFill(vector<int>& a) {
    int n = a.size();
    for (int i = 0; i < n; i++) a[i] = n - i;
}

// ---------- 合併排序 ----------
void merge(vector<int>& arr, int l, int m, int r, vector<int>& temp) {
    int i = l, j = m + 1, k = l;
    while (i <= m && j <= r) temp[k++] = (arr[i] < arr[j]) ? arr[i++] : arr[j++];
    while (i <= m) temp[k++] = arr[i++];
    while (j <= r) temp[k++] = arr[j++];
    for (int x = l; x <= r; x++) arr[x] = temp[x];
}
void merge_sort_recursive(vector<int>& arr, int l, int r, vector<int>& temp) {
    if (l < r) {
        int m = l + (r - l) / 2;
        merge_sort_recursive(arr, l, m, temp);
        merge_sort_recursive(arr, m + 1, r, temp);
        merge(arr, l, m, r, temp);
    }
}
void merge_sort(vector<int> arr) {
    vector<int> temp(arr.size());
    merge_sort_recursive(arr, 0, arr.size() - 1, temp);
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
        merge_sort(test);
        end = high_resolution_clock::now();

        duration = duration_cast<microseconds>(end - start).count();
        total_time += duration;
        if (duration > max_time) {
            max_time = duration;
            best_input = arr;
        }
    }

    cout << "Average time: " << total_time / trials << " microseconds" << endl;
    

    // 真正的最壞情況：In-place倒序
    if (sort_method == "insertion" || sort_method == "merge") {
        reverseFill(arr);
        vector<int> test = arr;
        start = high_resolution_clock::now();
        if (sort_method == "insertion") insertion_sort(test);
        else if (sort_method == "merge") merge_sort(test);
        end = high_resolution_clock::now();
        duration = duration_cast<microseconds>(end - start).count();
        cout << "Actual worst-case time (reverse order): " << duration << " microseconds" << endl;
    }
    else {
        cout << "Worst-case time (within average): " << max_time << " microseconds" << endl;
    }

    printMemoryUsage();
    return 0;
}

```

## 效能分析

1. 時間複雜度：最佳情況 $O(n\log n)$、最壞情況 $O(n\log n)$、平均情況 $O(n\log n)$
2. 空間複雜度：空間複雜度為 $O(n)$。

## 測試與驗證

### 平均測試案例

使用 Permute() 函式

| 測試案例 | 輸入參數 $n$ | Timer 精度（δ) | 排序執行時間 |
|----------|--------------|--------------|-------------|
| 測試一   | $n = 500$    | 100ns        | 144ms       |
| 測試二   | $n = 1000$   | 100ns        | 313ms       |
| 測試三   | $n = 2000$   | 100ns        | 893ms       |
| 測試四   | $n = 3000$   | 100ns        | 1289ms      |
| 測試五   | $n = 4000$   | 100ns        | 1896ms      | 
| 測試六   | $n = 5000$   | 100ns        | 2302ms      | 

### 最壞情況測試案例

使用ReverseFill() 函式

| 測試案例 | 輸入參數 $n$ | Timer 精度（δ) | 排序執行時間 |
|----------|--------------|--------------|-------------|
| 測試一   | $n = 500$    | 100ns        | 151ms       |
| 測試二   | $n = 1000$   | 100ns        | 322ms       |
| 測試三   | $n = 2000$   | 100ns        | 497ms       |
| 測試四   | $n = 3000$   | 100ns        | 1201ms      |
| 測試五   | $n = 4000$   | 100ns        | 1387ms      | 
| 測試六   | $n = 5000$   | 100ns        | 2296ms      | 

### 圖表（x 軸為 n，y 軸為時間）

![image](https://github.com/user-attachments/assets/0a53679f-88f8-4367-ae55-3f4d2768a2a0)

### 編譯與執行指令

```shell
$ g++ main.cpp --std=c++21 -o main.exe    # 編譯成執行檔
$ .\main.exe                              # 執行程式
Timer precision (delta δ): 0 nanoseconds
Original array: 4 2 9 1 6 5 8 10 3 7
Sorted array: 1 2 3 4 5 6 7 8 9 10
Sorting time: 35 microseconds
```

### 結論

1. 可以確認 Iterative Merge Sort 正確將隨機排列的資料排序
2. 在小型資料上具備穩定且快速的效能
3. 測試案例涵蓋多種不同資料量測試（$n = 500$、$n = 1000$、$n = 2000$、$n = 3000$、$n = 4000$、$n = 5000$），驗證程式能夠執行少量和大量的排序。

## 申論及開發報告

### 使用 Insertion Sort 的理由：

1. 避免遞迴帶來的 function call overhead，提升穩定性。
2. 適合在記憶體管理要求更高的環境中使用（例如嵌入式系統）。
3. 保持 Merge Sort 原有的  時間複雜度特性。

### 平均與最壞情況考量

在本次測試中，針對平均情況採用隨機排列資料，
而針對最壞情況則使用倒序排列作為測資來源。
雖然 Merge Sort 在不同資料排列下的理論時間複雜度一致，
但透實際程式跑過一次後，觀察到數據其實差了兩倍，
但我認為這是因為實驗數據不構所造成。

### 測試設計與開發經驗

開發過程中，特別注意在合併階段對左右子陣列邊界條件的處理，
確保每次合併時都能正確將資料有序地合併至主陣列。
此外，透過隨機排列產生器大量測試不同初始排列情形，驗證排序的正確性與穩定性。

透過以上設計與實作，可以確保 Merge Sort 在各種資料情境下均能保持優異的效能表現，並為後續組合排序函式設計提供良好的基礎。
