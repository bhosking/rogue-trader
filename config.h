#ifndef CONFIG_H
#define CONFIG_H
#include <vector>
#include <string>

class Resource;

class Config
{
public:
    Config();
    const std::vector<const Resource *> & getResources() const;
    const Resource * getResource(std::string name) const;
private:
    void loadResources();
    static std::vector<const Resource *> m_resources;
};

#endif // CONFIG_H
