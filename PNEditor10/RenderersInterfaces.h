#ifndef RENDERSINTERFACES_H

///////////////////////////////////////////////////////////////////////////////
/// \file
/// \brief Contains interfaces of renderers
/// \author Oleg Bulanov
/// \version 0.1.0
/// \date 05.07.2014
///////////////////////////////////////////////////////////////////////////////

#define RENDERSINTERFACES_H

#include "PetriNet.h"
#include <QPainter>
#include <QDebug>
#include <QtGui>
#include <QtCore>
#include <QGraphicsItem>


/** \brief Interface of Position renderer.
*   
*  
*/
template<class TPosData, class TPosCoord>
class IPositionRenderer
{
public:
    /** \brief Virtual destructor of the class */
    virtual ~IPositionRenderer() { } 
public:
    /** \brief Creates graphical representation of the given Position with (0,0) coordinates */
    virtual QGraphicsItem* createPosGraphicsItem(xi::PetriNet::Position<TPosData>* pos) const = 0;

    /** \brief Creates graphical representation of the given Position with the given coordinates */
    virtual QGraphicsItem* createPosGraphicsItem(xi::PetriNet::Position<TPosData>* pos, TPosCoord coords) const = 0;

    /** \brief Returns coordinates of the given graphical representstion of Position */
    virtual TPosCoord makePosCoordsList(QGraphicsItem* gri) const = 0 ; 



}; //class IPositionRenderer


/** \brief Interface of Transition renderer.
*   
*  
*/
template<class TTransData, class TTransCoord>
class ITransitionRenderer
{
public:
    /** \brief Virtual destructor of the class */
    virtual ~ITransitionRenderer() { } 
public:
    /** \brief Creates graphical representation of the given Transition with (0,0) coordinates */
    virtual QGraphicsItem* createTransGraphicsItem(xi::PetriNet::Transition<TTransData>* trans) const = 0;

    /** \brief Creates graphical representation of the given Transition with the given coordinates */
    virtual QGraphicsItem* createTransGraphicsItem(xi::PetriNet::Transition<TTransData>* trans, TTransCoord coords) const = 0;

    /** \brief Returns coordinates of the given graphical representstion of Transition */
    virtual TTransCoord makeTransCoordsList(QGraphicsItem* gri) const = 0 ; 
}; // class ITransitionRenderer


/** \brief Interface of Edge renderer.
*   
*  
*/
template<class TPosData, class TTransData, class TEdgeData, class TEdgeCoord>
class IEdgeRenderer
{
public:
    virtual ~IEdgeRenderer() { }
public:
    /** \brief Creates graphical representation of the Edge with the given coordinates */
    virtual QGraphicsItem* createEdgeGraphicsItem(TEdgeCoord coords, TEdgeData data) = 0;

    /** \brief Creates graphical representation of the given Edge */
    virtual QGraphicsItem* createEdgeGraphicsItem(xi::PetriNet::Edge<TPosData, TTransData,TEdgeData>* edge, QGraphicsItem* posGrItem, QGraphicsItem* transGrItem) = 0;

    /** \brief Creates graphical representation of the given Edge with the given coordinates */
    virtual QGraphicsItem* createEdgeGraphicsItem(xi::PetriNet::Edge<TPosData, TTransData,TEdgeData>* edge, QGraphicsItem* posGrItem, QGraphicsItem* transGrItem, TEdgeCoord coords) = 0;

     /** \brief Returns coordinates of the given graphical representstion of Edge */
    virtual TEdgeCoord makeEdgeCoordsList(QGraphicsItem* gri) const = 0 ; 

}; // class IEdgeRenderer




///** \brief Interface of PetriNet renderer.
//*   
//*  Inherits IPositionRenderer, ITransitionRenderer, IEdgeRenderer
//*/
//template <class TPosData, class TPosCoord, class TTransData, class TTransCoord, class TEdgeData>
//class IPNRenderer
//    : public IPositionRenderer<TPosData, TPosCoord>,
//    public ITransitionRenderer<TTransData, TTransCoord>,
//    public IEdgeRenderer<TEdgeData>
//{
//    /** \brief Interface of Position graphical representation.
//    *   
//    *  
//    */
//    class IPositionGrItem : public QGraphicsItem
//    {
//    public:
//        /** \brief Type of IPositionGrItem */
//        enum { Type = QGraphicsItem::UserType + PosGrItemTypeConst } = 0;
//    public:
//        /** \brief Constructs Position graphical representation with given data and coordinates */
//        virtual IPositionGrItem(const TPosData& data, TPosCoord& coord) = 0;
//
//        /** \brief Virtual destructor of the class */
//        virtual ~IPositionGrItem() = 0;
//
//    public:
//        /** \brief Returns type of PositionGrItem */
//        int type() const { return Type; }
//
//        /** \brief Returns bounding rectangle */
//        virtual QRectF boundingRect() const = 0;
//
//        /** \brief Returns the shape of this item as a QPainterPath in local coordinates */
//        virtual QPainterPath shape() const = 0;
//
//        /** \brief Draws Position graphical representation */
//        virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*) = 0;
//
//    public:
//        /** \brief Sets coordinates of the PositionGrItem */
//        virtual void setCoord(TPosCoord& coord) = 0;
//
//        /** \brief Sets data of the PositionGrItem */
//        virtual void setData(const TPosData& text) = 0;
//
//
//        /** \brief Returns coordinates of the PositionGrItem */
//        virtual const TPosData& getData() = 0;
//
//        /** \brief Returns data of PositionGrItem */
//        virtual TPosCoord& getCoord() = 0;
//
//
//        /** \brief Makes PositionGrItem selected */
//        virtual void selectItem() = 0;
//
//        /** \brief Makes PositionGrItem not selected */
//        virtual void selectOutItem() = 0;
//    }; // class IPositionItem
//
//
//
//    /** \brief Interface of Transition graphical representation.
//    *   
//    *  
//    */
//    class ITransitionGrItem : public QGraphicsItem
//    {
//    public:
//        /** \brief Type of ITransitionGrItem */
//        enum { Type = QGraphicsItem::UserType + TransGrItemTypeConst };
//    public:
//        /** \brief Constructs Transition graphical representation with given data and coordinates */
//        virtual ITransitionGrItem(const TTransData& data, TTransCoord& coord) = 0;
//
//        /** \brief Virtual destructor of the class */
//        virtual ~ITransitionGrItem() = 0;
//
//    public:
//        /** \brief Returns type of TransitionGrItem */
//        int type() const { return Type; }
//
//        /** \brief Returns bounding rectangle */
//        virtual QRectF boundingRect() const = 0;
//
//        /** \brief Returns the shape of this item as a QPainterPath */
//        virtual QPainterPath shape() const = 0;
//
//        /** \brief Draws Transition graphical representation */
//        virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*) = 0;
//
//    public:
//        /** \brief Sets coordinates of the TransitionGrItem */
//        virtual void setCoord(TTransCoord& coord) = 0;
//
//        /** \brief Sets data of the TransitionGrItem */
//        virtual void setData(const TTransData& text) = 0;
//
//
//        /** \brief Returns coordinates of the TransitionGrItem */
//        virtual const TTransData& getData() = 0;
//
//        /** \brief Returns data of TransitionGrItem */
//        virtual TTransCoord& getCoord() = 0;
//
//
//        /** \brief Makes TransitionGrItem selected */
//        virtual void selectItem() = 0;
//
//        /** \brief Makes TransitionGrItem not selected */
//        virtual void selectOutItem() = 0;
//    }; // class TransitionItem
//
//
//    class IEdgeGrItem : public QGraphicsPathItem
//    {
//    public:
//        enum { Type = QGraphicsItem::UserType + EdgeGrItemTypeConst };
//        /** \brief Types of Edges */
//        enum Dir
//        {
//            fromPosToTrans,     ///< Edge from Position to Transition
//            fromTransToPos,     ///< Edge from Transition to Position
//            fromPointToPoint    ///< Edge from one point to another
//        }; // enum Dir
//    
//    public:
//        /** \brief Constructs Edge with the given points and data on the given scene. Edge type is fromPointToPoint */
//        virtual IEdgeGrItem(QPointF from, QPointF to, QGraphicsScene* scene, const TEdgeData& data = TEdgeData()) = 0;
//
//        /** \brief Constructs Edge from IPositionGrItem to ITransitionGrItem with the given data. Edge type is fromPosToTrans */
//        virtual IEdgeGrItem(IPositionGrItem*, ITransitionGrItem*, const TEdgeData& data = TEdgeData()) = 0;
//
//         /** \brief Constructs Edge from ITransitionGrItem to IPositionGrItem with the given data. Edge type is fromTransToPos */
//        virtual IEdgeGrItem(ITransitionGrItem*, IPositionGrItem*, const TEdgeData& data = TEdgeData()) = 0;
//
//        /** \brief Destructor of the class */
//        virtual ~IEdgeGrItem() = 0;
//    
//    public:
//        /** \brief Returns type of EdgeGrItem */
//        int type() const { return Type; }
//
//        /** \brief Returns the shape of this item as a QPainterPath. See Qt documentation */
//        virtual QPainterPath shape() const  = 0;
//
//    public:
//        /** \brief Sets begin point of the edge */
//        virtual void setFromPoint(QPointF& from) = 0;
//
//        /** \brief Sets end point of the edge */
//        virtual void setToPoint(QPointF& to) = 0;
//
//        /** \brief Sets IPositionGrItem of the edge. If Edge type is fromPointToPoint does nothing */
//        virtual void setPos(IPositionGrItem* pos) = 0;
//
//        /** \brief Sets IPositionGrItem of the edge. If Edge type is fromPointToPoint does nothing */
//        virtual void setTrans(ITransitionGrItem* trans) = 0;
//
//        /** \brief Sets Data of the edge */
//        virtual void setData(const TEdgeData& data) = 0;
//
//
//        /** \brief Returns begin point of the edge */
//        virtual const QPointF getFromPoint() = 0;
//
//        /** \brief Returns end point of the edge */
//        virtual const QPointF getToPoint() = 0;
//
//        /** \brief Returns data of the edge */
//        virtual const TEdgeData& getData() = 0;
//
//        /** \brief Returns IPositionGrItem of the edge */
//        virtual IPositionGrItem* getPos() = 0;
//
//        /** \brief Returns ITransitionGrItem of the edge */
//        virtual ITransitionGrItem* getTrans() = 0;
//
//    public:
//        /** \brief Updating graphical representation of the edge */
//        virtual void rearrange() = 0;
//    }; // class IEdgeGrItem
//}; // class IPNRender
//
#endif