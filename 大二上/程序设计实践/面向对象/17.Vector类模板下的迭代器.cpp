#include <iostream>
#include <vector>
using namespace std;

template <class T>
class Vector{
public:
	vector<T> v;
	Vector(){}
	Vector(const Vector<T> &v2):v(v2.v){}       //const保证复制后母Vector不会被改变
	
	int add(T t){
		v.push_back(t);
        return v.size()-1;
	}
	int get_size(){
		return v.size();
	}
	void remove(T m){
		typename vector<T>::iterator it;        //类模板里的迭代器一定要加typename关键字
		for(it=v.begin();it!=v.end();it++){
			if(*it==m){
				v.erase(it);
				break;
			}
		}
	}
	T &operator[](int i){
		if(i<v.size()&&i>=0){
			return v[i];
		}
	}
	
};

int main()
{
    Vector<int> vint;
    int n,m;
    cin >> n >> m;
    for ( int i=0; i<n; i++ ) {
    //    add() can inflate the vector automatically
        vint.add(i);    
    }
    //    get_size() returns the number of elements stored in the vector
    cout << vint.get_size() << endl;
    cout << vint[m] << endl;
    //    remove() removes the element at the index which begins from zero
    vint.remove(m);
    cout << vint.add(-1) << endl;
    cout << vint[m] << endl;
    Vector<int> vv = vint;
    cout << vv[vv.get_size()-1] << endl;
    vv.add(m);
    cout << vint.get_size() << endl;
}
