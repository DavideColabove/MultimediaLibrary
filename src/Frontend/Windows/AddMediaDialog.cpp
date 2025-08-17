#include "AddMediaDialog.h"
#include <QApplication>
#include <QStyle>
#include <QDate>
#include <QPainter>
#include <QMouseEvent>
#include <QMimeData>
#include <QFileInfo>
#include <QFont>
#include <QRegularExpression>
#include <QRegularExpressionValidator>
#include <QCompleter>
#include <QFileDialog>
#include "../../Backend/Enums/Genres.h"
#include "../../Backend/Enums/Languages.h"

CoverDropArea::CoverDropArea(QWidget *parent)
    : QFrame(parent), hasImage(false)
{
    setAcceptDrops(true);
    setMinimumSize(200, 150);
    setMaximumSize(300, 200);
    setFrameStyle(QFrame::Box);
    setStyleSheet("QFrame { border: 2px dashed #555; border-radius: 8px; background-color: #3c3c3c; padding: 10px; }");
}

void CoverDropArea::setImagePath(const QString &path)
{
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

void CoverDropArea::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasUrls() || event->mimeData()->hasImage()) {
        event->acceptProposedAction();
        setStyleSheet("QFrame { border: 2px dashed #0078d4; border-radius: 8px; background-color: #3c3c3c; padding: 10px; }");
    }
}

void CoverDropArea::dropEvent(QDropEvent *event)
{
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

void CoverDropArea::paintEvent(QPaintEvent *event)
{
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

void CoverDropArea::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        // No-op here; selection handled by external button to avoid modal inside paint area
    }
}

AddMediaDialog::AddMediaDialog(QWidget *parent)
    : QDialog(parent)
{
    setupUI();
    setupCommonFields();
    setupTypeSpecificFields();
    setupConnections();
    applyDarkTheme();
    
    clearTypeSpecificFields();
    
    onMediaTypeChanged(0);
    
    setWindowTitle("Add New Media");
    setMinimumSize(600, 700);
    resize(800, 900);
    setModal(true);
}

AddMediaDialog::~AddMediaDialog()
{
}

AddMediaDialog::AddMediaDialog(Media *existingMediaToEdit, QWidget *parent)
    : QDialog(parent), isEditMode(true), existingMedia(existingMediaToEdit)
{
    setupUI();
    setupCommonFields();
    setupTypeSpecificFields();
    setupConnections();
    applyDarkTheme();

    if (existingMedia) {
        if (dynamic_cast<Book*>(existingMedia)) {
            onMediaTypeChanged(0);
        } else if (dynamic_cast<Movie*>(existingMedia)) {
            onMediaTypeChanged(1);
        } else if (dynamic_cast<Song*>(existingMedia)) {
            onMediaTypeChanged(2);
        } else if (dynamic_cast<Magazine*>(existingMedia)) {
            onMediaTypeChanged(3);
        } else if (dynamic_cast<Podcast*>(existingMedia)) {
            onMediaTypeChanged(4);
        }
        populateFromMedia(existingMedia);
        acceptBtn->setText("Save Changes");
        setWindowTitle("Edit Media");
        mediaTypeCombo->setEnabled(false);
    }

    setMinimumSize(600, 700);
    resize(800, 900);
    setModal(true);
}

void AddMediaDialog::setupUI()
{
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

void AddMediaDialog::setupCommonFields()
{
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
    
    // Cover image area with actions
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

void AddMediaDialog::setupTypeSpecificFields()
{
    bookWidget = new QWidget(this);
    movieWidget = new QWidget(this);
    songWidget = new QWidget(this);
    magazineWidget = new QWidget(this);
    podcastWidget = new QWidget(this);
    
    QFormLayout *bookLayout = new QFormLayout(bookWidget);
    QFormLayout *movieLayout = new QFormLayout(movieWidget);
    QFormLayout *songLayout = new QFormLayout(songWidget);
    QFormLayout *magazineLayout = new QFormLayout(magazineWidget);
    QFormLayout *podcastLayout = new QFormLayout(podcastWidget);
    
    setupBookFields(bookLayout);
    setupMovieFields(movieLayout);
    setupSongFields(songLayout);
    setupMagazineFields(magazineLayout);
    setupPodcastFields(podcastLayout);
    
    typeSpecificStack->addWidget(bookWidget);
    typeSpecificStack->addWidget(movieWidget);
    typeSpecificStack->addWidget(songWidget);
    typeSpecificStack->addWidget(magazineWidget);
    typeSpecificStack->addWidget(podcastWidget);
    
    typeSpecificStack->setCurrentIndex(0);
}

void AddMediaDialog::setupBookFields(QFormLayout *layout)
{
    publisherEdit = new QLineEdit(this);
    publisherEdit->setMaxLength(120);
    pagesSpinBox = new QSpinBox(this);
    pagesSpinBox->setRange(1, 9999);
    pagesSpinBox->setValue(300);
    isbnEdit = new QLineEdit(this);
    isbnEdit->setPlaceholderText("ISBN-10 or ISBN-13");
    isbnEdit->setMaxLength(17);
    isbnEdit->setValidator(new QRegularExpressionValidator(QRegularExpression("^[0-9-]{10,17}$"), isbnEdit));
    
    languageCombo = new QComboBox(this);
    languageCombo->setEditable(true);
    
    // Popola da enum invece di hardcodare
    auto languages = Enums::getAllLanguages();
    for (size_t i = 0; i < languages.size(); ++i) {
        languageCombo->addItem(QString::fromStdString(languages[i]), i);
    }
    
    languageCombo->setInsertPolicy(QComboBox::NoInsert);
    languageCombo->completer()->setFilterMode(Qt::MatchContains);
    languageCombo->completer()->setCompletionMode(QCompleter::PopupCompletion);
    
    bookGenreCombo = new QComboBox(this);
    bookGenreCombo->setEditable(true);
    
    // Popola da enum invece di hardcodare
    auto bookGenres = Enums::getAllBookGenres();
    for (size_t i = 0; i < bookGenres.size(); ++i) {
        bookGenreCombo->addItem(QString::fromStdString(bookGenres[i]), i);
    }
    
    bookGenreCombo->setInsertPolicy(QComboBox::NoInsert);
    bookGenreCombo->completer()->setFilterMode(Qt::MatchContains);
    bookGenreCombo->completer()->setCompletionMode(QCompleter::PopupCompletion);
    
    layout->addRow("Publisher:", publisherEdit);
    layout->addRow("Pages:", pagesSpinBox);
    layout->addRow("ISBN:", isbnEdit);
    layout->addRow("Language:", languageCombo);
    layout->addRow("Genre:", bookGenreCombo);
}

void AddMediaDialog::setupMovieFields(QFormLayout *layout)
{
    directorEdit = new QLineEdit(this);
    directorEdit->setMaxLength(120);
    durationSpinBox = new QSpinBox(this);
    durationSpinBox->setRange(1, 999);
    durationSpinBox->setValue(120);
    ratingEdit = new QLineEdit(this);
    ratingEdit->setPlaceholderText("e.g., PG-13, R, G");
    ratingEdit->setMaxLength(10);
    ratingEdit->setValidator(new QRegularExpressionValidator(QRegularExpression("^[A-Za-z0-9+-]{1,10}$"), ratingEdit));
    studioEdit = new QLineEdit(this);
    studioEdit->setPlaceholderText("e.g., Warner Bros., Disney, Universal");
    studioEdit->setMaxLength(120);
    
    movieGenreCombo = new QComboBox(this);
    movieGenreCombo->setEditable(true);
    
    // Popola da enum invece di hardcodare
    auto movieGenres = Enums::getAllMovieGenres();
    for (size_t i = 0; i < movieGenres.size(); ++i) {
        movieGenreCombo->addItem(QString::fromStdString(movieGenres[i]), i);
    }
    
    movieGenreCombo->setInsertPolicy(QComboBox::NoInsert);
    movieGenreCombo->completer()->setFilterMode(Qt::MatchContains);
    movieGenreCombo->completer()->setCompletionMode(QCompleter::PopupCompletion);
    
    layout->addRow("Director:", directorEdit);
    layout->addRow("Duration (minutes):", durationSpinBox);
    layout->addRow("Rating:", ratingEdit);
    layout->addRow("Studio:", studioEdit);
    layout->addRow("Genre:", movieGenreCombo);
}

void AddMediaDialog::setupSongFields(QFormLayout *layout)
{
    artistEdit = new QLineEdit(this);
    artistEdit->setMaxLength(120);
    albumEdit = new QLineEdit(this);
    albumEdit->setMaxLength(120);
    songDurationSpinBox = new QSpinBox(this);
    songDurationSpinBox->setRange(1, 999);
    songDurationSpinBox->setValue(180);
    
    musicGenreCombo = new QComboBox(this);
    musicGenreCombo->setEditable(true);
    
    // Popola da enum invece di hardcodare
    auto musicGenres = Enums::getAllMusicGenres();
    for (size_t i = 0; i < musicGenres.size(); ++i) {
        musicGenreCombo->addItem(QString::fromStdString(musicGenres[i]), i);
    }
    
    musicGenreCombo->setInsertPolicy(QComboBox::NoInsert);
    musicGenreCombo->completer()->setFilterMode(Qt::MatchContains);
    musicGenreCombo->completer()->setCompletionMode(QCompleter::PopupCompletion);
    
    layout->addRow("Artist:", artistEdit);
    layout->addRow("Album:", albumEdit);
    layout->addRow("Duration (seconds):", songDurationSpinBox);
    layout->addRow("Genre:", musicGenreCombo);
}

void AddMediaDialog::setupMagazineFields(QFormLayout *layout)
{
    magazinePublisherEdit = new QLineEdit(this);
    magazinePublisherEdit->setMaxLength(120);
    issueSpinBox = new QSpinBox(this);
    issueSpinBox->setRange(1, 999);
    issueSpinBox->setValue(1);
    issnEdit = new QLineEdit(this);
    issnEdit->setPlaceholderText("ISSN xxxx-xxxx");
    issnEdit->setMaxLength(9);
    issnEdit->setValidator(new QRegularExpressionValidator(QRegularExpression("^[0-9]{4}-?[0-9]{4}$"), issnEdit));
    editorEdit = new QLineEdit(this);
    editorEdit->setMaxLength(120);
    magazinePagesSpinBox = new QSpinBox(this);
    magazinePagesSpinBox->setRange(1, 999);
    magazinePagesSpinBox->setValue(50);
    frequencyEdit = new QLineEdit(this);
    frequencyEdit->setPlaceholderText("e.g., Monthly, Weekly, Quarterly");
    frequencyEdit->setMaxLength(40);
    
    magazineGenreCombo = new QComboBox(this);
    magazineGenreCombo->setEditable(true);
    
    // Popola da enum invece di hardcodare
    auto magazineGenres = Enums::getAllMagazineGenres();
    for (size_t i = 0; i < magazineGenres.size(); ++i) {
        magazineGenreCombo->addItem(QString::fromStdString(magazineGenres[i]), i);
    }
    
    magazineGenreCombo->setInsertPolicy(QComboBox::NoInsert);
    magazineGenreCombo->completer()->setFilterMode(Qt::MatchContains);
    magazineGenreCombo->completer()->setCompletionMode(QCompleter::PopupCompletion);
    
    layout->addRow("Publisher:", magazinePublisherEdit);
    layout->addRow("Issue Number:", issueSpinBox);
    layout->addRow("ISSN:", issnEdit);
    layout->addRow("Editor:", editorEdit);
    layout->addRow("Pages:", magazinePagesSpinBox);
    layout->addRow("Frequency:", frequencyEdit);
    layout->addRow("Genre:", magazineGenreCombo);
}

void AddMediaDialog::setupPodcastFields(QFormLayout *layout)
{
    hostEdit = new QLineEdit(this);
    hostEdit->setMaxLength(120);
    episodeSpinBox = new QSpinBox(this);
    episodeSpinBox->setRange(1, 999);
    episodeSpinBox->setValue(1);
    platformEdit = new QLineEdit(this);
    platformEdit->setPlaceholderText("e.g., Spotify, Apple Podcasts, Google Podcasts");
    platformEdit->setMaxLength(120);
    podcastDurationSpinBox = new QSpinBox(this);
    podcastDurationSpinBox->setRange(1, 999);
    podcastDurationSpinBox->setValue(30);
    seriesEdit = new QLineEdit(this);
    seriesEdit->setMaxLength(120);
    descriptionEdit = new QLineEdit(this);
    descriptionEdit->setPlaceholderText("Brief description of the podcast");
    descriptionEdit->setMaxLength(200);
    
    podcastGenreCombo = new QComboBox(this);
    podcastGenreCombo->setEditable(true);
    
    // Popola da enum invece di hardcodare
    auto podcastGenres = Enums::getAllPodcastGenres();
    for (size_t i = 0; i < podcastGenres.size(); ++i) {
        podcastGenreCombo->addItem(QString::fromStdString(podcastGenres[i]), i);
    }
    
    podcastGenreCombo->setInsertPolicy(QComboBox::NoInsert);
    podcastGenreCombo->completer()->setFilterMode(Qt::MatchContains);
    podcastGenreCombo->completer()->setCompletionMode(QCompleter::PopupCompletion);
    
    layout->addRow("Host:", hostEdit);
    layout->addRow("Episode Number:", episodeSpinBox);
    layout->addRow("Platform:", platformEdit);
    layout->addRow("Duration (minutes):", podcastDurationSpinBox);
    layout->addRow("Series:", seriesEdit);
    layout->addRow("Description:", descriptionEdit);
    layout->addRow("Genre:", podcastGenreCombo);
}

void AddMediaDialog::setupConnections()
{
    connect(mediaTypeCombo, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &AddMediaDialog::onMediaTypeChanged);
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

void AddMediaDialog::applyDarkTheme()
{
    setStyleSheet(R"(
        QDialog {
            background-color: #2b2b2b;
            color: #ffffff;
        }
        
        QScrollArea {
            background-color: #2b2b2b;
            border: none;
        }
        
        QGroupBox {
            background-color: #3c3c3c;
            border: 1px solid #555;
            border-radius: 5px;
            margin-top: 10px;
            padding-top: 10px;
            font-weight: bold;
        }
        
        QGroupBox::title {
            subcontrol-origin: margin;
            left: 10px;
            padding: 0 5px 0 5px;
            color: #ffffff;
        }
        
        QLineEdit, QSpinBox, QComboBox, QDateEdit {
            background-color: #555;
            border: 1px solid #777;
            border-radius: 3px;
            padding: 5px;
            color: #ffffff;
        }
        
        QLineEdit:focus, QSpinBox:focus, QComboBox:focus, QDateEdit:focus {
            border: 1px solid #0078d4;
        }
        
        QPushButton {
            background-color: #0078d4;
            border: none;
            border-radius: 3px;
            padding: 8px 16px;
            color: #ffffff;
            font-weight: bold;
        }
        
        QPushButton:hover {
            background-color: #106ebe;
        }
        
        QPushButton:pressed {
            background-color: #005a9e;
        }
        
        QCheckBox {
            color: #ffffff;
        }
        
        QCheckBox::indicator {
            width: 16px;
            height: 16px;
        }
        
        QCheckBox::indicator:unchecked {
            background-color: #555;
            border: 1px solid #777;
            border-radius: 2px;
        }
        
        QCheckBox::indicator:checked {
            background-color: #0078d4;
            border: 1px solid #0078d4;
            border-radius: 2px;
        }
        
        QFrame {
            background-color: #3c3c3c;
            border: 2px dashed #555;
            border-radius: 8px;
            padding: 10px;
        }
        
        QFrame:hover {
            border-color: #777;
        }
    )");
}

void AddMediaDialog::onMediaTypeChanged(int index)
{
    typeSpecificStack->setCurrentIndex(index);
}

void AddMediaDialog::clearTypeSpecificFields()
{
    typeSpecificStack->setCurrentIndex(0);
}



void AddMediaDialog::onImageDropped(const QString &path)
{
    coverDropArea->setImagePath(path);
}

void AddMediaDialog::onChooseImageClicked()
{
    const QString path = QFileDialog::getOpenFileName(this, "Choose Cover Image", QString(),
        "Images (*.png *.jpg *.jpeg *.bmp *.gif)");
    if (!path.isEmpty()) {
        coverDropArea->setImagePath(path);
    }
}

void AddMediaDialog::onRemoveImageClicked()
{
    coverDropArea->setImagePath(QString());
}

void AddMediaDialog::onAcceptClicked()
{
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

        if (auto book = dynamic_cast<Book*>(existingMedia)) {
            book->setGenre(static_cast<Enums::BookGenre>(bookGenreCombo->currentData().toInt()))
                .setPublisher(publisherEdit->text().toStdString())
                .setPages(pagesSpinBox->value())
                .setIsbn(isbnEdit->text().toStdString())
                .setLanguage(static_cast<Enums::Language>(languageCombo->currentData().toInt()));
        } else if (auto movie = dynamic_cast<Movie*>(existingMedia)) {
            movie->setGenre(static_cast<Enums::MovieGenre>(movieGenreCombo->currentData().toInt()))
                 .setDirector(directorEdit->text().toStdString())
                 .setDuration(durationSpinBox->value())
                 .setStudio(studioEdit->text().toStdString())
                 .setRating(ratingEdit->text().toStdString())
                 .setLanguage(static_cast<Enums::Language>(languageCombo->currentData().toInt()))
                 .setCountry("Unknown");
        } else if (auto song = dynamic_cast<Song*>(existingMedia)) {
            song->setGenre(static_cast<Enums::MusicGenre>(musicGenreCombo->currentData().toInt()))
                .setArtist(artistEdit->text().toStdString())
                .setAlbum(albumEdit->text().toStdString())
                .setDuration(songDurationSpinBox->value());
        } else if (auto magazine = dynamic_cast<Magazine*>(existingMedia)) {
            magazine->setGenre(static_cast<Enums::MagazineGenre>(magazineGenreCombo->currentData().toInt()))
                    .setPublisher(magazinePublisherEdit->text().toStdString())
                    .setIssueNumber(issueSpinBox->value())
                    .setIssn(issnEdit->text().toStdString())
                    .setEditor(editorEdit->text().toStdString())
                    .setPages(magazinePagesSpinBox->value())
                    .setFrequency(frequencyEdit->text().toStdString());
        } else if (auto podcast = dynamic_cast<Podcast*>(existingMedia)) {
            podcast->setGenre(static_cast<Enums::PodcastGenre>(podcastGenreCombo->currentData().toInt()))
                   .setHost(hostEdit->text().toStdString())
                   .setEpisodeNumber(episodeSpinBox->value())
                   .setPlatform(platformEdit->text().toStdString())
                   .setDuration(podcastDurationSpinBox->value())
                   .setSeries(seriesEdit->text().toStdString())
                   .setDescription(descriptionEdit->text().toStdString());
        }
        accept();
        return;
    }

    int mediaType = mediaTypeCombo->currentIndex();
    switch (mediaType) {
        case 0: { // Book
            auto book = std::make_unique<Book>(
                titleEdit->text().toStdString(),
                authorEdit->text().toStdString(),
                static_cast<Enums::BookGenre>(bookGenreCombo->currentData().toInt()),
                date,
                0,
                sizeSpinBox->value(),
                availableCheckBox->isChecked(),
                coverDropArea->getImagePath().toStdString(),
                publisherEdit->text().toStdString(),
                pagesSpinBox->value(),
                isbnEdit->text().toStdString(),
                static_cast<Enums::Language>(languageCombo->currentData().toInt())
            );
            createdMedia = std::move(book);
            break;
        }
        case 1: { // Movie
            auto movie = std::make_unique<Movie>(
                titleEdit->text().toStdString(),
                authorEdit->text().toStdString(),
                static_cast<Enums::MovieGenre>(movieGenreCombo->currentData().toInt()),
                date,
                0,
                sizeSpinBox->value(),
                availableCheckBox->isChecked(),
                coverDropArea->getImagePath().toStdString(),
                directorEdit->text().toStdString(),
                durationSpinBox->value(),
                studioEdit->text().toStdString(),
                ratingEdit->text().toStdString(),
                static_cast<Enums::Language>(languageCombo->currentData().toInt()),
                "Unknown"
            );
            createdMedia = std::move(movie);
            break;
        }
        case 2: { // Song
            auto song = std::make_unique<Song>(
                titleEdit->text().toStdString(),
                authorEdit->text().toStdString(),
                static_cast<Enums::MusicGenre>(musicGenreCombo->currentData().toInt()),
                date,
                0,
                sizeSpinBox->value(),
                availableCheckBox->isChecked(),
                coverDropArea->getImagePath().toStdString(),
                artistEdit->text().toStdString(),
                albumEdit->text().toStdString(),
                songDurationSpinBox->value(),
                "MP3",
                "Unknown",
                1
            );
            createdMedia = std::move(song);
            break;
        }
        case 3: { // Magazine
            auto magazine = std::make_unique<Magazine>(
                titleEdit->text().toStdString(),
                authorEdit->text().toStdString(),
                static_cast<Enums::MagazineGenre>(magazineGenreCombo->currentData().toInt()),
                date,
                0,
                sizeSpinBox->value(),
                availableCheckBox->isChecked(),
                coverDropArea->getImagePath().toStdString(),
                magazinePublisherEdit->text().toStdString(),
                issueSpinBox->value(),
                issnEdit->text().toStdString(),
                editorEdit->text().toStdString(),
                magazinePagesSpinBox->value(),
                frequencyEdit->text().toStdString()
            );
            createdMedia = std::move(magazine);
            break;
        }
        case 4: { // Podcast
            auto podcast = std::make_unique<Podcast>(
                titleEdit->text().toStdString(),
                authorEdit->text().toStdString(),
                static_cast<Enums::PodcastGenre>(podcastGenreCombo->currentData().toInt()),
                date,
                0,
                sizeSpinBox->value(),
                availableCheckBox->isChecked(),
                coverDropArea->getImagePath().toStdString(),
                hostEdit->text().toStdString(),
                episodeSpinBox->value(),
                platformEdit->text().toStdString(),
                podcastDurationSpinBox->value(),
                seriesEdit->text().toStdString(),
                descriptionEdit->text().toStdString()
            );
            createdMedia = std::move(podcast);
            break;
        }
    }
    accept();
}

void AddMediaDialog::onCancelClicked()
{
    reject();
}

// Check required fields based on media type
bool AddMediaDialog::validateInput()
{
    if (titleEdit->text().trimmed().isEmpty()) {
        showValidationError("Title is required.");
        return false;
    }
    
    if (authorEdit->text().trimmed().isEmpty()) {
        showValidationError("Author is required.");
        return false;
    }
    
    // Type-specific validation
    int mediaType = mediaTypeCombo->currentIndex();
    switch (mediaType) {
        case 0: // Book
            if (publisherEdit->text().trimmed().isEmpty()) {
                showValidationError("Publisher is required for books.");
                return false;
            }
            break;
        case 1: // Movie
            if (directorEdit->text().trimmed().isEmpty()) {
                showValidationError("Director is required for movies.");
                return false;
            }
            if (studioEdit->text().trimmed().isEmpty()) {
                showValidationError("Studio is required for movies.");
                return false;
            }
            break;
        case 2: // Song
            if (artistEdit->text().trimmed().isEmpty()) {
                showValidationError("Artist is required for songs.");
                return false;
            }
            break;
        case 3: // Magazine
            if (magazinePublisherEdit->text().trimmed().isEmpty()) {
                showValidationError("Publisher is required for magazines.");
                return false;
            }
            break;
        case 4: // Podcast
            if (hostEdit->text().trimmed().isEmpty()) {
                showValidationError("Host is required for podcasts.");
                return false;
            }
            break;
    }
    
    return true;
}

void AddMediaDialog::showValidationError(const QString& message)
{
    QMessageBox::warning(this, "Validation Error", message);
}

int AddMediaDialog::findIndexByData(QComboBox *combo, int value) const
{
    for (int i = 0; i < combo->count(); ++i) {
        if (combo->itemData(i).toInt() == value) return i;
    }
    return -1;
}

void AddMediaDialog::populateFromMedia(Media *media)
{
    if (!media) return;
    // Common
    titleEdit->setText(QString::fromStdString(media->getTitle()));
    authorEdit->setText(QString::fromStdString(media->getAuthor()));
    const Date &d = media->getReleaseDate();
    releaseDateEdit->setDate(QDate(d.getYear(), d.getMonth(), d.getDay()));
    sizeSpinBox->setValue(static_cast<int>(media->getKbSize()));
    availableCheckBox->setChecked(media->getIsAvailable());
    coverDropArea->setImagePath(QString::fromStdString(media->getImagePath()));

    // Type-specific
    if (auto book = dynamic_cast<Book*>(media)) {
        mediaTypeCombo->setCurrentIndex(0);
        publisherEdit->setText(QString::fromStdString(book->getPublisher()));
        pagesSpinBox->setValue(static_cast<int>(book->getPages()));
        isbnEdit->setText(QString::fromStdString(book->getIsbn()));
        int langIdx = findIndexByData(languageCombo, static_cast<int>(book->getLanguage()));
        if (langIdx >= 0) languageCombo->setCurrentIndex(langIdx);
        int genreIdx = findIndexByData(bookGenreCombo, static_cast<int>(book->getGenre()));
        if (genreIdx >= 0) bookGenreCombo->setCurrentIndex(genreIdx);
    } else if (auto movie = dynamic_cast<Movie*>(media)) {
        mediaTypeCombo->setCurrentIndex(1);
        directorEdit->setText(QString::fromStdString(movie->getDirector()));
        durationSpinBox->setValue(static_cast<int>(movie->getDuration()));
        studioEdit->setText(QString::fromStdString(movie->getStudio()));
        ratingEdit->setText(QString::fromStdString(movie->getRating()));
        int langIdx = findIndexByData(languageCombo, static_cast<int>(movie->getLanguage()));
        if (langIdx >= 0) languageCombo->setCurrentIndex(langIdx);
        int genreIdx = findIndexByData(movieGenreCombo, static_cast<int>(movie->getGenre()));
        if (genreIdx >= 0) movieGenreCombo->setCurrentIndex(genreIdx);
    } else if (auto song = dynamic_cast<Song*>(media)) {
        mediaTypeCombo->setCurrentIndex(2);
        artistEdit->setText(QString::fromStdString(song->getArtist()));
        albumEdit->setText(QString::fromStdString(song->getAlbum()));
        songDurationSpinBox->setValue(static_cast<int>(song->getDuration()));
        int genreIdx = findIndexByData(musicGenreCombo, static_cast<int>(song->getGenre()));
        if (genreIdx >= 0) musicGenreCombo->setCurrentIndex(genreIdx);
    } else if (auto magazine = dynamic_cast<Magazine*>(media)) {
        mediaTypeCombo->setCurrentIndex(3);
        magazinePublisherEdit->setText(QString::fromStdString(magazine->getPublisher()));
        issueSpinBox->setValue(static_cast<int>(magazine->getIssueNumber()));
        issnEdit->setText(QString::fromStdString(magazine->getIssn()));
        editorEdit->setText(QString::fromStdString(magazine->getEditor()));
        magazinePagesSpinBox->setValue(static_cast<int>(magazine->getPages()));
        frequencyEdit->setText(QString::fromStdString(magazine->getFrequency()));
        int genreIdx = findIndexByData(magazineGenreCombo, static_cast<int>(magazine->getGenre()));
        if (genreIdx >= 0) magazineGenreCombo->setCurrentIndex(genreIdx);
    } else if (auto podcast = dynamic_cast<Podcast*>(media)) {
        mediaTypeCombo->setCurrentIndex(4);
        hostEdit->setText(QString::fromStdString(podcast->getHost()));
        episodeSpinBox->setValue(static_cast<int>(podcast->getEpisodeNumber()));
        platformEdit->setText(QString::fromStdString(podcast->getPlatform()));
        podcastDurationSpinBox->setValue(static_cast<int>(podcast->getDuration()));
        seriesEdit->setText(QString::fromStdString(podcast->getSeries()));
        descriptionEdit->setText(QString::fromStdString(podcast->getDescription()));
        int genreIdx = findIndexByData(podcastGenreCombo, static_cast<int>(podcast->getGenre()));
        if (genreIdx >= 0) podcastGenreCombo->setCurrentIndex(genreIdx);
    }
}

std::unique_ptr<Media> AddMediaDialog::getCreatedMedia()
{
    return std::move(createdMedia);
}
