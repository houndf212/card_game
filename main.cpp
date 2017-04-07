#include <QApplication>
#include "static_deck.h"
#include "static_cardimage.h"
#include "testhandinfowidget.h"
#include "comparehandinfowidget.h"
#include "hinter.h"

void test_hinter()
{
    CardList all;
    all.push_back({Card::diamond, Card::V_2});
    all.push_back({Card::heart, Card::V_2});

    all.push_back({Card::diamond, Card::V_3});

    all.push_back({Card::diamond, Card::V_4});
    all.push_back({Card::spade, Card::V_4});
    all.push_back({Card::heart, Card::V_4});
    all.push_back({Card::club, Card::V_4});

    all.push_back({Card::club, Card::V_5});
    all.push_back({Card::spade, Card::V_5});
    all.push_back({Card::heart, Card::V_5});

    all.push_back({Card::diamond, Card::V_6});
    all.push_back({Card::diamond, Card::V_7});
    all.push_back({Card::heart, Card::V_7});

    all.push_back({Card::diamond, Card::V_8});

    all.push_back({Card::black_joker, Card::V_joker});
    all.push_back({Card::red_joker, Card::V_joker});

    CardList pre_hand;
    pre_hand.push_back({Card::spade, Card::V_4});
    pre_hand.push_back({Card::heart, Card::V_4});
    Hand_Hinter hinter;
    hinter.set_hand(all, pre_hand);

    int size = hinter.size();
    while(size-->0)
    {
        qDebug() << hinter.next_hint();
    }
}
int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    Static_Deck::init();
    Static_CardImage::init_image();

    qDebug() << "card size: " << Static_CardImage::image_size();

    test_hinter();
    CompareHandInfoWidget w;
    w.show();

//    return 0;

    return a.exec();
}
