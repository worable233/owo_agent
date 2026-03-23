#include <iostream>
// 文件操作
#include <filesystem>
#include <fstream>
#include "single_include/nlohmann/json.hpp"
#include "app.h"

// 成员函数：初始化
int app::check() {
    
    // 配置文件所在路径
    std::filesystem::path dir_path = this->path / "config";

    // 如果不存在文件夹
    if (!std::filesystem::exists(dir_path)) {
        // 创建路径
        std::filesystem::create_directory(dir_path);
    }

    // 加载配置
    bool status = app::loadConfig();

    // 如果存在配置文件
    if (status) {
        app::log(0, "文件检查完成");
    }
    else {
        app::log(2,"文件不存在!");
        // 写入文件
        std::ofstream file(dir_path / "config.json");
        if (file.is_open()) {
            std::cout << "[正常] config.json 创建成功" << std::endl;
            file << this->config.dump(4); // 格式化输出，缩进4空格
            std::cout << "[正常] config.json 写入成功" << std::endl;
            std::cout << "[正常] config.json 路径" << this->config_path << std::endl;
        }
        else {
            std::cerr << "[错误] 无法创建文件" << std::endl;
            return 1;
        }

    }
    return 0;
}