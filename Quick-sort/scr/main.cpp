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
    int pivot = arr[high];  // 以最後一個元素作為 pivot
    int i = low - 1;         // i 是小於 pivot 區域的最後一個元素的 index

    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;  // 回傳 pivot 的最終位置
}

// Quick Sort 主程式（遞迴）
void quickSort(vector<int> &arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);  // 找到 pivot 正確位置

        quickSort(arr, low, pi - 1);  // 排左半邊
        quickSort(arr, pi + 1, high); // 排右半邊
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

