# owo_agent

一个基于 C++ 的轻量级终端智能助理，可以使用 OpenAI API。
### 现状
基础功能写完啦，等测试完成后发布。✌️
### 待办
使用Lcui框架写出GUI界面。
优化token消耗。_(:з」∠)_

## 架构概览

- 入口：`main.cpp` — 程序启动与主流程。
- 核心：`app.h` / `app.cpp` — 应用逻辑与状态管理。
- OpenAI 客户端：`openai.cpp` — 与 OpenAI API 通信封装。
- 配置与持久化：`saveConfig.cpp` — 保存与加载用户配置。

构建：在 Visual Studio 中打开 `owo_agent.slnx` 并构建。
