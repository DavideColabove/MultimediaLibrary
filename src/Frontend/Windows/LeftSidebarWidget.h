#pragma once
#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QListWidget>

class LeftSidebarWidget : public QWidget {
    Q_OBJECT
    
    public:
        explicit LeftSidebarWidget(QWidget* parent = nullptr);
        QString currentCategory() const;
    signals:
        void categoryChanged(const QString& category);
    private:
        QVBoxLayout* layout_{};
        QLabel* title_{};
        QListWidget* list_{};
        void setupUi();
        void setupConnections();
        void setupIcons();
};
