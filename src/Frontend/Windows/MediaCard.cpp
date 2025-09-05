#include "MediaCard.h"
#include <QMouseEvent>
#include <QPainter>
#include <QApplication>
#include <QGuiApplication>
#include <QEnterEvent>
#include <QPainterPath>
#include <QFile>
#include <QScreen>
#include <QSvgRenderer>
#include "../../Backend/Elements/Book.h"
#include "../../Backend/Elements/Movie.h"
#include "../../Backend/Elements/Song.h"
#include "../../Backend/Elements/Magazine.h"
#include "../../Backend/Elements/Podcast.h"

MediaCard::MediaCard(Media* media, QWidget* parent)
    : QFrame(parent), media(media), isHovered(false)
{
    setMinimumSize(200, 260);
    setMaximumWidth(260);
    setObjectName("mediaCard");
    
    layout = new QVBoxLayout(this);
    layout->setSpacing(10);
    layout->setContentsMargins(10, 10, 10, 10);
    
    coverLabel = new QLabel(this);
    coverLabel->setObjectName("coverBox");
    coverLabel->setFixedSize(180, 180);
    coverLabel->setAlignment(Qt::AlignCenter);
    coverLabel->setText("Cover\nImage");
    layout->addWidget(coverLabel, 0, Qt::AlignHCenter);
    
    typeBadgeLabel = new QLabel(this);
    typeBadgeLabel->setObjectName("typeBadge");
    typeBadgeLabel->setAlignment(Qt::AlignCenter);
    typeBadgeLabel->setText(computeType());
    layout->addWidget(typeBadgeLabel, 0, Qt::AlignLeft);

    titleLabel = new QLabel(QString::fromStdString(media->getTitle()), this);
    titleLabel->setObjectName("mediaTitle");
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setWordWrap(true);
    layout->addWidget(titleLabel);
    
    yearLabel = new QLabel(QString::fromStdString(media->getReleaseDate().toString()), this);
    yearLabel->setObjectName("mediaYear");
    yearLabel->setAlignment(Qt::AlignCenter);
    layout->addWidget(yearLabel);
    
    
    
    setCursor(Qt::PointingHandCursor);
    updateCover();
}

void MediaCard::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton) {
        emit clicked(media);
    }
    QFrame::mousePressEvent(event);
}

void MediaCard::paintEvent(QPaintEvent* event)
{
    QFrame::paintEvent(event);
}

void MediaCard::enterEvent(QEnterEvent* event)
{
    isHovered = true;
    update();
    QFrame::enterEvent(event);
}

void MediaCard::leaveEvent(QEvent* event)
{
    isHovered = false;
    update();
    QFrame::leaveEvent(event);
}

void MediaCard::updateCover()
{
    QPixmap pix(QString::fromStdString(media->getImagePath()));
    if (!pix.isNull()) {
        const QSize target = coverLabel->size();
        QPixmap scaled = pix.scaled(target, Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);
        const int x = std::max(0, (scaled.width() - target.width()) / 2);
        const int y = std::max(0, (scaled.height() - target.height()) / 2);
        QPixmap cropped = scaled.copy(QRect(x, y, target.width(), target.height()));
        QPixmap rounded(target);
        rounded.fill(Qt::transparent);
        QPainter painter(&rounded);
        painter.setRenderHint(QPainter::Antialiasing, true);
        QPainterPath path;
        path.addRoundedRect(QRectF(0, 0, target.width(), target.height()), 8, 8);
        painter.setClipPath(path);
        painter.drawPixmap(0, 0, cropped);
        painter.end();
        coverLabel->setPixmap(rounded);
        coverLabel->setText("");
    } else {
        
        QString iconName;
        if (dynamic_cast<Book*>(media)) iconName = "book";
        else if (dynamic_cast<Movie*>(media)) iconName = "movie";
        else if (dynamic_cast<Song*>(media)) iconName = "music";
        else if (dynamic_cast<Magazine*>(media)) iconName = "magazine";
        else if (dynamic_cast<Podcast*>(media)) iconName = "podcast";

        auto findIconPath = [&](const QString& base)->QString{
            const QString res = QString(":/icons/%1.svg").arg(base);
            if (QFile::exists(res)) return res;
            const QStringList tries = {
                QString("src/Frontend/Resources/icons/%1.svg").arg(base),
                QString("icons/%1.svg").arg(base),
                QString("../icons/%1.svg").arg(base),
            };
            for (const QString& p : tries) if (QFile::exists(p)) return p;
            return QString();
        };

        const QString iconPath = findIconPath(iconName);
        if (!iconPath.isEmpty()) {
            const QSize target = coverLabel->size();
            const qreal ratio = 0.6;
            const qreal dpr = QGuiApplication::primaryScreen() ? QGuiApplication::primaryScreen()->devicePixelRatio() : 1.0;

            
            QPixmap iconPixmap;
            if (iconPath.endsWith(".svg", Qt::CaseInsensitive)) {
                const QSizeF logicalSize(target.width()*ratio, target.height()*ratio);
                const QSize pixelSize(qMax(1, int(logicalSize.width()*dpr)), qMax(1, int(logicalSize.height()*dpr)));
                QPixmap tmp(pixelSize);
                tmp.fill(Qt::transparent);
                QSvgRenderer renderer(iconPath);
                QPainter rp(&tmp);
                rp.setRenderHint(QPainter::Antialiasing, true);
                rp.setRenderHint(QPainter::SmoothPixmapTransform, true);
                renderer.render(&rp, QRectF(0, 0, pixelSize.width(), pixelSize.height()));
                rp.end();
                tmp.setDevicePixelRatio(dpr);
                iconPixmap = tmp;
            } else {
                
                QPixmap raw(iconPath);
                iconPixmap = raw.scaled(target.width()*ratio, target.height()*ratio, Qt::KeepAspectRatio, Qt::SmoothTransformation);
            }

            
            QPixmap canvas(QSize(target.width()*dpr, target.height()*dpr));
            canvas.fill(Qt::transparent);
            QPainter painter(&canvas);
            painter.setRenderHint(QPainter::Antialiasing, true);
            QPainterPath path;
            path.addRoundedRect(QRectF(0, 0, canvas.width(), canvas.height()), 8*dpr, 8*dpr);
            painter.setClipPath(path);
            painter.fillRect(QRectF(0,0,canvas.width(),canvas.height()), QColor(68,68,68));

            const int x = int((canvas.width()/dpr - iconPixmap.width()/iconPixmap.devicePixelRatio())/2 * dpr);
            const int y = int((canvas.height()/dpr - iconPixmap.height()/iconPixmap.devicePixelRatio())/2 * dpr);
            painter.drawPixmap(x, y, iconPixmap);
            painter.end();

            canvas.setDevicePixelRatio(dpr);
            coverLabel->setPixmap(canvas);
            coverLabel->setText("");
        } else {
            coverLabel->setPixmap(QPixmap());
            coverLabel->setText(" ");
        }
    }
}

QString MediaCard::computeType() const
{
    
    if (dynamic_cast<Book*>(media)) return "Book";
    if (dynamic_cast<Movie*>(media)) return "Movie";
    if (dynamic_cast<Song*>(media)) return "Song";
    if (dynamic_cast<Magazine*>(media)) return "Magazine";
    if (dynamic_cast<Podcast*>(media)) return "Podcast";
    return "";
}
