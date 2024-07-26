#include<iostream>
#include<iomanip>
#include<string>
#include<vector>
#include<fstream>
#include<sstream>
using namespace std;

class Record
{
private:
    string m_name;
    int m_hour, m_minute, m_second;
    double m_latitude, m_longitude;
public:
    //2(1).�������캯��
    Record(string name = "noName", int hour = 0, int minute = 0, int second = 0,
        double latitude = 0.0, double longitude = 0.0)
    {
        this->m_name = name;
        this->m_hour = hour;
        this->m_minute = minute;
        this->m_second = second;
        this->m_latitude = latitude;
        this->m_longitude = longitude;
    }
    //(5)�������캯��
    Record(const Record& other)
    {
        this->m_name = other.m_name;
        this->m_hour = other.m_hour;
        this->m_minute = other.m_minute;
        this->m_second = other.m_second;
        this->m_latitude = other.m_latitude;
        this->m_longitude = other.m_longitude;
    }
    // (2)����Ա�������ֱ𷵻����֡�ʱ���֡��롢γ�ȡ�����
    string get_name() const { return m_name; }
    int get_hour() const { return m_hour; }
    int get_minute()const { return m_minute; }
    int get_second()const { return m_second; }
    double get_latitude()const { return m_latitude; }
    double get_longitude()const { return m_longitude; }

    //// ����������г�Ա������   ����   ˽�г�Ա������ֵ
    //void set_time(int hour, int minute, int second) {
    //    m_hour = hour;
    //    m_minute = minute;
    //    m_second = second;
    //}

    //void set_location(double latitude, double longitude) {
    //    m_latitude = latitude;
    //    m_longitude = longitude;
    //}

    //(3)��Ԫ���� ����ǰ++�����ڽ���ǰ�����������1
    friend Record& operator++(Record& r)
     //��������Ԫ����������ûthisָ�룬����һ��Ҫ����
    {
        r.m_second++;
        if (r.m_second >= 60)
        {
            r.m_second = 0;
            r.m_minute++;
            if (r.m_minute >= 60)
            {
                r.m_minute = 0;
                r.m_hour++;
                if (r.m_hour >= 24)
                {
                    r.m_hour = 0;
                }
            }
        }
        return r;
    }
    //(4) ��Ԫ����������+,(��ͬ��++�������ԶԴ���Ĳ���)
    friend Record operator+(const Record& r, double value)
    {
        // ����Ϊ���ɱ�ģ�
        // ������Ӧ�޸Ĳ������������Ƿ���һ���µĽ��
        // ������Ҫ��һ���µ� temp���� record
        Record temp(r);//�ø�ֵ���캯��
        temp.m_latitude += value;
        temp.m_longitude += value;
        return temp;
    }
    //3����<<
    friend ostream& operator<<(ostream& o, const Record& r)
    {
        
        (o << left) << setw(10) << r.m_name << " "
            << right  << setw(2) << r.m_hour << ":"
            << right  << setw(2) << r.m_minute << ":"
            << right  << setw(2) << r.m_second << " "
            << right << setw(20) << fixed << setprecision(10) << r.m_latitude
            << right << setw(20) << fixed << setprecision(10) << r.m_longitude;
        return o;
    }
};

// 4.��д����inputData��������ݵĶ��룬������������vec_record��
void inputData(string& path, vector<Record>& vec_record)
{
    ifstream file(path);
    string line;
    while (getline(file, line))
    {
        istringstream iss1(line);
        string name;
        string time_str;
        // istringstream ������ÿ�ж�ȡ�����ַ��������н�����������
        // istringstream �ṩ������ȡ����� >>�����Է���ش��ж�ȡ����
        int hour, minute, second;
        double latitude, longitude;
        char delimiter;//������

        iss1 >> name>>time_str >> latitude >> longitude;
        istringstream iss2(time_str);
        iss2 >> hour >> delimiter >> minute >> delimiter >> second;


        Record temp(name, hour, minute, second, latitude, longitude);
        vec_record.push_back(temp);
    }
    file.close();
}

// 5.outPut�����ڰ�����vec_record��ǰn��������ʾ
void outPut(vector<Record>& vec_record, int n)
{
    for (int i = 0; i < vec_record.size() && i < n; i++)
    {
        cout << vec_record[i] << endl;
    }
}

// 6. processTime
void processTime(vector<Record>& vec_record)
{
    for (int i = 0; i < vec_record.size();)
    {
        if (!(vec_record[i].get_hour() >= 6 && vec_record[i].get_hour() <= 22))
        {
            vec_record.erase(vec_record.begin() + i);
        }
        else
        {
            i++;
        }
    }
}

// 7. processLocation
void processLocation(vector<Record>& vec_record)
{
    for (int i = 0; i < vec_record.size();)
    {
        vec_record[i] = vec_record[i] + 0.1;
        if (!(vec_record[i].get_latitude() >= 34.0 && vec_record[i].get_latitude() <= 41.0
            && vec_record[i].get_longitude() >= 96.0 && vec_record[i].get_longitude() <= 122.0))
        {
            vec_record.erase(vec_record.begin() + i);
        }
        else
        {
            i++;
        }
    }
}

int main()
{
    Record record1("Randy", 11, 12, 13, 34.15, 117.21);
    Record record2(record1);
    (cout << record2) << endl;

    vector<Record> vec_record;
    string path = "D:\\location.txt";
    inputData(path, vec_record);

    processTime(vec_record);
    cout << "After time processing: " << endl;
    outPut(vec_record, 10);

    processLocation(vec_record);
    cout << "After location processing: " << endl;
    outPut(vec_record, 10);

    return 0;
}
