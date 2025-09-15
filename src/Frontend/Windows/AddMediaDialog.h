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
#include "addItemWidgets/BookFormWidget.h"
#include "addItemWidgets/MovieFormWidget.h"
#include "addItemWidgets/SongFormWidget.h"
#include "addItemWidgets/MagazineFormWidget.h"
#include "addItemWidgets/PodcastFormWidget.h"
#include "../../Backend/Elements/Media.h"
#include "../../Backend/Elements/Book.h"
#include "../../Backend/Elements/Movie.h"
#include "../../Backend/Elements/Song.h"
#include "../../Backend/Elements/Magazine.h"
#include "../../Backend/Elements/Podcast.h"
#include "../../Backend/Enums/Genres.h"
#include "../../Backend/Enums/Languages.h"

class CoverDropArea : public QFrame{
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

class AddMediaDialog : public QDialog{
    Q_OBJECT

    public:
        explicit AddMediaDialog(QWidget *parent = nullptr);
        explicit AddMediaDialog(Media *existingMediaToEdit, QWidget *parent = nullptr);
        ~AddMediaDialog();
        std::unique_ptr<Media> getCreatedMedia();
    private slots:
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
        bool validateInput();
        void showValidationError(const QString& message);
        void populateFromMedia(Media *media);
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
        BookFormWidget* bookForm{};
        MovieFormWidget* movieForm{};
        SongFormWidget* songForm{};
        MagazineFormWidget* magazineForm{};
        PodcastFormWidget* podcastForm{};
        QHBoxLayout *buttonLayout;      
        QPushButton *acceptBtn;         
        QPushButton *cancelBtn;         
        std::unique_ptr<Media> createdMedia; 
        bool isEditMode = false;        
        Media *existingMedia = nullptr; 
};

#endif 
