/* 国际贸易统计:
题目：这里给出N个国家之间进行国际贸易的记录，请你统计这些国家进行国际贸易的收益。
输入：第一行给出一个正整数N（≤104），即参与国际贸易的国家数量，则这些国家从1到N编号。随后N行，
    第i行给出编号为i的国家在贸易中卖出商品的记录，格式如下：k N1 P1⋯Nk Pk，其中k(0≤k≤20)是买
    入商品国家的个数，Ni是买入商品国家的编号，Pi>0是其买入商品的金额（整数表示，以万元为单位）。
    注意：一次贸易对于买入和卖出国家的贸易次数都会增加1次。
输出：按照收入金额从高到低的递减顺序输出每个国家的编号和收入金额（整数表示，以万元为单位）。每个
    国家的信息占一行，两数字间有1个空格。如果收入金额有并列，则按参与国际贸易的次数递减输出；如
    果还有并列，则按国家编号递增输出。
*/
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Country
{
public:
    int No;
    int Income;
    int Trade;
    Country(int no=0,int income=0,int trade=0){
        this->No=no;
        this->Income=income;
        this->Trade=trade;
    }
    void Sell(int price,Country &cnt){
        Income+=price;
        Trade+=1;
        cnt.Income-=price;
        cnt.Trade+=1;
    }
    void print(){
        cout<<No<<" "<<Income<<endl;
    }
};
bool compare(Country c1,Country c2){    //涉及并列的排序用if语句
    if(c1.Income!=c2.Income){
        return c1.Income>c2.Income;
    }
    else if(c1.Income==c2.Income&&c1.Trade!=c2.Trade){
        return c1.Trade>c2.Trade;
    }
    else{
        return c1.No<c2.No;
    }
}

int main(){
    int N;
    cin>>N;
    vector<Country> country(N);
    for(int i=0;i<N;i++){
        country[i]=Country(i+1,0,0);    //注意i从0开始，国家编号从1开始
    }
    for(int i=0;i<N;i++){
        int k;
        cin>>k;
        for(int j=0;j<k;j++){
            int n,p;
            cin>>n>>p;
            country[i].Sell(p,country[n-1]);
        }
    }
    sort(country.begin(),country.end(),compare);
    for(int i=0;i<N;i++){
        country[i].print();
    }
    
    return 0;
}