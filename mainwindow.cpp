#include <cassert>
#include <algorithm>
#include <random>
#include <QMessageBox>
#include <iostream>

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent) :
        QMainWindow(parent), ui(new Ui::MainWindow),
        m_timer(std::make_unique<QTimer>(this)){
    ui->setupUi(this);

    //std::vector<QString> card_base_name = {":/diamonds_", ":/hearts_", ":/spades_", ":/clubs_"};
    const int NUMBER_OF_CARDS = 52;
    const int NUMBER_OF_COLUMNS = 13;
    const QSize CARD_SIZE(71, 94);
    for(auto suit :Card::suits()){
        QString card_base_name = ":/";
        switch(suit){
            case Card::diamonds:
                card_base_name += "diamonds";
                break;
            case Card::hearts:
                card_base_name += "hearts";
                break;
            case Card::spades:
                card_base_name += "spades";
                break;
            case Card::clubs:
                card_base_name += "clubs";
                break;
            default:
                assert(false);
        }
        card_base_name = card_base_name + "_";
        for (auto rank: Card::ranks()){
            const QString card_name =card_base_name + QString::number(rank);
            //std::cerr << card_name.toStdString() << "\n";
            auto card = std::make_shared<Card>(suit, rank, card_name);
            auto button = std::make_shared<CardButton>(this);
            button->setIcon(card->icon());
            button->setIconSize(CARD_SIZE);
            button->setFixedSize(CARD_SIZE);
            button->setFlat(true);
            int row = static_cast<int>(suit);
            int column = static_cast<int>(rank);
            m_cards.push_back(card);
            m_unmatchedCards.insert(card);
            m_buttons.push_back(button);
            m_buttonMap[card] = button;
            ui->gridLayout->addWidget(m_buttons.back().get(), row, column);
        }
    }
    shuffle();

    ui->statusBar->showMessage(
        QString("Guesses: ") + QString::number(m_guesses) +
        "   Matches: " + QString::number(m_matchedCards.size()/2));

    m_timer->setSingleShot(true);
    m_timer->setInterval(3000);

    QObject::connect(m_timer.get(), SIGNAL(timeout()),
                    this, SLOT(unblockButtonSignals()));
    QObject::connect(m_timer.get(), SIGNAL(timeout()),
                     this, SLOT(resetSelectedCards()));
    QObject::connect(ui->resetButton, SIGNAL(clicked()),
                     this, SLOT(shuffle()));
    QObject::connect(ui->quitButton, SIGNAL(clicked()),
                     this, SLOT(quit()));
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::quit() {
    QApplication::quit();
}

void MainWindow::sync() {
    // synchronize the button icons with the cards
    auto cardIt = m_cards.begin();
    auto buttonIt = m_buttons.begin();
    while (cardIt != m_cards.end()) {
        (*buttonIt)->setIcon((*cardIt)->icon());
        QObject::connect((buttonIt)->get(), SIGNAL(clicked()),
                         (cardIt)->get(), SLOT(flip()));
        QObject::connect((cardIt)->get(), SIGNAL(flipped(std::shared_ptr<Card>)),
                         (buttonIt)->get(), SLOT(updateIcon(std::shared_ptr<Card>)));
        ++cardIt;
        ++buttonIt;
    }
    assert(buttonIt == m_buttons.end());
}

void MainWindow::shuffle() {
    static std::default_random_engine g;
    std::shuffle(m_cards.begin(), m_cards.end(), g);
    sync();
}

void MainWindow::reset(){
    /*
//disconnect()
     QObject::disconnect((buttonIt)->get(), SIGNAL(clicked()),
                         (cardIt)->get(), SLOT(flip()));
    QObject::disconnect((cardIt)->get(), SIGNAL(flipped(std::shared_ptr<Card>)),
                         (buttonIt)->get(), SLOT(updateIcon(std::shared_ptr<Card>)));
//shuffle()
//connect()
     QObject::connect((buttonIt)->get(), SIGNAL(clicked()),
                         (cardIt)->get(), SLOT(flip()));
        QObject::connect((cardIt)->get(), SIGNAL(flipped(std::shared_ptr<Card>)),
                         (buttonIt)->get(), SLOT(updateIcon(std::shared_ptr<Card>)));
     */


}

void MainWindow::flippedCard(const std::shared_ptr<Card> card){
/*
m_firstCard = card;
m_secondCard = card;
m_guess++;
if (m_firstCard.m_rank == m_secondCard.m_rank){
    //add m_firstCard and m_secondCard to matched cards and remove from unmatched cards
    m_matchedCards.insert(m_firstCard);
    m_matchedCards.insert(m_secondCard);
    m_unmatchedCards.erase(m_firstCard);
    m_unmatchedCards.erase(m_secondCard);
    //can not flip cards back

else
    blockbuttonsSignals()
    timer 3 secs
    thank timer?
    resetSelectedCards() // flip cards back
    unblockButtonSignals()

}

if (m_matchedCards.size()/2) == 26){
display << "You win";
}
reset()
 */
}

void MainWindow::blockButtonSignals(){
    /*
    bool block = m_buttons -> blockSignals(true);
    m_buttons -> blockSignals(block);
    m_timer -> start(3000);
    */
}

void MainWindow::unblockButtonSignals(){
    /*
    bool unblock = m_buttons -> blockSignals(false);
    m_buttons -> blockSignals(unblock);
     */
}

void MainWindow::resetSelectedCards(){
    //flip cards
}