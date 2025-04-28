#include <iostream>
#include <vector>

using namespace std;

// �洫��Ӥ���
void swap(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}

// �N�}�C�̾� pivot ��������
int partition(vector<int> &arr, int low, int high) {
    int pivot = arr[high];  // �H�̫�@�Ӥ����@�� pivot
    int i = low - 1;         // i �O�p�� pivot �ϰ쪺�̫�@�Ӥ����� index

    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;  // �^�� pivot ���̲צ�m
}

// Quick Sort �D�{���]���j�^
void quickSort(vector<int> &arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);  // ��� pivot ���T��m

        quickSort(arr, low, pi - 1);  // �ƥ��b��
        quickSort(arr, pi + 1, high); // �ƥk�b��
    }
}

int main() {
    vector<int> arr;
    arr.push_back(5);
    arr.push_back(3);
    arr.push_back(8);
    arr.push_back(4);
    arr.push_back(2);

    cout << "�쥻���}�C�G";
for (int i = 0; i < arr.size(); i++)
    cout << arr[i] << " ";
cout << endl;

quickSort(arr, 0, arr.size() - 1);

cout << "�Ƨǫ᪺�}�C�G";
for (int i = 0; i < arr.size(); i++)
    cout << arr[i] << " ";
cout << endl;


    return 0;
}

