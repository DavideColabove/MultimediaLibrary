#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedLayout>
#include <memory>

class QToolBar;
class QToolButton;
class QAction;
class ItemListWidget;
class ItemDetailWidget;
class ItemEditWidget;
class Library; // existing backend

/**
 * MainWindow: an adaptation layer replicating the GUI/interaction model
 * from Progetto_Biblioteca-main while targeting the MultimediaLibrary backend.
 *
 * Incremental migration strategy: we keep the current modern MainWindow for now
 * and add this alternative window to verify backend wiring before removal.
 */
class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

protected:
    void closeEvent(QCloseEvent* event) override;

private slots:
    void createNewMedia();
    void editExistingMedia(unsigned int id);
    void createNewFile();
    void openExistingFile();
    void saveAll();
    void showInfo();
    void closeEditor();
    void addMediaCardSlot(const class Media& media);
    void showMediaDetails(unsigned int id);
    void deleteMedia(unsigned int id);

signals:
    void displayMediaDetails(const class Media& media);
    void deleteMediaCard(unsigned int id);
    void clearMediaList();

private:
    void setupToolBar();
    void setupCentralWidgets();
    void clearState();
    void applyFiltersAndSorting();
    void setupShortcuts();

    QToolBar* toolBar = nullptr;
    QToolButton* fileToolButton = nullptr;
    QAction* newMediaAct = nullptr;
    QAction* openFileAct = nullptr;
    QAction* saveAct = nullptr;
    QAction* infoAct = nullptr;
    QAction* newFileAct = nullptr;

    // Filter widgets
    class QComboBox* typeFilter = nullptr;
    class QCheckBox* availableOnlyCheck = nullptr;
    class QComboBox* sortCombo = nullptr;

    ItemEditWidget* editWidget = nullptr; // placeholder for editor integration
    ItemListWidget* listWidget = nullptr;     // left list
    ItemDetailWidget* detailWidget = nullptr; // right details
    QStackedLayout* rightStackedLayout = nullptr;

    std::unique_ptr<Library> library; // reuse backend
    bool unsavedChanges = false;
    QString currentPath;
    unsigned int currentSelectedId = 0; // for shortcut operations

    QAction* editAct = nullptr;
    QAction* deleteAct = nullptr;
    QAction* focusSearchAct = nullptr;
};

#endif // MAINWINDOW_H
