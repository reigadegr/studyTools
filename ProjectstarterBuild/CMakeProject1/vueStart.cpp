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

#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <regex>
#include <string>
#include <vector>

#include "clean.hpp"

#if defined(_WIN32)
const std::string yarn = "yarn.cmd";
#elif defined(__linux__)
const std::string yarn = "yarn";
#endif
namespace fs = std::filesystem;

auto shouldRemoveCharacter(const char c) -> bool
{
    return c == '"' || c == ':';
}

static inline auto determineStrExists(const char *inputFile, const char *str)
    -> bool
{
    std::ifstream file(inputFile);
    std::string buf;
    while (std::getline(file, buf)) {
        if (buf.find(str) == std::string::npos) {
            continue;
        }
        file.close();
        // std::puts("��Ϊ�գ�����");
        // system((yarn + " upgrade " + str).c_str());
        return true;
    }
    file.close();

    std::string vstr = str;
    vstr.erase(std::remove_if(vstr.begin(), vstr.end(), shouldRemoveCharacter),
               vstr.end());

    SPDLOG_INFO("{} is not install��start to install...", vstr);
    system((yarn + " add " + vstr).c_str());
    return false;
}

auto vue_projectStart() -> bool
{
    SPDLOG_INFO("Please make sure you have installed Node.js.");

    // init yarn tools
#if defined(_WIN32)
    system("yarn.cmd --version || npm install -g yarn");
#elif defined(__linux__)
    system("yarn --version || pkg install yarn -y");
#endif
    system((yarn + " global add yarn").c_str());
    system((yarn + " config set strict-ssl false").c_str());
    // change repo
    // yarn config set registry https://registry.npm.taobao.org/
    // yarn config set registry https://registry.npmjs.org/
    system((yarn + " config set registry https://registry.npm.taobao.org")
               .c_str());
    system((yarn + " install").c_str());
    // add some packages
    determineStrExists("package.json", "\"element-plus\":");

    determineStrExists("package.json", "\"axios\":");

    determineStrExists("package.json", "\"vue-router\":");

    determineStrExists("package.json", "\"vuex\":");

    determineStrExists("package.json", "\"vue\":");

    determineStrExists("package.json", "\"core-js\":");

    determineStrExists("package.json", "\"jquery\":");

    system((yarn + " serve || " + yarn + " dev || " + yarn +
            " global add @vue/cli && " + yarn + " serve || " + yarn + " dev")
               .c_str());
    clearPath("node_modules");
    return true;
}