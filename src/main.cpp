#include <QApplication>
#include <QStyleFactory>
#include <QIcon>
#include "Frontend/Windows/MainWindow.h"

/**
 * @brief Main entry point for the Multimedia Library application
 * 
 * This function initializes the Qt application, configures the application
 * properties, sets up the visual style, creates the main window, and
 * starts the event loop. It serves as the application's bootstrap process.
 * 
 * @param argc Number of command line arguments
 * @param argv Array of command line argument strings
 * @return Application exit code
 */
int main(int argc, char *argv[]) {
    // Ensure crisp icons on HiDPI displays before app construction
    QApplication::setAttribute(Qt::AA_UseHighDpiPixmaps, true);

    // Initialize the Qt application
    QApplication app(argc, argv);
    
    // Configure application metadata
    app.setApplicationName("Multimedia Library");
    app.setApplicationVersion("1.0.0");
    app.setOrganizationName("MultimediaLibrary");
    // App icon from resources
    app.setWindowIcon(QIcon(":/icons/appicon.svg"));
    
    // Set the application style to Fusion for consistent cross-platform appearance
    app.setStyle(QStyleFactory::create("Fusion"));

    // Apply a consistent dark palette across platforms (especially Linux)
    QPalette dark;
    dark.setColor(QPalette::Window, QColor(43, 43, 43));
    dark.setColor(QPalette::WindowText, QColor(255, 255, 255));
    dark.setColor(QPalette::Base, QColor(35, 35, 35));
    dark.setColor(QPalette::AlternateBase, QColor(49, 49, 49));
    dark.setColor(QPalette::ToolTipBase, QColor(53, 53, 53));
    dark.setColor(QPalette::ToolTipText, QColor(255, 255, 255));
    dark.setColor(QPalette::Text, QColor(230, 230, 230));
    dark.setColor(QPalette::Button, QColor(53, 53, 53));
    dark.setColor(QPalette::ButtonText, QColor(255, 255, 255));
    dark.setColor(QPalette::BrightText, QColor(255, 0, 0));
    dark.setColor(QPalette::Link, QColor(42, 130, 218));
    dark.setColor(QPalette::Highlight, QColor(90, 90, 90));
    dark.setColor(QPalette::HighlightedText, QColor(255, 255, 255));
    app.setPalette(dark);
    
    // Create and display the main application window
    MainWindow mainWindow;
    mainWindow.show();
    
    // Start the Qt event loop
    return app.exec();
}
