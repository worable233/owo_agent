#include <iostream>
// TODO: 文件操作
#include <filesystem>
#include <fstream>
#include "single_include/nlohmann/json.hpp"
#include "app.h"

// 成员函数：log
/*

    用法： app::log(int level,string text);
    int   ：0 -> 普通  1 -> 警告  2 -> 严重警告  3 -> 错误  4 -> 致命错误

*/
int app::log(int level, const std::string& text) {
    // debug
    if (!this->config["debug"]) {
        // 没开启debug直接退出（）
        return 0;
    }

    // 输出 cerr输出无缓冲
    if (level == 0) {
        std::cerr << "[正常]" << text << std::endl;
    }else if (level == 1) {
        std::cerr << "[警告]" << text << std::endl;
    }else if (level == 2) {
        std::cerr << "[严重警告]" << text << std::endl;
    } else if (level == 3) {
        std::cerr << "[错误]" << text << std::endl;
    }else if (level == 4) {
        std::cerr << "[致命错误]" << text << std::endl;
    }
    return 0;
}