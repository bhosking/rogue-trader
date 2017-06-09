#ifndef BUYORSELLWIDGET_H
#define BUYORSELLWIDGET_H

#include <QWidget>
#include <utility>
class Resource;
class QSlider;
class QPushButton;
class QLabel;



class BuyOrSellWidget : public QWidget
{

    Q_OBJECT
public:
    enum class Type{BUY,SELL};

    explicit BuyOrSellWidget(const Resource * resource, int townStock, Type type, QWidget *parent = 0);
    int getSelectedAmount();
    void setTownStockAmount(int newTownStockAmount);
    void setTownStock(const std::pair<const Resource *, int> &stock);
    void setPlayerStockAmount(int newPlayerStockAmount);
private:
    void update();
    QSlider * m_buyOrSellAmountSlider;
    const Resource * m_resource;
    QPushButton * m_buyOrSellButton;
    QLabel * m_unitPriceLabel;
    QLabel * m_totalPriceLabel;
    int m_townStock;
    int m_playerStock;
    int m_selectedAmount;
    Type m_type;
signals:
    void buyOrSellAmountOfResource(const Resource * resource, int amount);
public slots:
    void setSelectedAmount(int newAmount);
    void buyOrSellButtonPressed();

};

#endif // BUYORSELLWIDGET_H
