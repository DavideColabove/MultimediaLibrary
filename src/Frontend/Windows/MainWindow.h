#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenuBar>
#include <QStatusBar>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QWidget>
#include <QAction>
#include <QMessageBox>
#include <QFileDialog>
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
#include <QFormLayout>

#include "../../Backend/Elements/Media.h"
#include "../../Backend/Elements/Book.h"
#include "../../Backend/Elements/Movie.h"
#include "../../Backend/Elements/Song.h"
#include "../../Backend/Elements/Magazine.h"
#include "../../Backend/Elements/Podcast.h"
#include "../../Backend/Library/Library.h"
#include "MediaCard.h"
#include "AddMediaDialog.h"
#include "SearchDialog.h"

/**
 * @brief Main application window for the Multimedia Library
 * 
 * This class implements the primary user interface for the multimedia library
 * application. It provides a modern, responsive interface with a three-panel
 * layout: sidebar navigation, central media grid, and details panel. The window
 * supports real-time search, filtering, sorting, and comprehensive media management.
 * 
 * Features include:
 * - Responsive grid layout that adapts to window size
 * - Real-time search and filtering
 * - Category-based navigation
 * - Media details view with cover images
 * - Keyboard shortcuts for common operations
 * - Dark theme with Material UI styling
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @brief Constructs the main window
     * @param parent Parent widget (optional)
     */
    MainWindow(QWidget *parent = nullptr);
    
    /**
     * @brief Destructor
     */
    ~MainWindow();

protected:
    /**
     * @brief Handles window resize events for responsive layout
     * @param event Resize event information
     */
    void resizeEvent(QResizeEvent *event) override;

private slots:
    // Media management operations
    void addMedia();
    void editMedia();
    void deleteMedia();
    void exportData();
    void importData();
    void about();
    void showShortcuts();
    
    // UI interaction handlers
    void onCategoryChanged(int index);
    void onMediaCardClicked(const Media* media);
    void onBackToGridClicked();
    void onSearchTextChanged(const QString& text);
    void onAdvancedSearchClicked();
    void saveTriggered();
    void clearAdvancedFilters();
    void onSortChanged(int index);
    void onScrollBarRangeChanged();

private:
    // UI setup methods
    void setupUI();
    void setupMenuBar();
    void setupStatusBar();
    void setupLeftSidebar();
    void setupCentralArea();
    void setupRightPanel();
    void setupConnections();
    void applyDarkTheme();
    
    // Filter and utility methods
    bool mediaMatchesFilters(const Media* media) const;
    QString categoryToType(const QString& category) const;
    
    // Main layout components
    QWidget *centralWidget;      // Central widget containing all UI elements
    QHBoxLayout *mainLayout;     // Main horizontal layout
    
    // Left sidebar components
    QWidget *leftSidebar;        // Sidebar container
    QVBoxLayout *sidebarLayout;  // Sidebar vertical layout
    QLabel *sidebarTitle;        // Sidebar title label
    QListWidget *categoryList;   // Category navigation list
    
    // Central area components
    QWidget *centralArea;        // Central area container
    QVBoxLayout *centralLayout;  // Central area vertical layout
    QWidget *searchBar;          // Search bar container
    QHBoxLayout *searchLayout;   // Search bar horizontal layout
    QLineEdit *searchInput;      // Search input field
    QPushButton *advancedSearchBtn; // Advanced search button
    QPushButton *clearFiltersBtn;   // Clear filters button
    QComboBox *sortCombo;        // Sorting dropdown
    QPushButton *addTopBtn;      // Add media button
    QPushButton *importTopBtn;   // Import button
    QPushButton *exportTopBtn;   // Export button
    QPushButton *saveTopBtn;     // Save button
    QScrollArea *mediaGridArea;  // Scrollable media grid area
    QWidget *mediaGridWidget;    // Media grid container
    QGridLayout *mediaGridLayout; // Media grid layout
    
    // Right panel (details) components
    QWidget *rightPanel;         // Right panel container
    QVBoxLayout *rightLayout;    // Right panel vertical layout
    QWidget *detailsWidget;      // Details widget container
    QVBoxLayout *detailsLayout;  // Details vertical layout
    QLabel *coverImage;          // Cover image display
    QLabel *titleLabel;          // Title label
    QLabel *authorLabel;         // Author label
    QLabel *yearLabel;           // Year label
    QLabel *durationLabel;       // Duration label
    QLabel *summaryLabel;        // Summary label
    QLabel *coverPathLabel;      // Cover path label
    QGroupBox *attributesGroup;  // Attributes group box
    QWidget *attributesWidget;   // Attributes widget container
    QFormLayout *attributesForm; // Attributes form layout
    QPushButton *editBtn;        // Edit button
    QPushButton *deleteBtn;      // Delete button
    QPushButton *backBtn;        // Back to grid button
    
    // Stacked widget for view switching
    QStackedWidget *stackedWidget; // Stacked widget for grid/details views
    QWidget *gridPage;           // Grid view page
    QWidget *detailsPage;        // Details view page
    
    // Menu actions
    QAction *addAction;          // Add media action
    QAction *editAction;         // Edit media action
    QAction *deleteAction;       // Delete media action
    QAction *exportAction;       // Export action
    QAction *importAction;       // Import action
    QAction *shortcutsAction;    // Show shortcuts action
    QAction *saveAction;         // Save action
    QAction *aboutAction;        // About action
    
    // Application data
    std::unique_ptr<Library> library;  // Library backend instance
    Media* selectedMedia;              // Currently selected media item
    QString currentCategoryFilter;     // Current category filter
    QString currentSearchFilter;       // Current search filter
    AdvancedFilters advFilters;        // Advanced search filters
    QString currentSavePath;           // Current save file path
    
    /**
     * @brief Enumeration of available sorting modes
     */
    enum class SortMode { 
        TitleAsc,   // Sort by title ascending
        TitleDesc,  // Sort by title descending
        DateAsc,    // Sort by date ascending
        DateDesc    // Sort by date descending
    };
    SortMode currentSortMode;          // Current sorting mode
    
    // Helper methods for UI management
    void refreshMediaGrid();           // Refreshes the media grid display
    void clearMediaGrid();             // Clears all media cards from grid
    void addMediaCard(const Media* media, int row, int col); // Adds a media card to grid
    void showMediaDetails(const Media* media);               // Shows media details panel
    void hideMediaDetails();           // Hides media details panel
    void clearAttributesForm();        // Clears the attributes form
    void populateAttributesForm(const Media* media); // Populates attributes form with media data
    void filterMediaByCategory(const QString& category); // Filters media by category
    void applySearchFilter(const QString& searchText);   // Applies search filter
    int computeColumnsForWidth(int availableWidth) const; // Computes optimal column count
};

#endif // MAINWINDOW_H 