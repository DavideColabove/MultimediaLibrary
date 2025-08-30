#include "ItemListWidget.h"
#include "ItemCardWidget.h"
#include <QListWidgetItem>
#include "../../../Backend/Elements/Media.h"

ItemListWidget::ItemListWidget(QWidget* parent) : QWidget(parent) {
    QVBoxLayout* lay = new QVBoxLayout(this);
    searchField = new QLineEdit(this);
    searchField->setPlaceholderText("Search title/author");
    searchField->setStyleSheet("QLineEdit{color:#eee;} QLineEdit:placeholder{color:#bbb;}");
    list = new QListWidget(this);
    lay->addWidget(searchField);
    lay->addWidget(list);
    connect(searchField, &QLineEdit::textChanged, this, &ItemListWidget::filterChanged);
}

void ItemListWidget::addMediaCard(const Media& media) {
    auto* item = new QListWidgetItem(list);
    auto* card = new ItemCardWidget(media, list);
    item->setSizeHint(card->sizeHint());
    list->addItem(item);
    list->setItemWidget(item, card);
    idToItem[media.getID()] = item;
    connect(card, &ItemCardWidget::clicked, this, &ItemListWidget::mediaSelected);
}

void ItemListWidget::rebuild(const std::vector<const Media*>& items) {
    clearAll();
    for(const Media* m : items) if(m) addMediaCard(*m);
    if(!searchField->text().isEmpty()) filterChanged(searchField->text());
}

void ItemListWidget::deleteCard(unsigned int id) {
    auto it = idToItem.find(id);
    if (it!=idToItem.end()) {
        int row = list->row(it->second);
        delete list->takeItem(row);
        idToItem.erase(it);
    }
}

void ItemListWidget::clearAll() {
    list->clear();
    idToItem.clear();
}

void ItemListWidget::filterChanged(const QString& txt) {
    for (int i=0;i<list->count();++i) {
        QListWidgetItem* it = list->item(i);
        QWidget* w = list->itemWidget(it);
        auto* card = qobject_cast<ItemCardWidget*>(w);
        if (!card) continue;
        bool match = QString::fromStdString(card->mediaRef().getTitle()).contains(txt, Qt::CaseInsensitive) ||
                     QString::fromStdString(card->mediaRef().getAuthor()).contains(txt, Qt::CaseInsensitive);
        it->setHidden(!match);
    }
}
