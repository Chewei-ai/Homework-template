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

// ---------- 插入排序 ----------
void insertion_sort(vector<int> arr) {
    for (int i = 1; i < arr.size(); i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
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

// ---------- Heap Sort ----------
void maxHeapify(vector<int>& arr, int n, int i) {
    int largest = i, l = 2 * i + 1, r = 2 * i + 2;
    if (l < n && arr[l] > arr[largest]) largest = l;
    if (r < n && arr[r] > arr[largest]) largest = r;
    if (largest != i) {
        swap(arr[i], arr[largest]);
        maxHeapify(arr, n, largest);
    }
}
void heap_sort(vector<int> arr) {
    int n = arr.size();
    for (int i = n / 2 - 1; i >= 0; i--) maxHeapify(arr, n, i);
    for (int i = n - 1; i > 0; i--) {
        swap(arr[0], arr[i]);
        maxHeapify(arr, i, 0);
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
    int n = 500, trials = 30;

    /*5種排序選1*/
    string sort_method = "insertion";
    //string sort_method = "merge";
    //string sort_method = "heap";
    //string sort_method = "quick";
    //string sort_method = "composite";

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
