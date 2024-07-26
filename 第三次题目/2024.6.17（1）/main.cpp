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
	CAutomobile (const string& Lic, const string& Brand, double Dis)		//构造函数
	{
		m_Lic		= Lic;
		m_Brand		= Brand;
		m_Dis	= Dis;
	}
	string GetLic()const	//获取牌照
	{
		return m_Lic;
	}
	string GetBrand()const	//获取品牌
	{
		return m_Brand;
	}
	double GetDis()const		//获取排量
	{
		return m_Dis;
	}
	void SetDis(double Dis)		//设置排量
	{
		m_Dis = Dis;
	}
};

/******* 请在下面编写你的代码 *******/

/******* 请在上面编写你的代码 *******/

int main()
{
	vector<CTruck> var;
	double aver_dis;

	var = ReadFile("d:\\trucks.txt");
	cout<<"文件中一共有"<<var.size()<<"条卡车数据"<<endl;

	cout<<"用途为一般的卡车如下:"<<endl;
	ShowTrucks(var,1);

	cout<<"品牌为奔驰的卡车如下:"<<endl;
	ShowTrucks(var,"奔驰");

	cout<<"吨位超过10吨的渣土车的平均排量为:"<<fixed<<setw(10)<<setprecision(2)<<GetAverDis(var, 3, 10.0)<<endl;

	CTruck t1;
	cout<<t1<<endl;
	cout<<t1++<<endl;
	cout<<t1<<endl;
	cout<<++t1<<endl;
	cout<<t1<<endl;

	CTruck t2(t1);
	cout<<t2<<endl;

	cout<<"卡车数量合计:"<<CTruck::GetCount()<<endl;

	return 0;
}


