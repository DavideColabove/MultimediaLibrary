#pragma once
#include <QWidget>
#include <QFormLayout>
#include <QLineEdit>
#include <QSpinBox>
#include <QComboBox>
#include "../../../Backend/Enums/Genres.h"
#include "../../../Backend/Enums/Languages.h"

class Book; // fwd decl

class BookFormWidget : public QWidget {
    Q_OBJECT
public:
    explicit BookFormWidget(QWidget* parent=nullptr);
    void populateFrom(const Book& b);
    void applyTo(Book& b) const;
    bool validate(QString& err) const;
    QFormLayout* layout() const { return form_; }
    // Accessors used by dialog
    QString publisher() const { return publisher_->text(); }
    int pages() const { return pages_->value(); }
    QString isbn() const { return isbn_->text(); }
    int selectedGenre() const { return genreCombo_->currentData().toInt(); }
    int selectedLanguage() const { return languageCombo_->currentData().toInt(); }
private:
    QFormLayout* form_{};
    QLineEdit* publisher_{};
    QSpinBox* pages_{};
    QLineEdit* isbn_{};
    QComboBox* languageCombo_{};
    QComboBox* genreCombo_{};
};
