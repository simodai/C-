#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>
#include <algorithm>

using namespace std;

class CAutomobile
{
private:
	string		m_Lic;					//牌照
	string		m_Brand;			//品牌
	double		m_Dis;					//排量

public:
	CAutomobile(const string& Lic, const string& Brand, double Dis)		//构造函数
	{
		m_Lic = Lic;
		m_Brand = Brand;
		m_Dis = Dis;
	}
	string GetLic()const { return m_Lic; }	   //获取牌照
	string GetBrand()const { return m_Brand; }	//获取品牌
	double GetDis()const { return m_Dis; }		//获取排量

	void SetDis(double Dis) { m_Dis = Dis; }	//设置排量
};

class CTruck : public CAutomobile
{
private:
	double   m_Capacity;//额定载货量，单位：吨
	int      m_Function;//额定用途，1：一般   2：危险   3-渣土
	static int m_Counts;//卡车总数

public:
	//1.派生与基类的构造函数不一样
	CTruck(const string& Lic = "R00001", const string& Brand = "BENZ", double Dis = 5.0,
		int Function = 1, double Capacity = 20.0) : CAutomobile(Lic, Brand, Dis)
	{
		m_Function = Function;
		m_Capacity = Capacity;
		++m_Counts;
	}
	//2 拷背构造函数  无类型 无return
	CTruck(const CTruck& other) : CAutomobile(other.GetLic(), other.GetBrand(), other.GetDis())
	{
		m_Function = other.m_Function;
		m_Capacity = other.m_Capacity;
		++m_Counts;
	}
	//3 析构函数
	~CTruck()
	{
		--m_Counts;
	}
	//4 常成员函数
	double GetCapacity() const { return m_Capacity; }
	int GetFunction() const { return m_Function; }
	//5.静态成员函数
	static int GetCount() { return m_Counts; }
	//6 前置++
	CTruck& operator++()
	{
		++m_Capacity;
		SetDis(GetDis() + 1);
		return *this;
	}
	//7后置++
	CTruck operator++(int)
	{
		CTruck temp = *this;
		++(*this);
		return temp;
	}
	//8 <<
	friend ostream& operator<<(ostream& out, const CTruck& truck) {
		string st;
		/*switch (truck.m_Function) {
		case 1: functionStr = "一般"; break;
		case 2: functionStr = "危险"; break;
		case 3: functionStr = "渣土"; break;
		default: functionStr = "未知"; break;
		}*/
		if (truck.m_Function == 1) st = "一般";
		else if (truck.m_Function == 2)st = "危险";
		else if (truck.m_Function == 3)st = "渣土";
		else st = "未知";

		out << setw(10) << right << truck.GetLic()
			<< setw(10) << right << truck.GetBrand()
			<< setw(8) << right << fixed << setprecision(1) << truck.GetDis()
			<< setw(6) << right << st
			<< setw(8) << right << fixed << setprecision(2) << truck.m_Capacity;
		return out;
	}
};

int CTruck::m_Counts = 0;
//
//ReadFile函数
vector<CTruck> ReadFile(const string& filename)
{
	vector<CTruck> trucks;
	ifstream file(filename);
	string line;
	while (getline(file, line))
	{
		stringstream ss(line);
		string lic, brand;
		double dis, capacity;
		int function;
		ss >> lic >> brand >> dis >> function >> capacity;
		trucks.push_back(CTruck(lic, brand, dis, function, capacity));
	}
	file.close();
	return trucks;
}
//ShowTrucks函数(1)
void ShowTrucks(const vector<CTruck>& var, int x)  //要加从const？
{
	for (int i = 0; i < var.size(); i++)
	{
		if (var[i].GetFunction() == x)
			cout << var[i] << endl;   //用到重载的<<
	}
}
//ShowTrucks函数(2)
void ShowTrucks(const vector<CTruck>& var, string brand) {
	for (int i = 0; i < var.size(); i++)
	{
		if (var[i].GetBrand() == brand)
		{
			cout << var[i] << endl;
		}
	}
}
//GetAverDis
double GetAverDis(const vector<CTruck>& var, int y, double x)
{
	double totalDis = 0.0;
	int count = 0;
	for (int i = 0; i < var.size(); i++)
	{
		if (var[i].GetCapacity() >= x && var[i].GetFunction() == y)
		{
			totalDis += var[i].GetDis();
			count++;
		}
	}
	return totalDis / count;
}
int main()
{
	vector<CTruck> var;
	double aver_dis;
	var = ReadFile("d:\\trucks.txt");
	cout << "文件中一共有" << var.size() << "条卡车数据" << endl;

	cout << "用途为一般的卡车如下:" << endl;
	ShowTrucks(var, 1);

	cout << "品牌为奔驰的卡车如下:" << endl;
	ShowTrucks(var, "奔驰");

	cout << "吨位超过10吨的渣土车的平均排量为:" << fixed << setw(10) << setprecision(2) << GetAverDis(var, 3, 10.0) << endl;

	CTruck t1;
	cout << t1 << endl;
	cout << t1++ << endl;
	cout << t1 << endl;
	cout << ++t1 << endl;
	cout << t1 << endl;

	CTruck t2(t1);
	cout << t2 << endl;

	cout << "卡车数量合计:" << CTruck::GetCount() << endl;

	return 0;
}


