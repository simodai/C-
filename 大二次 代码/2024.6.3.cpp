#include<iostream>
#include<sstream>
#include<iomanip>
#include<vector>
#include<fstream>
using namespace std;
#include<string>

class Clyric
{
private:
	string m_text; //����ı�
	int m_min;  //����
	int m_sec;	//��
	int m_cenSec;//�ٷ�֮һ����
	static int m_errCount;//��¼������ʧ�ܵĴ���
public:
	//1
	Clyric(string text = "", int min = 0, int sec = 0, int cenSec = 0)
	{
		if (text.size() <= 100 && (min >= 0 && min < 60) &&
			(sec >= 0 && sec < 60) && (cenSec >= 0 && cenSec < 100))
		{
			m_text = text;
			m_min = min;
			m_sec = sec;
			m_cenSec = cenSec;
		}
		else
		{
			m_text = "";
			m_min = 0;
			m_sec = 0;
			m_cenSec = 0;
			m_errCount++;
		}
	}
	string getText() const { return m_text; }
	int getMin() const { return m_min; }
	int getSec() const { return m_sec; }
	int getCenSec() const { return m_cenSec; }

	static int getErrCount() { return m_errCount; }

	Clyric& operator++()
	{
		m_cenSec++;
		if (m_cenSec >= 100)
		{
			m_cenSec = 0;
			m_sec++;
			if (m_sec >= 60)
			{
				m_sec = 0;
				m_min++;
				if (m_min >= 60)
				{
					m_min = 0;
				}
			}
		}
		return *this;
	}
	//3
	friend ostream& operator<<(ostream& out, const Clyric& r)
	{
		out << '[' << setfill('0') << setw(2) << r.m_min << ':'
			<< setw(2) << r.m_sec << '.'
			<< setw(2) << r.m_cenSec << ']'
			<< r.m_text;
		return out;
	}
	//4
	friend Clyric operator+(const Clyric& r, int num)
	{
		Clyric temp;
		temp.m_text = r.m_text;
		temp.m_min = r.m_min;
		temp.m_sec = r.m_sec;
		temp.m_cenSec = r.m_cenSec + num;
		if (temp.m_cenSec >= 100)
		{
			temp.m_cenSec -= 100;
			temp.m_sec++;
			if (temp.m_sec >= 60)
			{
				temp.m_sec = 0;
				temp.m_min++;
				if (temp.m_min >= 60)
				{
					temp.m_min = 0;
				}
			}
		}
		return temp;
	}
};
int Clyric::m_errCount = 0;
//5
/* way 1   error  108line 		istringstream iss1(line);
bool readData(string path, vector <Clyric>& vec_lyric)
{
	ifstream file(path);
	if (!file.is_open()) return false;
	string line;
	while (getline(file, line))
	{
		istringstream iss1;
		char d1;
		int min;
		char d2;
		int sec;
		char d3;
		int censec;
		char d4;
		string t;
		iss1 >> d1 >> min >> d2 >> sec >> d3 >> censec >> d4 >> t;

		Clyric temp(t, min, sec, censec);
		vec_lyric.push_back(temp);
	}
	file.close();
	return true;
}*/
bool readData(string path, vector <Clyric>& vec_lyric)
{
	ifstream file(path);
	if (!file.is_open()) return false;
	string line;
	while (getline(file, line))
	{
		istringstream iss1(line);
		iss1.ignore(1);
		int min;
		iss1 >> min;
		iss1.ignore(1);
		int sec;
		iss1 >> sec;
		iss1.ignore(1);
		int censec;
		iss1 >> censec;
		iss1.ignore(1);
		string t;
		iss1>>t;

		Clyric temp(t, min, sec, censec);
		vec_lyric.push_back(temp);
	}
	file.close();
	return true;
}

/* way 2   stoi belongs to <string>
bool readData(string path, vector<Clyric>& vec_lyric)
{
	ifstream file(path);
	if (!file.is_open())
		return false;

	string line;
	while (getline(file, line))
	{
		if (line.size() < 10 || line[0] != '[' || line[9] != ']') {
			continue; // ����и�ʽ����ȷ������
		}

		string timePart = line.substr(1, 8); // ��ȡʱ�䲿�� [00:00.00]
		string textPart = line.substr(10);   // ��ȡ��ʲ���

		int min = stoi(timePart.substr(0, 2)); // ��ȡ��ת������
		int sec = stoi(timePart.substr(3, 2)); // ��ȡ��ת����
		int cenSec = stoi(timePart.substr(6, 2)); // ��ȡ��ת���ٷ�֮һ��

		Clyric temp(textPart, min, sec, cenSec);
		vec_lyric.push_back(temp);
	}
	file.close();
	return true;
}
*/

//way 3
//bool readData(string path, vector<Clyric>& vec_lyric)
//{
//	ifstream file(path);
//	if (!file.is_open()) return false;
//
//	string line;
//	while (getline(file, line))
//	{
//		istringstream iss(line);
//		char d1, d2, d3, d4;
//		int min, sec, censec;
//		string text;
//
//		// ����ʱ�䲿��
//		if (iss >> d1 >> min >> d2 >> sec >> d3 >> censec >> d4)
//		{
//			// ��ȡ����ı�����
//			getline(iss, text);
//
//			// ȥ������ı�ǰ��Ŀո�
//			text.erase(0, text.find_first_not_of(" "));
//
//			Clyric temp(text, min, sec, censec);
//			vec_lyric.push_back(temp);
//		}
//	}
//
//	file.close();
//	return true;
//}

//6
void showData(vector <Clyric>& vec_lyric, int n)
{
	for (int i = 0; i < vec_lyric.size() && i < n; i++)
	{
		cout << vec_lyric[i] << endl;
	}
}
//7
int deleteLyric(vector <Clyric>& vec_lyric)
{
	int count = 0;
	for (int i = 0; i < vec_lyric.size();)
	{
		if (vec_lyric[i].getCenSec() == 0 &&
			vec_lyric[i].getSec() == 0 &&
			vec_lyric[i].getMin() == 0 &&
			vec_lyric[i].getText() == "")
		{
			vec_lyric.erase(vec_lyric.begin() + i);
			count++;
		}
		else
		{
			i++;
		}
	}
	return count;
}
//8
int writeLyric(string newf, vector <Clyric>& vec_lyric)
{
	int count1 = 0;
	ofstream outfile(newf);
	for (int i = 0; i < vec_lyric.size(); i++)
	{
		if (vec_lyric[i].getText() != "")
		{
			count1++;
			outfile<< vec_lyric[i].getText();
		}
	}
	outfile.close();
	return count1;
}

int main()
{
	Clyric ly1("Soochow University", 7, 58, 99);
	cout << "���Ϊ��" << ly1.getText() << "��" << endl;
	cout << "ʱ��Ϊ��" << ly1.getMin() << ":" << ly1.getSec() << ":" << ly1.getCenSec() << "��" << endl;
	Clyric ly2("Test", 17, 75, 54);
	cout << "������ʧ�ܴ���:" << ly1.getErrCount() << endl;
	cout << "����ǰ��++��:";
	cout << ++ly1 << endl; //����ǰ��++
	ly2 = ly1 + 100;
	cout << "����+�������:";
	cout << ly2 << endl;

	vector <Clyric> vec_lyric;
	if (readData("d:\\song.txt", vec_lyric) == false)
	{
		cout << "���ļ�ʧ��";
		return -1;
	}
	cout << "�ϼ�" << vec_lyric.size() << "����" << endl;
	cout << "ǰ5����Ϊ" << endl;
	showData(vec_lyric, 5);
	int count = deleteLyric(vec_lyric);
	cout << "ɾ����" << count << "����" << endl;
	count = writeLyric("d:\\text.txt", vec_lyric);
	cout << "д����" << count << "����" << endl;
	cout << "������ʧ�ܴ���:" << ly1.getErrCount() << endl;
	return 1;
}