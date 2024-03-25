#include "card.h"
#include <cassert>


const std::array<Card::Suit, 4>&Card::suits(){
    static std::array<Suit, 4> m_suits = {diamonds, hearts, spades, clubs};
    return m_suits;
}
const std::array<Card::Rank, 13>& Card::ranks(){
    static std::array<Rank, 13> m_ranks = {
            ace, two, three, four, five, six, seven, eight, nine, ten, jack, queen, king
    };
    return m_ranks;
};

Card::Card(Suit suit, Rank rank, QString iconName, QObject* parent) :
    QObject(parent), m_suit(suit), m_rank(rank), m_front(iconName){
    assert(!m_front.isNull());
}

void Card::flip(){
    m_up = !m_up;
}



