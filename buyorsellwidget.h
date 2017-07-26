#ifndef BUYORSELLWIDGET_H
#define BUYORSELLWIDGET_H

#include <QWidget>
#include <utility>
class Resource;
class QSlider;
class QPushButton;
class QLabel;
class QSvgWidget;



class BuyOrSellWidget : public QWidget
{

    Q_OBJECT
public:

    explicit BuyOrSellWidget(const Resource * resource, QWidget *parent = 0);
    int getSelectedAmount();
    void setTownStockAmount(int newTownStockAmount);
    void setTownStock(const std::pair<const Resource *, int> &stock);
    void setPlayerStockAmount(int newPlayerStockAmount);
    void setTownPopulation(int population);
private:
    void update();
    QSlider * m_buyOrSellAmountSlider;
    const Resource * m_resource;
    QPushButton * m_buyOrSellButton;
    QLabel * m_unitPriceLabel;
    QLabel * m_totalPriceLabel;
    QSvgWidget * m_svg;
    int m_townStock;
    int m_townPopulation;
    int m_playerStock;
    int m_selectedAmount;
signals:
    void buyAmountOfResource(const Resource * resource, int amount);
    void sellAmountOfResource(const Resource * resource, int amount);

public slots:
    void setSelectedAmount(int newAmount);
    void buyOrSellButtonPressed();

};

#endif // BUYORSELLWIDGET_H
