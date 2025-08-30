#ifndef VIEW_ITEMLISTWIDGET_H
#define VIEW_ITEMLISTWIDGET_H

#include <QWidget>
#include <QListWidget>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QVector>
#include <map>

class Media;
class ItemCardWidget;

class ItemListWidget : public QWidget {
    Q_OBJECT
public:
    explicit ItemListWidget(QWidget* parent = nullptr);
    void addMediaCard(const Media& media);
    void rebuild(const std::vector<const Media*>& items); // rebuild list from scratch
    QString currentSearchText() const { return searchField->text(); }
    void applySearchText(const QString& txt) { searchField->setText(txt); filterChanged(txt); }
public slots:
    void deleteCard(unsigned int id);
    void clearAll();
    void filterChanged(const QString& text);
signals:
    void mediaSelected(unsigned int id);
private:
    QLineEdit* searchField;
    QListWidget* list;
    std::map<unsigned int, QListWidgetItem*> idToItem;
};

#endif // VIEW_ITEMLISTWIDGET_H
