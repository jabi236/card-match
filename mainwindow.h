#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <vector>
#include <memory>
#include <set>
#include <map>
#include <QTimer>
#include "card.h"
#include "cardbutton.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);

    ~MainWindow() override;

private slots:

    static void quit();

    void sync();

    void shuffle();

    void reset();

    void flippedCard(const std::shared_ptr<Card> card);

    void blockButtonSignals();

    void unblockButtonSignals();

    void resetSelectedCards();

private:
    Ui::MainWindow* ui;
    std::unique_ptr<QTimer> m_timer;
    std::vector<std::shared_ptr<CardButton>> m_buttons;
    std::vector<std::shared_ptr<Card>> m_cards;
    std::map<std::shared_ptr<Card>, std::shared_ptr<CardButton>> m_buttonMap;
    std::set<std::shared_ptr<Card>> m_matchedCards;
    std::set<std::shared_ptr<Card>> m_unmatchedCards;
    std::shared_ptr<Card> m_firstCard;
    std::shared_ptr<Card> m_secondCard;
    unsigned m_guesses = 0;
};

#endif // MAINWINDOW_H