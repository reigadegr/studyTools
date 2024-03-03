/* Copyright 2024 reigadegr@gitbub.com
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License. */
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/spdlog.h>

#include <filesystem>
#include <fstream>
#include <iostream>
#include <regex>
#include <string>

#include "k2.hpp"

namespace fs = std::filesystem;

#if defined(_WIN32)
const std::string yarn = "yarn.cmd";
#elif defined(__linux__)
const std::string yarn = "yarn";
#endif

auto vue_projectStart() -> bool;

auto springboot_projectStart() -> bool;

template <typename... Args>
[[maybe_unused]] static void LOG(const Args &...args)
{
    const auto printArg = [&](const auto &arg) { std::cout << arg; };
    (printArg(args), ...);
    std::cout << std::endl;
}

static inline auto oncePrint() -> void
{
    SPDLOG_INFO("Welcome to use projectStarter!");
    SPDLOG_INFO("Project Starter by reigadegr@github");
    SPDLOG_INFO("The software is not allowed for any commercial use");
    SPDLOG_INFO(
        "You can use projectStarter to start your vue project or springboot "
        "project");
    SPDLOG_INFO("\n");
}
static inline auto flutterStart() -> bool
{
    SPDLOG_INFO("Start to running flutter project.");
    int result = system("flutter run");
    // 检查命令是否成功执行
    if (result != 0) {
        SPDLOG_INFO("运行flutter项目时有问题");
        return false;
    }

    return true;
}
static inline auto Determine() -> bool
{
    if (fs::exists("pom.xml")) [[likely]] {
        springboot_projectStart();
        return true;
    }
    if (fs::exists("package.json")) [[likely]] {
        vue_projectStart();
        return true;
    }
    if (fs::exists("pubspec.yaml")) [[likely]] {
        flutterStart();
        return true;
    }

    SPDLOG_INFO("Not found springboot and vue dependency file,or flutter file");
    SPDLOG_INFO("Please make sure you have location in target directory.");
    SPDLOG_INFO("Press any keys to exit.");

    return false;
}

std::string logFile;

void InitLogger(void)
{
    auto logger = spdlog::default_logger();
    if (logFile.empty() == false) {
        auto sink =
            std::make_shared<spdlog::sinks::basic_file_sink_mt>(logFile, false);
        logger->sinks().emplace_back(sink);
    }
    // use SPDLOG_ACTIVE_LEVEL to switch log level
    logger->set_pattern("[%Y年%m月%d日 %H:%M:%S] [%L] %v%$");
}

auto main(int argc, char **argv) -> int
{
    InitLogger();
    // change to UTF-8 characters
#if defined(_WIN32)
    //    system("chcp 65001");
#endif
    SPDLOG_INFO("启动开始...");
    oncePrint();
    Determine();

    SPDLOG_ERROR("Maybe has some error,please try again");
    std::cin.get();
}
