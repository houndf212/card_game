#ifndef STATIC_CARDIMAGE_H
#define STATIC_CARDIMAGE_H
#include <QtCore>
#include <QPixmap>
#include <map>
#include "card.h"

class Static_CardImage
{
public:
    typedef std::map<Card, QPixmap, Card_Compare> Map;
public:
    static void init_image();
    static QSize image_size();
    static QPixmap get_image(const Card& c);
private:
    static QString get_file_name(const Card& c);
    static void scale_image();
private:
    static Map m_map;
};

#endif // STATIC_CARDIMAGE_H
