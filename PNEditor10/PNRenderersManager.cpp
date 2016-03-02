#include "PNRenderersManager.h"


//=============================================================================
// class PNRendererManager
//=============================================================================

//-----------------------------------------------------------------------------
// Constructs PNRenderersManager with the given default renderer
//-----------------------------------------------------------------------------
PNRenderersManager::PNRenderersManager(IVTMinePNRenderer* defaultRenderer)
{
    _defaultRenderer = defaultRenderer;
    _idToRendMap.insert(IRPair(defaultRenderer->getId(), defaultRenderer));
}

//-----------------------------------------------------------------------------
// Destructor of the class
//-----------------------------------------------------------------------------
PNRenderersManager::~PNRenderersManager()
{
    for(auto i = _idToRendMap.begin(); i != _idToRendMap.end(); ++i)
    {
        delete i->second;
    }
    _idToRendMap.clear();
}

//-----------------------------------------------------------------------------
// Adds new renderer to the PNRendererManager
//-----------------------------------------------------------------------------
void PNRenderersManager::registerRenderer(IVTMinePNRenderer* renderer)
{
    if(_idToRendMap.count(renderer->getId()) == 0)
        _idToRendMap.insert(IRPair(renderer->getId(),renderer));
}

//-----------------------------------------------------------------------------
// Sets default renderer
//-----------------------------------------------------------------------------
void PNRenderersManager::setDefaultRenderer(IVTMinePNRenderer* renderer)
{
    _defaultRenderer = renderer;
    if(_idToRendMap.count(renderer->getId()) == 0)
        _idToRendMap.insert(IRPair(renderer->getId(), renderer));
}

//-----------------------------------------------------------------------------
// Returns list of renderers
//-----------------------------------------------------------------------------
std::list<IVTMinePNRenderer*> PNRenderersManager::getListOfRenderers()
{
    std::list<IVTMinePNRenderer*> rendList;
    for(auto i = _idToRendMap.begin(); i != _idToRendMap.end(); ++i)
    {
        rendList.push_back(i->second);
    }
    return rendList;
}

//-----------------------------------------------------------------------------
// Returns default renderer
//-----------------------------------------------------------------------------
IVTMinePNRenderer* PNRenderersManager::getDefaultRenderer()
{
    return _defaultRenderer;
}

//-----------------------------------------------------------------------------
// Returns renderer with the given id
//-----------------------------------------------------------------------------
IVTMinePNRenderer* PNRenderersManager::getRenderer(const QString& id)
{
    auto rendIt = _idToRendMap.find(id); 
    if(rendIt != _idToRendMap.end())
        return _idToRendMap.find(id)->second;
    return _defaultRenderer; // может лучше не так
}

//-----------------------------------------------------------------------------
// Returns default Position bounding rectangle of the renderer with the given id
//-----------------------------------------------------------------------------
QRectF PNRenderersManager::getRendererPosDefaultRect(const QString& id)
{
    auto rendIt = _idToRendMap.find(id); 
    if(rendIt != _idToRendMap.end())
    {
        auto rend = rendIt->second;
        PositionWithPtr* pos = new PositionWithPtr(std::shared_ptr<PNBaseDataDefaultImpl>(new PNBaseDataDefaultImpl("a")));
        auto posI = static_cast<IVTMinePNRenderer::IPositionGrItem*>(rend->createPosGraphicsItem(pos));
        QRectF rec = posI->boundingRect();
        delete pos;
        return rec;
    }
    return QRectF(0,0,1,1);
}

//-----------------------------------------------------------------------------
// Returns default Transition bounding rectangle of the renderer with the given id
//-----------------------------------------------------------------------------
QRectF PNRenderersManager::getRendererTransDefaultSizeRect(const QString& id)
{
    auto rendIt = _idToRendMap.find(id); 
    if(rendIt != _idToRendMap.end())
    {
        auto rend = rendIt->second;
        TransitionWithPtr* trans = new TransitionWithPtr(std::shared_ptr<PNBaseDataDefaultImpl>(new PNBaseDataDefaultImpl("a")));
        auto transI = static_cast<IVTMinePNRenderer::ITransitionGrItem*>(rend->createTransGraphicsItem(trans));
        QRectF rec = transI->boundingRect();
        delete trans;
        return rec;
    }
    return QRectF(0,0,1,1);
}