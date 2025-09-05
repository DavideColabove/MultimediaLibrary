#include "MainWindow.h"
#include <QApplication>
#include <QIcon>
#include <QStyle>
#include <QMouseEvent>
#include <QPainter>
#include <QScrollArea>
#include <QFrame>
#include <QComboBox>
#include <QCheckBox>
#include <QGroupBox>
#include <QSpacerItem>
#include <QShortcut>
#include <QFile>
#include <QScrollBar>
#include <QTimer>
#include <QCollator>
#include <QResizeEvent>
#include <QStandardPaths>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QListWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QMessageBox>
#include <QFileDialog>
#include <QDir>
#include <QFormLayout>
#include <QPixmap>
#include "../../Backend/Elements/MediaVisitor.h"
#include "../Visitors/FrontendVisitors.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), selectedMedia(nullptr)
{
    library = std::make_unique<Library>();
    currentCategoryFilter = "All";
    currentSearchFilter.clear();
    currentSavePath.clear();
    currentSortMode = SortMode::TitleAsc;
    
    setupUI();
    setupMenuBar();
    setupStatusBar();
    setupLeftSidebar();
    setupCentralArea();
    setupRightPanel();
    setupConnections();
    
    
    setWindowTitle("Multimedia Library");
    setMinimumSize(1200, 800);
    resize(1400, 900);
}

MainWindow::~MainWindow()
{
}

void MainWindow::setupUI()
{
    centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);
    
    mainLayout = new QHBoxLayout(centralWidget);
    mainLayout->setSpacing(0);
    mainLayout->setContentsMargins(0, 0, 0, 0);
}

void MainWindow::setupLeftSidebar()
{
    leftSidebar = new LeftSidebarWidget(this);
    connect(leftSidebar, &LeftSidebarWidget::categoryChanged, this, &MainWindow::filterMediaByCategory);
    mainLayout->addWidget(leftSidebar);
}

void MainWindow::setupCentralArea()
{
    centralArea = new QWidget(this);
    centralArea->setObjectName("centralArea");
    
    centralLayout = new QVBoxLayout(centralArea);
    centralLayout->setSpacing(0);
    centralLayout->setContentsMargins(0, 0, 0, 0);
    
    
    topBar = new TopBarWidget(centralArea);
    centralLayout->addWidget(topBar);
    
    
    mediaGrid = new MediaGridWidget(centralArea);
    centralLayout->addWidget(mediaGrid);
    
    mainLayout->addWidget(centralArea, 1);
    
    
    connect(topBar, &TopBarWidget::searchTextChanged, this, &MainWindow::onSearchTextChanged);
    connect(topBar, &TopBarWidget::advancedSearchRequested, this, &MainWindow::onAdvancedSearchClicked);
    connect(topBar, &TopBarWidget::clearFiltersRequested, this, &MainWindow::clearAdvancedFilters);
    connect(topBar, &TopBarWidget::sortChanged, this, &MainWindow::onSortChanged);
    connect(topBar, &TopBarWidget::addRequested, this, &MainWindow::addMedia);
    connect(topBar, &TopBarWidget::importRequested, this, &MainWindow::importData);
    connect(topBar, &TopBarWidget::exportRequested, this, &MainWindow::exportData);
    connect(topBar, &TopBarWidget::saveRequested, this, &MainWindow::saveTriggered);
    connect(mediaGrid, &MediaGridWidget::mediaClicked, this, &MainWindow::onMediaCardClicked);
}

void MainWindow::setupRightPanel()
{
    detailsPanel = new DetailsPanel(this);
    connect(detailsPanel, &DetailsPanel::backRequested, this, &MainWindow::onBackToGridClicked);
    connect(detailsPanel, &DetailsPanel::editRequested, this, &MainWindow::editMedia);
    connect(detailsPanel, &DetailsPanel::deleteRequested, this, &MainWindow::deleteMedia);
    mainLayout->addWidget(detailsPanel);
}

void MainWindow::setupMenuBar()
{
    QMenuBar *menuBar = this->menuBar();
    
    
    QMenu *fileMenu = menuBar->addMenu("&File");
    importAction = fileMenu->addAction("&Import...");
    exportAction = fileMenu->addAction("&Export...");
    saveAction = fileMenu->addAction("&Save");
    fileMenu->addSeparator();
    fileMenu->addAction("E&xit", this, &QWidget::close);
    
    
    QMenu *editMenu = menuBar->addMenu("&Edit");
    addAction = editMenu->addAction("&Add Media...");
    editAction = editMenu->addAction("&Edit Media...");
    deleteAction = editMenu->addAction("&Delete Media");
    
    addAction->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_N));
    editAction->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_E));
    deleteAction->setShortcut(QKeySequence(Qt::Key_Delete));
    importAction->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_I));
    exportAction->setShortcut(QKeySequence(Qt::CTRL | Qt::SHIFT | Qt::Key_E));
    saveAction->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_S));
    
    
    QMenu *helpMenu = menuBar->addMenu("&Help");
    shortcutsAction = helpMenu->addAction("Keyboard &Shortcuts");
    aboutAction = helpMenu->addAction("&About");
}

void MainWindow::setupStatusBar()
{
    QStatusBar *statusBar = this->statusBar();
    statusBar->showMessage("Ready");
}

void MainWindow::setupConnections()
{
    
    connect(addAction, &QAction::triggered, this, &MainWindow::addMedia);
    connect(editAction, &QAction::triggered, this, &MainWindow::editMedia);
    connect(deleteAction, &QAction::triggered, this, &MainWindow::deleteMedia);
    connect(exportAction, &QAction::triggered, this, &MainWindow::exportData);
    connect(importAction, &QAction::triggered, this, &MainWindow::importData);
    connect(saveAction, &QAction::triggered, this, &MainWindow::saveTriggered);
    connect(aboutAction, &QAction::triggered, this, &MainWindow::about);
    connect(shortcutsAction, &QAction::triggered, this, &MainWindow::showShortcuts);
    
    
    QShortcut* focusSearch = new QShortcut(QKeySequence(Qt::CTRL | Qt::Key_F), this);
    connect(focusSearch, &QShortcut::activated, [this]() {
        if (topBar && topBar->searchField()) { topBar->searchField()->setFocus(); topBar->searchField()->selectAll(); }
    });
}


void MainWindow::refreshMediaGrid()
{
    auto allMedia = library->getAllMedia();
    
    QCollator coll; coll.setCaseSensitivity(Qt::CaseInsensitive); coll.setNumericMode(true);
    std::sort(allMedia.begin(), allMedia.end(), [&](Media* a, Media* b){
        if (currentSortMode == SortMode::TitleAsc)
            return coll.compare(QString::fromStdString(a->getTitle()), QString::fromStdString(b->getTitle())) < 0;
        if (currentSortMode == SortMode::TitleDesc)
            return coll.compare(QString::fromStdString(a->getTitle()), QString::fromStdString(b->getTitle())) > 0;
        const Date& da = a->getReleaseDate(); const Date& db = b->getReleaseDate();
        if (currentSortMode == SortMode::DateAsc) return da < db; else return da > db;
    });
    
    std::vector<Media*> filtered;
    filtered.reserve(allMedia.size());
    for (auto* m : allMedia) if (mediaMatchesFilters(m)) filtered.push_back(m);
    if (mediaGrid) mediaGrid->setMedia(filtered);
    statusBar()->showMessage(QString("Total media: %1").arg(allMedia.size()));
}

 

 

void MainWindow::onMediaCardClicked(Media* media)
{
    selectedMedia = media;
    showMediaDetails(media);
}

void MainWindow::onBackToGridClicked()
{
    hideMediaDetails();
    
    
    QTimer::singleShot(100, this, &MainWindow::refreshMediaGrid);
}

void MainWindow::onSearchTextChanged(const QString& text)
{
    currentSearchFilter = text;
    refreshMediaGrid();
}

void MainWindow::onAdvancedSearchClicked()
{
    SearchDialog dlg(advFilters, this);
    if (dlg.exec() == QDialog::Accepted) {
        advFilters = dlg.criteria();
        refreshMediaGrid();
    }
}

void MainWindow::clearAdvancedFilters()
{
    advFilters = AdvancedFilters{}; 
    currentSearchFilter.clear();
    refreshMediaGrid();
    statusBar()->showMessage("Filtri avanzati rimossi", 2500);
}

 

void MainWindow::onSortChanged(int index)
{
    switch (index) {
        case 0: currentSortMode = SortMode::TitleAsc; break;
        case 1: currentSortMode = SortMode::TitleDesc; break;
        case 2: currentSortMode = SortMode::DateAsc; break;
        case 3: currentSortMode = SortMode::DateDesc; break;
        default: currentSortMode = SortMode::TitleAsc; break;
    }
    refreshMediaGrid();
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    QMainWindow::resizeEvent(event);
    
    
    QTimer::singleShot(100, this, &MainWindow::refreshMediaGrid);
}

 

void MainWindow::showMediaDetails(Media* media)
{
    if (!media) return;
    detailsPanel->show();
    detailsPanel->showMedia(media);
}

void MainWindow::hideMediaDetails()
{
    detailsPanel->hide();
    selectedMedia = nullptr;
}

 

void MainWindow::filterMediaByCategory(const QString& category)
{
    currentCategoryFilter = category;
    refreshMediaGrid();
}

 

bool MainWindow::mediaMatchesFilters(Media* media) const
{
    if (!media) return false;
    
    QString typeNeeded = categoryToType(currentCategoryFilter);
    if (!typeNeeded.isEmpty()) {
        FrontendVisitors::TypeNameVisitor v; media->accept(v);
        if (v.typeName != typeNeeded) return false;
    }
    
    if (advFilters.enabled && !advFilters.type.isEmpty()) {
        FrontendVisitors::TypeNameVisitor v; media->accept(v);
        if (v.typeName != advFilters.type) return false;
    }
    
    if (!currentSearchFilter.trimmed().isEmpty()) {
        const QString needle = currentSearchFilter.trimmed();
        QString title = QString::fromStdString(media->getTitle());
        QString author = QString::fromStdString(media->getAuthor());
        if (!title.contains(needle, Qt::CaseInsensitive) &&
            !author.contains(needle, Qt::CaseInsensitive)) {
            return false;
        }
    }
    
    if (advFilters.enabled) {
        if (!advFilters.titleContains.trimmed().isEmpty()) {
            if (!QString::fromStdString(media->getTitle()).contains(advFilters.titleContains, Qt::CaseInsensitive)) return false;
        }
        if (!advFilters.authorContains.trimmed().isEmpty()) {
            if (!QString::fromStdString(media->getAuthor()).contains(advFilters.authorContains, Qt::CaseInsensitive)) return false;
        }
        if (advFilters.onlyAvailable && !media->getIsAvailable()) return false;
        
        const Date& d = media->getReleaseDate();
        QDate qd(d.getYear(), d.getMonth(), d.getDay());
        if (advFilters.useDateFrom && qd < advFilters.dateFrom) return false;
        if (advFilters.useDateTo && qd > advFilters.dateTo) return false;
        
        FrontendVisitors::GenreCheckVisitor v(
            advFilters.bookGenre,
            advFilters.movieGenre,
            advFilters.musicGenre,
            advFilters.magazineGenre,
            advFilters.podcastGenre
        );
    media->accept(v);
    if (!v.ok) return false;
    }
    return true;
}

QString MainWindow::categoryToType(const QString& category) const
{
    if (category == "All" || category.isEmpty()) return QString();
    if (category == "Books") return "Book";
    if (category == "Movies") return "Movie";
    if (category == "Songs") return "Song";
    if (category == "Magazines") return "Magazine";
    if (category == "Podcasts") return "Podcast";
    return QString();
}


void MainWindow::addMedia()
{
    AddMediaDialog dialog(this);
    if (dialog.exec() == QDialog::Accepted) {
        auto newMedia = dialog.getCreatedMedia();
        if (newMedia) {
            library->addMedia(std::move(newMedia));
            refreshMediaGrid();
            statusBar()->showMessage("Media added successfully!", 3000);
        }
    }
}

void MainWindow::editMedia()
{
    if (!selectedMedia) {
        QMessageBox::information(this, "Edit", "Please select a media item first.");
        return;
    }
    
    AddMediaDialog dialog(selectedMedia, this);
    if (dialog.exec() == QDialog::Accepted) {
        
        refreshMediaGrid();
        statusBar()->showMessage("Media updated successfully!", 3000);
    }
}

void MainWindow::deleteMedia()
{
    if (!selectedMedia) {
        QMessageBox::information(this, "Delete", "Please select a media item first.");
        return;
    }
    
    QMessageBox::StandardButton reply = QMessageBox::question(this, "Delete Media", 
        QString("Are you sure you want to delete '%1'?").arg(QString::fromStdString(selectedMedia->getTitle())),
        QMessageBox::Yes | QMessageBox::No);
    
    if (reply == QMessageBox::Yes) {
        int mediaId = static_cast<int>(selectedMedia->getID());
        library->removeMedia(mediaId);
        selectedMedia = nullptr;
        hideMediaDetails();
        
        
        refreshMediaGrid();
        statusBar()->showMessage("Media deleted.", 3000);
    }
}

void MainWindow::exportData()
{
    QString filter = "JSON (*.json);;XML (*.xml)";
    QString defaultDir = QDir::homePath();
    QString selectedFilter;
    QString filePath = QFileDialog::getSaveFileName(this, "Export Library", defaultDir, filter, &selectedFilter);
    if (filePath.isEmpty()) return;

    
    if (selectedFilter.contains("*.json") && !filePath.endsWith(".json", Qt::CaseInsensitive)) {
        filePath += ".json";
    } else if (selectedFilter.contains("*.xml") && !filePath.endsWith(".xml", Qt::CaseInsensitive)) {
        filePath += ".xml";
    }

    bool ok = false;
    if (filePath.endsWith(".json", Qt::CaseInsensitive)) {
        ok = library->saveJson(filePath.toStdString());
    } else if (filePath.endsWith(".xml", Qt::CaseInsensitive)) {
        ok = library->saveXml(filePath.toStdString());
    } else {
        QMessageBox::warning(this, "Export", "Formato non supportato. Usa .json o .xml");
        return;
    }

    if (ok) {
        statusBar()->showMessage("Export completato: " + filePath, 4000);
        QMessageBox::information(this, "Export", "Esportazione completata con successo.");
    } else {
        QMessageBox::critical(this, "Export", "Errore durante l'esportazione del file.");
    }
}

void MainWindow::importData()
{
    QString filter = "JSON (*.json);;XML (*.xml)";
    QString defaultDir = QDir::homePath();
    QString filePath = QFileDialog::getOpenFileName(this, "Import Library", defaultDir, filter);
    if (filePath.isEmpty()) return;

    bool ok = false;
    if (filePath.endsWith(".json", Qt::CaseInsensitive)) {
        ok = library->loadJson(filePath.toStdString());
        currentSavePath = filePath;
    } else if (filePath.endsWith(".xml", Qt::CaseInsensitive)) {
        ok = library->loadXml(filePath.toStdString());
        currentSavePath = filePath;
    } else {
        QMessageBox::warning(this, "Import", "Formato non supportato. Seleziona un file .json o .xml");
        return;
    }

    if (ok) {
        selectedMedia = nullptr;
        hideMediaDetails();
        refreshMediaGrid();
        statusBar()->showMessage("Import completato: " + filePath, 4000);
        QMessageBox::information(this, "Import", "Importazione completata con successo.");
    } else {
        QMessageBox::critical(this, "Import", "Errore durante l'importazione del file.");
    }
}

void MainWindow::saveTriggered()
{
    
    if (currentSavePath.isEmpty()) {
        QString filter = "JSON (*.json);;XML (*.xml)";
        QString defaultDir = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);
        QString selectedFilter;
        QString path = QFileDialog::getSaveFileName(this, "Save Library", defaultDir + "/MultimediaLibrary.json", filter, &selectedFilter);
        if (path.isEmpty()) return;
        if (selectedFilter.contains("*.json") && !path.endsWith(".json", Qt::CaseInsensitive)) path += ".json";
        if (selectedFilter.contains("*.xml") && !path.endsWith(".xml", Qt::CaseInsensitive)) path += ".xml";
        currentSavePath = path;
    }

    bool ok = false;
    if (currentSavePath.endsWith(".json", Qt::CaseInsensitive)) {
        ok = library->saveJson(currentSavePath.toStdString());
    } else if (currentSavePath.endsWith(".xml", Qt::CaseInsensitive)) {
        ok = library->saveXml(currentSavePath.toStdString());
    } else {
        
        currentSavePath.clear();
        saveTriggered();
        return;
    }
    statusBar()->showMessage(ok ? "Salvato in " + currentSavePath : "Errore salvataggio", 3000);
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

void MainWindow::showShortcuts()
{
    QMessageBox::information(this, "Keyboard Shortcuts",
        "Ctrl+N: Add Media\n"
        "Ctrl+E: Edit Media\n"
        "Delete: Delete Media\n"
        "Ctrl+I: Import\n"
        "Ctrl+Shift+E: Export\n"
        "Ctrl+S: Save\n"
        "Ctrl+F: Focus search bar (click the search field)");
}