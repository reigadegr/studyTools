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
#include <spdlog/spdlog.h>

#include <filesystem>
#include <fstream>
#include <iostream>
#include <regex>
#include <string>

namespace fs = std::filesystem;

auto execCmdSync(const char *command) -> std::string
{
    // #分OS的命令

#if defined(_WIN32)
    FILE *pipe = _popen(command, "r");
#elif defined(__linux__)
    FILE *pipe = popen(command, "r");
#endif

    if (pipe == nullptr) {
        return {};
    }
    char buffer[2];
    std::string result;
    while (fgets(buffer, sizeof(buffer), pipe) != nullptr) {
        result += buffer;
    }

#if defined(_WIN32)
    _pclose(pipe);
#elif defined(__linux__)
    pclose(pipe);
#endif
    return result;
}

void readfile(std::string &applicationFile, std::string &result)
{
    if (fs::exists(applicationFile)) {
        std::ifstream file(applicationFile);
        std::string buf;
        while (getline(file, buf)) {
            if (buf.find("port") != std::string::npos) {
                size_t pos = buf.find(":");
                result = buf.substr(pos + 1);
                SPDLOG_INFO("找到了端口号\0");
                file.close();
                return;
            }
        }
    }
    else {
        SPDLOG_INFO("{} ������\0", applicationFile);
    }
}

std::string getFilePath(std::string projrct_root)
{
#if defined(_WIN32)
    std::string fileDirname = projrct_root + "\\src\\main\\resources\\";
#elif defined(__linux__)
    std::string fileDirname = projrct_root + "/src/main/resources/";
#endif
    std::string pattern = "application.*";
    std::regex regex(pattern);

    std::string NewfileName;
    for (const auto &entry : fs::directory_iterator(fileDirname)) {
        std::string filename = entry.path().filename().string();
        if (std::regex_match(filename, regex)) {
            SPDLOG_INFO("发现了文件: {}", filename);
            NewfileName = fileDirname + filename;
            break;
        }
    }
    return NewfileName;
}

void getPort(std::string &port)
{
    // 获取端口
    fs::path currentPath = fs::current_path();
    std::string applicationFile = getFilePath(currentPath.string());
    readfile(applicationFile, port);
}

void killer()
{
    std::string port = "";
    getPort(port);
    const std::string pid = execCmdSync(
        ("for /f \"skip=1 tokens=5\" %i in ('netstat -ano ^| findstr " + port +
         "') do @echo %i")
            .c_str());
    if (pid == "") {
        SPDLOG_INFO("端口未被占用\0");
    }
    else {
        SPDLOG_INFO("开始杀进程: :{}\0", pid);
        system(("taskkill /F /PID " + pid).c_str());
    }
    return;
}
