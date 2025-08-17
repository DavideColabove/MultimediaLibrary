#ifndef SEARCHDIALOG_H
#define SEARCHDIALOG_H

#include <QDialog>
#include <QFormLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QComboBox>
#include <QDateEdit>
#include <QDate>
#include <QCheckBox>
#include <QPushButton>
#include <QStackedWidget>
#include <QGroupBox>

#include "../../Backend/Enums/Genres.h"

/**
 * @brief Structure containing advanced search filter criteria
 * 
 * This structure holds all the search parameters for advanced filtering
 * of media items. It supports filtering by type, title, author, date range,
 * availability, and type-specific genres.
 */
struct AdvancedFilters
{
    bool enabled = false;           // Flag indicating if advanced filters are active
    QString type;                   // Media type filter ("", "Book", "Movie", "Song", "Magazine", "Podcast")
    QString titleContains;          // Title substring filter
    QString authorContains;         // Author substring filter
    bool useDateFrom = false;       // Flag for using start date filter
    QDate dateFrom;                 // Start date for date range filter
    bool useDateTo = false;         // Flag for using end date filter
    QDate dateTo;                   // End date for date range filter
    bool onlyAvailable = false;     // Flag for filtering only available items
    
    // Type-specific genre filters (using enum indices)
    int bookGenre = -1;             // Book genre filter index
    int movieGenre = -1;            // Movie genre filter index
    int musicGenre = -1;            // Music genre filter index
    int magazineGenre = -1;         // Magazine genre filter index
    int podcastGenre = -1;          // Podcast genre filter index
};

/**
 * @brief Dialog for advanced search and filtering
 * 
 * This dialog provides a comprehensive interface for advanced search and
 * filtering of media items. It supports filtering by multiple criteria
 * including type, title, author, date range, availability, and type-specific
 * genres. The interface dynamically adapts based on the selected media type.
 * 
 * Features include:
 * - Dynamic form fields based on selected media type
 * - Date range filtering with optional start/end dates
 * - Genre filtering for each media type
 * - Availability filtering
 * - Integration with backend enum system
 * - Preset filter loading and saving
 */
class SearchDialog : public QDialog
{
    Q_OBJECT
public:
    /**
     * @brief Constructs a search dialog with initial filter criteria
     * @param initial Initial filter criteria to populate the dialog
     * @param parent Parent widget (optional)
     */
    explicit SearchDialog(const AdvancedFilters& initial, QWidget* parent = nullptr);
    
    /**
     * @brief Gets the current search criteria
     * @return AdvancedFilters structure containing current search parameters
     */
    AdvancedFilters criteria() const { return current; }

private slots:
    /**
     * @brief Handles media type selection changes
     * @param idx Selected media type index
     */
    void onTypeChanged(int idx);
    
    /**
     * @brief Handles accept button clicks
     */
    void onAccept();

private:
    // UI setup methods
    void setupUI();
    void setupTypeSpecific();
    void populateFrom(const AdvancedFilters& initial);

    AdvancedFilters current;        // Current search criteria

    // Main layout components
    QVBoxLayout* mainLayout;        // Main vertical layout
    QFormLayout* formLayout;        // Form layout for input fields
    
    // Common search fields
    QComboBox* typeCombo;           // Media type dropdown
    QLineEdit* titleEdit;           // Title search input
    QLineEdit* authorEdit;          // Author search input
    QCheckBox* fromCheck;           // Start date checkbox
    QDateEdit* fromDate;            // Start date picker
    QCheckBox* toCheck;             // End date checkbox
    QDateEdit* toDate;              // End date picker
    QCheckBox* availableCheck;      // Available only checkbox

    // Type-specific genre filtering
    QGroupBox* typeGroup;           // Type-specific filters group box
    QStackedWidget* typeStack;      // Stacked widget for different type pages
    
    // Container widgets for each media type
    QWidget* bookPage;              // Book filters page
    QComboBox* bookGenreCombo;      // Book genre dropdown
    QWidget* moviePage;             // Movie filters page
    QComboBox* movieGenreCombo;     // Movie genre dropdown
    QWidget* songPage;              // Song filters page
    QComboBox* musicGenreCombo;     // Music genre dropdown
    QWidget* magazinePage;          // Magazine filters page
    QComboBox* magazineGenreCombo;  // Magazine genre dropdown
    QWidget* podcastPage;           // Podcast filters page
    QComboBox* podcastGenreCombo;   // Podcast genre dropdown
};

#endif // SEARCHDIALOG_H


