#ifndef SIDEWINDOW_H
#define SIDEWINDOW_H

#include <QWidget>
#include <memory>

class QLabel;
class BuyOrSellWidget;
class Info;

class SideWindow : public QWidget
{
    Q_OBJECT
public:
    SideWindow();
    void setInfo(std::shared_ptr<const Info> newInfo);
public slots:
    void playerArrivedAtTown(std::shared_ptr<const Info> info);
    void playerLeftTown();
private:
    QLabel * m_townNameLabel;
    std::vector<BuyOrSellWidget*> m_buyWidgets;
};

#endif // SIDEWINDOW_H
