
#include <cmath>
#include "graph.h"
void minHeapify(path**& arr, int n, int size)//creates a max heap out of an array of floats
{
	int left = 2 * n+1;
	int right = 2 * n + 2;
	int smallest;
	if (left < size && arr[left]->d < arr[n]->d)//checks if left is smaller than parent
		smallest = left;
	else
		smallest = n;
	if (right < size && arr[right]->d < arr[smallest]->d)//checks if right is smaller than parent
		smallest = right;
	if (smallest != n)//flips the smallest with parent
	{
		path* temp;
		temp = arr[n];
		arr[n] = arr[smallest];
		arr[smallest] = temp;
		minHeapify(arr, smallest, size);//moves the parent down the heap recursively until  it is at the correct location
	}


}
//build max heap uses 
void buildMinHeap(path**& arr, int size) {//does minheapify starting from the middle of the array
	int i = (int)floor(size / 2);
	for (i; i >= 0; i--)
	{

		minHeapify(arr, i, size);
	}

}
