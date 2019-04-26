//
// Created by 任振涛 on 2019/3/20.
//

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