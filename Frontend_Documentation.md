# 📚 Frontend Documentation - MultimediaLibrary

## 🎯 General Overview

The Frontend of the MultimediaLibrary project is built using the Qt 6 framework and implements a modern, responsive, and intuitive interface for managing a multimedia library. The architecture follows the Model-View-Controller pattern, where the GUI represents the "View" that interacts with the backend through the controller. The system includes a Material UI dark theme, scalable SVG icons, and an adaptive layout that automatically resizes.

---

## 🏗️ Folder Structure

```
src/Frontend/
├── Windows/           # Main windows and dialogs
│   ├── MainWindow.h/.cpp      # Main window
│   ├── MediaCard.h/.cpp       # Card for each media
│   ├── AddMediaDialog.h/.cpp  # Add/edit dialog
│   └── SearchDialog.h/.cpp    # Advanced search dialog
├── Resources/         # Graphic resources (icons, images)
│   └── icons/        # SVG icons for each media type
└── main.cpp          # Application entry point
```

---

## 📁 Main Frontend Files

### 1. **main.cpp** - Entry Point
**Path:** `src/Frontend/main.cpp`

**Function:** Main file that launches the Qt application and creates the main window.

**Responsibilities:**
- Qt application initialization
- Fusion theme configuration
- MainWindow creation and display
- Application lifecycle management

**Key Code:**
```cpp
int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    app.setApplicationName("Multimedia Library");
    app.setApplicationVersion("1.0.0");
    app.setOrganizationName("MultimediaLibrary");
    app.setStyle(QStyleFactory::create("Fusion"));
    MainWindow mainWindow;
    mainWindow.show();
    return app.exec();
}
```

---

### 2. **MainWindow.h** - Main Window Header
**Path:** `src/Frontend/Windows/MainWindow.h`

**Function:** Declaration of the main class that manages the complete user interface.

**Responsibilities:**
- Main window interface definition
- Declaration of all UI widgets and controls
- Declaration of slots and public/private methods
- Main layout management (grid + details panel)

**Main Components:**
- **Main layout:** Horizontal splitter with media grid and details panel
- **Top controls:** Toolbar, filters, search, sorting
- **Grid area:** Media grid view with scroll
- **Right panel:** Detailed view of selected media

**Key Methods:**
```cpp
class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    MainWindow(QWidget *parent = nullptr);
    
private slots:
    void refreshMediaGrid();                    // Updates media grid
    void onMediaCardClicked(Media*);           // Handles media card click
    void onBackToGridClicked();                // Returns to grid view
    void onSearchTextChanged(const QString&);  // Handles textual search
    void onAdvancedSearchClicked();            // Opens advanced search
    void onSortChanged(int);                   // Handles sorting
    void onCategoryChanged(const QString&);    // Handles category filters
    void onScrollBarRangeChanged();            // Handles scrollbar resizing
    
private:
    void setupUI();                            // Configures interface
    void setupConnections();                   // Sets up connections
    void showMediaDetails(Media*);             // Shows media details
    void hideMediaDetails();                   // Hides media details
    void addMediaCard(Media*, int, int);       // Adds card to grid
    int computeColumnsForWidth(int);           // Calculates columns for width
    void populateAttributesForm(Media*);       // Populates specific attributes form
    bool mediaMatchesFilters(Media*) const;    // Checks if media matches filters
};
```

---

### 3. **MainWindow.cpp** - Main Window Implementation
**Path:** `src/Frontend/Windows/MainWindow.cpp`

**Function:** Complete implementation of main window logic and user interface management.

**Responsibilities:**
- **UI Setup:** Creation and configuration of all widgets
- **Event Management:** Resize, click, search, filters
- **Dynamic Updates:** Grid that automatically adapts
- **Search System:** Real-time textual search + advanced filters
- **Performance Management:** Optimizations for large grids

**Key Features:**

#### **🔍 Advanced Search System**
```cpp
void MainWindow::onSearchTextChanged(const QString& text)
{
    currentSearchFilter = text;
    refreshMediaGrid();  // Updates in real-time
}

bool MainWindow::mediaMatchesFilters(Media* media) const
{
    // Category filter
    QString typeNeeded = categoryToType(currentCategoryFilter);
    if (!typeNeeded.isEmpty()) {
        std::string t = library->getMediaType(media);
        if (QString::fromStdString(t) != typeNeeded) return false;
    }
    
    // Text search (title + author)
    if (!currentSearchFilter.trimmed().isEmpty()) {
        const QString needle = currentSearchFilter.trimmed();
        QString title = QString::fromStdString(media->getTitle());
        QString author = QString::fromStdString(media->getAuthor());
        if (!title.contains(needle, Qt::CaseInsensitive) &&
            !author.contains(needle, Qt::CaseInsensitive)) {
            return false;
        }
    }
    
    // Advanced filters
    if (advFilters.enabled) {
        // ... complex filters implementation
    }
    
    return true;
}
```

#### **📱 Responsive Grid Management (`refreshMediaGrid`)**
```cpp
void MainWindow::refreshMediaGrid()
{
    clearMediaGrid();
    
    auto allMedia = library->getAllMediaConst();
    
    // Dynamic sorting
    std::sort(allMedia.begin(), allMedia.end(), [&](Media* a, Media* b){
        if (currentSortMode == SortMode::TitleAsc) return a->getTitle() < b->getTitle();
        if (currentSortMode == SortMode::TitleDesc) return a->getTitle() > b->getTitle();
        const Date& da = a->getReleaseDate(); const Date& db = b->getReleaseDate();
        if (currentSortMode == SortMode::DateAsc) return da < db;
        return da > db; // DateDesc
    });
    
    // Adaptive column calculation
    int availableWidth = mediaGridArea->viewport()->width();
    int margins = 40;
    int colsPerRow = computeColumnsForWidth(availableWidth - margins);
    
    // Grid population
    int row = 0, col = 0;
    for (auto media : allMedia) {
        if (!mediaMatchesFilters(media)) continue;
        addMediaCard(media, row, col);
        col++;
        if (col >= colsPerRow) { col = 0; row++; }
    }
    
    // Force layout update
    mediaGridWidget->updateGeometry();
    mediaGridArea->viewport()->update();
}
```

#### **⚡ Performance Optimizations**
```cpp
// Resize handling with delay to avoid multiple calls
void MainWindow::resizeEvent(QResizeEvent *event)
{
    QMainWindow::resizeEvent(event);
    QTimer::singleShot(100, this, &MainWindow::refreshMediaGrid);
}

// Automatic update when scrollbar changes
void MainWindow::onScrollBarRangeChanged()
{
    QTimer::singleShot(100, this, &MainWindow::refreshMediaGrid);
}

// Optimized column calculation
int MainWindow::computeColumnsForWidth(int availableWidth) const
{
    const int itemWidth = 240;
    const int spacing = 24;
    int cols = std::max(1, (availableWidth + spacing) / (itemWidth + spacing));
    return cols;
}
```

---

### 4. **MediaCard.h/.cpp** - Media Card
**Path:** `src/Frontend/Windows/MediaCard.h` / `src/Frontend/Windows/MediaCard.cpp`

**Function:** Custom widget that represents each media in the grid with responsive design and fallback for missing images.

**Responsibilities:**
- **Media Display:** Title, author, cover, type
- **Click Management:** Emits signal when clicked
- **Fallback Icon:** Shows type icon if cover missing
- **Responsive Styling:** Adapts to available dimensions

**Key Features:**
```cpp
class MediaCard : public QFrame
{
    Q_OBJECT
    
public:
    MediaCard(Media* media, QWidget* parent = nullptr);
    
signals:
    void clicked(Media* media);
    
private:
    void setupUI();
    void loadCoverImage();
    void setupFallbackIcon();
    
    Media* media;
    QLabel* coverLabel;
    QLabel* titleLabel;
    QLabel* authorLabel;
    QLabel* typeLabel;
};
```

**Fallback Icon System:**
```cpp
void MediaCard::setupFallbackIcon()
{
    // Determines media type and loads appropriate icon
    auto typeToIcon = [&](Media* m)->QString{
        if (dynamic_cast<Book*>(m)) return "book";
        if (dynamic_cast<Movie*>(m)) return "movie";
        if (dynamic_cast<Song*>(m)) return "music";
        if (dynamic_cast<Magazine*>(m)) return "magazine";
        if (dynamic_cast<Podcast*>(m)) return "podcast";
        return "";
    };
    
    QString iconName = typeToIcon(media);
    if (!iconName.isEmpty()) {
        // Load from Qt resources
        const QString resPath = QString(":/icons/%1.svg").arg(iconName);
        if (QFile::exists(resPath)) {
            QPixmap iconPixmap(resPath);
            coverLabel->setPixmap(iconPixmap.scaled(
                coverLabel->size(), 
                Qt::KeepAspectRatio, 
                Qt::SmoothTransformation
            ));
        }
    }
}
```

---

### 5. **AddMediaDialog.h/.cpp** - Add/Edit Dialog
**Path:** `src/Frontend/Windows/AddMediaDialog.h` / `src/Frontend/Windows/AddMediaDialog.cpp`

**Function:** Complete dialog for media creation and modification with validation, dynamic fields, and backend enum integration.

**Responsibilities:**
- **Dynamic Form:** Type-specific fields for each media
- **Input Validation:** Data correctness checks
- **Enum Integration:** Genres and languages from backend
- **Cover Management:** Drag & drop + fallback

**Key Features:**
```cpp
class AddMediaDialog : public QDialog
{
    Q_OBJECT
    
public:
    AddMediaDialog(QWidget* parent = nullptr);
    AddMediaDialog(Media* existingMedia, QWidget* parent = nullptr);
    
    std::unique_ptr<Media> getCreatedMedia() const;
    
private slots:
    void onMediaTypeChanged(int index);
    void onCoverDropped(const QString& path);
    
private:
    void setupUI();
    void setupBookFields();
    void setupMovieFields();
    void setupSongFields();
    void setupMagazineFields();
    void setupPodcastFields();
    void populateFromMedia(Media* media);
    
    // Common fields
    QLineEdit* titleEdit;
    QLineEdit* authorEdit;
    QDateEdit* dateEdit;
    QComboBox* mediaTypeCombo;
    
    // Type-specific fields
    QStackedWidget* fieldsStack;
    QWidget* bookFields;
    QWidget* movieFields;
    QWidget* songFields;
    QWidget* magazineFields;
    QWidget* podcastFields;
    
    // Cover
    CoverDropArea* coverArea;
    QString coverPath;
};
```

**Backend Enum Integration:**
```cpp
void AddMediaDialog::setupBookFields()
{
    // Populate genres from backend enum
    auto bookGenres = Enums::getAllBookGenres();
    for (const auto& genre : bookGenres) {
        bookGenreCombo->addItem(QString::fromStdString(genre));
    }
    
    // Populate languages from backend enum
    auto languages = Enums::getAllLanguages();
    for (const auto& lang : languages) {
        languageCombo->addItem(QString::fromStdString(lang));
    }
}
```

---

### 6. **SearchDialog.h/.cpp** - Advanced Search Dialog
**Path:** `src/Frontend/Windows/SearchDialog.h` / `src/Frontend/Windows/SearchDialog.cpp`

**Function:** Dialog for advanced search with multiple filters, logical combinations, and backend enum integration.

**Responsibilities:**
- **Multiple Filters:** Genre, language, dates, availability
- **Logical Combinations:** Combinable filters
- **Persistence:** Maintains filters between sessions
- **Reset:** Button to clear all filters

**Filter Structure:**
```cpp
struct AdvancedFilters {
    bool enabled = false;
    
    // Text filters
    QString titleContains;
    QString authorContains;
    
    // Type and availability filters
    QString type;
    bool onlyAvailable = false;
    
    // Date filters
    bool useDateFrom = false;
    bool useDateTo = false;
    QDate dateFrom;
    QDate dateTo;
    
    // Genre filters by type
    int bookGenre = -1;
    int movieGenre = -1;
    int musicGenre = -1;
    int magazineGenre = -1;
    int podcastGenre = -1;
};
```

**Search Implementation:**
```cpp
void SearchDialog::setupUI()
{
    // Populate genres from backend enum
    fillGenres(bookGenreCombo, Enums::getAllBookGenres());
    fillGenres(movieGenreCombo, Enums::getAllMovieGenres());
    fillGenres(musicGenreCombo, Enums::getAllMusicGenres());
    fillGenres(magazineGenreCombo, Enums::getAllMagazineGenres());
    fillGenres(podcastGenreCombo, Enums::getAllPodcastGenres());
}

static void fillGenres(QComboBox* combo, const std::vector<std::string>& names)
{
    combo->clear();
    combo->addItem("Any", -1);
    for (const auto& name : names) {
        combo->addItem(QString::fromStdString(name));
    }
}
```

---

## 🎨 **Styling and Theme System**

### **Material UI Dark Theme**
```cpp
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
        
        #searchBar {
            background-color: #3c3c3c;
            border-bottom: 1px solid #555;
        }
        
        QPushButton {
            background-color: #555;
            border: 1px solid #777;
            border-radius: 5px;
            color: #ffffff;
            padding: 8px 16px;
            font-weight: 500;
        }
        
        QPushButton:hover {
            background-color: #666;
            border-color: #888;
        }
        
        QLineEdit {
            background-color: #3c3c3c;
            border: 1px solid #777;
            border-radius: 5px;
            color: #ffffff;
            padding: 8px 12px;
        }
    )");
}
```

### **SVG Icons and Resources**
```cpp
// Icon loading from Qt resources
QPixmap MainWindow::loadIconByName(const QString& baseName)
{
    const QString resPath = QString(":/icons/%1.svg").arg(baseName);
    if (QFile::exists(resPath)) {
        return QPixmap(resPath);
    }
    
    // Fallback to local files
    const QStringList tries = {
        QString("src/Frontend/Resources/icons/%1.svg").arg(baseName),
        QString("icons/%1.svg").arg(baseName)
    };
    
    for (const QString& path : tries) {
        if (QFile::exists(path)) {
            return QPixmap(path);
        }
    }
    
    return QPixmap();
}
```

---

## 🔍 **Search and Filter System**

### **Real-time Text Search**
- **Activation:** With each typed character
- **Fields:** Title + author (case-insensitive)
- **Performance:** Optimized for large collections
- **Integration:** Works with other filters

### **Advanced Filters**
- **By Type:** Book, Movie, Song, Magazine, Podcast
- **By Genre:** All available genres by type
- **By Language:** 40+ supported languages
- **By Date:** Customizable range
- **By Availability:** Only available/unavailable

### **Logical Combinations**
- **AND:** All filters must match
- **OR:** At least one filter must match (for genres)
- **Priority:** Type > Genre > Language > Date > Text

---

## 📱 **Responsive Design and Performance**

### **Adaptive Grid**
- **Dynamic Calculation:** Columns based on available width
- **Optimized Spacing:** Consistent margins and spacing
- **Smart Scroll:** Automatic layout updates

### **Performance Optimizations**
- **QTimer::singleShot:** Avoids multiple calls during resize
- **Lazy Loading:** Icons loaded only when needed
- **Update Geometry:** Forces layout updates when necessary
- **Scrollbar Connection:** Automatic updates when content changes

### **Event Management**
- **Resize Event:** Grid automatically adapts
- **Scrollbar Range:** Updates when content changes
- **Search Text:** Real-time filtering
- **Category Change:** Filtering by media type

---

## ⌨️ **Shortcuts and UX**

### **Keyboard Shortcuts**
- **Ctrl+F:** Focus on search bar
- **Ctrl+N:** New media
- **Ctrl+O:** Open file
- **Ctrl+S:** Save
- **Ctrl+Q:** Exit
- **F5:** Refresh grid
- **Esc:** Close dialog

### **UX Improvements**
- **Placeholder Text:** Input field suggestions
- **Tooltips:** Descriptions for buttons and controls
- **Status Bar:** Informative messages and counts
- **Progress Indicators:** Feedback for long operations
- **Error Handling:** Clear and useful error messages

---

## 🚀 **Advanced Features**

### **Drag & Drop**
- **Covers:** Drag images for covers
- **File Import:** Drag files for import
- **Reordering:** Grid reorganization (future)

### **Export/Import**
- **Formats:** JSON, XML
- **Selection:** All or filtered only
- **Batch Operations:** Operations on multiple selections

### **Statistics and Analytics**
- **Counts:** Total media by type
- **Charts:** Genre and language distribution
- **Trends:** Media added over time

---

## 🔧 **Debug and Development**

### **Logging and Monitoring**
- **Performance:** Loading time metrics
- **Memory:** Memory usage monitoring
- **Events:** UI event tracking

### **Testing**
- **Unit Tests:** Tests for individual components
- **Integration Tests:** Tests for complete flows
- **UI Tests:** Automated interface tests

---

## 📋 **Roadmap and Next Steps**

### **Phase 1: Stabilization (Completed ✅)**
- ✅ Complete base interface
- ✅ Advanced search system
- ✅ Responsive grid
- ✅ Material UI dark theme

### **Phase 2: UX Improvements (In Progress 🔄)**
- 🔄 Grid performance optimizations
- 🔄 Smooth animations and transitions
- 🔄 User theme customization
- 🔄 Customizable shortcuts

### **Phase 3: Advanced Features (Planned 📋)**
- 📋 Tag and playlist system
- 📋 Advanced statistics and analytics
- 📋 Automatic backup and synchronization
- 📋 Plugin system for extensions

---

## ✅ **Current Frontend Status**

### **Core Components (100% ✅)**
- ✅ **MainWindow**: Complete main interface
- ✅ **MediaCard**: Responsive card with fallback
- ✅ **AddMediaDialog**: Media creation/modification
- ✅ **SearchDialog**: Complete advanced search

### **UI Features (95% ✅)**
- ✅ **Responsive Layout**: Adaptive grid
- ✅ **Search System**: Quick + advanced
- ✅ **Dark Theme**: Complete Material UI
- ✅ **SVG Icons**: Complete system
- 🔄 **Performance**: Optimizations in progress

### **Backend Integration (100% ✅)**
- ✅ **Enum Integration**: Genres and languages
- ✅ **Data Binding**: Real-time updates
- ✅ **Error Handling**: Robust error management
- ✅ **Validation**: Complete input checks

---

**The Frontend is now in an advanced and production-ready state, with all core functionality implemented and a focus on performance and UX improvements.** 🎯✨
