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
    src/Backend/Persistence/XmlPersistence.cpp \
    src/Frontend/Windows/MainWindow.cpp \
    src/Frontend/Windows/MediaCard.cpp \
    src/Frontend/Windows/AddMediaDialog.cpp \
    src/Frontend/Windows/SearchDialog.cpp \
    src/Frontend/Windows/LeftSidebarWidget.cpp \
    src/Frontend/Windows/TopBarWidget.cpp \
    src/Frontend/Windows/FlowLayout.cpp \
    src/Frontend/Windows/MediaGridWidget.cpp \
    src/Frontend/Windows/DetailsPanel.cpp \
    src/Frontend/Windows/addItemWidgets/BookFormWidget.cpp \
    src/Frontend/Windows/addItemWidgets/MovieFormWidget.cpp \
    src/Frontend/Windows/addItemWidgets/SongFormWidget.cpp \
    src/Frontend/Windows/addItemWidgets/MagazineFormWidget.cpp \
    src/Frontend/Windows/addItemWidgets/PodcastFormWidget.cpp

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
    src/Backend/Persistence/IPersistence.h \
    src/Backend/Enums/Genres.h \
    src/Backend/Enums/Languages.h \
    src/Backend/Library/Library.h \
    src/Backend/Persistence/JsonPersistence.h \
    src/Backend/Persistence/XmlPersistence.h \
    src/Frontend/Windows/MainWindow.h \
    src/Frontend/Windows/MediaCard.h \
    src/Frontend/Windows/AddMediaDialog.h \
    src/Frontend/Windows/SearchDialog.h \
    src/Frontend/Windows/LeftSidebarWidget.h \
    src/Frontend/Windows/TopBarWidget.h \
    src/Frontend/Windows/FlowLayout.h \
    src/Frontend/Windows/MediaGridWidget.h \
    src/Frontend/Windows/DetailsPanel.h \
    src/Frontend/Windows/addItemWidgets/BookFormWidget.h \
    src/Frontend/Windows/addItemWidgets/MovieFormWidget.h \
    src/Frontend/Windows/addItemWidgets/SongFormWidget.h \
    src/Frontend/Windows/addItemWidgets/MagazineFormWidget.h \
    src/Frontend/Windows/addItemWidgets/PodcastFormWidget.h

# Removed obsolete MediaFactory and Persistence sources

# Include paths
INCLUDEPATH += \
    src/Backend/Elements \
    src/Backend/Enums \
    src/Backend/Library \
    src/Frontend/Windows \
    src/Frontend/Windows/addItemWidgets

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
