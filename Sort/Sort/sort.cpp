#include<iostream>
using namespace std;

template <class T>
int getArrayLen(T& array)
{
	//使用模板定义一 个函数getArrayLen,该函数将返回数组array的长度
	return (sizeof(array) / sizeof(array[0]));
}

void BubbleSort(int a[], int length);              //冒泡排序
void SelectSort(int a[], int length);              //选择排序
void QuickSort(int a[], int left, int right);      //快速排序
void HeapSort(int a[],int length);                 //堆排序
void ShellSort(int a[], int n);                    //希尔排序
void MergeSort(int a[], int p, int r);              //归并排序

void main()
{
	int b[] = {2,39,90,3,9,0,9,0,1010,222,1,1,45,67,89,888888,788,55555};

	int length = getArrayLen(b);

	/*冒泡排序*/
	//BubbleSort(b, length);

	/*选择排序*/
	//SelectSort(b, length);

	/*快速排序*/
	/*QuickSort(b, 0, length-1);*/

	/*堆排序*/
	/*HeapSort(b,length-1);*/

	/*希尔排序*/
	/*ShellSort(b, length);*/

	MergeSort(b,0,length-1);

	//输出
	cout << "排序后的数组为:";
	for (int i = 0; i < length; i++)
	{
		cout << b[i] << " ";
	}
	cout << endl;
}



/*1.优化后的冒泡排序算法*/
//通过与相邻元素的比较和交换，每一次都把剩余最小的数交换到最前面
//最好情况下：正序有序，只需要比较n次。故，为O(n)
//最坏情况下: 逆序有序，则需要比较(n - 1) + (n - 2) + …… + 1，故，复杂度为O(N*N)
//稳定性
//排序过程中只交换相邻两个元素的位置,当两个数相等时,是没必要交换两个数的位置的,所以，它们的相对位置并没有改变，冒泡排序算法是稳定的！
void BubbleSort(int a[], int length)
{
	bool flag;
	for (int i = 0; i < length - 1; i++)
	{
		flag = false;
		for (int j = length - 1; j > i; j--)
		{
			if (a[j] < a[j - 1])
			{
				swap(a[j], a[j - 1]);
				flag = true;
			}
		}
		if (flag == false)    //上一个循环比较结束而没有发生交换，但是每两个相邻元素都比较过了，说明已经有序  
		{
			break;//已经有序跳出循环  
		}
	}
}



/*2.选择排序*/
//选择最小的元素与未排序部分的首部交换，使得序列的前面为有序
//最好情况时间：O(n ^ 2)
//最坏情况时间：O(n ^ 2)
//不稳定
void SelectSort(int a[], int length)
{
	int minIndex;
	for(int i=0;i<length-1;i++)
	{ 
		minIndex = i;
		for (int j = i + 1; j < length; j++)   //从i+1开始比较，因为minIndex默认为i了，i就没必要比了
		{
			if (a[j] < a[minIndex])
			{
				minIndex = j;
			}
		}
		if (minIndex != i)                    //如果minIndex不为i，说明找到了更小的值，交换之
		{
			swap(a[i], a[minIndex]);
		}
	}

}




/*3.快速排序*/
//在待排序的n个记录中任取一个记录(通常取第一个记录), 把该记录放入适当位置后, 数据序列被此记录划分成两部分,
//所有关键字比该记录关键字小的记录放置在前一部分,所有比它大的记录放置在后一部分,并把该记录排在这两部分的中间(称为该记录归位)
//最好的情况下：因为每次都将序列分为两个部分(一般二分都复杂度都和logN相关)，故为 O(N*logN)
//最坏的情况下：基本有序时，退化为冒泡排序，几乎要比较N*N次，故为O(N*N)
//3、稳定性
//由于每次都需要和中轴元素交换，因此原来的顺序就可能被打乱。如序列为 5 3 3 4 3 8 9 10 11会将3的顺序打乱。所以说，快速排序是不稳定的！
void QuickSort(int a[], int low,int high)
{
	

	if (low >= high)
	{
		return;
	}

	int first = low;
	int last = high;
	int key = a[first];/*用字表的第一个记录作为枢轴*/

	while (first < last)
	{
		while (first < last && a[last] >= key)
		{
			--last;
		}

		a[first] = a[last];/*将比第一个小的移到低端*/

		while (first < last && a[first] <= key)
		{
			++first;
		}

		a[last] = a[first];/*将比第一个大的移到高端*/
	}
	a[first] = key;/*枢轴记录到位*/
	QuickSort(a, low, first - 1);
	QuickSort(a, first + 1, high);
}




/*4.堆排序*/
/*思想：利用完全二叉树中双亲节点和孩子节点之间的内在关系，在当前无序区中选择关键字最大(或者最小)的记录。也就是说，以最小堆为例，根节点为最小元素，较大的节点偏向于分布在堆底附近*/
//最坏情况下，接近于最差情况下：O(N*logN)
//要不断调整堆，不稳定
void sift(int a[], int k, int m)
{//要筛选的节点编号为k，堆中最后一个节点为m  
	int i, j, temp;
	i = k;
	j = 2 * i;       //编号为k的节点的左孩子  
	temp = a[i];     //将筛选记录暂存(需要调整的位置)  
	while (j <= m)   //筛选还没进行到的叶子  
	{
		if (j<m && a[j]<a[j + 1])//j<m说明i节点还有一个右孩子，为二度节点  
		{
			j++;     //i有两个孩子，取大孩子  
		}
		//一个孩子或者左孩子比右孩子大  
		if (a[i] > a[j])
		{
			break;//孩子比父亲小  
		}
		else//孩子比父亲大  
		{
			a[i] = a[j];//将较大的节点移到根上。  
			i = j;
			j = 2 * i;
			//将i指向交换的位置，为进一步移动做准备。  
		}
		a[i] = temp;//将筛选记录移到正确位置  
	}
}
void makeHeap(int a[], int root, int last)
{
	int n = last;
	for (int i = n / 2; i>0; i--)//初始建堆操作  
	{
		sift(a, i, n);
	}
	swap(a[1], a[last]);
	cout<< a[last] << " ";
}
void HeapSort(int a[],int length) {
	cout << "排序后的数组为:";
	for (int i = 1; i <= length; i++)
	{
		makeHeap(a, 1, length - i + 1);
	}
	cout << endl;
}




/*5.希尔排序*/
//先将整个待排记录序列分割成为若干子序列分别进行直接插入排序，待整个序列中的记录基本有序时再对全体记录进行一次直接插入排序
//最坏情况下：O(N*logN)，最坏的情况下和平均情况下差不多
//先取定一个小于n的整数d1作为第一个增量,把表的全部记录分成d1个组,所有距离为d1的倍数的记录放在同一个组中,在各组内进行直接插入排序；然后,取第二个增量d2(＜d1),重复上述的分组和排序,直至所取的增量dt=1(dt<dt-1<…<d2<d1),即所有记录放在同一组中进行直接插入排序为止
void ShellSort(int a[], int length)
{
	for (int gap = 3; gap >0; gap--)           /*数组分为三部分进行排序*/
	{
		for (int i = 0; i<gap; i++)
		{
			for (int j = i + gap; j<length; j = j + gap)
			{
				if (a[j]<a[j - gap])
				{
					int temp = a[j];
					int k = j - gap;
					while (k >= 0 && a[k]>temp)
					{
						a[k + gap] = a[k];
						k = k - gap;
					}
					a[k + gap] = temp;
				}
			}
		}
	}
}




/*6归并排序*/
//多次将两个或两个以上的有序表合并成一个新的有序表
//最好的情况下：一趟归并需要n次，总共需要logN次，因此为O(N*logN)
//最坏的情况下，接近于平均情况下，为O(N*logN)
void Merge(int a[], int first, int q, int last)
{
	int n1 = q - first + 1;
	int n2 = last - q;
	int *L = new int[n1 + 1];
	int *R = new int[n2 + 1];
	int i, j, k;

	for (i = 0; i<n1; i++) {
		L[i] = a[first + i];
	}
	for (j = 0; j<n2; j++) {
		R[j] = a[q + j + 1];
	}
	L[n1] = 10000000;
	R[n2] = 10000000;

	for (i = 0, j = 0, k = first; k <= last; k++)
	{
		if (L[i] <= R[j])
		{
			a[k] = L[i];
			i++;
		}
		else {
			a[k] = R[j];
			j++;
		}
	}
	delete[]L;
	delete[]R;
}
void MergeSort(int a[], int first, int last)
{
	if (first<last)
	{
		int q = (first + last) / 2;
		MergeSort(a, first, q);
		MergeSort(a, q + 1, last);
		Merge(a, first, q, last);
	}
}