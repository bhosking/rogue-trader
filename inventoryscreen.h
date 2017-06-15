#ifndef INVENTORYSCREEN_H
#define INVENTORYSCREEN_H
#include <QWidget>
#include <unordered_map>
#include <vector>
#include <utility>

class Resource;
class InventoryRow;
class QLabel;

class InventoryScreen : public QWidget
{
public:
    InventoryScreen();
    void refreshInventory(const std::unordered_map<const Resource *, int> & inv);
    void setGold(int amount);
private:
    std::vector<InventoryRow *> m_currentInv;
    InventoryRow * m_headerRow;
    QLabel * m_goldAmount;
};

#endif // INVENTORYSCREEN_H
