#pragma once
// 防止头文件被多次包含
#include <string>
#include <vector>
#include <iostream>
#include <filesystem>
#include "single_include/nlohmann/json.hpp"

// 简化命名空间
using json = nlohmann::json;

// 声明 app 类
class app {
public:
    // 每次发布更新需要修改这个版本号
    std::string version = "1.0.0";

    // 程序所在路径
    std::filesystem::path path = std::filesystem::current_path();
    // config 的路径
    std::filesystem::path config_path = path / "config" / "config.json";

    // 默认的 config
    json default_config = {
    {"version", version},
    {"debug", true},
    {"model", {
        {"name", "Deepseek"},
        {"base_url", "https://api.deepseek.com"},
        {"api_key", "YOUR_API_KEY_HERE"}
    }},
    {"settings", {
        {"timeout", 30},
        {"retry", 3},
        {"model", "deepseek-chat"},
        {"stream", true}
    }}
    };

    // 读取的 config
    json config;

    // 构造函数，防止初始化前日志的debug读不到报错
    app() : config(default_config) {}

    // 静态函数
    int run(int argc, char* argv[]);                      // 主程序
    // 函数
    bool loadConfig();                                        // 读取配置文件
    bool saveConfig();                                        // 保存配置文件
    int log(int title, const std::string& text);      // 日志
    int check();                                                    // 初始化
    int openai();                                                  // openai接口相关

};