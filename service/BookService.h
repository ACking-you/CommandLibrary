//
// Created by Alone on 2022-6-5.
//

#ifndef LIBRARY_BOOKSERVICE_H
#define LIBRARY_BOOKSERVICE_H
#include <Book.h>

class BookService {
public:
    static void AddBook(Book const& book);
    static void UpdateBook(Book const&book);
    static Book QueryBookById(std::string const& book_id);
    static std::vector<Book> QueryAllBooks();
    static void DeleteBook(std::string const&book_id);
};


#endif //LIBRARY_BOOKSERVICE_H
