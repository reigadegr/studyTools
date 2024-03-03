#include <fstream>
#include <iostream>
#include <vector>

#include "include/LOG.h"
#include "include/class.h"
auto readProfile(const char *inputFile, std::string &className,
                 std::vector<dbAttribute> &NameAndAttribute) -> void;
auto runTypeCasting(const std::string &type, std::vector<mapping> &typeCasting)
    -> std::string;
auto initTypeCasting(std::vector<mapping> &typeCasting) -> void;
auto printEntity(std::string &className,
                 std::vector<dbAttribute> &NameAndAttribute,
                 std::vector<mapping> &typeCasting) -> void;
auto printMapperInterface(std::string &className) -> void;
auto printServiceInterface(std::string &className) -> void;
auto printServiceClass(std::string &className) -> void;
auto printController(std::string &className) -> void;
#if 0
```java
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.CrossOrigin;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

@RestController
public class AdminController {
    @Autowired
    private AdminService adminService;

    @CrossOrigin(origins = "*")
    @RequestMapping("/adminloginverify")
    public Admin findByAdminIdAndPassword(@RequestBody Admin admin) {
        String admin_id = admin.getAdmin_id();
        String password = admin.getPassword();
        return adminService.findByAdminIdAndPassword(admin_id, password);
    }

}
```
#endif
auto printAnyJava(std::string &className,
                  std::vector<dbAttribute> &NameAndAttribute,
                  std::vector<mapping> &typeCasting) -> void
{
    // 生成实体类
    printEntity(className, NameAndAttribute, typeCasting);
    // 生成mapper接口
    printMapperInterface(className);
    // 生成service接口
    printServiceInterface(className);
    // 生成service接口实现类
    printServiceClass(className);
    // 生成cotroller
    printController(className);
}
auto main(int argc, char **argv) -> int
{
    if (argv[1] == nullptr) {
        LOG("没输入命令行参数");
        return 2;
    }
    std::string className = "";
    std::string orgClassName = "";
    std::vector<dbAttribute> NameAndAttribute;
    std::vector<mapping> typeCasting;
    LOG("//开始生成...");
    initTypeCasting(typeCasting);
    // 读取建表命令
    readProfile(argv[1], className, NameAndAttribute);
    printAnyJava(className, NameAndAttribute, typeCasting);
}
