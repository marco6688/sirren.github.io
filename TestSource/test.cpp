#include <iostream>
#include <string>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;
int reset(int *p1,int *p2);

int sum_num(vector<int> arr,int &cut );

int main(){

//   vector<string> v5(10,'100');
//    vector<string> mygoal = { "Try", "my", "best" };
//int a1 = 10,b1 = 20;
//
//reset(&a1,&b1);
//cout<<a1<<"-"<<b1<<endl;
vector<int> aa;
aa.push_back(1);
aa.push_back(2);
aa.push_back(3);
aa.push_back(4);
int num = 0;

int a1 = sum_num(aa,num);
std::cout << a1 << ' '<<endl;
std::cout << num << ' '<<endl;

//    while(cin>>line){
//        cout<< "hi:" << endl;
//        cout<< line << endl;
//    }
    return 0;
}

//int iPrint(vector aaa){
//    for(int i=0; i<aaa.size(); ++i)
//    {
//        std::cout << aaa[i] << ' ';
//    }
//    return  0;
//}


int reset(int *p1,int *p2){

//    *p = 0;
//    cout<<p<<endl;
//    cout<<&p<<endl;
//    cout<<*p<<endl;

    int p = 0;
    p =  *p1;
    *p1 = *p2;
    *p2 = p;
    return 0;
}

int sum_num(vector<int> arr,int &cut ){
    int num = 0;
    for(int i=0;i<arr.size();i++){
        num += arr[i];
        cut++;
    }
    return num;
}
