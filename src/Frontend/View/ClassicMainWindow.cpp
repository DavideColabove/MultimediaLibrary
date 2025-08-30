#include "ClassicMainWindow.h" // will be renamed to MainWindow in follow-up patch
#include <QToolBar>
#include <QToolButton>
#include <QAction>
#include <QMenu>
#include <QSplitter>
#include <QMessageBox>
#include <QFileDialog>
#include <QCloseEvent>
#include <QLabel>
#include <QComboBox>
#include <QCheckBox>
#include <QIcon>
#include <QShortcut>
#include <QKeySequence>

#include "../../Backend/Library/Library.h"
#include "../../Backend/Elements/Media.h"
#include "ListWidgets/ItemListWidget.h"
#include "DetailWidgets/ItemDetailWidget.h"
#include "EditWidgets/ItemEditDialog.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), library(std::make_unique<Library>()) {
    setupToolBar();
    setupCentralWidgets();
    setupShortcuts();
    setWindowTitle("MultimediaLibrary");
    resize(1100,650);
}

MainWindow::~MainWindow() {}

void MainWindow::setupToolBar() {
    fileToolButton = new QToolButton(this);
    fileToolButton->setText(" File");
    fileToolButton->setPopupMode(QToolButton::InstantPopup);
    fileToolButton->setStyleSheet("QToolButton::menu-indicator { image: none; }");
    newMediaAct = new QAction(QIcon(":/icons/add.svg"), " New Media");
    openFileAct = new QAction(QIcon(":/icons/import.svg"), " Open");
    saveAct = new QAction(QIcon(":/icons/save.svg"), " Save");
    infoAct = new QAction(QIcon(":/icons/appicon.svg"), " Info");
    newFileAct = new QAction(QIcon(":/icons/all.svg"), " New File");

    QMenu* fileMenu = new QMenu();
    fileMenu->addAction(newFileAct);
    fileMenu->addAction(openFileAct);
    fileMenu->addAction(saveAct);
    fileToolButton->setMenu(fileMenu);

    connect(newMediaAct, &QAction::triggered, this, &MainWindow::createNewMedia);
    connect(newFileAct, &QAction::triggered, this, &MainWindow::createNewFile);
    connect(openFileAct, &QAction::triggered, this, &MainWindow::openExistingFile);
    connect(saveAct, &QAction::triggered, this, &MainWindow::saveAll);
    connect(infoAct, &QAction::triggered, this, &MainWindow::showInfo);

    toolBar = addToolBar("ToolBar");
    toolBar->addWidget(fileToolButton);
    toolBar->addAction(newMediaAct);
    toolBar->addAction(infoAct);
    toolBar->setMovable(false);
    toolBar->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    // Filters & sorting
    typeFilter = new QComboBox(this);
    typeFilter->addItem(QIcon(":/icons/all.svg"), "All");
    typeFilter->addItem(QIcon(":/icons/book.svg"), "Book");
    typeFilter->addItem(QIcon(":/icons/movie.svg"), "Movie");
    typeFilter->addItem(QIcon(":/icons/music.svg"), "Song");
    typeFilter->addItem(QIcon(":/icons/magazine.svg"), "Magazine");
    typeFilter->addItem(QIcon(":/icons/podcast.svg"), "Podcast");
    sortCombo = new QComboBox(this);
    sortCombo->addItems({"Title A-Z","Title Z-A","Author A-Z","Author Z-A","Date Newest","Date Oldest"});
    availableOnlyCheck = new QCheckBox("Available", this);
    toolBar->addSeparator();
    toolBar->addWidget(typeFilter);
    toolBar->addWidget(sortCombo);
    toolBar->addWidget(availableOnlyCheck);
    // Style: make search placeholder visible later; availability like a toggle button
    availableOnlyCheck->setStyleSheet("QCheckBox{padding:4px 8px;border:1px solid #555;border-radius:4px;} QCheckBox::indicator{width:0;height:0;} QCheckBox:checked{background:#555;} QCheckBox:hover{background:#444;}");
    connect(typeFilter,&QComboBox::currentTextChanged,[this]{ applyFiltersAndSorting(); });
    connect(availableOnlyCheck,&QCheckBox::toggled,[this]{ applyFiltersAndSorting(); });
    connect(sortCombo,&QComboBox::currentTextChanged,[this]{ applyFiltersAndSorting(); });
}

void MainWindow::setupCentralWidgets() {
    QSplitter* splitter = new QSplitter(Qt::Horizontal, this);
    setCentralWidget(splitter);

    listWidget = new ItemListWidget(this);
    detailWidget = new ItemDetailWidget(this);
    splitter->addWidget(listWidget);
    splitter->addWidget(detailWidget);
    splitter->setSizes({1400, 1600});

    QObject::connect(listWidget, &ItemListWidget::mediaSelected, this, &MainWindow::showMediaDetails);
    QObject::connect(this, &MainWindow::deleteMediaCard, listWidget, &ItemListWidget::deleteCard);
    QObject::connect(this, &MainWindow::clearMediaList, listWidget, &ItemListWidget::clearAll);
    QObject::connect(detailWidget, &ItemDetailWidget::editRequested, this, &MainWindow::editExistingMedia);
    QObject::connect(detailWidget, &ItemDetailWidget::deleteRequested, this, &MainWindow::deleteMedia);
}

void MainWindow::createNewMedia() {
    ItemEditDialog dlg(library.get(), ItemEditDialog::Create, nullptr, this);
    if(dlg.exec()==QDialog::Accepted){
        auto media = dlg.takeResult();
        if(media){
            unsigned int id = media->getID();
            library->addMedia(std::move(media));
            if(auto m = library->findMediaById(id)){
                listWidget->addMediaCard(*m);
                unsavedChanges = true;
            }
        }
    }
}

void MainWindow::editExistingMedia(unsigned int id) {
    if(auto existing = library->findMediaById(static_cast<int>(id))){
        ItemEditDialog dlg(library.get(), ItemEditDialog::Edit, existing, this);
        if(dlg.exec()==QDialog::Accepted){
            auto updated = dlg.takeResult();
            if(updated){
                // Remove old then insert new (keep id)
                library->removeMedia(id);
                updated->setID(id);
                library->addMedia(std::move(updated));
                // Refresh card (simplest: delete + re-add)
                emit deleteMediaCard(id);
                if(auto m2 = library->findMediaById(id)){
                    listWidget->addMediaCard(*m2);
                    showMediaDetails(id);
                }
                unsavedChanges = true;
            }
        }
    }
}

void MainWindow::createNewFile() {
    QString path = QFileDialog::getSaveFileName(this, "Create new JSON or XML file", "./", "Data files (*.json *.xml)");
    if (path.isEmpty()) return;
    if (!path.endsWith(".json") && !path.endsWith(".xml")) path += ".json";
    QFile f(path);
    if (!f.exists()) { if (f.open(QIODevice::WriteOnly)) { f.write(path.endsWith(".json")?"{}":"<library/>" ); f.close(); } }
    currentPath = path;
    clearState();
    if(library) library->clear();
    unsavedChanges = false;
}

void MainWindow::openExistingFile() {
    QString path = QFileDialog::getOpenFileName(this, "Open Library", "./", "Data files (*.json *.xml)");
    if (path.isEmpty()) return;
    clearState();
    bool ok = false;
    if (path.endsWith(".json", Qt::CaseInsensitive)) ok = library->loadJson(path.toStdString());
    else if (path.endsWith(".xml", Qt::CaseInsensitive)) ok = library->loadXml(path.toStdString());
    if (!ok) QMessageBox::critical(this, "Error", "Failed to load file");
    else {
        currentPath = path; unsavedChanges = false;
        // populate list
        for(auto m : library->getAllMediaConst()) {
            listWidget->addMediaCard(*m);
        }
    applyFiltersAndSorting();
    }
}

void MainWindow::saveAll() {
    if (currentPath.isEmpty()) { createNewFile(); return; }
    bool ok = false;
    if (currentPath.endsWith(".json", Qt::CaseInsensitive)) ok = library->saveJson(currentPath.toStdString());
    else if (currentPath.endsWith(".xml", Qt::CaseInsensitive)) ok = library->saveXml(currentPath.toStdString());
    if (!ok) QMessageBox::critical(this, "Error", "Save failed");
    else unsavedChanges = false;
}

void MainWindow::showInfo() {
    QMessageBox::information(this, "Info", "Davide Colabove\nOussama Mahdi");
}

void MainWindow::closeEditor() {
    // placeholder for when edit widget integrated
}

void MainWindow::addMediaCardSlot(const Media&) { unsavedChanges = true; }

void MainWindow::showMediaDetails(unsigned int id) {
    if (auto m = library->findMediaById(static_cast<int>(id))) {
    currentSelectedId = id;
        detailWidget->displayMedia(*m);
    }
}

void MainWindow::deleteMedia(unsigned int id) {
    if (QMessageBox::question(this, "Delete", "Delete this media?") == QMessageBox::Yes){
        library->removeMedia(id);
        emit deleteMediaCard(id);
        unsavedChanges = true;
    }
}

void MainWindow::clearState() {
    emit clearMediaList();
    // Backend not automatically cleared here to allow caller control (e.g., open vs new file)
}

void MainWindow::closeEvent(QCloseEvent* event) {
    if (unsavedChanges) {
        auto reply = QMessageBox::question(this, "Unsaved changes", "You have unsaved changes. Exit?", QMessageBox::Yes|QMessageBox::No);
        if (reply == QMessageBox::No) { event->ignore(); return; }
    }
    event->accept();
}

void MainWindow::setupShortcuts() {
    // New media Ctrl+N
    newMediaAct->setShortcut(QKeySequence::New);
    // Open Ctrl+O
    openFileAct->setShortcut(QKeySequence::Open);
    // Save Ctrl+S
    saveAct->setShortcut(QKeySequence::Save);
    // Quit Ctrl+Q
    auto quitAct = new QAction(this);
    quitAct->setShortcut(QKeySequence::Quit);
    addAction(quitAct);
    connect(quitAct,&QAction::triggered,this,&QWidget::close);

    // Edit selected (Ctrl+E)
    editAct = new QAction(this);
    editAct->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_E));
    addAction(editAct);
    connect(editAct,&QAction::triggered,[this]{ if(currentSelectedId) editExistingMedia(currentSelectedId); });

    // Delete selected (Del key)
    deleteAct = new QAction(this);
    deleteAct->setShortcut(QKeySequence(Qt::Key_Delete));
    addAction(deleteAct);
    connect(deleteAct,&QAction::triggered,[this]{ if(currentSelectedId) deleteMedia(currentSelectedId); });

    // Focus search (Ctrl+F)
    focusSearchAct = new QAction(this);
    focusSearchAct->setShortcut(QKeySequence::Find);
    addAction(focusSearchAct);
    connect(focusSearchAct,&QAction::triggered,[this]{ if(listWidget) listWidget->setFocus(); });

    // Cycle sort mode (Ctrl+T)
    auto sortCycleAct = new QAction(this);
    sortCycleAct->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_T));
    addAction(sortCycleAct);
    connect(sortCycleAct,&QAction::triggered,[this]{ if(sortCombo){ int n = (sortCombo->currentIndex()+1)%sortCombo->count(); sortCombo->setCurrentIndex(n);} });

    // Toggle availability filter (Ctrl+A)
    auto toggleAvailAct = new QAction(this);
    toggleAvailAct->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_A));
    addAction(toggleAvailAct);
    connect(toggleAvailAct,&QAction::triggered,[this]{ if(availableOnlyCheck){ availableOnlyCheck->setChecked(!availableOnlyCheck->isChecked()); }});
}

void MainWindow::applyFiltersAndSorting() {
    if(!library) return;
    std::vector<const Media*> items = library->getAllMediaConst();
    // Type filter
    if(typeFilter && typeFilter->currentText()!="All") {
        QString wanted = typeFilter->currentText();
        std::vector<const Media*> filtered; filtered.reserve(items.size());
        for(const Media* m: items) if(m && QString::fromStdString(library->getMediaType(m))==wanted) filtered.push_back(m);
        items.swap(filtered);
    }
    // Availability
    if(availableOnlyCheck && availableOnlyCheck->isChecked()) {
        std::vector<const Media*> filtered; filtered.reserve(items.size());
        for(const Media* m: items) if(m && m->getIsAvailable()) filtered.push_back(m);
        items.swap(filtered);
    }
    // Sorting
    if(sortCombo){
        QString mode = sortCombo->currentText();
        std::sort(items.begin(), items.end(), [mode](const Media* a, const Media* b){
            if(!a||!b) return a<b;
            if(mode=="Title A-Z") return a->getTitle()<b->getTitle();
            if(mode=="Title Z-A") return a->getTitle()>b->getTitle();
            if(mode=="Author A-Z") return a->getAuthor()<b->getAuthor();
            if(mode=="Author Z-A") return a->getAuthor()>b->getAuthor();
            if(mode=="Date Newest") return a->getReleaseDate()>b->getReleaseDate();
            if(mode=="Date Oldest") return a->getReleaseDate()<b->getReleaseDate();
            return a->getTitle()<b->getTitle();
        });
    }
    QString searchText = listWidget->currentSearchText();
    listWidget->rebuild(items);
    if(!searchText.isEmpty()) listWidget->applySearchText(searchText);
}
