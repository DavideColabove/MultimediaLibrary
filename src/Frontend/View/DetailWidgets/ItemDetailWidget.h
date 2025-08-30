#ifndef VIEW_ITEMDETAILWIDGET_H
#define VIEW_ITEMDETAILWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>

class Media;

class ItemDetailWidget : public QWidget {
    Q_OBJECT
public:
    explicit ItemDetailWidget(QWidget* parent=nullptr);
public slots:
    void displayMedia(const Media& media);
signals:
    void editRequested(unsigned int id);
    void deleteRequested(unsigned int id);
private:
    QLabel* titleLabel;
    QLabel* authorLabel;
    QLabel* dateLabel;
    QLabel* extraLabel;
    QLabel* imageLabel;
    QPushButton* editBtn;
    QPushButton* deleteBtn;
    unsigned int currentId = 0;
};

#endif // VIEW_ITEMDETAILWIDGET_H
