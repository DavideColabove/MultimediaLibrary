#include "SongFormWidget.h"
#include "../../../Backend/Elements/Song.h"
#include <QCompleter>

SongFormWidget::SongFormWidget(QWidget* parent): QWidget(parent) {
    form_ = new QFormLayout(this);
    artist_ = new QLineEdit(this); artist_->setMaxLength(120);
    album_ = new QLineEdit(this); album_->setMaxLength(120);
    duration_ = new QSpinBox(this); duration_->setRange(1, 999); duration_->setValue(180);

    genreCombo_ = new QComboBox(this); genreCombo_->setEditable(true);
    auto musicGenres = Enums::getAllMusicGenres();
    for (size_t i = 0; i < musicGenres.size(); ++i) genreCombo_->addItem(QString::fromStdString(musicGenres[i]), static_cast<int>(i));
    genreCombo_->setInsertPolicy(QComboBox::NoInsert);
    genreCombo_->completer()->setFilterMode(Qt::MatchContains);
    genreCombo_->completer()->setCompletionMode(QCompleter::PopupCompletion);

    form_->addRow("Artist:", artist_);
    form_->addRow("Album:", album_);
    form_->addRow("Duration (seconds):", duration_);
    form_->addRow("Genre:", genreCombo_);
}

void SongFormWidget::populateFrom(const Song& s) {
    artist_->setText(QString::fromStdString(s.getArtist()));
    album_->setText(QString::fromStdString(s.getAlbum()));
    duration_->setValue(static_cast<int>(s.getDuration()));
    int genreIdx = genreCombo_->findData(static_cast<int>(s.getGenre()));
    if (genreIdx >= 0) genreCombo_->setCurrentIndex(genreIdx);
}

void SongFormWidget::applyTo(Song& s) const {
    s.setGenre(static_cast<Enums::MusicGenre>(genreCombo_->currentData().toInt()))
     .setArtist(artist_->text().toStdString())
     .setAlbum(album_->text().toStdString())
     .setDuration(duration_->value());
}

bool SongFormWidget::validate(QString& err) const {
    if (artist_->text().trimmed().isEmpty()) { err = "Artist is required for songs."; return false; }
    return true;
}
