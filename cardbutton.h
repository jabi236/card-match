#ifndef CARDBUTTON_H
#define CARDBUTTON_H

#include <QIcon>
#include <QString>
#include <QPushButton>
#include <QObject>
#include "card.h"

class CardButton:public QPushButton{
    Q_OBJECT

public:
    CardButton(QWidget* parent = nullptr);

public slots:

    void updateIcon(const std::shared_ptr<Card> card);

};
#endif //CARDBUTTON_H
