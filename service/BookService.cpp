//
// Created by Alone on 2022-6-5.
//

#include "BookService.h"

void BookService::AddBook(const Book &book) {
    if(BookDAO::getInstance().IsBookExist(book.book_id)){
        throw std::runtime_error("Repeated book_id");
    }
    BookDAO::getInstance().AddBook(book);
}

void BookService::UpdateBook(const Book &book) {
    if(!BookDAO::getInstance().IsBookExist(book.book_id)){
        throw std::runtime_error("Update failed, book does not exist");
    }
    BookDAO::getInstance().UpdateBook(book);
}

Book BookService::QueryBookById(const std::string &book_id) {
    if (!BookDAO::getInstance().IsBookExist(book_id)) {
        throw std::runtime_error("The query failed, the book_id does not exist");
    }
    return BookDAO::getInstance().QueryBookById(book_id);
}

#define BG BookDAO::getInstance()

std::vector<Book> BookService::QueryAllBooks() {
    return BG.QueryAllBooks();
}

void BookService::DeleteBook(const std::string &book_id) {
    if (!BG.IsBookExist(book_id)) {
        throw std::runtime_error("The book_id to be deleted does not exist");
    }
    BG.DeleteBook(book_id);
}
