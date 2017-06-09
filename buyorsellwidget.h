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

    explicit BuyOrSellWidget(const Resource * resource, int stock, Type type, QWidget *parent = 0);
    int getSelectedAmount();
    void setStockAmount(int newStockAmount);
    void setStock(const std::pair<const Resource *, int> &stock);
private:
    QSlider * m_buyOrSellAmountSlider;
    const Resource * m_resource;
    QPushButton * m_buyOrSellButton;
    QLabel * m_unitPriceLabel;
    QLabel * m_totalPriceLabel;
    int m_stock;
    int m_selectedAmount;
    Type m_type;
signals:
    void buyOrSellButtonPressed();
public slots:
    void setSelectedAmount(int newAmount);

};

#endif // BUYORSELLWIDGET_H
