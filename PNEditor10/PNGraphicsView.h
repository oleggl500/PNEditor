#ifndef PNGRAPHICSVIEW_H

///////////////////////////////////////////////////////////////////////////////
/// \file
/// \brief Contains implementation of PNGraphicsView.
/// \author Oleg Bulanov
/// \version 0.1.0
/// \date 14.08.2014
///////////////////////////////////////////////////////////////////////////////

#define PNGRAPHICSVIEW_H

#include <QtGUI>
#include <QGraphicsView>
#include "PNGraphicalLayout.h"

/** \brief Gives graphical representation of PNGraphicalLayout and contains event filters
* 
*
*
*/
class PNGraphicsView : public QGraphicsView
{
    Q_OBJECT

public:
    /** \brief Type definition for Position graphical representation */
    typedef IVTMinePNRenderer::IPositionGrItem PosGrItem;

    /** \brief Type definition for Transition graphical representation */
    typedef IVTMinePNRenderer::ITransitionGrItem TransGrItem;

    /** \brief Type definition for Edge graphical representation */
    typedef IVTMinePNRenderer::IEdgeGrItem EdgeGrItem;

    /** \brief Type definition for base Data */
    typedef IPNBaseData::IPNBaseDataPtr Data;
public:
    /** \brief Constructs PNGraphicsView with the given PNGraphicalLayout */
    PNGraphicsView(PNGraphicalLayout* layout, QWidget* parent = nullptr);

    /** \brief Destructor of the class */
    ~PNGraphicsView();

    /** \brief Sets PNGraphicalLayout of the PNGraphicsView */
    void setGrLayout(PNGraphicalLayout* layout);

    /** \brief Allows adding edges if tf equal true or forbids adding edges if tf equal false */
    void setAddingEdgesAllowed(bool tf);

    /** \brief Returns PNGraphicalLayout of the PNGraphicsView */
    PNGraphicalLayout* getGrLayout();

private:
    /** \brief Event filter of PNGraphicsView that calls other filters depending on mde of PNGraphicalLayout */
    bool eventFilter(QObject* watched, QEvent* event);

    /** \brief Move filter of PNGraphicsView */
    void moveFilter(QGraphicsSceneMouseEvent* mouseEvent, QEvent* event);

    /** \brief Edit filter of PNGraphicsView */
    void editFilter(QGraphicsSceneMouseEvent* mouseEvent, QEvent* event);
    
    /** \brief Selects the given item */
    void selectingItem(QGraphicsSceneMouseEvent* mouseEvent, QGraphicsItem* item);

private slots:
    /** \brief Remove selected item slot */
    void remove();
    
    /** \brief Rename selected item slot */
    void rename();

    /** \brief Bring to front slot */
    void increaseZValue();

    /** \brief Send to back slot */
    void decreaseZValue();


private:

    PNGraphicalLayout*   _grLayout;         ///< PNGraphicalLayout of the PNGraphicsView

    bool                 _allowAddingEdges; ///< Allow/fobid adding edges flag

    EdgeGrItem*          _curEdge;          ///< Current edge
    QGraphicsItem*       _from;             ///<

    QAction*             _removeAct;        ///< Remove action
    QAction*             _renameAct;        ///< Rename action
    QAction*             _increaseZValueAct;///< Bring to front action
    QAction*             _decreaseZValueAct;///< Send to back action
    QGraphicsItem*       _selectedItem;     ///< Selected item

    IVTMinePNRenderer::IVTMineEdgeRenderer* _edgeRenderer;  ///< Edge renderer


}; // class PNGraphicsView

#endif