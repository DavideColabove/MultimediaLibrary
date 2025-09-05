#pragma once
#include <QWidget>
#include <QFormLayout>
#include <QLineEdit>
#include <QSpinBox>
#include <QComboBox>
#include "../../../Backend/Enums/Genres.h"

// Forward declaration
class Magazine;

class MagazineFormWidget : public QWidget {
    Q_OBJECT
public:
    explicit MagazineFormWidget(QWidget* parent=nullptr);
    void populateFrom(const Magazine& mg);
    void applyTo(Magazine& mg) const;
    bool validate(QString& err) const;
    QFormLayout* layout() const { return form_; }
    int selectedGenre() const { return genreCombo_->currentData().toInt(); }
    QString publisher() const { return publisher_->text(); }
    int issue() const { return issue_->value(); }
    QString issn() const { return issn_->text(); }
    QString editor() const { return editor_->text(); }
    int pages() const { return pages_->value(); }
    QString frequency() const { return frequency_->text(); }
private:
    QFormLayout* form_{};
    QLineEdit* publisher_{};
    QSpinBox* issue_{};
    QLineEdit* issn_{};
    QLineEdit* editor_{};
    QSpinBox* pages_{};
    QLineEdit* frequency_{};
    QComboBox* genreCombo_{};
};
