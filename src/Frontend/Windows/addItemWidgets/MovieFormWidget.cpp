#include "MovieFormWidget.h"
#include "../../../Backend/Elements/Movie.h"
#include <QCompleter>
#include <QRegularExpression>
#include <QRegularExpressionValidator>

MovieFormWidget::MovieFormWidget(QWidget* parent): QWidget(parent) {
    form_ = new QFormLayout(this);
    director_ = new QLineEdit(this); director_->setMaxLength(120);
    duration_ = new QSpinBox(this); duration_->setRange(1, 999); duration_->setValue(120);
    rating_ = new QLineEdit(this); rating_->setPlaceholderText("e.g., PG-13, R, G"); rating_->setMaxLength(10);
    rating_->setValidator(new QRegularExpressionValidator(QRegularExpression("^[A-Za-z0-9+-]{1,10}$"), rating_));
    studio_ = new QLineEdit(this); studio_->setPlaceholderText("e.g., Warner Bros., Disney, Universal"); studio_->setMaxLength(120);

    languageCombo_ = new QComboBox(this); languageCombo_->setEditable(true);
    auto languages = Enums::getAllLanguages();
    for (size_t i = 0; i < languages.size(); ++i) languageCombo_->addItem(QString::fromStdString(languages[i]), static_cast<int>(i));
    languageCombo_->setInsertPolicy(QComboBox::NoInsert);
    languageCombo_->completer()->setFilterMode(Qt::MatchContains);
    languageCombo_->completer()->setCompletionMode(QCompleter::PopupCompletion);

    genreCombo_ = new QComboBox(this); genreCombo_->setEditable(true);
    auto movieGenres = Enums::getAllMovieGenres();
    for (size_t i = 0; i < movieGenres.size(); ++i) genreCombo_->addItem(QString::fromStdString(movieGenres[i]), static_cast<int>(i));
    genreCombo_->setInsertPolicy(QComboBox::NoInsert);
    genreCombo_->completer()->setFilterMode(Qt::MatchContains);
    genreCombo_->completer()->setCompletionMode(QCompleter::PopupCompletion);

    form_->addRow("Director:", director_);
    form_->addRow("Duration (minutes):", duration_);
    form_->addRow("Rating:", rating_);
    form_->addRow("Studio:", studio_);
    form_->addRow("Language:", languageCombo_);
    form_->addRow("Genre:", genreCombo_);
}

void MovieFormWidget::populateFrom(const Movie& m) {
    director_->setText(QString::fromStdString(m.getDirector()));
    duration_->setValue(static_cast<int>(m.getDuration()));
    studio_->setText(QString::fromStdString(m.getStudio()));
    rating_->setText(QString::fromStdString(m.getRating()));
    int langIdx = languageCombo_->findData(static_cast<int>(m.getLanguage()));
    if (langIdx >= 0) languageCombo_->setCurrentIndex(langIdx);
    int genreIdx = genreCombo_->findData(static_cast<int>(m.getGenre()));
    if (genreIdx >= 0) genreCombo_->setCurrentIndex(genreIdx);
}

void MovieFormWidget::applyTo(Movie& m) const {
    m.setGenre(static_cast<Enums::MovieGenre>(genreCombo_->currentData().toInt()))
     .setDirector(director_->text().toStdString())
     .setDuration(duration_->value())
     .setStudio(studio_->text().toStdString())
     .setRating(rating_->text().toStdString())
     .setLanguage(static_cast<Enums::Language>(languageCombo_->currentData().toInt()))
     .setCountry("Unknown");
}

bool MovieFormWidget::validate(QString& err) const {
    if (director_->text().trimmed().isEmpty()) { err = "Director is required for movies."; return false; }
    if (studio_->text().trimmed().isEmpty()) { err = "Studio is required for movies."; return false; }
    return true;
}
