#include "MediaGridWidget.h"

MediaGridWidget::MediaGridWidget(QWidget* parent) : QWidget(parent) {
    layout_ = new QVBoxLayout(this);
    layout_->setContentsMargins(0,0,0,0);
    area_ = new QScrollArea(this);
    area_->setWidgetResizable(true);
    area_->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    area_->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    content_ = new QWidget(area_);
    content_->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    flow_ = new FlowLayout(content_, 20, 24, 24);
    content_->setLayout(flow_);
    area_->setWidget(content_);
    layout_->addWidget(area_);
}

void MediaGridWidget::clear() {
    while (flow_->count() > 0) {
        if (auto* it = flow_->takeAt(0)) {
            if (auto* w = it->widget()) w->deleteLater();
            delete it;
        }
    }
}

void MediaGridWidget::setMedia(const std::vector<Media*>& items) {
    clear();
    for (auto* m : items) {
        auto* card = new MediaCard(m, content_);
        QObject::connect(card, &MediaCard::clicked, this, &MediaGridWidget::mediaClicked);
        flow_->addWidget(card);
    }
    content_->updateGeometry();
}
