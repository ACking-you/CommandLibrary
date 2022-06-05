//
// Created by Alone on 2022-6-5.
//
#include "CMD.h"
#include "Menu.h"
#include <sstream>
#include <Timer.h>

//用于解析运行命令的类



CMD & CMD::GetInstance() {
    static CMD cmd;
    return cmd;
}

void CMD::Trim(std::string &cmd) {
    //去除左空格
    cmd.erase(cmd.begin(), find_if(cmd.begin(), cmd.end(), [](int ch) {
        return !isspace(ch);
    }));
    //去除右空格
    cmd.erase(find_if(cmd.rbegin(), cmd.rend(), [](int ch) {
        return !isspace(ch);
    }).base(), cmd.end());
}

void printOne(std::string const& book_id, std::string const& name, std::string const& author, int book_count, int borrow_count)
{
    printf("|%-9s|%-6s|%-8s|%-12d|%-15d|\n", book_id.c_str(), name.c_str(), author.c_str(), book_count, borrow_count);
}

void printGap()
{
    printf("+%s+%s+%s+%s+%s+\n", std::string(9, '-').c_str(), std::string(6, '-').c_str(), std::string(8, '-').c_str(), std::string(12, '-').c_str(), std::string(15, '-').c_str());
}

void CMD::PrintAll()
{
    Timer timer;
    printGap();
    printf("|%-9s|%-6s|%-8s|%-12s|%-15s|\n", "book_id", "name", "author", "book_count", "borrow_count");
    printGap();
    for(auto&& book :BookService::QueryAllBooks())
    {
        printOne(book.book_id, book.name, book.author, book.kBookCount, book.kBorrowerCount);
    }
    printGap();
    std::cout<<"time consume:";
}

void CMD::ParseCmd(std::string &cmd) {
    //每条命令行都是由op指令和需要操作的索书号构成（中间空格隔开
    //解析参数
    std::stringstream in;
    in << cmd;
    std::string op, book_id;
    std::getline(in, op, ' ');
    std::getline(in, book_id);
    //根据参数进行具体函数调用
    if (auto iter = operations.find(op);iter != operations.end()) {
        iter->second(book_id);
    } else {
        std::cerr << "Command format error, please re-enter\n";
    }
}

void CMD::doQuery(std::string const &book_id) {
    Timer timer;
    try {
        std::cout << "The results are as follows:\n";
        std::cout << BookService::QueryBookById(book_id) << std::endl;
    } catch (std::runtime_error &e) {
        std::cerr << e.what() << "\n";
    }
    std::cerr<<"Execution time:";
}

void CMD::doList(std::string const& book_id)
{
    Trim(const_cast<std::string&>(book_id));
    if(book_id.empty())
    {
        PrintAll();
    }else
    {
        doQuery(book_id);
    }
}

//需要外界再输入书籍其他相关信息，然后组成具体的对象调用Service层添加即可
void CMD::doAdd(std::string const &book_id) {
    Book* book = nullptr;
    try{
        book = getBook();
    }catch (std::exception const&e){
        std::cerr<<"Error at "<<e.what()<<"\n\n";
        return;
    }
    book->book_id = book_id;
    Timer timer;
    try{
        BookService::AddBook(*book);
    }catch (std::exception const& error){
        std::cerr<<error.what();
        return;
    }
    std::cout<<"Add successfully\n"<<*book;
    std::cout<<"Execution time:"<<std::endl;
}

//TODO
void CMD::doDelete(std::string const &book_id) {
    Timer timer;
    try{
        BookService::DeleteBook(book_id);
    }catch (std::exception const&exception){
        std::cerr<<exception.what();
        return;
    }
    std::cout<<"Execution time:"<<std::endl;
}

//TODO 需要外界输入需要更新的值，然后组成对象实例，调用Service层的方法即可
void CMD::doUpdate(std::string const &book_id) {

}

Book *CMD::getBook() {
    static Book book;
    std::string cmd;
    do{
        cmd = Menu::GetBookInfo("name");
        if(!cmd.empty()){
            book.name = cmd;
        }
    } while (cmd.empty());

    do{
        cmd = Menu::GetBookInfo("author");
        if(!cmd.empty()){
            book.author = cmd;
        }
    } while (cmd.empty());

    do{
        cmd = Menu::GetBookInfo("num");
        if(!cmd.empty()){
            book.kBookCount = std::stoi(cmd);
        }
    } while (cmd.empty());
    book.kBorrowerCount = 0; //添加书籍后，这个borrowCount由用户借阅书籍的动作去改变

    return &book;
}
