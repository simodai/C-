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
	string	sfzh;//身份证号
	int		ct;  //Ct值
};
//1
bool readInfo(string filename, vector<struct info>& infos)
{
	ifstream file(filename);
	if (!file.is_open())     //这个逻辑应该不成立
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
	int coefficients[] = { 7, 9, 10, 5, 8, 4, 2, 1, 6, 3, 7, 9, 10, 5, 8, 4, 2 }; // 系数数组
	char checkCodes[] = { '1', '0', 'X', '9', '8', '7', '6', '5', '4', '3', '2' }; // 校验码数组
	for (const auto& info : infos)
	{
		int sum = 0;
		for (int j = 0; j < 17; ++j) {
			sum += (info.sfzh[j] - '0') * coefficients[j]; // info.sfzh[j] - '0' 是将字符形式的数字转换为整数
		}
		int yu = sum % 11;
		if (info.sfzh[17] != checkCodes[yu])
		{
			res.push_back(info.sfzh);
		}
	}
	return res;
}
//8 重载函数
void showInfo(vector<string>& res)
{
	if (res.size() == 0) cout << "身份证号全部正确";
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
	if (readInfo("C:\\Users\\lenovo\\Desktop\\C++\\考试试题\\20220419\\input.txt", infos) == false)
	{
		cout << "打开文件失败，请确认文件路径" << endl;
		return 0;
	}
	cout << "合计有" << infos.size() << "条数据。";
	cout << "前5条数据为：" << endl;
	showInfo(infos);
	int count = delInfo(infos);
	cout << "删除了身份证不合法的" << count << "条，剩余" << infos.size() << "条" << endl;
	sortInfo(infos);
	cout << "排序后数据为：" << endl;
	showInfo(infos, infos.size());
	vector<int> counts = groupInfo(infos);
	cout << "其中陽性：" << counts[0] << "人" << endl;
	cout << "其中灰区：" << counts[1] << "人" << endl;
	cout << "其中阴性：" << counts[2] << "人" << endl;
	if (writeInfo("d:\\out.txt", infos) == true)
	{
		cout << "写文件成功" << endl;
	}
	else
	{
		cout << "打开文件失败" << endl;
	}
	vector <string> res = findInvalidSfzh(infos);
	cout << "身份证号错误检查结果如下：" << endl;
	showInfo(res);
	return 0;
}