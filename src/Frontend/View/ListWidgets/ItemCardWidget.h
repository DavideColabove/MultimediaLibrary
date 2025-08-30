#ifndef VIEW_ITEMCARDWIDGET_H
#define VIEW_ITEMCARDWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>

class Media;

class ItemCardWidget : public QWidget {
    Q_OBJECT
public:
    explicit ItemCardWidget(const Media& media, QWidget* parent = nullptr);
    unsigned int mediaId() const;
    const Media& mediaRef() const { return media; }
signals:
    void clicked(unsigned int id);
protected:
    void mousePressEvent(QMouseEvent* event) override;
private:
    const Media& media;
    QLabel* titleLabel;
    QLabel* authorLabel;
    QLabel* iconLabel = nullptr;
};

#endif // VIEW_ITEMCARDWIDGET_H
