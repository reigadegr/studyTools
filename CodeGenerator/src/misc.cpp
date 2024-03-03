#include <fstream>
#include <iostream>
#include <vector>

#include "include/LOG.h"
#include "include/class.h"
auto getStr(std::string &buf, std::string &className,
            std::vector<dbAttribute> &NameAndAttribute) -> void;
auto initTypeCasting(std::vector<mapping> &typeCasting) -> void
{
    typeCasting.push_back({"VARCHAR", "String"});
    typeCasting.push_back({"varchar", "String"});
    typeCasting.push_back({"int", "Integer"});
    typeCasting.push_back({"INT", "Integer"});
}
auto getStr(std::string &buf, std::string &className,
            std::vector<dbAttribute> &NameAndAttribute) -> void
{
    if (buf.find('`') == std::string::npos) {
        return;
    }
    size_t start = buf.find('`');
    std::string name;

    // 找到第二个反引号的位置
    size_t end = buf.find('`', start + 1);
    if (end != std::string::npos) {
        // 提取反引号中的字符
        name = buf.substr(start + 1, end - start - 1);
        if (buf.find("CREATE TABLE") != std::string::npos) {
            className = name;
            // 首字母变大写
            className[0] = toupper(className[0]);
            // LOG("//类名: ", className, "类名结束");
        }
    }
    buf.erase(0, end + 2);
    // 获取字段类型
    size_t left = buf.find('(');
    std::string type = buf.substr(0, left);
    if (type != "") {
        NameAndAttribute.push_back({name, type});
    }

    return;
}
auto readProfile(const char *inputFile, std::string &className,
                 std::vector<dbAttribute> &NameAndAttribute) -> void
{
    std::ifstream file(inputFile);
    std::string buf;
    while (std::getline(file, buf)) {
        getStr(buf, className, NameAndAttribute);
    }
    file.close();
    return;
}

auto runTypeCasting(const std::string &type, std::vector<mapping> &typeCasting)
    -> std::string
{
    const char *constCharType = type.c_str();
    for (const auto &tmp : typeCasting) {
        if (strcmp(constCharType, tmp.dbType.c_str()) == 0) {
            return tmp.javaType;
        }
    }
    return type;
}
auto printEntity(std::string &className,
                 std::vector<dbAttribute> &NameAndAttribute,
                 std::vector<mapping> &typeCasting) -> void
{
    LOG("//这是 ", className, ".java", "\n");
    LOG("import lombok.AllArgsConstructor;");
    LOG("import lombok.Data;");
    LOG("import lombok.NoArgsConstructor;\n");
    LOG("@Data");
    LOG("@AllArgsConstructor");
    LOG("@NoArgsConstructor\n");

    LOG("public class ", className, "{");

    for (const auto &tmp : NameAndAttribute) {
        const std::string newtype = runTypeCasting(tmp.type, typeCasting);
        LOG("    private ", newtype, " ", tmp.name, ";");
    }
    LOG("}");
    LOG("//-----------------结束----------------");
    LOG("\n");
}

auto printMapperInterface(std::string &className) -> void
{
    std::string orgClassName = className;
    orgClassName[0] = std::tolower(orgClassName[0]);
    LOG("//这是 ", className, "Mapper.java", "\n");
    LOG("import org.apache.ibatis.annotations.Mapper;");
    LOG("import org.apache.ibatis.annotations.Param;");
    LOG("import org.apache.ibatis.annotations.Select;\n");
    LOG("@Mapper");
    LOG("public interface " + className + "Mapper {");
    LOG("    @Select(\"SELECT * FROM ", orgClassName, " WHERE ", orgClassName,
        "_id = #{", orgClassName,
        "Id} AND "
        "password"
        "= #{password}\")");

    LOG("    ", className + " findBy" + className + "IdAndPassword",
        "(@Param(\"", orgClassName, "Id\") String ", orgClassName,
        "Id, @Param(\"password\") String "
        "password);");
    LOG("}");
    LOG("//-----------------结束----------------");
    LOG("\n");
}

auto printServiceInterface(std::string &className) -> void
{
    std::string orgClassName = className;
    orgClassName[0] = std::tolower(orgClassName[0]);
    LOG("//这是 ", className, "Service.java", "\n");
    LOG("public interface " + className, "Service {");
    LOG("    public ", className, " ", "findBy", className,
        "IdAndPassword(String ", orgClassName, "Id, String password);");
    LOG("}");
    LOG("//-----------------结束----------------");
    LOG("\n");
}

auto printServiceClass(std::string &className) -> void
{
    std::string orgClassName = className;
    orgClassName[0] = std::tolower(orgClassName[0]);
    LOG("//这是 ", className, "ServiceImpl.java", "\n");
    LOG("import org.springframework.beans.factory.annotation.Autowired;");
    LOG("import org.springframework.stereotype.Service;\n");
    LOG("@Service");
    LOG("public class ", className, "ServiceImpl implements ", className,
        "Service {");
    LOG("    @Autowired");
    LOG("    private ", className, "Mapper ", orgClassName, "Mapper;");

    LOG("    @Override");
    LOG("    public ", className, " findBy", className, "IdAndPassword(String ",
        orgClassName, "Id, String password) {");
    LOG("        return ", orgClassName, "Mapper.findBy", className,
        "IdAndPassword(", orgClassName, "Id, password);");
    LOG("    }");
    LOG("}");
    LOG("//-----------------结束----------------");
    LOG("\n");
}
auto printController(std::string &className) -> void
{
    std::string orgClassName = className;
    orgClassName[0] = std::tolower(orgClassName[0]);
    LOG("//这是 ", className, "Controller.java", "\n");
    LOG("import org.springframework.beans.factory.annotation.Autowired;");
    LOG("import org.springframework.web.bind.annotation.CrossOrigin;");
    LOG("import org.springframework.web.bind.annotation.RequestBody;");
    LOG("import org.springframework.web.bind.annotation.RequestMapping;");
    LOG("import org.springframework.web.bind.annotation.RestController;\n");
    LOG("@RestController");
    LOG("public class ", className, "Controller {");
    LOG("   @Autowired");
    LOG("   private ", className, "Service ", orgClassName, "Service;\n");
    LOG("   @CrossOrigin(origins = \"*\")");
    LOG("   @RequestMapping(\"/", orgClassName, "loginverify\")");
    LOG("   public ", className, " findBy", className,
        "IdAndPassword(@RequestBody ", className, " ", orgClassName, ") {");
    LOG("       String ", orgClassName, "_id = ", orgClassName, ".get",
        className, "_id();");
    LOG("       String password = ", orgClassName, ".getPassword();");
    LOG("       return ", orgClassName, "Service.findBy", className,
        "IdAndPassword(", orgClassName, "_id, password);\n   }");
    LOG("}");
    LOG("//-----------------结束----------------");
    LOG("\n");
}
