#ifndef SIDEWINDOW_H
#define SIDEWINDOW_H

#include <QWidget>
#include <memory>
#include <unordered_map>

class QLabel;
class BuyOrSellWidget;
class Info;
class QTabWidget;
class QGridLayout;
class Resource;

class SideWindow : public QWidget
{
    Q_OBJECT
public:
    SideWindow();
    void setInfo(std::shared_ptr<const Info> newInfo, const std::unordered_map<const Resource *, int> & inventory);
public slots:
    void playerArrivedAtTown(std::shared_ptr<const Info> info, const std::unordered_map<const Resource *, int> & inventory);
    void playerLeftTown();
signals:
    void buyWidgetClicked(const Resource * resource, int amount);
    void sellWidgetClicked(const Resource * resource, int amount);
private:
    QLabel * m_townNameLabel;
    std::vector<BuyOrSellWidget*> m_buyOrSellWidgets;
    std::vector<BuyOrSellWidget*> m_sellWidgets;
    QTabWidget * m_tabWidget;
    QGridLayout * m_buyAndSellResourcesTab;
    QGridLayout * m_buyAndSellInfoTab;
};

#endif // SIDEWINDOW_H
