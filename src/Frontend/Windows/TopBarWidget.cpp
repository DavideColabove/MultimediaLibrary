#include "TopBarWidget.h"
#include <QFile>
#include <QIcon>

static QIcon loadIconByName(const QString& baseName) {
    const QString resPath = QString(":/icons/%1.svg").arg(baseName);
    if (QFile::exists(resPath)) return QIcon(resPath);
    return QIcon();
}

TopBarWidget::TopBarWidget(QWidget* parent) : QWidget(parent) {
    setObjectName("searchBar");
    setupUi();
    setupConnections();
}

void TopBarWidget::setupUi() {
    layout_ = new QHBoxLayout(this);
    layout_->setContentsMargins(20,10,20,10);
    search_ = new QLineEdit(this);
    search_->setObjectName("searchInput");
    search_->setPlaceholderText("Search...");
    search_->setMinimumHeight(35);
    layout_->addWidget(search_);
    advancedBtn_ = new QToolButton(this);
    advancedBtn_->setText("Advanced");
    setIcon(advancedBtn_, "filter-advanced");
    layout_->addWidget(advancedBtn_);
    clearBtn_ = new QToolButton(this);
    clearBtn_->setText("Clear");
    setIcon(clearBtn_, "filter-clear");
    layout_->addWidget(clearBtn_);
    sortCombo_ = new QComboBox(this);
    sortCombo_->addItems({"Title ▲","Title ▼","Date ▲","Date ▼"});
    sortCombo_->setFixedSize(100,35);
    layout_->addWidget(sortCombo_);
    addBtn_ = new QToolButton(this); addBtn_->setText("Add"); setIcon(addBtn_, "add"); layout_->addWidget(addBtn_);
    importBtn_ = new QToolButton(this); importBtn_->setText("Import"); setIcon(importBtn_, "import"); layout_->addWidget(importBtn_);
    exportBtn_ = new QToolButton(this); exportBtn_->setText("Export"); setIcon(exportBtn_, "export"); layout_->addWidget(exportBtn_);
    saveBtn_ = new QToolButton(this); saveBtn_->setText("Save"); setIcon(saveBtn_, "save"); layout_->addWidget(saveBtn_);
}

void TopBarWidget::setupConnections() {
    QObject::connect(search_, &QLineEdit::textChanged, this, &TopBarWidget::searchTextChanged);
    QObject::connect(advancedBtn_, &QToolButton::clicked, this, &TopBarWidget::advancedSearchRequested);
    QObject::connect(clearBtn_, &QToolButton::clicked, this, &TopBarWidget::clearFiltersRequested);
    QObject::connect(sortCombo_, qOverload<int>(&QComboBox::currentIndexChanged), this, &TopBarWidget::sortChanged);
    QObject::connect(addBtn_, &QToolButton::clicked, this, &TopBarWidget::addRequested);
    QObject::connect(importBtn_, &QToolButton::clicked, this, &TopBarWidget::importRequested);
    QObject::connect(exportBtn_, &QToolButton::clicked, this, &TopBarWidget::exportRequested);
    QObject::connect(saveBtn_, &QToolButton::clicked, this, &TopBarWidget::saveRequested);
}

void TopBarWidget::setIcon(QToolButton* b, const QString& name) {
    b->setIcon(loadIconByName(name));
    b->setIconSize(QSize(18,18));
}
