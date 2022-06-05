//
// Created by Alone on 2022-6-5.
//

#ifndef LIBRARY_MENU_H
#define LIBRARY_MENU_H
#include <string>

//用户菜单界面
class Menu {
public:
    //运行
    static void Run();
    //打印帮助
    static void Help();
    //获取输入
    static std::string GetLine();
    //获取book输入
    static std::string GetBookInfo(const char *info);
};


#endif //LIBRARY_MENU_H
