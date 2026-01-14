#include "MainWindow.h"
#include <QApplication>
#include <QIcon>
#include <QStyle>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // Initialize library
    library = std::make_unique<Library>();
    
    setupUI();
    setupMenuBar();
    setupToolBar();
    setupStatusBar();
    setupTable();
    setupConnections();
    
    // Set window properties
    setWindowTitle("Multimedia Library");
    setMinimumSize(800, 600);
    resize(1200, 800);
}

MainWindow::~MainWindow()
{
}

void MainWindow::setupUI()
{
    centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);
    
    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);
    
    // Create table
    mediaTable = new QTableWidget(this);
    mainLayout->addWidget(mediaTable);
}

void MainWindow::setupMenuBar()
{
    QMenuBar *menuBar = this->menuBar();
    
    // File menu
    QMenu *fileMenu = menuBar->addMenu("&File");
    importAction = fileMenu->addAction("&Import...");
    exportAction = fileMenu->addAction("&Export...");
    fileMenu->addSeparator();
    fileMenu->addAction("E&xit", this, &QWidget::close);
    
    // Edit menu
    QMenu *editMenu = menuBar->addMenu("&Edit");
    addAction = editMenu->addAction("&Add Media...");
    editAction = editMenu->addAction("&Edit Media...");
    deleteAction = editMenu->addAction("&Delete Media");
    
    // Search menu
    QMenu *searchMenu = menuBar->addMenu("&Search");
    searchAction = searchMenu->addAction("&Search...");
    
    // Help menu
    QMenu *helpMenu = menuBar->addMenu("&Help");
    aboutAction = helpMenu->addAction("&About");
}

void MainWindow::setupToolBar()
{
    toolBar = addToolBar("Main Toolbar");
    toolBar->setMovable(false);
    
    toolBar->addAction(addAction);
    toolBar->addAction(editAction);
    toolBar->addAction(deleteAction);
    toolBar->addSeparator();
    toolBar->addAction(searchAction);
    toolBar->addSeparator();
    toolBar->addAction(exportAction);
}

void MainWindow::setupStatusBar()
{
    statusBarWidget = this->statusBar();
    statusBarWidget->showMessage("Ready");
}

void MainWindow::setupTable()
{
    // Set table properties
    mediaTable->setAlternatingRowColors(true);
    mediaTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    mediaTable->setSelectionMode(QAbstractItemView::SingleSelection);
    mediaTable->setSortingEnabled(true);
    
    // Set column headers
    QStringList headers;
    headers << "ID" << "Type" << "Title" << "Author" << "Genre" << "Release Date" << "Size (KB)" << "Available";
    mediaTable->setColumnCount(headers.size());
    mediaTable->setHorizontalHeaderLabels(headers);
    
    // Set column widths
    mediaTable->setColumnWidth(0, 50);   // ID
    mediaTable->setColumnWidth(1, 80);   // Type
    mediaTable->setColumnWidth(2, 200);  // Title
    mediaTable->setColumnWidth(3, 150);  // Author
    mediaTable->setColumnWidth(4, 120);  // Genre
    mediaTable->setColumnWidth(5, 100);  // Release Date
    mediaTable->setColumnWidth(6, 80);   // Size
    mediaTable->setColumnWidth(7, 80);   // Available
    
    // Make columns stretch
    mediaTable->horizontalHeader()->setStretchLastSection(true);
}

void MainWindow::setupConnections()
{
    // Connect menu actions
    connect(addAction, &QAction::triggered, this, &MainWindow::addMedia);
    connect(editAction, &QAction::triggered, this, &MainWindow::editMedia);
    connect(deleteAction, &QAction::triggered, this, &MainWindow::deleteMedia);
    connect(searchAction, &QAction::triggered, this, &MainWindow::searchMedia);
    connect(exportAction, &QAction::triggered, this, &MainWindow::exportData);
    connect(importAction, &QAction::triggered, this, &MainWindow::importData);
    connect(aboutAction, &QAction::triggered, this, &MainWindow::about);
}

void MainWindow::addMedia()
{
    statusBarWidget->showMessage("Add Media - Not implemented yet");
    // TODO: Implement AddMediaDialog
    // Example usage:
    // auto book = std::make_unique<Book>();
    // book->setTitle("Sample Book");
    // book->setAuthor("Sample Author");
    // library->addMedia(std::move(book));
    // refreshTable();
}

void MainWindow::editMedia()
{
    statusBarWidget->showMessage("Edit Media - Not implemented yet");
    // TODO: Implement EditMediaDialog
}

void MainWindow::deleteMedia()
{
    statusBarWidget->showMessage("Delete Media - Not implemented yet");
    // TODO: Implement delete functionality
    // Example usage:
    // int selectedRow = mediaTable->currentRow();
    // if (selectedRow >= 0) {
    //     int id = mediaTable->item(selectedRow, 0)->text().toInt();
    //     library->removeMedia(id);
    //     refreshTable();
    // }
}

void MainWindow::searchMedia()
{
    statusBarWidget->showMessage("Search Media - Not implemented yet");
    // TODO: Implement SearchDialog
}

void MainWindow::exportData()
{
    statusBarWidget->showMessage("Export Data - Not implemented yet");
    // TODO: Implement export functionality
    // Example usage:
    // QString filename = QFileDialog::getSaveFileName(this, "Export Library", "", "CSV Files (*.csv)");
    // if (!filename.isEmpty()) {
    //     library->saveToFile(filename.toStdString());
    // }
}

void MainWindow::importData()
{
    statusBarWidget->showMessage("Import Data - Not implemented yet");
    // TODO: Implement import functionality
    // Example usage:
    // QString filename = QFileDialog::getOpenFileName(this, "Import Library", "", "CSV Files (*.csv)");
    // if (!filename.isEmpty()) {
    //     library->loadFromFile(filename.toStdString());
    //     refreshTable();
    // }
}

void MainWindow::about()
{
    QMessageBox::about(this, "About Multimedia Library",
                      "Multimedia Library v1.0.0\n\n"
                      "A comprehensive media management application.\n\n"
                      "Features:\n"
                      "- Book management\n"
                      "- Movie management\n"
                      "- Music management\n"
                      "- Magazine management\n"
                      "- Podcast management");
}

void MainWindow::refreshTable()
{
    clearTable();
    
    auto allMedia = library->getAllMedia();
    for (size_t i = 0; i < allMedia.size(); ++i) {
        addMediaToTable(allMedia[i], i);
    }
}

void MainWindow::addMediaToTable(const Media* media, int row)
{
    if (!media) return;
    
    mediaTable->insertRow(row);
    
    // ID
    mediaTable->setItem(row, 0, new QTableWidgetItem(QString::number(media->getID())));
    
    // Type (using Library's getMediaType method)
    mediaTable->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(library->getMediaType(media))));
    
    // Title
    mediaTable->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(media->getTitle())));
    
    // Author
    mediaTable->setItem(row, 3, new QTableWidgetItem(QString::fromStdString(media->getAuthor())));
    
    // Genre (to be implemented in derived classes)
    mediaTable->setItem(row, 4, new QTableWidgetItem("N/A"));
    
    // Release Date
    mediaTable->setItem(row, 5, new QTableWidgetItem(QString::fromStdString(media->getReleaseDate().toString())));
    
    // Size
    mediaTable->setItem(row, 6, new QTableWidgetItem(QString::number(media->getKbSize())));
    
    // Available
    mediaTable->setItem(row, 7, new QTableWidgetItem(media->getIsAvailable() ? "Yes" : "No"));
}

void MainWindow::clearTable()
{
    mediaTable->setRowCount(0);
} 