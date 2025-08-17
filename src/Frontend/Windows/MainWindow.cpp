#include "MainWindow.h"
#include <QApplication>
#include <QGuiApplication>
#include <QIcon>
#include <QStyle>
#include <QSvgRenderer>
#include <QMouseEvent>
#include <QPainter>
#include <QPainterPath>
#include <QScrollArea>
#include <QFrame>
#include <QStackedWidget>
#include <QComboBox>
#include <QCheckBox>
#include <QGroupBox>
#include <QSpacerItem>
#include <QShortcut>
#include <QFile>
#include <QIcon>
#include <QScrollBar>
#include <QTimer>
#include <QCollator>
namespace {
static QIcon loadIconByName(const QString& baseName) {
    // Try resource first
    const QString resPath = QString(":/icons/%1.svg").arg(baseName);
    if (QFile::exists(resPath)) return QIcon(resPath);
    // Try common relative paths when running from build directories
    const QStringList tryPaths = {
        QString("icons/%1.svg").arg(baseName),
        QString("../icons/%1.svg").arg(baseName),
        QString("../../icons/%1.svg").arg(baseName),
        QString("../../../icons/%1.svg").arg(baseName)
    };
    for (const QString& p : tryPaths) {
        if (QFile::exists(p)) return QIcon(p);
    }
    return QIcon();
}
}
#include <QResizeEvent>
#include <QStandardPaths>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
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
#include <QSpacerItem>
#include <QTimer>

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
    applyDarkTheme();
    
    // Set window properties
    setWindowTitle("Multimedia Library");
    setMinimumSize(1200, 800);
    resize(1400, 900);
    
    // Ensure window is visible
    setVisible(true);
    raise();
    activateWindow();
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
    leftSidebar = new QWidget(this);
    leftSidebar->setFixedWidth(200);
    leftSidebar->setObjectName("leftSidebar");
    
    sidebarLayout = new QVBoxLayout(leftSidebar);
    sidebarLayout->setSpacing(10);
    sidebarLayout->setContentsMargins(20, 20, 20, 20);
    
    // Title
    sidebarTitle = new QLabel("Media", leftSidebar);
    sidebarTitle->setObjectName("sidebarTitle");
    sidebarTitle->setAlignment(Qt::AlignCenter);
    sidebarLayout->addWidget(sidebarTitle);
    
    // Category list
    categoryList = new QListWidget(leftSidebar);
    categoryList->setObjectName("categoryList");
    categoryList->addItem("All");
    categoryList->addItem("Books");
    categoryList->addItem("Movies");
    categoryList->addItem("Songs");
    categoryList->addItem("Magazines");
    categoryList->addItem("Podcasts");

    const struct { int row; const char* iconBase; const char* tip; } catIcons[] = {
        {0, "all",       "All media"},
        {1, "book",      "Books"},
        {2, "movie",     "Movies"},
        {3, "music",     "Songs"},
        {4, "magazine",  "Magazines"},
        {5, "podcast",   "Podcasts"},
    };
    for (const auto& ci : catIcons) {
        if (QListWidgetItem* it = categoryList->item(ci.row)) {
            it->setIcon(loadIconByName(QString::fromUtf8(ci.iconBase)));
            it->setToolTip(QString::fromUtf8(ci.tip));
        }
    }
    categoryList->setCurrentRow(0);
    sidebarLayout->addWidget(categoryList);
    
    mainLayout->addWidget(leftSidebar);
}

void MainWindow::setupCentralArea()
{
    centralArea = new QWidget(this);
    centralArea->setObjectName("centralArea");
    
    centralLayout = new QVBoxLayout(centralArea);
    centralLayout->setSpacing(0);
    centralLayout->setContentsMargins(0, 0, 0, 0);
    
    // Search bar
    searchBar = new QWidget(centralArea);
    searchBar->setObjectName("searchBar");
    searchBar->setFixedHeight(60);
    
    searchLayout = new QHBoxLayout(searchBar);
    searchLayout->setContentsMargins(20, 10, 20, 10);
    
    // Search input
    searchInput = new QLineEdit(searchBar);
    searchInput->setObjectName("searchInput");
    searchInput->setPlaceholderText("Search...");
    searchInput->setMinimumHeight(35);
    searchLayout->addWidget(searchInput);
    
    // Advanced search button (icon-only)
    advancedSearchBtn = new QPushButton("", searchBar);
    advancedSearchBtn->setToolTip("Advanced");
    advancedSearchBtn->setObjectName("advancedSearchBtn");
    advancedSearchBtn->setFixedSize(80, 35);
    searchLayout->addWidget(advancedSearchBtn);

    // Clear filters button (icon-only)
    clearFiltersBtn = new QPushButton("", searchBar);
    clearFiltersBtn->setToolTip("Clear");
    clearFiltersBtn->setObjectName("clearFiltersBtn");
    clearFiltersBtn->setFixedSize(70, 35);
    searchLayout->addWidget(clearFiltersBtn);

    // Sort combo
    sortCombo = new QComboBox(searchBar);
    sortCombo->addItem("Title ▲");
    sortCombo->addItem("Title ▼");
    sortCombo->addItem("Date ▲");
    sortCombo->addItem("Date ▼");
    sortCombo->setFixedSize(100, 35);
    // Make it visually consistent with the rest of the top bar controls
    sortCombo->setStyleSheet(
        "QComboBox { background-color: #555; border: 1px solid #777; border-radius: 5px; color: #ffffff; padding: 5px 10px; }"
        "QComboBox::drop-down { border: 0px; }"
        "QComboBox QAbstractItemView { background-color: #3c3c3c; color: #ffffff; border: 1px solid #777; }"
    );
    searchLayout->addWidget(sortCombo);
    // Move sorting combo to the far left of the search bar
    searchLayout->removeWidget(sortCombo);
    searchLayout->insertWidget(0, sortCombo);
    
    // Action buttons: Add / Import / Export / Save (icon-only)
    addTopBtn = new QPushButton("", searchBar);
    addTopBtn->setToolTip("Add");
    addTopBtn->setFixedSize(36, 36);
    searchLayout->addWidget(addTopBtn);

    importTopBtn = new QPushButton("", searchBar);
    importTopBtn->setToolTip("Import");
    importTopBtn->setFixedSize(36, 36);
    searchLayout->addWidget(importTopBtn);

    exportTopBtn = new QPushButton("", searchBar);
    exportTopBtn->setToolTip("Export");
    exportTopBtn->setFixedSize(36, 36);
    searchLayout->addWidget(exportTopBtn);

    saveTopBtn = new QPushButton("", searchBar);
    saveTopBtn->setToolTip("Save");
    saveTopBtn->setFixedSize(36, 36);
    searchLayout->addWidget(saveTopBtn);
    
    centralLayout->addWidget(searchBar);
    
    // Stacked widget for grid (details page removed; grid stays visible)
    stackedWidget = new QStackedWidget(centralArea);
    
    // Grid page
    gridPage = new QWidget();
    QVBoxLayout* gridPageLayout = new QVBoxLayout(gridPage);
    gridPageLayout->setContentsMargins(20, 20, 20, 20);
    
    mediaGridArea = new QScrollArea(gridPage);
    mediaGridArea->setWidgetResizable(true);
    mediaGridArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    mediaGridArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    
    mediaGridWidget = new QWidget(mediaGridArea);
    mediaGridLayout = new QGridLayout(mediaGridWidget);
    mediaGridLayout->setSpacing(24);
    mediaGridLayout->setAlignment(Qt::AlignTop);
    
    mediaGridArea->setWidget(mediaGridWidget);
    gridPageLayout->addWidget(mediaGridArea);
    
    stackedWidget->addWidget(gridPage);
    stackedWidget->setCurrentWidget(gridPage);
    
    centralLayout->addWidget(stackedWidget);
    
    mainLayout->addWidget(centralArea, 1);
    
    // Connect resize events for better grid management
    connect(mediaGridArea->horizontalScrollBar(), &QScrollBar::rangeChanged, 
            this, &MainWindow::onScrollBarRangeChanged);
}

void MainWindow::setupRightPanel()
{
    rightPanel = new QWidget(this);
    rightPanel->setObjectName("rightPanel");
    rightPanel->setFixedWidth(420);
    
    rightLayout = new QVBoxLayout(rightPanel);
    rightLayout->setSpacing(20);
    rightLayout->setContentsMargins(20, 20, 20, 20);
    
    // Details widget with inline Back button
    detailsWidget = new QWidget(rightPanel);
    detailsWidget->setObjectName("detailsWidget");
    
    detailsLayout = new QVBoxLayout(detailsWidget);
    detailsLayout->setSpacing(15);
    
    // Back to grid button at top of details panel (icon + text, no duplicate arrow)
    backBtn = new QPushButton("Back to Grid", detailsWidget);
    backBtn->setObjectName("backBtn");
    backBtn->setMinimumHeight(36);
    detailsLayout->addWidget(backBtn);
    
    // Header card: cover + title grouped consistently like MediaCard
    QFrame* headerCard = new QFrame(detailsWidget);
    headerCard->setObjectName("detailsHeaderCard");
    headerCard->setStyleSheet("#detailsHeaderCard { background-color: #3c3c3c; border: 1px solid #555; border-radius: 8px; } ");
    QVBoxLayout* headerLay = new QVBoxLayout(headerCard);
    headerLay->setContentsMargins(12, 12, 12, 12);
    headerLay->setSpacing(10);

    // Cover image inside header card
    coverImage = new QLabel(headerCard);
    coverImage->setObjectName("coverImage");
    coverImage->setFixedSize(260, 300);
    coverImage->setAlignment(Qt::AlignCenter);
    coverImage->setStyleSheet("border: none; background: transparent;");
    headerLay->addWidget(coverImage, 0, Qt::AlignHCenter);

    // Title inside header card
    titleLabel = new QLabel(headerCard);
    titleLabel->setObjectName("titleLabel");
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setWordWrap(true);
    titleLabel->setStyleSheet("color: #ffffff; font-size: 16px; font-weight: bold;");
    headerLay->addWidget(titleLabel);

    detailsLayout->addWidget(headerCard, 0, Qt::AlignCenter);
    
    // Author
    authorLabel = new QLabel(detailsWidget);
    authorLabel->setObjectName("authorLabel");
    detailsLayout->addWidget(authorLabel);
    
    // Year
    yearLabel = new QLabel(detailsWidget);
    yearLabel->setObjectName("yearLabel");
    detailsLayout->addWidget(yearLabel);
    
    // Duration
    durationLabel = new QLabel(detailsWidget);
    durationLabel->setObjectName("durationLabel");
    detailsLayout->addWidget(durationLabel);
    
    // Summary
    summaryLabel = new QLabel(detailsWidget);
    summaryLabel->setObjectName("summaryLabel");
    summaryLabel->setWordWrap(true);
    detailsLayout->addWidget(summaryLabel);
    
    // Cover path
    coverPathLabel = new QLabel(detailsWidget);
    coverPathLabel->setObjectName("coverPathLabel");
    detailsLayout->addWidget(coverPathLabel);

    // Attributes group (type-specific)
    attributesGroup = new QGroupBox("Attributes", detailsWidget);
    attributesWidget = new QWidget(attributesGroup);
    attributesForm = new QFormLayout(attributesWidget);
    QVBoxLayout* attrGroupLay = new QVBoxLayout(attributesGroup);
    attrGroupLay->addWidget(attributesWidget);
    detailsLayout->addWidget(attributesGroup);
    
    detailsLayout->addStretch();
    
    // Buttons
    QHBoxLayout* buttonLayout = new QHBoxLayout();
    buttonLayout->setSpacing(12);
    buttonLayout->setAlignment(Qt::AlignHCenter);
    editBtn = new QPushButton("Edit", detailsWidget);
    editBtn->setObjectName("editBtn");
    editBtn->setMinimumSize(110, 36);
    editBtn->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    buttonLayout->addWidget(editBtn);
    
    deleteBtn = new QPushButton("Delete", detailsWidget);
    deleteBtn->setObjectName("deleteBtn");
    deleteBtn->setMinimumSize(120, 36);
    deleteBtn->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    buttonLayout->addWidget(deleteBtn);
    
    detailsLayout->addLayout(buttonLayout);
    
    rightLayout->addWidget(detailsWidget);
    
    mainLayout->addWidget(rightPanel);
}

void MainWindow::setupMenuBar()
{
    QMenuBar *menuBar = this->menuBar();
    
    // File menu
    QMenu *fileMenu = menuBar->addMenu("&File");
    importAction = fileMenu->addAction("&Import...");
    exportAction = fileMenu->addAction("&Export...");
    saveAction = fileMenu->addAction("&Save");
    fileMenu->addSeparator();
    fileMenu->addAction("E&xit", this, &QWidget::close);
    
    // Edit menu
    QMenu *editMenu = menuBar->addMenu("&Edit");
    addAction = editMenu->addAction("&Add Media...");
    editAction = editMenu->addAction("&Edit Media...");
    deleteAction = editMenu->addAction("&Delete Media");
    // Shortcuts
    addAction->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_N));
    editAction->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_E));
    deleteAction->setShortcut(QKeySequence(Qt::Key_Delete));
    importAction->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_I));
    exportAction->setShortcut(QKeySequence(Qt::CTRL | Qt::SHIFT | Qt::Key_E));
    saveAction->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_S));
    
    // Help menu
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
    // Connect menu actions
    connect(addAction, &QAction::triggered, this, &MainWindow::addMedia);
    connect(editAction, &QAction::triggered, this, &MainWindow::editMedia);
    connect(deleteAction, &QAction::triggered, this, &MainWindow::deleteMedia);
    connect(exportAction, &QAction::triggered, this, &MainWindow::exportData);
    connect(importAction, &QAction::triggered, this, &MainWindow::importData);
    connect(saveAction, &QAction::triggered, this, &MainWindow::saveTriggered);
    connect(aboutAction, &QAction::triggered, this, &MainWindow::about);
    connect(shortcutsAction, &QAction::triggered, this, &MainWindow::showShortcuts);
    
    // Connect new UI elements
    connect(categoryList, &QListWidget::currentRowChanged, this, &MainWindow::onCategoryChanged);
    connect(searchInput, &QLineEdit::textChanged, this, &MainWindow::onSearchTextChanged);
    connect(advancedSearchBtn, &QPushButton::clicked, this, &MainWindow::onAdvancedSearchClicked);
    connect(clearFiltersBtn, &QPushButton::clicked, this, &MainWindow::clearAdvancedFilters);
    connect(sortCombo, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &MainWindow::onSortChanged);
    connect(addTopBtn, &QPushButton::clicked, this, &MainWindow::addMedia);
    connect(importTopBtn, &QPushButton::clicked, this, &MainWindow::importData);
    connect(exportTopBtn, &QPushButton::clicked, this, &MainWindow::exportData);
    addTopBtn->setIcon(loadIconByName("add"));
    importTopBtn->setIcon(loadIconByName("import"));
    exportTopBtn->setIcon(loadIconByName("export"));
    saveTopBtn->setIcon(loadIconByName("save"));
    if (advancedSearchBtn) advancedSearchBtn->setIcon(loadIconByName("filter-advanced"));
    if (clearFiltersBtn) clearFiltersBtn->setIcon(loadIconByName("filter-clear"));
    // Icon-only buttons
    const QSize topIconSize(20,20);
    addTopBtn->setIconSize(topIconSize);
    importTopBtn->setIconSize(topIconSize);
    exportTopBtn->setIconSize(topIconSize);
    saveTopBtn->setIconSize(topIconSize);
    if (advancedSearchBtn) advancedSearchBtn->setIconSize(topIconSize);
    if (clearFiltersBtn) clearFiltersBtn->setIconSize(topIconSize);

    auto styleIconButton = [](QPushButton* b){
        if (!b) return;
        b->setFlat(true);
        b->setCursor(Qt::PointingHandCursor);
        b->setStyleSheet("QPushButton { background-color: transparent; border: none; padding: 6px; } QPushButton:hover { background-color: rgba(255,255,255,0.08); border-radius: 6px; }");
        b->setMinimumSize(36,36);
        b->setMaximumSize(36,36);
    };
    styleIconButton(addTopBtn);
    styleIconButton(importTopBtn);
    styleIconButton(exportTopBtn);
    styleIconButton(saveTopBtn);
    styleIconButton(advancedSearchBtn);
    styleIconButton(clearFiltersBtn);

    backBtn->setIcon(loadIconByName("back"));
    editBtn->setIcon(loadIconByName("edit"));
    deleteBtn->setIcon(loadIconByName("delete"));
    backBtn->setIconSize(QSize(20,20));
    editBtn->setIconSize(QSize(20,20));
    deleteBtn->setIconSize(QSize(20,20));

    connect(saveTopBtn, &QPushButton::clicked, this, &MainWindow::saveTriggered);
    connect(backBtn, &QPushButton::clicked, this, &MainWindow::onBackToGridClicked);
    connect(editBtn, &QPushButton::clicked, this, &MainWindow::editMedia);
    connect(deleteBtn, &QPushButton::clicked, this, &MainWindow::deleteMedia);

    // Keyboard shortcut: Ctrl+F focuses the search field
    QShortcut* focusSearch = new QShortcut(QKeySequence(Qt::CTRL | Qt::Key_F), this);
    connect(focusSearch, &QShortcut::activated, [this]() { searchInput->setFocus(); searchInput->selectAll(); });
}

// Update grid with current sorting and filters, recalculate layout
void MainWindow::refreshMediaGrid()
{
    clearMediaGrid();
    
    auto allMedia = library->getAllMedia();
    // Sort according to currentSortMode (locale-aware, case-insensitive, numeric-aware). Keep leading articles.
    QCollator coll; coll.setCaseSensitivity(Qt::CaseInsensitive); coll.setNumericMode(true);
    std::sort(allMedia.begin(), allMedia.end(), [&](Media* a, Media* b){
        if (currentSortMode == SortMode::TitleAsc)
            return coll.compare(QString::fromStdString(a->getTitle()), QString::fromStdString(b->getTitle())) < 0;
        if (currentSortMode == SortMode::TitleDesc)
            return coll.compare(QString::fromStdString(a->getTitle()), QString::fromStdString(b->getTitle())) > 0;
        const Date& da = a->getReleaseDate(); const Date& db = b->getReleaseDate();
        if (currentSortMode == SortMode::DateAsc) return da < db;
        return da > db; // DateDesc
    });
    
    // Calculate available width more accurately
    int availableWidth = mediaGridArea->viewport()->width();
    int margins = 40; // Left and right margins
    int colsPerRow = computeColumnsForWidth(availableWidth - margins);
    
    int row = 0, col = 0;
    for (auto media : allMedia) {
        if (!mediaMatchesFilters(media)) continue;
        addMediaCard(media, row, col);
        col++;
        if (col >= colsPerRow) { 
            col = 0; 
            row++; 
        }
    }
    
    // Force layout update
    mediaGridWidget->updateGeometry();
    mediaGridArea->viewport()->update();
    
    // Update status bar with count
    QString statusMessage = QString("Total media: %1").arg(allMedia.size());
    statusBar()->showMessage(statusMessage);
}

int MainWindow::computeColumnsForWidth(int availableWidth) const
{
    const int itemWidth = 240;
    const int spacing = 24; // Same as mediaGridLayout->setSpacing(24)
    
    // Calculate how many items can fit with proper spacing
    int cols = std::max(1, (availableWidth + spacing) / (itemWidth + spacing));
    return cols;
}

void MainWindow::applyDarkTheme()
{
    setStyleSheet(R"(
        QMainWindow {
            background-color: #2b2b2b;
            color: #ffffff;
            font-family: 'Segoe UI', 'Inter', 'Roboto', sans-serif;
            font-size: 12px;
        }
        
        #leftSidebar {
            background-color: #3c3c3c;
            border-right: 1px solid #555;
        }
        
        #sidebarTitle {
            color: #ffffff;
            font-size: 18px;
            font-weight: bold;
            padding: 10px;
        }
        
        #categoryList {
            background-color: #3c3c3c;
            border: none;
            color: #f0f0f0;
            font-size: 14px;
        }
        
        #categoryList::item {
            padding: 10px;
            border-radius: 5px;
            margin: 2px;
        }
        
        #categoryList::item:selected {
            background-color: #0078d4;
            color: #ffffff;
        }
        
        #categoryList::item:hover {
            background-color: #555;
        }
        
        #centralArea {
            background-color: #2b2b2b;
        }
        
        #searchBar {
            background-color: #3c3c3c;
            border-bottom: 1px solid #555;
        }
        
        #searchInput {
            background-color: #555;
            border: 1px solid #777;
            border-radius: 5px;
            color: #ffffff;
            padding: 5px 10px;
            font-size: 14px;
        }
        
        #searchInput:focus {
            border: 1px solid #0078d4;
        }
        
        #advancedSearchBtn, QPushButton {
            background-color: #555;
            border: 1px solid #777;
            border-radius: 5px;
            color: #ffffff;
            padding: 5px 10px;
        }
        
        #advancedSearchBtn:hover, QPushButton:hover {
            background-color: #666;
        }
        
        #rightPanel {
            background-color: #3c3c3c;
            border-left: 1px solid #555;
        }
        
        #detailsWidget {
            background-color: #3c3c3c;
        }
        
        #titleLabel {
            color: #ffffff;
            font-size: 18px;
            font-weight: bold;
        }
        
        #authorLabel, #yearLabel, #durationLabel, #summaryLabel, #coverPathLabel {
            color: #e0e0e0;
            font-size: 14px;
        }
        
        #editBtn, #deleteBtn, #backBtn {
            background-color: #0078d4;
            border: none;
            border-radius: 5px;
            color: #ffffff;
            padding: 10px 18px;
            font-size: 15px;
        }
        
        #editBtn:hover, #backBtn:hover {
            background-color: #106ebe;
        }
        
        #deleteBtn {
            background-color: #d13438;
        }
        
        #deleteBtn:hover {
            background-color: #b02a2e;
        }
        
        QScrollArea {
            background-color: #2b2b2b;
            border: none;
        }
        
        QScrollBar:vertical {
            background-color: #555;
            width: 12px;
            border-radius: 6px;
        }
        
        QScrollBar::handle:vertical {
            background-color: #777;
            border-radius: 6px;
            min-height: 20px;
        }
        
        QScrollBar::handle:vertical:hover {
            background-color: #888;
        }
    )");
}

void MainWindow::onCategoryChanged(int index)
{
    QString category = categoryList->item(index)->text();
    currentCategoryFilter = category;
    refreshMediaGrid();
}

void MainWindow::onMediaCardClicked(Media* media)
{
    selectedMedia = media;
    showMediaDetails(media);
}

void MainWindow::onBackToGridClicked()
{
    hideMediaDetails();
    
    // Ensure the grid adapts to the new layout
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
    advFilters = AdvancedFilters{}; // reset
    currentSearchFilter.clear();
    refreshMediaGrid();
    statusBar()->showMessage("Filtri avanzati rimossi", 2500);
}

void MainWindow::onScrollBarRangeChanged()
{
    // Update grid when scrollbar range changes (indicates content size change)
    QTimer::singleShot(100, this, &MainWindow::refreshMediaGrid);
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
    
    // Delay the grid refresh to ensure the resize is complete
    QTimer::singleShot(100, this, &MainWindow::refreshMediaGrid);
}

void MainWindow::clearMediaGrid()
{
    // Clear existing cards
    QLayoutItem* item;
    while ((item = mediaGridLayout->takeAt(0)) != nullptr) {
        delete item->widget();
        delete item;
    }
}

void MainWindow::addMediaCard(Media* media, int row, int col)
{
    MediaCard* card = new MediaCard(media, mediaGridWidget);
    connect(card, &MediaCard::clicked, this, &MainWindow::onMediaCardClicked);
    mediaGridLayout->addWidget(card, row, col);
}

void MainWindow::showMediaDetails(Media* media)
{
    if (!media) return;
    
    // Update details
    titleLabel->setText(QString::fromStdString(media->getTitle()));
    authorLabel->setText("Author: " + QString::fromStdString(media->getAuthor()));
    yearLabel->setText("Year: " + QString::fromStdString(media->getReleaseDate().toString()));
    
    // Set cover image from path with fallback, scaled to fit nicely without borders
    QPixmap pix(QString::fromStdString(media->getImagePath()));
    if (!pix.isNull()) {
        coverImage->setPixmap(pix.scaled(coverImage->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
        coverImage->setText("");
    } else {
        // Fallback: show type icon placeholder, consistent with MediaCard
        QString iconName;
        if (dynamic_cast<Book*>(media)) iconName = "book";
        else if (dynamic_cast<Movie*>(media)) iconName = "movie";
        else if (dynamic_cast<Song*>(media)) iconName = "music";
        else if (dynamic_cast<Magazine*>(media)) iconName = "magazine";
        else if (dynamic_cast<Podcast*>(media)) iconName = "podcast";

        auto findIconPath = [&](const QString& base)->QString{
            const QString res = QString(":/icons/%1.svg").arg(base);
            if (QFile::exists(res)) return res;
            const QStringList tries = {
                QString("src/Frontend/Resources/icons/%1.svg").arg(base),
                QString("icons/%1.svg").arg(base),
                QString("../icons/%1.svg").arg(base),
            };
            for (const QString& p : tries) if (QFile::exists(p)) return p;
            return QString();
        };

        const QString iconPath = findIconPath(iconName);
        if (!iconPath.isEmpty()) {
            const QSize target = coverImage->size();
            const qreal ratio = 0.6;
            const qreal dpr = QGuiApplication::primaryScreen() ? QGuiApplication::primaryScreen()->devicePixelRatio() : 1.0;

            // Render SVG crisply at target pixel size
            QPixmap iconPixmap;
            if (iconPath.endsWith(".svg", Qt::CaseInsensitive)) {
                const QSizeF logicalSize(target.width()*ratio, target.height()*ratio);
                const QSize pixelSize(qMax(1, int(logicalSize.width()*dpr)), qMax(1, int(logicalSize.height()*dpr)));
                QPixmap tmp(pixelSize);
                tmp.fill(Qt::transparent);
                QSvgRenderer renderer(iconPath);
                QPainter rp(&tmp);
                rp.setRenderHint(QPainter::Antialiasing, true);
                rp.setRenderHint(QPainter::SmoothPixmapTransform, true);
                renderer.render(&rp, QRectF(0, 0, pixelSize.width(), pixelSize.height()));
                rp.end();
                tmp.setDevicePixelRatio(dpr);
                iconPixmap = tmp;
            } else {
                // Fallback for raster icons
                QPixmap raw(iconPath);
                iconPixmap = raw.scaled(target.width()*ratio, target.height()*ratio, Qt::KeepAspectRatio, Qt::SmoothTransformation);
            }

            // Compose rounded canvas and center icon
            QPixmap canvas(QSize(target.width()*dpr, target.height()*dpr));
            canvas.fill(Qt::transparent);
            QPainter painter(&canvas);
            painter.setRenderHint(QPainter::Antialiasing, true);
            QPainterPath path;
            path.addRoundedRect(QRectF(0, 0, canvas.width(), canvas.height()), 8*dpr, 8*dpr);
            painter.setClipPath(path);
            painter.fillRect(QRectF(0,0,canvas.width(),canvas.height()), QColor(68,68,68));

            const int x = int((canvas.width()/dpr - iconPixmap.width()/iconPixmap.devicePixelRatio())/2 * dpr);
            const int y = int((canvas.height()/dpr - iconPixmap.height()/iconPixmap.devicePixelRatio())/2 * dpr);
            painter.drawPixmap(x, y, iconPixmap);
            painter.end();

            canvas.setDevicePixelRatio(dpr);
            coverImage->setPixmap(canvas);
            coverImage->setText("");
        } else {
            coverImage->setPixmap(QPixmap());
            coverImage->setText(" ");
        }
    }
    
    // Clear and populate attributes form
    clearAttributesForm();
    populateAttributesForm(media);
    
    // Show the right panel
    rightPanel->show();
    
    // Refresh the grid to ensure proper layout adaptation when showing details
    QTimer::singleShot(50, this, &MainWindow::refreshMediaGrid);
}

void MainWindow::hideMediaDetails()
{
    rightPanel->hide();
    selectedMedia = nullptr;
    
    // Refresh the grid to ensure proper layout adaptation
    QTimer::singleShot(50, this, &MainWindow::refreshMediaGrid);
}

void MainWindow::clearAttributesForm()
{
    if (!attributesForm) return;
    // Remove rows safely to avoid QFormLayout::takeAt warnings
    for (int row = attributesForm->rowCount() - 1; row >= 0; --row) {
        if (QLayoutItem* l = attributesForm->itemAt(row, QFormLayout::LabelRole)) {
            if (QWidget* lw = l->widget()) lw->deleteLater();
        }
        if (QLayoutItem* f = attributesForm->itemAt(row, QFormLayout::FieldRole)) {
            if (QWidget* fw = f->widget()) fw->deleteLater();
        }
        attributesForm->removeRow(row);
    }
}

void MainWindow::populateAttributesForm(Media* media)
{
    if (!media || !attributesForm) return;
    
    if (auto b = dynamic_cast<Book*>(media)) {
        attributesForm->addRow("Type:", new QLabel("Book", attributesWidget));
        attributesForm->addRow("Publisher:", new QLabel(QString::fromStdString(b->getPublisher()), attributesWidget));
        attributesForm->addRow("Pages:", new QLabel(QString::number(b->getPages()), attributesWidget));
        attributesForm->addRow("ISBN:", new QLabel(QString::fromStdString(b->getIsbn()), attributesWidget));
        attributesForm->addRow("Language:", new QLabel(QString::fromStdString(b->getLanguageString()), attributesWidget));
        attributesForm->addRow("Genre:", new QLabel(QString::fromStdString(b->getGenreString()), attributesWidget));
    } else if (auto m = dynamic_cast<Movie*>(media)) {
        attributesForm->addRow("Type:", new QLabel("Movie", attributesWidget));
        attributesForm->addRow("Director:", new QLabel(QString::fromStdString(m->getDirector()), attributesWidget));
        attributesForm->addRow("Duration:", new QLabel(QString::number(m->getDuration()) + " min", attributesWidget));
        attributesForm->addRow("Studio:", new QLabel(QString::fromStdString(m->getStudio()), attributesWidget));
        attributesForm->addRow("Rating:", new QLabel(QString::fromStdString(m->getRating()), attributesWidget));
        attributesForm->addRow("Language:", new QLabel(QString::fromStdString(m->getLanguageString()), attributesWidget));
        attributesForm->addRow("Country:", new QLabel(QString::fromStdString(m->getCountry()), attributesWidget));
        attributesForm->addRow("Genre:", new QLabel(QString::fromStdString(m->getGenreString()), attributesWidget));
    } else if (auto s = dynamic_cast<Song*>(media)) {
        attributesForm->addRow("Type:", new QLabel("Song", attributesWidget));
        attributesForm->addRow("Artist:", new QLabel(QString::fromStdString(s->getArtist()), attributesWidget));
        attributesForm->addRow("Album:", new QLabel(QString::fromStdString(s->getAlbum()), attributesWidget));
        attributesForm->addRow("Duration:", new QLabel(QString::number(s->getDuration()) + " s", attributesWidget));
        attributesForm->addRow("Format:", new QLabel(QString::fromStdString(s->getFormat()), attributesWidget));
        attributesForm->addRow("Label:", new QLabel(QString::fromStdString(s->getLabel()), attributesWidget));
        attributesForm->addRow("Track:", new QLabel(QString::number(s->getTrackNumber()), attributesWidget));
        attributesForm->addRow("Genre:", new QLabel(QString::fromStdString(s->getGenreString()), attributesWidget));
    } else if (auto mg = dynamic_cast<Magazine*>(media)) {
        attributesForm->addRow("Type:", new QLabel("Magazine", attributesWidget));
        attributesForm->addRow("Publisher:", new QLabel(QString::fromStdString(mg->getPublisher()), attributesWidget));
        attributesForm->addRow("Issue:", new QLabel(QString::number(mg->getIssueNumber()), attributesWidget));
        attributesForm->addRow("ISSN:", new QLabel(QString::fromStdString(mg->getIssn()), attributesWidget));
        attributesForm->addRow("Editor:", new QLabel(QString::fromStdString(mg->getEditor()), attributesWidget));
        attributesForm->addRow("Pages:", new QLabel(QString::number(mg->getPages()), attributesWidget));
        attributesForm->addRow("Frequency:", new QLabel(QString::fromStdString(mg->getFrequency()), attributesWidget));
        attributesForm->addRow("Genre:", new QLabel(QString::fromStdString(mg->getGenreString()), attributesWidget));
    } else if (auto p = dynamic_cast<Podcast*>(media)) {
        attributesForm->addRow("Type:", new QLabel("Podcast", attributesWidget));
        attributesForm->addRow("Host:", new QLabel(QString::fromStdString(p->getHost()), attributesWidget));
        attributesForm->addRow("Episodes:", new QLabel(QString::number(p->getEpisodeNumber()), attributesWidget));
        attributesForm->addRow("Platform:", new QLabel(QString::fromStdString(p->getPlatform()), attributesWidget));
        attributesForm->addRow("Duration:", new QLabel(QString::number(p->getDuration()) + " min", attributesWidget));
        attributesForm->addRow("Series:", new QLabel(QString::fromStdString(p->getSeries()), attributesWidget));
        attributesForm->addRow("Description:", new QLabel(QString::fromStdString(p->getDescription()), attributesWidget));
        attributesForm->addRow("Genre:", new QLabel(QString::fromStdString(p->getGenreString()), attributesWidget));
    }
}

void MainWindow::filterMediaByCategory(const QString& category)
{
    currentCategoryFilter = category;
    refreshMediaGrid();
}

void MainWindow::applySearchFilter(const QString& searchText)
{
    currentSearchFilter = searchText;
    refreshMediaGrid();
}

bool MainWindow::mediaMatchesFilters(Media* media) const
{
    if (!media) return false;
    // Category filter
    QString typeNeeded = categoryToType(currentCategoryFilter);
    if (!typeNeeded.isEmpty()) {
        std::string t = library->getMediaType(media);
        if (QString::fromStdString(t) != typeNeeded) return false;
    }
    // Advanced type filter override
    if (advFilters.enabled && !advFilters.type.isEmpty()) {
        std::string t = library->getMediaType(media);
        if (QString::fromStdString(t) != advFilters.type) return false;
    }
    // Text search (title or author, case-insensitive, contains)
    if (!currentSearchFilter.trimmed().isEmpty()) {
        const QString needle = currentSearchFilter.trimmed();
        QString title = QString::fromStdString(media->getTitle());
        QString author = QString::fromStdString(media->getAuthor());
        if (!title.contains(needle, Qt::CaseInsensitive) &&
            !author.contains(needle, Qt::CaseInsensitive)) {
            return false;
        }
    }
    // Advanced text filters
    if (advFilters.enabled) {
        if (!advFilters.titleContains.trimmed().isEmpty()) {
            if (!QString::fromStdString(media->getTitle()).contains(advFilters.titleContains, Qt::CaseInsensitive)) return false;
        }
        if (!advFilters.authorContains.trimmed().isEmpty()) {
            if (!QString::fromStdString(media->getAuthor()).contains(advFilters.authorContains, Qt::CaseInsensitive)) return false;
        }
        if (advFilters.onlyAvailable && !media->getIsAvailable()) return false;
        // Date range (assuming Date has getters)
        const Date& d = media->getReleaseDate();
        QDate qd(d.getYear(), d.getMonth(), d.getDay());
        if (advFilters.useDateFrom && qd < advFilters.dateFrom) return false;
        if (advFilters.useDateTo && qd > advFilters.dateTo) return false;
        // Type-specific genres via dynamic_cast
        if (auto b = dynamic_cast<Book*>(media); advFilters.bookGenre >= 0) {
            if (b && static_cast<int>(b->getGenre()) != advFilters.bookGenre) return false;
        }
        if (auto m = dynamic_cast<Movie*>(media); advFilters.movieGenre >= 0) {
            if (m && static_cast<int>(m->getGenre()) != advFilters.movieGenre) return false;
        }
        if (auto s = dynamic_cast<Song*>(media); advFilters.musicGenre >= 0) {
            if (s && static_cast<int>(s->getGenre()) != advFilters.musicGenre) return false;
        }
        if (auto mg = dynamic_cast<Magazine*>(media); advFilters.magazineGenre >= 0) {
            if (mg && static_cast<int>(mg->getGenre()) != advFilters.magazineGenre) return false;
        }
        if (auto p = dynamic_cast<Podcast*>(media); advFilters.podcastGenre >= 0) {
            if (p && static_cast<int>(p->getGenre()) != advFilters.podcastGenre) return false;
        }
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

// Existing methods (placeholders for now)
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
        // Media was edited in place, just refresh the grid
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
        
        // Refresh UI
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

    // Ensure extension matches chosen filter
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
    // Se non c'è ancora un percorso, apri Save As
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
        // Estensione inattesa: forza Save As di nuovo
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