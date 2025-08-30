#ifndef ITEM_EDIT_DIALOG_H
#define ITEM_EDIT_DIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QSpinBox>
#include <QDateEdit>
#include <QCheckBox>
#include <QComboBox>
#include <QStackedWidget>
#include <QDialogButtonBox>
#include <QLabel>
#include <QPushButton>
#include <memory>

class Library;
class Media;

class ItemEditDialog : public QDialog {
    Q_OBJECT
public:
    enum Mode { Create, Edit };
    ItemEditDialog(Library* library, Mode mode, Media* existing=nullptr, QWidget* parent=nullptr);
    std::unique_ptr<Media> takeResult();
    bool isModified() const { return modified; }
private slots:
    void browseImage();
    void accept() override;
private:
    Library* library;
    Mode mode;
    Media* existing;
    bool modified=false;

    // Common fields
    QLineEdit* titleEdit; QLineEdit* authorEdit; QDateEdit* dateEdit; QSpinBox* sizeEdit; QCheckBox* availableCheck; QLineEdit* imageEdit; QPushButton* imageBrowse; QComboBox* typeCombo; QLabel* idLabel;

    // Stacked pages for subtype specifics
    QStackedWidget* stack;
    // Book
    QLineEdit *bookPublisher, *bookIsbn; QSpinBox *bookPages; QComboBox *bookLanguage, *bookGenre;
    // Movie
    QLineEdit *movieDirector,*movieStudio,*movieRating,*movieCountry; QSpinBox *movieDuration; QComboBox *movieLanguage,*movieGenre;
    // Song
    QLineEdit *songArtist,*songAlbum,*songFormat,*songLabel; QSpinBox *songDuration,*songTrack; QComboBox *songGenre;
    // Magazine
    QLineEdit *magPublisher,*magIssn,*magEditor,*magFrequency; QSpinBox *magIssue,*magPages; QComboBox *magGenre;
    // Podcast
    QLineEdit *podHost,*podPlatform,*podSeries,*podDescription; QSpinBox *podEpisode,*podDuration; QComboBox *podGenre;

    void buildUI();
    QWidget* buildBookPage();
    QWidget* buildMoviePage();
    QWidget* buildSongPage();
    QWidget* buildMagazinePage();
    QWidget* buildPodcastPage();
    void loadExisting();
    std::unique_ptr<Media> buildMediaFromInputs();
};

#endif // ITEM_EDIT_DIALOG_H
