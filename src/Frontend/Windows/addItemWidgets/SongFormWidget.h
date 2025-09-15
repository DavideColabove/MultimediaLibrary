#pragma once
#include <QWidget>
#include <QFormLayout>
#include <QLineEdit>
#include <QSpinBox>
#include <QComboBox>
#include "../../../Backend/Enums/Genres.h"

class Song;

class SongFormWidget : public QWidget {
    Q_OBJECT
    
    public:
        explicit SongFormWidget(QWidget* parent=nullptr);
        void populateFrom(const Song& s);
        void applyTo(Song& s) const;
        bool validate(QString& err) const;
        QFormLayout* layout() const { return form_; }
        int selectedGenre() const { return genreCombo_->currentData().toInt(); }
        QString artist() const { return artist_->text(); }
        QString album() const { return album_->text(); }
        int duration() const { return duration_->value(); }
    private:
        QFormLayout* form_{};
        QLineEdit* artist_{};
        QLineEdit* album_{};
        QSpinBox* duration_{};
        QComboBox* genreCombo_{};
};
