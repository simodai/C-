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
	string m_text; //歌词文本
	int m_min;  //分钟
	int m_sec;	//秒
	int m_cenSec;//百分之一秒数
	static int m_errCount;//记录对象构造失败的次数
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
			continue; // 如果行格式不正确，跳过
		}

		string timePart = line.substr(1, 8); // 提取时间部分 [00:00.00]
		string textPart = line.substr(10);   // 提取歌词部分

		int min = stoi(timePart.substr(0, 2)); // 提取并转换分钟
		int sec = stoi(timePart.substr(3, 2)); // 提取并转换秒
		int cenSec = stoi(timePart.substr(6, 2)); // 提取并转换百分之一秒

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
//		// 解析时间部分
//		if (iss >> d1 >> min >> d2 >> sec >> d3 >> censec >> d4)
//		{
//			// 获取歌词文本部分
//			getline(iss, text);
//
//			// 去掉歌词文本前面的空格
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
	cout << "歌词为【" << ly1.getText() << "】" << endl;
	cout << "时间为【" << ly1.getMin() << ":" << ly1.getSec() << ":" << ly1.getCenSec() << "】" << endl;
	Clyric ly2("Test", 17, 75, 54);
	cout << "对象构造失败次数:" << ly1.getErrCount() << endl;
	cout << "调用前置++后:";
	cout << ++ly1 << endl; //调用前置++
	ly2 = ly1 + 100;
	cout << "调用+运算符后:";
	cout << ly2 << endl;

	vector <Clyric> vec_lyric;
	if (readData("d:\\song.txt", vec_lyric) == false)
	{
		cout << "打开文件失败";
		return -1;
	}
	cout << "合计" << vec_lyric.size() << "句歌词" << endl;
	cout << "前5句歌词为" << endl;
	showData(vec_lyric, 5);
	int count = deleteLyric(vec_lyric);
	cout << "删除了" << count << "句歌词" << endl;
	count = writeLyric("d:\\text.txt", vec_lyric);
	cout << "写入了" << count << "句歌词" << endl;
	cout << "对象构造失败次数:" << ly1.getErrCount() << endl;
	return 1;
}