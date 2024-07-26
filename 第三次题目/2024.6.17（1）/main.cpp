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
	string		m_Lic;					//����
	string		m_Brand;			//Ʒ��
	double		m_Dis;					//����

public:
	CAutomobile (const string& Lic, const string& Brand, double Dis)		//���캯��
	{
		m_Lic		= Lic;
		m_Brand		= Brand;
		m_Dis	= Dis;
	}
	string GetLic()const	//��ȡ����
	{
		return m_Lic;
	}
	string GetBrand()const	//��ȡƷ��
	{
		return m_Brand;
	}
	double GetDis()const		//��ȡ����
	{
		return m_Dis;
	}
	void SetDis(double Dis)		//��������
	{
		m_Dis = Dis;
	}
};

/******* ���������д��Ĵ��� *******/

/******* ���������д��Ĵ��� *******/

int main()
{
	vector<CTruck> var;
	double aver_dis;

	var = ReadFile("d:\\trucks.txt");
	cout<<"�ļ���һ����"<<var.size()<<"����������"<<endl;

	cout<<"��;Ϊһ��Ŀ�������:"<<endl;
	ShowTrucks(var,1);

	cout<<"Ʒ��Ϊ���۵Ŀ�������:"<<endl;
	ShowTrucks(var,"����");

	cout<<"��λ����10�ֵ���������ƽ������Ϊ:"<<fixed<<setw(10)<<setprecision(2)<<GetAverDis(var, 3, 10.0)<<endl;

	CTruck t1;
	cout<<t1<<endl;
	cout<<t1++<<endl;
	cout<<t1<<endl;
	cout<<++t1<<endl;
	cout<<t1<<endl;

	CTruck t2(t1);
	cout<<t2<<endl;

	cout<<"���������ϼ�:"<<CTruck::GetCount()<<endl;

	return 0;
}


