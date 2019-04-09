---
title: PrimerC++-函数
date: 2019-04-03 15:42:01
categories:
- 读书笔记
tags:
- 读书笔记
- C++
---

本篇介绍函数的定义声明，以及传参和返回结果，c++中允许重载函数和函数指针的一些知识

# 函数基础

函数是一个命名了的代码块，我们通过调用函数执行获得相应的代码，函数可以有0个或者多个参数，而且会返回一个结果

一个函数由返回类型，函数名字，0个或者多个形参组成的列表和函数体组成。形参由逗号隔开，位于函数名后的小括号内

```c++

//编写一个求数的阶乘程序，n的阶乘是从1到n的乘积

int function fact(int val){
	int ret = 1;
	while(ret>1){
		ret *= val--;
	}
}

//调用函数
int main(){
	int j = fact(10);
	cout<<"10 is:"<<j<<endl;
	return 0 ;
}
```
## 局部函数

在C++中名字有作用域，对象有生命周期

- 名字的作用域是程序文本的一部分，名字在其中可见
- 对象的声明周期是程序执行过程中该对象存在的一段时间

**自动对象**是指普通对象所对应的对象在函数控制路径经过变量定义语句时，创建该对象，当达到定义块末尾时销毁该对象

**局部静态对象**局部变量的生命周期贯穿函数调用及以后的时间

## 函数声明

函数声明和函数定义类型，唯一的区别就是没有函数体

函数可以被定义一次，但可以被多次声明

# 参数传递

当实参是引用类型时，我们称之为**引用传递**，引用形参也是他对应实参的别名

当实参的值拷贝给形参时，形参和实参是两个独立的对象，我们称之为**按值传递**

## 传值参数

指针形参，当执行指针拷贝操作时，拷贝的是指针的值，拷贝之后两个指针是不同的指针，因为指针可以使我们间接的访问他所指的对象，所以通过指针可以修改它所指对象的值

## 传引用参数

拷贝大的类型对象或者容器对象比较低效，甚至有的类类型不知道拷贝操作，当某些对象不支持拷贝操作时，函数只能通过引用形参的方式访问该类的对象

一个对象只能返回一个值，当函数需要返回多个值的时候，我们可以通过按引用传递改变引用对象的值，已达到隐式返回多个值的目的

```

int main(){
	vector<int> aa;
	aa.push_back(1);
	aa.push_back(2);
	aa.push_back(3);
	aa.push_back(4);
	int num = 0;
	int a1 = sum_num(aa,num);
}
int sum_num(vector<int> arr,int &cut ){
    int num = 0;
    for(int i=0;i<arr.size();i++){
        num += arr[i];
        cut++;
    }
    return num;
}

```

## const形参和实参

当用实参初始化形参时会忽略掉顶层const，当形参有顶层const时，传给他常量对象和非常量对象都是可以的

```

void fuc(const int i){
//i可以读取，但是不能更改
}

void fuc(int i){
//错误，重复定义函数
}

```

形参的初始化方式和和变量的初始化方式是一样的

把不会改变的形参定义成引用是一种比较常见的错误，可以将该形参定义成常量引用

## 数组形参

数组有两个特殊性质对定个和使用上有影响。第一个是数组不允许拷贝，使用数组时会转换成其指针。

```
//下面的三个函数是等价的
//每个函数都是一个const int*的形参
void(const int*);
void(const int[0]);
void(const int[10]);


int i=0; j[2] = {1,2};
print(&i);//转换成int *
print(j);//j转换成int * 指向j[0]

```

数组是以指针的形式传递给数组的，所以函数一开始不知道数组的确切大小，调用者应该为此提供一些额外的信息，管理指针形参常用的三个技术

- 使用标记指定数组长度

```C++
void print(const *cp){
	if(cp){
		while(*cp){
			cout<<*cp++;
		}
	}
}

```

- 使用标准库规范


```C++
void print(const int *beg,const int *end){
	while(beg!=end){
		cout<<*beg++;
	}
}

print(j.begin(),j.end());
int j[] = {0,1};


```

- 显示传递一个表示数组大小的形参

```C++

void print(const int ia[],size_t size){
	for(size_t i=0 i!=size;++i){
		cout<<ia[i]<<endl;
	}
}

int j[] = {0,1};
print(j,end(i)-begin(j));

```

- 数组形参和const

当我们不需要对数组形参进行写操作的时候数组形参应该是指向const指针，只有函数再确认改变元素之的时候才把形参定义成非常量指针

- 数组引用形参

C++允许把变量定义成为数组的引用，形参也可以是数组的引用，此时形参绑定到对应的实体上，也就是绑定到数组上

```

void print(int (&arr)[10]){
	for(auto elem:arr){
		cout<<elem<<endl;
	}
}
int i=0;j[2]={0,1};
int k[10]={0,1,2,3,4,5,6,7,8,9};
print(&i);	//错误，实参不是含义10个整数的数组
print(j);		//错误，实参不是含义10个整数的数组
print(k);		//正确


```

- 传递多维数组

C++中没有真正意义的多维数组，和所有数组一样，当将多维数组传递给函数时，真正传递的是首元素的指针

```

//matrix的神明看起来是一个二维数组，实际上形参是包含10个整数的数组的指针。
void print(int (*matrix)[10],int rowSize);
//等价于
void print(int matrix[][10],int rowSize);

```

## main：处理命令行选项

```

//prog -d -o ofile data0
int main(int argc,char *argv[]){}
//因为第二个参数是一个数组，所以也可以使用以下定义
int main(int argc,char **argv){}
//以上示例，argc应该等于5，argv应该是以下表示
argv[0] = "prog";
argv[1] = "-d";
argv[2] = "-o";
argv[3] = "ofile";
argv[4] = "data0";

```

## 含有可变形参的函数

在无法预知应该向函数传递多少个实参的时候，如果所有实参的类型相同可以传递一个名为initializer_list的标准库类型。如果实参的类型不同，可以编写一个特殊的函数，也就是可变参数模版

C++还有一种特殊的形参类型（即省略符），可以用来传递可变实参。以下做简单介绍

### initializer_list 形参

initializer_list是一种标准库类型，用于表示特定类型的值得数组


| 操作 | 描述 |
| --- | --- |
| initializer_list<T> lst; | 默认初始化；T类型元素空列表 |
| initializer_list<T> lst{a,b,c...} | lst的元素数量和初始值一样对；lst的元素对应初始值的副本；列表中的元素是const |
| lst2(lst) | 拷贝和赋值都不会拷贝列表中的元素，拷贝后原始列表和副本共享元素 |
| lst2 = lst | |
| lst.size() | 列表中的元素数量 |
| lst.begin() | lst的首元素指针 |
| lst.end() | lst的尾元素的下一个指针 |



```c++

//定义函数
void error_msg(initializer_list<string> il){
	for (auto beg = li.begin();beg!=li.end();++beg){
		cout<<*beg<<endl;
	}
}
//调用函数，需要传递{}序列

error_msg({"error","bigerror"})

```

### 省略符形参

省略符形参是为了便于C++程序访问某些特殊的C代码而设置的，这写代码使用了varargs的C标准库功能，通常省略符不应该用于其他目的

省略符只能出现在形参列表的最后一个位置

# 返回类型和return语句

return语句是终止当前执行函数并将控制权返回到调用该函数的地方，return有两种形式

- return；
- return expression；

## 无返回值的函数

没有返回值的return语句只能用在返回值是void的函数中，返回void的函数不要求一定有return，这类函数会在函数最后语句隐式的执行return

## 有返回值的函数

只要函数返回类型不是void，则该函数每条return语句必须返回一个值，返回值得类型必须与函数返回类型相同，或者能隐式的转换成函数的返回类型

### 值是如何被返回的

返回一个值和初始化一个变量或者形参是完全一样的，返回值用于初始化调用点的一个临变量，该临变量就是函数的调用结果

```

//该函数返回类型是string，意味这返回值被拷贝到调用点
string make_plural(size_t ctr,const string &word,const string &ending){
	return (ctr>1)?word+ending:word;
}

//该函数返回引用，则该引用是他所引用对象的一个别名
//其中形参和返回类型都是 const string 的引用，不管是调用函数和返回结果都不会真正拷贝string对象。
const string shorterString(const string &s1,const string &s2){
	return s1.size()>=s2.size()?s1:s2;
}

```

### 不要返回局部对象和指针

函数调用结束后所占用的空间会被释放掉，也就意味这函数的局部变量引用将指向不再有效的内存区域

```
//严重错误，该函数试图返回局部对象的引用
const string &mapip(){
	string ret;
	ret = "1234";
	if(ret.empty()){
		return ret;		//错误，返回局部对象的引用
	}else{
		return "Empty";	//错误，返回局部临时变量
	}
}

```

### 返回类类型的函数和调用运算符

调用运算符也有优先级和结合律，调用运算符的优先级与点运算符和箭头运算符相同，并且也复合左结合律。因此，如果函数返回指针、引用或类的对象，我们就能使用韩式调用结果访问结果对象成员

```

//调用string对象的size成员，string对象由函数返回
auto sz = shorterString(s1,s2).size();

```

### 引用返回左值

函数的返回类型决定函数的调用是否是左值。调用一个返回引用的函数得到左值，其他返回类型得到右值。

如果返回类型是常量引用，我们无法为其赋值

```

//返回指定下标的引用
char &get_val(string &str,string::size_type ix){
	return str[ix];
}
string s("a value")；
get_val(s,0) = 'A'; //改变s[0]的值为A

```

### 列表初始化返回值

C++11新标准规定，函数可以返回花括号包围的值的列表

```

vector<string> process(){
	return {"hello","world"};
}

```

### 主函数main的返回值

函数的返回类型不是void那么他必须有一个返回值，但是main函数例外。允许main函数没有return语句直接结束掉，编译器将隐式的插入一条返回0的return语句

### 递归

如果一个函数调用了他的自身，不管是直接调用还是间接调用，都称这种函数为递归函数

## 返回数组指针

数组不能被拷贝，所以函数不能返回数组。不过函数可以返回数组的指针或引用

通过类型别名简化定义数组指针

```
typedef int arrT[10];	//arrT是一个类型别名，他表示的类型是含有10个整数的数组
using arrT = int[10];	//arrT的等价声明

arrT* func(int i);		//func返回含有10个整数的数组的指针

```

### 声明一个返回数组指针的函数

如果想要定义一个返回数组指针的函数，则数组的维度必须跟在函数名字之后，然后函数的形参也应该跟在函数名后，且形参列表应该优先于数组维度。
> Type (\*function(parameter_list))[dimension];
> type是元素类型，dimension表示数组大小，(\*function(parameter_list))两端的圆括号必须存在，没有这对括号返回类型是指针的数组

逐层理解定义
int(*func(int i))[10];

	- func(int i)表示函数传入一个int类型实参
	- *(func(int i)) 表示对函数结果进行解引用操作
	- (*(func(int i)))[10]表示将要得到的大小是10的数组
	- int (*(func(int i)))[10]表示数组中的元素是int类型

### 使用尾置返回类型

C++11新标准中可以使用一种简化上述的func声明，称为位置返回类型

auto func(int i)->int(*)[10];

### 使用decltype

如果我们知道将要返回的结果是哪个数组，就可以使用decltype来声明返回类型,因为返回的是指针，所以还要再声明的时候加一个*解引用

```
int old[] = {1,2,3,4};
int even[] = {5,6,7,8};

decltype(old) *arrPtr(int i){
	return (i%2)?&old:&even;
}

```

# 函数重载

 如果同一个作用域中，函数名字相同但形参列表不同，我们称之为重载函数。
 
 - const形参与重载
 
 const是修饰符，不能区分顶层const和没有顶层const的区别。所以不影响传入的对象。
 如果const是某种引用或者指针，则通过区分指向常量对象还是非常量对象可以实现函数重载，此时的const是底层的
 
 - const_cast与重载

 转换const函数为普通返回值
 
 ```
 const string &shorterString(const string &s1,const string &s2){
 	return s1.size()>=s2.size()?s1:s2;
 }
 
 string &shorterString(string &s1,string &s2){
 	
 	auto r = shorterString(const_cast<const string&>(s1),const_cast<const string&>(s2));
  
  
 	return const_cast<string&>(r);
 }
 
 ```
 
 - 调用重载函数

**函数匹配**是指我们把函数调用与一组函数的某一个关联起来，函数匹配也叫做**重载确定**，匹配会得到三种结果

- 
    - 编译器找到一个**最佳匹配**结果，并生成该调用函数
    - 找不到任何一个函数与调用的实参匹配，编译器发出**无匹配**的错误
    - 存在多个函数可以匹配，但是每一个都不是最佳选择，此时也会发生错误，称为**二义性调用** 




	 



