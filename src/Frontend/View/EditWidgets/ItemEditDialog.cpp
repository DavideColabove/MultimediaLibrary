#include "ItemEditDialog.h"
#include <QVBoxLayout>
#include <QFormLayout>
#include <QPushButton>
#include <QFileDialog>
#include <QMessageBox>
#include <QDate>
#include "../../../Backend/Library/Library.h"
#include "../../../Backend/Elements/Media.h"
#include "../../../Backend/Elements/Book.h"
#include "../../../Backend/Elements/Movie.h"
#include "../../../Backend/Elements/Song.h"
#include "../../../Backend/Elements/Magazine.h"
#include "../../../Backend/Elements/Podcast.h"
#include "../../../Backend/Enums/Genres.h"
#include "../../../Backend/Enums/Languages.h"
#include "../../../Backend/Elements/Date.h"

ItemEditDialog::ItemEditDialog(Library* lib, Mode m, Media* existingMedia, QWidget* parent)
    : QDialog(parent), library(lib), mode(m), existing(existingMedia) {
    setWindowTitle(mode==Create?"Create Media":"Edit Media");
    buildUI();
    if (existing) loadExisting();
}

void ItemEditDialog::buildUI(){
    QVBoxLayout* main = new QVBoxLayout(this);
    QFormLayout* base = new QFormLayout();
    titleEdit = new QLineEdit();
    authorEdit = new QLineEdit();
    dateEdit = new QDateEdit(QDate::currentDate()); dateEdit->setCalendarPopup(true);
    sizeEdit = new QSpinBox(); sizeEdit->setRange(0, 10000000);
    availableCheck = new QCheckBox("Available"); availableCheck->setChecked(true);
    imageEdit = new QLineEdit(); imageBrowse = new QPushButton("Browse");
    connect(imageBrowse,&QPushButton::clicked,this,&ItemEditDialog::browseImage);
    QWidget* imgRow = new QWidget(); QHBoxLayout* imgLay = new QHBoxLayout(imgRow); imgLay->addWidget(imageEdit); imgLay->addWidget(imageBrowse); imgLay->setContentsMargins(0,0,0,0);
    typeCombo = new QComboBox(); typeCombo->addItems({"Book","Movie","Song","Magazine","Podcast"});
    base->addRow("Title", titleEdit);
    base->addRow("Author", authorEdit);
    base->addRow("Release Date", dateEdit);
    base->addRow("Size (KB)", sizeEdit);
    base->addRow("Image", imgRow);
    base->addRow("Type", typeCombo);
    base->addRow("Available", availableCheck);
    main->addLayout(base);

    stack = new QStackedWidget();
    stack->addWidget(buildBookPage());
    stack->addWidget(buildMoviePage());
    stack->addWidget(buildSongPage());
    stack->addWidget(buildMagazinePage());
    stack->addWidget(buildPodcastPage());
    main->addWidget(stack);
    connect(typeCombo, &QComboBox::currentTextChanged, [this](const QString& t){
        int idx = typeCombo->findText(t); if(idx>=0) stack->setCurrentIndex(idx);
    });

    QDialogButtonBox* bb = new QDialogButtonBox(QDialogButtonBox::Ok|QDialogButtonBox::Cancel);
    connect(bb,&QDialogButtonBox::accepted,this,&ItemEditDialog::accept);
    connect(bb,&QDialogButtonBox::rejected,this,&ItemEditDialog::reject);
    main->addWidget(bb);
    setLayout(main);
    resize(500,600);
}

QWidget* ItemEditDialog::buildBookPage(){
    QWidget* w = new QWidget(); QFormLayout* f = new QFormLayout(w);
    bookPublisher=new QLineEdit(); bookIsbn=new QLineEdit(); bookPages=new QSpinBox(); bookPages->setRange(0,100000);
    bookLanguage=new QComboBox(); for(const auto &lnStr:Enums::getAllLanguages()) { bookLanguage->addItem(QString::fromStdString(lnStr)); }
    bookGenre=new QComboBox(); for(const auto &gStr:Enums::getAllBookGenres()) { bookGenre->addItem(QString::fromStdString(gStr)); }
    f->addRow("Publisher", bookPublisher); f->addRow("ISBN", bookIsbn); f->addRow("Pages", bookPages); f->addRow("Language", bookLanguage); f->addRow("Genre", bookGenre);
    return w;
}
QWidget* ItemEditDialog::buildMoviePage(){
    QWidget* w = new QWidget(); QFormLayout* f = new QFormLayout(w);
    movieDirector=new QLineEdit(); movieStudio=new QLineEdit(); movieRating=new QLineEdit(); movieCountry=new QLineEdit(); movieDuration=new QSpinBox(); movieDuration->setRange(0,2000);
    movieLanguage=new QComboBox(); for(const auto &lnStr:Enums::getAllLanguages()) { movieLanguage->addItem(QString::fromStdString(lnStr)); }
    movieGenre=new QComboBox(); for(const auto &gStr:Enums::getAllMovieGenres()) { movieGenre->addItem(QString::fromStdString(gStr)); }
    f->addRow("Director", movieDirector); f->addRow("Studio", movieStudio); f->addRow("Rating", movieRating); f->addRow("Country", movieCountry); f->addRow("Duration", movieDuration); f->addRow("Language", movieLanguage); f->addRow("Genre", movieGenre);
    return w;
}
QWidget* ItemEditDialog::buildSongPage(){
    QWidget* w = new QWidget(); QFormLayout* f = new QFormLayout(w);
    songArtist=new QLineEdit(); songAlbum=new QLineEdit(); songFormat=new QLineEdit(); songLabel=new QLineEdit(); songDuration=new QSpinBox(); songDuration->setRange(0,100000); songTrack=new QSpinBox(); songTrack->setRange(0,1000);
    songGenre=new QComboBox(); for(const auto &gStr:Enums::getAllMusicGenres()) { songGenre->addItem(QString::fromStdString(gStr)); }
    f->addRow("Artist", songArtist); f->addRow("Album", songAlbum); f->addRow("Format", songFormat); f->addRow("Label", songLabel); f->addRow("Duration", songDuration); f->addRow("Track #", songTrack); f->addRow("Genre", songGenre);
    return w;
}
QWidget* ItemEditDialog::buildMagazinePage(){
    QWidget* w = new QWidget(); QFormLayout* f = new QFormLayout(w);
    magPublisher=new QLineEdit(); magIssn=new QLineEdit(); magEditor=new QLineEdit(); magFrequency=new QLineEdit(); magIssue=new QSpinBox(); magIssue->setRange(0,100000); magPages=new QSpinBox(); magPages->setRange(0,100000);
    magGenre=new QComboBox(); for(const auto &gStr:Enums::getAllMagazineGenres()) { magGenre->addItem(QString::fromStdString(gStr)); }
    f->addRow("Publisher", magPublisher); f->addRow("ISSN", magIssn); f->addRow("Editor", magEditor); f->addRow("Frequency", magFrequency); f->addRow("Issue #", magIssue); f->addRow("Pages", magPages); f->addRow("Genre", magGenre);
    return w;
}
QWidget* ItemEditDialog::buildPodcastPage(){
    QWidget* w = new QWidget(); QFormLayout* f = new QFormLayout(w);
    podHost=new QLineEdit(); podPlatform=new QLineEdit(); podSeries=new QLineEdit(); podDescription=new QLineEdit(); podEpisode=new QSpinBox(); podEpisode->setRange(0,100000); podDuration=new QSpinBox(); podDuration->setRange(0,100000);
    podGenre=new QComboBox(); for(const auto &gStr:Enums::getAllPodcastGenres()) { podGenre->addItem(QString::fromStdString(gStr)); }
    f->addRow("Host", podHost); f->addRow("Platform", podPlatform); f->addRow("Series", podSeries); f->addRow("Description", podDescription); f->addRow("Episode #", podEpisode); f->addRow("Duration", podDuration); f->addRow("Genre", podGenre);
    return w;
}

void ItemEditDialog::browseImage(){
    QString fp = QFileDialog::getOpenFileName(this,"Select Image","","Images (*.png *.jpg *.jpeg *.bmp)");
    if(!fp.isEmpty()) imageEdit->setText(fp);
}

void ItemEditDialog::loadExisting(){
    titleEdit->setText(QString::fromStdString(existing->getTitle()));
    authorEdit->setText(QString::fromStdString(existing->getAuthor()));
    dateEdit->setDate(QDate(existing->getReleaseDate().getYear(), existing->getReleaseDate().getMonth(), existing->getReleaseDate().getDay()));
    sizeEdit->setValue(existing->getKbSize());
    availableCheck->setChecked(existing->getIsAvailable());
    imageEdit->setText(QString::fromStdString(existing->getImagePath()));
    // Detect subtype and select proper page + prefill specific fields
    if(auto b = dynamic_cast<Book*>(existing)){
        typeCombo->setCurrentText("Book"); stack->setCurrentIndex(0);
        bookPublisher->setText(QString::fromStdString(b->getPublisher()));
        bookIsbn->setText(QString::fromStdString(b->getIsbn()));
        bookPages->setValue(b->getPages());
        // language & genre strings must match combobox entries
        int li = bookLanguage->findText(QString::fromStdString(b->getLanguageString())); if(li>=0) bookLanguage->setCurrentIndex(li);
        int gi = bookGenre->findText(QString::fromStdString(b->getGenreString())); if(gi>=0) bookGenre->setCurrentIndex(gi);
    } else if(auto mv = dynamic_cast<Movie*>(existing)){
        typeCombo->setCurrentText("Movie"); stack->setCurrentIndex(1);
        movieDirector->setText(QString::fromStdString(mv->getDirector()));
        movieStudio->setText(QString::fromStdString(mv->getStudio()));
        movieRating->setText(QString::fromStdString(mv->getRating()));
        movieCountry->setText(QString::fromStdString(mv->getCountry()));
        movieDuration->setValue(mv->getDuration());
        int li = movieLanguage->findText(QString::fromStdString(mv->getLanguageString())); if(li>=0) movieLanguage->setCurrentIndex(li);
        int gi = movieGenre->findText(QString::fromStdString(mv->getGenreString())); if(gi>=0) movieGenre->setCurrentIndex(gi);
    } else if(auto s = dynamic_cast<Song*>(existing)){
        typeCombo->setCurrentText("Song"); stack->setCurrentIndex(2);
        songArtist->setText(QString::fromStdString(s->getArtist()));
        songAlbum->setText(QString::fromStdString(s->getAlbum()));
        songFormat->setText(QString::fromStdString(s->getFormat()));
        songLabel->setText(QString::fromStdString(s->getLabel()));
        songDuration->setValue(s->getDuration());
        songTrack->setValue(s->getTrackNumber());
        int gi = songGenre->findText(QString::fromStdString(s->getGenreString())); if(gi>=0) songGenre->setCurrentIndex(gi);
    } else if(auto mg = dynamic_cast<Magazine*>(existing)){
        typeCombo->setCurrentText("Magazine"); stack->setCurrentIndex(3);
        magPublisher->setText(QString::fromStdString(mg->getPublisher()));
        magIssn->setText(QString::fromStdString(mg->getIssn()));
        magEditor->setText(QString::fromStdString(mg->getEditor()));
        magFrequency->setText(QString::fromStdString(mg->getFrequency()));
        magIssue->setValue(mg->getIssueNumber());
        magPages->setValue(mg->getPages());
        int gi = magGenre->findText(QString::fromStdString(mg->getGenreString())); if(gi>=0) magGenre->setCurrentIndex(gi);
    } else if(auto p = dynamic_cast<Podcast*>(existing)){
        typeCombo->setCurrentText("Podcast"); stack->setCurrentIndex(4);
        podHost->setText(QString::fromStdString(p->getHost()));
        podPlatform->setText(QString::fromStdString(p->getPlatform()));
        podSeries->setText(QString::fromStdString(p->getSeries()));
        podDescription->setText(QString::fromStdString(p->getDescription()));
        podEpisode->setValue(p->getEpisodeNumber());
        podDuration->setValue(p->getDuration());
        int gi = podGenre->findText(QString::fromStdString(p->getGenreString())); if(gi>=0) podGenre->setCurrentIndex(gi);
    }
}

std::unique_ptr<Media> ItemEditDialog::buildMediaFromInputs(){
    Date d(dateEdit->date().day(), dateEdit->date().month(), dateEdit->date().year());
    unsigned int id = existing? existing->getID() : library->getNextId();
    std::string type = typeCombo->currentText().toStdString();
    if (type=="Book") {
        auto lang = Enums::stringToLanguage(bookLanguage->currentText().toStdString());
        auto genre = Enums::stringToBookGenre(bookGenre->currentText().toStdString());
        return std::make_unique<Book>(titleEdit->text().toStdString(), authorEdit->text().toStdString(), genre, d, id, sizeEdit->value(), availableCheck->isChecked(), imageEdit->text().toStdString(), bookPublisher->text().toStdString(), bookPages->value(), bookIsbn->text().toStdString(), lang);
    } else if (type=="Movie") {
        auto lang = Enums::stringToLanguage(movieLanguage->currentText().toStdString());
        auto genre = Enums::stringToMovieGenre(movieGenre->currentText().toStdString());
        return std::make_unique<Movie>(titleEdit->text().toStdString(), authorEdit->text().toStdString(), genre, d, id, sizeEdit->value(), availableCheck->isChecked(), imageEdit->text().toStdString(), movieDirector->text().toStdString(), movieDuration->value(), movieStudio->text().toStdString(), movieRating->text().toStdString(), lang, movieCountry->text().toStdString());
    } else if (type=="Song") {
        auto genre = Enums::stringToMusicGenre(songGenre->currentText().toStdString());
        return std::make_unique<Song>(titleEdit->text().toStdString(), authorEdit->text().toStdString(), genre, d, id, sizeEdit->value(), availableCheck->isChecked(), imageEdit->text().toStdString(), songArtist->text().toStdString(), songAlbum->text().toStdString(), songDuration->value(), songFormat->text().toStdString(), songLabel->text().toStdString(), songTrack->value());
    } else if (type=="Magazine") {
        auto genre = Enums::stringToMagazineGenre(magGenre->currentText().toStdString());
        return std::make_unique<Magazine>(titleEdit->text().toStdString(), authorEdit->text().toStdString(), genre, d, id, sizeEdit->value(), availableCheck->isChecked(), imageEdit->text().toStdString(), magPublisher->text().toStdString(), magIssue->value(), magIssn->text().toStdString(), magEditor->text().toStdString(), magPages->value(), magFrequency->text().toStdString());
    } else { // Podcast
        auto genre = Enums::stringToPodcastGenre(podGenre->currentText().toStdString());
        return std::make_unique<Podcast>(titleEdit->text().toStdString(), authorEdit->text().toStdString(), genre, d, id, sizeEdit->value(), availableCheck->isChecked(), imageEdit->text().toStdString(), podHost->text().toStdString(), podEpisode->value(), podPlatform->text().toStdString(), podDuration->value(), podSeries->text().toStdString(), podDescription->text().toStdString());
    }
}

void ItemEditDialog::accept(){
    if(titleEdit->text().isEmpty()) { QMessageBox::warning(this,"Validation","Title required"); return; }
    modified=true;
    QDialog::accept();
}

std::unique_ptr<Media> ItemEditDialog::takeResult(){
    if(!modified) return nullptr;
    return buildMediaFromInputs();
}
