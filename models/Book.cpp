//
// Created by Alone on 2022-6-5.
//
#include <fstream>
#include <iostream>
#include "Book.h"

using namespace nlohmann;

std::ostream &operator<<(std::ostream& os,Book const& book){
    //直接序列化为json打印
    try{
        json j;
        j = book;
        os<<j.dump(4);
    }catch (std::exception const&e){
        std::cerr<<"Error in cout:\n"<<e.what();
    }
    return os;
}

void from_json(const json &j, Book &book) {
    j["book_id"].get_to(book.book_id);
    j["name"].get_to(book.name);
    j["author"].get_to(book.author);
    j["book_count"].get_to(book.kBookCount);
    j["borrower_count"].get_to(book.kBorrowerCount);
}

void to_json(json &j, const Book &book) {
    j["book_id"] = book.book_id;
    j["name"] = book.name;
    j["author"] = book.author;
    j["book_count"] = book.kBookCount;
    j["borrower_count"] = book.kBorrowerCount;
}

BookDAO::BookDAO() {
    try{
        if(std::ifstream ifs(BOOKS_PATH);ifs){
            json j;
            ifs>>j;
            j["data"].get_to(m_books);
        }
    }catch (const std::exception& error){
        std::cerr<<error.what();
        //这里捕获到异常，肯定是初始化数据出错，你可以添加额外的描述信息
        std::cerr<<"Error initializing books\n";
    }
}

BookDAO::~BookDAO() {
    try{
        if(std::ofstream ofs(BOOKS_PATH);ofs){
            json j;
            j["data"] = m_books;
            ofs<<j.dump(4);
        }
    }catch (std::exception&e){
        std::cerr<<e.what();
        std::cerr<<"Error saving books\n";
    }
}

void BookDAO::AddBook(const Book &book) {
    m_books.push_back(book);
}

void BookDAO::UpdateBook(const Book &book) {
    auto dst = findBookById(book.book_id);
    //抛异常
    if(dst== nullptr)throw std::runtime_error("The book does not exist");
    //更新
    *dst = book;
}

//查询book，找不到返回null，找到返回book则返回其存储在vector中的地址
Book *BookDAO::findBookById(const std::string &book_id) {
    for(auto& book:m_books){
        if(book.book_id == book_id){
            return &book;
        }
    }
    return nullptr;
}

bool BookDAO::IsBookExist(const std::string &book_id) {
    return findBookById(book_id)!= nullptr;
}

Book BookDAO::QueryBookById(const std::string &book_id) {
    Book ret;
    for(auto&& book:m_books){
        if(book.book_id==book_id){
            ret = book;
            break;
        }
    }
    return ret;
}

std::vector<Book> BookDAO::QueryAllBooks() {
    return m_books;
}

void BookDAO::DeleteBook(const std::string &book_id) {
    //remove_if内部实现其实很简单，有兴趣点进去看即可，就是把所有不符合条件的全都移动到最前面，然后返回最后的那个迭代器
    //所以如果想要容器真正的删除，那么后续的元素就是没用的，需要通过它来删除
    auto start = std::remove_if(m_books.begin(), m_books.end(),[&book_id](Book const& book){
        return book.book_id==book_id;
    });
    m_books.erase(start,m_books.end());
}
