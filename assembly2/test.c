#include <stdio.h>

int add(int a, int b){
		return a + b;
}

int mul(int a, int b){
		return a * b;
}

int main(){
		int i, j, res = 0;
		int arr1[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
		int arr2[10] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
		
		for (i = 0; i < 10; i++){
				j = mul(arr1[i], arr2[i]);
				res = add(res, j);
		}
		return 0;
}