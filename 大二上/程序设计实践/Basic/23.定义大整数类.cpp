/*设计实现大整数类：
题目：设计实现“HugeInteger” 大整数类，实现大整数的加法、输入和输出功能。
*/
#include<iostream>
#include<cmath>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<string>
#include<deque>
#include<iterator>
#include<algorithm>
using namespace std;

class HugeInteger
{
public:
    HugeInteger():num(), negative(false){
    }
    HugeInteger(const long long);
    HugeInteger(const char *);
    HugeInteger(const string);
    HugeInteger(const HugeInteger &x);

    HugeInteger &operator =(const HugeInteger &);
    friend istream &operator >>(istream &,HugeInteger &);
    friend ostream &operator <<(ostream &,HugeInteger);

    //比较操作符
    bool operator > (const HugeInteger &) const;
    bool operator < (const HugeInteger &) const;
    bool operator == (const HugeInteger &) const;
    bool operator >= (const HugeInteger &) const;
    bool operator <= (const HugeInteger &) const;

    //绝对值与取反运算
    friend const HugeInteger abs(const HugeInteger &);
    const HugeInteger operator - () const;

    //四则运算
    const HugeInteger operator + (const HugeInteger &) const;
    const HugeInteger operator - (const HugeInteger &) const;
    const HugeInteger operator * (const HugeInteger &) const;
    const HugeInteger operator / (const long long &) const;

    //取模运算
    const long long operator % (const long long &) const;

private:
    deque<int>num;      //存那些数
    bool negative;      //确定符号
};

//构造函数
HugeInteger::HugeInteger(const long long x)
{
    long long t=abs(x);
    negative = x >= 0 ? false : true;
    while(t > 0)
    {
        num.push_front(t % 10);
        t /= 10;
    }
}
HugeInteger::HugeInteger(const char* str)
{
    unsigned i = str[0] == '-' ? 1 : 0;
    this->negative = (str[0] == '-' ? true : false);
    for(; i < strlen(str); i++)
        num.push_front(str[i] - '0');
}
HugeInteger::HugeInteger(const string str)
{
    unsigned i= str[0] == '-' ? 1 : 0;
    this->negative = (str[0] == '0' ? true : false);
    for(; i < str.length(); ++i)
    {
        num.push_front(str[i] - '0');
    }
}
HugeInteger::HugeInteger(const HugeInteger &x):num(x.num),negative(x.negative){}

//运算
HugeInteger & HugeInteger::operator = (const HugeInteger &x)
{
    negative = x.negative;
    num = x.num;
    return (*this);
}
istream & operator >> (istream & in, HugeInteger &x)
{
    string str;
    in >> str;
    x = str;
    return in;
}
ostream & operator << (ostream &out, HugeInteger x)
{
    if(x.negative) out << '-';
    for(unsigned i = 0; i != x.num.size(); i++)
        out << x.num[i];
    return out;
}

//比较运算
bool HugeInteger:: operator > (const HugeInteger & rhs) const
{
    HugeInteger x = (*this), y = rhs;
    //讨论运算符
    if(!x.negative && y.negative) return true;      //x正y负
    if(x.negative && !y.negative) return false;     //x负y正
    if(x.negative && y.negative) swap(x,y);         //x,y都是负的则交换
    if(x.num.size() > y.num.size()) return true;    //x的位数多
    if(x.num.size() < y.num.size()) return false;   //y的位数多
    for(unsigned i = 0; i != x.num.size(); ++i)
    {
        if(x.num[i] > y.num[i]) return true;
        if(x.num[i] < y.num[i]) return false;
    }

    return false;
}
bool HugeInteger::operator < (const HugeInteger & rhs) const
{
    return rhs > *this;
}
bool HugeInteger::operator == (const HugeInteger & rhs) const
{
    return negative ==rhs.negative && num == rhs.num;
}
bool HugeInteger::operator >= (const HugeInteger & rhs) const
{
    return *this > rhs || *this ==rhs;
}
bool HugeInteger::operator <= (const HugeInteger & rhs) const
{
    return rhs >= *this;
}

//取反与绝对值运算
const HugeInteger abs(const HugeInteger &rhs)
{
    HugeInteger res;
    res.negative = false;
    res.num = rhs.num;
    return res;
}
const HugeInteger HugeInteger::operator - () const
{
    HugeInteger ret = *this;
    ret.negative = !ret.negative;
    return ret;
}

//四则运算
const HugeInteger HugeInteger::operator + (const HugeInteger &y) const
{
    //讨论符号
    if(!this->negative && y.negative) return *this - abs(y);
    if(this->negative && !y.negative) return y - abs(*this);
    if(this->negative && y.negative) return -(abs(*this) + abs(y));
    HugeInteger x = *this, res;
    int temp = 0;
    for(int i = x.num.size() - 1, j = y.num.size()-1;i >= 0||j >= 0;--i, --j)     //加法运算原理：从最后一位两者相加，余数进队列，商进前一位
    {
        int a = i < 0 ? 0 : x.num[i];
        int b = j < 0 ? 0 : y.num[j];
        res.num.push_front((a + b + temp) % 10);    //余数往前放
        temp = (a + b + temp) / 10;         //商
    }
    if(temp != 0)
        res.num.push_front(temp);           //如果最后还有进位，放在最前面
    return res;
}
const HugeInteger HugeInteger::operator - (const HugeInteger &y) const     //减法运算原理：绝对值运算，先倒过来，然后从第一位开始，上下相减，再重新遍历一遍，如果发现负的，加10，前一位减1
{
    //讨论符号
    if(!this->negative && y.negative) return *this + abs(y);
    if(this->negative && !y.negative) return -(abs(*this)+y);
    if(this->negative && y.negative) return abs(y)-abs(*this);
    deque<int>a, b, res;
    HugeInteger ret;
    copy(this->num.begin(), this->num.end(), front_inserter(a));        //倒过来
    copy(y.num.begin(), y.num.end(), front_inserter(b));
    if(y > *this)
    {
        swap(a, b);         //绝对值大的放到a上
        ret.negative = true;
    }
    res.resize(max(a.size(), b.size()) + 5);            //重新定义队列的大小
    for(unsigned i = 0, j = 0;i < a.size() || j < b.size(); ++i, ++j)
    {
        int m = i < a.size() ? a[i] : 0;
        int n = j < b.size() ? b[i] : 0;
        res[i] = m - n;                                 //先减
    }
    for(unsigned i = 0;i < res.size()-1; ++i)
    {
        if(res[i] < 0)
        {
            res[i] = res[i] + 10;                       //如果发现负的，说明不够减，借位
            res[i+1]--;
        }
    }
    while (res.size() >= 2 && res.back() == 0)          //后面的0去掉，因为待会要倒过来才是解，就成了前面的0了
    {
        res.pop_back();
    }
    reverse(res.begin(), res.end());                    //倒过来得到答案
    ret.num = res;
    return ret;
}
const HugeInteger HugeInteger::operator * (const HugeInteger &y) const //乘法原理：先不考虑进位，先存，相应的位相乘，得到最后的结果， 然后满十的往前进
{
    deque<int>a, b, res;
    copy(this->num.begin(), this->num.end(), front_inserter(a));    //倒过来
    copy(y.num.begin(), y.num.end(), front_inserter(b));
    res.resize(a.size() + b.size() + 5);
    for(unsigned i = 0; i < a.size(); ++i)
        for(unsigned j = 0; j<b.size(); ++j)
            res[i+j] = res[i+j] + a[i] * b[j];                      //相应的位上相乘，放好，此时没有考虑进位
    for(unsigned i = 0; i < res.size() - 1; ++i)
    {
        res[i+1] = res[i+1] + res[i] / 10;                          //此时考虑进位
        res[i] = res[i] % 10;                                       //进位之后取余
    }
    while(res.size() && res.back() == 0)                            //去掉前面的0
        res.pop_back();
    reverse(res.begin(), res.end());
    HugeInteger ret;
    ret.negative = this->negative ^ y.negative;                     //符号是两个数异或得来的
    ret.num = res;
    return ret;
}
const HugeInteger HugeInteger::operator / (const long long & rhs) const   //除法运算 从最低位开始，除，如果不够，加一位，再一次，慢慢的往高位
{
    long long temp = 0;
    HugeInteger x = (*this), res;
    res.negative = this->negative ^ (rhs < 0 ? 1 : 0);  //确定符号
    int y = abs(rhs);
    for(unsigned i = 0;i < x.num.size(); ++i)
    {
        temp = temp * 10 + x.num[i];
        res.num.push_back((int)(temp / y));
        temp %= y;
    }
    while (res.num.size() >= 2 && res.num.front() == 0) //把前面的0去掉
        res.num.pop_front();
    return res;
}

//取模运算
const long long HugeInteger::operator % (const long long & y) const
{
    long long res = 0;
    for(unsigned i = 0; i < this->num.size(); ++i)
        res = (res * 10 + this->num[i]) % y;
    return res;
}

int main()
{
   HugeInteger n1( 7654321 );
   HugeInteger n2( 7891234 );
   HugeInteger n3( "99999999999999999999999999999" );
   HugeInteger n4( "1" );
   HugeInteger n5;
   cout << "n1 is " << n1 << "\nn2 is " << n2
      << "\nn3 is " << n3 << "\nn4 is " << n4
      << "\nn5 is " << n5 << "\n\n";
   n5 = n1 + n2;
   cout << n1 << " + " << n2 << " = " << n5 << "\n\n";
   cout << n3 << " + " << n4 << "\n= " << ( n3 + n4 ) << "\n\n";
   n5 = n1 + 9;
   cout << n1 << " + " << 9 << " = " << n5 << "\n\n";
   n5 = n2 + "10000";
   cout << n2 << " + " << "10000" << " = " << n5 << endl;

    return 0;
}