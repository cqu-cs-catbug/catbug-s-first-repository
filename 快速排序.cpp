#include<bits/stdc++.h>
using namespace std;
int partition(vector<int>& nums,int l,int r){ //l,r分别表示数组的左右元素索引
	int pivot =nums[r]; //以最右边的元素作为标准
	int i =l-1;
	for(int j=l;j<r;j++){
		if(nums[j]<pivot){
			i+=1;
			swap(nums[i],nums[j]);
		}
	}
	swap(nums[i+1],nums[r]);
	return i+1;
} //快速排序的底层逻辑

void quickSort(vector<int>& nums,int l,int r){
	if(l<r){
		int mid=partition(nums,l,r);
		quickSort(nums,l,mid-1);
		quickSort(nums,mid+1,r);
	} //使用递归，直到只剩一个元素
}
int main(){
	vector<int> nums={2,4,1,6,3,9,8,7};
	quickSort(nums,0,nums.size()-1);
	for(int x:nums){cout<<x<<" ";};
}
