# 41043146

本題要求實現一個**快速排序（Quick Sort）**演算法，將一個整數陣列排序成由小到大的順序。

解題策略
使用分治法（Divide and Conquer）：

選定一個元素作為pivot。

將陣列分成小於 pivot 和大於等於 pivot 的兩部分。

對左右子陣列遞迴進行排序。

主程式呼叫快速排序遞迴函式，並輸出排序後的結果。

程式實作
以下為主要程式碼：

#include <iostream>
#include <vector>
using namespace std;

// 交換兩個元素
void swap(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}

// 將陣列依據 pivot 分成兩邊
int partition(vector<int> &arr, int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

// Quick Sort 主程式（遞迴）
void quickSort(vector<int> &arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

int main() {
    vector<int> arr;
    arr.push_back(5);
    arr.push_back(3);
    arr.push_back(8);
    arr.push_back(4);
    arr.push_back(2);

    cout << "原本的陣列：";
    for (int i = 0; i < arr.size(); i++)
        cout << arr[i] << " ";
    cout << endl;

    quickSort(arr, 0, arr.size() - 1);

    cout << "排序後的陣列：";
    for (int i = 0; i < arr.size(); i++)
        cout << arr[i] << " ";
    cout << endl;

    return 0;
}
效能分析
時間複雜度：

最佳情況（pivot 平均分割）：$O(n \log n)$

最差情況（pivot 總是最大或最小）：$O(n^2)$

空間複雜度：

平均情況下為 $O(\log n)$（來自遞迴呼叫堆疊的空間使用）

測試與驗證

測試案例	輸入陣列	預期輸出	實際輸出
測試一	{5, 3, 8, 4, 2}	{2, 3, 4, 5, 8}	{2, 3, 4, 5, 8}
測試二	{1}	{1}	{1}
測試三	{}（空陣列）	{}	{}
測試四	{7, 7, 7, 7}	{7, 7, 7, 7}	{7, 7, 7, 7}
測試五	{9, 1, 5, 3, 7}	{1, 3, 5, 7, 9}	{1, 3, 5, 7, 9}

編譯與執行指令

$ g++ -std=c++98 -o quicksort quicksort.cpp
$ ./quicksort
（如果使用 C++11，可以改成 -std=c++11）

結論
程式能正確對整數陣列進行排序，並符合快速排序的標準流程。 測試案例涵蓋了多種情況（一般情形、單元素、空陣列、重複元素、亂數陣列），驗證了程式的正確性與穩定性。

申論及開發報告
選擇快速排序的原因
快速排序在大多數實際情況下表現非常出色，時間複雜度為 $O(n \log n)$，且空間使用少。

遞迴的寫法自然表達出「分而治之」的策略。

程式碼精簡、效率高，適合初學者理解分治策略與遞迴概念。

例如，快速排序的遞迴公式為：

𝑄𝑢𝑖𝑐𝑘𝑆𝑜𝑟𝑡(𝐴)=𝑄𝑢𝑖𝑐𝑘𝑆𝑜𝑟𝑡(小於pivot的子陣列)+pivot+𝑄𝑢𝑖𝑐𝑘𝑆𝑜𝑟𝑡(大於pivot的子陣列)
QuickSort(A)=QuickSort(小於pivot的子陣列)+pivot+QuickSort(大於pivot的子陣列)
每次遞迴呼叫都處理更小的子陣列，最終將整個陣列完成排序。

注意事項
選 pivot 時若不謹慎，可能會導致最差情況（$O(n^2)$）。可以透過隨機選 pivot 或三數取中來優化。

當陣列很小時，可以考慮改用 Insertion Sort 減少遞迴開銷。

總結來說，快速排序結合了簡潔性與高效性，適合用來學習與應用在一般排序問題上。本題要求實現一個**快速排序（Quick Sort）**演算法，將一個整數陣列排序成由小到大的順序。

解題策略
使用分治法（Divide and Conquer）：

選定一個元素作為pivot。

將陣列分成小於 pivot 和大於等於 pivot 的兩部分。

對左右子陣列遞迴進行排序。

主程式呼叫快速排序遞迴函式，並輸出排序後的結果。

程式實作
以下為主要程式碼：
#include <iostream>
#include <vector>
using namespace std;

// 交換兩個元素
void swap(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}

// 將陣列依據 pivot 分成兩邊
int partition(vector<int> &arr, int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

// Quick Sort 主程式（遞迴）
void quickSort(vector<int> &arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

int main() {
    vector<int> arr;
    arr.push_back(5);
    arr.push_back(3);
    arr.push_back(8);
    arr.push_back(4);
    arr.push_back(2);

    cout << "原本的陣列：";
    for (int i = 0; i < arr.size(); i++)
        cout << arr[i] << " ";
    cout << endl;

    quickSort(arr, 0, arr.size() - 1);

    cout << "排序後的陣列：";
    for (int i = 0; i < arr.size(); i++)
        cout << arr[i] << " ";
    cout << endl;

    return 0;
}
效能分析
時間複雜度：

最佳情況（pivot 平均分割）：$O(n \log n)$

最差情況（pivot 總是最大或最小）：$O(n^2)$

空間複雜度：

平均情況下為 $O(\log n)$（來自遞迴呼叫堆疊的空間使用）

測試與驗證

測試案例	輸入陣列	預期輸出	實際輸出
測試一	{5, 3, 8, 4, 2}	{2, 3, 4, 5, 8}	{2, 3, 4, 5, 8}
測試二	{1}	{1}	{1}
測試三	{}（空陣列）	{}	{}
測試四	{7, 7, 7, 7}	{7, 7, 7, 7}	{7, 7, 7, 7}
測試五	{9, 1, 5, 3, 7}	{1, 3, 5, 7, 9}	{1, 3, 5, 7, 9}
編譯與執行指令

$ g++ -std=c++98 -o quicksort quicksort.cpp
$ ./quicksort
（如果使用 C++11，可以改成 -std=c++11）

結論
程式能正確對整數陣列進行排序，並符合快速排序的標準流程。 測試案例涵蓋了多種情況（一般情形、單元素、空陣列、重複元素、亂數陣列），驗證了程式的正確性與穩定性。

申論及開發報告
選擇快速排序的原因
快速排序在大多數實際情況下表現非常出色，時間複雜度為 $O(n \log n)$，且空間使用少。

遞迴的寫法自然表達出「分而治之」的策略。

程式碼精簡、效率高，適合初學者理解分治策略與遞迴概念。

例如，快速排序的遞迴公式為：

𝑄𝑢𝑖𝑐𝑘𝑆𝑜𝑟𝑡(𝐴)=𝑄𝑢𝑖𝑐𝑘𝑆𝑜𝑟𝑡(小於pivot的子陣列)+pivot+𝑄𝑢𝑖𝑐𝑘𝑆𝑜𝑟𝑡(大於pivot的子陣列)
QuickSort(A)=QuickSort(小於pivot的子陣列)+pivot+QuickSort(大於pivot的子陣列)
每次遞迴呼叫都處理更小的子陣列，最終將整個陣列完成排序。

注意事項
選 pivot 時若不謹慎，可能會導致最差情況（$O(n^2)$）。可以透過隨機選 pivot 或三數取中來優化。

當陣列很小時，可以考慮改用 Insertion Sort 減少遞迴開銷。

總結來說，快速排序結合了簡潔性與高效性，適合用來學習與應用在一般排序問題上。
