//
// Created by Alone on 2022-6-5.
//

#ifndef LIBRARY_BOOK_H
#define LIBRARY_BOOK_H

#include <string>
#include <json.hpp>
#include <vector>
#include "config.h"

//数据模型
struct Book {
    std::string book_id; //书本索书号
    std::string name;   //书本名称
    std::string author; //作者
    int kBookCount; //书本总数量
    int kBorrowerCount; //借阅人数
    friend std::ostream &operator<<(std::ostream &os, Book const &book);
};

void from_json(const nlohmann::json &j, Book &book); //用于反序列化

void to_json(nlohmann::json &j, const Book &book);//用于序列化


//用于对数据进行操作的类
class BookDAO {
    //初始化磁盘的持久化模型 (从磁盘读取过程
    BookDAO();

public:
    //一个单例
    inline static BookDAO &getInstance() {
        static BookDAO dao;
        return dao;
    }

    //以json格式存入磁盘持久化
    ~BookDAO();

public:
    //增删改查
    void AddBook(Book const &book);

    void UpdateBook(Book const &book);

    bool IsBookExist(std::string const &book_id);

    Book QueryBookById(std::string const &book_id);

    std::vector<Book> QueryAllBooks();

    void DeleteBook(std::string const &book_id);

private:
    Book *findBookById(std::string const &book_id);

private:
    std::vector<Book> m_books;
};

#endif //LIBRARY_BOOK_H
