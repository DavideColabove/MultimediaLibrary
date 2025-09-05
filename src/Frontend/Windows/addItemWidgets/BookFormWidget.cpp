#include "BookFormWidget.h"
#include "../../../Backend/Elements/Book.h"
#include <QCompleter>
#include <QRegularExpression>
#include <QRegularExpressionValidator>

BookFormWidget::BookFormWidget(QWidget* parent): QWidget(parent) {
    form_ = new QFormLayout(this);
    publisher_ = new QLineEdit(this);
    publisher_->setMaxLength(120);
    pages_ = new QSpinBox(this);
    pages_->setRange(1, 9999);
    pages_->setValue(300);
    isbn_ = new QLineEdit(this);
    isbn_->setPlaceholderText("ISBN-10 or ISBN-13");
    isbn_->setMaxLength(17);
    isbn_->setValidator(new QRegularExpressionValidator(QRegularExpression("^[0-9-]{10,17}$"), isbn_));

    languageCombo_ = new QComboBox(this);
    languageCombo_->setEditable(true);
    auto languages = Enums::getAllLanguages();
    for (size_t i = 0; i < languages.size(); ++i) languageCombo_->addItem(QString::fromStdString(languages[i]), static_cast<int>(i));
    languageCombo_->setInsertPolicy(QComboBox::NoInsert);
    languageCombo_->completer()->setFilterMode(Qt::MatchContains);
    languageCombo_->completer()->setCompletionMode(QCompleter::PopupCompletion);

    genreCombo_ = new QComboBox(this);
    genreCombo_->setEditable(true);
    auto bookGenres = Enums::getAllBookGenres();
    for (size_t i = 0; i < bookGenres.size(); ++i) genreCombo_->addItem(QString::fromStdString(bookGenres[i]), static_cast<int>(i));
    genreCombo_->setInsertPolicy(QComboBox::NoInsert);
    genreCombo_->completer()->setFilterMode(Qt::MatchContains);
    genreCombo_->completer()->setCompletionMode(QCompleter::PopupCompletion);

    form_->addRow("Publisher:", publisher_);
    form_->addRow("Pages:", pages_);
    form_->addRow("ISBN:", isbn_);
    form_->addRow("Language:", languageCombo_);
    form_->addRow("Genre:", genreCombo_);
}

void BookFormWidget::populateFrom(const Book& b) {
    publisher_->setText(QString::fromStdString(b.getPublisher()));
    pages_->setValue(static_cast<int>(b.getPages()));
    isbn_->setText(QString::fromStdString(b.getIsbn()));
    int langIdx = languageCombo_->findData(static_cast<int>(b.getLanguage()));
    if (langIdx >= 0) languageCombo_->setCurrentIndex(langIdx);
    int genreIdx = genreCombo_->findData(static_cast<int>(b.getGenre()));
    if (genreIdx >= 0) genreCombo_->setCurrentIndex(genreIdx);
}

void BookFormWidget::applyTo(Book& b) const {
    b.setGenre(static_cast<Enums::BookGenre>(genreCombo_->currentData().toInt()))
     .setPublisher(publisher_->text().toStdString())
     .setPages(pages_->value())
     .setIsbn(isbn_->text().toStdString())
     .setLanguage(static_cast<Enums::Language>(languageCombo_->currentData().toInt()));
}

bool BookFormWidget::validate(QString& err) const {
    if (publisher_->text().trimmed().isEmpty()) { err = "Publisher is required for books."; return false; }
    return true;
}
