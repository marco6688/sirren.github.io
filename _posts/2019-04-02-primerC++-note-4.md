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

先执行一次循环体，然后检查循环条件

```c++

do{
	statement;
}while(condition)

```

# 跳转语句

跳转语句中断当前执行过程，break、continue、goto和return四种跳转语句

break 负责终止离他最近的迭代语句（while，do while，for，switch）；并从这些语句之后的第一条开始执行

continue 负责终止当前迭代语句的当前迭代并立即开始下一次迭代

goto 是无条件跳转到同一函数的另一条语句

```c++
end:
statement;

goto end;

```
return语句，终止函数的执行

# try语句块和异常处理

- throw表达式，检测异常部分使用了throw表达式来表示他遇到了无法处理的问题。
- try语句块，异常处理部分使用了try语句块处理异常，catch捕获处理
- 一套异常类，用于在throw和catch子句之间传递异常的具体信息

# 标准异常

- exception 定义了通用的异常类，只报告不提供任何额外信息
- stdexcept 定义了几种常用的异常类
- new 头文件定义了had_alloc异常类型
- type_info 头文件定义了had_cast异常类型

类型|错误提示|描述
---|---|---
exception|The most general kind of problem.|最常见的问题。
runtime_error|Problem that can be detected only at run time.|运行时错误：仅在运行时才能检测到问题
range_error|Run-time error: result generated outside the range of
values that are meaningful.|运行时错误：生成的结果超出了有意义的值域范围
overflow_error|Run-time error: computation that overflowed.|运行时错误：计算上溢
underflow_error|Run-time error: computation that underflowed.|运行时错误：计算下溢
logic_error|Problem that could be detected before run time.|逻辑错误：可在运行前检测到问题
domain_error|Logic error: argument for which no result exists.|逻辑错误：参数的结果值不存在
invalid_argument|Logic error: inappropriate argument.|逻辑错误：不合适的参数
length_error|Logic error: attempt to create an object larger than the
maximum size for that type.|逻辑错误：试图生成一个超出该类型最大长度的对象
out_of_range|Logic error: used a value outside the valid range.|逻辑错误：使用一个超出有效范围的值


                                                                                                                                                                                                    




