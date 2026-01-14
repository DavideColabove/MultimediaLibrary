#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenuBar>
#include <QToolBar>
#include <QStatusBar>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QWidget>
#include <QAction>
#include <QMessageBox>
#include <QFileDialog>
#include <QHeaderView>

#include "../../Backend/Elements/Media.h"
#include "../../Backend/Elements/Book.h"
#include "../../Backend/Elements/Movie.h"
#include "../../Backend/Elements/Song.h"
#include "../../Backend/Elements/Magazine.h"
#include "../../Backend/Elements/Podcast.h"
#include "../../Backend/Library/Library.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void addMedia();
    void editMedia();
    void deleteMedia();
    void searchMedia();
    void exportData();
    void importData();
    void about();

private:
    void setupUI();
    void setupMenuBar();
    void setupToolBar();
    void setupStatusBar();
    void setupTable();
    void setupConnections();
    
    // UI Components
    QWidget *centralWidget;
    QTableWidget *mediaTable;
    QToolBar *toolBar;
    QStatusBar *statusBarWidget;
    
    // Actions
    QAction *addAction;
    QAction *editAction;
    QAction *deleteAction;
    QAction *searchAction;
    QAction *exportAction;
    QAction *importAction;
    QAction *aboutAction;
    
    // Data
    std::unique_ptr<Library> library;
    
    // Helper methods
    void refreshTable();
    void addMediaToTable(const Media* media, int row);
    void clearTable();
};

#endif // MAINWINDOW_H 