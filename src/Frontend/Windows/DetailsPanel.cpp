#include "DetailsPanel.h"
#include <QFile>
#include <QPixmap>
#include <QPainter>
#include <QHBoxLayout>
#include <QDir>
#include <QFileInfo>
#include <QCoreApplication>
#include "../../Backend/Elements/MediaVisitor.h"
#include "../Visitors/FrontendVisitors.h"

static QIcon loadIconByNameDP(const QString& baseName) {
    const QString resPath = QString(":/icons/%1.svg").arg(baseName);
    if (QFile::exists(resPath)) return QIcon(resPath);
    return QIcon();
}

DetailsPanel::DetailsPanel(QWidget* parent) : QWidget(parent) {
    setObjectName("rightPanel");
    setFixedWidth(420);
    setupUi();
}

void DetailsPanel::setupUi() {
    layout_ = new QVBoxLayout(this);
    layout_->setSpacing(20);
    layout_->setContentsMargins(20,20,20,20);

    QWidget* detailsWidget = new QWidget(this);
    QVBoxLayout* detailsLayout = new QVBoxLayout(detailsWidget);
    detailsLayout->setSpacing(15);

    backBtn_ = new QPushButton("Back to Grid", detailsWidget);
    backBtn_->setObjectName("backBtn");
    backBtn_->setIcon(loadIconByNameDP("back"));
    backBtn_->setIconSize(QSize(20,20));
    QObject::connect(backBtn_, &QPushButton::clicked, this, &DetailsPanel::backRequested);
    detailsLayout->addWidget(backBtn_);

    coverImage_ = new QLabel(detailsWidget);
    coverImage_->setObjectName("coverImage");
    coverImage_->setFixedSize(260, 300);
    coverImage_->setAlignment(Qt::AlignCenter);
    detailsLayout->addWidget(coverImage_, 0, Qt::AlignCenter);

    titleLabel_ = new QLabel(detailsWidget);
    titleLabel_->setObjectName("titleLabel");
    titleLabel_->setAlignment(Qt::AlignCenter);
    detailsLayout->addWidget(titleLabel_);

    authorLabel_ = new QLabel(detailsWidget); detailsLayout->addWidget(authorLabel_);
    yearLabel_ = new QLabel(detailsWidget); detailsLayout->addWidget(yearLabel_);
    durationLabel_ = new QLabel(detailsWidget); detailsLayout->addWidget(durationLabel_);
    summaryLabel_ = new QLabel(detailsWidget); summaryLabel_->setWordWrap(true); detailsLayout->addWidget(summaryLabel_);
    coverPathLabel_ = new QLabel(detailsWidget); detailsLayout->addWidget(coverPathLabel_);

    attributesGroup_ = new QGroupBox("Attributes", detailsWidget);
    attributesWidget_ = new QWidget(attributesGroup_);
    attributesForm_ = new QFormLayout(attributesWidget_);
    QVBoxLayout* attrLay = new QVBoxLayout(attributesGroup_);
    attrLay->addWidget(attributesWidget_);
    detailsLayout->addWidget(attributesGroup_);

    detailsLayout->addStretch();

    QHBoxLayout* buttonLayout = new QHBoxLayout();
    editBtn_ = new QPushButton("Edit", detailsWidget);
    editBtn_->setObjectName("editBtn"); editBtn_->setIcon(loadIconByNameDP("edit")); editBtn_->setIconSize(QSize(20,20));
    deleteBtn_ = new QPushButton("Delete", detailsWidget);
    deleteBtn_->setObjectName("deleteBtn"); deleteBtn_->setIcon(loadIconByNameDP("delete")); deleteBtn_->setIconSize(QSize(20,20));
    QObject::connect(editBtn_, &QPushButton::clicked, this, &DetailsPanel::editRequested);
    QObject::connect(deleteBtn_, &QPushButton::clicked, this, &DetailsPanel::deleteRequested);
    buttonLayout->addWidget(editBtn_);
    buttonLayout->addWidget(deleteBtn_);
    buttonLayout->setAlignment(Qt::AlignHCenter);
    buttonLayout->setSpacing(12);
    detailsLayout->addLayout(buttonLayout);

    layout_->addWidget(detailsWidget);
}

void DetailsPanel::clear() {
    coverImage_->clear();
    titleLabel_->clear();
    authorLabel_->clear();
    yearLabel_->clear();
    durationLabel_->clear();
    summaryLabel_->clear();
    coverPathLabel_->clear();
    clearAttributes();
}

void DetailsPanel::clearAttributes() {
    if (!attributesForm_) return;
    for (int row = attributesForm_->rowCount() - 1; row >= 0; --row) {
        if (auto* l = attributesForm_->itemAt(row, QFormLayout::LabelRole)) if (auto* lw = l->widget()) lw->deleteLater();
        if (auto* f = attributesForm_->itemAt(row, QFormLayout::FieldRole)) if (auto* fw = f->widget()) fw->deleteLater();
        attributesForm_->removeRow(row);
    }
}

void DetailsPanel::populateAttributes(Media* media) {
    if (!media || !attributesForm_) return;
    FrontendVisitors::TypeNameVisitor tn; media->accept(tn);
    attributesForm_->addRow("Type:", new QLabel(tn.typeName, attributesWidget_));
    struct AttrVisitor : MediaVisitor {
        QFormLayout* form;
        QWidget* parent;
        void visit(const Book& b) override {
            add("Publisher:", b.getPublisher());
            add("Pages:", QString::number(b.getPages()));
            add("ISBN:", b.getIsbn());
            add("Language:", b.getLanguageString());
            add("Genre:", b.getGenreString());
        }
        void visit(const Movie& m) override {
            add("Director:", m.getDirector());
            add("Duration:", QString::number(m.getDuration()) + " min");
            add("Studio:", m.getStudio());
            add("Rating:", m.getRating());
            add("Language:", m.getLanguageString());
            add("Country:", m.getCountry());
            add("Genre:", m.getGenreString());
        }
        void visit(const Song& s) override {
            add("Artist:", s.getArtist());
            add("Album:", s.getAlbum());
            add("Duration:", QString::number(s.getDuration()) + " s");
            add("Format:", s.getFormat());
            add("Label:", s.getLabel());
            add("Track:", QString::number(s.getTrackNumber()));
            add("Genre:", s.getGenreString());
        }
        void visit(const Magazine& mg) override {
            add("Publisher:", mg.getPublisher());
            add("Issue:", QString::number(mg.getIssueNumber()));
            add("ISSN:", mg.getIssn());
            add("Editor:", mg.getEditor());
            add("Pages:", QString::number(mg.getPages()));
            add("Frequency:", mg.getFrequency());
            add("Genre:", mg.getGenreString());
        }
        void visit(const Podcast& p) override {
            add("Host:", p.getHost());
            add("Episodes:", QString::number(p.getEpisodeNumber()));
            add("Platform:", p.getPlatform());
            add("Duration:", QString::number(p.getDuration()) + " min");
            add("Series:", p.getSeries());
            add("Description:", p.getDescription());
            add("Genre:", p.getGenreString());
        }
        void add(const QString& key, const QString& value) {
            form->addRow(key, new QLabel(value, parent));
        }
        void add(const QString& key, const std::string& value) { add(key, QString::fromStdString(value)); }
    } visitor; visitor.form = attributesForm_; visitor.parent = attributesWidget_;
    media->accept(visitor);
}

void DetailsPanel::showMedia(Media* media) {
    if (!media) return;
    titleLabel_->setText(QString::fromStdString(media->getTitle()));
    authorLabel_->setText("Author: " + QString::fromStdString(media->getAuthor()));
    yearLabel_->setText("Year: " + QString::fromStdString(media->getReleaseDate().toString()));

    auto loadPixmapWithFallbacks = [&](const QString& rawPath)->QPixmap{
        QPixmap p(rawPath);
        if (!p.isNull()) return p;
        const QStringList tries = {
            rawPath,
            QCoreApplication::applicationDirPath() + "/" + rawPath,
            QDir::currentPath() + "/" + rawPath,
            QString("%1/%2").arg(QDir::currentPath(), QString("src/Frontend/Resources/assets/%1").arg(QFileInfo(rawPath).fileName())),
            QString("src/Frontend/Resources/assets/%1").arg(QFileInfo(rawPath).fileName()),
        };
        for (const QString& t : tries) { QPixmap candidate(t); if (!candidate.isNull()) return candidate; }
        return QPixmap();
    };

    QPixmap pix = loadPixmapWithFallbacks(QString::fromStdString(media->getImagePath()));
    if (!pix.isNull()) {
        coverImage_->setPixmap(pix.scaled(coverImage_->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
        coverImage_->setText("");
    } else {
        coverImage_->setPixmap(QPixmap());
        coverImage_->setText(" ");
    }
    clearAttributes();
    populateAttributes(media);
}
