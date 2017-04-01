#include "image_deck.h"
#include "card_compare.h"
#include <array>

Image_Deck::Map Image_Deck::m_map(&order_less);

static constexpr std::array<const char*, 5> str_color =
{
    "none",
    "diamond",
    "club",
    "heart",
    "spade"
};

static constexpr std::array<const char*, 14> str_value =
{
    "none",
    "2",
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
    "ace"
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
    int start_col = static_cast<int>(Card_Color::Diamond);
    int end_col = static_cast<int>(Card_Color::Spade);

    Q_ASSERT(end_col > start_col);

    for (; start_col <= end_col; ++start_col)
    {
        int start_val = static_cast<int>(Card_Value::V_2);
        int end_val = static_cast<int>(Card_Value::V_ace);

        Q_ASSERT(end_val > start_val);
        for (; start_val <= end_val; ++start_val)
        {
            Card c(static_cast<Card_Color>(start_col), static_cast<Card_Value>(start_val));
            QString filestr = get_file_name(c);
            QPixmap pix(filestr);
            Q_ASSERT(!pix.isNull());
            m_map.insert({c, pix});
        }
    }

    Card black_joker(Card_Color::Black_Joker, Card_Value::V_joker);
    QPixmap bpix(QString(":/png_cards/black_joker.png"));
    Q_ASSERT(!bpix.isNull());
    m_map.insert({black_joker, bpix});

    Card red_joker(Card_Color::Red_Joker, Card_Value::V_joker);
    QPixmap rpix(QString(":/png_cards/red_joker.png"));
    Q_ASSERT(!rpix.isNull());
    m_map.insert({red_joker, rpix});

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


