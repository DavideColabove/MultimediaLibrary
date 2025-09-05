#include "DetailsPanel.h"
#include <QFile>
#include <QPixmap>
#include <QPainter>
#include <QHBoxLayout>

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
    if (!media) return;
    if (auto b = dynamic_cast<Book*>(media)) {
        attributesForm_->addRow("Type:", new QLabel("Book", attributesWidget_));
        attributesForm_->addRow("Publisher:", new QLabel(QString::fromStdString(b->getPublisher()), attributesWidget_));
        attributesForm_->addRow("Pages:", new QLabel(QString::number(b->getPages()), attributesWidget_));
        attributesForm_->addRow("ISBN:", new QLabel(QString::fromStdString(b->getIsbn()), attributesWidget_));
        attributesForm_->addRow("Language:", new QLabel(QString::fromStdString(b->getLanguageString()), attributesWidget_));
        attributesForm_->addRow("Genre:", new QLabel(QString::fromStdString(b->getGenreString()), attributesWidget_));
    } else if (auto m = dynamic_cast<Movie*>(media)) {
        attributesForm_->addRow("Type:", new QLabel("Movie", attributesWidget_));
        attributesForm_->addRow("Director:", new QLabel(QString::fromStdString(m->getDirector()), attributesWidget_));
        attributesForm_->addRow("Duration:", new QLabel(QString::number(m->getDuration()) + " min", attributesWidget_));
        attributesForm_->addRow("Studio:", new QLabel(QString::fromStdString(m->getStudio()), attributesWidget_));
        attributesForm_->addRow("Rating:", new QLabel(QString::fromStdString(m->getRating()), attributesWidget_));
        attributesForm_->addRow("Language:", new QLabel(QString::fromStdString(m->getLanguageString()), attributesWidget_));
        attributesForm_->addRow("Country:", new QLabel(QString::fromStdString(m->getCountry()), attributesWidget_));
        attributesForm_->addRow("Genre:", new QLabel(QString::fromStdString(m->getGenreString()), attributesWidget_));
    } else if (auto s = dynamic_cast<Song*>(media)) {
        attributesForm_->addRow("Type:", new QLabel("Song", attributesWidget_));
        attributesForm_->addRow("Artist:", new QLabel(QString::fromStdString(s->getArtist()), attributesWidget_));
        attributesForm_->addRow("Album:", new QLabel(QString::fromStdString(s->getAlbum()), attributesWidget_));
        attributesForm_->addRow("Duration:", new QLabel(QString::number(s->getDuration()) + " s", attributesWidget_));
        attributesForm_->addRow("Format:", new QLabel(QString::fromStdString(s->getFormat()), attributesWidget_));
        attributesForm_->addRow("Label:", new QLabel(QString::fromStdString(s->getLabel()), attributesWidget_));
        attributesForm_->addRow("Track:", new QLabel(QString::number(s->getTrackNumber()), attributesWidget_));
        attributesForm_->addRow("Genre:", new QLabel(QString::fromStdString(s->getGenreString()), attributesWidget_));
    } else if (auto mg = dynamic_cast<Magazine*>(media)) {
        attributesForm_->addRow("Type:", new QLabel("Magazine", attributesWidget_));
        attributesForm_->addRow("Publisher:", new QLabel(QString::fromStdString(mg->getPublisher()), attributesWidget_));
        attributesForm_->addRow("Issue:", new QLabel(QString::number(mg->getIssueNumber()), attributesWidget_));
        attributesForm_->addRow("ISSN:", new QLabel(QString::fromStdString(mg->getIssn()), attributesWidget_));
        attributesForm_->addRow("Editor:", new QLabel(QString::fromStdString(mg->getEditor()), attributesWidget_));
        attributesForm_->addRow("Pages:", new QLabel(QString::number(mg->getPages()), attributesWidget_));
        attributesForm_->addRow("Frequency:", new QLabel(QString::fromStdString(mg->getFrequency()), attributesWidget_));
        attributesForm_->addRow("Genre:", new QLabel(QString::fromStdString(mg->getGenreString()), attributesWidget_));
    } else if (auto p = dynamic_cast<Podcast*>(media)) {
        attributesForm_->addRow("Type:", new QLabel("Podcast", attributesWidget_));
        attributesForm_->addRow("Host:", new QLabel(QString::fromStdString(p->getHost()), attributesWidget_));
        attributesForm_->addRow("Episodes:", new QLabel(QString::number(p->getEpisodeNumber()), attributesWidget_));
        attributesForm_->addRow("Platform:", new QLabel(QString::fromStdString(p->getPlatform()), attributesWidget_));
        attributesForm_->addRow("Duration:", new QLabel(QString::number(p->getDuration()) + " min", attributesWidget_));
        attributesForm_->addRow("Series:", new QLabel(QString::fromStdString(p->getSeries()), attributesWidget_));
        attributesForm_->addRow("Description:", new QLabel(QString::fromStdString(p->getDescription()), attributesWidget_));
        attributesForm_->addRow("Genre:", new QLabel(QString::fromStdString(p->getGenreString()), attributesWidget_));
    }
}

void DetailsPanel::showMedia(Media* media) {
    if (!media) return;
    titleLabel_->setText(QString::fromStdString(media->getTitle()));
    authorLabel_->setText("Author: " + QString::fromStdString(media->getAuthor()));
    yearLabel_->setText("Year: " + QString::fromStdString(media->getReleaseDate().toString()));

    QPixmap pix(QString::fromStdString(media->getImagePath()));
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
