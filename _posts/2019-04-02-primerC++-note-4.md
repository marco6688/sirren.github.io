---
title: PrimerC++-语句
date: 2019-04-02 16:58:02
categories:
- 读书笔记
tags:
- 读书笔记
- C++
---

C++提供了条件执行语句，重复执行语句和用于中断当前控制流的跳转语句，本篇介绍C++所支持的语句

# 简单语句

C++的语句一般以分号结尾，一个表达式便是一条语句

1. 空语句-最简单的语句只有一个分号
2. 复合语句是指一个作用块内的语句一般在花括号内

# 语句的作用域

可以在if、switch、while和for的控制结构内定义变量，在结构内定义变量，在控制结构中的变量只在相应的语句内可见，一旦语句结束，变量就超出其作用范围了。

# 条件语句

## if语句

if条件的作用就是判断一个指定条件是否为真，根据判断结果执行相应的语句

```c++

if(condition){
	statement1；
}else{
	statement2;
}

```
## switch语句

switch语句提供了一种能在若干条固定选项中做出选择，执行相关的语句

```c++
int a=10；
switch(a){
 case 'a':
 	statement1；
 	break;
 case 'b':
 	statement2；
 	break;
 case 'c':
 	statement3；
 	break;
 default:
 	def statement4；
 	break;
}

```

# 迭代语句

迭代语句又被成为循环语句，重复执行到满足某个条件才停下来

## while语句

只要条件为真，while语句就会重复执行循环体

```c++
while(condition){
	statement;
}

```



## for语句

```c++

for(initializer;condition;expression){
	statement;
}
```
- initializer表述初始化的值，可以有多个初始化
- condition是判断表达式
- expression负责修改initializer变量
- for语句可以省略任意一条语句头，可以以省略掉全部的语句头；

## 范围for语句

C++11引入了更简单的for语句，用来遍历容器或者其他序列的所有元素

```

vector<int> v={1,2,3,4,5,6};
for(auto &r : v){
	r+=2;
}
//等价于
for(auto beg=v.bengin(),end=v.end();beg!=end;++beg){
	auto &r = *beg;
	r+=2;
}

```
## do while语句




