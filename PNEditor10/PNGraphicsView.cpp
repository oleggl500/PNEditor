#include "PNGraphicsView.h"

//=============================================================================
// class PNGraphicsView
//=============================================================================

//-----------------------------------------------------------------------------
// Constructs PNGraphicsView with the given PNGraphicalLayout
//-----------------------------------------------------------------------------
PNGraphicsView::PNGraphicsView (PNGraphicalLayout* layout, QWidget* parent)
    : QGraphicsView(parent)
{
    _grLayout = layout;
    _removeAct = new QAction("Delete",this);
    connect(_removeAct, SIGNAL(triggered()), this, SLOT(remove()));
    _renameAct = new QAction("Rename",this);
    connect(_renameAct, SIGNAL(triggered()), this, SLOT(rename()));
    _increaseZValueAct = new QAction("Bring to Front",this);
    connect(_increaseZValueAct, SIGNAL(triggered()), this, SLOT(increaseZValue()));
    _decreaseZValueAct = new QAction("Send to Back",this);
    connect(_decreaseZValueAct, SIGNAL(triggered()), this, SLOT(decreaseZValue()));
    _selectedItem = nullptr;
    _curEdge = nullptr;
    _from = nullptr;

    _edgeRenderer = _grLayout->getEdgeRenderer();
    //_grLayout = layout;
    //setScene(_grLayout->getScene());
    _allowAddingEdges = false;
    setScene(_grLayout->getScene());
    setRenderHint(QPainter::Antialiasing);
    scene()->installEventFilter(this);
}

//-----------------------------------------------------------------------------
// Destructor of the class
//-----------------------------------------------------------------------------
PNGraphicsView::~PNGraphicsView()
{
    delete _removeAct;
    delete _renameAct;
    delete _increaseZValueAct;
    delete _decreaseZValueAct;
}

//-----------------------------------------------------------------------------
// Sets PNGraphicalLayout of the PNGraphicsView
//-----------------------------------------------------------------------------
void PNGraphicsView::setGrLayout(PNGraphicalLayout* layout)
{
    _grLayout = layout;
    setScene(_grLayout->getScene());//??
    scene()->installEventFilter(this);
}

//-----------------------------------------------------------------------------
// Allows adding edges if tf equal true or forbids adding edges if tf equal false
//-----------------------------------------------------------------------------
void PNGraphicsView::setAddingEdgesAllowed(bool tf)
{
    _allowAddingEdges = tf;
}

//-----------------------------------------------------------------------------
// Returns PNGraphicalLayout of the PNGraphicsView
//-----------------------------------------------------------------------------
PNGraphicalLayout* PNGraphicsView::getGrLayout()
{
    return _grLayout;
}

//-----------------------------------------------------------------------------
// Event filter of PNGraphicsView that calls other filters depending on mde of PNGraphicalLayout
//-----------------------------------------------------------------------------
bool PNGraphicsView::eventFilter(QObject* watched, QEvent* event)
{
    QGraphicsItem* item = nullptr;
    QGraphicsSceneMouseEvent* mouseEvent = nullptr;
    if (event->type() == QEvent::GraphicsSceneMousePress ||
        event->type() == QEvent::GraphicsSceneMouseMove ||
        event->type() == QEvent::GraphicsSceneMouseRelease)
        mouseEvent = static_cast<QGraphicsSceneMouseEvent*>(event);
    switch(_grLayout->mode())
    {
    case PNGraphicalLayout::mdMove :
        {
            moveFilter(mouseEvent, event);
            break;
        }
    case PNGraphicalLayout::mdView :
        {
            _grLayout->setMoveFlags(false);
            break;
        }
    case PNGraphicalLayout::mdEdit :
        {
            editFilter(mouseEvent, event);
            break;
        }
    };
    return QGraphicsView::eventFilter(watched, event);
}

//-----------------------------------------------------------------------------
// Move filter of PNGraphicsView
//-----------------------------------------------------------------------------
void PNGraphicsView::moveFilter(QGraphicsSceneMouseEvent* mouseEvent, QEvent* event)
{
    QGraphicsItem* item = nullptr;
    _grLayout->setMoveFlags(true);

    if(event->type() == QEvent::GraphicsSceneMouseMove)
    {
        item = scene()->itemAt(mouseEvent->scenePos().toPoint());
        if (!item)
            return;
        if(item->type() == EdgeGrItem::Type)
            return;
        if(item->type() == PosGrItem::Type && _grLayout->searchPosGrItem(static_cast<PosGrItem*>(item)->getData()) != nullptr)
        {
            PosGrItem* movingPos = static_cast<PosGrItem*>(item);
            std::vector<EdgeGrItem*> movingEdges = _grLayout->getPosEdges(movingPos);
            for(auto i = movingEdges.begin(); i != movingEdges.end(); ++i)
            {
                EdgeGrItem* movingEdge = *i;
                movingEdge->rearrange();
            }
            return;
        }
        if(item->type() == TransGrItem::Type && _grLayout->searchTransGrItem(static_cast<TransGrItem*>(item)->getData()) != nullptr)
        {
            TransGrItem* movingTrans = static_cast<TransGrItem*>(item);
            std::vector<EdgeGrItem*> movingEdges = _grLayout->getTransEdges(movingTrans);
            for(auto i = movingEdges.begin(); i != movingEdges.end(); ++i)
            {
                EdgeGrItem* movingEdge = *i;
                movingEdge->rearrange();
            }
            return;
        }
    }
}

//-----------------------------------------------------------------------------
// Edit filter of PNGraphicsView
//-----------------------------------------------------------------------------
void PNGraphicsView::editFilter(QGraphicsSceneMouseEvent* mouseEvent, QEvent* event)
{
    QGraphicsItem* item = nullptr;
    if(!_allowAddingEdges)
    {
        _grLayout->setMoveFlags(true);
        if(event->type() == QEvent::GraphicsSceneMousePress)
        {

            item = scene()->itemAt(mouseEvent->scenePos().toPoint());
            if (!item)
            {
                if(_selectedItem)
                {
                    if(_selectedItem->type() == PosGrItem::Type)
                        ((PosGrItem*)_selectedItem)->selectOutItem();
                    else
                        if(_selectedItem->type() == TransGrItem::Type)
                            ((TransGrItem*)_selectedItem)->selectOutItem();
                }
                return;
            }
            selectingItem(mouseEvent, item);
            if(mouseEvent->button() == Qt::RightButton)
            {
                if(item->type() == EdgeGrItem::Type)
                {
                    QMenu menu(this);
                    menu.addAction(_removeAct);
                    _selectedItem = item;
                    menu.exec( mouseEvent->screenPos());
                }
                else
                {
                    QMenu menu(this);
                    _selectedItem = item;
                    menu.addAction(_increaseZValueAct);
                    menu.addAction(_decreaseZValueAct);
                    menu.addAction(_renameAct);
                    menu.addAction(_removeAct);
                    menu.exec( mouseEvent->screenPos());
                }
            }
            return;
        }else 
            if(event->type() == QEvent::GraphicsSceneMouseMove)
            {

                item = scene()->itemAt(mouseEvent->scenePos().toPoint());
                if (!item)
                    return;
                if(item->type() == EdgeGrItem::Type)
                    return;
                if(item->type() == PosGrItem::Type && _grLayout->searchPosGrItem(static_cast<PosGrItem*>(item)->getData()) != nullptr)
                {
                    PosGrItem* movingPos = static_cast<PosGrItem*>(item);
                    std::vector<EdgeGrItem*> movingEdges = _grLayout->getPosEdges(movingPos);
                    for(auto i = movingEdges.begin(); i != movingEdges.end(); ++i)
                    {
                        EdgeGrItem* movingEdge = *i;
                        movingEdge->rearrange();
                        scene()->update();
                    }
                }
                if(item->type() == TransGrItem::Type && _grLayout->searchTransGrItem(static_cast<TransGrItem*>(item)->getData()) != nullptr)
                {
                    TransGrItem* movingTrans = static_cast<TransGrItem*>(item);
                    std::vector<EdgeGrItem*> movingEdges = _grLayout->getTransEdges(movingTrans);
                    for(auto i = movingEdges.begin(); i != movingEdges.end(); ++i)
                    {
                        EdgeGrItem* movingEdge = *i;
                        movingEdge->rearrange();
                        scene()->update();
                    }
                }
                return;
            }
    }
    else //adding edges
    {
        _grLayout->setMoveFlags(false);
        switch(event->type())
        {
        case QEvent::GraphicsSceneMousePress :
            {
                item = scene()->itemAt(mouseEvent->scenePos().toPoint());
                if (!item)
                    break;
                if (mouseEvent->button() == Qt::RightButton)
                    break;
                if (mouseEvent->button() == Qt::LeftButton && (item->type() == PosGrItem::Type || item->type() == TransGrItem::Type))
                {
                    _from = item;
                    if(item->type() == PosGrItem::Type)
                    {
                        EdgeCoords edgeCoords;
                        edgeCoords.setBeginPoint(item->scenePos() + static_cast<PosGrItem*>(item)->center());
                        edgeCoords.setEndPoint(mouseEvent->scenePos());
                        edgeCoords.setMiddlePoint((edgeCoords.getBeginPoint() + edgeCoords.getEndPoint()) / 2);
                        std::shared_ptr<PNBaseDataDefaultImpl> data(new PNBaseDataDefaultImpl);
                        auto eGrIt = _edgeRenderer->createEdgeGraphicsItem(edgeCoords, data);
                        _curEdge = static_cast<EdgeGrItem*>(eGrIt);
                        //_curEdge = new OlegRenderDef1::EdgeItem(item->scenePos() + static_cast<PosGrItem*>(item)->outCenter(), mouseEvent->scenePos(),scene());
                    }
                    if(item->type() == TransGrItem::Type)
                    {
                        EdgeCoords edgeCoords;
                        edgeCoords.setBeginPoint(item->scenePos() + static_cast<TransGrItem*>(item)->center());
                        edgeCoords.setEndPoint(mouseEvent->scenePos());
                        edgeCoords.setMiddlePoint((edgeCoords.getBeginPoint() + edgeCoords.getEndPoint()) / 2);
                        Data data(new PNBaseDataDefaultImpl());
                        auto eGrIt = _edgeRenderer->createEdgeGraphicsItem(edgeCoords, data);
                        _curEdge = static_cast<EdgeGrItem*>(eGrIt);
                        //_curEdge = new OlegRenderDef1::EdgeItem(item->scenePos() + static_cast<TransGrItem*>(item)->outCenter(), mouseEvent->scenePos(),scene());
                    }
                    scene()->addItem(_curEdge);
                    _curEdge->rearrange();
                }
                break;
            }
        case QEvent::GraphicsSceneMouseMove :
            {
                //item = scene()->itemAt(mouseEvent->scenePos().toPoint());
                //if (!item)
                //break;
                if(_curEdge)
                {
                    EdgeCoords edgeCoords = _curEdge->getCoords();
                    edgeCoords.setEndPoint(mouseEvent->scenePos());
                    _curEdge->setCoords(edgeCoords);
                    _curEdge->rearrange();
                }
                break;
            }
        case QEvent::GraphicsSceneMouseRelease :
            {
                item = scene()->itemAt(mouseEvent->scenePos().toPoint());
                if (!item)
                {
                    if(_curEdge)
                    {
                        scene()->removeItem(_curEdge);
                        delete _curEdge;
                        _curEdge = nullptr;
                    }
                    break;
                }

                if (mouseEvent->button() == Qt::RightButton)
                    break;

                if (_curEdge && mouseEvent->button() == Qt::LeftButton)
                {
                    if(_from->type() == PosGrItem::Type && item->type() == TransGrItem::Type)
                    {
                        PosGrItem* fromPosItem = static_cast<PosGrItem*>(_from);
                        TransGrItem* toTransItem = static_cast<TransGrItem*>(item);

                        PositionWithPtr* fromPos = _grLayout->getPN()->searchPos(fromPosItem->getData());
                        TransitionWithPtr* toTrans = _grLayout->getPN()->searchTrans(toTransItem->getData());

                        EdgeWithPtr* newEdge = _grLayout->getPN()->addEdge(fromPos, toTrans);
                        _grLayout->addEdge(newEdge)->rearrange();
                    }
                    if(_from->type() == TransGrItem::Type && item->type() == PosGrItem::Type)
                    {
                        PosGrItem* toPosItem = static_cast<PosGrItem*>(item);
                        TransGrItem* fromTransItem = static_cast<TransGrItem*>(_from);

                        PositionWithPtr* toPos = _grLayout->getPN()->searchPos(toPosItem->getData());
                        TransitionWithPtr* fromTrans = _grLayout->getPN()->searchTrans(fromTransItem->getData());

                        EdgeWithPtr* newEdge = _grLayout->getPN()->addEdge(fromTrans, toPos);
                        _grLayout->addEdge(newEdge)->rearrange();
                    }

                }
                if(_curEdge)
                {
                    scene()->removeItem(_curEdge);
                    delete _curEdge;
                    _curEdge = nullptr;
                }
                break;
            }
        };
        return;
    }

}

//-----------------------------------------------------------------------------
// Selects the given item
//-----------------------------------------------------------------------------
void PNGraphicsView::selectingItem(QGraphicsSceneMouseEvent* mouseEvent, QGraphicsItem* item)
{
    if(mouseEvent->button() == Qt::LeftButton || mouseEvent->button() == Qt::RightButton)
    {
        if(item->type() == PosGrItem::Type)
        {
            if(_selectedItem)
            {
                if(_selectedItem->type() == PosGrItem::Type)
                {
                    ((PosGrItem*)_selectedItem)->selectOutItem();
                }
                else
                    if(_selectedItem->type() == TransGrItem::Type)
                    {
                        ((TransGrItem*)_selectedItem)->selectOutItem();
                    }
            }
            _selectedItem = item;
            ((PosGrItem*)item)->selectItem();
        }
        else if(item->type() == TransGrItem::Type)
        {
            if(_selectedItem)
            {
                if(_selectedItem->type() == PosGrItem::Type)
                {
                    ((PosGrItem*)_selectedItem)->selectOutItem();
                }
                else
                    if(_selectedItem->type() == TransGrItem::Type)
                    {
                        ((TransGrItem*)_selectedItem)->selectOutItem();
                    }
            }
            _selectedItem = item;
            ((TransGrItem*)item)->selectItem();
        }
        else
        {
            if(_selectedItem)
            {
                if(_selectedItem->type() == PosGrItem::Type)
                {
                    ((PosGrItem*)_selectedItem)->selectOutItem();
                }
                else
                    if(_selectedItem->type() == TransGrItem::Type)
                    {
                        ((TransGrItem*)_selectedItem)->selectOutItem();
                    }
            }
        }
    }
}

//-----------------------------------------------------------------------------
// Remove selected item slot
//-----------------------------------------------------------------------------
void PNGraphicsView::remove()
{
    _grLayout->removeItem(_selectedItem);
    _selectedItem = nullptr;
}

//-----------------------------------------------------------------------------
// Rename selected item slot
//-----------------------------------------------------------------------------
void PNGraphicsView::rename()
{
    if(_selectedItem->type() == PosGrItem::Type)
    {
        bool ok;
        QString text = QInputDialog::getText(this, "Enter position name", "Position name", QLineEdit::Normal, QString(), &ok);

        if(ok)
        {
            Data data(new PNBaseDataDefaultImpl(text));
            if(_grLayout->searchPosGrItem(data) == nullptr)
            {
                PosGrItem* posI = static_cast<PosGrItem*>(_selectedItem);
                data = posI->getData();
                data->setName(text);
                //_grLayout->getPN()->searchPos(posI->getData())->setData(data);

                /*auto position = _grLayout->getPN()->getPos(pos->getName().toStdString());
                _grLayout->getPN()->renamePos(position, text.toStdString());*/

                //_grLayout->rename(pos, text);


                //auto itPos = _grLayout->getPN()->getTransitions().find(pos->getName().toStdString());
                //itPos->first = text.toStdString();
            }
            else
            {
                QMessageBox msgBox;
                msgBox.setText(tr("Position with this name exists.\n"
                    "Position have not been added.\n"
                    "Try again"));
                msgBox.exec();
            }
        }
    }
    else if(_selectedItem->type() == TransGrItem::Type)
    {
        bool ok;
        QString text = QInputDialog::getText(this, "Enter Transition name", "Transition name", QLineEdit::Normal, QString(), &ok);

        if(ok)
        {
            Data data(new PNBaseDataDefaultImpl(text));
            if(_grLayout->searchTransGrItem(data) == nullptr)
            {
                TransGrItem* transI = static_cast<TransGrItem*>(_selectedItem);
                data = transI->getData();
                data->setName(text);
                //_grLayout->getPN()->searchTrans(transI->getData())->setData(data);

                /*auto transition = _grLayout->getPN()->getTrans(trans->getName().toStdString());
                _grLayout->getPN()->renameTrans(transition, text.toStdString());*/

                //_grLayout->rename(trans, text);

            }
            else
            {
                QMessageBox msgBox1;
                msgBox1.setText(tr("Transition with this name exists.\n"
                    "Transition have not been added.\n"
                    "Try again"));
                msgBox1.exec();
            }

        }
    }
}

//-----------------------------------------------------------------------------
// Bring to front slot
//-----------------------------------------------------------------------------
void PNGraphicsView::increaseZValue()
{
    static qreal highestZValue = 0;
    if(_selectedItem)
    {
        highestZValue += 0.01;
        _selectedItem->setZValue(highestZValue);
    }
    //_selectedItem->update();
}

//-----------------------------------------------------------------------------
// Send to back slot
//-----------------------------------------------------------------------------
void PNGraphicsView::decreaseZValue()
{
    static qreal lowestZValue = 0;
    if(_selectedItem)
    {
        lowestZValue -= 0.01;
        _selectedItem->setZValue(lowestZValue);
    }
}