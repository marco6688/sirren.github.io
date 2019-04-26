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

class Screen
{
public:
    Screen &set(char);
    const Screen &display();

    Screen &display()
    {
        do_display();
        return *this;
    }
    const Screen &display()
    {
        do_display();
        return *this;
    }
private:
    void do_display() const
    {
        cout << this->contents << endl;
    }
};

inline Screen &Screen::set(char c)
{
    contents[cursor] = c;
    return *this;
}
const Screen &display()
{
    cout << this->contents << endl;
    return *this;
}

int main(){

    Screen myScreen(2, 4);
    const Screen blank();
    myScreen.display().set('*'); //对
    blank.display(); //对
    blank.display(); //错
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


