#ifndef CARD_H
#define CARD_H

#include <QIcon>
#include <QString>
#include <QObject>

class Card: public QObject, public std::enable_shared_from_this<Card>{
    Q_OBJECT
public:

    enum Suit{
        diamonds = 1, hearts, spades, clubs
    };

    enum Rank{
        ace = 1, two, three, four, five, six, seven, eight, nine, ten ,jack, queen, king
    };

    [[nodiscard]] static const std::array<Suit, 4>& suits();

    [[nodiscard]] static const std::array<Rank, 13>& ranks();

    explicit Card(Suit suit, Rank rank, QString iconName, QObject* parent = nullptr);

    [[nodiscard]] const QIcon& icon() const {
        static QIcon back(":/back.png");
        return m_up ? m_front : back;
    }

    inline bool operator<(const Card& card) const;

    [[nodiscard]] bool isUp() const {return m_up;}

    Suit suit() const {return m_suit;}

    Rank rank() const {return m_rank;}

    void setUp(bool up) {m_up = up;}

public slots:

    void flip();

    signals:

    void flipped(const std::shared_ptr<Card> card);




private:
    Suit m_suit;
    Rank m_rank;
    QIcon m_front;
    bool m_up = false;

};

bool Card::operator<(const Card& card) const{
    if (m_suit == card.m_suit){
        return m_rank < card.m_rank;
    }else{
        return m_suit < card.m_suit;
    }
}

#endif // CARD_H
