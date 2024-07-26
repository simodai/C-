#include<iostream>
#include<iomanip>
#include<vector>
#include<algorithm>
#include<fstream>
#include<string>
#include<sstream>
#include<cmath>
using namespace std;

//1
int ReadInfo(const string& filePath, vector<vector<int>>& vecInt2D)
{
	ifstream file(filePath);
	if (!file.is_open()) {
		return -1;
	}
	string line;
	while (getline(file, line))
	{
		vector<int> vecInt;
		istringstream iss(line);//Ϊʲô��������string
		// istringstream ������ÿ�ж�ȡ�����ַ��������н�����������istringstream �ṩ������ȡ����� >>�����Է���ش��ж�ȡ����
		int num;
		while (iss >> num)
		{
			vecInt.push_back(num);
		}
		vecInt2D.push_back(vecInt);
	}
	file.close();
	return 1;
}
//2
void ShowData(vector<vector<int>>& vecInt2D)
{
	for (int i = 0; i < vecInt2D.size(); i++)
	{
		for (int j = 0; j < vecInt2D[i].size(); j++)
		{
			cout << setw(5) << right << vecInt2D[i][j];
		}
		cout << endl;
	}
}
//3
vector<int> GetNumbers(vector<vector<int>>& vecInt2D, bool flag = true)
{
	vector<int> a;
	vector<int> b;
	for (int i = 0; i < vecInt2D.size(); i++)
	{
		sort(vecInt2D[i].begin(), vecInt2D[i].end());
		a.push_back(vecInt2D[i][vecInt2D[i].size() - 1]);
		b.push_back(vecInt2D[i][0]);
	}
	if (flag == true)	return a;
	else				return b;
}
//4
void ShowData(vector<int>& vecB, int x = 5, int y = 5)
{
	for (int i = 0; i < vecB.size(); i++)
	{
		if (i % x == 4) cout << left << setw(y) << vecB[i] << endl;
		else		    cout << left << setw(y) << vecB[i];
	}
}
//5
int DelVecNumber(vector<int>& vecB)
{
	int count = 0;
	for (int i = 0; i < vecB.size() - 1;)
	{
		if (vecB[i] == vecB[i + 1])
		{
			vecB.erase(vecB.begin() + i);
			count++;
		}
		else
		{
			i++;
		}
	}
	return count;
}
// 6
int f(int x)
{
	int sum = 0;
	while (x > 0)
	{
		sum += x % 10;
		x /= 10;
	}
	return sum;
}
bool compare(int a, int b)
{
	if (f(a) != f(b))
	{
		return f(a) < f(b);
	}
	return a < b;// �������֮����ȣ�����ԭʼ�����Ĵ�С˳������
}
void SortData(vector<int>& vecB)
{
	sort(vecB.begin(), vecB.end(), compare);
}
//7
int writeInfo(string newfile, vector<int>& vecB)
{
	ofstream outfile(newfile);
	if (!outfile.is_open()) return -1;

	int count = 0;
	for (int i = 0; i < vecB.size(); i++)
	{
		if (count % 3 == 0) {
			outfile << endl;
		}
		outfile << setw(5) << right << vecB[i];
		count++;
	}
	outfile.close();
	return 1;
}
int main()
{
	vector< vector<int> > vecInt2D;
	vector<int> vecB;
	int count;

	if (ReadInfo("d:\\data.txt", vecInt2D) == -1)         //1
	{
		cout << "��d:\\data.txt�ļ�ʧ��" << endl;
	}
	else
	{
		cout << "��ȡ��" << vecInt2D.size() << "������" << endl;
	}
	cout << "��ȡ���Ķ�ά����Ϊ:\n";
	ShowData(vecInt2D);                                  //2
	vecB = GetNumbers(vecInt2D);                         //3
	cout << "\nÿ�����ֵ���ɵ�������\n";
	ShowData(vecB, 5);                                    //4

	count = DelVecNumber(vecB);                           //5
	cout << "\nɾ�����ظ�Ԫ�ظ���Ϊ:" << count << endl;
	SortData(vecB);
	cout << "\n������������\n";
	ShowData(vecB);

	if (writeInfo("D:\\result.txt", vecB) == -1)
	{
		cout << "��d:\\result.txt�ļ�ʧ��!\n";
	}

	return 0;
}