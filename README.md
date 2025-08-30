# Multimedia Library

A complete and modern multimedia library with C++17 backend and Qt 6 frontend, designed to manage books, movies, songs, magazines, and podcasts with an elegant and functional graphical interface.

## 🚀 **Main Features**

- **🎯 C++17 Backend**: Robust architecture with advanced design patterns
- **🎨 Qt 6 Frontend**: Modern graphical interface with Material UI dark theme
- **🔍 Advanced Search**: Real-time textual search + advanced filters
- **📱 Responsive UI**: Adaptive grid that automatically resizes
- **🎵 Multi-Media Support**: 5 media types with specific properties
- **💾 Data Persistence**: Save/load in JSON and XML
- **⌨️ Keyboard Shortcuts**: Fast navigation with global shortcuts
- **🎭 Customizable Theme**: Advanced CSS styling with SVG icons

## 📁 **Project Structure**

```
MultimediaLibrary/
├── src/
│   ├── Backend/
│   │   ├── Elements/              # Base and derived classes
│   │   │   ├── Media.h/.cpp       # Abstract base class
│   │   │   ├── Book.h/.cpp        # Book management
│   │   │   ├── Movie.h/.cpp       # Movie management
│   │   │   ├── Song.h/.cpp        # Song management
│   │   │   ├── Magazine.h/.cpp    # Magazine management
│   │   │   ├── Podcast.h/.cpp     # Podcast management
│   │   │   └── Date.h/.cpp        # Custom date class
│   │   ├── Enums/                 # Typed enums for genres and languages
│   │   │   ├── Genres.h/.cpp      # Genres for all media types
│   │   │   └── Languages.h/.cpp   # Supported languages
│   │   ├── Library/               # Media collection management
│   │   │   └── Library.h/.cpp     # CRUD, search, filters, statistics
│   │   └── Persistence/           # Data save/load
│   │       ├── JsonPersistence.h/.cpp
│   │       └── XmlPersistence.h/.cpp
│   ├── Frontend/
│   │   ├── View/                  # New classic UI layer (replaces legacy Windows/)
│   │   │   ├── ClassicMainWindow.h/.cpp   # Primary application window
│   │   │   ├── ListWidgets/                # List & card widgets
│   │   │   │   ├── ItemListWidget.h/.cpp
│   │   │   │   └── ItemCardWidget.h/.cpp
│   │   │   ├── DetailWidgets/              # Detail/inspection widgets
│   │   │   │   └── ItemDetailWidget.h/.cpp
│   │   │   └── EditWidgets/                # Create/Edit dialog
│   │   │       └── ItemEditDialog.h/.cpp
│   │   └── Resources/             # Graphic resources
│   │       └── icons/             # SVG icons for each media type
│   └── main.cpp                   # Application entry point
├── resources.qrc                   # Qt resources file
├── MultimediaLibrary.pro           # Qt project
├── Frontend_Documentation.md       # Frontend documentation
├── Backend_Documentation.md        # Backend documentation
└── README.md                       # This file
```

## 🛠️ **Prerequisites**

### **Backend (Required)**
- **MSYS2** with MinGW-w64
- **Make** (installed via MSYS2)
- **g++** (C++17 compiler)

### **Qt Frontend (Required)**
- **Qt 6.8.3** installed in `D:\qt\6.8.3\mingw_64`
- **Qt Creator** for development (optional)
 - Module QtSvg (required)

## 🔧 **Installation and Setup**

### 1. **Install Make (if not present)**
```bash
# Add to PATH
$env:PATH += ";C:\msys64\usr\bin"
```

### 2. **Configure Qt**
```bash
# Add Qt to PATH
$env:PATH += "path"
```

## 🏗️ **Compilation**

### **Option 1: Qt/qmake (Recommended)**
```bash
# Generate Makefile from Qt project
qmake MultimediaLibrary.pro

# Compile
make

# Clean
make clean
```

### **Linux quick setup**
```bash
# Install build deps (auto-detects distro)
bash scripts/setup-linux.sh

# Build
qmake MultimediaLibrary.pro  # or qmake6
make
./build/bin/MultimediaLibrary
```
Nota: il progetto richiede QtSvg. In assenza del modulo, il file `.pro` fallirà con un messaggio chiaro.

## 🚀 **Execution**

### **GUI Mode (Main)**
```bash
# Launch Qt graphical interface
./build/bin/MultimediaLibrary.exe
```

## 🎯 **Implemented Features**

### **✅ Complete Backend**
- **Media Base Class**: Abstract interface for all types
- **Derived Classes**: Book, Movie, Song, Magazine, Podcast
- **Enum System**: Typed genres and languages for each media
- **Library Class**: Complete CRUD, search, filters, statistics
- **Persistence**: Save/load in JSON and XML
- **Validation**: Data integrity checks

### **✅ Advanced Qt Frontend**
- **ClassicMainWindow**: Unified main window (toolbar + list + detail)
- **ItemListWidget / ItemCardWidget**: Sortable & filterable list with per-type icon
- **ItemDetailWidget**: Rich metadata + edit/delete actions
- **ItemEditDialog**: Unified create/edit dialog (dynamic subtype pages)
- **Inline Search & Filters**: Title/author search, type & availability filters
- **Sorting**: Title (A↔Z) and date (newest/oldest)
- **Keyboard Shortcuts**: Productivity-focused key bindings

### **✅ Advanced UX/UI**
- **Dark Theme**: Material-inspired palette
- **SVG Icons**: Scalable per media type
- **Split Layout**: Persistent list + detail in splitter
- **Keyboard Shortcuts**: Comprehensive set
- **Responsive Design**: Panels adapt on resize

## 📚 **Architecture and Design Patterns**

### **Backend Patterns**
- **Inheritance/Polymorphism**: Media hierarchy with derived classes
- **Visitor Pattern**: `MediaVisitor` for type-specific operations
- **Strategy Pattern**: Persistence in different formats
- **Factory Pattern**: Dynamic creation of media objects
- **Observer Pattern**: Change notifications

### **Frontend Patterns**
- **MVC**: Separation between logic and presentation
- **Signal/Slot**: Asynchronous Qt communication
- **Widget Composition**: Modular UI assembly
- **Resource Management**: Centralized resource management

## 🎨 **User Interface**

### **Main Components**
- **Toolbar**: File ops, create/edit/delete, filters, sorting
- **Search Field**: Real-time title/author query
- **Type & Availability Filters**: Inline combobox + checkbox
- **List Panel**: Vertical list of media cards
- **Detail Panel**: Contextual attributes & actions
- **Status Feedback**: Dialogs / selection cues

### **UI Features**
- **Instant Search**: Title/author, persistent across rebuilds
- **Sorting**: Title (A→Z/Z→A) & Date (newest/oldest)
- **Inline Filters**: Type + availability toggle
- **Unified Dialog**: Single edit dialog for all subtypes
- **Responsive Splitter**: Remembers sizing
- **Dark Theme**: SVG icon support

## 🔍 **Search System**

### **Quick Search (Search Bar)**
- **Real-time**: Activates with each character typed
- **Case-insensitive**: Doesn't distinguish uppercase/lowercase
- **Multi-field**: Searches in title AND author
- **Integrated**: Works with other filters

<!-- Legacy Advanced Search dialog removed; simplified inline search + filters retained. -->

## 💾 **Data Management**

### **Supported Formats**
- **JSON**: Main format, readable and compatible
- **XML**: Alternative format for interoperability

### **Operations**
- **Import/Export**: Data loading and saving
- **Backup**: Automatic saving
- **Validation**: Data integrity checks
- **Migration**: Conversion between formats

## 🎵 **Supported Media Types**

### **Book**
- **Properties**: Title, author, publisher, pages, ISBN, language, genre
- **Genres**: Fiction, Non-Fiction, Mystery, Thriller, Romance, Sci-Fi, Fantasy, Horror, Historical, Biography, Self-Help, Business, Philosophy, Religion, Science, Technology, Cooking, Travel, Poetry, Drama, Children, Young Adult, Academic

### **Movie**
- **Properties**: Title, director, duration, rating, language, genre
- **Genres**: Action, Adventure, Comedy, Drama, Horror, Thriller, Sci-Fi, Fantasy, Romance, Documentary, Animation, Crime, Mystery, War, Western, Musical, Historical, Biographical, Family, Superhero

### **Song**
- **Properties**: Title, artist, album, duration, genre
- **Genres**: Pop, Rock, Jazz, Classical, Hip-Hop, Electronic, Country, Blues, Folk, R&B, Metal, Punk, Reggae, World, Alternative, Indie, Gospel, Soul, Funk, Disco

### **Magazine**
- **Properties**: Title, publisher, issue, language, genre
- **Genres**: News, Fashion, Technology, Science, Health, Business, Politics, Entertainment, Sports, Travel, Food, Home, Art, Literature, Education, Finance, Lifestyle, Automotive, Gaming, Music

### **Podcast**
- **Properties**: Title, host, episodes, duration, genre
- **Genres**: News, Technology, Business, Education, Entertainment, Comedy, True Crime, History, Science, Health, Politics, Sports, Music, Arts, Literature, Philosophy, Religion, Travel, Food, Lifestyle

### **Supported Languages**
"Italian", "English", "Spanish", "French", "German", "Portuguese", "Russian", 
                "Chinese", "Japanese", "Korean", "Arabic", "Hindi", "Dutch", "Swedish", 
                "Norwegian", "Danish", "Finnish", "Polish", "Czech", "Hungarian", "Romanian", 
                "Bulgarian", "Greek", "Turkish", "Hebrew", "Persian", "Thai", "Vietnamese", 
                "Indonesian", "Malay", "Filipino", "Latin", "Ancient Greek", "Sanskrit", 
                "Old English", "Middle English", "Old French", "Old German", "Old Italian", 
                "Old Spanish", "Old Portuguese", "Old Russian", "Old Chinese", "Old Japanese", 
                "Old Korean", "Old Arabic", "Old Hindi", "Old Dutch", "Old Swedish", 
                "Old Norwegian", "Old Danish", "Old Finnish", "Old Polish", "Old Czech", 
                "Old Hungarian", "Old Romanian", "Old Bulgarian", "Old Greek", "Old Turkish", 
                "Old Hebrew", "Old Persian", "Old Thai", "Old Vietnamese", "Old Indonesian", 
                "Old Malay", "Old Filipino", "Old Latin", "Old Ancient Greek", "Old Sanskrit", "Other"

## 🔧 **Debug and Development**

### **Debug Compilation**
```bash
make debug
```

### **Qt Verification**
```bash
qmake --version
```

### **Make Verification**
```bash
make --version
```

### **Logging and Debug**
- **Error Handling**: Robust error management
- **Performance Monitoring**: Performance metrics
- **Memory Management**: Optimized memory management

## 📝 **Development Notes**

### **To Open in Qt Creator**
1. Open `MultimediaLibrary.pro` in Qt Creator
2. Configure MinGW kit
3. Compile and run directly from Qt Creator

### **For Terminal Development**
1. Use `qmake && make` to compile GUI
2. Use `./build/bin/MultimediaLibrary.exe` to run
3. Use `make clean` to clean build files

### **Code Structure**
- **Backend**: Pure C++17, no Qt dependencies
- **Frontend**: Qt 6, complete graphical interface
- **Separation**: Business logic separated from UI
- **Modularity**: Reusable and testable components

## 🎯 **Next Steps and Roadmap**

### **Phase 1: Stabilization (Completed ✅)**
- ✅ Robust backend architecture
- ✅ Complete Qt interface
- ✅ Advanced search system
- ✅ JSON/XML data persistence

### **Phase 2: UX Improvements (In Progress 🔄)**
- 🔄 Grid performance optimization
- 🔄 Responsive design improvement
- 🔄 Smooth animations addition
- 🔄 User theme customization

## ✅ **Current Project Status**

### **Backend (100% ✅)**
- ✅ **Architecture**: Design patterns implemented
- ✅ **Media Classes**: Complete and functional hierarchy
- ✅ **Enum System**: Typed genres and languages
- ✅ **Library Class**: CRUD, search, filters, statistics
- ✅ **Persistence**: JSON and XML working
- ✅ **Validation**: Complete integrity checks

### **Frontend (95% ✅)**
- ✅ **ClassicMainWindow**: Unified list + detail layout
- ✅ **ItemListWidget / ItemCardWidget**: Listing with filtering & sorting
- ✅ **ItemDetailWidget**: Detailed metadata + actions
- ✅ **ItemEditDialog**: Create/Edit unified dialog
- ✅ **Search & Filters**: Inline search, type & availability
- ✅ **Sorting**: Title/date modes
- ✅ **Theme & Icons**: Dark theme + SVG icons
- ✅ **Shortcuts**: Comprehensive set
- 🔄 **Performance**: Optimizations in progress

### **Documentation (90% ✅)**
- ✅ **README**: Complete project guide
- ✅ **Frontend Documentation**: Frontend documentation
- ✅ **Backend Documentation**: Backend documentation
- 🔄 **Code Comments**: Comments in code

### **Testing and Quality (90% ✅)**
- ✅ **Compilation**: Working build system
- ✅ **Runtime**: Stable and performant application
- ✅ **Error Handling**: Robust error management
- 🔄 **Integration Tests**: Integration tests planned

---

Legacy GUI components (MainWindow, MediaCard, AddMediaDialog, SearchDialog) have been removed from source and build in favor of the lean Classic view architecture.

**Developed with ❤️ using C++17, Qt 6.8.3 and Make** 🚀

