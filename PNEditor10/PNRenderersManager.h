#ifndef PNRENDERERSMANAGER_H

///////////////////////////////////////////////////////////////////////////////
/// \file
/// \brief Contains PNRenderersManager
/// \author Oleg Bulanov
/// \version 0.1.0
/// \date 17.08.2014
///////////////////////////////////////////////////////////////////////////////

#define PNRENDERERSMANAGER_H

#include "PNRendererDefaultImpl.h"

/** \brief PNRenderersManager manages renderers-lifetime 
  * 
  *
  *
*/
class PNRenderersManager
{
public:
    /** \brief Type definition for map from QString to IVTMinePNRenderer */
    typedef std::map<QString, IVTMinePNRenderer*> IdToRendererMap;

    /** \brief Type definition for pair QString and IVTMinePNRenderer */
    typedef std::pair<QString, IVTMinePNRenderer*> IRPair;
public:
    /** \brief Constructs PNRenderersManager with the given default renderer */
    PNRenderersManager(IVTMinePNRenderer* defaultRenderer);

    /** \brief Destructor of the class */
    ~PNRenderersManager();

public:
    /** \brief Adds new renderer to the PNRendererManager */
    void registerRenderer(IVTMinePNRenderer* renderer);
    
    /** \brief Sets default renderer */
    void setDefaultRenderer(IVTMinePNRenderer* renderer);

    /** \brief Returns list of renderers */
    std::list<IVTMinePNRenderer*> getListOfRenderers();

    /** \brief Returns default renderer */
    IVTMinePNRenderer* getDefaultRenderer();
    
    /** \brief Returns renderer with the given id */
    IVTMinePNRenderer* getRenderer(const QString& id);
    
    /** \brief Returns default Position bounding rectangle of the renderer with the given id */
    QRectF getRendererPosDefaultRect(const QString& id); // может лишнее
    
    /** \brief Returns default Transition bounding rectangle of the renderer with the given id */
    QRectF getRendererTransDefaultSizeRect(const QString& id);

private:
    IdToRendererMap         _idToRendMap;       ///< Map that stores renderers
    IVTMinePNRenderer*      _defaultRenderer;   ///< Default renderer
}; // class PNRenderersManager

#endif