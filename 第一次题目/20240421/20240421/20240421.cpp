/*  学号:2327405038
 *  姓名:戴庭章
 *  IP:192.168.158.4
 *  上传时间:2024/4/22 16:25:09
*/
#include<iostream>
#include<iomanip>
#include<fstream>
#include<cmath>
#include<vector>
#include<algorithm>
#include<string>
using namespace std;

struct Mark
{
	string name;//姓名
	string id;	//学号
	int select;	//选择题成绩
	int program;//编程题成绩
};
//1
bool readData(string filename, vector<struct Mark>& datas)
{
	ifstream  file(filename);
	if (!file.is_open()) return false;
	struct Mark temp;
	while (file >> temp.name >> temp.id >> temp.select >> temp.program)
	{
		datas.push_back(temp);
	}
	file.close();    //文件未关闭 -1分
	return true;
}
//2
void showData(vector<struct Mark>& datas, int n = 3)
{
	for (int i = 0; i < n && i < datas.size(); i++)
	{
		cout << left << setw(10) << datas[i].id
			<< right << setw(10) << datas[i].name
			<< right << setw(5) << datas[i].select
			<< right << setw(5) << datas[i].program << endl;
	}
}
//3
vector<struct Mark> delError(vector<struct Mark>& datas)
{
	vector<struct  Mark> a;
	for (int i = 0; i < datas.size();)
	{
		if (datas[i].select > 20 || datas[i].select < 0 ||
			datas[i].program < 0 || datas[i].program>80)
		{
			a.push_back(datas[i]);
			datas.erase(datas.begin() + i);
		}
		else
		{
			i++;
		}
	}
	return a;
}
//4 < 
double statisticsData(vector<struct Mark>& datas, int& maxMark, int& minMark)
{
	double n = 0;
	maxMark = datas[0].select + datas[0].program;
	minMark = datas[0].select + datas[0].program;
	for (int i = 0; i < datas.size(); i++)
	{

		n += datas[i].select + datas[i].program;
		if ((datas[i].select + datas[i].program) < minMark)
			minMark = datas[i].select + datas[i].program;
		else maxMark = datas[i].select + datas[i].program;

	}
	return n / datas.size();
}
//5
bool compare(Mark a, Mark b)
{
	if (a.select + a.program != b.select + b.program)
		return a.select + a.program > b.select + b.program;
	else if (a.program != b.program)
		return a.program > b.program;
	else
		return a.id < b.id;//按学号大小asc码 从小到大（及字典序）
}
void sortData(vector<struct Mark>& datas)
{
	sort(datas.begin(), datas.end(), compare);
}
//6
vector<int> groupData(vector<struct Mark>& datas)
{
	vector<int> res(5,0);
	//int c1 = 0;
	//int c2 = 0;
	//int c3 = 0;
	//int c4 = 0;
	//int c5 = 0;
	for (int i = 0; i < datas.size(); i++)
	{
		int he = datas[i].select + datas[i].program;
		if (he <= 100 && he >= 90) res[0]++;
		else if (he <= 89 && he >= 80) res[1]++;
		else if (he <= 79 && he >= 70) res[2]++;
		else if (he <= 69 && he >= 60) res[3]++;
		else res[4]++;
	}
	//res.push_back(c1);
	//res.push_back(c2);
	//res.push_back(c3);
	//res.push_back(c4);
	//res.push_back(c5);
	return res;
}
//7
void showData(vector<int>& res, int n = 5)
{
	for (int i = 0; i < res.size() && i < n; i++)
	{
		if (i == 0) cout << i + 1 << " [90,100] " << res[i] << endl;
		else if (i == 1) cout << i + 1 << " [80,89] " << res[i] << endl;
		else if (i == 2) cout << i + 1 << " [70,79] " << res[i] << endl;
		else if (i == 3) cout << i + 1 << " [60,69] " << res[i] << endl;
		else cout << i + 1 << " [0,59] " << res[i] << endl;
	}
}
//8
bool writeData(string newfile, vector<int>& res)
{
	ofstream outfile(newfile);
	if (!outfile.is_open()) return false;
	for (int i = 0; i < res.size(); i++)
	{
		if (i == 0) outfile << i + 1 << " [90,100] " << res[i] << endl;
		else if (i == 1) outfile << i + 1 << " [80,89] " << res[i] << endl;
		else if (i == 2) outfile << i + 1 << " [70,79] " << res[i] << endl;
		else if (i == 3) outfile << i + 1 << " [60,69] " << res[i] << endl;
		else outfile << i + 1 << " [0,59] " << res[i] << endl;
	}
	outfile.close();
	return true;
}
//9
double getStdMark(vector<struct Mark>& datas)
{
	double s = 0;//s为方差
	double x1 = 0;//x1平均值
	for (int i = 0; i < datas.size(); i++)
	{
		x1 += datas[i].program;
	}
	x1 /= datas.size();  //这句不能写再循环内
	for (int i = 0; i < datas.size(); i++)
	{
		double x = pow((datas[i].program) - x1, 2);
		s += x;
		s /= datas.size();
	}
	return sqrt(s);
}
int main()
{
	vector<struct Mark> datas;
	if (readData("d:\\mark.txt", datas) == false)
	{
		cout << "打开文件失败";
		return -1;
	}
	cout << "读取到" << datas.size() << "条数据\n";
	cout << "前3条数据为:\n";
	showData(datas, 3);
	vector<struct Mark> infos = delError(datas);
	cout << "异常数据为：\n";
	showData(infos, infos.size());
	int maxMark = 0, minMark = 0;
	double averMark = statisticsData(datas, maxMark, minMark);
	cout << "平均分:" << averMark << "，最高分:" << maxMark << "，最低分:" << minMark << endl;
	sortData(datas);
	cout << "排序后结果为：\n";
	showData(datas, datas.size());
	vector<int> res = groupData(datas);
	cout << "汇总结果为：\n";
	showData(res);
	if (writeData("d:\\result.txt", res) == true)
	{
		cout << "文件写入成功\n";
	}
	cout << "标准差为:" << getStdMark(datas);
	return 0;
}
