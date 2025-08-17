#ifndef ADDMEDIADIALOG_H
#define ADDMEDIADIALOG_H

#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QLineEdit>
#include <QSpinBox>
#include <QComboBox>
#include <QPushButton>
#include <QLabel>
#include <QGroupBox>
#include <QCheckBox>
#include <QDateEdit>
#include <QMessageBox>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QMimeData>
#include <QScrollArea>
#include <QFrame>
#include <QStackedWidget>

#include "../../Backend/Elements/Media.h"
#include "../../Backend/Elements/Book.h"
#include "../../Backend/Elements/Movie.h"
#include "../../Backend/Elements/Song.h"
#include "../../Backend/Elements/Magazine.h"
#include "../../Backend/Elements/Podcast.h"
#include "../../Backend/Enums/Genres.h"
#include "../../Backend/Enums/Languages.h"

/**
 * @brief Custom widget for drag-and-drop cover image upload
 * 
 * This widget provides a drag-and-drop interface for uploading cover images
 * to media items. It displays a preview of the uploaded image and supports
 * visual feedback during drag operations.
 */
class CoverDropArea : public QFrame
{
    Q_OBJECT

public:
    /**
     * @brief Constructs a cover drop area
     * @param parent Parent widget (optional)
     */
    explicit CoverDropArea(QWidget *parent = nullptr);
    
    /**
     * @brief Gets the current image path
     * @return Path to the uploaded image
     */
    QString getImagePath() const { return imagePath; }
    
    /**
     * @brief Sets the image path and updates the display
     * @param path Path to the image file
     */
    void setImagePath(const QString &path);

signals:
    /**
     * @brief Signal emitted when an image is dropped
     * @param path Path to the dropped image file
     */
    void imageDropped(const QString &path);

protected:
    /**
     * @brief Handles drag enter events for visual feedback
     * @param event Drag enter event information
     */
    void dragEnterEvent(QDragEnterEvent *event) override;
    
    /**
     * @brief Handles drop events for image upload
     * @param event Drop event information
     */
    void dropEvent(QDropEvent *event) override;
    
    /**
     * @brief Handles custom painting for visual effects
     * @param event Paint event information
     */
    void paintEvent(QPaintEvent *event) override;
    
    /**
     * @brief Handles mouse press events
     * @param event Mouse press event information
     */
    void mousePressEvent(QMouseEvent *event) override;

private:
    QString imagePath;     // Path to the uploaded image
    bool hasImage;         // Flag indicating if an image is loaded
    QPixmap coverPixmap;   // Pixmap for image display
};

/**
 * @brief Dialog for adding and editing media items
 * 
 * This dialog provides a comprehensive interface for creating new media items
 * or editing existing ones. It dynamically adapts its form fields based on
 * the selected media type and includes validation, drag-and-drop image upload,
 * and integration with the backend enum system.
 * 
 * Features include:
 * - Dynamic form fields based on media type
 * - Drag-and-drop cover image upload
 * - Input validation with error messages
 * - Integration with backend genre and language enums
 * - Support for both creation and editing modes
 * - Responsive layout with scrollable content
 */
class AddMediaDialog : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief Constructs a dialog for creating new media items
     * @param parent Parent widget (optional)
     */
    explicit AddMediaDialog(QWidget *parent = nullptr);
    
    /**
     * @brief Constructs a dialog for editing existing media items
     * @param existingMediaToEdit Pointer to the media item to edit
     * @param parent Parent widget (optional)
     */
    explicit AddMediaDialog(Media *existingMediaToEdit, QWidget *parent = nullptr);
    
    /**
     * @brief Destructor
     */
    ~AddMediaDialog();

    /**
     * @brief Gets the created or edited media object
     * @return Unique pointer to the media object
     */
    std::unique_ptr<Media> getCreatedMedia();

private slots:
    /**
     * @brief Handles media type selection changes
     * @param index Selected media type index
     */
    void onMediaTypeChanged(int index);
    
    /**
     * @brief Handles accept button clicks
     */
    void onAcceptClicked();
    
    /**
     * @brief Handles cancel button clicks
     */
    void onCancelClicked();
    
    /**
     * @brief Handles image drop events
     * @param path Path to the dropped image
     */
    void onImageDropped(const QString &path);
    void onChooseImageClicked();
    void onRemoveImageClicked();

private:
    // UI setup methods
    void setupUI();
    void setupCommonFields();
    void setupTypeSpecificFields();
    void setupConnections();
    void applyDarkTheme();
    
    // Type-specific field management
    void clearTypeSpecificFields();
    void setupBookFields(QFormLayout *layout);
    void setupMovieFields(QFormLayout *layout);
    void setupSongFields(QFormLayout *layout);
    void setupMagazineFields(QFormLayout *layout);
    void setupPodcastFields(QFormLayout *layout);
    
    // Validation and data management
    bool validateInput();
    void showValidationError(const QString& message);
    void populateFromMedia(Media *media);
    int findIndexByData(QComboBox *combo, int value) const;

    // Main layout components
    QVBoxLayout *mainLayout;        // Main vertical layout
    QScrollArea *scrollArea;        // Scrollable area for content
    QWidget *scrollContent;         // Scrollable content widget
    
    // Common fields section
    QGroupBox *commonGroup;         // Common fields group box
    QFormLayout *commonLayout;      // Common fields form layout
    QLineEdit *titleEdit;           // Title input field
    QLineEdit *authorEdit;          // Author input field
    QDateEdit *releaseDateEdit;     // Release date picker
    QSpinBox *sizeSpinBox;          // File size input
    QCheckBox *availableCheckBox;   // Availability checkbox
    CoverDropArea *coverDropArea;   // Cover image drop area
    QPushButton *chooseImageBtn;    // Button to choose image via dialog
    QPushButton *removeImageBtn;    // Button to remove current image
    
    // Media type selection
    QComboBox *mediaTypeCombo;      // Media type dropdown
    
    // Type-specific fields section
    QGroupBox *typeSpecificGroup;   // Type-specific fields group box
    QVBoxLayout *typeSpecificLayout; // Type-specific fields layout
    QStackedWidget *typeSpecificStack; // Stacked widget for different types
    
    // Container widgets for each media type
    QWidget *bookWidget;            // Book fields container
    QWidget *movieWidget;           // Movie fields container
    QWidget *songWidget;            // Song fields container
    QWidget *magazineWidget;        // Magazine fields container
    QWidget *podcastWidget;         // Podcast fields container
    
    // Book-specific fields
    QLineEdit *publisherEdit;       // Publisher input
    QSpinBox *pagesSpinBox;         // Page count input
    QLineEdit *isbnEdit;            // ISBN input
    QComboBox *languageCombo;       // Language dropdown
    QComboBox *bookGenreCombo;      // Book genre dropdown
    
    // Movie-specific fields
    QLineEdit *directorEdit;        // Director input
    QSpinBox *durationSpinBox;      // Duration input
    QLineEdit *ratingEdit;          // Rating input
    QLineEdit *studioEdit;          // Studio input
    QComboBox *movieGenreCombo;     // Movie genre dropdown
    
    // Song-specific fields
    QLineEdit *artistEdit;          // Artist input
    QLineEdit *albumEdit;           // Album input
    QSpinBox *songDurationSpinBox;  // Song duration input
    QComboBox *musicGenreCombo;     // Music genre dropdown
    
    // Magazine-specific fields
    QLineEdit *magazinePublisherEdit; // Magazine publisher input
    QSpinBox *issueSpinBox;         // Issue number input
    QLineEdit *issnEdit;            // ISSN input
    QLineEdit *editorEdit;          // Editor input
    QSpinBox *magazinePagesSpinBox; // Magazine page count input
    QLineEdit *frequencyEdit;       // Publication frequency input
    QComboBox *magazineGenreCombo;  // Magazine genre dropdown
    
    // Podcast-specific fields
    QLineEdit *hostEdit;            // Host input
    QSpinBox *episodeSpinBox;       // Episode number input
    QLineEdit *platformEdit;        // Platform input
    QSpinBox *podcastDurationSpinBox; // Podcast duration input
    QLineEdit *seriesEdit;          // Series input
    QLineEdit *descriptionEdit;     // Description input
    QComboBox *podcastGenreCombo;   // Podcast genre dropdown
    
    // Dialog buttons
    QHBoxLayout *buttonLayout;      // Button layout
    QPushButton *acceptBtn;         // Accept button
    QPushButton *cancelBtn;         // Cancel button
    
    // Application data
    std::unique_ptr<Media> createdMedia; // Created or edited media object
    bool isEditMode = false;        // Flag indicating edit mode
    Media *existingMedia = nullptr; // Pointer to existing media for editing
};

#endif // ADDMEDIADIALOG_H
