---
title: "Manipulating Data - 重命名因子水平"
date: 2017-09-23
categories: 
- R
- R-Cookbook
tags:
- R
- levels
---





## 问题

你想要重命名因子水平。



<!-- more -->

## 方案

```R
# 处理一个因子的样例
x <- factor(c("alpha","beta","gamma","alpha","beta"))
x
#> [1] alpha beta  gamma alpha beta 
#> Levels: alpha beta gamma

levels(x)
#> [1] "alpha" "beta"  "gamma"
```

最简单的办法是使用`plyr`包中的`revalue()`或者`mapvalues()`函数。

```R
library(plyr)
revalue(x, c("beta"="two", "gamma"="three"))
#> [1] alpha two   three alpha two  
#> Levels: alpha two three

mapvalues(x, from = c("beta", "gamma"), to = c("two", "three"))
#> [1] alpha two   three alpha two  
#> Levels: alpha two three
```

如果你不想要依赖`plyr`包，你可以使用R的内置函数进行以下处理。注意这些方法会直接修改变量`x`；这说明，你不需要将结果重新赋值回给`x`。

```R
# 通过名字重命名: change "beta" to "two"
levels(x)[levels(x)=="beta"] <- "two"


# 你也可以通过位置重命名，但这种做法比较危险（会因数据变化造成不可控结果），不值得推荐

# 通过因子列表索引重命名: change third item, "gamma", to "three".
levels(x)[3] <- "three"
x
#> [1] alpha two   three alpha two  
#> Levels: alpha two three

# 重命名所有的因子水平
levels(x) <- c("one","two","three")
x
#> [1] one   two   three one   two  
#> Levels: one two three
```

我们可以不使用`plyr`包而通过名字实现因子水平的重命名，但记住这只有在所有的水平都在列表中时才起作用，否则会返回NA以代替寻找不到的因子水平。

```R
# Rename all levels, by name
x <- factor(c("alpha","beta","gamma","alpha","beta"))
levels(x) <- list(A="alpha", B="beta", C="gamma")
x
#> [1] A B C A B
#> Levels: A B C
```

我们也可以使用R的字符串搜索与替换函数去重命名因子水平。注意字符`alpha`周围的`^`与`$`符号是用来确保整个字符串能够匹配（正则表达式）。如果没有它们，字符`alphabet`也能够被成功匹配并会被替换为`onbet`。

```R
# 一个样例
x <- factor(c("alpha","beta","gamma","alpha","beta"))
x
#> [1] alpha beta  gamma alpha beta 
#> Levels: alpha beta gamma

levels(x) <- sub("^alpha$", "one", levels(x))
x
#> [1] one   beta  gamma one   beta 
#> Levels: one beta gamma


# Across all columns, replace all instances of "a" with "X"
levels(x) <- gsub("a", "X", levels(x))
x
#> [1] one   betX  gXmmX one   betX 
#> Levels: one betX gXmmX

# gsub() replaces all instances of the pattern in each factor level.
# sub() replaces only the first instance in each factor level.
```

## 更多参考

匹配向量中值并将其替换为新的值操作类似，参见 [../Mapping vector values](http://www.cookbook-r.com/Manipulating_data/Mapping_vector_values)获取更多信息。

***
原文链接：<http://www.cookbook-r.com/Manipulating_data/Renaming_levels_of_a_factor/>