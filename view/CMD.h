//
// Created by Alone on 2022-6-5.
//
#pragma once

#include <iostream>
#include <string>
#include <unordered_map>
#include <functional>
#include <BookService.h>

//用于解析运行命令的类
class CMD {
    CMD() = default;

public:
    //定义操作
    std::unordered_map<std::string, std::function<void(std::string const &)>> operations{
            {"query",  doQuery},
            {"delete", doDelete},
            {"add",    doAdd},
            {"update", doUpdate},
            {"clear",  [](std::string const &) {
                system("cls");
            }},
            {"list",   doList},
    };

    static CMD &GetInstance();

    static void Trim(std::string &cmd);

    static void PrintAll();

    void ParseCmd(std::string &cmd);

private:
    static void doQuery(std::string const &book_id);

    static void doList(std::string const &book_id);

    //需要外界再输入书籍其他相关信息，然后组成具体的对象调用Service层添加即可
    static void doAdd(std::string const &book_id);

    //TODO
    static void doDelete(std::string const &book_id);

    //TODO 需要外界输入需要更新的值，然后组成对象实例，调用Service层的方法即可
    static void doUpdate(std::string const &book_id);


    static Book *getBook();
};