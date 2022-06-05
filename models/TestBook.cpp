//
// Created by Alone on 2022-6-5.
//
#include <fstream>
#include <iostream>
#include "Book.h"
#include "../../BenchMark/Timer.h"

void Test1() {
    Timer t; //可以bench计时
    //测试book的序列化
    {
        Book book{"book_id", "书名", "作者", 32, 10};
        if (std::ofstream ofs(BOOKS_PATH);ofs) {
            nlohmann::json j;
            j = book;
            ofs << j.dump(4);
        }
    }
    //测试book反序列化
    {
        Book book;
        if (std::ifstream ifs(BOOKS_PATH);ifs) {
            nlohmann::json j;
            ifs >> j;
            j.get_to(book);
        }
        printf("%s,%s,%d,%d\n", book.book_id.c_str(), book.author.c_str(), book.kBookCount, book.kBorrowerCount);
    }
}

void TestBookAdd(std::string const &bookId) {
    Timer timer;
    Book book{bookId, "书名", "作者", 32, 10};
    BookDAO::getInstance().AddBook(book);
    std::cout << BookDAO::getInstance().QueryBookById("book_id");
}

void TestBookDelete() {
    Timer timer;
    BookDAO::getInstance().DeleteBook("book_id");
    std::cout << BookDAO::getInstance().QueryBookById("book_id");
}


int main() {

}