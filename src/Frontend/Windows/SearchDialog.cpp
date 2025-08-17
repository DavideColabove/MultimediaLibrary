#include "SearchDialog.h"
#include <QGroupBox>
#include "../../Backend/Enums/Genres.h"

static void fillGenres(QComboBox* combo, const std::vector<std::string>& names)
{
    combo->clear();
    combo->addItem("Any", -1);
    for (size_t i = 0; i < names.size(); ++i) {
        combo->addItem(QString::fromStdString(names[i]), i);
    }
}

SearchDialog::SearchDialog(const AdvancedFilters& initial, QWidget* parent)
    : QDialog(parent)
{
    setupUI();
    populateFrom(initial);
    setWindowTitle("Advanced Search");
    setModal(true);
    resize(500, 400);
}

void SearchDialog::setupUI()
{
    mainLayout = new QVBoxLayout(this);
    formLayout = new QFormLayout();

    typeCombo = new QComboBox(this);
    typeCombo->addItem("Any", "");
    typeCombo->addItem("Book", "Book");
    typeCombo->addItem("Movie", "Movie");
    typeCombo->addItem("Song", "Song");
    typeCombo->addItem("Magazine", "Magazine");
    typeCombo->addItem("Podcast", "Podcast");

    titleEdit = new QLineEdit(this);
    authorEdit = new QLineEdit(this);

    fromCheck = new QCheckBox("From", this);
    fromDate = new QDateEdit(QDate::currentDate(), this);
    fromDate->setCalendarPopup(true);
    toCheck = new QCheckBox("To", this);
    toDate = new QDateEdit(QDate::currentDate(), this);
    toDate->setCalendarPopup(true);
    availableCheck = new QCheckBox("Only available", this);

    QWidget* fromRow = new QWidget(this);
    QHBoxLayout* fromLay = new QHBoxLayout(fromRow);
    fromLay->setContentsMargins(0,0,0,0);
    fromLay->addWidget(fromCheck);
    fromLay->addWidget(fromDate);

    QWidget* toRow = new QWidget(this);
    QHBoxLayout* toLay = new QHBoxLayout(toRow);
    toLay->setContentsMargins(0,0,0,0);
    toLay->addWidget(toCheck);
    toLay->addWidget(toDate);

    formLayout->addRow("Type:", typeCombo);
    formLayout->addRow("Title contains:", titleEdit);
    formLayout->addRow("Author contains:", authorEdit);
    formLayout->addRow(fromRow);
    formLayout->addRow(toRow);
    formLayout->addRow(availableCheck);

    typeGroup = new QGroupBox("Type-specific", this);
    typeStack = new QStackedWidget(this);
    QVBoxLayout* typeLay = new QVBoxLayout(typeGroup);
    typeLay->addWidget(typeStack);

    bookPage = new QWidget(this); bookGenreCombo = new QComboBox(bookPage);
    moviePage = new QWidget(this); movieGenreCombo = new QComboBox(moviePage);
    songPage = new QWidget(this); musicGenreCombo = new QComboBox(songPage);
    magazinePage = new QWidget(this); magazineGenreCombo = new QComboBox(magazinePage);
    podcastPage = new QWidget(this); podcastGenreCombo = new QComboBox(podcastPage);

    auto bookLay = new QFormLayout(bookPage); bookLay->addRow("Book genre:", bookGenreCombo);
    auto movieLay = new QFormLayout(moviePage); movieLay->addRow("Movie genre:", movieGenreCombo);
    auto songLay = new QFormLayout(songPage); songLay->addRow("Music genre:", musicGenreCombo);
    auto magLay = new QFormLayout(magazinePage); magLay->addRow("Magazine genre:", magazineGenreCombo);
    auto podLay = new QFormLayout(podcastPage); podLay->addRow("Podcast genre:", podcastGenreCombo);

    typeStack->addWidget(new QWidget(this)); // Any
    typeStack->addWidget(bookPage);
    typeStack->addWidget(moviePage);
    typeStack->addWidget(songPage);
    typeStack->addWidget(magazinePage);
    typeStack->addWidget(podcastPage);

    // Popola i ComboBox dei generi usando gli enum invece di hardcodare
    fillGenres(bookGenreCombo, Enums::getAllBookGenres());
    fillGenres(movieGenreCombo, Enums::getAllMovieGenres());
    fillGenres(musicGenreCombo, Enums::getAllMusicGenres());
    fillGenres(magazineGenreCombo, Enums::getAllMagazineGenres());
    fillGenres(podcastGenreCombo, Enums::getAllPodcastGenres());

    // Buttons
    QHBoxLayout* btns = new QHBoxLayout();
    QPushButton* ok = new QPushButton("Apply", this);
    QPushButton* cancel = new QPushButton("Cancel", this);
    btns->addStretch();
    btns->addWidget(ok); btns->addWidget(cancel);

    mainLayout->addLayout(formLayout);
    mainLayout->addWidget(typeGroup);
    mainLayout->addLayout(btns);

    connect(typeCombo, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &SearchDialog::onTypeChanged);
    connect(ok, &QPushButton::clicked, this, &SearchDialog::onAccept);
    connect(cancel, &QPushButton::clicked, this, &SearchDialog::reject);
}

void SearchDialog::populateFrom(const AdvancedFilters& initial)
{
    current = initial;
    int typeIdx = 0;
    if (initial.type == "Book") typeIdx = 1;
    else if (initial.type == "Movie") typeIdx = 2;
    else if (initial.type == "Song") typeIdx = 3;
    else if (initial.type == "Magazine") typeIdx = 4;
    else if (initial.type == "Podcast") typeIdx = 5;
    typeCombo->setCurrentIndex(typeIdx);
    onTypeChanged(typeIdx);

    titleEdit->setText(initial.titleContains);
    authorEdit->setText(initial.authorContains);
    fromCheck->setChecked(initial.useDateFrom); fromDate->setDate(initial.dateFrom.isValid() ? initial.dateFrom : QDate::currentDate());
    toCheck->setChecked(initial.useDateTo); toDate->setDate(initial.dateTo.isValid() ? initial.dateTo : QDate::currentDate());
    availableCheck->setChecked(initial.onlyAvailable);

    bookGenreCombo->setCurrentIndex(bookGenreCombo->findData(initial.bookGenre));
    movieGenreCombo->setCurrentIndex(movieGenreCombo->findData(initial.movieGenre));
    musicGenreCombo->setCurrentIndex(musicGenreCombo->findData(initial.musicGenre));
    magazineGenreCombo->setCurrentIndex(magazineGenreCombo->findData(initial.magazineGenre));
    podcastGenreCombo->setCurrentIndex(podcastGenreCombo->findData(initial.podcastGenre));
}

void SearchDialog::onTypeChanged(int idx)
{
    typeStack->setCurrentIndex(idx);
}

void SearchDialog::onAccept()
{
    current.enabled = true;
    current.type = typeCombo->currentData().toString();
    current.titleContains = titleEdit->text();
    current.authorContains = authorEdit->text();
    current.useDateFrom = fromCheck->isChecked();
    current.dateFrom = fromDate->date();
    current.useDateTo = toCheck->isChecked();
    current.dateTo = toDate->date();
    current.onlyAvailable = availableCheck->isChecked();
    current.bookGenre = bookGenreCombo->currentData().toInt();
    current.movieGenre = movieGenreCombo->currentData().toInt();
    current.musicGenre = musicGenreCombo->currentData().toInt();
    current.magazineGenre = magazineGenreCombo->currentData().toInt();
    current.podcastGenre = podcastGenreCombo->currentData().toInt();
    accept();
}


