#include "MagazineFormWidget.h"
#include "../../../Backend/Elements/Magazine.h"
#include <QRegularExpression>
#include <QRegularExpressionValidator>
#include <QCompleter>

MagazineFormWidget::MagazineFormWidget(QWidget* parent): QWidget(parent) {
    form_ = new QFormLayout(this);
    publisher_ = new QLineEdit(this); publisher_->setMaxLength(120);
    issue_ = new QSpinBox(this); issue_->setRange(1, 999); issue_->setValue(1);
    issn_ = new QLineEdit(this); issn_->setPlaceholderText("ISSN xxxx-xxxx"); issn_->setMaxLength(9);
    issn_->setValidator(new QRegularExpressionValidator(QRegularExpression("^[0-9]{4}-?[0-9]{4}$"), issn_));
    editor_ = new QLineEdit(this); editor_->setMaxLength(120);
    pages_ = new QSpinBox(this); pages_->setRange(1, 999); pages_->setValue(50);
    frequency_ = new QLineEdit(this); frequency_->setPlaceholderText("e.g., Monthly, Weekly, Quarterly"); frequency_->setMaxLength(40);
    genreCombo_ = new QComboBox(this); genreCombo_->setEditable(true);
    auto magazineGenres = Enums::getAllMagazineGenres();
    for (size_t i = 0; i < magazineGenres.size(); ++i) genreCombo_->addItem(QString::fromStdString(magazineGenres[i]), static_cast<int>(i));
    genreCombo_->setInsertPolicy(QComboBox::NoInsert);
    genreCombo_->completer()->setFilterMode(Qt::MatchContains);
    genreCombo_->completer()->setCompletionMode(QCompleter::PopupCompletion);
    form_->addRow("Publisher:", publisher_);
    form_->addRow("Issue Number:", issue_);
    form_->addRow("ISSN:", issn_);
    form_->addRow("Editor:", editor_);
    form_->addRow("Pages:", pages_);
    form_->addRow("Frequency:", frequency_);
    form_->addRow("Genre:", genreCombo_);
}

void MagazineFormWidget::populateFrom(const Magazine& mg) {
    publisher_->setText(QString::fromStdString(mg.getPublisher()));
    issue_->setValue(static_cast<int>(mg.getIssueNumber()));
    issn_->setText(QString::fromStdString(mg.getIssn()));
    editor_->setText(QString::fromStdString(mg.getEditor()));
    pages_->setValue(static_cast<int>(mg.getPages()));
    frequency_->setText(QString::fromStdString(mg.getFrequency()));
    int genreIdx = genreCombo_->findData(static_cast<int>(mg.getGenre()));
    if (genreIdx >= 0) genreCombo_->setCurrentIndex(genreIdx);
}

void MagazineFormWidget::applyTo(Magazine& mg) const {
    mg.setGenre(static_cast<Enums::MagazineGenre>(genreCombo_->currentData().toInt()))
      .setPublisher(publisher_->text().toStdString())
      .setIssueNumber(issue_->value())
      .setIssn(issn_->text().toStdString())
      .setEditor(editor_->text().toStdString())
      .setPages(pages_->value())
      .setFrequency(frequency_->text().toStdString());
}

bool MagazineFormWidget::validate(QString& err) const {
    if (publisher_->text().trimmed().isEmpty()) { err = "Publisher is required for magazines."; return false; }
    return true;
}
