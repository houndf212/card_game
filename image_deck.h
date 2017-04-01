#ifndef IMAGE_DECK_H
#define IMAGE_DECK_H
#include <QtCore>
#include <QPixmap>
#include <map>
#include "card.h"

class Image_Deck
{
    typedef std::map<Card, QPixmap, bool (*)(const Card&, const Card&)> Map;
public:
    static void init_image();
    static QPixmap get_image(const Card& c);
private:
    static QString get_file_name(const Card& c);
    static void scale_image();
private:
    static Map m_map;
};

#endif // IMAGE_DECK_H
