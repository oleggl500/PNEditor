#ifndef IVTMINEPNRENDERERER_H

///////////////////////////////////////////////////////////////////////////////
/// \file
/// \brief Contains PetriNet renderer interface that will be used in VTMine framework.
/// \author Oleg Bulanov
/// \version 0.1.0
/// \date 30.07.2014
///////////////////////////////////////////////////////////////////////////////

#define IVTMINEPNRENDERERER_H

#include "RenderersInterfaces.h"
#include "IPNBaseData.h"
#include "VTMinePetriNet.h"

/** \brief Class that stores edge coordinates 
*   
*  
*/
class EdgeCoords
{
public:
    /** \brief Default constructor */
    EdgeCoords()
    {
        _begin = QPointF(); _end = QPointF(); _middle = QPointF();
    }

    /** \brief Constructs EdgeCoords with given points */
    EdgeCoords(QPointF begin, QPointF end, QPointF middle)
    {
        _begin = begin; _end = end; _middle = middle;
    }
public:
    /** \brief Returns begin QPointF of EdgeCoords */
    QPointF getBeginPoint() { return _begin; }

    /** \brief Returns middle QPointF of EdgeCoords */
    QPointF getMiddlePoint() { return _middle; }

    /** \brief Returns end QPointF of EdgeCoords */
    QPointF getEndPoint() { return _end; }

    /** \brief Sets begin QPointF of EdgeCoords */
    void setBeginPoint (QPointF point) { _begin = point; }

    /** \brief Sets middle QPointF of EdgeCoords */
    void setMiddlePoint (QPointF point) { _middle = point; }

    /** \brief Sets end QPointF of EdgeCoords */
    void setEndPoint (QPointF point) { _end = point; }
    
private:
    QPointF _begin;     ///< Begin QPointF of EdgeCoords
    QPointF _middle;    ///< Middle QPointF of EdgeCoords 
    QPointF _end;       ///< End QPointF of EdgeCoords
};


/** \brief Special interface of PetriNet renderer that will be used in VTMine framework 
*   
*  
*/
class IVTMinePNRenderer
    : public IPositionRenderer<IPNBaseData::IPNBaseDataPtr, QRectF>,
    public ITransitionRenderer<IPNBaseData::IPNBaseDataPtr, QRectF>,
    public IEdgeRenderer<IPNBaseData::IPNBaseDataPtr, IPNBaseData::IPNBaseDataPtr, IPNBaseData::IPNBaseDataPtr, EdgeCoords>
{
public:
    /** \brief Type definition for special PositionRenderer interface that will be used in VTMine framework */
    typedef IPositionRenderer<IPNBaseData::IPNBaseDataPtr, QRectF> IVTMinePositionRenderer;

    /** \brief Type definition for special TransitionRenderer interface that will be used in VTMine framework */
    typedef ITransitionRenderer<IPNBaseData::IPNBaseDataPtr, QRectF> IVTMineTransitionRenderer;

    /** \brief Type definition for special EdgeRenderer interface that will be used in VTMine framework */
    typedef IEdgeRenderer<IPNBaseData::IPNBaseDataPtr, IPNBaseData::IPNBaseDataPtr, IPNBaseData::IPNBaseDataPtr, EdgeCoords> IVTMineEdgeRenderer;
    
public:
    /** \brief Interface of Position graphical representation.
    *   
    *  
    */
    class IPositionGrItem : public QGraphicsItem
    {
    public:
        static const int PosGrItemTypeConst = 5;  ///< Const to define Position graphical representation type

    public:
        /** \brief Type of IPositionGrItem */
        enum { Type = QGraphicsItem::UserType + PosGrItemTypeConst };

    public:
        /** \brief Virtual destructor of the class */
        virtual ~IPositionGrItem() { }

    public:
        /** \brief Returns type of PositionGrItem */
        int type() const { return Type; }

        /** \brief Returns bounding rectangle */
        virtual QRectF boundingRect() const = 0;

        /** \brief Returns the shape of this item as a QPainterPath in local coordinates */
        virtual QPainterPath shape() const = 0;

        /** \brief Draws Position graphical representation */
        virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*) = 0;

    public:
        /** \brief Sets coordinates of the PositionGrItem */
        virtual void setCoord(QRectF& coord) = 0;

        /** \brief Sets data of the PositionGrItem */
        virtual void setData(IPNBaseData::IPNBaseDataPtr data) = 0;


        /** \brief Returns coordinates of the PositionGrItem */
        virtual const IPNBaseData::IPNBaseDataPtr& getData() = 0;

        /** \brief Returns data of PositionGrItem */
        virtual QRectF getCoord() = 0;


        /** \brief Makes PositionGrItem selected */
        virtual void selectItem() = 0;

        /** \brief Makes PositionGrItem not selected */
        virtual void selectOutItem() = 0;

        /** \brief Returns center of the PositionGrItem */
        virtual QPointF center() = 0;
    }; // class IPositionItem



    /** \brief Interface of Transition graphical representation.
    *   
    *  
    */
    class ITransitionGrItem : public QGraphicsItem
    {
    public:
        static const int TransGrItemTypeConst = 6; ///< Const to define Transition graphical representation type

    public:
        /** \brief Type of ITransitionGrItem */
        enum { Type = QGraphicsItem::UserType + TransGrItemTypeConst };

    public:
        /** \brief Virtual destructor of the class */
        virtual ~ITransitionGrItem()  { }

    public:
        /** \brief Returns type of TransitionGrItem */
        int type() const { return Type; }

        /** \brief Returns bounding rectangle */
        virtual QRectF boundingRect() const = 0;

        /** \brief Draws Transition graphical representation */
        virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*) = 0;

    public:
        /** \brief Sets coordinates of the TransitionGrItem */
        virtual void setCoord(QRectF& coord) = 0;

        /** \brief Sets data of the TransitionGrItem */
        virtual void setData(IPNBaseData::IPNBaseDataPtr data) = 0;


        /** \brief Returns coordinates of the TransitionGrItem */
        virtual const IPNBaseData::IPNBaseDataPtr& getData() = 0;

        /** \brief Returns data of TransitionGrItem */
        virtual QRectF getCoord() = 0;


        /** \brief Makes TransitionGrItem selected */
        virtual void selectItem() = 0;

        /** \brief Makes TransitionGrItem not selected */
        virtual void selectOutItem() = 0;

        /** \brief Returns center of the TransitionGrItem */
        virtual QPointF center() = 0;
    }; // class TransitionItem

    /** \brief Interface of Transition graphical representation.
    *   
    *  
    */
    class IEdgeGrItem : public QGraphicsPathItem
    {
    public:
        static const int EdgeGrItemTypeConst = 4;  ///< Const to define Edge graphical representation type

    public:
        enum { Type = QGraphicsItem::UserType + EdgeGrItemTypeConst };
        /** \brief Types of Edges */
        enum Dir
        {
            fromPosToTrans,     ///< Edge from Position to Transition
            fromTransToPos,     ///< Edge from Transition to Position
            fromPointToPoint    ///< Edge from one point to another
        }; // enum Dir

    public:
        /** \brief Destructor of the class */
        virtual ~IEdgeGrItem() { }

    public:
        /** \brief Returns type of EdgeGrItem */
        int type() const { return Type; }

        /** \brief Returns the shape of this item as a QPainterPath. See Qt documentation */
        virtual QPainterPath shape() const  = 0;

    public:
        /** \brief Sets coordinates of the edge */
        virtual void setCoords(EdgeCoords coords) = 0;

        /** \brief Sets IPositionGrItem of the edge. If Edge type is fromPointToPoint does nothing */
        virtual void setPos(IPositionGrItem* pos) = 0;

        /** \brief Sets IPositionGrItem of the edge. If Edge type is fromPointToPoint does nothing */
        virtual void setTrans(ITransitionGrItem* trans) = 0;

        /** \brief Sets Data of the edge */
        virtual void setData(IPNBaseData::IPNBaseDataPtr data) = 0;

        /** \brief Sets direction (Dir) of the edge */
        virtual void setDir(Dir dir) = 0;


        
        /** \brief Returns coordinates of the edge */
        virtual EdgeCoords getCoords() = 0;

        /** \brief Returns data of the edge */
        virtual IPNBaseData::IPNBaseDataPtr getData() = 0;

        /** \brief Returns IPositionGrItem of the edge */
        virtual IPositionGrItem* getPos() = 0;

        /** \brief Returns ITransitionGrItem of the edge */
        virtual ITransitionGrItem* getTrans() = 0;

        /** \brief Returns direction (Dir) of the edge */
        virtual Dir getDir() = 0;

    public:
        /** \brief Updating graphical representation of the edge */
        virtual void rearrange() = 0;
    }; // class IEdgeGrItem

    public:
        virtual ~IVTMinePNRenderer() { }
    public:
        /** \brief Returns id of the Renderer */
        virtual QString getId() = 0;

        /** \brief Returns name of the Renderer */
        virtual QString getName() = 0;

        /** \brief Creates graphical representation of the given Position with (0,0) coordinates */
        virtual QGraphicsItem* createPosGraphicsItem(PositionWithPtr* pos) const = 0;

        /** \brief Creates graphical representation of the given Position with the given coordinates */
        virtual QGraphicsItem* createPosGraphicsItem(PositionWithPtr* pos, QRectF coords) const = 0;

        /** \brief Returns coordinates of the given graphical representstion of Position */
        virtual QRectF makePosCoordsList(QGraphicsItem* gri) const = 0; 

        /** \brief Creates graphical representation of the given Transition with (0,0) coordinates */
        virtual QGraphicsItem* createTransGraphicsItem(TransitionWithPtr* trans) const = 0;

        /** \brief Creates graphical representation of the given Transition with the given coordinates */
        virtual QGraphicsItem* createTransGraphicsItem(TransitionWithPtr* trans, QRectF coords) const = 0;

        /** \brief Returns coordinates of the given graphical representstion of Transition */
        virtual QRectF makeTransCoordsList(QGraphicsItem* gri) const = 0; 

        /** \brief Creates graphical representation of the Edge with the given coordinates with the given data */
        virtual QGraphicsItem* createEdgeGraphicsItem(EdgeCoords coords, IPNBaseData::IPNBaseDataPtr data) = 0;

        /** \brief Creates graphical representation of the given Edge */
        virtual QGraphicsItem* createEdgeGraphicsItem(EdgeWithPtr* edge, QGraphicsItem* posGrItem, QGraphicsItem* transGrItem) = 0;

        /** \brief Creates graphical representation of the given Edge with the given coordinates */
        virtual QGraphicsItem* createEdgeGraphicsItem(EdgeWithPtr* edge, QGraphicsItem* posGrItem, QGraphicsItem* transGrItem, EdgeCoords coords) = 0;


        /** \brief Returns coordinates of the given graphical representstion of Edge */
        virtual EdgeCoords makeEdgeCoordsList(QGraphicsItem* gri) const = 0; 


}; // class IVTMinePNRenderer





#endif