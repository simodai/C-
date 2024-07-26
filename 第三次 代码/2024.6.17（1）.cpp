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
	CAutomobile(const string& Lic, const string& Brand, double Dis)		//���캯��
	{
		m_Lic = Lic;
		m_Brand = Brand;
		m_Dis = Dis;
	}
	string GetLic()const { return m_Lic; }	   //��ȡ����
	string GetBrand()const { return m_Brand; }	//��ȡƷ��
	double GetDis()const { return m_Dis; }		//��ȡ����

	void SetDis(double Dis) { m_Dis = Dis; }	//��������
};

class CTruck : public CAutomobile
{
private:
	double   m_Capacity;//��ػ�������λ����
	int      m_Function;//���;��1��һ��   2��Σ��   3-����
	static int m_Counts;//��������

public:
	//1.���������Ĺ��캯����һ��
	CTruck(const string& Lic = "R00001", const string& Brand = "BENZ", double Dis = 5.0,
		int Function = 1, double Capacity = 20.0) : CAutomobile(Lic, Brand, Dis)
	{
		m_Function = Function;
		m_Capacity = Capacity;
		++m_Counts;
	}
	//2 �������캯��  ������ ��return
	CTruck(const CTruck& other) : CAutomobile(other.GetLic(), other.GetBrand(), other.GetDis())
	{
		m_Function = other.m_Function;
		m_Capacity = other.m_Capacity;
		++m_Counts;
	}
	//3 ��������
	~CTruck()
	{
		--m_Counts;
	}
	//4 ����Ա����
	double GetCapacity() const { return m_Capacity; }
	int GetFunction() const { return m_Function; }
	//5.��̬��Ա����
	static int GetCount() { return m_Counts; }
	//6 ǰ��++
	CTruck& operator++()
	{
		++m_Capacity;
		SetDis(GetDis() + 1);
		return *this;
	}
	//7����++
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
		case 1: functionStr = "һ��"; break;
		case 2: functionStr = "Σ��"; break;
		case 3: functionStr = "����"; break;
		default: functionStr = "δ֪"; break;
		}*/
		if (truck.m_Function == 1) st = "һ��";
		else if (truck.m_Function == 2)st = "Σ��";
		else if (truck.m_Function == 3)st = "����";
		else st = "δ֪";

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
//ReadFile����
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
//ShowTrucks����(1)
void ShowTrucks(const vector<CTruck>& var, int x)  //Ҫ�Ӵ�const��
{
	for (int i = 0; i < var.size(); i++)
	{
		if (var[i].GetFunction() == x)
			cout << var[i] << endl;   //�õ����ص�<<
	}
}
//ShowTrucks����(2)
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
	cout << "�ļ���һ����" << var.size() << "����������" << endl;

	cout << "��;Ϊһ��Ŀ�������:" << endl;
	ShowTrucks(var, 1);

	cout << "Ʒ��Ϊ���۵Ŀ�������:" << endl;
	ShowTrucks(var, "����");

	cout << "��λ����10�ֵ���������ƽ������Ϊ:" << fixed << setw(10) << setprecision(2) << GetAverDis(var, 3, 10.0) << endl;

	CTruck t1;
	cout << t1 << endl;
	cout << t1++ << endl;
	cout << t1 << endl;
	cout << ++t1 << endl;
	cout << t1 << endl;

	CTruck t2(t1);
	cout << t2 << endl;

	cout << "���������ϼ�:" << CTruck::GetCount() << endl;

	return 0;
}


