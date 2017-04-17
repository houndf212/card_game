#ifndef STATIC_CARDIMAGE_H
#define STATIC_CARDIMAGE_H
#include <QtCore>
#include <QPixmap>
#include <map>
#include "card.h"

class Static_CardImage
{
public:
    typedef std::map<Card, QPixmap> Map;
public:
    static void init_image();
    static QSize image_size() { return m_card_size; }
    static QPixmap get_image(const Card& c);
private:
    static QString get_file_name(const Card& c);
    static void scale_image();
private:
    static Map m_map;
    static QSize m_card_size;
};

#endif // STATIC_CARDIMAGE_H
