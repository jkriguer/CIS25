#include <iostream>

using namespace std;

int main() {
	int arr[]{ 1,2,3,4,5 };
	for (int i : arr)//print original array
		cout << i << " ";
	cout << '\n';
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0])/2; i++) {
		int temp = arr[i];
		arr[i] = arr[sizeof(arr) / sizeof(arr[0]) - i - 1];
		arr[sizeof(arr) / sizeof(arr[0]) - i - 1] = temp;
	}
	for (int i : arr)//print reversed array
		cout << i << " ";
	cout << '\n';
}