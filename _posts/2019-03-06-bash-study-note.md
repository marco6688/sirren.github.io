---
title: bash的基本使用
date: 2019-03-05 16:41:31
categories:
- 读书笔记
tags:
- 读书笔记
- bash
---

Bash（GNU Bourne-Again Shell）是一个为GNU计划编写的Unix shell，它是许多Linux平台默认使用的shell。

shell是一个命令解释器，是介于操作系统内核与用户之间的一个绝缘层。准确地说，它也是能力很强的计算机语言，被称为解释性语言或脚本语言。它可以通过将系统调用、公共程序、工具和编译过的二进制程序”粘合“在一起来建立应用，这是大多数脚本语言的共同特征，所以有时候脚本语言又叫做“胶水语言”

事实上，所有的UNIX命令和工具再加上公共程序，对于shell脚本来说，都是可调用的。Shell脚本对于管理系统任务和其它的重复工作的例程来说，表现的非常好，根本不需要那些华而不实的成熟紧凑的编译型程序语言。

# Hello world

### 创建脚本
1. 打开编辑器 创建hello.sh文件
2. 输入以下代码 

``` sh
 #!/bin/bash
 # This is a comment
 echo Hello World
```
> #! 是说明文件类型，linux是根据“#!”来确定文件类型的
> 第二行的“# This is ……” 是注释，在bash中#是注释的开始
> 第三行的echo的功能是把echo后面的字符串输出到标准输出中去
### 运行脚本

- 使用shell来执行
  $ sh hello.sh
- 使用bash来执行
  $ bash hello.sh
- 使用.来执行
  $ . ./hello.sh
- 使用source来执行
  $ source hello.sh
- 还可以赋予脚本所有者执行权限，允许该用户执行该脚本
  $ chmod u+rx hello.sh
  $  ./hello.sh
