#include "PodcastFormWidget.h"
#include "../../../Backend/Elements/Podcast.h"
#include <QCompleter>

PodcastFormWidget::PodcastFormWidget(QWidget* parent): QWidget(parent) {
    form_ = new QFormLayout(this);
    host_ = new QLineEdit(this); host_->setMaxLength(120);
    episode_ = new QSpinBox(this); episode_->setRange(1, 999); episode_->setValue(1);
    platform_ = new QLineEdit(this); platform_->setPlaceholderText("e.g., Spotify, Apple Podcasts, Google Podcasts"); platform_->setMaxLength(120);
    duration_ = new QSpinBox(this); duration_->setRange(1, 999); duration_->setValue(30);
    series_ = new QLineEdit(this); series_->setMaxLength(120);
    description_ = new QLineEdit(this); description_->setPlaceholderText("Brief description of the podcast"); description_->setMaxLength(200);

    genreCombo_ = new QComboBox(this); genreCombo_->setEditable(true);
    auto podcastGenres = Enums::getAllPodcastGenres();
    for (size_t i = 0; i < podcastGenres.size(); ++i) genreCombo_->addItem(QString::fromStdString(podcastGenres[i]), static_cast<int>(i));
    genreCombo_->setInsertPolicy(QComboBox::NoInsert);
    genreCombo_->completer()->setFilterMode(Qt::MatchContains);
    genreCombo_->completer()->setCompletionMode(QCompleter::PopupCompletion);

    form_->addRow("Host:", host_);
    form_->addRow("Episode Number:", episode_);
    form_->addRow("Platform:", platform_);
    form_->addRow("Duration (minutes):", duration_);
    form_->addRow("Series:", series_);
    form_->addRow("Description:", description_);
    form_->addRow("Genre:", genreCombo_);
}

void PodcastFormWidget::populateFrom(const Podcast& p) {
    host_->setText(QString::fromStdString(p.getHost()));
    episode_->setValue(static_cast<int>(p.getEpisodeNumber()));
    platform_->setText(QString::fromStdString(p.getPlatform()));
    duration_->setValue(static_cast<int>(p.getDuration()));
    series_->setText(QString::fromStdString(p.getSeries()));
    description_->setText(QString::fromStdString(p.getDescription()));
    int genreIdx = genreCombo_->findData(static_cast<int>(p.getGenre()));
    if (genreIdx >= 0) genreCombo_->setCurrentIndex(genreIdx);
}

void PodcastFormWidget::applyTo(Podcast& p) const {
    p.setGenre(static_cast<Enums::PodcastGenre>(genreCombo_->currentData().toInt()))
     .setHost(host_->text().toStdString())
     .setEpisodeNumber(episode_->value())
     .setPlatform(platform_->text().toStdString())
     .setDuration(duration_->value())
     .setSeries(series_->text().toStdString())
     .setDescription(description_->text().toStdString());
}

bool PodcastFormWidget::validate(QString& err) const {
    if (host_->text().trimmed().isEmpty()) { err = "Host is required for podcasts."; return false; }
    return true;
}
