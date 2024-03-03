#include <iostream>
#include <fstream>
#include "vector"
#include <string>

class pathVariableMap {
public:
    std::string path;
    std::string variable;
};

bool readProfile(const char *input, std::vector<pathVariableMap> &myList) {
    std::ifstream file(input);
    std::string buf = "";
    std::string path = "", value = "";
    while (std::getline(file, buf)) {
        if (buf[0] == '#' || buf.empty()) {
            continue;
        }

        size_t pos = buf.find(' ');
        if (pos != std::string::npos) {
            path = buf.substr(0, pos);
            value = buf.erase(0, pos);
            pathVariableMap obj;
            obj.path = path;
            obj.variable = value;
            myList.push_back(obj);
        }

    }
    file.close();
    return true;
}

int main(int argc, char **argv) {
    if (argv[1] == nullptr) {
        std::cout << "未输入命令行参数 即将退出\n";
        std::cin.get();
        return 0;
    }
    std::vector<pathVariableMap> myList;
    readProfile(argv[1], myList);
    for (const auto &tmp: myList) {
        std::cout << "键：" << tmp.path << "\n";
        std::cout << "值：" << tmp.variable << "\n";
        system(("setx " + tmp.path + " " + tmp.variable + " /m").c_str());
    }
//    system("setx PATH \"%PATH%;D:\\flutter2\\bin\"");
    std::cout << "执行完毕\n";
    std::cin.get();
}
