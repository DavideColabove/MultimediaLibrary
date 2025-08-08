QT += core widgets

CONFIG += c++17

TARGET = MultimediaLibrary
TEMPLATE = app

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
    src/Frontend/Windows/MainWindow.cpp

# Backend headers
HEADERS += \
    src/Backend/Elements/Date.h \
    src/Backend/Elements/Media.h \
    src/Backend/Elements/Book.h \
    src/Backend/Elements/Movie.h \
    src/Backend/Elements/Song.h \
    src/Backend/Elements/Magazine.h \
    src/Backend/Elements/Podcast.h \
    src/Backend/Enums/Genres.h \
    src/Backend/Enums/Languages.h \
    src/Backend/Library/Library.h \
    src/Frontend/Windows/MainWindow.h

# Include paths
INCLUDEPATH += \
    src/Backend/Elements \
    src/Backend/Enums \
    src/Backend/Library \
    src/Frontend/Windows

# Compiler flags
QMAKE_CXXFLAGS += -std=c++17 -Wall -Wextra

# Output directory
DESTDIR = build/bin
