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
	string teamA;//主队名称	
	int scoreA;//主队得分
	int scoreB;//客队得分
	string teamB;//客队名称
};

struct goal
{
	string team;//队伍名称
	int point;//积分
};

//1
bool readInfo(string filename, vector<match>& matchs)//引用matchs这个向量
{
	ifstream file(filename);  //打开并将文件名filename的文件  读入 file
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
vector<goal> GroupInfo(vector<struct match>& matchs) {  //struct 可以省略吗？ 可以
	unordered_map<string, int> jifen;

	for (auto& m : matchs) {
		jifen[m.teamA] += 3 * (m.scoreA > m.scoreB) + (m.scoreA == m.scoreB);
		jifen[m.teamB] += 3 * (m.scoreB > m.scoreA) + (m.scoreA == m.scoreB);
	}

	vector<goal> goals;
	for (auto& s : jifen) {
		goals.push_back({ s.first, s.second }); //first代表键second代表值
	}
	return goals;//返回值是一个  我自定义的 struct goal
}
//5
int delInfo(vector<goal>& points, double& aver)
{
	int count = 0; // 记录积分低于平均的队伍数量
	int n = points.size();
	for (int i = 0; i < n; i++)
	{
		aver += static_cast<double>(points[i].point);
	}
	aver /= n;
	for (int i = 0; i < points.size(); )//for (int i = 0; i < n; )这里有一点需要注意，就是你计算平均值时的循环应该使用 points.size() 而不是变量 n，
		//因为 n 只是在计算平均值之前 points 的大小，如果在删除元素之后 points 的大小发生了变化，使用 n 可能会导致错误。
		//不过，在你提供的代码中，由于删除操作是在计算平均值之后进行的，所以这里使用 n 是安全的。
	{
		if (static_cast<double>(points[i].point) < aver)
		{
			points.erase(points.begin() + i); // 删除位于第i位的元素
			count += 1;
		}
		else
		{
			i++; // 只有当不删除元素时，才增加i的值
		}
	}
	return count; // 返回被删除的元素数量
}				 //做完这一步 points向量中 就只剩下 积分大于平均的 队伍goal（string，int）

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
//9 如何找出哈希表中 value最小值？并返回 对应的键？ 
string  getWeakestAwayHome(vector<struct match>& matchs) {
	unordered_map<string, int> dminmark;
	for (vector<match>::iterator m = matchs.begin(); m != matchs.end(); ++m) {
		dminmark[m->teamB] += m->scoreB;
	}
	string weakestTeam;
	int minScore = INT_MAX;			// 初始化 minScore 为整数类型的最大值 
	for (const auto& team_score : dminmark)
	{
		if (team_score.second < minScore)
		{
			minScore = team_score.second;
			weakestTeam = team_score.first;
		}
	}
	return weakestTeam; // 返回客场得分最少的队伍名称

}
int main()
{
	vector<struct match> matchs;
	if (readInfo("D:\\input.txt", matchs) == false)
	{
		cout << "打开文件失败";
		return -1;
	}
	cout << "共有" << matchs.size() << "条比赛成绩" << endl;
	cout << "前三条为:" << endl;
	showInfo(matchs);
	cout << "最大分差为:" << findMaxGap(matchs) << endl;    //3
	vector<struct goal> points = GroupInfo(matchs);         //4?
	cout << "合计有" << points.size() << "支队伍";
	double aver = 0;
	cout << "删除了" << delInfo(points, aver) << "个队伍" << endl; //5
	cout << "队伍的平均积分为" << aver << endl;

	//sortInfo(points);

	cout << "前8名队伍信息如下\n";
	showInfo(points);												//7
	if (writeInfo("d:\\result.txt", points) == true)				//8
		cout << "文件保存成功\n";
	cout << "客场得分最少的球队是:" << getWeakestAwayHome(matchs);//9
	return 0;
}