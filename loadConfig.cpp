#include <iostream>
#include "single_include/nlohmann/json.hpp"
#include "app.h"

// 成员函数：加载配置文件
bool app::loadConfig() {
    // 判断配置文件是否存在
    if (std::filesystem::exists(this->path / "config" / "config.json")) {
        log(0,"文件存在")
    }
    else {
        log(1,"文件不存在!");
        return false;
    }

	return true;
}