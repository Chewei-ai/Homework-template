# 41125243 
# 41043146

作業五 (Composite Sort)

## 解題說明

### 問題描述

本題要求使用 Composite Sort 針對指定數量的整數進行排序，結合過去四種排序資料最快的區間做優化，整合出一個最快排序的排序方法。

### 解題策略

1. 小資料（n ≤ 32）：
   使用 Insertion Sort，其在小筆資料下比其他演算法更快，且具有原地排序的記憶體優勢。

2. 已排序資料：
   使用 is_sorted() 檢查，若資料本身已排序，則直接跳過不進行排序，可節省排序成本。

3. 中～大筆資料：
   先以「三數取中法」取得 pivot，並統計該 pivot 的切分分布是否嚴重失衡（pivot 左右分布差異大）。
   若發現切分極端（如 95% 元素集中於一側），判定 Quick Sort 容易退化，則轉用 Merge Sort 作為保底手段。
   否則採用改良版 Quick Sort 進行排序。
   
4. 使用隨機排列產生器（程式 7.20）產生測試資料。

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

// ---------- 綜合排序 (Composite Sort) ----------
void composite_sort(vector<int> arr) {
    int n = arr.size();
    if (n <= 32) {
        insertion_sort(arr);
        return;
    }
    if (is_sorted(arr.begin(), arr.end())) {
        return;
    }

    // 使用 pivot 拿來判斷分布好壞（是否有極度不平均的情況）
    int low = 0, high = n - 1;
    int mid = low + (high - low) / 2;
    int a = arr[low], b = arr[mid], c = arr[high];
    int pivot;
    if (a > b) swap(a, b);
    if (b > c) swap(b, c);
    if (a > b) swap(a, b);
    pivot = b;

    int count_low = 0, count_high = 0;
    for (int i = 0; i < n; i++) {
        if (arr[i] < pivot) count_low++;
        else if (arr[i] > pivot) count_high++;
    }

    double balance_ratio = double(min(count_low, count_high)) / n;

    // 如果分布太極端 → fallback 用 merge sort
    if (balance_ratio < 0.05) {
        merge_sort(arr);
    }
    else {
        quick_sort_recursive(arr, 0, n - 1);
    }
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
        composite_sort(test);
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

1. 時間複雜度：最壞情況 $O(nlogn)$、平均情況 $O(nlogn)$
2. 空間複雜度：空間複雜度為 $O(n)$。

## 測試與驗證

### 平均情況測試案例

使用 Permule() 函式
| 測試案例 | 輸入參數 $n$ | Timer 精度（δ) | 排序執行時間 |
|----------|--------------|--------------|-------------|
| 測試一   | $n = 500$    | 100ns        | 81ms        |
| 測試二   | $n = 1000$   | 100ns        | 173ms       |
| 測試三   | $n = 2000$   | 100ns        | 307ms       |
| 測試四   | $n = 3000$   | 100ns        | 586ms       |
| 測試五   | $n = 4000$   | 100ns        | 660ms       | 
| 測試六   | $n = 5000$   | 100ns        | 979ms       | 

### 最壞情況測試案例

使用 ReverseFill() 函式
| 測試案例 | 輸入參數 $n$ | Timer 精度（δ) | 排序執行時間 |
|----------|--------------|--------------|-------------|
| 測試一   | $n = 500$    | 100ns        | 159ms       |
| 測試二   | $n = 1000$   | 100ns        | 261ms       |
| 測試三   | $n = 2000$   | 100ns        | 397ms       |
| 測試四   | $n = 3000$   | 200ns        | 766ms       |
| 測試五   | $n = 4000$   | 100ns        | 853ms       | 
| 測試六   | $n = 5000$   | 100ns        | 1385ms      | 


### Composite 圖表（x 軸為 n，y 軸為時間）

![image](https://github.com/user-attachments/assets/b0f39f6c-6ab3-48e5-8cff-c54bfa2abbb7)

### 所有排序的 Worst time 、 Average time 比較（x 軸為 n，y 軸為時間）

![image](https://github.com/user-attachments/assets/afc9ad41-ee30-4c0a-9063-571283d3bb10)

![image](https://github.com/user-attachments/assets/ed896bf6-c378-4b6e-b20b-461c8cf8fcde)

#### 實際運作的時間看起來比Quick Sort慢的原因

因為本測試中 composite_sort 的排序時間包含 is_sorted 與 pivot 預判策略的時間，因此反映整體函式實際執行效率，如果將這些時間扣掉就會比Quick Sort還快

### 編譯與執行指令
```shell
$ g++ sort_all_in_one.cpp -std=c++17 -o main -lpsapi
$ .\\main
```

### 結論

1. 程式能正確計算 Timer 精度和最終排序執行時間。  
2. 測試案例涵蓋多種不同資料量測試（$n = 500$、$n = 1000$、$n = 2000$、$n = 3000$、$n = 4000$、$n = 5000$），驗證程式能夠執行少量和大量的排序。
3. 在多數資料結構下皆能保持優異效能，且透過事前預判與切分失衡的 fallback 策略，有效避免 Quick Sort 退化至 $O(n^2)$的風險
4. 整合 Insertion Sort 與 Merge Sort 的強項，使其在小型資料、已排序資料或極端分布資料下都能快速完成排序。
   


## 申論及開發報告

### 使用 Composite Sort 的理由：

#### 在設計排序函式時，我們觀察到不同的排序演算法在不同資料結構下有明顯的效能差異。例如：

    1. Insertion Sort 在小筆資料下效率極高，但在大資料下退化成 $(O(n^2)$
    2. Quick Sort 在平均情況非常快速，但在極端切分時會退化
    3. Merge Sort 時間複雜度穩定，但記憶體需求較高
    4. Heap Sort 則在一些情況下表現穩定，但排序結果不穩定（非穩定排序）

#### 本次作業設計一個名為 composite_sort() 的綜合排序函式，整合上述演算法的優點，依照資料特性自動選擇最合適的排序方式：

    1. 小於等於 32 筆 → 使用 Insertion Sort
    2. 資料已排序 → 直接跳過不排序
    3. 資料切分過於不平衡 → 使用 Merge Sort 保底
    4. 一般情況 → 使用改良版 Quick Sort

這樣設計能有效避免排序退化情形，同時兼顧時間效率與穩定性，為本作業提出一個具備實用價值的多工排序策略。
