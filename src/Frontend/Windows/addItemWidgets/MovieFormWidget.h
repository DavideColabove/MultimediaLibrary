#pragma once
#include <QWidget>
#include <QFormLayout>
#include <QLineEdit>
#include <QSpinBox>
#include <QComboBox>
#include "../../../Backend/Enums/Genres.h"
#include "../../../Backend/Enums/Languages.h"

// Forward declaration to avoid heavy includes in header
class Movie;

class MovieFormWidget : public QWidget {
    Q_OBJECT
public:
    explicit MovieFormWidget(QWidget* parent=nullptr);
    void populateFrom(const Movie& m);
    void applyTo(Movie& m) const;
    bool validate(QString& err) const;
    QFormLayout* layout() const { return form_; }
    int selectedGenre() const { return genreCombo_->currentData().toInt(); }
    int selectedLanguage() const { return languageCombo_->currentData().toInt(); }
    QString director() const { return director_->text(); }
    int duration() const { return duration_->value(); }
    QString rating() const { return rating_->text(); }
    QString studio() const { return studio_->text(); }
private:
    QFormLayout* form_{};
    QLineEdit* director_{};
    QSpinBox* duration_{};
    QLineEdit* rating_{};
    QLineEdit* studio_{};
    QComboBox* languageCombo_{};
    QComboBox* genreCombo_{};
};
