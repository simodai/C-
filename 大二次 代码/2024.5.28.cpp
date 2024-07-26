#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>

using namespace std;

class CBubbleTea {
private:
    static int m_totalCount;  // 要在外面给它赋值，否则报错
    int m_No;
    int m_type;  // [1,5]
    int m_vol;  // 500, 750, 1000 三选一

public:
    // 带2个参数的构造函数
    CBubbleTea(int type = 1, int vol = 500);

    // 复制构造函数
    CBubbleTea(const CBubbleTea& t);

    // 静态成员函数
    static int get_totalCount() {
        return m_totalCount;
    }

    // 常成员函数
    int get_No() const {return m_No;}
    int get_Type() const {return m_type;}
    int get_Vol() const { return m_vol; }

    // 前自增运算符重载
    friend CBubbleTea& operator++(CBubbleTea& t1);

    // 赋值运算符重载
    CBubbleTea& operator=(const CBubbleTea& t);

    // 流输出运算符重载
    friend ostream& operator<<(ostream& out, const CBubbleTea& t);
};

// 初始化静态成员变量
int CBubbleTea::m_totalCount = 0;

// 构造函数
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

// 复制构造函数
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

//= 赋值运算符重载
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

// 前自增运算符重载  friend
CBubbleTea& operator++(CBubbleTea& t1) {
    if (t1.m_No != 0 && t1.m_vol != 1000) {
        t1.m_vol += 250;
    }
    return t1;
}

// 流输出运算符重载 friend
ostream& operator<<(ostream& out, const CBubbleTea& t) {
    if (t.m_No == 0) {
        out << "无效数据" << endl;
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
            << "奶茶编号: " << t.m_No << endl
            << "奶茶类型: " << typeStr << endl
            << "奶茶容量: " << t.m_vol << " ml" << endl
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
    cout << "合计生产了: " << CBubbleTea::get_totalCount() << "杯奶茶" << endl;
    return 0;
}
