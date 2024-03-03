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
#include <iostream>

template <typename... Args>
static void LOG(const Args &...args)
{
    const auto printArg = [&](const auto& arg) { std::cout << arg; };
    (printArg(args), ...);
    std::cout << std::endl;
}

auto main(int argc, char** argv) -> int
{
    if (argv[1] == nullptr) {
        LOG("cmdline arguments is nullptr");
        LOG("Please make sure your input arguments");
        std::cin.get();
        return 2;
    }
    const std::string argv1 = argv[1];

    system("git gc --prune=all");
    system("git add .");
    system(("git commit -m " + argv1).c_str());
    if (argv[2] != nullptr) {
        const std::string argv2 = argv[2];
        system(("git push origin " + argv2).c_str());
    }
    else {
        system("git push origin main");
    }
}
