#ifndef MEDIACARD_H
#define MEDIACARD_H

#include <QFrame>
#include <QLabel>
#include <QVBoxLayout>
#include <QMouseEvent>
#include <QPainter>
#include <QEnterEvent>
#include <QGraphicsDropShadowEffect>
#include "../../Backend/Elements/Media.h"


class MediaCard : public QFrame
{
    Q_OBJECT

public:
    
    MediaCard(Media* media, QWidget* parent = nullptr);
    
    
    Media* getMedia() const { return media; }

signals:
    
    void clicked(Media* media);

protected:
    
    void mousePressEvent(QMouseEvent* event) override;
    
    
    void paintEvent(QPaintEvent* event) override;
    
    
    void enterEvent(QEnterEvent* event) override;
    
    
    void leaveEvent(QEvent* event) override;

private:
    Media* media;              
    QLabel* coverLabel;        
    QLabel* titleLabel;        
    QLabel* yearLabel;         
    QLabel* typeBadgeLabel;    
    QVBoxLayout* layout;       
    bool isHovered;            
    
    
    void updateCover();
    
    
    QString computeType() const;
};

#endif 
