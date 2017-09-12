#include<iostream>
using namespace std;

template <class T>
int getArrayLen(T& array)
{
	//ʹ��ģ�嶨��һ ������getArrayLen,�ú�������������array�ĳ���
	return (sizeof(array) / sizeof(array[0]));
}

void BubbleSort(int a[], int length);              //ð������
void SelectSort(int a[], int length);              //ѡ������
void QuickSort(int a[], int left, int right);      //��������
void HeapSort(int a[],int length);                 //������
void ShellSort(int a[], int n);                    //ϣ������
void MergeSort(int a[], int p, int r);              //�鲢����

void main()
{
	int b[] = {2,39,90,3,9,0,9,0,1010,222,1,1,45,67,89,888888,788,55555};

	int length = getArrayLen(b);

	/*ð������*/
	//BubbleSort(b, length);

	/*ѡ������*/
	//SelectSort(b, length);

	/*��������*/
	/*QuickSort(b, 0, length-1);*/

	/*������*/
	/*HeapSort(b,length-1);*/

	/*ϣ������*/
	/*ShellSort(b, length);*/

	MergeSort(b,0,length-1);

	//���
	cout << "����������Ϊ:";
	for (int i = 0; i < length; i++)
	{
		cout << b[i] << " ";
	}
	cout << endl;
}



/*1.�Ż����ð�������㷨*/
//ͨ��������Ԫ�صıȽϺͽ�����ÿһ�ζ���ʣ����С������������ǰ��
//�������£���������ֻ��Ҫ�Ƚ�n�Ρ��ʣ�ΪO(n)
//������: ������������Ҫ�Ƚ�(n - 1) + (n - 2) + ���� + 1���ʣ����Ӷ�ΪO(N*N)
//�ȶ���
//���������ֻ������������Ԫ�ص�λ��,�����������ʱ,��û��Ҫ������������λ�õ�,���ԣ����ǵ����λ�ò�û�иı䣬ð�������㷨���ȶ��ģ�
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
		if (flag == false)    //��һ��ѭ���ȽϽ�����û�з�������������ÿ��������Ԫ�ض��ȽϹ��ˣ�˵���Ѿ�����  
		{
			break;//�Ѿ���������ѭ��  
		}
	}
}



/*2.ѡ������*/
//ѡ����С��Ԫ����δ���򲿷ֵ��ײ�������ʹ�����е�ǰ��Ϊ����
//������ʱ�䣺O(n ^ 2)
//����ʱ�䣺O(n ^ 2)
//���ȶ�
void SelectSort(int a[], int length)
{
	int minIndex;
	for(int i=0;i<length-1;i++)
	{ 
		minIndex = i;
		for (int j = i + 1; j < length; j++)   //��i+1��ʼ�Ƚϣ���ΪminIndexĬ��Ϊi�ˣ�i��û��Ҫ����
		{
			if (a[j] < a[minIndex])
			{
				minIndex = j;
			}
		}
		if (minIndex != i)                    //���minIndex��Ϊi��˵���ҵ��˸�С��ֵ������֮
		{
			swap(a[i], a[minIndex]);
		}
	}

}




/*3.��������*/
//�ڴ������n����¼����ȡһ����¼(ͨ��ȡ��һ����¼), �Ѹü�¼�����ʵ�λ�ú�, �������б��˼�¼���ֳ�������,
//���йؼ��ֱȸü�¼�ؼ���С�ļ�¼������ǰһ����,���б�����ļ�¼�����ں�һ����,���Ѹü�¼�����������ֵ��м�(��Ϊ�ü�¼��λ)
//��õ�����£���Ϊÿ�ζ������з�Ϊ��������(һ����ֶ����Ӷȶ���logN���)����Ϊ O(N*logN)
//�������£���������ʱ���˻�Ϊð�����򣬼���Ҫ�Ƚ�N*N�Σ���ΪO(N*N)
//3���ȶ���
//����ÿ�ζ���Ҫ������Ԫ�ؽ��������ԭ����˳��Ϳ��ܱ����ҡ�������Ϊ 5 3 3 4 3 8 9 10 11�Ὣ3��˳����ҡ�����˵�����������ǲ��ȶ��ģ�
void QuickSort(int a[], int low,int high)
{
	

	if (low >= high)
	{
		return;
	}

	int first = low;
	int last = high;
	int key = a[first];/*���ֱ�ĵ�һ����¼��Ϊ����*/

	while (first < last)
	{
		while (first < last && a[last] >= key)
		{
			--last;
		}

		a[first] = a[last];/*���ȵ�һ��С���Ƶ��Ͷ�*/

		while (first < last && a[first] <= key)
		{
			++first;
		}

		a[last] = a[first];/*���ȵ�һ������Ƶ��߶�*/
	}
	a[first] = key;/*�����¼��λ*/
	QuickSort(a, low, first - 1);
	QuickSort(a, first + 1, high);
}




/*4.������*/
/*˼�룺������ȫ��������˫�׽ڵ�ͺ��ӽڵ�֮������ڹ�ϵ���ڵ�ǰ��������ѡ��ؼ������(������С)�ļ�¼��Ҳ����˵������С��Ϊ�������ڵ�Ϊ��СԪ�أ��ϴ�Ľڵ�ƫ���ڷֲ��ڶѵ׸���*/
//�����£��ӽ����������£�O(N*logN)
//Ҫ���ϵ����ѣ����ȶ�
void sift(int a[], int k, int m)
{//Ҫɸѡ�Ľڵ���Ϊk���������һ���ڵ�Ϊm  
	int i, j, temp;
	i = k;
	j = 2 * i;       //���Ϊk�Ľڵ������  
	temp = a[i];     //��ɸѡ��¼�ݴ�(��Ҫ������λ��)  
	while (j <= m)   //ɸѡ��û���е���Ҷ��  
	{
		if (j<m && a[j]<a[j + 1])//j<m˵��i�ڵ㻹��һ���Һ��ӣ�Ϊ���Ƚڵ�  
		{
			j++;     //i���������ӣ�ȡ����  
		}
		//һ�����ӻ������ӱ��Һ��Ӵ�  
		if (a[i] > a[j])
		{
			break;//���ӱȸ���С  
		}
		else//���ӱȸ��״�  
		{
			a[i] = a[j];//���ϴ�Ľڵ��Ƶ����ϡ�  
			i = j;
			j = 2 * i;
			//��iָ�򽻻���λ�ã�Ϊ��һ���ƶ���׼����  
		}
		a[i] = temp;//��ɸѡ��¼�Ƶ���ȷλ��  
	}
}
void makeHeap(int a[], int root, int last)
{
	int n = last;
	for (int i = n / 2; i>0; i--)//��ʼ���Ѳ���  
	{
		sift(a, i, n);
	}
	swap(a[1], a[last]);
	cout<< a[last] << " ";
}
void HeapSort(int a[],int length) {
	cout << "����������Ϊ:";
	for (int i = 1; i <= length; i++)
	{
		makeHeap(a, 1, length - i + 1);
	}
	cout << endl;
}




/*5.ϣ������*/
//�Ƚ��������ż�¼���зָ��Ϊ���������зֱ����ֱ�Ӳ������򣬴����������еļ�¼��������ʱ�ٶ�ȫ���¼����һ��ֱ�Ӳ�������
//�����£�O(N*logN)���������º�ƽ������²��
//��ȡ��һ��С��n������d1��Ϊ��һ������,�ѱ��ȫ����¼�ֳ�d1����,���о���Ϊd1�ı����ļ�¼����ͬһ������,�ڸ����ڽ���ֱ�Ӳ�������Ȼ��,ȡ�ڶ�������d2(��d1),�ظ������ķ��������,ֱ����ȡ������dt=1(dt<dt-1<��<d2<d1),�����м�¼����ͬһ���н���ֱ�Ӳ�������Ϊֹ
void ShellSort(int a[], int length)
{
	for (int gap = 3; gap >0; gap--)           /*�����Ϊ�����ֽ�������*/
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




/*6�鲢����*/
//��ν��������������ϵ������ϲ���һ���µ������
//��õ�����£�һ�˹鲢��Ҫn�Σ��ܹ���ҪlogN�Σ����ΪO(N*logN)
//�������£��ӽ���ƽ������£�ΪO(N*logN)
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