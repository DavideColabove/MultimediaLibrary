#include "FlowLayout.h"
#include <QStyle>
#include <QWidget>
#include <algorithm>

FlowLayout::FlowLayout(QWidget *parent, int margin, int hSpacing, int vSpacing)
    : QLayout(parent), m_hSpace(hSpacing), m_vSpace(vSpacing) {
    setContentsMargins(margin, margin, margin, margin);
}

FlowLayout::~FlowLayout() { qDeleteAll(itemList); }

void FlowLayout::addItem(QLayoutItem *item) { itemList.append(item); }
int FlowLayout::count() const { return itemList.size(); }
QLayoutItem *FlowLayout::itemAt(int index) const { return itemList.value(index); }
QLayoutItem *FlowLayout::takeAt(int index) { return index>=0 && index<itemList.size() ? itemList.takeAt(index) : nullptr; }
QSize FlowLayout::sizeHint() const { return minimumSize(); }
QSize FlowLayout::minimumSize() const {
    QSize size;
    for (QLayoutItem *item : itemList) size = size.expandedTo(item->minimumSize());
    int l=0,t=0,r=0,b=0;
    getContentsMargins(&l,&t,&r,&b);
    size += QSize(l + r, t + b);
    return size;
}

int FlowLayout::horizontalSpacing() const { return m_hSpace >= 0 ? m_hSpace : smartSpacing(QStyle::PM_LayoutHorizontalSpacing); }
int FlowLayout::verticalSpacing() const { return m_vSpace >= 0 ? m_vSpace : smartSpacing(QStyle::PM_LayoutVerticalSpacing); }

void FlowLayout::setGeometry(const QRect &rect) { QLayout::setGeometry(rect); doLayout(rect, false); }

int FlowLayout::heightForWidth(int width) const {
    
    QRect rect(0, 0, width, 0);
    return doLayout(rect, true);
}

int FlowLayout::doLayout(const QRect &rect, bool testOnly) const {
    int left, top, right, bottom;
    getContentsMargins(&left, &top, &right, &bottom);
    QRect effectiveRect = rect.adjusted(+left, +top, -right, -bottom);
    int x = effectiveRect.x();
    int y = effectiveRect.y();
    int lineHeight = 0;
    const int hSpace = horizontalSpacing() >= 0 ? horizontalSpacing() : 24;
    const int vSpace = verticalSpacing() >= 0 ? verticalSpacing() : 24;

    for (QLayoutItem *item : itemList) {
        int spaceX = hSpace;
        int spaceY = vSpace;
        int nextX = x + item->sizeHint().width() + spaceX;
        if (nextX - spaceX > effectiveRect.right() && lineHeight > 0) {
            x = effectiveRect.x();
            y += lineHeight + spaceY;
            nextX = x + item->sizeHint().width() + spaceX;
            lineHeight = 0;
        }
        if (!testOnly) item->setGeometry(QRect(QPoint(x, y), item->sizeHint()));
        x = nextX;
    lineHeight = std::max(lineHeight, item->sizeHint().height());
    }
    return y + lineHeight - rect.y() + bottom;
}

int FlowLayout::smartSpacing(QStyle::PixelMetric pm) const {
    QObject *parent = this->parent();
    if (!parent) return -1;
    if (parent->isWidgetType()) {
        QWidget *pw = static_cast<QWidget *>(parent);
        return pw->style()->pixelMetric(pm, nullptr, pw);
    }
    return -1;
}
