#ifndef CONFIG_H
#define CONFIG_H
#include <unordered_map>

class Resource;

class Config
{
public:
    Config();
    const std::unordered_map<std::string, Resource *> & getResources() const;
    const Resource * getResource(std::string name) const;
private:
    void loadResources();
    std::unordered_map<std::string, Resource *> m_resources;
};

#endif // CONFIG_H
