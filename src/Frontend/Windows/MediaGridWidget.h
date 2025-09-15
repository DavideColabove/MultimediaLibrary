#pragma once
#include <QWidget>
#include <QScrollArea>
#include <QVBoxLayout>
#include <vector>
#include "FlowLayout.h"
#include "MediaCard.h"
#include "../../Backend/Elements/Media.h"

class MediaGridWidget : public QWidget {
    Q_OBJECT
    
    public:
        explicit MediaGridWidget(QWidget* parent = nullptr);
        void setMedia(const std::vector<Media*>& items);
        void clear();
    signals:
        void mediaClicked(Media*);
    private:
        QVBoxLayout* layout_{};
        QScrollArea* area_{};
        QWidget* content_{};
        FlowLayout* flow_{};
};
