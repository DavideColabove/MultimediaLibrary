#pragma once
#include <QLayout>
#include <QRect>
#include <QWidgetItem>
#include <QStyle>
#include <QList>

class FlowLayout : public QLayout {
    public:
        explicit FlowLayout(QWidget *parent = nullptr, int margin = -1, int hSpacing = -1, int vSpacing = -1);
        ~FlowLayout();
        void addItem(QLayoutItem *item) override;
        int count() const override;
        QLayoutItem *itemAt(int index) const override;
        QLayoutItem *takeAt(int index) override;
        QSize sizeHint() const override;
        QSize minimumSize() const override;
        bool hasHeightForWidth() const override { return true; }
        int heightForWidth(int width) const override;
        void setGeometry(const QRect &rect) override;
        int horizontalSpacing() const;
        int verticalSpacing() const;
    private:
        int doLayout(const QRect &rect, bool testOnly) const;
        int smartSpacing(QStyle::PixelMetric pm) const;
        QList<QLayoutItem *> itemList;
        int m_hSpace;
        int m_vSpace;
};
