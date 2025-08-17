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

/**
 * @brief Custom widget for displaying media items in a grid layout
 * 
 * This class represents a single media item card in the library grid view.
 * Each card displays the media's cover image, title, year, and type badge.
 * The card supports hover effects, click interactions, and responsive
 * design with fallback icons for missing cover images.
 * 
 * Features include:
 * - Cover image display with fallback to type-specific icons
 * - Hover effects with shadow and scaling
 * - Click handling for media selection
 * - Responsive layout that adapts to content
 * - Type badge indicating media category
 */
class MediaCard : public QFrame
{
    Q_OBJECT

public:
    /**
     * @brief Constructs a media card for the specified media item
     * @param media Pointer to the media item to display
     * @param parent Parent widget (optional)
     */
    MediaCard(Media* media, QWidget* parent = nullptr);
    
    /**
     * @brief Gets the media item associated with this card
     * @return Pointer to the media item
     */
    Media* getMedia() const { return media; }

signals:
    /**
     * @brief Signal emitted when the card is clicked
     * @param media Pointer to the media item that was clicked
     */
    void clicked(Media* media);

protected:
    /**
     * @brief Handles mouse press events for card interaction
     * @param event Mouse press event information
     */
    void mousePressEvent(QMouseEvent* event) override;
    
    /**
     * @brief Handles custom painting for visual effects
     * @param event Paint event information
     */
    void paintEvent(QPaintEvent* event) override;
    
    /**
     * @brief Handles mouse enter events for hover effects
     * @param event Mouse enter event information
     */
    void enterEvent(QEnterEvent* event) override;
    
    /**
     * @brief Handles mouse leave events for hover effects
     * @param event Mouse leave event information
     */
    void leaveEvent(QEvent* event) override;

private:
    Media* media;              // Associated media item
    QLabel* coverLabel;        // Label for cover image or icon
    QLabel* titleLabel;        // Label for media title
    QLabel* yearLabel;         // Label for release year
    QLabel* typeBadgeLabel;    // Label for media type badge
    QVBoxLayout* layout;       // Vertical layout for card content
    bool isHovered;            // Hover state flag
    
    /**
     * @brief Updates the cover image or fallback icon
     */
    void updateCover();
    
    /**
     * @brief Computes the media type string for display
     * @return String representation of the media type
     */
    QString computeType() const;
};

#endif // MEDIACARD_H
