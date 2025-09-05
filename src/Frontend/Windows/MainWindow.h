#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenuBar>
#include <QStatusBar>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QWidget>
#include <QAction>
#include <QMessageBox>
#include <QFileDialog>
#include <QListWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QScrollArea>
#include <QFrame>
#include <QStackedWidget>
#include <QComboBox>
#include <QCheckBox>
#include <QGroupBox>
#include <QFormLayout>

#include "../../Backend/Elements/Media.h"
#include "../../Backend/Elements/Book.h"
#include "../../Backend/Elements/Movie.h"
#include "../../Backend/Elements/Song.h"
#include "../../Backend/Elements/Magazine.h"
#include "../../Backend/Elements/Podcast.h"
#include "../../Backend/Library/Library.h"
#include "MediaCard.h"
#include "LeftSidebarWidget.h"
#include "TopBarWidget.h"
#include "MediaGridWidget.h"
#include "DetailsPanel.h"
#include "AddMediaDialog.h"
#include "SearchDialog.h"


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    
    MainWindow(QWidget *parent = nullptr);
    
    
    ~MainWindow();

protected:
    
    void resizeEvent(QResizeEvent *event) override;

private slots:
    
    void addMedia();
    void editMedia();
    void deleteMedia();
    void exportData();
    void importData();
    void about();
    void showShortcuts();
    
    
    void onMediaCardClicked(Media* media);
    void onBackToGridClicked();
    void onSearchTextChanged(const QString& text);
    void onAdvancedSearchClicked();
    void saveTriggered();
    void clearAdvancedFilters();
    void onSortChanged(int index);
    void onScrollBarRangeChanged();

private:
    
    void setupUI();
    void setupMenuBar();
    void setupStatusBar();
    void setupLeftSidebar();
    void setupCentralArea();
    void setupRightPanel();
    void setupConnections();
    void applyDarkTheme();
    
    
    bool mediaMatchesFilters(Media* media) const;
    QString categoryToType(const QString& category) const;
    
    
    QWidget *centralWidget;      
    QHBoxLayout *mainLayout;     
    
    
    LeftSidebarWidget* leftSidebar; 
    
    
    QWidget *centralArea;        
    QVBoxLayout *centralLayout;  
    TopBarWidget* topBar;        
    MediaGridWidget* mediaGrid;  
    
    
    DetailsPanel* detailsPanel;  
    
    
    QStackedWidget *stackedWidget; 
    QWidget *gridPage;           
    
    
    QAction *addAction;          
    QAction *editAction;         
    QAction *deleteAction;       
    QAction *exportAction;       
    QAction *importAction;       
    QAction *shortcutsAction;    
    QAction *saveAction;         
    QAction *aboutAction;        
    
    
    std::unique_ptr<Library> library;  
    Media* selectedMedia;              
    QString currentCategoryFilter;     
    QString currentSearchFilter;       
    AdvancedFilters advFilters;        
    QString currentSavePath;           
    
    
    enum class SortMode { 
        TitleAsc,   
        TitleDesc,  
        DateAsc,    
        DateDesc    
    };
    SortMode currentSortMode;          
    
    
    void refreshMediaGrid();           
    void clearMediaGrid();             
    void addMediaCard(Media* media, int row, int col); 
    void showMediaDetails(Media* media);               
    void hideMediaDetails();           
    void clearAttributesForm();        
    void populateAttributesForm(Media* media); 
    void filterMediaByCategory(const QString& category); 
    void applySearchFilter(const QString& searchText);   
    int computeColumnsForWidth(int availableWidth) const; 
};

#endif 