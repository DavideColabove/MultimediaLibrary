#pragma once
#include <QWidget>
#include <QLineEdit>
#include <QToolButton>
#include <QComboBox>
#include <QHBoxLayout>

class TopBarWidget : public QWidget {
    Q_OBJECT
    
    public:
        explicit TopBarWidget(QWidget* parent = nullptr);
        QLineEdit* searchField() const { return search_; }
    signals:
        void searchTextChanged(const QString&);
        void advancedSearchRequested();
        void clearFiltersRequested();
        void sortChanged(int);
        void addRequested();
        void importRequested();
        void exportRequested();
        void saveRequested();
    private:
        QHBoxLayout* layout_{};
        QLineEdit* search_{};
        QToolButton* advancedBtn_{};
        QToolButton* clearBtn_{};
        QComboBox* sortCombo_{};
        QToolButton* addBtn_{};
        QToolButton* importBtn_{};
        QToolButton* exportBtn_{};
        QToolButton* saveBtn_{};
        void setupUi();
        void setupConnections();
        void setIcon(QToolButton* b, const QString& name);
};
