#include "ItemCardWidget.h"
#include <QMouseEvent>
#include <QIcon>
#include "../../../Backend/Elements/Media.h"
#include "../../../Backend/Elements/Book.h"
#include "../../../Backend/Elements/Movie.h"
#include "../../../Backend/Elements/Song.h"
#include "../../../Backend/Elements/Magazine.h"
#include "../../../Backend/Elements/Podcast.h"

ItemCardWidget::ItemCardWidget(const Media& m, QWidget* parent)
    : QWidget(parent), media(m) {
    QHBoxLayout* root = new QHBoxLayout(this);
    iconLabel = new QLabel(this);
    iconLabel->setFixedSize(24,24);
    QIcon icn(":/icons/all.svg");
    if(dynamic_cast<const Book*>(&m)) icn = QIcon(":/icons/book.svg");
    else if(dynamic_cast<const Movie*>(&m)) icn = QIcon(":/icons/movie.svg");
    else if(dynamic_cast<const Song*>(&m)) icn = QIcon(":/icons/music.svg");
    else if(dynamic_cast<const Magazine*>(&m)) icn = QIcon(":/icons/magazine.svg");
    else if(dynamic_cast<const Podcast*>(&m)) icn = QIcon(":/icons/podcast.svg");
    iconLabel->setPixmap(icn.pixmap(24,24));
    QVBoxLayout* lay = new QVBoxLayout();
    titleLabel = new QLabel(QString::fromStdString(media.getTitle()), this);
    titleLabel->setStyleSheet("font-weight:bold");
    authorLabel = new QLabel(QString::fromStdString(media.getAuthor()), this);
    lay->addWidget(titleLabel);
    lay->addWidget(authorLabel);
    root->addWidget(iconLabel);
    root->addLayout(lay);
    root->addStretch();
    setLayout(root);
    setCursor(Qt::PointingHandCursor);
    setObjectName("classicCard");
    setStyleSheet("#classicCard{border:1px solid #555;border-radius:6px;padding:6px;} #classicCard:hover{background:#444;}");
}

unsigned int ItemCardWidget::mediaId() const { return media.getID(); }

void ItemCardWidget::mousePressEvent(QMouseEvent* e) {
    if (e->button()==Qt::LeftButton) emit clicked(media.getID());
    QWidget::mousePressEvent(e);
}
