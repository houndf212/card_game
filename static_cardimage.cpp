#include "static_cardimage.h"
#include "static_deck.h"

Static_CardImage::Map Static_CardImage::m_map(&order_less);

QString Static_CardImage::get_file_name(const Card &c)
{
    QMetaEnum mcolor = QMetaEnum::fromType<Card::Color>();
    const char* col = mcolor.key(c.color());

    QMetaEnum mvalue = QMetaEnum::fromType<Card::Value>();
    const char* val = mvalue.key(c.value());
    QString str = QString(":/png_cards/") + col + "_" + val + ".png";
    return str.remove("V_");
}

void Static_CardImage::scale_image()
{
    for (auto& p : m_map)
    {
        const QPixmap& pix = p.second;
        p.second = pix.scaled(pix.size()/5, Qt::KeepAspectRatioByExpanding	, Qt::SmoothTransformation);
    }
}

void Static_CardImage::init_image()
{
    for (auto c : Static_Deck::get_init())
    {
        QString filestr = get_file_name(c);
        QPixmap pix(filestr);

        Q_ASSERT(!pix.isNull());

        m_map.insert({c, pix});
    }

    Q_ASSERT(m_map.size() == Static_Deck::SIZE);
    scale_image();
}

QSize Static_CardImage::image_size()
{
    return m_map.begin()->second.size();
}

QPixmap Static_CardImage::get_image(const Card &c)
{
    auto p = m_map.find(c);
    Q_ASSERT(p!=m_map.cend());
    return p->second;
}
