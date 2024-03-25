#include "cardbutton.h"
CardButton::CardButton(QWidget *parent):QPushButton(parent){
}

void CardButton::updateIcon(const std::shared_ptr<Card> card){
    setIcon(card->icon());
}

