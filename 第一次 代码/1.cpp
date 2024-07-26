#include<iostream>
#include<iomanip>
#include<string>
#include<algorithm>
#include<cmath>
#include <vector>
#include <fstream>
#include <unordered_map>
using namespace std;

struct match
{
	string teamA;//��������	
	int scoreA;//���ӵ÷�
	int scoreB;//�Ͷӵ÷�
	string teamB;//�Ͷ�����
};

struct goal
{
	string team;//��������
	int point;//����
};

//1
bool readInfo(string filename, vector<match>& matchs)//����matchs�������
{
	ifstream file(filename);  //�򿪲����ļ���filename���ļ�  ���� file
	if (!file.is_open())
	{
		return false;
	}
	struct match temp;
	while (file >> temp.teamA >> temp.scoreA >> temp.scoreB >> temp.teamB)
	{
		matchs.push_back(temp);
	}
	file.close();
	return true;
}
//2
void showInfo(vector<match>& matchs, int n = 3)
{
	for (int i = 0; i < n && i < matchs.size(); i++)
	{
		cout << left << setw(12) << matchs[i].teamA
			<< right << setw(3) << matchs[i].scoreA << " : "
			<< left << setw(3) << matchs[i].scoreB
			<< right << setw(12) << matchs[i].teamB << endl;
	}
}
//3
int findMaxGap(vector<match>& matches) {
	int maxGap = 0;
	for (int i = 0; i < 3; i++) {
		int gap = abs(matches[i].scoreA - matches[i].scoreB);
		if (gap > maxGap) {
			maxGap = gap;
		}
	}
	return maxGap;
}
//4
vector<goal> GroupInfo(vector<struct match>& matchs) {  //struct ����ʡ���� ����
	unordered_map<string, int> jifen;

	for (auto& m : matchs) {
		jifen[m.teamA] += 3 * (m.scoreA > m.scoreB) + (m.scoreA == m.scoreB);
		jifen[m.teamB] += 3 * (m.scoreB > m.scoreA) + (m.scoreA == m.scoreB);
	}

	vector<goal> goals;
	for (auto& s : jifen) {
		goals.push_back({ s.first, s.second }); //first�����second����ֵ
	}
	return goals;//����ֵ��һ��  ���Զ���� struct goal
}
//5
int delInfo(vector<goal>& points, double& aver)
{
	int count = 0; // ��¼���ֵ���ƽ���Ķ�������
	int n = points.size();
	for (int i = 0; i < n; i++)
	{
		aver += static_cast<double>(points[i].point);
	}
	aver /= n;
	for (int i = 0; i < points.size(); )//for (int i = 0; i < n; )������һ����Ҫע�⣬���������ƽ��ֵʱ��ѭ��Ӧ��ʹ�� points.size() �����Ǳ��� n��
		//��Ϊ n ֻ���ڼ���ƽ��ֵ֮ǰ points �Ĵ�С�������ɾ��Ԫ��֮�� points �Ĵ�С�����˱仯��ʹ�� n ���ܻᵼ�´���
		//�����������ṩ�Ĵ����У�����ɾ���������ڼ���ƽ��ֵ֮����еģ���������ʹ�� n �ǰ�ȫ�ġ�
	{
		if (static_cast<double>(points[i].point) < aver)
		{
			points.erase(points.begin() + i); // ɾ��λ�ڵ�iλ��Ԫ��
			count += 1;
		}
		else
		{
			i++; // ֻ�е���ɾ��Ԫ��ʱ��������i��ֵ
		}
	}
	return count; // ���ر�ɾ����Ԫ������
}				 //������һ�� points������ ��ֻʣ�� ���ִ���ƽ���� ����goal��string��int��

//6
bool compare(const goal& a, const goal& b)
{
	if (a.point != b.point)
		return a.point > b.point;
	else if (a.team.length() != b.team.length())
		return a.team.length() < b.team.length();
	else
		return a.team < b.team;
}
void sortInfo(vector<goal>& points)
{
	sort(points.begin(), points.end(), compare);
}

//7
void showInfo(vector<struct goal>& points, int n = 8) {
	sortInfo(points);
	if (n == 0) n = 8;
	for (int i = 0; i < points.size() && i < n; i++) {
		struct goal g = points[i];
		cout << setw(3) << left << i + 1
			<< setw(12) << left << g.team
			<< setw(3) << right << g.point << endl;
	}
}
//8
bool writeInfo(const string& filename, const vector<struct goal>& points) {
	ofstream outfil(filename);
	if (!outfil.is_open())
		return false;
	for (const auto& point : points)
		outfil << point.point << " " << point.team << endl;
	outfil.close();
	return true;
}
//9 ����ҳ���ϣ���� value��Сֵ�������� ��Ӧ�ļ��� 
string  getWeakestAwayHome(vector<struct match>& matchs) {
	unordered_map<string, int> dminmark;
	for (vector<match>::iterator m = matchs.begin(); m != matchs.end(); ++m) {
		dminmark[m->teamB] += m->scoreB;
	}
	string weakestTeam;
	int minScore = INT_MAX;			// ��ʼ�� minScore Ϊ�������͵����ֵ 
	for (const auto& team_score : dminmark)
	{
		if (team_score.second < minScore)
		{
			minScore = team_score.second;
			weakestTeam = team_score.first;
		}
	}
	return weakestTeam; // ���ؿͳ��÷����ٵĶ�������

}
int main()
{
	vector<struct match> matchs;
	if (readInfo("D:\\input.txt", matchs) == false)
	{
		cout << "���ļ�ʧ��";
		return -1;
	}
	cout << "����" << matchs.size() << "�������ɼ�" << endl;
	cout << "ǰ����Ϊ:" << endl;
	showInfo(matchs);
	cout << "���ֲ�Ϊ:" << findMaxGap(matchs) << endl;    //3
	vector<struct goal> points = GroupInfo(matchs);         //4?
	cout << "�ϼ���" << points.size() << "֧����";
	double aver = 0;
	cout << "ɾ����" << delInfo(points, aver) << "������" << endl; //5
	cout << "�����ƽ������Ϊ" << aver << endl;

	//sortInfo(points);

	cout << "ǰ8��������Ϣ����\n";
	showInfo(points);												//7
	if (writeInfo("d:\\result.txt", points) == true)				//8
		cout << "�ļ�����ɹ�\n";
	cout << "�ͳ��÷����ٵ������:" << getWeakestAwayHome(matchs);//9
	return 0;
}