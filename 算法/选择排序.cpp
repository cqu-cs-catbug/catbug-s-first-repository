//换种思路
#include<bits/stdc++.h>
using namespace std;
void bidierctionalSort(vector<int>& arr){
	int left=0;
	int right=arr.size()-1;
	while(left<right){
		int maxPointer=left;
		int minPointer=right;
		for(int i=left;i<=right;i++){
			if(arr[maxPointer]<arr[i]){maxPointer=i;}
			else if(arr[minPointer]>arr[i]){minPointer=i;}
		}    
		if(minPointer!=left){ // 将最小值交换到左边
			swap(arr[minPointer],arr[left]);
			if(maxPointer==left){maxPointer=minPointer;}
			// 如果最大值的索引恰好是left，交换后最大值现在在minPointer位置
		}
		
		if(maxPointer!=right){// 将最大值交换到右边
			swap(arr[maxPointer],arr[right]);
		}
		
		left++;
		right--;
	}    
}

void printArray(vector<int>& arr){
	for (int num : arr){
		cout<<num<<' ';
	}
}
int main(){
	vector<int>arr={12,56,11,89,45,32,77,6,29,44,33,67};
	bidierctionalSort(arr);
	printArray(arr);
	return 0;
}
