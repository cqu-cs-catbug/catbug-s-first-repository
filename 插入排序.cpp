#include<bits/stdc++.h>
using namespace std;
void insertionSort(vector<int>& arr){
	int n=arr.size();
	for (int i=0;i<n;i++){
		int key=arr[i]; //确定待插入的元素
		int j=i-1;
		while(j>=0&&arr[j]>key){
			arr[j+1]=arr[j];//比key大的后移一位
			j--;
		}
		
		//使用二分查找可以加速寻找插入位置的过程
		
		arr[j+1]=key;//插入元素
	}
}
void printArray(vector<int>& arr){
	for(int num:arr){
		cout<<num<<' ';
	}
}
int main(){
	vector<int>arr={98,65,32,46,78,56,13,34,77,11,64,33};
	insertionSort(arr);
	printArray(arr);
	return 0;
}
