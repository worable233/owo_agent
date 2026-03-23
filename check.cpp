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
        app::log(0, "配置文件检查完成");
    }
    else {
        app::log(2,"配置文件不存在!");
        // 写入文件
        std::ofstream file(this->config_path);
        if (file.is_open()) {
            log(0,"config.json 创建成功");
            file << this->default_config.dump(4); // 格式化输出，缩进4空格
            log(0,"config.json 写入成功" );
            log(0,"config.json 路径" + std::string(this->config_path ));
        }
        else {
            log(3,"无法创建文件");
            return 1;
        }

    }
    return 0;
}