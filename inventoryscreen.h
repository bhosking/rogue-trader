#ifndef INVENTORYSCREEN_H
#define INVENTORYSCREEN_H
#include <QWidget>
#include <unordered_map>
#include <vector>
#include <utility>

class Resource;
class InventoryRow;

class InventoryScreen : public QWidget
{
public:
    InventoryScreen();
    void refreshInventory(const std::unordered_map<const Resource *, int> & inv);
private:
    std::vector<InventoryRow *> m_currentInv;
    InventoryRow * m_headerRow;
};

#endif // INVENTORYSCREEN_H
