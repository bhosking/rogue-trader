#ifndef CONFIG_H
#define CONFIG_H
#include "resource.h"


class Config
{
public:
    Config();
    std::vector<Resource*> loadResources();
};

#endif // CONFIG_H
