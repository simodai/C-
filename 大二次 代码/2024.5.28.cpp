#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>

using namespace std;

class CBubbleTea {
private:
    static int m_totalCount;  // Ҫ�����������ֵ�����򱨴�
    int m_No;
    int m_type;  // [1,5]
    int m_vol;  // 500, 750, 1000 ��ѡһ

public:
    // ��2�������Ĺ��캯��
    CBubbleTea(int type = 1, int vol = 500);

    // ���ƹ��캯��
    CBubbleTea(const CBubbleTea& t);

    // ��̬��Ա����
    static int get_totalCount() {
        return m_totalCount;
    }

    // ����Ա����
    int get_No() const {return m_No;}
    int get_Type() const {return m_type;}
    int get_Vol() const { return m_vol; }

    // ǰ�������������
    friend CBubbleTea& operator++(CBubbleTea& t1);

    // ��ֵ���������
    CBubbleTea& operator=(const CBubbleTea& t);

    // ��������������
    friend ostream& operator<<(ostream& out, const CBubbleTea& t);
};

// ��ʼ����̬��Ա����
int CBubbleTea::m_totalCount = 0;

// ���캯��
CBubbleTea::CBubbleTea(int type, int vol) {
    if (type >= 1 && type <= 5 && (vol == 500 || vol == 750 || vol == 1000)) {
        m_type = type;
        m_vol = vol;
        m_No = ++m_totalCount;
    }
    else {
        m_type = 0;
        m_vol = 0;
        m_No = 0;
    }
}

// ���ƹ��캯��
CBubbleTea::CBubbleTea(const CBubbleTea& t) {
    if (t.m_No != 0) {
        m_type = t.m_type;
        m_vol = t.m_vol;
        m_No = ++m_totalCount;
    }
    else {
        m_No = 0;
        m_type = 0;
        m_vol = 0;
    }
}

//= ��ֵ���������
CBubbleTea& CBubbleTea::operator=(const CBubbleTea& t) {
    if (this == &t) {
        return *this;
    }

    if (t.m_No == 0) {
        m_No = 0;
        m_type = 0;
        m_vol = 0;
    }
    else {
        m_No = ++m_totalCount;
        m_type = t.m_type;
        m_vol = t.m_vol;
    }
    return *this;
}

// ǰ�������������  friend
CBubbleTea& operator++(CBubbleTea& t1) {
    if (t1.m_No != 0 && t1.m_vol != 1000) {
        t1.m_vol += 250;
    }
    return t1;
}

// �������������� friend
ostream& operator<<(ostream& out, const CBubbleTea& t) {
    if (t.m_No == 0) {
        out << "��Ч����" << endl;
    }
    else {
        string typeStr;
        switch (t.m_type) {
        case 1: typeStr = "Coconut milk tea"; break;
        case 2: typeStr = "Fruit tea"; break;
        case 3: typeStr = "Green tea"; break;
        case 4: typeStr = "Black tea"; break;
        case 5: typeStr = "Coffee"; break;
        default: typeStr = "Unknown"; break;
        }
        out << "********************" << endl
            << "�̲���: " << t.m_No << endl
            << "�̲�����: " << typeStr << endl
            << "�̲�����: " << t.m_vol << " ml" << endl
            << "********************" << endl;
    }
    return out;
}

int main() {
    CBubbleTea tea1(2, 500);
    cout << tea1;
    CBubbleTea tea2(tea1);
    cout << tea2;
    CBubbleTea tea3(2, 5000);
    cout << tea3;
    tea3 = tea2;
    cout << tea3;
    cout << ++tea3;
    cout << "�ϼ�������: " << CBubbleTea::get_totalCount() << "���̲�" << endl;
    return 0;
}
