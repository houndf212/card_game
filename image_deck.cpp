#include "image_deck.h"
#include "card_compare.h"
#include "card_deck.h"

Image_Deck::Map Image_Deck::m_map(&order_less);

static constexpr std::array<const char*, 8> str_color =
{
    "none",
    "diamond",
    "club",
    "heart",
    "spade",
    "black",
    "red"
};

static constexpr std::array<const char*, 15> str_value =
{
    "none",
    "3",
    "4",
    "5",
    "6",
    "7",
    "8",
    "9",
    "10",
    "jack",
    "queen",
    "king",
    "ace",
    "2",
    "joker",
};

QString Image_Deck::get_file_name(const Card &c)
{
    const char* col = str_color.at(static_cast<int>(c.color()));
    const char* val = str_value.at(static_cast<int>(c.value()));
    QString str = QString(":/png_cards/") + col + "_" + val + ".png";
    return str;
}

void Image_Deck::scale_image()
{
    for (auto& p : m_map)
    {
        const QPixmap& pix = p.second;
        p.second = pix.scaled(pix.size()/3, Qt::KeepAspectRatioByExpanding	, Qt::SmoothTransformation);
    }
}

void Image_Deck::init_image()
{
    for (auto c : Card_Deck::get_init())
    {
        QString filestr = get_file_name(c);
        QPixmap pix(filestr);

        Q_ASSERT(!pix.isNull());

        m_map.insert({c, pix});
    }

    Q_ASSERT(m_map.size() == 54);
    scale_image();
}

QPixmap Image_Deck::get_image(const Card &c)
{
    auto p = m_map.find(c);
    if (p!=m_map.cend())
        return p->second;

    return QPixmap();
}


