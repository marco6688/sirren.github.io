---
title: PrimerC++-IO库
date: 2019-04-29 17:23:27
categories:
- 读书笔记
tags:
- 读书笔记
- C++
---

C++语言不直接处理输入输出，而是通过一组定义在标准库中的类型来处理IO，这些类型支持从设备读取数据、向设备写入数据的IO操作，设备可以是文件、控制台窗口等

# IO类

为了支持不同的IO操作，标准库除了基本的istream和ostream，还有一些其他的IO类型

iostream	定义了读写流的基本类型
fstream 	定义了读写命名文件的类型
sstream	定义了读写内存string对象类型

|	头文件	|	类型	|
|	---		|	---		|
| iostream|istream，wistream从流读取数据|
|			|ostream，wostream从流写入数据|
|			|iostream，wiostream读写流|
| fstream	|ifstream，wifstream从文件读取数据|
|			|ofstream，wofstream从文件写入数据|
|			|fstream，wfstream读写文件|
| sstream	|istringstream，wistringstream从string读取数据|
|			|ostringstream，wostringstream从string写入数据|
|			|stringstream，wstringstream读写string|

概念上设备类型和字符大小不会影响我们进行IO操作
ifstream和istringstream都是继承istream，所以都是操作都是一样的

## IO对象没有拷贝赋值

由于不能拷贝IO对象，我们不能将返回类型设置为流类型，进行IO操作的函数通常是以引用的方式传递和返回流。读写一个IO对象会改变起状态，因此产地和返回的引用不能使const的

错误示例：

```
ofstream o1, o2;
o1 = o2; //错误：不能赋值

ofstream print(ofstream); //错误：这里是一个print声明，
//后一个ofstream会被初始化，就是拷贝，不行
//前一个是返回类型，返回的时候也会拷贝，不行
```
## 条件状态

IO操作与生俱来的问题就是可能发生错误，IO类定义了一些函数和标志，可以帮我们访问和操纵流的条件状态

![IO库条件状态](/assets/images/2019-04-29IO1.png)
![IO库条件状态](/assets/images/2019-04-29IO2.png)

下面是个错误示范：

```
int ival;
cin >>ival;
```
这段代码是没有错误的，但是我们在标准输入上键入foo，这个与我们预期的int类型有误，cin就会进入错误状态。类似的，我们输入一个文件结束标识，cin也会进入错误状态

一个流发生错误，后续的IO操作都会失败，只有一个流处于无错误状态的时候，我们才可以从他读取数据，向他写入数据。

### 查询流状态

我们可以把流作为条件使用，这样只能告诉我们流是否有效，而无法告诉我们具体发生了什么

IO库定义了一个与机器无关的iostate类型，它提供了表达流状态的完整功能

### 管理条件状态

下面代码展示如何使用条件状态

```
auto old _state = cin.rdstate(); //调用rdstate记住cin的当前状态
cin.clear(); //调用clear函数使cin有效
process_input(cin); //使用cin
cin.setstate(old_state); //将cin置为原有状态
```

clear()会清除所有错误标志位（复位）。

clear还有一个接受一个参数的版本，下面的代码只复位failbit和badbit：

```
cin.clear(cin.rdstate() & ~cin.failbit & ~cin.badbit); //括号内为位运算
```

## 管理输出缓冲区

每个输出流都管理一个缓冲区，用来保存程序读写的数据

文本串可以立即被打印出来，也有可能被操作系统保存到缓冲区，随后在打印。有了缓冲机制，操作系统可以把多个输出操作组合成单一的系统的写操作

导致缓冲刷新的原因有很多：

* 程序正常结束，作为main函数的return操作的一部分，缓冲刷新被执行
* 缓冲区满了，所以要刷新缓冲，以便后来的数据能继续写入缓冲
* 使用例如endl的操作符来显式刷新缓冲区
* 在每个输出操作后，我们可以用unitbuf设置流的内部状态来清空缓冲区。对于cerr来说，unitbuf是默认设置的，因此写到cerr的内容都是立即刷新的
* 一个输出流关联到另一个流时，当读写被关联的流时，关联到的流的缓冲区自动刷新。例如，默认情况下，cin和cerr都关联到cout，因此读cin或者写cerr都会导致cout的缓冲区被刷新

### 刷新输出缓冲区

```
cout << "Hi" << endl; //输出Hi和换行，然后刷新缓冲区
cout << "Hi" << flush; //输出Hi，然后刷新缓冲区
cout << "Hi" << ends; //输出Hi和一个空字符，然后刷新缓冲区
```

### unitbuf 操纵符

```
cout << unitbuf;
//接下来的所有输出都立即刷新，无缓冲
cout << nounitbuf //恢复正常的缓冲方式
```

### 关联输入和输出流

标准库将cout和cin关联起来，所以从cin中读取数据会刷新cout缓冲区

```
ostream *old_tie = cin.tie(nullptr);
//原来cin与cout是默认关联，现在cin不再与其他流关联

cin.tie(&cerr); //cin现在与cerr关联，读取cin会刷新cerr而不是cout了

cin.tie(old_tie); //恢复常态
```
每个流同时最多关联到一个流，但多个流可以同时关联到同一个ostream

# 文件输入输出

头文件fstream定义了三个类型支持文件IO

* ifstream从一个给定文件读取数据
* ofstream向一个给定的文件写入数据
* fstream 可以读写给定文件

![fstream特有操作](/assets/images/QQ20190505-150514@2x.png)

## 使用文件流对象

当我们读写一个文件时，可以定义一个文件流对象，并将对象与文件关联起来

创建文件流对象时，我们可以提供文件名，如果提供了文件名，则open函数自动调用

```
ifstream in(ifile);	//构造一个ifstream并打开给定文件
ofstream out			//输出文件流未关联到任何文件
```

### 使用fsteam代替iostream&

```
ifstream input(record); //打开销售记录文件，关联到input
ofstream output(out); //打开输出文件

Sales_data total; //保存销售额总量
if(read(input, total)) //读取第一条销售记录
{
    Sales_data trans; //保存下一条
    while(read(input, trans))
    {
        if(total.isbn() == trans.isbn())
        {
            total.combine(trans); //同一条，加上去
        }
        else
        {
            print(output, total) << endl; //不同的，输出前一条，刷新缓存
            total = trans; //准备搞下一条
        }
    }
    print(output, total) << endl; //打印最后一条
}
else
{
    cerr << "没数据啊老板" << endl;
}
```

### 成员函数open和close

定义一个空文件流，随后调用open将他与文件关联起来

```
string ifile = "f";
ifstream in(ifile); //构建一个ifstream并打开f文件
ofstream out;
out.open(ifile + "1"); //打开指定文件f1，out与f1关联
if(out) //如果打开成功（文件不能被连续打开）
{
    in.close(); //关闭文件f
    in.open(ifile + "2"); //打开f2文件
}
else
{
    cerr << "文件不存在" << endl;
}
```

### 自动构造和析构

当一个fstream对象离开其作用域时，与之关联的文件会自动关闭

## 文件模式

每一个流都有一个关联的文件模式，用来指出如何使用文件

|操作|文件模式|
|---|---|
| in|以读的方式打开|
| out|以写的方式打开|
| app|每次写操作钱均定位到文件末尾|
| ate|打开文件后立即定位到末尾|
| trunc|截断文件|
| binary|以二进制方式进行IO|

无论以哪种方式打开文件，我们都可以指定的文件模式，指定文件模式有如下限制:

* 只可以对ofstream和fstream对象out模式
* 只可以对ifstream和fstream对象in模式
* 只有当out也被设定是才可以是这trunc模式
* 只要trunc模式没被设定，就可以设置app模式，即时没有显示指定out模式，文件也是以输出方式打开
* 默认情况下即时我们没有指定trunc，以out模式打开的文件也会被截断。为了保留以out打开的文件的内容，我们必须同时指定app模式，这样会把数据追加到文件末尾；或者同时指定in模式，即打开文件同时进行读写操作
* ate和binary模式可用于任何类型文件流并且可以和任何文件模式组合使用

每个文件都定义了一个默认的文件模式，当我们未指定模式时，就会使用默认的文件模式：

文件流类型|模式
---|---
ifstream|in
ofstream|out
fstream|in和out

### 以out模式打开文件会丢弃已有数据

打开ofstream时文件内容会被丢弃，阻止这个操作的方法是指定app模式

```
ofstream app("file1", ofstream::app); 
ofstream app2("file1", ofstream::out | ofstream::app);
//这样就不会被清空了，定位到文件末尾了嘛
```

### 每次调用open时都会确定文件模式


对于一个给定流，每次打开文件，都可以指定其文件模式：

```
ofstream out; //未指定
out.open("f"); //默认为out和trunc
//接下来改变它的模式
out.close(); //先关闭
out.open("f", ofstream::app); 模式为out和app
```
每次打开文件，都要设置文件模式，未指定时就使用默认值

# string 流

文件流类型|模式
---|---
istringstream|从string读取数据
ostringstream|向string写入数据
stringtream|既可以读数据也可以写数据

![stringstream特有操作](/assets/images/QQ20190505-154200@2x.png)

## 使用isteingstream

列出一些人和他们的电话号码，某些人只有一些号码，某些人有多个电话，我们暑促文件可能是这样子：

>renzhentao 19823113333
>renhao 123333 132344

定义类描述输输入数据

```
struct PersonInfo{
	string name;
	vector<string> phones;
}

```

我们程序读取数据文件，并创建一个PersonInfo的vector，vector每个元素对应一条记录。在一个循环处理数据，每一次读取一条数据，提取出名字和若干电话号码

```
string line, word;
vector<PersonInfo> people;
while(getline(cin, line))
{
  PersonInfo info;
  istringstream record(line); //将记录绑定到刚读入的行
  record >> info.name; //读取名字
  while(record >> word) //读取这个人所有电话号码
  {
      info.phones.push_back(word);
  }
  people.push_back(info); //把这个人的信息装进通讯录
}
```

## 使用ostringstream

我们逐步构造输出，希望最后一次打印，我们想逐个验证电话号码并改变其格式。如果所有号码都是有效的我们希望输出一个新的文件，包含改变个时候的电话号码。对于那些无效的号码，我们不会将他输出到新的文件中，而是打印一条错误信息

```
for(const auto &entry : people) //遍历
{
    ostingstream goodNums, badNums; //每步循环创建对象
    for(const auto &nums : entry.phones)
    {
        if(!valid(nums)) //如果号码不合法（我们假定有这个valid函数）
        {
            badNums << " " << nums;
        }
        else
        {
            goodNums << " " << nums;
        }
    }
    if(badNums.str().empty()) //全对，没有错误号码
    {
        os << entry.name << " " << goodNums.str() << endl; 
    }
    else
    {
        cerr << "有错误号码" << entry.name << badNums.str() << endl;
    }
}
```



