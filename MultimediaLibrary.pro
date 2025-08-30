QT += core widgets svg

CONFIG += c++17

TARGET = MultimediaLibrary
TEMPLATE = app

# Define USE_QT flag for conditional compilation
DEFINES += USE_QT

# Backend sources
SOURCES += \
    src/main.cpp \
    src/Backend/Elements/Date.cpp \
    src/Backend/Elements/Media.cpp \
    src/Backend/Elements/Book.cpp \
    src/Backend/Elements/Movie.cpp \
    src/Backend/Elements/Song.cpp \
    src/Backend/Elements/Magazine.cpp \
    src/Backend/Elements/Podcast.cpp \
    src/Backend/Enums/Genres.cpp \
    src/Backend/Enums/Languages.cpp \
    src/Backend/Library/Library.cpp \
    src/Backend/Persistence/JsonPersistence.cpp \
    src/Backend/Persistence/XmlPersistence.cpp

# Classic (legacy style) view adaptation sources (work in progress)
SOURCES += \
    src/Frontend/View/ClassicMainWindow.cpp \
    src/Frontend/View/ListWidgets/ItemCardWidget.cpp \
    src/Frontend/View/ListWidgets/ItemListWidget.cpp \
    src/Frontend/View/DetailWidgets/ItemDetailWidget.cpp \
    src/Frontend/View/EditWidgets/ItemEditDialog.cpp

# Backend headers
HEADERS += \
    src/Backend/Elements/Date.h \
    src/Backend/Elements/Media.h \
    src/Backend/Elements/MediaVisitor.h \
    src/Backend/Elements/Book.h \
    src/Backend/Elements/Movie.h \
    src/Backend/Elements/Song.h \
    src/Backend/Elements/Magazine.h \
    src/Backend/Elements/Podcast.h \
    src/Backend/Enums/Genres.h \
    src/Backend/Enums/Languages.h \
    src/Backend/Library/Library.h \
    src/Backend/Persistence/IPersistence.h \
    src/Backend/Persistence/JsonPersistence.h \
    src/Backend/Persistence/XmlPersistence.h

# Classic (legacy style) view adaptation headers
HEADERS += \
    src/Frontend/View/ClassicMainWindow.h \
    src/Frontend/View/ListWidgets/ItemCardWidget.h \
    src/Frontend/View/ListWidgets/ItemListWidget.h \
    src/Frontend/View/DetailWidgets/ItemDetailWidget.h \
    src/Frontend/View/EditWidgets/ItemEditDialog.h

# Include paths
INCLUDEPATH += \
    src/Backend/Elements \
    src/Backend/Enums \
    src/Backend/Library \
    src/Frontend/View \
    src/Frontend/View/ListWidgets \
    src/Frontend/View/DetailWidgets \
    src/Frontend/View/EditWidgets

# Compiler flags
QMAKE_CXXFLAGS += -std=c++17 -Wall -Wextra

# Ensure QtSvg module is available
!qtHaveModule(svg) {
    error("QtSvg not found. Install the module (e.g., Ubuntu/Debian: 'sudo apt install qt6-base-dev qt6-svg-dev')")
}

# Output directory
DESTDIR = build/bin

# Optional: add icons resource file if present
exists(resources.qrc) {
    RESOURCES += resources.qrc
}
