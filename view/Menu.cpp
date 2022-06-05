//
// Created by Alone on 2022-6-5.
//

#include "Menu.h"
#include <iostream>
#include <CMD.h>

std::string Menu::GetLine() {
    std::string cmd;
    std::cout<<"library> ";
    std::getline(std::cin,cmd );
    fflush(stdout);
    fflush(stdin);
    CMD::Trim(cmd);
    return cmd;
}

void Menu::Help() {
    printf(R"(Please enter the command operation in the following format:
<op> <book_id>
For example:
query  <book_id>
list   <book_id> 
add    <book_id>  
update <book_id>
delete <book_id>
clear

)");
}

void Menu::Run() {
    printf(R"(Type 'help' for help. Type 'clear' to clear the current input statement.

)");
    std::string cmd;
    do{
        cmd = GetLine();
        if(cmd.empty()){
            continue;
        }
        if(cmd=="help")
        {
            Help();
            continue;
        }
        CMD::GetInstance().ParseCmd(cmd);
        std::cout<<std::endl;
    }while(cmd!="quit"&&cmd!="exit");
}

std::string Menu::GetBookInfo(const char *info) {
    std::string cmd;
    printf("%6s-> ",info);
    std::getline(std::cin,cmd );
    fflush(stdout);
    fflush(stdin);
    CMD::Trim(cmd);
    return cmd;
}

