---
title: PrimerC++-字符串、向量和数组
date: 2019-03-20 16:01:32
categories:
- 读书笔记
tags:
- 读书笔记
- C++
---

本篇介绍标准库String、Vector、迭代器和数组

# 命名空间 using 的使用

```c++
#include <iostream>

using std::cin;     //当我们使用cin时，从命名空间std中获取

int main(){

    int i;
    cin >> i;       //正确，通过using声明
    cunt << i;      //错误，没有声明，必须使用完整名称
    std::cunt << i; //正确，从std中使用cout
    return 0;

}

```

- 每个名字都需要独立的using声明
- 头文件中不应包含using声明

# 标准库类型 string

标准库类型string是可变长点string的字符序列，使用string类型必须好汉string头文件

```c++

#include <string>
using std::string;

```

## 定义和初始化string

- 使用等号初始化一个变量是*拷贝初始化*
- 不使用等号则是*直接初始化*

```c++

string s1;              // 默认初始化，s1是一个空串
string s2 = s1;         // 拷贝初始化，s2是s1的副本
string s3 = "hahaa";    // 拷贝初始化，s3内容是字面值“hahaa”
string s4(10,c);        // 直接初始化，s4的内容是10个“c“ 


```

## string对象的操作

| 操作  | 说明 |
|  --- | --- |
| os<<s | 将s写到输出流os当中，返回os |
| is>>s | 从is中读取数据付给s，字符以空白分割，返回s |
| getline(is,s) | 从is中取出1行赋给s |
| s.empty() | s为空则返回true，否则返回false |
| s.size() | 返回s中字符的个数 |
| s.[n] | 返回位置n的字符引用，n从0计 |
| s1+s2 | 返回连接后的结果 |
| s1=s2 | s2的副本替换s1的副本|
| s1==s2 | s1的对象等于s2的对象判断 ，大小写敏感|
| s1!=s2 | - |
| <,<=,>,>= | 利用字符在字典顺序进行比较，并且字母大小写敏感 |

## <cctype>(ctype.h)中字符处理函数

|函数名|说明|
|---|---|
|isalnum | 检查字符是否为字母数字|
|isalpha | 检查字符是否为字母|
|isblank | (c++ 11)	检查字符是否为空格空白|
|iscntrl | 检查字符是否为控制字符|
|isdigit | 检查字符是否为十进制数|
|isgraph | 检查字符是否有图形输出|
|islower | 检查字符是否为小写字母|
|isprint | 检查字符是否能输出|
|ispunct | 检查字符是否为标点|
|isspace | 检查字符是否为区域空白|
|isupper | 检查字符是否为大写字母|
|isxdigit | 检查字符是否为十六进制的数|
|tolower | 将大写字母转换为小写字母|
|toupper | 将小写字母转换为大写字母|

# 标准库类型 vector

标准库*vextor*表示类的集合，其中所有对象的类型都相同，集合中每个对象都有一个与之对应的索引，索引用于访问对象

## vector的使用

```c++

#include <vector>
using std::vector

```

C++ 既有*类模板*也有函数模版，其中vector是一个类模板

## 初始化与赋值

|代码|介绍|
|---|---|
|vector<T> v1|v1是一个空的vector，潜在元素是T类型|
|vector<T> v2(v1)|v2包含有v1的所有元素的副本|
|vector<T> v2=v1|等同于v2(v1)|
|vector<T> v3(n,val)|包含n个重复元素，值是val|
|vector<T> v4(n)|重复了n个初始化对象|
|vector<T> v5{n1,n2,n3...}|包含了n个初始化对象，每个元素都有相应的初始值|
|vector<T>  v6 = {n1,n2,n3...}|等同于v5{n1,n2,n3...}|

## vector 操作

|函数|介绍|
|---|---|
|v.empty()|如果v中不含元素返回真，否则假|
|v.size()|返回v中元素个数|
|v.push_back(t)|在末尾压入一个t的元素|
|v.[n]|返回第n个元素的引用|
|v1=v2|使用v2元素拷贝替换v1|
|v1={z,x,c,v...}|使用指定列表中的元素拷贝替换v1|
|v1==v2|判断v1v2元素个数以及对应位置的元素相同|
|v1!=v2||
|<,<=,>,>=|以字典数据进行比较时间|

# 迭代器

每个元素都有begin和end的成员，begin指向第一个元素（字符），end指向最后一个字符的下一个位置

|迭代器操作|说明|
|---|---|
|*iter| 返回迭代器iter所指元素的引用|
|iter->name|解引用，获取该元素名为name的成员，等价于(*iter).name|
|++iter|指向iter下一个元素|
|++iter|指向iter上一个元素|
|iter1==iter2|判断两个迭代器是否指向同一个元素|
|iter1!=iter2|判断两个迭代器是否指向同一个元素|








