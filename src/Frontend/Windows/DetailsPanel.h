#pragma once
#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QGroupBox>
#include <QFormLayout>
#include <QPushButton>
#include "../../Backend/Elements/Media.h"
#include "../../Backend/Elements/Book.h"
#include "../../Backend/Elements/Movie.h"
#include "../../Backend/Elements/Song.h"
#include "../../Backend/Elements/Magazine.h"
#include "../../Backend/Elements/Podcast.h"

class DetailsPanel : public QWidget {
    Q_OBJECT
public:
    explicit DetailsPanel(QWidget* parent = nullptr);
    void clear();
    void showMedia(Media* media);
signals:
    void backRequested();
    void editRequested();
    void deleteRequested();
private:
    QVBoxLayout* layout_{};
    QPushButton* backBtn_{};
    QLabel* coverImage_{};
    QLabel* titleLabel_{};
    QLabel* authorLabel_{};
    QLabel* yearLabel_{};
    QLabel* durationLabel_{};
    QLabel* summaryLabel_{};
    QLabel* coverPathLabel_{};
    QGroupBox* attributesGroup_{};
    QWidget* attributesWidget_{};
    QFormLayout* attributesForm_{};
    QPushButton* editBtn_{};
    QPushButton* deleteBtn_{};
    void setupUi();
    void clearAttributes();
    void populateAttributes(Media* media);
};
