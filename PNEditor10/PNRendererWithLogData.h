#ifndef PNRENDERERWITHLOGDATA_H

///////////////////////////////////////////////////////////////////////////////
/// \file
/// \brief Contains PNRendererWithLogData implementation.
/// \author Oleg Bulanov
/// \version 0.1.0
/// \date 18.08.2014
///////////////////////////////////////////////////////////////////////////////

#define PNRENDERERWITHLOGDATA_H

#include "VTMinePetriNet.h"
#include "IVTMinePNRenderer.h"
#include "qrect.h"
#include "qmath.h"
#include "LogData.h"

/** \brief PetriNet renderer definition 1
*   
*  
*/
class PNRendererWithLogData : public IVTMinePNRenderer
{
public:

    /** \brief Position graphical representation.
    *   
    *  Position is represented as circle
    */
    class PositionGrItem : public IPositionGrItem
    {
    public:
        static const int posDefaultSize = 40; ///< Default diameter of circle

    public:
        /** \brief Constructs Position graphical representation with given data and coordinates */
        PositionGrItem(IPNBaseData::IPNBaseDataPtr data, QRectF& coord);

        /** \brief Destructor of the class */
        ~PositionGrItem() { }
    public:

        /** \brief Returns bounding rectangle */
        QRectF boundingRect() const;

        /** \brief Returns the shape of this item as a QPainterPath in local coordinates */
        QPainterPath shape() const;

        /** \brief Draws Position graphical representation */
        void paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*);

    public:
        /** \brief Sets coordinates of the PositionGrItem */
        void setCoord(QRectF& coord);

        /** \brief Sets data of the PositionGrItem */
        void setData(IPNBaseData::IPNBaseDataPtr data);


        /** \brief Returns data of PositionGrItem */
        const IPNBaseData::IPNBaseDataPtr& getData();

        /** \brief Returns coordinates of the PositionGrItem */
        QRectF getCoord();


        /** \brief Makes PositionGrItem selected */
        void selectItem();

        /** \brief Makes PositionGrItem not selected */
        void selectOutItem();

        /** \brief Returns center of the PositionGrItem */
        QPointF center();

    private:
        QRectF                      _rec;       ///< Bounding rectangle
        IPNBaseData::IPNBaseDataPtr _data;      ///< Data of Position
        qreal                       _posSize;   ///< Diameter of circle
        QPen                        _pen;       ///< Pen of PositionGrItem
        QBrush                      _brush;     ///< Brush of PositionGrItem

    }; // class PositionGrItem



    /** \brief Transition graphical representation.
    *   
    *  Transition is represented as rectangle with LogData
    */
    class TransitionGrItem : public ITransitionGrItem
    {
    public:
        static const int transDefaultWidth = 40;    ///< Default width of rectangle
        static const int transDefaultHeight = 40;   ///< Default height of rectangle
    public:
        /** \brief Constructs Transition graphical representation with given data and coordinates */
        TransitionGrItem(IPNBaseData::IPNBaseDataPtr data, QRectF& coord);

        /** \brief destructor of the class */
        ~TransitionGrItem() { };

    public:
        /** \brief Returns bounding rectangle */
        QRectF boundingRect() const;

        /** \brief Draws Transition graphical representation */
        void paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*);

    public:
        /** \brief Sets coordinates of the TransitionGrItem */
        void setCoord(QRectF& coord);

        /** \brief Sets data of the TransitionGrItem */
        void setData(IPNBaseData::IPNBaseDataPtr data);

        /** \brief Returns data of TransitionGrItem */
        const IPNBaseData::IPNBaseDataPtr& getData();

        /** \brief Returns coordinates of the TransitionGrItem */
        QRectF getCoord();


        /** \brief Makes TransitionGrItem selected */
        void selectItem();

        /** \brief Makes TransitionGrItem not selected */
        void selectOutItem();

        /** \brief Returns center of the TransitionGrItem */
        QPointF center();
    private:
        QRectF                      _rec;           ///< Bounding rectangle
        IPNBaseData::IPNBaseDataPtr _data;          ///< LogData of Transition
        qreal                       _transWidth;    ///< Width of TransitionGrItem
        qreal                       _transHeight;   ///< Height of TransitionGrItem
        QPen                        _pen;           ///< Pen of TransitionGrItem
        QBrush                      _brush;         ///< Brush of TransitionGrItem
    }; // class TransitionItem


    /** \brief Edge graphical representation.
    *   
    *  Edge is represented as arrow
    */
    class EdgeGrItem : public IEdgeGrItem
    {
    public:
        static const int pikeDefaultLength = 15;
        static const int pikeDefaultAngle = 15;
        static const int shapeDefaultEps = 5;
    public:
        /** \brief Constructs Edge with the given coordinates and data. Edge type is fromPointToPoint */
        EdgeGrItem(EdgeCoords coords, IPNBaseData::IPNBaseDataPtr data);

        /** \brief Constructs Edge from IPositionGrItem to ITransitionGrItem with the given data. Edge type is fromPosToTrans */
        EdgeGrItem(PositionGrItem* from, TransitionGrItem* to, IPNBaseData::IPNBaseDataPtr data);

        /** \brief Constructs Edge from ITransitionGrItem to IPositionGrItem with the given data. Edge type is fromTransToPos */
        EdgeGrItem(TransitionGrItem* from, PositionGrItem* to, IPNBaseData::IPNBaseDataPtr data);

        /** \brief Destructor of the class */
        ~EdgeGrItem() { }

    public:

        /** \brief Returns the shape of this item as a QPainterPath. See Qt documentation */
        QPainterPath shape() const;

    public:
        /** \brief Sets coords of the edge */
        void setCoords(EdgeCoords coords);

        /** \brief Sets IPositionGrItem of the edge. If Edge type is fromPointToPoint does nothing */
        void setPos(IPositionGrItem* pos);

        /** \brief Sets IPositionGrItem of the edge. If Edge type is fromPointToPoint does nothing */
        void setTrans(ITransitionGrItem* trans);

        /** \brief Sets Data of the edge */
        void setData(IPNBaseData::IPNBaseDataPtr data);

        /** \brief Sets direction (Dir) of the edge */
        void setDir(Dir dir);

        
        /** \brief Returns coordinates of the edge */
        EdgeCoords getCoords();

        /** \brief Returns data of the edge */
        IPNBaseData::IPNBaseDataPtr getData();

        /** \brief Returns IPositionGrItem of the edge */
        IPositionGrItem* getPos();

        /** \brief Returns ITransitionGrItem of the edge */
        ITransitionGrItem* getTrans();

        /** \brief Returns direction (Dir) of the edge */
        Dir getDir();

    public:
        /** \brief Updating graphical representation of the edge */
        void rearrange();

    protected:
        /** \brief Receives mouse press events */
        void mousePressEvent ( QGraphicsSceneMouseEvent * mouseEvent )
        {
            if(mouseEvent->button() == Qt::LeftButton)
                grabMouse();
        }

        /** \brief Receives mouse press events */
        void mouseMoveEvent ( QGraphicsSceneMouseEvent * event )
        {

            _coords.setMiddlePoint(event->scenePos());
            rearrange();

        }

        /** \brief Receives mouse press events */
        void mouseReleaseEvent ( QGraphicsSceneMouseEvent * mouseEvent )
        {
            ungrabMouse();
        }
    
    private:
        /** \brief Returns QPointF of contact edge with position */
        QPointF           posContact();
        
        /** \brief Returns QPointF of contact edge with transition */
        QPointF           transContact();

    private:
        EdgeCoords                  _coords;        ///< Coordinates of EdgeGrItem
        qreal                       _pikeLength;    ///< Length of pike
        qreal                       _pikeAngle;     ///< Angle of pike
        QPainterPath                _shape;         ///< Shape of EdgeGrItem
        qreal                       _shapeEps;      ///< Shape number of EdgeGrItem
        Dir                         _dir;           ///< Direction of the Edge
        IPNBaseData::IPNBaseDataPtr _data;          ///< Data of the Edge
        IPositionGrItem*            _pos;           ///< PositionGrItem of the EdgeGrItem
        ITransitionGrItem*          _trans;         ///< TransitionGrItem of the EdgeGrItem
        QPen                        _pen;           ///< Pen of EdgeGrItem
        QBrush                      _brush;         ///< Brush of EdgeGrItem
    }; // class EdgeItem

public:
    PNRendererWithLogData() { _id = "1"; _name = "RendererWithLogData"; }
    ~PNRendererWithLogData() { }
public:
    /** \brief Returns id of the Renderer */
    QString getId() { return _id; };

    /** \brief Returns name of the Renderer */
    QString getName() { return _name; };

    /** \brief Creates graphical representation of the given Position with (0,0) coordinates */
    QGraphicsItem* createPosGraphicsItem(PositionWithPtr* pos) const;

    /** \brief Creates graphical representation of the given Position with the given coordinates */
    QGraphicsItem* createPosGraphicsItem(PositionWithPtr* pos, QRectF coords) const;

    /** \brief Returns coordinates of the given graphical representstion of Position */
    QRectF makePosCoordsList(QGraphicsItem* gri) const ; 
    
    /** \brief Creates graphical representation of the given Transition with (0,0) coordinates */
    QGraphicsItem* createTransGraphicsItem(TransitionWithPtr* trans) const;

    /** \brief Creates graphical representation of the given Transition with the given coordinates */
    QGraphicsItem* createTransGraphicsItem(TransitionWithPtr* trans, QRectF coords) const;

    /** \brief Returns coordinates of the given graphical representstion of Transition */
    QRectF makeTransCoordsList(QGraphicsItem* gri) const; 
    
    /** \brief Creates graphical representation of the Edge with the given coordinates with the given data */
    QGraphicsItem* createEdgeGraphicsItem(EdgeCoords coords, IPNBaseData::IPNBaseDataPtr data);

    /** \brief Creates graphical representation of the given Edge */
    QGraphicsItem* createEdgeGraphicsItem(EdgeWithPtr* edge, QGraphicsItem* posGrItem, QGraphicsItem* transGrItem);

    /** \brief Creates graphical representation of the given Edge with the given coordinates */
    QGraphicsItem* createEdgeGraphicsItem(EdgeWithPtr* edge, QGraphicsItem* posGrItem, QGraphicsItem* transGrItem, EdgeCoords coords);

    /** \brief Returns coordinates of the given graphical representstion of Edge */
    EdgeCoords makeEdgeCoordsList(QGraphicsItem* gri) const;

private:
    QString _id;    ///< ID of the renderer
    QString _name;  ///< Name of the renderer

}; // class PNRendererWithLogData



#endif