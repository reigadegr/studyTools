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

namespace fs = std::filesystem;

#if defined(_WIN32)
const std::string yarn = "yarn.cmd";
#elif defined(__linux__)
const std::string yarn = "yarn";
#endif

void killer();

auto springboot_projectStart() -> bool
{
    killer();
    clearPath("target");
    SPDLOG_INFO("Please make sure you have installed maven.");
    system("mvn spring-boot:run");
    return true;
}