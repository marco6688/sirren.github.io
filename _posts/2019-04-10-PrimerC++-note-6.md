---
title: PrimerC++-类
date: 2019-04-10 17:59:20
categories:
- 读书笔记
tags:
- 读书笔记
- C++
---

C++语言中我们可以定义自己的数据类型。通过定义新的类型来反映解决问题中的各种概念，可以是我们更容易编写，调试和修改程序。

类的基本思想是**数据抽象**和**封装**，数据抽象是一种依赖**接口**和**实现**分离的编程技术。

# 定义抽象数据类型

设计一个Sales_data类，允许用户直接访问他的数据成员
## 设计类

这个类名由Sales_data组成，包含以下操作

1. isbn成员函数，返回对象的ISBN编号（用来确认是不是同一种书）
2. combine成员函数，用来将一个Sales_data对象加到另外一个对象上
3. add函数，执行两个Sales_data对象相加
4. read函数，将数据从istream读入到Sales_data对象中
5. print函数，将Sales_data对象输出ostream

设计一个类有一个很好的窍门，就是假如已经实现了他，下面代码介绍如何使用这个类

```
Sales_data current; //保存当前求和结果的变量
if(read(cin, current)) //如果有交易输入
{
    Sales_data next; //用于保存下一条交易数据
    while(read(cin, next))
    {
        if(current.isbn() == next.isbn()) //如果是同一种书
        {
            current.combine(next); //加上这个交易额和交易数量
        }
        else
        {
            print(cout, current) << endl; //输出目前这种书的结果
            current = next; //更新书本
        }
    }
    print(cout, current) << endl; //输出最后一条
}
else
{
    cout << "没输入啊" << endl; //提醒用户没输入
}

```

## 定义改进类

根据之前使用的类，添加了成员函数

```
struct Sale_data {
 	//成员函数
    string isbn() const //返回书本isbn号，这里的const待会解释
    {
        return bookNo;
    }
    Sales_data& combine(const Sales_data&); //函数声明
    double avg_price() const; //返回售出书籍的均价，这里的const也待会解释
	
    std::string bookNo;
    unsigned units_sold = 0;
    double revenue = 0.0;
};

//Sale_data的非成员接口函数
Sale_data add (const Sales_data&,const Sales_data&);
std::ostream &print(std:: ostream&,const Sales_data&);
std::istream &read(std:: istream&,const Sales_data&);


```

### 定义成员函数

每个成员都应该在类中声明，但是成员函数体可以定义在类内，也可以定义在类外

>std::string isbn() const { return bookNo;}

和其他函数一样，成员函数也是一个块

### this引入

成员函数是通过**this**的额外隐式参数来访问调用他的那个对象

```
total.isbn();
//等同于
Sales_data::isbn(&tatal);

//
string isbn() const //返回书本isbn号，这里的const待会解释
    {
        return this->bookNo;
    }
```
也就是说当isbn使用bookNo时，他隐式的使用this指向了的成员就像this->bookNo;一样

this形参是隐式定义的，任何手动定义名为this的参数或变量的行为都是非法的，因为this总是指向这个对象，所以this是一个常量指针，我们不允许改变this中的地址。


### const引入

this是隐式的，没有办法可以把它声明为指向常量的指针，于是设计者们想出了这样的办法：把const放在参数列表之后，表示this是一个指向常量的指针，这样的使用const成员函数被称为**常量成员函数**

```
//下面代码说明const是怎么样使用的，this是一个常量指针，isbn是一个常量成员
std::string Sales_data::isbn(const Sales_data *const this){
 	return this->bookNo;
}
```

在不加const情况下，this是一个常量指针，只有他本身的值不变，但是可以改变他所指对象的值，当所指对象是const的时候就会发生错误

> 常量成员函数->常量和非常量对象都可调用
> 普通成员函数->非常量对象可调用

理解上面的内容，就明白const的使用了

### 类的作用域

在类的外部定义成员函数时，穿越函数必须与他的声明匹配。

```
//我们定义一个外部求平局数的函数
double Sales_data::avg_price() const {
	if(units_sold)
		return revenue/units_sold;
	else
		return 0;
}

//我们定义一个返回this对象的函数
Sales:data& Sales_data::combine(const Sales_data &rhs){
	units_sold += rhs.units_sold;
	revenue += ths. revenue;
	return *this;
}

```

## 定义类相关的非成员函数

read和print函数的作用是将数据读到给定的对象中和打印到指定的流中，因为IO类型不能拷贝所以传递的是引用
add函数是接受两个对象值进行相加

```
//输入的信息包括ISBN、售出总数和售出价格
istream &read(istream &is, Sales_data &item)
{
    double price = 0;
    is >> item.bookNo >> item.units_sold >> price;
    item.revenue = price * item.units_sold;
    return is;
}
//输出对象信息
ostream &print(ostream &os,const Sales_data &item){
	os<<item.isbn()<<" "<<item.units_sold<<" "<<item.revenue<<" "<<item.avg_price();
	return os;
}

//相加两个对象
Sales_data add(const Sale_data &lns,const Sale_data &rns){
	Sales_data sum = lhs;
	sum.combine(rhs);
	return sum;
}
```

## 构造函数

每个类都分别定义了其对象初始化的方式，就是通过构造函数来控制其对象的初始化过程；构造函数的任务是：初始化对象的数据成员，只要类的对象被创建，就会执行构造函数

本篇只介绍构造函数的基础知识，构造函数是一个负责的问题，后续篇幅会在做介绍

构造函数的名称和类名相同，构造函数没有返回值，构造函数也有一个形参列表和一个函数体，类可以有多个构造函数
构造函数不能被声明为const，当我们为类创建一个const对象时，知道构造函数完成初始化过程，对象才能取得常量属性构造函数在const对象的构造过程中可以向其中写值

### 默认构造函数

当类中没有定义构造函数，便会执行**默认构造函数**，默认构造函数没有任何实参
默认构造函数按照以下规则初始化类的数据成员

* 如果存在类内的初始值，用它执行默认初始化
* 如果不存在，则执行默认初始化

某些类不适合依赖默认构造函数，原因如下：

* 编译器只有在发现没有构造函数的时候帮我们定义，否则我们定义了其他构造函数将不会执行默认构造函数
* 有些内置或复合数据类型（比如数组和指针），在执行默认构造过程中会得到未定义的值
* 类中包含其他类类型成员，这个成员没有默认构造函数，编译器无法初始化这个成员


现在我们在之前的成员中新建几个构造函数

```
struct Sales_data
{
	//新加的构造函数
    Sales_data() = default;

    Sales_data(const string &s) : bookNo(s) {}

    Sales_data(const string &s, unsigned n, double p) :
            (bookNo(s), units_sold(n), revenue(p*n)) {};

    Sales_data(istream &);
    
    //之前已有函数
    ...;
}
```

> =default

这个是不接受任何实参的默认构造函数，C++11的标准是可以通过=defalult来要求编译器生成构造函数。这个函数在类的内部是内联函数，如果再外部就不是内联的

> 构造函数和初始值列表

```
Sales_data(const string &s) : bookNo(s) {}
//等同于
Sales_data(const string &s){
	bookNo =s;
}
```
> 类的外部定义构造函数

以istream为参数的构造函数需要执行一些实际的操作

```
Sales_data::Sales_data(istream &is)
{
    read(is, *this); //调用原来的read函数从is中读取一条交易信息存入this所指的对象中
}
```

## 拷贝、赋值和析构

类在以下几种情况下会被拷贝

* 初始化变量以及以值得方式传递或返回一个对象
* 当我们使用赋值运算符时会发生对象的赋值操作

当对象不存在时执行销毁动作，比如一个局部变量在创建它的作用快结束时被销毁，当vector对象销毁时其中的存储的对象也会被销毁

当类需要分配类对象之外的资源时，当类被销毁时需要手动释放这些资源

# 访问控制与封装

使用**访问说明符**加强类的封装性：

* 定义在public说明符之后的成员在整个程序内都可以访问
* 定义在private说明符的成员可以被类的成员函数访问，但是不能使用该类的代码访问

```
class Sales_data
{

public:    
    //成员函数
    Sales_data()=default;
    string isbn() const //返回书本isbn号，这里的const待会解释
    {
        return bookNo;
    }
    Sales_data& combine(const Sales_data&); //函数声明
    double avg_price() const; //返回售出书籍的均价，这里的const也待会解释
private:
    //数据成员
    string bookNo; //书号
    unsigned units_sold = 0; //售出册数
    double revenue = 0; //总销售收入
}

```
作为接口的一部分,构造函数和部分成员函数紧跟着public说明符之后，而数据成员和作为实现部分的函数跟在private说明符后面

一个类可以包含0个或者多个说明符，对于每个说明符出现的次数也没有严格的限制。每个说明符指定了接下来的成员访问级别，有效的范围是下一次出现说明符活到达类的结尾处

定义类使用**class**或**struct**,本质上没有区别。唯一的区别是使用class在访问说明符之前的成员是private，使用struct则属性是public

## 友元

Sales_data的数据成员是private的，而函数read、print、add作为类的一部分，但是他们不是类的成员

类可以允许其他类或者函数访问他们的非公有成员，令其他类成为他的**有元**，只需要在增加一条以friend关键字开始的函数声明

```
struct Sales_data
{
    friend istream &read(istream&, Sales_data&);

private:
    //数据成员
    string bookNo; //书号
    unsigned units_sold = 0; //售出册数
    double revenue = 0; //总销售收入

public:
    //成员函数
    string isbn() const //返回书本isbn号，这里的const待会解释
    {
        return bookNo;
    }
    Sales_data& combine(const Sales_data&); //函数声明
    double avg_price() const; //返回售出书籍的均价，这里的const也待会解释
}
istream &read(istream&, Sales_data&) //声明在类外且无作用域符号，为非成员函数
{
    double price = 0;
    is >> item.bookNo >> item.units_sold >> price;
    item.revenue = price * item.units_sold;
    return is;
}

```

友元只能在类的内部声明，并且不受访问修饰符的限制。类内只是声明友元，我们还需再专门对函数进行一次声明

# 类的其他特性

其他特性主要是：类型成员、类型成员类内初始值、可变数据成员、内联成员函数、从成员函数返回*this、关于如何定义类类型及有元类型

## 类成员再探

定义一个类

```C++
class Screen
{
public:
    typedef string::size_type pos; //类型别名，别忘了啊
    Screen() = default //强制生成默认构造函数

    //自定义构造函数，别忘了这个初始化方式
    Screen(pos ht, pos wd, char c): height(ht), width(wd), contents(ht*wd, c){}

    //定义在类内部的成员函数都是隐式的内联函数
    char get() const //别忘了这边的const是干啥的
    {
        return contents[cursor]; //读取光标中的字符
    }

    inline char get(pos ht, pos wd) const; //显式内联声明，重载哦
    Screen &move(pos r, pos c); //函数声明

private:
    pos cursor = 0;
    pos height = 0, width = 0;
    string contents;
};


inline //在类外面定义内联函数
Screen &Screen::move(pos r, pos c)
{
    pos row = r * width; //计算行的位置
    cursor = row + c; //列
    return *this; //返回左值对象
}
//重载get函数
char Screen::get(pos r, pos c) const
{
    pos row = r * width;
    return contents[row + c];
}
//其实在声明和定义处都写inline也可以，推荐在类外面写，更易理解

```

### 可变数据成员

有时会发生我们想修改一个数据成员，即时他是const类型。这时我们用到mutable关键字就可以了

```C++
class Screen
{
public:
    void some_member() const; //成员函数声明

private:
    mutable size_t access_ctr; //mutable即使在const对象内也能被修改
}

void Screen::some_member() const
{
    ++access_ctr; //你看，可以改变吧
};

```

### 类数据成员的初始值

定义好Screen类之后，我们将定义一个窗口管理类并用它表示显示器上的一组Screen，这个类包含Screen类的的vector，每个元素表示一个特定的Screen，在默认情况下，我们希望这个类有一个默认的初始化Screen

```
class Window_mgr
{
private:
    vector<Screen> screens{ Screen(24, 80, ' ') }
}
```

## 返回*this的成员函数

下面添加一些返回this指针的函数

``` c++
class Screen
{
public:
    Screen &set(char);
    const Screen &display();
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
//调用
Screen myScreen;
myScreen.move(4, 0).set('$'); //对吗，为什么
myScreen.display().set('*'); //对吗，为什么
```

上面代码第一个值是返回左值是引用，可以连续调用。第二个值返回的是常量引用，我们无法改变他的值，解决办法是重载。
下面是基于const的重载

```c++
class Screen
{
public:
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
```

## 类类型

每个类定义了一个唯一的类型，即时他们的成员完全一样他们也是两个不同的类型

### 类的声明

类可以像函数那样把申明和定义分离开，我们也能仅声明，不定义

```c++
class Screen;		//Screen类的声明
```

* 一个类在声明之后定义之前是一个**不完全类型**，这时我们知道他是一个类，但是不清楚他到底包含哪些成员
* 对于一个类来说，我们在创建他的对象之前该类必须被定义过，而不能仅仅是声明。否则编译器无法了解这样的对象需要多少存储空间。
* 因为一个类被声明过了，所以编译器知道他指针和引用，但是不知道他的存储空间。所以类在定义之前他的成员不是是他自己 ，但是可以使他的指针和引用

## 友元再探

### 我们可以指定一个类为另一个类的友元类

```c++
class Screen
{
    friend class Window_mgr;    
    //Window_mgr可以访问Screen所有成员
}
```

### 令其成员为其友元

```c++
class Screen
{
    friend void Window_mgr::clear();    
    //这里是跟人家的成员函数做朋友
}
```

### 函数重载和友元

尽管重载函数的名字相同，但是他们是两个不同的函数。如果一个类想把一组重载函数声明成他的友元，他需要对这组函数中的每一个分别声明


### 友元声明和作用域

当我们声明一个友元函数时，当前作用域中可以不包含这个函数，但是定义这个函数的时候其中使用的要包含在当前作用域中

```c++
struct X
{
    friend void f(){} //友元函数，定义在类内部
    X(){ f(); } //默认构造函数调用f
    //这种调用时错误的，因为f没有被声明

    //俩成员函数的声明
    void g();
    void h();
}

void X::g(){f();} //错误，f没有被声明
void f(); //好，现在声明了
void X::h() {f();} //这样就对了
```

# 类的作用域

每个类都有自己的作用域，在类的作用域之外，普通的数据和函数成员只能由对象、引用或者指针使用成员访问运算符来访问

```c++
Screen::pos ht = 24, wd = 80;
Screen scr(ht, wd, ' '); //调用构造函数实例化一个对象scr
Screen *p = &scr; //p是指向对象的指针
char c = scr.get(); //通过scr对象，调用成员函数get去获取字符
c = p->get(); //通过指针调用get函数
```

下面给Window_mgr类添加一个成员函数，返回刚加入数据的id

```
class Window_mgr
{
public:
    //向窗口添加一个Screen，返回它的编号
    ScreenIndex addScreen(const Screen&);
};
Window_mgr::ScreenIndex Window_mgr::addScreen(const Screen &s)
{
    screens.push_back(s);
    return screens.size()-1;
}
```

## 名字查找与类的作用域

**名字查找**是寻找所用名字最佳匹配的声明过程

1. 首先会在名字所在的快中寻找声明语句，只考虑名字在使用之前的声明
2. 没有找到回去查找外层作用域
3. 最终没有找到会报错

对于类内部的成员函数来说，解析其中的名字与上述的查找规则有所区别

1. 首先，编译成员的声明
2. 直到类全部可见的时候才编译函数体

### 用于类成员声明的名字查找

上面只适用于成员函数中使用的名字，声明中使用的名字包括返回类型和形参列表使用的名字都必须确保使用前可见，如果某个类中使用的类中尚未出现的名字，编译器会在定义该类的作用域中继续查找

内层作用域可以重新定义外层作用域的名字，即时该名字在内层作用域中是用过。然而在类中，如果成员使用外层作用域中的名字，而改名字代表一种类型，二值化不能再之后重新定义该名字

```
typedef double Money;
string bal = "a";
class Accout
{
public:
    Money balance()
    {
        return bal;			//使用的是类内的成员变量，返回1
    }
private:
    Money bal = 1;
    typedef double Money; //这样不行的，重新定义类型不能覆盖，是错误的行为
    //但是编译器并不会报错，所以要自己小心
};
```

### 成员定义中的普通块作用域的名字查找

成员函数使用的名字按照以下解析：

1. 在成员函数内查找该属性的声明，只有函数使用之前出现的声明才会被考虑
2. 成员函数没有找到，再类内继续查找
3. 类内没有找到，去定义类的外层作用域找

下面代码说明成员作用域：

```
int height = 1;
class Screen
{
public:
    typedef string::size_type pos;
    void f(pos height)
    {
        cursor = width * height; //这里的height是形参，会覆盖类成员
    }
private:
    pos cursor = 0;
    pos height = 0, width = 0;
};
```

如果我们要强制使用类成员，第一种我们可以改变形参名称，第二种是我们使用类运算符指定成员

```c++
void f(pos height)
{
	cursor = width * this->height; 	//使用this操作符
	cursor = width * Screen::height; 	//使用类属性
}
```

使用类作用域之外的成员，在外围的作用域查找

```
void Screen::f(pos height)
{
    cursor = width * ::height; //用的是外面那个全局的
}

```

# 构造函数再探

前面对构造函数有了一些认识，下面介绍构造函数的一些其他功能

## 构造函数初始值列表

### 构造函数那些时候必须需要初始值

当成员为const或者是引用的时候，必须将其初始化。当成员属于某种类类型，并且该类型没有定义默认构造函数时，也必须将这个成员初始化

```
class ConstRef
{
public:
    ConstRef(int ii);
private:
    int i;
    const int ci;
    int &ri;
};

ConstRef::ConstRef(int ii)
{
    i = ii; //正确
    ci = ii; //错误：不能给const赋值
    ri = i; //错误：引用没有初始化
}
//我们初始化const或者引用类型的数据成员的唯一机会就是通过构造函数初始值，于是我们可以这么写：
ConstRef::ConstRef(int ii) : i(ii), ci(ii), ri(i){}
```

### 成员初始化顺序

构造函数的初始化顺序与他们类中定义的顺序一致，形参列表只说明初始化成员的值
一般来说，初始化的顺序没有什么特别的要求，但是一个成员需要使用另外的一个成员来进行初始化，这个顺序就很关键了

```
class X
{
    int i;
    int j;
public:
	//未定义的i在j之前被初始化
    X(int val) : j(val), i(j){} 	
};
```

上面代码是错误的，那么下面提供正确的写法

```
X(int val) : i(val), j(val){}
```

### 默认实参和构造函数

一般来说默认构造函数是没有实参的，但是我们可以通过以下写法为默认构造函数添加一个默认实参

```
class Sales_data
{
public:
    Sales_data(string s = "") : bookNo(s){}
}
```

### 委托构造函数

一个委托构造函数使用它所属类的其他构造函数执行他自己的初始化过程

```
class Sales_data
{
public:
    //这是函数一，是一个普通的构造函数
    Sales_data(string s, unsigned cnt, double price) : bookNo(s), units_sold(cnt), revenue(cnt*price){}

    //接下来就是各种偷懒方法了，注意看
    Sales_data(): Sales_data("", 0, 0){} //函数二是默认构造函数，委托函数一帮忙初始化，也可以认为是调用了函数一
    Sales_data(string s): Sales_data(s, 0, 0){} //函数三接受一个string参数，委托函数一帮忙初始化
    Sales_data(istream &is): Sales_data()
    {
        read(is, *this);
    }
    //函数四复杂些，它先委托函数二，就是默认构造函数，函数二去委托函数一，这些函数执行完成后，再执行函数四的函数体
    //调用read函数读取给定的istream
};
```

### 默认构造函数的作用

当对象在默认初始化或值初始化的时自动执行默认构造函数
下面代码说明经常出现的错误：

```
class NoDefault
{
public:
    NoDefault(const string &);
    //定义了构造函数，但没有默认构造函数，而且编译器不会生成，这样这个类本身不会有问题，但是用起来很容易出问题
};

struct A
{
    NoDefault a;
};
A a; //你这样看着挺正常，A没有写构造函数，于是编译器会自动生成默认构造函数去初始化成员变量，可惜啊，这个成员变量的
//类型是类类型NoDefault，而这个该死的类类型又没有默认构造函数，还不让编译器自己生成，于是就报错了

//还有一种错误是这样的：
struct B
{
    B(){}
    NoDefault b;
    //b作为类类型成员，在构造函数没有被初始化，于是它会调用默认构造函数初始化，结果该死的NoDefault没有默认构造函数
};
```

使用构造函数

> Sales_data obj; //注意不要加括号啊，加了括号就成了函数声明了

## 隐式类型转换

如果构造函数只接受一个实参，则它实际上定义了转换为此类类型的隐式转换机制。我们把这种构造函数称为**转换构造函数**

### 类类型转换
该类有一个只接受一个string的构造函数，所以啊，我们可以把string转换为Sales_data类的对象：

```
Sales_data b;
string a = "1";
b.combine(a); //这里a被转换为Sales_data对象，编译器创建了一个临时对象


Sales_data item;
item.combine("1");
//这样是错的，因为字符串常量到string是一步，string到类对象时一步，两步不行的
//不过我们可以用显式地写
item.combine(string("1"));
item.combine(Sales_data("1"))
//总之，隐式的只能帮你一步
```
### 抑制构造函数定义的隐式转换


在转换构造函数（只接受一个实参的构造函数）前加explicit关键字就可以阻止隐式转换，注意，explicit关键字只对类内的转换构造函数有用，而且被声明为explicit的构造函数只能用于直接初始化，不能拷贝初始化
只能在类内声明构造函数时使用explicit关键字，在类外部定义不应重复

```
class Sales_data
{
public:
    Sales_data() = default;
    explicit Sales_data(const string &s): bookNo(s){}
    explicit Sales_data(istream&);
};

Sales_data item;
string b = "1"
item.combine(b); //这样就不行了
explicit Sales_data::Sales_data(istream& is){} //这样也不行，在外面了
Sales_data item1(b); //这样可以
Sales_data item2 = item1; //不行，explicit声明的不能拷贝初始化

//但是，多事C++又说我们还是可以强行转换：
item.combine(Sales_data(b)); //可以
item.combine(static_cats<Sales_data>(cin)); //可以
```

## 聚合类

用户可以直接访问其成员，并且具有特殊的初始化语法形式，称为**聚合类**，需要满足以下条件：

1. 所以成员都是public
2. 没有定义任何构造函数
3. 没有类内初始值
4. 没有基类，也没有virtual函数

下面是一个聚合类：

```
struct Data
{
 int val;
 string s;
};
//实例化
Data a = {0, "a"}; //一定要按类内定义的顺序
```
缺点：

1. 需要所以成员都是public
2. 正确初始化每个成员的任务交给了类的用户（而非作者）。因为用户很容易忘掉某个初始值，或提供了一个不恰当的初始值，所以这样初始化过程冗长乏味且容易出错
3. 添加或删除一个成员，所有的初始化语句都需要更新

## 字面值常量类

数据成员都是字面值类型的聚合类是字面值常量类，如果一个类不是聚合类，但是他符合下述要求，则他是一个字面值常量类：

* 数据成员必须都是字面值类型
* 类必须至少含有一个constexpr构造函数
* 如果数据成员含有类内初始值，则内置类型成员必须是一条常量表达式；或者成员属于某种类类型，则初始值必须使用成员自己的constexpr构造函数
* 类必须使用析构函数的默认定义，该成员负责销毁类的对象


### constexpr构造函数


构造函数不能是const的，但是字面值常量类的构造函数可以是constexpr的，且必须至少有一个constexpr构造函数。 如果不是默认的构造函数，那么constexpr类的构造函数基本就是空函数体，因为以下两点：

constexpr函数的要求是唯一可执行语句时return语句，构造函数不能包含返回语句 所以就只好函数体为空了。 constexpr构造函数必须初始化所有数据成员，初始值或者使用constexpr构造函数或者是一条常量表达式。

```
class Debug
{
public:
    //带有一个默认实参，它也是默认构造函数哦
    constexpr Debug(bool b = true): hw(b), io(b), other(b){}

private:
    bool hw;
    bool io;
    bool other;
};
```

# 类的静态成员

有些时候类需要他的成员与类本身相关，而不是与类的各个对象保持关联，这个时候就需要**静态成员**

## 声明静态成员

我们通过在成员声明之前加上关键字static使其与类关联在一起，静态成员可以被public活private修饰，静态数据成员可以是常量、引用、指针、类类型等

```
class Account
{
public:
    void calculate()
    {
        amaunt += amount * intereatRate;
    }
    static double rate(){return interestRate;}
    static void rate(double);

private:
    string owner;
    double amount;
    static double interestRate;
    static double initRate();
};
```

类的静态成员存在于对象之外，所以啊，每个Account对象只有两个数据成员：owner和amount。只存在一个interestRate对象，而且他被所有Account对象共享

因为静态成员函数不与任何对象绑定，所以没有this指针，不能声明为const的

## 使用类的静态成员

使用类作用域运算符::直接访问：

```
double r;
r = Account::rate();
```

我们还是可以用对象去访问静态成员，毕竟共享

```
Account c1;
Account *ac2 = &ac1;
r = ac1.rate();
r = ac2->rate();
``` 

类内使用不用通过作用域运算符

```
class Account
{
public:
    void calculate()
    {
        amount += amount * intereatRate;
    }

private:
    double amount;
    static double interestRate;
};
```

## 定义静态成员

我们可以在类的内部或者外部定义静态成员，在类的外部定义静态成员时，不能使用static关键字，该
关键字只能出现在类内部的声明语句

静态数据成员不属于类的任何一个对象，所以他不是在创建类的时候被定义的。这意味这他不能通过构造函数初始化。一般我们在类的外部定义和初始化每个静态成员，并且一个静态成员只能被定义一次

类似全部变量，静态数据成员定义在任何但是之外，因为他一旦被定义，就将一直存在于程序的生命周期中

我们来定义一个在类内已经声明的static成员：

```
double Account::interestRate = initRate();
//为什么不用在initRate函数前面加Account::呢
//因为从类名开始，剩下的部分都处于类的作用域之内了。
```

## 静态成员的类内初始化

静态成员提供const整数类型的类内初始值，不过要求静态成员必须是字面常量类型的constexpr。初始值必须是常量表达式，因为这些成员本身就是常量表达式，所以他们能用在适合于常量表达式的地方

```
class Account
{
public:
    static double rate(){return interestRate;}
    static void rate(double);

private:
    static constexpr int period = 30;
    double daily_tbl[period];
};
```

为什么这儿要把初始化放在类内呢？因为period的唯一用途就是去定义daily_tbl的维度，那我们就直接在类内定义一下，外面反正不用。值得注意的是，在外面还是要定义一下，相当于声明一下：

```
constexpr int Account::period; //不带初始值的定义
```

## 静态成员能用于某些场景，而普通成员不行

静态成员独立于任何对象，因此某些非静态数据成员可能非法的场合，静态成员可以使用。

静态数据成员可以是不完全类型，静态数据成员类型可以是他所属的类类型。

```
class Bar
{
    private:
        static Bar m1; //可以自己的类型
        statuc int &m2; //未初始化的引用
};
```

静态数据成员可以作为默认实参

```
class Screen
{
public:
    Screen& clear(char = bkground); //666
private:
    static const char bkground; 
};
```
非静态数据成员不能作为默认实参，因为它是属于对象的，你用对象的值去作为默认实参，结果是无法真正提供一个对象来获取成员的值，会引发错误。