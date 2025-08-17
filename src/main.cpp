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
    
    // Create and display the main application window
    MainWindow mainWindow;
    mainWindow.show();
    
    // Start the Qt event loop
    return app.exec();
}
