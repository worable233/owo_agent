#include <iostream>
#include <fstream>
#include "single_include/nlohmann/json.hpp"
#include "app.h"

// 成员函数：保存配置文件
bool app::saveConfig() {
    // 打开文件
    std::ofstream file(this->config_path);

    // 如果不能正常打开
    if (!file.is_open()) {
        log(3,"无法写入配置文件: ");
        return false;
    }
    file << this->config.dump(4);  // 格式化保存
    return true;
}