#include <iostream>
#include <cstdlib>  // 包含exit()的头文件
#include <cctype>   // 包含 tolower 函数
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>
#include <algorithm>
using namespace std;

class CWorker
{
private:
	int m_ID; //工号
	string m_Name; //姓名
	int m_Sex; //性别 0代表女性 1代表男性
	int m_Age; //年龄
public:
	CWorker(int ID, string Name, int Sex, int Age)
	{
		if (Sex < 0 || Sex>1)
		{
			cout << "性别初始值" << Sex << "不符合要求！" << endl;
			exit(0);
		}
		if (Age <= 0)
		{
			cout << "年龄初始值" << Age << "不符合要求！" << endl;
			exit(0);
		}
		m_ID = ID;
		m_Name = Name;
		m_Sex = Sex;
		m_Age = Age;
	}
	string GetName()const { return m_Name; }
	int GetSex()const{ return m_Sex;}
	int GetAge()const{ return m_Age;}

	friend ostream& operator<<(ostream& Out, const CWorker& Obj)
	{
		Out << right << setw(5) << Obj.m_ID;
		Out << right << setw(10) << Obj.m_Name;
		Out << right << setw(5) << Obj.m_Sex;
		Out << right << setw(6) << Obj.m_Age;
		return Out;
	}
};

class CBenchWorker : public CWorker
{
private:
	int m_Grade; //钳工级别 1-5，最大为5级
public:
	CBenchWorker():CWorker(0,"No Name",0,18)
	{
		m_Grade = 1;
	}
	CBenchWorker(int ID, string Name, int Sex, int Age, int Grade)
		:CWorker(ID, Name, Sex, Age)
	{
		m_Grade = Grade;
	}
	int GetGrade() const { return m_Grade; }

	CBenchWorker& operator++()
	{
		if (m_Grade < 5) 
			m_Grade++;
		return *this;
	}
	friend ostream& operator<<(ostream& Out, const CBenchWorker& Obj)
	{
		Out << static_cast<const CWorker>(Obj);
		Out << right << setw(5) << Obj.m_Grade;
		return Out;
	}
};
bool  ReadData(const string& filename, vector<CBenchWorker>& a)
{
	ifstream file(filename);
	if (!file.is_open()) return false;

	string line;
	while (getline(file, line))
	{
		CBenchWorker temp;
		istringstream ss(line);
		int id, sex, age, grade;
		string name;
		ss >> id >> name >> sex >> age >> grade;
		temp = CBenchWorker(id, name, sex, age, grade);
		a.push_back(temp);
		//这两句  可以写为 a.emplace_back(id, name, sex, age, grade);
	}
	file.close();
	return true;
}

void DisplayData(const vector<CBenchWorker>& workers)
{
	for (const auto& worker : workers)
		cout << worker << endl;
}

void InecData(vector<CBenchWorker>& workers)
{
	for (auto& worker : workers)
		++worker; 
}

int DelData(vector<CBenchWorker>& a, int age, int grade)
{
	int count1=0;
	for (int i = 0; i < a.size(); )
	{
		if (a[i].GetAge() >= age && a[i].GetGrade() <= grade)
		{
			a.erase(a.begin() + i);
			//cout << "Deleting worker: " << a[i].GetName() << endl;
			count1++;
		}
		else
			i++;
	}
	return count1;
}

string toLower(const string& s)
{
    string result;
    result.resize(s.size());
    transform(s.begin(), s.end(), result.begin(), ::tolower);
    return result;
}
int DelData(vector<CBenchWorker>& a,string s)
{
	int count2 = 0;
	string snew =toLower(s);
	for (int i = 0; i < a.size(); )
	{
		string s1 = toLower(a[i].GetName());
		if (s1.find(snew) != string::npos)
		{
			a.erase(a.begin() + i);
			count2++;
		}
		else
			i++;
	}
	return count2;
}

bool compare(const CBenchWorker& a, const CBenchWorker& b)
{
	if (a.GetSex() != b.GetSex())
		return a.GetSex() < b.GetSex(); 
		// 女性在前，男性在后
	else if (a.GetSex() == 0) 
		return a.GetGrade() > b.GetGrade();
		// 同性别女性，按级别降序排列
	else 
		return a.GetGrade() < b.GetGrade();
		// 同性别男性，按级别升序排列
}
void SortData(vector<CBenchWorker>& a)
{
	sort(a.begin(), a.end(), compare);
}
int WriteData(const string& path, vector<CBenchWorker>& a)
{
	ofstream outFile(path);
	if (!outFile)	return 0;
	for (const auto& worker : a)
	{
		outFile << worker << endl;
	}
	outFile.close();
	return 1;
}

int main()
{
	vector<CBenchWorker> a;
	int c;

	if (ReadData("d:\\workers.txt", a) == 0)
		return -1;

	cout << "文件读取后一共有 " << a.size() << " 条钳工数据：" << endl;
	DisplayData(a);

	InecData(a);

	c = DelData(a, 55, 2);	//第2个参数为年龄，第3个参数为等级
	cout << endl << "第1次删除了" << c << "个钳工数据" << endl;

	c = DelData(a, "Tom");
	cout << endl << "第2次删除了" << c << "个钳工数据" << endl;
	SortData(a);
	cout << endl << "上述流程结束后一共有 " << a.size() << " 条钳工数据：" << endl;
	DisplayData(a);

	if (WriteData("d:\\res.txt", a) == 0)
		return -1;
	cout << endl << "文件保存成功" << endl << endl;
}

