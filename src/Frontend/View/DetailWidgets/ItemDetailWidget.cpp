#include "ItemDetailWidget.h"
#include "../../../Backend/Elements/Media.h"
#include "../../../Backend/Elements/Book.h"
#include "../../../Backend/Elements/Movie.h"
#include "../../../Backend/Elements/Song.h"
#include "../../../Backend/Elements/Magazine.h"
#include "../../../Backend/Elements/Podcast.h"
#include <QHBoxLayout>
#include <QCoreApplication>
#include <QFileInfo>
#include <QDir>

ItemDetailWidget::ItemDetailWidget(QWidget* parent) : QWidget(parent) {
    setObjectName("detailPane");
    setStyleSheet("#detailPane{background:#2f2f2f;border-left:1px solid #444;padding:12px;} ");

    // Root vertical layout
    QVBoxLayout* rootV = new QVBoxLayout(this);
    rootV->setContentsMargins(16,12,16,12);
    rootV->setSpacing(6);

    // Top horizontal: text (left) + image (right)
    QHBoxLayout* topH = new QHBoxLayout();
    topH->setContentsMargins(0,0,0,0);
    topH->setSpacing(8); // small gap between text and image

    QVBoxLayout* textCol = new QVBoxLayout();
    textCol->setContentsMargins(0,0,0,0);
    textCol->setSpacing(2);
    titleLabel = new QLabel("Title", this);
    titleLabel->setStyleSheet("font-size:20px;font-weight:600;color:#ffffff;margin-bottom:0;");
    authorLabel = new QLabel("Author", this);
    authorLabel->setStyleSheet("font-size:16px;font-weight:500;color:#cccccc;margin-bottom:0;");
    dateLabel = new QLabel("Date", this);
    dateLabel->setStyleSheet("font-size:14px;font-style:italic;color:#aaaaaa;margin-bottom:2px;");
    textCol->addWidget(titleLabel);
    textCol->addWidget(authorLabel);
    textCol->addWidget(dateLabel);

    topH->addLayout(textCol);
    topH->addStretch(); // push image to right margin

    imageLabel = new QLabel(this);
    imageLabel->setObjectName("detailImage");
    imageLabel->setFixedSize(160,220);
    imageLabel->setAlignment(Qt::AlignCenter);
    imageLabel->setStyleSheet("#detailImage{border:1px solid #555;background:#3a3a3a;color:#888;font-size:12px;padding:4px;}");
    imageLabel->setText("No Image\nAvailable");
    topH->addWidget(imageLabel, 0, Qt::AlignTop);

    rootV->addLayout(topH);

    // Centered extra information below
    extraLabel = new QLabel("", this);
    extraLabel->setAlignment(Qt::AlignHCenter | Qt::AlignTop);
    extraLabel->setWordWrap(true);
    extraLabel->setStyleSheet("font-size:13px;line-height:1.15;color:#dddddd;");
    rootV->addWidget(extraLabel, 1, Qt::AlignTop);

    // Buttons centered
    QHBoxLayout* btnH = new QHBoxLayout();
    btnH->addStretch();
    editBtn = new QPushButton("Edit", this);
    deleteBtn = new QPushButton("Delete", this);
    btnH->addWidget(editBtn);
    btnH->addWidget(deleteBtn);
    btnH->addStretch();
    rootV->addLayout(btnH);

    connect(editBtn, &QPushButton::clicked, [this](){ emit editRequested(currentId); });
    connect(deleteBtn, &QPushButton::clicked, [this](){ emit deleteRequested(currentId); });
}

void ItemDetailWidget::displayMedia(const Media& media) {
    currentId = media.getID();
    titleLabel->setText(QString::fromStdString(media.getTitle()));
    authorLabel->setText(QString::fromStdString(media.getAuthor()));
    dateLabel->setText(QString::fromStdString(media.getReleaseDate().toString()));

    // Determine type name (matching JSON/XML 'type') via dynamic_cast
    QString typeName;
    if(dynamic_cast<const Book*>(&media)) typeName = "Book";
    else if(dynamic_cast<const Movie*>(&media)) typeName = "Movie";
    else if(dynamic_cast<const Song*>(&media)) typeName = "Song";
    else if(dynamic_cast<const Magazine*>(&media)) typeName = "Magazine";
    else if(dynamic_cast<const Podcast*>(&media)) typeName = "Podcast";
    else typeName = "Media"; // fallback

    // Clear previous state and load ONLY the explicit imagePath.
    imageLabel->setPixmap(QPixmap());
    imageLabel->setText("No Image\nAvailable");
    const std::string& imgPath = media.getImagePath();
    if(!imgPath.empty()){
        QString path = QString::fromStdString(imgPath);
        QList<QString> candidates;
        if(QFileInfo::exists(path)) candidates << path;
        bool isRelative = !path.startsWith(":/") && !QFileInfo(path).isAbsolute();
        if(isRelative){
            QString exeDir = QCoreApplication::applicationDirPath();
            candidates << exeDir + "/" + path;          // build/bin/ + relative
            candidates << exeDir + "/../" + path;       // build/ + relative
            candidates << exeDir + "/../../" + path;    // project root + relative (if exe in build/bin)
        }
        bool loaded = false;
        for(const QString& c : candidates){
            QPixmap pm(c);
            if(!pm.isNull()){
                pm = pm.scaled(imageLabel->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
                imageLabel->setPixmap(pm);
                imageLabel->setText("");
                loaded = true;
                break;
            }
        }
        if(!loaded){
            imageLabel->setText("Image\nnot found");
        }
    }

        extraLabel->setTextFormat(Qt::RichText);
        QString typeHeader;
        QString body;
        if(const Book* b = dynamic_cast<const Book*>(&media)){
            typeHeader = "Book";
            body = QString("Publisher: %1\nPages: %2\nISBN: %3\nLanguage: %4\nGenre: %5")
                .arg(QString::fromStdString(b->getPublisher()))
                .arg(b->getPages())
                .arg(QString::fromStdString(b->getIsbn()))
                .arg(QString::fromStdString(b->getLanguageString()))
                .arg(QString::fromStdString(b->getGenreString()));
        } else if(const Movie* mv = dynamic_cast<const Movie*>(&media)){
            typeHeader = "Movie";
            body = QString("Director: %1\nDuration: %2 min\nStudio: %3\nRating: %4\nLanguage: %5\nCountry: %6\nGenre: %7")
                .arg(QString::fromStdString(mv->getDirector()))
                .arg(mv->getDuration())
                .arg(QString::fromStdString(mv->getStudio()))
                .arg(QString::fromStdString(mv->getRating()))
                .arg(QString::fromStdString(mv->getLanguageString()))
                .arg(QString::fromStdString(mv->getCountry()))
                .arg(QString::fromStdString(mv->getGenreString()));
        } else if(const Song* s = dynamic_cast<const Song*>(&media)){
            typeHeader = "Song";
            body = QString("Artist: %1\nAlbum: %2\nDuration: %3 s\nFormat: %4\nLabel: %5\nTrack #: %6\nGenre: %7")
                .arg(QString::fromStdString(s->getArtist()))
                .arg(QString::fromStdString(s->getAlbum()))
                .arg(s->getDuration())
                .arg(QString::fromStdString(s->getFormat()))
                .arg(QString::fromStdString(s->getLabel()))
                .arg(s->getTrackNumber())
                .arg(QString::fromStdString(s->getGenreString()));
        } else if(const Magazine* mg = dynamic_cast<const Magazine*>(&media)){
            typeHeader = "Magazine";
            body = QString("Publisher: %1\nIssue: %2\nISSN: %3\nEditor: %4\nPages: %5\nFrequency: %6\nGenre: %7")
                .arg(QString::fromStdString(mg->getPublisher()))
                .arg(mg->getIssueNumber())
                .arg(QString::fromStdString(mg->getIssn()))
                .arg(QString::fromStdString(mg->getEditor()))
                .arg(mg->getPages())
                .arg(QString::fromStdString(mg->getFrequency()))
                .arg(QString::fromStdString(mg->getGenreString()));
        } else if(const Podcast* p = dynamic_cast<const Podcast*>(&media)){
            typeHeader = "Podcast";
            body = QString("Host: %1\nEpisode: %2\nPlatform: %3\nDuration: %4 min\nSeries: %5\nDescription: %6\nGenre: %7")
                .arg(QString::fromStdString(p->getHost()))
                .arg(p->getEpisodeNumber())
                .arg(QString::fromStdString(p->getPlatform()))
                .arg(p->getDuration())
                .arg(QString::fromStdString(p->getSeries()))
                .arg(QString::fromStdString(p->getDescription()))
                .arg(QString::fromStdString(p->getGenreString()));
        }
        QString html = QString("<div style='margin-bottom:6px;'><b>%1</b></div><div>%2</div>")
            .arg(typeHeader, body.toHtmlEscaped().replace("\n","<br/>"));
        extraLabel->setText(html);
}
