#include <iostream>
#include <filesystem>
#include <cstdlib>
#include <string>
#include <vector>
#include "single_include/nlohmann/json.hpp"
#include "include/curl/curl.h"
#include "app.h"
                                            
// 简化命名空间
using json = nlohmann::json;

// 入口点
int app::run(int argc, char* argv[]) {
	std::string username = this->config["username"];
	// 判断是不是第一次使用
	if (username == "")
	{
		// 引导使用的临时变量
		bool a = false;
		std::string b = "";
		// 进入欢迎引导
		std::cout << std::string(5, '\n') << std::endl;
		std::cout << "Welcome To owoAgent" << std::endl;
		std::cout << "欢迎使用" << std::endl;
		std::cout << std::string(2, '\n') << std::endl;
		std::cout << "已自动为您创建了配置文件," << std::endl;
		std::cout << "请跟随提示进行初步的配置." << std::endl;
		std::cout << std::string(2, '\n') << std::endl;
		// 设置用户名
		while (a != true){
			std::cout << std::string(1, '\n') << std::endl;
			std::cout << "Phase 1 / Step 1" << std::endl;
			std::cout <<"请设置您的用户名:" << std::endl;
			std::cin >> username;
			std::cout << std::string(1, '\n') << std::endl;
			std::cout << "Phase 1 / Step 2" << std::endl;
			std::cout <<"您的用户名为 " << username << "\n您确定使用此用户名吗?( 确定请输入 y )"<< std::endl;
			std::cin >> b;
			if (b == "y" ) {
				a == true;
			}
		};
		std::cout << std::string(2, '\n') << std::endl;
		// 未完待续，懒得继续写了（）
	}
	

	return 0;
}

void app::list_models() {
	// 遍历
    int i = 1;
    for (auto a = this->config["models"].begin(); a != config["models"].end(); ++a) {
		// 获取模型名称
        std::string model_name = a.value().value("name", "未知模型");
		// 直接输出
        std::cout << i << " " << model_name << std::endl;
        i++;
    }
}

// 设置模型
int app::set_model(const std::string& id) {
	std::string models_id = "model_"+id;
	// 检查 config 中是否有 "models" 对象
    if (!this->config.contains("models") || !this->config["models"].is_object()) {
        log(3, "config 中没有有效的 models 对象");
        return 1;
    }

    // 检查传入的 id 是否存在
    if (!this->config["models"].contains(models_id)) {
        log(3, "未找到模型 id: " + id);
        return 2; 
    }

    // 将选中的模型配置赋值给成员变量 model
    this->model["api_key"] = this->config["models"][models_id]["api_key"];
	this->model["base_url"] = this->config["models"][models_id]["base_url"];

    // 可选：输出成功信息
    log(0, "[模型] 已切换到: " + this->config["models"][models_id].value("name", "unknown") + "也就是" +models_id );
    return 0;
}