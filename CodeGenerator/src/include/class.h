#pragma once
#include <iostream>
class dbAttribute {
public:
    std::string name;
    std::string type;
};

class mapping {
public:
    std::string dbType;
    std::string javaType;
};