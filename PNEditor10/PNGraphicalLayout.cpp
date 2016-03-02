#include "PNGraphicalLayout.h"

//=============================================================================
// class PNGraphicalLayout
//=============================================================================

//-----------------------------------------------------------------------------
// Constructs empty PNGraphicalLayout with the given PetriNet and renderer
//-----------------------------------------------------------------------------
PNGraphicalLayout::PNGraphicalLayout(VTMinePetriNet* pn, IVTMinePNRenderer* renderer)
{
    if(pn)
    {
        _pn = new VTMinePetriNet(pn);
    }
    
    _scene = new QGraphicsScene();
    _mode = mdEdit;
    _rendererId = renderer->getId();
    _posRenderer = renderer;
    _transRenderer = renderer;
    _edgeRenderer = renderer;

}

//-----------------------------------------------------------------------------
// Constructs empty PNGraphicalLayout with the given PetriNet and default renderer
//-----------------------------------------------------------------------------
//PNGraphicalLayout::PNGraphicalLayout(VTMinePetriNet* pn)
//{
//    if(pn)
//    {
//        _pn = new VTMinePetriNet(pn);
//    }
//    _scene = new QGraphicsScene();
//    _mode = mdEdit;
//    PNRendererDefaultImpl* renderer = new PNRendererDefaultImpl; // надо брать из менеджера
//    _posRenderer = renderer;
//    _transRenderer = renderer;
//    _edgeRenderer = renderer;
//}

/** \brief Copy constructor */
PNGraphicalLayout::PNGraphicalLayout(const PNGraphicalLayout& copyThat)
{
    _pn = new VTMinePetriNet(copyThat._pn);
    _scene = new QGraphicsScene();
    _mode = copyThat._mode;
    _rendererId = copyThat._rendererId;
    _posRenderer = copyThat._posRenderer;
    _transRenderer = copyThat._transRenderer;
    _edgeRenderer = copyThat._edgeRenderer;
    _name = copyThat._name;
    for(auto i = copyThat._positions.begin(); i != copyThat._positions.end(); ++i)
    {
        PosGrItem* posI = *i;
        PositionWithPtr* pos = _pn->searchPos(posI->getData());
        addPos(pos, posI->getCoord());
    }

    for(auto i = copyThat._transitions.begin(); i != copyThat._transitions.end(); ++i)
    {
        TransGrItem* transI = *i;
        TransitionWithPtr* trans = _pn->searchTrans(transI->getData());
        addTrans(trans, transI->getCoord());
    }

    for(auto i = copyThat._posToEdges.begin(); i != copyThat._posToEdges.end(); ++i)
    {
        EdgeGrItem* edgeI = i->second;
        PositionWithPtr* pos = _pn->searchPos(edgeI->getPos()->getData());
        TransitionWithPtr* trans = _pn->searchTrans(edgeI->getTrans()->getData());
        if (edgeI->getDir() == IVTMinePNRenderer::IEdgeGrItem::fromPosToTrans)
        {
            EdgeWithPtr* edge = _pn->searchEdge(pos, trans, EdgeWithPtr::fromPosToTrans);
            addEdge(edge, edgeI->getCoords())->rearrange();
        }
        if (edgeI->getDir() == IVTMinePNRenderer::IEdgeGrItem::fromTransToPos)
        {
            EdgeWithPtr* edge = _pn->searchEdge(pos, trans, EdgeWithPtr::fromTransToPos);
            addEdge(edge, edgeI->getCoords())->rearrange();
        }
    }
}

//-----------------------------------------------------------------------------
// Constructs PNGraphicalLayout with the given PNGraphicalLayout
//-----------------------------------------------------------------------------
PNGraphicalLayout::PNGraphicalLayout(PNGraphicalLayout* copyThat)
{
    _pn = new VTMinePetriNet(copyThat->_pn);
    _scene = new QGraphicsScene();
    _mode = copyThat->_mode;
    _rendererId = copyThat->_rendererId;
    _posRenderer = copyThat->_posRenderer;
    _transRenderer = copyThat->_transRenderer;
    _edgeRenderer = copyThat->_edgeRenderer;
    _name = copyThat->_name;
    for(auto i = copyThat->_positions.begin(); i != copyThat->_positions.end(); ++i)
    {
        PosGrItem* posI = *i;
        PositionWithPtr* pos = _pn->searchPos(posI->getData());
        addPos(pos, posI->getCoord());
    }

    for(auto i = copyThat->_transitions.begin(); i != copyThat->_transitions.end(); ++i)
    {
        TransGrItem* transI = *i;
        TransitionWithPtr* trans = _pn->searchTrans(transI->getData());
        addTrans(trans, transI->getCoord());
    }

    for(auto i = copyThat->_posToEdges.begin(); i != copyThat->_posToEdges.end(); ++i)
    {
        EdgeGrItem* edgeI = i->second;
        PositionWithPtr* pos = _pn->searchPos(edgeI->getPos()->getData());
        TransitionWithPtr* trans = _pn->searchTrans(edgeI->getTrans()->getData());
        if (edgeI->getDir() == IVTMinePNRenderer::IEdgeGrItem::fromPosToTrans)
        {
            EdgeWithPtr* edge = _pn->searchEdge(pos, trans, EdgeWithPtr::fromPosToTrans);
            addEdge(edge, edgeI->getCoords())->rearrange();
        }
        if (edgeI->getDir() == IVTMinePNRenderer::IEdgeGrItem::fromTransToPos)
        {
            EdgeWithPtr* edge = _pn->searchEdge(pos, trans, EdgeWithPtr::fromTransToPos);
            addEdge(edge, edgeI->getCoords())->rearrange();
        }
    }
}
//-----------------------------------------------------------------------------
// Destructor of the class
//-----------------------------------------------------------------------------
PNGraphicalLayout::~PNGraphicalLayout()
{
    for(auto i = _posToEdges.begin(); i != _posToEdges.end(); ++i)
        delete i->second;

    for(auto i = _positions.begin(); i != _positions.end(); ++i)
        delete *i;
    
    for(auto i = _transitions.begin(); i != _transitions.end(); ++i)
        delete *i;

    _positions.clear();
    _transitions.clear();
    _posToEdges.clear();
    _transToEdges.clear();
    _posToItem.clear();
    _transToItem.clear();

    delete _scene;
}

//-----------------------------------------------------------------------------
// Adds new PosGrItem to the PNGraphicalLayout with the given Position and 
// coordinates
//-----------------------------------------------------------------------------
PNGraphicalLayout::PosGrItem* PNGraphicalLayout::addPos(PositionWithPtr* pos, QRectF coords)
{
    if(searchPosGrItem(pos->getData()) == nullptr)
    {
        PosGrItem* posI = static_cast<PosGrItem*>(_posRenderer->createPosGraphicsItem(pos, coords));
        //coords.setTopLeft(posI->mapToScene(coords.topLeft()));
        //posI->setCoord(coords);
        //posI->setPos(coords.topLeft()); так не работает
        _scene->addItem(posI);
        
        
        _positions.push_back(posI);
        addTranslation(pos, posI);
        return posI;
    }
    return nullptr;
}

//-----------------------------------------------------------------------------
// Adds new TransGrItem to the PNGraphicalLayout with the given Transition 
// and coordinates
//-----------------------------------------------------------------------------
PNGraphicalLayout::TransGrItem* PNGraphicalLayout::addTrans(TransitionWithPtr* trans, QRectF coords)
{
    if(searchTransGrItem(trans->getData()) == nullptr)
    {
        TransGrItem* transI = static_cast<TransGrItem*>(_transRenderer->createTransGraphicsItem(trans, coords));
        //coords.setTopLeft(transI->mapToScene(coords.topLeft()));
        //transI->setCoord(coords);
        //transI->setPos(transI->mapFromScene(coords.topLeft()));
        _scene->addItem(transI);
        
        
        auto tp = transI->scenePos();
        
        
        _transitions.push_back(transI);
        addTranslation(trans, transI);
        return transI;
    }
    return nullptr;
}

//-----------------------------------------------------------------------------
// Adds new EdgeGrItem to the PNGraphicalLayout with the given Edge
//-----------------------------------------------------------------------------
PNGraphicalLayout::EdgeGrItem* PNGraphicalLayout::addEdge(EdgeWithPtr* edge)
{
    auto posI = getGrItem(edge->getPos());
    auto transI = getGrItem(edge->getTrans());
    EdgeGrItem* edgeI = static_cast<EdgeGrItem*>(_edgeRenderer->createEdgeGraphicsItem(edge, posI, transI));
    _scene->addItem(edgeI);
    addTranslation(edge, edgeI);
    _posToEdges.insert(PIEIPair(posI, edgeI));
    _transToEdges.insert(TIEIPair(transI, edgeI));
    return edgeI;
}

//-----------------------------------------------------------------------------
// Adds new EdgeGrItem to the PNGraphicalLayout with the given Edge and 
// coordinates
//-----------------------------------------------------------------------------
PNGraphicalLayout::EdgeGrItem* PNGraphicalLayout::addEdge(EdgeWithPtr* edge, EdgeCoords coords)
{
    auto posI = getGrItem(edge->getPos());
    auto transI = getGrItem(edge->getTrans());
    EdgeGrItem* edgeI = static_cast<EdgeGrItem*>(_edgeRenderer->createEdgeGraphicsItem(edge, posI, transI, coords));
    _scene->addItem(edgeI);
    addTranslation(edge, edgeI);
    _posToEdges.insert(PIEIPair(posI, edgeI));
    _transToEdges.insert(TIEIPair(transI, edgeI));
    return edgeI;
}

//-----------------------------------------------------------------------------
// Removes item from the PNGraphicalLayout if the item benongs to 
// PNGraphicalLayout
//-----------------------------------------------------------------------------
void PNGraphicalLayout::removeItem(QGraphicsItem* rem)
{
    if (!rem)
        return;
    if (rem->type() == PosGrItem::Type)
    {
        removePos(static_cast<PosGrItem*>(rem));
    }else
        if(rem->type() == TransGrItem::Type)
        {
            removeTrans(static_cast<TransGrItem*>(rem));
        }else
            if(rem->type() == EdgeGrItem::Type)
            {
                removeEdge(static_cast<EdgeGrItem*>(rem));
            }
}

//-----------------------------------------------------------------------------
// Removes PosGrItem from the PNGraphicalLayout if the PosGrItem benongs to 
// PNGraphicalLayout
//-----------------------------------------------------------------------------
void PNGraphicalLayout::removePos(PosGrItem* remPosI)
{
    removeEdgesWithPos(remPosI);
    _scene->removeItem(remPosI);
    PositionWithPtr* pos = _pn->searchPos(remPosI->getData());
    _posToItem.erase(_posToItem.find(pos));
    _pn->removePos(pos);
    _positions.remove(remPosI); // сам вызывает деструктор
}

//-----------------------------------------------------------------------------
// Removes TransGrItem from the PNGraphicalLayout if the TransGrItem benongs 
// to PNGraphicalLayout
//-----------------------------------------------------------------------------
void PNGraphicalLayout::removeTrans(TransGrItem* remTransI)
{
    removeEdgesWithTrans(remTransI);
    _scene->removeItem(remTransI);
    TransitionWithPtr* trans = _pn->searchTrans(remTransI->getData());
    _transToItem.erase(_transToItem.find(trans));
    _pn->removeTrans(trans);
    _transitions.remove(remTransI); // сам вызывает деструктор
}

//-----------------------------------------------------------------------------
// Removes EdgeGrItem from the PNGraphicalLayout if the EdgeGrItem benongs 
// to PNGraphicalLayout
//-----------------------------------------------------------------------------
void PNGraphicalLayout::removeEdge(EdgeGrItem* edgeI)
{
    auto delIt1 = _posToEdges.equal_range(edgeI->getPos());
    for ( auto i = delIt1.first; i != delIt1.second; ++i )
    {
        if (i->second == edgeI)
        {
            _posToEdges.erase(i);
            break;
        }
    }
    auto delIt2 = _transToEdges.equal_range(edgeI->getTrans());
    for ( auto i = delIt2.first; i != delIt2.second; ++i )
    {
        if (i->second == edgeI)
        {
            _transToEdges.erase(i);
            break;
        }
    }

    _scene->removeItem(edgeI);
    
    auto pos = _pn->searchPos(edgeI->getPos()->getData());
    auto trans = _pn->searchTrans(edgeI->getTrans()->getData());
    EdgeWithPtr* edge = nullptr;
    if(edgeI->getDir() == EdgeGrItem::fromPosToTrans)
    {
        edge = _pn->searchEdge(pos, trans, EdgeWithPtr::fromPosToTrans);
    }
    if(edgeI->getDir() == EdgeGrItem::fromTransToPos)
    {
        edge = _pn->searchEdge(pos, trans, EdgeWithPtr::fromTransToPos);
    }

    _edgeToItem.erase(_edgeToItem.find(edge));
    _pn->removeEdge(edge);
    delete edgeI;

}

//-----------------------------------------------------------------------------
// Removes all edges that are connected with the given PosGrItem
//-----------------------------------------------------------------------------
void PNGraphicalLayout::removeEdgesWithPos(PosGrItem* posI)
{
    auto delInt = _posToEdges.equal_range(posI);
    for (auto i = delInt.first; i != delInt.second; ++i)
    {

        auto edgeI = i->second;
        _scene->removeItem(edgeI);
        auto delIt2 = _transToEdges.equal_range(edgeI->getTrans());
        for ( auto i = delIt2.first; i != delIt2.second; ++i )
        {
            if (i->second == edgeI)
            {
                _transToEdges.erase(i);
                break;
            }
        }

        auto pos = _pn->searchPos(edgeI->getPos()->getData());
        auto trans = _pn->searchTrans(edgeI->getTrans()->getData());
        EdgeWithPtr* edge = nullptr;
        if(edgeI->getDir() == EdgeGrItem::fromPosToTrans)
        {
            edge = _pn->searchEdge(pos, trans, EdgeWithPtr::fromPosToTrans);
        }
        if(edgeI->getDir() == EdgeGrItem::fromTransToPos)
        {
            edge = _pn->searchEdge(pos, trans, EdgeWithPtr::fromTransToPos);
        }

        _edgeToItem.erase(_edgeToItem.find(edge));
        _pn->removeEdge(edge);
        delete edgeI;
    }
    _posToEdges.erase(delInt.first, delInt.second);
}

//-----------------------------------------------------------------------------
// Removes all edges that are connected with the given TransGrItem
//-----------------------------------------------------------------------------
void PNGraphicalLayout::removeEdgesWithTrans(TransGrItem* transI)
{
    auto delInt = _transToEdges.equal_range(transI);
    for (auto i = delInt.first; i != delInt.second; ++i)
    {
        auto edgeI = i->second;
        _scene->removeItem(edgeI);
        auto delIt1 = _posToEdges.equal_range(edgeI->getPos());
        for ( auto i = delIt1.first; i != delIt1.second; ++i )
        {
            if (i->second == edgeI)
            {
                _posToEdges.erase(i);
                break;
            }
        }

        auto pos = _pn->searchPos(edgeI->getPos()->getData());
        auto trans = _pn->searchTrans(edgeI->getTrans()->getData());
        EdgeWithPtr* edge = nullptr;
        if(edgeI->getDir() == EdgeGrItem::fromPosToTrans)
        {
            edge = _pn->searchEdge(pos, trans, EdgeWithPtr::fromPosToTrans);
        }
        if(edgeI->getDir() == EdgeGrItem::fromTransToPos)
        {
            edge = _pn->searchEdge(pos, trans, EdgeWithPtr::fromTransToPos);
        }

        _edgeToItem.erase(_edgeToItem.find(edge));
        _pn->removeEdge(edge);
        delete edgeI;
    }
    _transToEdges.erase(delInt.first,delInt.second);
}

//-----------------------------------------------------------------------------
// Finds PosGrItem in the PNGraphicalLayout with given data.
//-----------------------------------------------------------------------------
PNGraphicalLayout::PosGrItem* PNGraphicalLayout::searchPosGrItem(Data data)
{
    for(auto i = _positions.begin(); i != _positions.end(); ++i)
    {
        PosGrItem* posI = *i;
        if(posI->getData() == data)
        {
            return posI;
        }
    }
    return nullptr;
}

//-----------------------------------------------------------------------------
// Finds TransGrItem in the PNGraphicalLayout with given data.
//-----------------------------------------------------------------------------
PNGraphicalLayout::TransGrItem* PNGraphicalLayout::searchTransGrItem(Data data)
{
    for(auto i = _transitions.begin(); i != _transitions.end(); ++i)
    {
        TransGrItem* transI = *i;
        if(transI->getData() == data)
        {
            return transI;
        }
    }
    return nullptr;
}

//-----------------------------------------------------------------------------
// Finds EdgeGrItem in the PNGraphicalLayout with the given PosGrItem, 
// TransGrItem, Dir.
//-----------------------------------------------------------------------------
PNGraphicalLayout::EdgeGrItem* PNGraphicalLayout::searchEdgeGrItem(PosGrItem* posI, TransGrItem* transI, EdgeGrItem::Dir dir)
{
    auto serIt = _posToEdges.equal_range(posI);
    for ( auto i = serIt.first; i != serIt.second; ++i )
    {
        if (i->second->getPos() == posI && i->second->getTrans() == transI && i->second->getDir() == dir)
        {
            return i->second;
        }
    }
    return nullptr;
}

//-----------------------------------------------------------------------------
// Sets IVTMinePNRenderer of the PNGraphicalLayout with te given IVTMinePNRenderer
//-----------------------------------------------------------------------------
void PNGraphicalLayout::setRenderer(IVTMinePNRenderer* renderer)
{
    _rendererId = renderer->getId();
    _posRenderer = renderer;
    _transRenderer = renderer;
    _edgeRenderer = renderer;

    auto oldPositions = _positions;
    auto oldTransitions = _transitions;
    auto oldEdges = _posToEdges;

    for(auto i = oldPositions.begin(); i != oldPositions.end(); ++i)
    {
        auto remPosI = *i;
        auto coord = remPosI->getCoord();
        //coord.setTopLeft(remPosI->scenePos());// + coord.topLeft()
        PositionWithPtr* pos = _pn->searchPos(remPosI->getData());
        _posToItem.erase(_posToItem.find(pos));
        _scene->removeItem(remPosI);
        _positions.remove(remPosI);
        addPos(pos, coord);
    }

    for(auto i = oldTransitions.begin(); i != oldTransitions.end(); ++i)
    {
        auto remTransI = *i;
        auto coord = remTransI->getCoord();
        //coord.setTopLeft(remTransI->scenePos());// + coord.topLeft()
        TransitionWithPtr* trans = _pn->searchTrans(remTransI->getData());
        _transToItem.erase(_transToItem.find(trans));
        _scene->removeItem(remTransI);
        _transitions.remove(remTransI);
        addTrans(trans, coord);
        
    }

    for(auto i = oldEdges.begin(); i != oldEdges.end(); ++i)
    {
        auto edgeI = i->second;
        auto delIt1 = _posToEdges.equal_range(edgeI->getPos());
        for ( auto i = delIt1.first; i != delIt1.second; ++i )
        {
            if (i->second == edgeI)
            {
                _posToEdges.erase(i);
                break;
            }
        }
        auto delIt2 = _transToEdges.equal_range(edgeI->getTrans());
        for ( auto i = delIt2.first; i != delIt2.second; ++i )
        {
            if (i->second == edgeI)
            {
                _transToEdges.erase(i);
                break;
            }
        }

        _scene->removeItem(edgeI);

        auto pos = _pn->searchPos(edgeI->getPos()->getData());
        auto trans = _pn->searchTrans(edgeI->getTrans()->getData());
        EdgeWithPtr* edge = nullptr;
        if(edgeI->getDir() == EdgeGrItem::fromPosToTrans)
        {
            edge = _pn->searchEdge(pos, trans, EdgeWithPtr::fromPosToTrans);
        }
        if(edgeI->getDir() == EdgeGrItem::fromTransToPos)
        {
            edge = _pn->searchEdge(pos, trans, EdgeWithPtr::fromTransToPos);
        }

        _edgeToItem.erase(_edgeToItem.find(edge));
        addEdge(edge, edgeI->getCoords())->rearrange();
        delete edgeI;
    }

}

//-----------------------------------------------------------------------------
// Sets QGraphicsScene of the PNGraphicalLayout with te given QGraphicsScene
//-----------------------------------------------------------------------------
void PNGraphicalLayout::setScene(QGraphicsScene* scene)
{
    _scene = scene;
}

//-----------------------------------------------------------------------------
// Sets PetriNet of the PNGraphicalLayout with te given VTMinePetriNet
//-----------------------------------------------------------------------------
void PNGraphicalLayout::setPN(VTMinePetriNet* pn)
{
    if(pn)
    {
        _pn = new VTMinePetriNet(pn);
    }
}

//void PNGraphicalLayout::setWF(const WFNet* WF)
//{
//   if(WF)
//   {
//      _WF = new WFNet(*WF);
//   }
//}

//-----------------------------------------------------------------------------
// Sets Mode of the PNGraphicalLayout with te given Mode
//-----------------------------------------------------------------------------
void PNGraphicalLayout::setMode(Mode mode)
{
    _mode = mode;
}

//-----------------------------------------------------------------------------
// Makes items of the PNGraphicalLayout movable (if tf equal true) of not 
// movable (if tf equal false)
//-----------------------------------------------------------------------------
void PNGraphicalLayout::setMoveFlags(bool tf)
{
    Q_FOREACH(PosGrItem* i, _positions)
    {
        i->setFlag(QGraphicsItem::ItemIsMovable, tf);
    }
    Q_FOREACH(TransGrItem* i, _transitions)
    {
        i->setFlag(QGraphicsItem::ItemIsMovable, tf);
    }
}

//-----------------------------------------------------------------------------
// Sets name of the PNGraphicalLayout with te given name
//-----------------------------------------------------------------------------
void PNGraphicalLayout::setName(const QString& name)
{
    _name = name;
}

//-----------------------------------------------------------------------------
// Returns name of the PNGraphicalLayout
//-----------------------------------------------------------------------------
const QString& PNGraphicalLayout::getName()
{
    return _name;
}

//-----------------------------------------------------------------------------
// Returns PosGrItem that gives graphical representation of the given Position
//-----------------------------------------------------------------------------
PNGraphicalLayout::PosGrItem* PNGraphicalLayout::getGrItem(PositionWithPtr* pos)
{
    return _posToItem.find(pos)->second;
}

//-----------------------------------------------------------------------------
// Returns TransGrItem that gives graphical representation of the given Transition
//-----------------------------------------------------------------------------
PNGraphicalLayout::TransGrItem* PNGraphicalLayout::getGrItem(TransitionWithPtr* trans)
{
    return _transToItem.find(trans)->second;
}

//-----------------------------------------------------------------------------
// Returns EdgeGrItem that gives graphical representation of the given Edge
//-----------------------------------------------------------------------------
PNGraphicalLayout::EdgeGrItem* PNGraphicalLayout::getGrItem(EdgeWithPtr* edge)
{
    return _edgeToItem.find(edge)->second;
}

//-----------------------------------------------------------------------------
// Returns  EdgeGrItems that contains the given PosGrItem
//-----------------------------------------------------------------------------
std::vector<PNGraphicalLayout::EdgeGrItem*> PNGraphicalLayout::getPosEdges(PosGrItem* posI)
{
    auto edgesIt = _posToEdges.equal_range(posI);
    std::vector<EdgeGrItem*> edgeVec;
    for(auto i = edgesIt.first; i != edgesIt.second; ++i)
    {
        edgeVec.push_back(i->second);
    }
    return edgeVec;
}

//-----------------------------------------------------------------------------
// Returns  EdgeGrItems that contains the given TransGrItem 
//-----------------------------------------------------------------------------
std::vector<PNGraphicalLayout::EdgeGrItem*> PNGraphicalLayout::getTransEdges(TransGrItem* transI)
{
    auto edgesIt = _transToEdges.equal_range(transI);
    std::vector<EdgeGrItem*> edgeVec;
    for(auto i = edgesIt.first; i != edgesIt.second; ++i)
    {
        edgeVec.push_back(i->second);
    }
    return edgeVec;
}
//-----------------------------------------------------------------------------
// Returns QGraphicsScene of the PNGraphicalLayout
//-----------------------------------------------------------------------------
QGraphicsScene* PNGraphicalLayout::getScene()
{
    return _scene;
}

//-----------------------------------------------------------------------------
// Returns PetriNet of the PNGraphicalLayout
//-----------------------------------------------------------------------------
VTMinePetriNet* PNGraphicalLayout::getPN()
{
    return _pn;
}

//-----------------------------------------------------------------------------
// Returns PositionRenderer of the PNGraphicalLayout
//-----------------------------------------------------------------------------
IVTMinePNRenderer::IVTMinePositionRenderer* PNGraphicalLayout::getPosRenderer()
{
    return _posRenderer;
}

//-----------------------------------------------------------------------------
// Returns TransitionRenderer of the PNGraphicalLayout
//-----------------------------------------------------------------------------
IVTMinePNRenderer::IVTMineTransitionRenderer* PNGraphicalLayout::getTransRenderer()
{
    return _transRenderer;
}

//-----------------------------------------------------------------------------
// Returns EdgeRenderer of the PNGraphicalLayout
//-----------------------------------------------------------------------------
IVTMinePNRenderer::IVTMineEdgeRenderer* PNGraphicalLayout::getEdgeRenderer()
{
    return _edgeRenderer;
}

//-----------------------------------------------------------------------------
// Returns list of PosGrItems of the PNGraphicalLayout
//-----------------------------------------------------------------------------
PNGraphicalLayout::PosGrItemsList& PNGraphicalLayout::getPositions()
{
    return _positions;
}

//-----------------------------------------------------------------------------
// Returns list of TransGrItems of the PNGraphicalLayout
//-----------------------------------------------------------------------------
PNGraphicalLayout::TransGrItemsList& PNGraphicalLayout::getTransitions()
{
    return _transitions;
}

//-----------------------------------------------------------------------------
// Adds translation from Position to PositionGrItem
//-----------------------------------------------------------------------------
void PNGraphicalLayout::addTranslation(PositionWithPtr* pos, PosGrItem* posItem)
{
    _posToItem.insert(PPIPair(pos, posItem));
}

//-----------------------------------------------------------------------------
// Adds translation from Transition to TransitionGrItem
//-----------------------------------------------------------------------------
void PNGraphicalLayout::addTranslation(TransitionWithPtr* trans, TransGrItem* transItem)
{
    _transToItem.insert(TTIPair(trans, transItem));
}

//-----------------------------------------------------------------------------
// Adds translation from Edge to EdgeGrItem
//-----------------------------------------------------------------------------
void PNGraphicalLayout::addTranslation(EdgeWithPtr* edge, EdgeGrItem* edgeItem)
{
    _edgeToItem.insert(EEIPair(edge, edgeItem));
}