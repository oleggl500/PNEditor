#include "PNRendererWithLogData.h"



//=============================================================================
//class PositionGrItem
//=============================================================================

//-----------------------------------------------------------------------------
// Constructs Position graphical representation with given data and coordinates
//-----------------------------------------------------------------------------
PNRendererWithLogData::PositionGrItem::PositionGrItem(IPNBaseData::IPNBaseDataPtr data, QRectF& coord)
{
    _posSize = posDefaultSize;
    _pen.setColor(Qt::black);
    _brush.setColor(Qt::white);
    _brush.setStyle(Qt::SolidPattern);
    _data = data;
    _rec = QRectF(coord.x(), coord.y(), _posSize, _posSize);
    setFlag(QGraphicsItem::ItemIsMovable);
    //setFlag(QGraphicsItem::ItemIsSelectable);
}

//-----------------------------------------------------------------------------
// Returns bounding rectangle
//-----------------------------------------------------------------------------
QRectF PNRendererWithLogData::PositionGrItem::boundingRect() const
{
    return _rec;
}

//-----------------------------------------------------------------------------
// Returns the shape of this item as a QPainterPath in local coordinates
//-----------------------------------------------------------------------------
QPainterPath PNRendererWithLogData::PositionGrItem::shape() const
{
    QPainterPath path;
    path.addEllipse(boundingRect());
    return path;
}

//-----------------------------------------------------------------------------
// Draws Position graphical representation
//-----------------------------------------------------------------------------
void PNRendererWithLogData::PositionGrItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* op, QWidget* wg)
{
    painter->setOpacity(1);
    painter->setPen(_pen);
    painter->setBrush(_brush);
    painter->drawEllipse(_rec);
    painter->drawText(_rec,Qt::AlignCenter,_data->getName());
}

//-----------------------------------------------------------------------------
// Sets coordinates of the PositionGrItem
//-----------------------------------------------------------------------------
void PNRendererWithLogData::PositionGrItem::setCoord(QRectF& coord)
{
    _rec = QRectF(coord.x(), coord.y(), _posSize, _posSize);
}

//-----------------------------------------------------------------------------
// Sets data of the PositionGrItem
//-----------------------------------------------------------------------------
void PNRendererWithLogData::PositionGrItem::setData(IPNBaseData::IPNBaseDataPtr data)
{
    _data = data;
}

//-----------------------------------------------------------------------------
// Returns data of PositionGrItem
//-----------------------------------------------------------------------------
const IPNBaseData::IPNBaseDataPtr& PNRendererWithLogData::PositionGrItem::getData()
{
    return _data;
}

//-----------------------------------------------------------------------------
// Returns coordinates of the PositionGrItem
//-----------------------------------------------------------------------------
QRectF PNRendererWithLogData::PositionGrItem::getCoord()
{
    auto topLeft = _rec.topLeft() + scenePos();
    return QRectF(topLeft.x(),topLeft.y(),_rec.width(), _rec.height());
}

//-----------------------------------------------------------------------------
// Makes PositionGrItem selected
//-----------------------------------------------------------------------------
void PNRendererWithLogData::PositionGrItem::selectItem ()
{
    _brush.setColor(Qt::blue);
    update();
}

//-----------------------------------------------------------------------------
// Makes PositionGrItem not selected
//-----------------------------------------------------------------------------
void PNRendererWithLogData::PositionGrItem::selectOutItem ()
{
    _brush.setColor(Qt::white);
    update();
}

//-----------------------------------------------------------------------------
// Returns center of the PositionGrItem
//-----------------------------------------------------------------------------
QPointF PNRendererWithLogData::PositionGrItem::center()
{
    return _rec.center() + scenePos();
}



//=============================================================================
//класс TransitionGrItem
//=============================================================================

//-----------------------------------------------------------------------------
//Constructs Transition graphical representation with given data and coordinates
//-----------------------------------------------------------------------------
PNRendererWithLogData::TransitionGrItem::TransitionGrItem(IPNBaseData::IPNBaseDataPtr data, QRectF& coord)
{
    _transWidth = transDefaultWidth;
    _transHeight = transDefaultHeight;
    _pen.setColor(Qt::black);
    _brush.setColor(Qt::white);
    _brush.setStyle(Qt::SolidPattern);
    _data = data;
    _rec = QRectF(coord.x(), coord.y(), _transWidth, _transHeight);
    std::shared_ptr<LogData> logData = std::dynamic_pointer_cast<LogData>(_data);
    if(logData == NULL)
    {
        QString data1 = "\nName: " + _data->getName() + "\n";
        auto rec = _rec;
        rec = QFontMetrics(QFont()).boundingRect(_rec.toRect(), Qt::AlignCenter, data1);
        _transHeight = rec.height();
        _transWidth = rec.width();
    }
    else
    {
        QString data1 = "\nName: " +  logData->getName() + "\n";
        data1 += "Timestamp: " + logData->getTimestamp().toString() + "\n";
        data1 += "Resource: " + logData->getResource() + "\n";
        auto rec = QFontMetrics(QFont()).boundingRect(_rec.toRect(), Qt::AlignCenter, data1);
        _transHeight = rec.height();
        _transWidth = rec.width();
    }
    _rec = QRectF(coord.x(), coord.y(), _transWidth, _transHeight);
    //delete painter;
    setFlag(QGraphicsItem::ItemIsMovable);
    //setFlag(QGraphicsItem::ItemIsFocusable);
}

//-----------------------------------------------------------------------------
// Returns bounding rectangle
//-----------------------------------------------------------------------------

QRectF PNRendererWithLogData::TransitionGrItem::boundingRect() const
{
    return _rec;
}

//-----------------------------------------------------------------------------
// Draws Transition graphical representation
//-----------------------------------------------------------------------------
void PNRendererWithLogData::TransitionGrItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* op, QWidget* wg)
{
    painter->setOpacity(1);
    painter->setPen(_pen);
    painter->setBrush(_brush);
    
    std::shared_ptr<LogData> logData = std::dynamic_pointer_cast<LogData>(_data);
    if(logData == NULL)
    {
        QString data = "\nName: " + _data->getName() + "\n";
        auto rec = _rec;
        _transHeight = rec.height();
        _transWidth = rec.width();
        _rec = QRectF(_rec.x(), _rec.y(), _transWidth, _transHeight);
        painter->drawRect(_rec);
        painter->drawText(_rec,Qt::AlignCenter, data);
    }
    else
    {
        QString data = "\nName: " +  logData->getName() + "\n";
        data += "Timestamp: " + logData->getTimestamp().toString() + "\n";
        data += "Resource: " + logData->getResource() + "\n";
        auto rec = painter->boundingRect(_rec, Qt::AlignCenter, data);
        _transHeight = rec.height();
        _transWidth = rec.width();
        _rec = QRectF(_rec.x(), _rec.y(), _transWidth, _transHeight);
        painter->drawRect(_rec);
        painter->drawText(_rec,Qt::AlignCenter,data);
    }
}

//-----------------------------------------------------------------------------
// Sets coordinates of the TransitionGrItem
//-----------------------------------------------------------------------------
void PNRendererWithLogData::TransitionGrItem::setCoord(QRectF& coord)
{
    _rec = QRectF(coord.x(), coord.y(), _transWidth, _transHeight);
}

//-----------------------------------------------------------------------------
// Sets data of the TransitionGrItem
//-----------------------------------------------------------------------------
void PNRendererWithLogData::TransitionGrItem::setData(IPNBaseData::IPNBaseDataPtr data)
{
    _data = data;
}

//-----------------------------------------------------------------------------
// Returns data of TransitionGrItem
//-----------------------------------------------------------------------------
const IPNBaseData::IPNBaseDataPtr& PNRendererWithLogData::TransitionGrItem::getData()
{
    return _data;
}

//-----------------------------------------------------------------------------
// Returns coordinates of the PositionGrItem
//-----------------------------------------------------------------------------
QRectF PNRendererWithLogData::TransitionGrItem::getCoord()
{
    auto topLeft = _rec.topLeft() + scenePos();
    return QRectF(topLeft.x(),topLeft.y(),_rec.width(), _rec.height());
}

//-----------------------------------------------------------------------------
// Makes TransitionGrItem selected
//-----------------------------------------------------------------------------
void PNRendererWithLogData::TransitionGrItem::selectItem ()
{
    _brush.setColor(Qt::blue);
    update();
}

//-----------------------------------------------------------------------------
// Makes TransitionGrItem not selected
//-----------------------------------------------------------------------------
void PNRendererWithLogData::TransitionGrItem::selectOutItem ()
{
    _brush.setColor(Qt::white);
    update();
}

//-----------------------------------------------------------------------------
// Returns center of the TransitionGrItem
//-----------------------------------------------------------------------------
QPointF PNRendererWithLogData::TransitionGrItem::center()
{
    return _rec.center() + scenePos();
}


//=============================================================================
//класс EdgeGrItem
//=============================================================================

//-----------------------------------------------------------------------------
// Constructs Edge with the given coordinates and data. 
// Edge type is fromPointToPoint
//-----------------------------------------------------------------------------
PNRendererWithLogData::EdgeGrItem::EdgeGrItem(EdgeCoords coords, IPNBaseData::IPNBaseDataPtr data)
{
    _pikeLength = pikeDefaultLength;
    _pikeAngle = pikeDefaultAngle;
    _shapeEps = shapeDefaultEps;
    _shape = QPainterPath();
    _pen = QPen(Qt::black);
    _brush = QBrush(Qt::black,Qt::SolidPattern);
    setPen(_pen);
    setBrush(_brush);
    _data = data;
    _coords = coords;
    _dir = fromPointToPoint;
}

//-----------------------------------------------------------------------------
// Constructs Edge from IPositionGrItem to ITransitionGrItem with the given data. 
// Edge type is fromPosToTrans
//-----------------------------------------------------------------------------
PNRendererWithLogData::EdgeGrItem::EdgeGrItem(PositionGrItem* pos, TransitionGrItem* trans, IPNBaseData::IPNBaseDataPtr data)
{
    _pikeLength = pikeDefaultLength;
    _pikeAngle = pikeDefaultAngle;
    _shapeEps = shapeDefaultEps;
    _shape = QPainterPath();
    _pen = QPen(Qt::black);
    _brush = QBrush(Qt::black,Qt::SolidPattern);
    setPen(_pen);
    setBrush(_brush);
    _data = data;
    _dir = fromPosToTrans;
    _pos = pos;
    _trans = trans;
    auto fromP = _pos->center() + _pos->scenePos();
    auto toP = _trans->center() + trans->scenePos();
    auto midP = (fromP + toP)/2;
    _coords = EdgeCoords(fromP, toP, midP);

}

//-----------------------------------------------------------------------------
// Constructs Edge from ITransitionGrItem to IPositionGrItem with the given data.
// Edge type is fromTransToPos
//-----------------------------------------------------------------------------
PNRendererWithLogData::EdgeGrItem::EdgeGrItem(TransitionGrItem* trans, PositionGrItem* pos, IPNBaseData::IPNBaseDataPtr data)
{
    _pikeLength = pikeDefaultLength;
    _pikeAngle = pikeDefaultAngle;
    _shapeEps = shapeDefaultEps;
    _shape = QPainterPath();
    _pen = QPen(Qt::black);
    _brush = QBrush(Qt::black,Qt::SolidPattern);
    setPen(_pen);
    setBrush(_brush);
    _data = data;
    _dir = fromTransToPos;
    _pos = pos;
    _trans = trans;
    auto fromP = _trans->center() + _trans->scenePos();
    auto toP = _pos->center() + _pos->scenePos();
    auto midP = (fromP + toP)/2;
    _coords = EdgeCoords(fromP, toP, midP);
}

//-----------------------------------------------------------------------------
//Returns the shape of this item as a QPainterPath. See Qt documentation
//-----------------------------------------------------------------------------
QPainterPath PNRendererWithLogData::EdgeGrItem::shape() const
{
    return _shape;
}

//-----------------------------------------------------------------------------
// Sets coords of the edge
//-----------------------------------------------------------------------------
void PNRendererWithLogData::EdgeGrItem::setCoords(EdgeCoords coords)
{
    _coords = coords;
}

//-----------------------------------------------------------------------------
// Sets IPositionGrItem of the edge. If Edge type is fromPointToPoint does nothing
//-----------------------------------------------------------------------------
void PNRendererWithLogData::EdgeGrItem::setPos(IPositionGrItem* pos)
{
    if(_dir != fromPointToPoint)
        _pos = pos;
}

//-----------------------------------------------------------------------------
// Sets ITransitionGrItem of the edge. If Edge type is fromPointToPoint does nothing
//-----------------------------------------------------------------------------
void PNRendererWithLogData::EdgeGrItem::setTrans(ITransitionGrItem* trans)
{
    if(_dir != fromPointToPoint)
        _trans = trans;
}

//-----------------------------------------------------------------------------
// Sets Data of the edge
//-----------------------------------------------------------------------------
void PNRendererWithLogData::EdgeGrItem::setData(IPNBaseData::IPNBaseDataPtr data)
{
    _data = data;
}

//-----------------------------------------------------------------------------
// Sets direction (Dir) of the edge
//-----------------------------------------------------------------------------
void PNRendererWithLogData::EdgeGrItem::setDir(Dir dir)
{
    _dir = dir;
}

//-----------------------------------------------------------------------------
// Returns coordinates of the edge
//-----------------------------------------------------------------------------
EdgeCoords PNRendererWithLogData::EdgeGrItem::getCoords()
{
    return _coords;
}

//-----------------------------------------------------------------------------
// Returns data of the edge
//-----------------------------------------------------------------------------
IPNBaseData::IPNBaseDataPtr PNRendererWithLogData::EdgeGrItem::getData()
{
    return _data;
}

//-----------------------------------------------------------------------------
// Returns IPositionGrItem of the edge
//-----------------------------------------------------------------------------
IVTMinePNRenderer::IPositionGrItem* PNRendererWithLogData::EdgeGrItem::getPos()
{
    return _pos;
}

//-----------------------------------------------------------------------------
// Returns ITransitionGrItem of the edge
//-----------------------------------------------------------------------------
IVTMinePNRenderer::ITransitionGrItem* PNRendererWithLogData::EdgeGrItem::getTrans()
{
    return _trans;
}

//-----------------------------------------------------------------------------
// Returns direction (Dir) of the edge
//-----------------------------------------------------------------------------
IVTMinePNRenderer::IEdgeGrItem::Dir PNRendererWithLogData::EdgeGrItem::getDir()
{
    return _dir;
}

//-----------------------------------------------------------------------------
// Updating graphical representation of the edge
//-----------------------------------------------------------------------------
void PNRendererWithLogData::EdgeGrItem::rearrange()
{
    if (_dir == fromPosToTrans)
    {
        QPointF begPoint = posContact();
        QPointF endPoint = transContact();
        //QPointF midPoint = (begPoint + endPoint)/2; 
        _coords.setBeginPoint(begPoint);
        _coords.setEndPoint(endPoint);
        //_coords.setMiddlePoint(midPoint);
    }
    if (_dir == fromTransToPos)
    {
        QPointF begPoint = transContact();
        QPointF endPoint = posContact();
        //QPointF midPoint = (begPoint + endPoint)/2; 
        _coords.setBeginPoint(begPoint);
        _coords.setEndPoint(endPoint);
        //_coords.setMiddlePoint(midPoint);
    }

    // состовляем конец стрелки
    QLineF l(_coords.getEndPoint(), _coords.getMiddlePoint());
    l.setAngle(l.angle() - _pikeAngle);
    l.setLength(_pikeLength);
    QLineF l2(_coords.getEndPoint(), _coords.getMiddlePoint());
    l2.setAngle(l2.angle() + _pikeAngle);
    l2.setLength(_pikeLength);
    QPolygonF pike;
    pike  << _coords.getEndPoint() << l.p2() << l2.p2() << _coords.getEndPoint();

    // рисуем ребро
    QPainterPath edgePath;
    edgePath.moveTo(_coords.getBeginPoint());
    //edgePath.lineTo(_trans->scenePos() + _trans->getCoord().topLeft());
    edgePath.quadTo(_coords.getMiddlePoint(), _coords.getEndPoint());
    edgePath.addPolygon(pike);
    edgePath.quadTo(_coords.getMiddlePoint(), _coords.getBeginPoint());
    setPath(edgePath);

    // создаём shape
    const double eps = 5;
    if(abs(_coords.getBeginPoint().x() - _coords.getEndPoint().x()) < eps && _coords.getBeginPoint().y() != _coords.getEndPoint().y())
    {
        QPointF begR = _coords.getBeginPoint() + QPointF(_shapeEps, 0);
        QPointF begL = _coords.getBeginPoint() - QPointF(_shapeEps, 0);
        QPointF midR = _coords.getMiddlePoint() + QPointF(_shapeEps, 0);
        QPointF midL = _coords.getMiddlePoint() - QPointF(_shapeEps, 0);
        QPointF endR = _coords.getEndPoint() + QPointF(_shapeEps, 0);
        QPointF endL = _coords.getEndPoint() - QPointF(_shapeEps, 0);
        _shape.moveTo(begR);
        _shape.quadTo(midR, endR);
        _shape.lineTo(endL);
        _shape.quadTo(midL, begL);
        _shape.lineTo(begR);
    }
    else
    {
        QPointF begU = _coords.getBeginPoint() + QPointF(0, _shapeEps);
        QPointF begD = _coords.getBeginPoint() - QPointF(0, _shapeEps);
        QPointF midU = _coords.getMiddlePoint() + QPointF(0, _shapeEps);
        QPointF midD = _coords.getMiddlePoint() - QPointF(0, _shapeEps);
        QPointF endU = _coords.getEndPoint() + QPointF(0, _shapeEps);
        QPointF endD = _coords.getEndPoint() - QPointF(0, _shapeEps);
        _shape.moveTo(begU);
        _shape.quadTo(midU, endU);
        _shape.lineTo(endD);
        _shape.quadTo(midD, begD);
        _shape.lineTo(begU);
    }

}




QPointF PNRendererWithLogData::EdgeGrItem::posContact()
{
    if(_dir == fromPointToPoint)
        return QPointF();
    QPointF posCenter;
    QPointF transCenter;
    posCenter = _pos->center();// +  _pos->scenePos();
    transCenter = _coords.getMiddlePoint();//_trans->scenePos() + _trans->center();//
    qreal r = PositionGrItem::posDefaultSize/2;
    QPointF posContact = posCenter;
    QLineF edge(posCenter, transCenter);//posCenter);
    qreal Pi = qAcos(0)*2;
    qreal angle = edge.angle()*Pi/180;
    posContact += QPointF(r*qCos(angle), -r*qSin(angle));
    return posContact; //+ _pos->scenePos();
}

QPointF PNRendererWithLogData::EdgeGrItem::transContact()
{
    if(_dir == fromPointToPoint)
        return QPointF();
    QPointF posCenter;
    QPointF transCenter;
    //if(_dir == fromPosToTrans)
    posCenter =   _coords.getMiddlePoint();//  _pos->center() + _pos->scenePos();//
    transCenter =  _trans->center();// + _trans->scenePos();
    
    QPointF transTopLeft = _trans->boundingRect().topLeft() + _trans->scenePos();
    QPointF transBottomLeft = _trans->boundingRect().bottomLeft() + _trans->scenePos();
    QPointF transTopRight = _trans->boundingRect().topRight() + _trans->scenePos();
    QPointF transBottomRight = _trans->boundingRect().bottomRight() + _trans->scenePos();
    
    QPointF posTopLeft = _pos->boundingRect().topLeft() + _pos->scenePos();
    QPointF posBottomRight = _pos->boundingRect().bottomRight() + _pos->scenePos();
    
    QRectF scenePosRec(posTopLeft, posBottomRight);
    QRectF sceneTransRec(transTopLeft, transBottomRight);

    if (sceneTransRec.intersects(scenePosRec))
    {
        return transCenter;
    }
    if(sceneTransRec.contains(posCenter))
    {
        posCenter =   _pos->center();// + _pos->scenePos();//_coords.getMiddlePoint();//  
        transCenter =  _trans->center();// + _trans->scenePos();
    }
    QLineF transLeftSide(transTopLeft, transBottomLeft);
    QLineF transRightSide(transTopRight, transBottomRight);
    QLineF transTopSide(transTopLeft, transTopRight);
    QLineF transBottomSide(transBottomLeft, transBottomRight);

    /*QLineF angle1 = QLineF(transCenter, transTopRight);
    QLineF angle2 = QLineF(transCenter, transTopLeft);
    QLineF angle3 = QLineF(transCenter, transBottomLeft);
    QLineF angle4 = QLineF(transCenter, transBottomRight);*/

    QPointF transContact;
    QLineF edge(transCenter, posCenter);

    if(edge.intersect(transLeftSide, &transContact) == QLineF::BoundedIntersection)
        return transContact;
    if(edge.intersect(transRightSide, &transContact) == QLineF::BoundedIntersection)
        return transContact;
    if(edge.intersect(transTopSide, &transContact) == QLineF::BoundedIntersection)
        return transContact;
    if(edge.intersect(transBottomSide, &transContact) == QLineF::BoundedIntersection)
        return transContact;
    return transContact; //+ _trans->scenePos();
    //qreal angle = edge.angle();
}

//=============================================================================
// class PNRenderDefaultImpl
//=============================================================================

//-----------------------------------------------------------------------------
// Creates graphical representation of the given Position with (0,0) coordinates
//-----------------------------------------------------------------------------
QGraphicsItem* PNRendererWithLogData::createPosGraphicsItem(PositionWithPtr* pos) const
{
    PositionGrItem* posGrI = new PositionGrItem(pos->getData(), QRectF(0, 0, 1, 1));
    return posGrI;
}

//-----------------------------------------------------------------------------
// Creates graphical representation of the given Position with the given coordinates
//-----------------------------------------------------------------------------
QGraphicsItem* PNRendererWithLogData::createPosGraphicsItem(PositionWithPtr* pos, QRectF coords) const
{
    PositionGrItem* posGrI = new PositionGrItem(pos->getData(), coords);
    return posGrI;
}

//-----------------------------------------------------------------------------
//Returns coordinates of the given graphical representstion of Position
//-----------------------------------------------------------------------------
QRectF PNRendererWithLogData::makePosCoordsList(QGraphicsItem* gri) const 
{
    if(gri->type() == IPositionGrItem::Type)
    {
        auto posGrI = static_cast<PositionGrItem*>(gri);
        return posGrI->getCoord();
    }
    return QRectF(0,0,0,0);
}

//-----------------------------------------------------------------------------
// Creates graphical representation of the given Transition with (0,0) coordinates
//-----------------------------------------------------------------------------
QGraphicsItem* PNRendererWithLogData::createTransGraphicsItem(TransitionWithPtr* trans) const
{
    TransitionGrItem* transGrI = new TransitionGrItem(trans->getData(), QRectF(0, 0, 0, 0));
    return transGrI;
}

//-----------------------------------------------------------------------------
// Creates graphical representation of the given Transition with the given coordinates
//-----------------------------------------------------------------------------
QGraphicsItem* PNRendererWithLogData::createTransGraphicsItem(TransitionWithPtr* trans, QRectF coords) const
{
    TransitionGrItem* transGrI = new TransitionGrItem(trans->getData(), coords);
    return transGrI;
}

//-----------------------------------------------------------------------------
//Returns coordinates of the given graphical representstion of Transition
//-----------------------------------------------------------------------------
QRectF PNRendererWithLogData::makeTransCoordsList(QGraphicsItem* gri) const 
{
    if(gri->type() == ITransitionGrItem::Type)
    {
        auto transGrI = static_cast<TransitionGrItem*>(gri);
        return transGrI->getCoord();
    }
    return QRectF(0,0,0,0);
}

//-----------------------------------------------------------------------------
// Creates graphical representation of the Edge with the given coordinates 
// with the given data
//-----------------------------------------------------------------------------
QGraphicsItem* PNRendererWithLogData::createEdgeGraphicsItem(EdgeCoords coords, IPNBaseData::IPNBaseDataPtr data)
{
    EdgeGrItem* edgeGrI = new EdgeGrItem(coords, data);
    return edgeGrI;
}

//-----------------------------------------------------------------------------
// Creates graphical representation of the given Edge 
//-----------------------------------------------------------------------------
QGraphicsItem* PNRendererWithLogData::createEdgeGraphicsItem(EdgeWithPtr* edge, QGraphicsItem* posGrItem, QGraphicsItem* transGrItem)
{
    if(posGrItem->type() == IPositionGrItem::Type && transGrItem->type() == ITransitionGrItem::Type)
    {
        PositionGrItem* posI = static_cast<PositionGrItem*>(posGrItem);
        TransitionGrItem* transI = static_cast<TransitionGrItem*>(transGrItem);
        if(edge->getDir() == EdgeWithPtr::fromPosToTrans)
        {
            EdgeGrItem* edgeGrI = new EdgeGrItem(posI, transI, edge->getData());
            return edgeGrI;
        }
        if(edge->getDir() == EdgeWithPtr::fromTransToPos)
        {
            EdgeGrItem* edgeGrI = new EdgeGrItem(transI, posI, edge->getData());
            return edgeGrI;
        }
    }
    return nullptr;
}

//-----------------------------------------------------------------------------
// Creates graphical representation of the given Edge with the given coordinates
//-----------------------------------------------------------------------------
QGraphicsItem* PNRendererWithLogData::createEdgeGraphicsItem(EdgeWithPtr* edge, QGraphicsItem* posGrItem, QGraphicsItem* transGrItem, EdgeCoords coords)
{
    EdgeGrItem* edgeGrI = static_cast<EdgeGrItem*>(createEdgeGraphicsItem(edge, posGrItem, transGrItem));
    edgeGrI->setCoords(coords);
    return edgeGrI;
}

//-----------------------------------------------------------------------------
// Returns coordinates of the given graphical representstion of Edge
//-----------------------------------------------------------------------------
EdgeCoords PNRendererWithLogData::makeEdgeCoordsList(QGraphicsItem* gri) const
{
    if(gri->type() == EdgeGrItem::Type)
    {
        EdgeGrItem* edgeGrI = static_cast<EdgeGrItem*>(gri);
        return edgeGrI->getCoords();
    }
    return EdgeCoords();
}



////*****************************************************************************
////____________________класс EdgePT (ребро позиция->переход)____________________
////*****************************************************************************
//
//OlegRenderDef1::EdgePT::EdgePT(TransitionItem* from, TransitionItem* to)
//{
//    _from = from;
//    _to = to;
//    _toPoint = _to->scenePos() + _to->inCenter();
//    _fromPoint = _from->scenePos() + _from->outCenter();
//    _pikeLength = 15;
//    _pikeAngle = 15;
//    _highestY = from->scene()->sceneRect().y();
//    _lowestY = from->scene()->sceneRect().top() + from->scene()->sceneRect().height();
//
//}
//
//void OlegRenderDef1::EdgePT::rearrange()
//{
//    _fromPoint = _from->scenePos() +  posContact(_from, _to->center() + _to->scenePos());//_from->outCenter();
//    _toPoint = _to->scenePos() + transContact(_to, _from->center() + _from->scenePos());//_to->inCenter();
//    if(_fromPoint.x() < _toPoint.x())
//    {
//        //-----------------------------------------------------------------------
//        //обычная стрелка
//        //-----------------------------------------------------------------------
//
//        QLineF l(_toPoint, _fromPoint);
//        l.setAngle(l.angle() - _pikeAngle);
//        l.setLength(_pikeLength);
//        QLineF l2(_toPoint, _fromPoint);
//        l2.setAngle(l2.angle() + _pikeAngle);
//        l2.setLength(_pikeLength);
//        QPolygonF pol;
//        pol  << _toPoint << l.p2() << l2.p2() << _toPoint;
//
//        QPainterPath path;
//        path.moveTo(_fromPoint);
//        //auto diff = _toPoint - _fromPoint , p1 = _toPoint, p2 = _fromPoint;
//        /*p1 += QPointF(diff.x() * 0.25, _lowestY);
//        p2 += QPointF(diff.x() * 0.75, _lowestY);
//        path.cubicTo(p1, p2, _toPoint);*/
//        path.cubicTo((_fromPoint + _toPoint)/2, (_fromPoint + _toPoint)/2, _toPoint);
//        //path.lineTo(_toPoint);
//        path.addPolygon(pol);
//        //path.moveTo(_toPoint);
//        //path.cubicTo(p2, p1, _fromPoint);
//        //path.lineTo(_toPoint);
//        setPath(path);
//
//
//        // рисование shape для попадания мышки
//        QPainterPath shape;
//        QLineF ls1(_toPoint, _fromPoint);
//        QLineF ls2(_toPoint, _fromPoint);
//        QLineF ls3(_fromPoint, _toPoint);
//        QLineF ls4(_fromPoint, _toPoint);
//        ls1.setAngle(ls1.angle() - 90);
//        ls1.setLength(_shapeEps);
//        ls2.setAngle(ls2.angle() + 90);
//        ls2.setLength(_shapeEps);
//        ls3.setAngle(ls3.angle() - 90);
//        ls3.setLength(_shapeEps);
//        ls4.setAngle(ls4.angle() + 90);
//        ls4.setLength(_shapeEps);
//
//        QPolygonF pols;
//        shape.moveTo(ls1.p2());
//        shape.lineTo(ls2.p2());
//        shape.lineTo(ls3.p2());
//        shape.lineTo(ls4.p2());
//        shape.lineTo(ls1.p2());
//        //pols << ls1.p2() << ls2.p2() << ls3.p2() << ls4.p2()<< ls1.p2();
//        //shape.addPolygon(pols);
//        _shape = shape;
//        //setPath(shape);
//    }
//    else
//    {
//        if(_fromPoint.y() > 0)
//        {
//            //--------------------------------------------------------------------
//            //нижняя длинная стрелка
//            //--------------------------------------------------------------------
//            QPainterPath path;
//            path.moveTo(_fromPoint);
//            const qreal dist = 10;
//            /*path.lineTo(_fromPoint.x() + dist, _lowestY + dist);
//            path.lineTo(_toPoint.x() - dist, _lowestY + dist);
//            path.lineTo(_toPoint);*/
//            auto diff = _toPoint - _fromPoint , p1 = _toPoint, p2 = _fromPoint;
//            p1 += QPointF(diff.x() * 0.25, _lowestY);
//            p2 += QPointF(diff.x() * 0.75, _lowestY);
//            path.cubicTo(p1, p2, _toPoint);
//
//            //рисуем стрелку
//            QLineF l(_toPoint, p2);//QPointF(_toPoint.x() - dist, _lowestY + dist));
//            l.setAngle(l.angle() - _pikeAngle);
//            l.setLength(_pikeLength);
//            QLineF l2(_toPoint, p2);//QPointF(_toPoint.x() - dist, _lowestY + dist));
//            l2.setAngle(l2.angle() + _pikeAngle);
//            l2.setLength(_pikeLength);
//            path.lineTo(l.p2());
//            path.lineTo(l2.p2());
//            path.lineTo(_toPoint);
//            //возврат обратно, чтоб не заливал (почему-то происходит автоматическая заливка от начала до конца пути)
//            /*path.lineTo(_toPoint.x() - dist, _lowestY + dist);
//            path.lineTo(_fromPoint.x() + dist, _lowestY + dist);*/
//            path.moveTo(_toPoint);
//            path.cubicTo(p2, p1, _fromPoint);
//            setPath(path);
//        }
//        else
//        {
//            //--------------------------------------------------------------------
//            //верхняя длинная стрелка
//            //--------------------------------------------------------------------
//            QPainterPath path;
//            path.moveTo(_fromPoint);
//            const qreal dist = 10;
//            /*path.lineTo(_fromPoint.x() + dist, _highestY - dist);
//            path.lineTo(_toPoint.x() - dist, _highestY - dist);
//            path.lineTo(_toPoint);*/
//            auto diff = _toPoint - _fromPoint , p1 = _toPoint, p2 = _fromPoint;
//            p1 += QPointF(diff.x() * 0.25, _highestY);
//            p2 += QPointF(diff.x() * 0.75, _highestY);
//            path.cubicTo(p1, p2, _toPoint);
//
//            //рисуем стрелку
//            QLineF l(_toPoint, p2);//QPointF(_toPoint.x() - dist, _highestY - dist));
//            l.setAngle(l.angle() - _pikeAngle);
//            l.setLength(_pikeLength);
//            QLineF l2(_toPoint, p2);//QPointF(_toPoint.x() - dist, _highestY - dist));
//            l2.setAngle(l2.angle() + _pikeAngle);
//            l2.setLength(_pikeLength);
//            path.lineTo(l.p2());
//            path.lineTo(l2.p2());
//            path.lineTo(_toPoint);
//            //возврат обратно, чтоб не заливал (почему-то происходит автоматическая заливка от начала до конца пути)
//            /*path.lineTo(_toPoint.x() - dist, _highestY - dist);
//            path.lineTo(_fromPoint.x() + dist, _highestY - dist);*/
//            path.moveTo(_toPoint);
//            path.cubicTo(p2, p1, _fromPoint);
//            setPath(path);
//        }
//    }
//    //_fromPoint = _from->scenePos() + _from->outCenter();
//    //_toPoint = _to->scenePos() + _to->inCenter();
//    //if(_fromPoint.x() < _toPoint.x())
//    //{
//    //   //-----------------------------------------------------------------------
//    //   //обычная стрелка
//    //   //-----------------------------------------------------------------------
//
//    //   QLineF l(_toPoint, _fromPoint);
//    //   l.setAngle(l.angle() - _pikeAngle);
//    //   l.setLength(_pikeLength);
//    //   QLineF l2(_toPoint, _fromPoint);
//    //   l2.setAngle(l2.angle() + _pikeAngle);
//    //   l2.setLength(_pikeLength);
//    //   QPolygonF pol;
//    //   pol  << _toPoint << l.p2() << l2.p2();
//    //   
//    //   QPainterPath path;
//    //   path.moveTo(_fromPoint);
//    //   path.lineTo(_toPoint);
//    //   path.addPolygon(pol);
//    //   path.lineTo(_toPoint);
//    //   
//    //   setPath(path);
//    //}
//    //else
//    //{
//    //   if(_fromPoint.y() > 0)
//    //   {
//    //      //--------------------------------------------------------------------n
//    //      //нижняя длинная стрелка
//    //      //--------------------------------------------------------------------
//    //      QPainterPath path;
//    //      path.moveTo(_fromPoint);
//    //      const qreal dist = 10;
//    //      path.lineTo(_fromPoint.x() + dist, _lowestY + dist);
//    //      path.lineTo(_toPoint.x() - dist, _lowestY + dist);
//    //      path.lineTo(_toPoint);
//    //      
//    //      //рисуем стрелку
//    //      QLineF l(_toPoint, QPointF(_toPoint.x() - dist, _lowestY + dist));
//    //      l.setAngle(l.angle() - _pikeAngle);
//    //      l.setLength(_pikeLength);
//    //      QLineF l2(_toPoint, QPointF(_toPoint.x() - dist, _lowestY + dist));
//    //      l2.setAngle(l2.angle() + _pikeAngle);
//    //      l2.setLength(_pikeLength);
//    //      path.lineTo(l.p2());
//    //      path.lineTo(l2.p2());
//    //      path.lineTo(_toPoint);
//    //      //возврат обратно, чтоб не заливал (почему-то происходит автоматическая заливка от начала до конца пути)
//    //      path.lineTo(_toPoint.x() - dist, _lowestY + dist);
//    //      path.lineTo(_fromPoint.x() + dist, _lowestY + dist);
//    //      setPath(path);
//    //   }
//    //   else
//    //   {
//    //      //--------------------------------------------------------------------
//    //      //верхняя длинная стрелка
//    //      //--------------------------------------------------------------------
//    //      QPainterPath path;
//    //      path.moveTo(_fromPoint);
//    //      const qreal dist = 10;
//    //      path.lineTo(_fromPoint.x() + dist, _highestY - dist);
//    //      path.lineTo(_toPoint.x() - dist, _highestY - dist);
//    //      path.lineTo(_toPoint);
//    //      
//    //      //рисуем стрелку
//    //      QLineF l(_toPoint, QPointF(_toPoint.x() - dist, _highestY - dist));
//    //      l.setAngle(l.angle() - _pikeAngle);
//    //      l.setLength(_pikeLength);
//    //      QLineF l2(_toPoint, QPointF(_toPoint.x() - dist, _highestY - dist));
//    //      l2.setAngle(l2.angle() + _pikeAngle);
//    //      l2.setLength(_pikeLength);
//    //      path.lineTo(l.p2());
//    //      path.lineTo(l2.p2());
//    //      path.lineTo(_toPoint);
//    //      //возврат обратно, чтоб не заливал (почему-то происходит автоматическая заливка от начала до конца пути)
//    //      path.lineTo(_toPoint.x() - dist, _highestY - dist);
//    //      path.lineTo(_fromPoint.x() + dist, _highestY - dist);
//    //      setPath(path);
//    //   }
//    //}
//}
//
//
//
//
////*****************************************************************************
////____________________класс EdgeTP (ребро переход->позиция)____________________
////*****************************************************************************
//
//OlegRenderDef1::EdgeTP::EdgeTP(OlegRenderDef1::TransitionItem* from, OlegRenderDef1::PositionItem* to)
//{
//    _from = from;
//    _to = to;
//    _pikeLength = 15;
//    _pikeAngle = 15;
//    _toPoint = _to->scenePos() +_to->inCenter();
//    _fromPoint = _from->scenePos() + _from->outCenter();
//    _highestY = from->scene()->sceneRect().y();
//    _lowestY = from->scene()->sceneRect().top() + from->scene()->sceneRect().height();
//
//}
//
////-----------------------------------------------------------------------------
////сеттеры и геттеры
////-----------------------------------------------------------------------------
//
//OlegRenderDef1::TransitionItem* OlegRenderDef1::EdgeTP::getFrom()
//{
//    return _from;
//}
//
//OlegRenderDef1::PositionItem* OlegRenderDef1::EdgeTP::getTo()
//{
//    return _to;
//}
//
//void OlegRenderDef1::EdgeTP::setFrom(OlegRenderDef1::TransitionItem* from)
//{
//    if(from)
//    {
//        _from = from;
//    }
//}
//
//void OlegRenderDef1::EdgeTP::setTo(OlegRenderDef1::PositionItem* to)
//{
//    if(to)
//    {
//        _to = to;
//    }
//}
//
//void OlegRenderDef1::EdgeTP::rearrange()
//{
//    _fromPoint = _from->scenePos() + transContact(_from, _to->center() + _to->scenePos());
//    _toPoint = _to->scenePos() + posContact(_to, _from->center() + _from->scenePos());
//    if(_fromPoint.x() < _toPoint.x())
//    {
//        //-----------------------------------------------------------------------
//        //обычная стрелка
//        //-----------------------------------------------------------------------
//
//        QLineF l(_toPoint, _fromPoint);
//        l.setAngle(l.angle() - _pikeAngle);
//        l.setLength(_pikeLength);
//        QLineF l2(_toPoint, _fromPoint);
//        l2.setAngle(l2.angle() + _pikeAngle);
//        l2.setLength(_pikeLength);
//        QPolygonF pol;
//        pol  << _toPoint << l.p2() << l2.p2() << _toPoint;
//
//        QPainterPath path;
//        path.moveTo(_fromPoint);
//        //auto diff = _toPoint - _fromPoint , p1 = _toPoint, p2 = _fromPoint;
//        /*p1 += QPointF(diff.x() * 0.25, _lowestY);
//        p2 += QPointF(diff.x() * 0.75, _lowestY);
//        path.cubicTo(p1, p2, _toPoint);*/
//        //path.cubicTo((_fromPoint + _toPoint)/2, (_fromPoint + _toPoint)/2, _toPoint);
//        path.lineTo(_toPoint);
//        path.addPolygon(pol);
//        //path.moveTo(_toPoint);
//        //path.cubicTo(p2, p1, _fromPoint);
//        //path.lineTo(_toPoint);
//
//        setPath(path);
//        QPainterPath shape;
//        QLineF ls1(_toPoint, _fromPoint);
//        QLineF ls2(_toPoint, _fromPoint);
//        QLineF ls3(_fromPoint, _toPoint);
//        QLineF ls4(_fromPoint, _toPoint);
//        ls1.setAngle(ls1.angle() - 90);
//        ls1.setLength(_shapeEps);
//        ls2.setAngle(ls2.angle() + 90);
//        ls2.setLength(_shapeEps);
//        ls3.setAngle(ls3.angle() - 90);
//        ls3.setLength(_shapeEps);
//        ls4.setAngle(ls4.angle() + 90);
//        ls4.setLength(_shapeEps);
//
//        QPolygonF pols;
//        shape.moveTo(ls1.p2());
//        shape.lineTo(ls2.p2());
//        shape.lineTo(ls3.p2());
//        shape.lineTo(ls4.p2());
//        shape.lineTo(ls1.p2());
//        //pols << ls1.p2() << ls2.p2() << ls3.p2() << ls4.p2()<< ls1.p2();
//        //shape.addPolygon(pols);
//        _shape = shape;
//        //setPath(shape);
//    }
//    else
//    {
//        if(_fromPoint.y() > 0)
//        {
//            //--------------------------------------------------------------------
//            //нижняя длинная стрелка
//            //--------------------------------------------------------------------
//            QPainterPath path;
//            path.moveTo(_fromPoint);
//            const qreal dist = 10;
//            /*path.lineTo(_fromPoint.x() + dist, _lowestY + dist);
//            path.lineTo(_toPoint.x() - dist, _lowestY + dist);
//            path.lineTo(_toPoint);*/
//            auto diff = _toPoint - _fromPoint , p1 = _toPoint, p2 = _fromPoint;
//            p1 += QPointF(diff.x() * 0.25, _lowestY);
//            p2 += QPointF(diff.x() * 0.75, _lowestY);
//            path.cubicTo(p1, p2, _toPoint);
//
//            //рисуем стрелку
//            QLineF l(_toPoint, p2);//QPointF(_toPoint.x() - dist, _lowestY + dist));
//            l.setAngle(l.angle() - _pikeAngle);
//            l.setLength(_pikeLength);
//            QLineF l2(_toPoint, p2);//QPointF(_toPoint.x() - dist, _lowestY + dist));
//            l2.setAngle(l2.angle() + _pikeAngle);
//            l2.setLength(_pikeLength);
//            path.lineTo(l.p2());
//            path.lineTo(l2.p2());
//            path.lineTo(_toPoint);
//            //возврат обратно, чтоб не заливал (почему-то происходит автоматическая заливка от начала до конца пути)
//            /*path.lineTo(_toPoint.x() - dist, _lowestY + dist);
//            path.lineTo(_fromPoint.x() + dist, _lowestY + dist);*/
//            path.moveTo(_toPoint);
//            path.cubicTo(p2, p1, _fromPoint);
//            setPath(path);
//        }
//        else
//        {
//            //--------------------------------------------------------------------
//            //верхняя длинная стрелка
//            //--------------------------------------------------------------------
//            QPainterPath path;
//            path.moveTo(_fromPoint);
//            const qreal dist = 10;
//            /*path.lineTo(_fromPoint.x() + dist, _highestY - dist);
//            path.lineTo(_toPoint.x() - dist, _highestY - dist);
//            path.lineTo(_toPoint);*/
//            auto diff = _toPoint - _fromPoint , p1 = _toPoint, p2 = _fromPoint;
//            p1 += QPointF(diff.x() * 0.25, _highestY);
//            p2 += QPointF(diff.x() * 0.75, _highestY);
//            path.cubicTo(p1, p2, _toPoint);
//
//            //рисуем стрелку
//            QLineF l(_toPoint, p2);//QPointF(_toPoint.x() - dist, _highestY - dist));
//            l.setAngle(l.angle() - _pikeAngle);
//            l.setLength(_pikeLength);
//            QLineF l2(_toPoint, p2);//QPointF(_toPoint.x() - dist, _highestY - dist));
//            l2.setAngle(l2.angle() + _pikeAngle);
//            l2.setLength(_pikeLength);
//            path.lineTo(l.p2());
//            path.lineTo(l2.p2());
//            path.lineTo(_toPoint);
//            //возврат обратно, чтоб не заливал (почему-то происходит автоматическая заливка от начала до конца пути)
//            /*path.lineTo(_toPoint.x() - dist, _highestY - dist);
//            path.lineTo(_fromPoint.x() + dist, _highestY - dist);*/
//            path.moveTo(_toPoint);
//            path.cubicTo(p2, p1, _fromPoint);
//            setPath(path);
//        }
//    }
//}
//
//// TODO: должно стать:
//
//QGraphicsItem* OlegRenderDef1::createPosGraphicsItem(Position<IPNBaseData*>* pos, const QRectF& coord)//QPointF placeOfItem)
//
//
//    // TODO: было
//    QGraphicsItem* OlegRenderDef1::createPosGraphicsItem(Position* pos, QPointF placeOfItem)
//{
//    QString text = QString::fromStdString(pos->getName());
//    PositionItem* posItem = new PositionItem(text, placeOfItem);
//    return posItem;
//}
//
//QGraphicsItem* OlegRenderDef1::createTransGraphicsItem(Transition* trans, QPointF placeOfItem)
//{
//    QString text = QString::fromStdString(trans->getName());
//    TransitionItem* transItem = new TransitionItem(text, placeOfItem);
//    return transItem;
//}
//
//QGraphicsItem* OlegRenderDef1::createEdgeGraphicsItem(QPointF from, QPointF to, QGraphicsScene* scene)
//{
//    EdgeItem* edgeItem = new EdgeItem(from, to, scene);
//    return edgeItem;
//}
//
//QGraphicsItem* OlegRenderDef1::createEdgePTGraphicsItem(QGraphicsItem* fromPos, QGraphicsItem* toTrans)
//{
//    if(fromPos->type() != PositionItem::Type || toTrans->type() != TransitionItem::Type)
//        throw std::exception("Invalid edge type"); 
//    PositionItem* pos = static_cast<PositionItem*>(fromPos);
//    TransitionItem* trans = static_cast<TransitionItem*>(toTrans);
//    EdgePT* edge = new EdgePT(pos, trans);
//    return edge;
//}
//
//QGraphicsItem* OlegRenderDef1::createEdgeTPGraphicsItem(QGraphicsItem* fromTrans, QGraphicsItem* toPos)
//{
//    if(toPos->type() != PositionItem::Type || fromTrans->type() != TransitionItem::Type)
//        throw std::exception("Invalid edge type"); 
//    PositionItem* pos = static_cast<PositionItem*>(toPos);
//    TransitionItem* trans = static_cast<TransitionItem*>(fromTrans);
//    EdgeTP* edge = new EdgeTP(trans, pos);
//    return edge;
//}