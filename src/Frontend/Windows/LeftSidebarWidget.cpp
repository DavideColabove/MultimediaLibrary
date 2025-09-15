#include "LeftSidebarWidget.h"
#include <QFile>
#include <QIcon>

static QIcon loadIconByName(const QString& baseName) {
    const QString resPath = QString(":/icons/%1.svg").arg(baseName);
    if (QFile::exists(resPath)) return QIcon(resPath);
    return QIcon();
}

LeftSidebarWidget::LeftSidebarWidget(QWidget* parent) : QWidget(parent) {
    setObjectName("leftSidebar");
    setFixedWidth(200);
    setupUi();
    setupIcons();
    setupConnections();
}

void LeftSidebarWidget::setupUi() {
    layout_ = new QVBoxLayout(this);
    layout_->setSpacing(10);
    layout_->setContentsMargins(20,20,20,20);
    title_ = new QLabel("Media", this);
    title_->setObjectName("sidebarTitle");
    title_->setAlignment(Qt::AlignCenter);
    layout_->addWidget(title_);
    list_ = new QListWidget(this);
    list_->setObjectName("categoryList");
    list_->addItems({"All","Books","Movies","Songs","Magazines","Podcasts"});
    list_->setCurrentRow(0);
    layout_->addWidget(list_);
}

void LeftSidebarWidget::setupIcons() {
    const struct { int row; const char* iconBase; const char* tip; } catIcons[] = {
        {0, "all",       "All media"},
        {1, "book",      "Books"},
        {2, "movie",     "Movies"},
        {3, "music",     "Songs"},
        {4, "magazine",  "Magazines"},
        {5, "podcast",   "Podcasts"},
    };
    for (const auto& ci : catIcons) {
        if (QListWidgetItem* it = list_->item(ci.row)) {
            it->setIcon(loadIconByName(QString::fromUtf8(ci.iconBase)));
            it->setToolTip(QString::fromUtf8(ci.tip));
        }
    }
}

void LeftSidebarWidget::setupConnections() {
    QObject::connect(list_, &QListWidget::currentRowChanged, this, [this](int idx){
        if (auto* it = list_->item(idx)) emit categoryChanged(it->text());
    });
}

QString LeftSidebarWidget::currentCategory() const { return list_->currentItem() ? list_->currentItem()->text() : QString(); }
