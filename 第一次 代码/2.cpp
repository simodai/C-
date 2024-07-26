#include<iostream>
#include<iomanip>
#include<string>
#include<algorithm>
#include<cmath>
#include <vector>
#include <fstream>
#include <unordered_map>

using namespace std;

struct info
{
	string	sfzh;//���֤��
	int		ct;  //Ctֵ
};
//1
bool readInfo(string filename, vector<struct info>& infos)
{
	ifstream file(filename);
	if (!file.is_open())     //����߼�Ӧ�ò�����
	{
		return false;
	}
	struct info temp;

	while (file >> temp.sfzh >> temp.ct)
	{
		infos.push_back(temp);
	}
	file.close();
	return true;
}
//2
void showInfo(vector<struct info>& infos, int n = 5)
{
	for (int i = 0; i < n && i < infos.size(); i++)
	{
		cout << left << setw(20) << infos[i].sfzh
			<< right << setw(5) << infos[i].ct << endl;;
	}
}
//3
int delInfo(vector<struct info>& infos)
{
	int count = 0;
	for (int i = 0; i < infos.size(); )
	{
		if (infos[i].sfzh.size() != 18)
		{
			infos.erase(infos.begin() + i);
			count++;
		}
		else
		{
			i++;
		}
	}
	return count;
}
//4
bool compare(info a, info b)
{
	if (a.ct != b.ct) return a.ct < b.ct;
	else if (a.sfzh != b.sfzh)return a.sfzh < b.sfzh;
}
void sortInfo(vector<info>& infos)
{
	sort(infos.begin(), infos.end(), compare);
}
//5
vector<int> groupInfo(vector<info>& infos)
{
	vector <int> a(3);
	for (int i = 0; i < infos.size(); i++)
	{
		if (infos[i].ct >= 40)
			a[2]++;
		else if (infos[i].ct < 40 && infos[i].ct >= 37)
			a[1]++;
		else
			a[0]++;
	}
	return a;
}
//6
bool writeInfo(string new_filename, vector<info>& infos)
{
	ofstream outfile(new_filename);
	for (const auto& inf : infos)
	{
		if (inf.ct >= 37 && inf.ct < 40)
		{
			outfile << inf.sfzh << " " << inf.ct << endl;
		}
	}
	outfile.close();
	return true;
}
//7
vector<string> findInvalidSfzh(vector<info>& infos)
{
	vector<string> res;
	int coefficients[] = { 7, 9, 10, 5, 8, 4, 2, 1, 6, 3, 7, 9, 10, 5, 8, 4, 2 }; // ϵ������
	char checkCodes[] = { '1', '0', 'X', '9', '8', '7', '6', '5', '4', '3', '2' }; // У��������
	for (const auto& info : infos)
	{
		int sum = 0;
		for (int j = 0; j < 17; ++j) {
			sum += (info.sfzh[j] - '0') * coefficients[j]; // info.sfzh[j] - '0' �ǽ��ַ���ʽ������ת��Ϊ����
		}
		int yu = sum % 11;
		if (info.sfzh[17] != checkCodes[yu])
		{
			res.push_back(info.sfzh);
		}
	}
	return res;
}
//8 ���غ���
void showInfo(vector<string>& res)
{
	if (res.size() == 0) cout << "���֤��ȫ����ȷ";
	else
	{
		for (int i = 0; i < res.size(); i++)
		{
			cout << res[i] << endl;
		}
	}
}

int main()
{
	vector<struct info> infos;
	if (readInfo("C:\\Users\\lenovo\\Desktop\\C++\\��������\\20220419\\input.txt", infos) == false)
	{
		cout << "���ļ�ʧ�ܣ���ȷ���ļ�·��" << endl;
		return 0;
	}
	cout << "�ϼ���" << infos.size() << "�����ݡ�";
	cout << "ǰ5������Ϊ��" << endl;
	showInfo(infos);
	int count = delInfo(infos);
	cout << "ɾ�������֤���Ϸ���" << count << "����ʣ��" << infos.size() << "��" << endl;
	sortInfo(infos);
	cout << "���������Ϊ��" << endl;
	showInfo(infos, infos.size());
	vector<int> counts = groupInfo(infos);
	cout << "������ԣ�" << counts[0] << "��" << endl;
	cout << "���л�����" << counts[1] << "��" << endl;
	cout << "�������ԣ�" << counts[2] << "��" << endl;
	if (writeInfo("d:\\out.txt", infos) == true)
	{
		cout << "д�ļ��ɹ�" << endl;
	}
	else
	{
		cout << "���ļ�ʧ��" << endl;
	}
	vector <string> res = findInvalidSfzh(infos);
	cout << "���֤�Ŵ����������£�" << endl;
	showInfo(res);
	return 0;
}