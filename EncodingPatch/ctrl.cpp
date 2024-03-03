#include <iconv.h>

#include <fstream>
#include <iostream>
#include <vector>

// 函数：将GB2312编码的字符串转换为UTF-8
std::string gb2312_to_utf8(const std::string &gb2312_str)
{
    std::string utf8_str;
    size_t in_len = gb2312_str.size();
    size_t out_len = in_len * 4;  // 分配足够大的空间以确保能存储转换后的字符串
    std::vector<char> out_buf(out_len);
    char *in_ptr = const_cast<char *>(gb2312_str.data());
    char *out_ptr = out_buf.data();

    iconv_t cd = iconv_open("UTF-8", "GB2312");  // 打开转换描述符
    if (cd == (iconv_t)-1) {
        perror("iconv_open");
        return "";
    }

    if (iconv(cd, &in_ptr, &in_len, &out_ptr, &out_len) == (size_t)-1) {
        perror("iconv");
        iconv_close(cd);
        return "";
    }

    utf8_str.assign(out_buf.data(), out_buf.size() - out_len);
    iconv_close(cd);

    return utf8_str;
}

int main(int argc, char **argv)
{
    std::ifstream file(argv[1],
                       std::ios::binary);  // 以二进制模式打开GB2312编码的文件
    // std::cout << "打开" << argv[1] << "中\n";
    if (!file) {
        std::cerr << "Cannot open file\n";
        return 1;
    }

    // 读取整个文件到string
    std::string content((std::istreambuf_iterator<char>(file)),
                        std::istreambuf_iterator<char>());
    file.close();

    // 将GB2312编码的内容转换为UTF-8
    std::string utf8_content = gb2312_to_utf8(content);

    // 输出转换后的内容
    std::cout << utf8_content << std::endl;

    return 0;
}
