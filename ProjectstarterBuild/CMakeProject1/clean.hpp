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
#pragma once

#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/spdlog.h>

#include <filesystem>
#include <regex>
#include <string>
#include <vector>

namespace fs = std::filesystem;

template <typename... Args>
auto clearPath(Args... args) -> bool
{
    std::vector<std::string> need_delete;
    (need_delete.push_back(args), ...);

    for (const auto &tmp : need_delete) {
        if (fs::exists(tmp)) [[likely]] {
            fs::remove_all(tmp);
            SPDLOG_INFO("{} is already cleared.", tmp);
        }
    }
    return true;
}
