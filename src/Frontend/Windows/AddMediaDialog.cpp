#include "AddMediaDialog.h"
#include <QDate>
#include <QPainter>
#include <QMimeData>
#include <QFileInfo>
#include <QFont>
#include <QRegularExpression>
#include <QRegularExpressionValidator>
#include <QCompleter>
#include <QFileDialog>
#include <QMessageBox>
#include "../../Backend/Enums/Genres.h"
#include "../../Backend/Enums/Languages.h"

CoverDropArea::CoverDropArea(QWidget *parent): QFrame(parent), hasImage(false){
    setAcceptDrops(true);
    setMinimumSize(200, 150);
    setMaximumSize(300, 200);
    setFrameStyle(QFrame::Box);
}

void CoverDropArea::setImagePath(const QString &path){
    imagePath = path;
    if (!path.isEmpty()) {
        coverPixmap.load(path);
        hasImage = !coverPixmap.isNull();
    } else {
        hasImage = false;
        coverPixmap = QPixmap();
    }
    update();
}

void CoverDropArea::dragEnterEvent(QDragEnterEvent *event){
    if (event->mimeData()->hasUrls() || event->mimeData()->hasImage()) {
        event->acceptProposedAction();
    }
}

void CoverDropArea::dropEvent(QDropEvent *event){
    setStyleSheet("QFrame { border: 2px dashed #555; border-radius: 8px; background-color: #3c3c3c; padding: 10px; }");
    if (event->mimeData()->hasUrls()) {
        QList<QUrl> urls = event->mimeData()->urls();
        if (!urls.isEmpty()) {
            QString filePath = urls.first().toLocalFile();
            if (QFileInfo(filePath).suffix().toLower() == "jpg" || 
                QFileInfo(filePath).suffix().toLower() == "jpeg" ||
                QFileInfo(filePath).suffix().toLower() == "png" ||
                QFileInfo(filePath).suffix().toLower() == "bmp" ||
                QFileInfo(filePath).suffix().toLower() == "gif") {
                setImagePath(filePath);
                emit imageDropped(filePath);
            }
        }
    }
}

void CoverDropArea::paintEvent(QPaintEvent *event){
    QFrame::paintEvent(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::SmoothPixmapTransform);
    
    if (hasImage && !coverPixmap.isNull()) {
        QPixmap scaledPixmap = coverPixmap.scaled(size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
        int x = (width() - scaledPixmap.width()) / 2;
        int y = (height() - scaledPixmap.height()) / 2;
        painter.drawPixmap(x, y, scaledPixmap);
    } else {
        painter.setPen(QPen(Qt::white));
        painter.setFont(QFont("Arial", 10));
        painter.drawText(rect(), Qt::AlignCenter, "Drag & Drop Image");
    }
}



AddMediaDialog::AddMediaDialog(QWidget *parent): QDialog(parent){
    setupUI();
    setupCommonFields();
    setupTypeSpecificFields();
    setupConnections();
    typeSpecificStack->setCurrentIndex(0);
    
    setWindowTitle("Add New Media");
    setMinimumSize(600, 700);
    resize(800, 900);
    setModal(true);
}

AddMediaDialog::~AddMediaDialog(){}

AddMediaDialog::AddMediaDialog(Media *existingMediaToEdit, QWidget *parent): QDialog(parent), isEditMode(true), existingMedia(existingMediaToEdit){
    setupUI();
    setupCommonFields();
    setupTypeSpecificFields();
    setupConnections();

    if (existingMedia) {
        struct IndexVisitor : MediaVisitor {
            int idx{-1};
            void visit(const Book&) override { idx = 0; }
            void visit(const Movie&) override { idx = 1; }
            void visit(const Song&) override { idx = 2; }
            void visit(const Magazine&) override { idx = 3; }
            void visit(const Podcast&) override { idx = 4; }
        } v;
    existingMedia->accept(v);
    if (v.idx >= 0) typeSpecificStack->setCurrentIndex(v.idx);
        populateFromMedia(existingMedia);
        acceptBtn->setText("Save Changes");
        setWindowTitle("Edit Media");
        mediaTypeCombo->setEnabled(false);
    }

    setMinimumSize(600, 700);
    resize(800, 900);
    setModal(true);
}

void AddMediaDialog::setupUI(){
    mainLayout = new QVBoxLayout(this);
    mainLayout->setSpacing(20);
    mainLayout->setContentsMargins(20, 20, 20, 20);
    
    scrollArea = new QScrollArea(this);
    scrollContent = new QWidget();
    scrollArea->setWidget(scrollContent);
    scrollArea->setWidgetResizable(true);
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    
    QVBoxLayout *contentLayout = new QVBoxLayout(scrollContent);
    contentLayout->setSpacing(20);
    
    mediaTypeCombo = new QComboBox(this);
    mediaTypeCombo->addItem("Book");
    mediaTypeCombo->addItem("Movie");
    mediaTypeCombo->addItem("Song");
    mediaTypeCombo->addItem("Magazine");
    mediaTypeCombo->addItem("Podcast");
    contentLayout->addWidget(new QLabel("Media Type:"));
    contentLayout->addWidget(mediaTypeCombo);
    
    commonGroup = new QGroupBox("Common Information", this);
    commonLayout = new QFormLayout(commonGroup);
    contentLayout->addWidget(commonGroup);
    
    typeSpecificGroup = new QGroupBox("Type-Specific Information", this);
    typeSpecificLayout = new QVBoxLayout(typeSpecificGroup);
    typeSpecificStack = new QStackedWidget(this);
    typeSpecificLayout->addWidget(typeSpecificStack);
    contentLayout->addWidget(typeSpecificGroup);
    
    buttonLayout = new QHBoxLayout();
    acceptBtn = new QPushButton("Add Media", this);
    cancelBtn = new QPushButton("Cancel", this);
    buttonLayout->addStretch();
    buttonLayout->addWidget(acceptBtn);
    buttonLayout->addWidget(cancelBtn);
    mainLayout->addWidget(scrollArea);
    mainLayout->addLayout(buttonLayout);
}

void AddMediaDialog::setupCommonFields(){
    titleEdit = new QLineEdit(this);
    commonLayout->addRow("Title:", titleEdit);
    
    authorEdit = new QLineEdit(this);
    commonLayout->addRow("Author:", authorEdit);
    
    releaseDateEdit = new QDateEdit(this);
    releaseDateEdit->setDate(QDate::currentDate());
    releaseDateEdit->setCalendarPopup(true);
    commonLayout->addRow("Release Date:", releaseDateEdit);
    
    sizeSpinBox = new QSpinBox(this);
    sizeSpinBox->setRange(1, 999999);
    sizeSpinBox->setValue(1024);
    commonLayout->addRow("Size (KB):", sizeSpinBox);
    
    availableCheckBox = new QCheckBox(this);
    availableCheckBox->setChecked(true);
    commonLayout->addRow("Available:", availableCheckBox);
    
    
    QWidget *coverRow = new QWidget(this);
    QHBoxLayout *coverLayout = new QHBoxLayout(coverRow);
    coverLayout->setContentsMargins(0,0,0,0);
    coverDropArea = new CoverDropArea(this);
    chooseImageBtn = new QPushButton("Choose...", this);
    removeImageBtn = new QPushButton("Remove", this);
    coverLayout->addWidget(coverDropArea, 1);
    coverLayout->addSpacing(8);
    QVBoxLayout *actionsCol = new QVBoxLayout();
    actionsCol->setContentsMargins(0,0,0,0);
    actionsCol->addWidget(chooseImageBtn);
    actionsCol->addWidget(removeImageBtn);
    actionsCol->addStretch();
    coverLayout->addLayout(actionsCol);
    commonLayout->addRow("Cover Image:", coverRow);
}

void AddMediaDialog::setupTypeSpecificFields(){
    bookForm = new BookFormWidget(this);    bookWidget = bookForm;
    movieForm = new MovieFormWidget(this);  movieWidget = movieForm;
    songForm = new SongFormWidget(this);    songWidget = songForm;
    magazineForm = new MagazineFormWidget(this); magazineWidget = magazineForm;
    podcastForm = new PodcastFormWidget(this); podcastWidget = podcastForm;

    typeSpecificStack->addWidget(bookWidget);
    typeSpecificStack->addWidget(movieWidget);
    typeSpecificStack->addWidget(songWidget);
    typeSpecificStack->addWidget(magazineWidget);
    typeSpecificStack->addWidget(podcastWidget);
    
    typeSpecificStack->setCurrentIndex(0);
}

void AddMediaDialog::setupConnections(){
    connect(mediaTypeCombo, QOverload<int>::of(&QComboBox::currentIndexChanged),
            typeSpecificStack, &QStackedWidget::setCurrentIndex);
    connect(coverDropArea, &CoverDropArea::imageDropped,
            this, &AddMediaDialog::onImageDropped);
    connect(acceptBtn, &QPushButton::clicked,
            this, &AddMediaDialog::onAcceptClicked);
    connect(cancelBtn, &QPushButton::clicked,
            this, &AddMediaDialog::onCancelClicked);
    connect(chooseImageBtn, &QPushButton::clicked,
            this, &AddMediaDialog::onChooseImageClicked);
    connect(removeImageBtn, &QPushButton::clicked,
            this, &AddMediaDialog::onRemoveImageClicked);
}


void AddMediaDialog::onImageDropped(const QString &path){
    coverDropArea->setImagePath(path);
}

void AddMediaDialog::onChooseImageClicked(){
    const QString path = QFileDialog::getOpenFileName(this, "Choose Cover Image", QString(),
        "Images (*.png *.jpg *.jpeg *.bmp *.gif)");
    if (!path.isEmpty()) {
        coverDropArea->setImagePath(path);
    }
}

void AddMediaDialog::onRemoveImageClicked(){
    coverDropArea->setImagePath(QString());
}

void AddMediaDialog::onAcceptClicked(){
    if (!validateInput()) {
        return;
    }
    QDate releaseQDate = releaseDateEdit->date();
    Date date(releaseQDate.year(), releaseQDate.month(), releaseQDate.day());
    if (isEditMode && existingMedia) {
        existingMedia->setTitle(titleEdit->text().toStdString())
                     .setAuthor(authorEdit->text().toStdString())
                     .setReleaseDate(date)
                     .setKbSize(sizeSpinBox->value())
                     .setIsAvailable(availableCheckBox->isChecked())
                     .setImagePath(coverDropArea->getImagePath().toStdString());
        struct ApplyEditsVisitor : MediaVisitorMutable {
            AddMediaDialog* dlg; explicit ApplyEditsVisitor(AddMediaDialog* d) : dlg(d) {}
            void visit(Book& b) override { if (dlg->bookForm) dlg->bookForm->applyTo(b); }
            void visit(Movie& m) override { if (dlg->movieForm) dlg->movieForm->applyTo(m); }
            void visit(Song& s) override { if (dlg->songForm) dlg->songForm->applyTo(s); }
            void visit(Magazine& mg) override { if (dlg->magazineForm) dlg->magazineForm->applyTo(mg); }
            void visit(Podcast& p) override { if (dlg->podcastForm) dlg->podcastForm->applyTo(p); }
        } applyVisitor(this);
    if (existingMedia) existingMedia->accept(applyVisitor);
        accept();
        return;
    }
    int mediaType = mediaTypeCombo->currentIndex();
    switch (mediaType) {
        case 0: {
            auto book = std::make_unique<Book>(
                titleEdit->text().toStdString(),
                authorEdit->text().toStdString(),
                static_cast<Enums::BookGenre>(bookForm->selectedGenre()),
                date,
                0,
                sizeSpinBox->value(),
                availableCheckBox->isChecked(),
                coverDropArea->getImagePath().toStdString(),
                bookForm->publisher().toStdString(),
                bookForm->pages(),
                bookForm->isbn().toStdString(),
                static_cast<Enums::Language>(bookForm->selectedLanguage())
            );
            createdMedia = std::move(book);
            break;
        }
        case 1: {
            auto movie = std::make_unique<Movie>(
                titleEdit->text().toStdString(),
                authorEdit->text().toStdString(),
                static_cast<Enums::MovieGenre>(movieForm->selectedGenre()),
                date,
                0,
                sizeSpinBox->value(),
                availableCheckBox->isChecked(),
                coverDropArea->getImagePath().toStdString(),
                movieForm->director().toStdString(),
                movieForm->duration(),
                movieForm->studio().toStdString(),
                movieForm->rating().toStdString(),
                static_cast<Enums::Language>(movieForm->selectedLanguage()),
                std::string("Unknown")
            );
            createdMedia = std::move(movie);
            break;
        }
        case 2: {
            auto song = std::make_unique<Song>(
                titleEdit->text().toStdString(),
                authorEdit->text().toStdString(),
                static_cast<Enums::MusicGenre>(songForm->selectedGenre()),
                date,
                0,
                sizeSpinBox->value(),
                availableCheckBox->isChecked(),
                coverDropArea->getImagePath().toStdString(),
                songForm->artist().toStdString(),
                songForm->album().toStdString(),
                songForm->duration(),
                std::string("MP3"),
                std::string("Unknown"),
                1
            );
            createdMedia = std::move(song);
            break;
        }
        case 3: {
            auto magazine = std::make_unique<Magazine>(
                titleEdit->text().toStdString(),
                authorEdit->text().toStdString(),
                static_cast<Enums::MagazineGenre>(magazineForm->selectedGenre()),
                date,
                0,
                sizeSpinBox->value(),
                availableCheckBox->isChecked(),
                coverDropArea->getImagePath().toStdString(),
                magazineForm->publisher().toStdString(),
                magazineForm->issue(),
                magazineForm->issn().toStdString(),
                magazineForm->editor().toStdString(),
                magazineForm->pages(),
                magazineForm->frequency().toStdString()
            );
            createdMedia = std::move(magazine);
            break;
        }
        case 4: {
            auto podcast = std::make_unique<Podcast>(
                titleEdit->text().toStdString(),
                authorEdit->text().toStdString(),
                static_cast<Enums::PodcastGenre>(podcastForm->selectedGenre()),
                date,
                0,
                sizeSpinBox->value(),
                availableCheckBox->isChecked(),
                coverDropArea->getImagePath().toStdString(),
                podcastForm->host().toStdString(),
                podcastForm->episode(),
                podcastForm->platform().toStdString(),
                podcastForm->duration(),
                podcastForm->series().toStdString(),
                podcastForm->description().toStdString()
            );
            createdMedia = std::move(podcast);
            break;
        }
    }
    accept();
}

void AddMediaDialog::onCancelClicked(){
    reject();
}


bool AddMediaDialog::validateInput(){
    if (titleEdit->text().trimmed().isEmpty()) {
        showValidationError("Title is required.");
        return false;
    }
    if (authorEdit->text().trimmed().isEmpty()) {
        showValidationError("Author is required.");
        return false;
    }
    int mediaType = mediaTypeCombo->currentIndex();
    QString err;
    switch (mediaType) {
        case 0: if (bookForm && !bookForm->validate(err)) { showValidationError(err); return false; } break;
        case 1: if (movieForm && !movieForm->validate(err)) { showValidationError(err); return false; } break;
        case 2: if (songForm && !songForm->validate(err)) { showValidationError(err); return false; } break;
        case 3: if (magazineForm && !magazineForm->validate(err)) { showValidationError(err); return false; } break;
        case 4: if (podcastForm && !podcastForm->validate(err)) { showValidationError(err); return false; } break;
    }
    return true;
}

void AddMediaDialog::showValidationError(const QString& message){
    QMessageBox::warning(this, "Validation Error", message);
}

void AddMediaDialog::populateFromMedia(Media *media){
    if (!media) return;
    titleEdit->setText(QString::fromStdString(media->getTitle()));
    authorEdit->setText(QString::fromStdString(media->getAuthor()));
    const Date &d = media->getReleaseDate();
    releaseDateEdit->setDate(QDate(d.getYear(), d.getMonth(), d.getDay()));
    sizeSpinBox->setValue(static_cast<int>(media->getKbSize()));
    availableCheckBox->setChecked(media->getIsAvailable());
    coverDropArea->setImagePath(QString::fromStdString(media->getImagePath()));
    struct PopulateVisitor : MediaVisitor {
        AddMediaDialog* dlg;
        explicit PopulateVisitor(AddMediaDialog* d) : dlg(d) {}
        void visit(const Book& b) override {
            dlg->mediaTypeCombo->setCurrentIndex(0);
            dlg->bookForm->populateFrom(b);
        }
        void visit(const Movie& m) override {
            dlg->mediaTypeCombo->setCurrentIndex(1);
            dlg->movieForm->populateFrom(m);
        }
        void visit(const Song& s) override {
            dlg->mediaTypeCombo->setCurrentIndex(2);
            dlg->songForm->populateFrom(s);
        }
        void visit(const Magazine& mg) override {
            dlg->mediaTypeCombo->setCurrentIndex(3);
            dlg->magazineForm->populateFrom(mg);
        }
        void visit(const Podcast& p) override {
            dlg->mediaTypeCombo->setCurrentIndex(4);
            dlg->podcastForm->populateFrom(p);
        }
    } pop(this);
    media->accept(pop);
}

std::unique_ptr<Media> AddMediaDialog::getCreatedMedia(){
    return std::move(createdMedia);
}
