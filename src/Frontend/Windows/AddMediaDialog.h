#ifndef ADDMEDIADIALOG_H
#define ADDMEDIADIALOG_H

#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QLineEdit>
#include <QSpinBox>
#include <QComboBox>
#include <QPushButton>
#include <QLabel>
#include <QGroupBox>
#include <QCheckBox>
#include <QDateEdit>
#include <QMessageBox>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QMimeData>
#include <QScrollArea>
#include <QFrame>
#include <QStackedWidget>

#include "../../Backend/Elements/Media.h"
#include "../../Backend/Elements/Book.h"
#include "../../Backend/Elements/Movie.h"
#include "../../Backend/Elements/Song.h"
#include "../../Backend/Elements/Magazine.h"
#include "../../Backend/Elements/Podcast.h"
#include "../../Backend/Enums/Genres.h"
#include "../../Backend/Enums/Languages.h"


class CoverDropArea : public QFrame
{
    Q_OBJECT

public:
    
    explicit CoverDropArea(QWidget *parent = nullptr);
    
    
    QString getImagePath() const { return imagePath; }
    
    
    void setImagePath(const QString &path);

signals:
    
    void imageDropped(const QString &path);

protected:
    
    void dragEnterEvent(QDragEnterEvent *event) override;
    
    
    void dropEvent(QDropEvent *event) override;
    
    
    void paintEvent(QPaintEvent *event) override;
    

private:
    QString imagePath;     
    bool hasImage;         
    QPixmap coverPixmap;   
};


class AddMediaDialog : public QDialog
{
    Q_OBJECT

public:
    
    explicit AddMediaDialog(QWidget *parent = nullptr);
    
    
    explicit AddMediaDialog(Media *existingMediaToEdit, QWidget *parent = nullptr);
    
    
    ~AddMediaDialog();

    
    std::unique_ptr<Media> getCreatedMedia();

private slots:
    
    void onMediaTypeChanged(int index);
    
    
    void onAcceptClicked();
    
    
    void onCancelClicked();
    
    
    void onImageDropped(const QString &path);
    void onChooseImageClicked();
    void onRemoveImageClicked();

private:
    
    void setupUI();
    void setupCommonFields();
    void setupTypeSpecificFields();
    void setupConnections();
    void applyDarkTheme();
    
    
    void clearTypeSpecificFields();
    void setupBookFields(QFormLayout *layout);
    void setupMovieFields(QFormLayout *layout);
    void setupSongFields(QFormLayout *layout);
    void setupMagazineFields(QFormLayout *layout);
    void setupPodcastFields(QFormLayout *layout);
    
    
    bool validateInput();
    void showValidationError(const QString& message);
    void populateFromMedia(Media *media);
    int findIndexByData(QComboBox *combo, int value) const;

    
    QVBoxLayout *mainLayout;        
    QScrollArea *scrollArea;        
    QWidget *scrollContent;         
    
    
    QGroupBox *commonGroup;         
    QFormLayout *commonLayout;      
    QLineEdit *titleEdit;           
    QLineEdit *authorEdit;          
    QDateEdit *releaseDateEdit;     
    QSpinBox *sizeSpinBox;          
    QCheckBox *availableCheckBox;   
    CoverDropArea *coverDropArea;   
    QPushButton *chooseImageBtn;    
    QPushButton *removeImageBtn;    
    
    
    QComboBox *mediaTypeCombo;      
    
    
    QGroupBox *typeSpecificGroup;   
    QVBoxLayout *typeSpecificLayout; 
    QStackedWidget *typeSpecificStack; 
    
    
    QWidget *bookWidget;            
    QWidget *movieWidget;           
    QWidget *songWidget;            
    QWidget *magazineWidget;        
    QWidget *podcastWidget;         
    
    
    QLineEdit *publisherEdit;       
    QSpinBox *pagesSpinBox;         
    QLineEdit *isbnEdit;            
    QComboBox *languageCombo;       
    QComboBox *bookGenreCombo;      
    
    
    QLineEdit *directorEdit;        
    QSpinBox *durationSpinBox;      
    QLineEdit *ratingEdit;          
    QLineEdit *studioEdit;          
    QComboBox *movieGenreCombo;     
    
    
    QLineEdit *artistEdit;          
    QLineEdit *albumEdit;           
    QSpinBox *songDurationSpinBox;  
    QComboBox *musicGenreCombo;     
    
    
    QLineEdit *magazinePublisherEdit; 
    QSpinBox *issueSpinBox;         
    QLineEdit *issnEdit;            
    QLineEdit *editorEdit;          
    QSpinBox *magazinePagesSpinBox; 
    QLineEdit *frequencyEdit;       
    QComboBox *magazineGenreCombo;  
    
    
    QLineEdit *hostEdit;            
    QSpinBox *episodeSpinBox;       
    QLineEdit *platformEdit;        
    QSpinBox *podcastDurationSpinBox; 
    QLineEdit *seriesEdit;          
    QLineEdit *descriptionEdit;     
    QComboBox *podcastGenreCombo;   
    
    
    QHBoxLayout *buttonLayout;      
    QPushButton *acceptBtn;         
    QPushButton *cancelBtn;         
    
    
    std::unique_ptr<Media> createdMedia; 
    bool isEditMode = false;        
    Media *existingMedia = nullptr; 
};

#endif 
