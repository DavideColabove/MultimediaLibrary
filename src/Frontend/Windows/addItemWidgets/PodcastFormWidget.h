#pragma once
#include <QWidget>
#include <QFormLayout>
#include <QLineEdit>
#include <QSpinBox>
#include <QComboBox>
#include "../../../Backend/Enums/Genres.h"

class Podcast;

class PodcastFormWidget : public QWidget {
    Q_OBJECT
    
    public:
        explicit PodcastFormWidget(QWidget* parent=nullptr);
        void populateFrom(const Podcast& p);
        void applyTo(Podcast& p) const;
        bool validate(QString& err) const;
        QFormLayout* layout() const { return form_; }
        int selectedGenre() const { return genreCombo_->currentData().toInt(); }
        QString host() const { return host_->text(); }
        int episode() const { return episode_->value(); }
        QString platform() const { return platform_->text(); }
        int duration() const { return duration_->value(); }
        QString series() const { return series_->text(); }
        QString description() const { return description_->text(); }
    private:
        QFormLayout* form_{};
        QLineEdit* host_{};
        QSpinBox* episode_{};
        QLineEdit* platform_{};
        QSpinBox* duration_{};
        QLineEdit* series_{};
        QLineEdit* description_{};
        QComboBox* genreCombo_{};
};
