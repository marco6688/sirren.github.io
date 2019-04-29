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