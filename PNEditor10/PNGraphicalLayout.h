#ifndef PNGRAPHICALLAYOUT_H

///////////////////////////////////////////////////////////////////////////////
/// \file
/// \brief Contains implementation of PNGraphicalLayout.
/// \author Oleg Bulanov
/// \version 0.1.0
/// \date 07.08.2014
///////////////////////////////////////////////////////////////////////////////

#define PNGRAPHICALLAYOUT_H

#include <QtGui/QMainWindow>
#include <map>
#include <QString>
#include <QMap>
//#include "PNRendererDefaultImpl.h"
#include "IVTMinePNRenderer.h"
#include "VTMinePetriNet.h"

// со временем появится namespace vtmine {


/** \brief PNGraphicalLayout stores graphical representation of PetriNet elements and PeriNet. 
  * 
  *
  *
*/
class PNGraphicalLayout
{
public:
    /** \brief Modes of PNEditor */
    enum Mode
    {
        mdView, ///< View mode
        mdMove, ///< View mode with ability to move PetriNet items
        mdEdit  ///< Edit mode
    };
public:
    /** \brief Type definition for Position graphical representation */
    typedef IVTMinePNRenderer::IPositionGrItem PosGrItem;

    /** \brief Type definition for Transition graphical representation */
    typedef IVTMinePNRenderer::ITransitionGrItem TransGrItem;

    /** \brief Type definition for Edge graphical representation */
    typedef IVTMinePNRenderer::IEdgeGrItem EdgeGrItem;

    /** \brief Type definition for base Data */
    typedef IPNBaseData::IPNBaseDataPtr Data;

    /** \brief Type definition for List of PosGrItems */
    typedef std::list<PosGrItem*> PosGrItemsList;

    /** \brief Type definition for List of TransGrItems */
    typedef std::list<TransGrItem*> TransGrItemsList;

    /** \brief Type definition for Map from PosGrItem to EdgeGrItem */
    typedef std::multimap<PosGrItem*, EdgeGrItem*> PosGrIToEdgeGrIMap;

    /** \brief Type definition for Map from TransGrItem to EdgeGrItem */
    typedef std::multimap<TransGrItem*, EdgeGrItem*> TransGrIToEdgeGrIMap;

    /** \brief Type definition for Map from PositionWithPtr to PosGrItem */
    typedef std::map<PositionWithPtr*, PosGrItem*> PosToPosGrItemMap;

    /** \brief Type definition for Map from TransitionWithPtr to TransGrItem */
    typedef std::map<TransitionWithPtr*, TransGrItem*> TransToTransGrItemMap;

    /** \brief Type definition for Map from EdgeWithPtr to EdgeGrItem */
    typedef std::map<EdgeWithPtr*, EdgeGrItem*> EdgeToEdgeGrItemMap;

    /** \brief Type definition for pair PositionWithPtr and PosGrItem */
    typedef std::pair<PositionWithPtr*, PosGrItem*> PPIPair;

    /** \brief Type definition for pair TransitionWithPtr and TransGrItem */
    typedef std::pair<TransitionWithPtr*, TransGrItem*> TTIPair;

    /** \brief Type definition for pair EdgeWithPtr and EdgeGrItem */
    typedef std::pair<EdgeWithPtr*, EdgeGrItem*> EEIPair;

    /** \brief Type definition for pair PosGrItem and EdgeGrItem */
    typedef std::pair<PosGrItem*, EdgeGrItem*> PIEIPair;

    /** \brief Type definition for pair TransGrItem and EdgeGrItem */
    typedef std::pair<TransGrItem*, EdgeGrItem*> TIEIPair;

public:
    /** \brief Constructs empty PNGraphicalLayout with empty PetriNet and default renderer */
    //PNGraphicalLayout();

    /** \brief Constructs empty PNGraphicalLayout with the given PetriNet and renderer */
    PNGraphicalLayout(VTMinePetriNet* pn, IVTMinePNRenderer* renderer);

    //** \brief Constructs empty PNGraphicalLayout with the given PetriNet and default renderer */
    //PNGraphicalLayout(VTMinePetriNet* pn);

    /** \brief Copy constructor */
    PNGraphicalLayout(const PNGraphicalLayout& copyThat);

    /** \brief Constructs PNGraphicalLayout with the given PNGraphicalLayout */
    PNGraphicalLayout(PNGraphicalLayout* layout);

    /** \brief Destructor of the class */
    ~PNGraphicalLayout();

public:
    /** \brief Returns Mode of PNEditor */
    Mode mode() { return _mode; }

    /** \brief Returns Id of renderer */
    const QString& getRendererId() { return _rendererId; }

    /** \brief Adds new PosGrItem to the PNGraphicalLayout with the given Position and coordinates */
    PosGrItem* addPos(PositionWithPtr* pos, QRectF coords);

    /** \brief Adds new TransGrItem to the PNGraphicalLayout with the given Transition and coordinates */
    TransGrItem* addTrans(TransitionWithPtr* trans, QRectF coords);

    /** \brief Adds new EdgeGrItem to the PNGraphicalLayout with the given Edge */
    EdgeGrItem* addEdge(EdgeWithPtr* edge);

    /** \brief Adds new EdgeGrItem to the PNGraphicalLayout with the given Edge and coordinates */
    EdgeGrItem* addEdge(EdgeWithPtr* edge, EdgeCoords coords);

    
    /** \brief Removes item from the PNGraphicalLayout if the item benongs to PNGraphicalLayout */
    void removeItem(QGraphicsItem* rem);

    /** \brief Removes PosGrItem from the PNGraphicalLayout if the PosGrItem benongs to PNGraphicalLayout */
    void removePos(PosGrItem* posI);

    /** \brief Removes TransGrItem from the PNGraphicalLayout if the TransGrItem benongs to PNGraphicalLayout */
    void removeTrans(TransGrItem* transI);

    /** \brief Removes EdgeGrItem from the PNGraphicalLayout if the EdgeGrItem benongs to PNGraphicalLayout */
    void removeEdge(EdgeGrItem* edgeI);

    /** \brief Removes all edges that are connected with the given PosGrItem */
    void removeEdgesWithPos(PosGrItem* posI);

    /** \brief Removes all edges that are connected with the given TransGrItem */
    void removeEdgesWithTrans(TransGrItem* transI);

    
    /** \brief Finds PosGrItem in the PNGraphicalLayout with given data.
    *  Returns nullptr if PosGrItem with the given data has not been found.
    */
    PosGrItem* searchPosGrItem(Data);
    
    /** \brief Finds TransGrItem in the PNGraphicalLayout with given data.
    *  Returns nullptr if TransGrItem with the given data has not been found.
    */
    TransGrItem* searchTransGrItem(Data);

    /** \brief Finds EdgeGrItem in the PNGraphicalLayout with the given PosGrItem, TransGrItem, Dir.
    *  Returns nullptr if EdgeGrItem with the params has not been found.
    */
    EdgeGrItem* searchEdgeGrItem(PosGrItem* posI, TransGrItem* transI, EdgeGrItem::Dir dir);
    
    /** \brief Sets IVTMinePNRenderer of the PNGraphicalLayout with te given IVTMinePNRenderer */
    void setRenderer(IVTMinePNRenderer* renderer);

    /** \brief Sets QGraphicsScene of the PNGraphicalLayout with te given QGraphicsScene */
    void setScene(QGraphicsScene* scene);

    /** \brief Sets PetriNet of the PNGraphicalLayout with te given VTMinePetriNet */
    void setPN(VTMinePetriNet* pn);

    /** \brief Sets Mode of the PNGraphicalLayout with te given Mode */
    void setMode(Mode mode);

    /** \brief Makes items of the PNGraphicalLayout movable (if tf equal true) of not movable (if tf equal false) */
    void setMoveFlags(bool tf);

    /** \brief Sets name of the PNGraphicalLayout with te given name */
    void setName(const QString& name);

    /** \brief Returns name of the PNGraphicalLayout */
    const QString& getName();

    /** \brief Returns PosGrItem that gives graphical representation of the given Position */
    PosGrItem* getGrItem(PositionWithPtr* pos);

    /** \brief Returns TransGrItem that gives graphical representation of the given Transition */
    TransGrItem* getGrItem(TransitionWithPtr* trans);

    /** \brief Returns EdgeGrItem that gives graphical representation of the given Edge */
    EdgeGrItem* getGrItem(EdgeWithPtr* edge);

    /** \brief Returns  EdgeGrItems that contains the given PosGrItem */
    std::vector<EdgeGrItem*> getPosEdges(PosGrItem* posI);

    /** \brief Returns  EdgeGrItems that contains the given TransGrItem */
    std::vector<EdgeGrItem*> getTransEdges(TransGrItem* transI);
    
    
    /** \brief Returns QGraphicsScene of the PNGraphicalLayout */
    QGraphicsScene* getScene();

    /** \brief Returns PetriNet of the PNGraphicalLayout */
    VTMinePetriNet* getPN();

    /** \brief Returns PositionRenderer of the PNGraphicalLayout */
    IVTMinePNRenderer::IVTMinePositionRenderer*      getPosRenderer();
    
    /** \brief Returns TransitionRenderer of the PNGraphicalLayout */
    IVTMinePNRenderer::IVTMineTransitionRenderer*    getTransRenderer();

    /** \brief Returns EdgeRenderer of the PNGraphicalLayout */
    IVTMinePNRenderer::IVTMineEdgeRenderer*          getEdgeRenderer();

    
    /** \brief Returns list of PosGrItems of the PNGraphicalLayout */
    PosGrItemsList& getPositions();

    /** \brief Returns list of TransGrItems of the PNGraphicalLayout */
    TransGrItemsList& getTransitions();


    
private:
    /** \brief Adds translation from Position to PositionGrItem */
    void addTranslation(PositionWithPtr*, PosGrItem*);

    /** \brief Adds translation from Transition to TransitionGrItem */
    void addTranslation(TransitionWithPtr*, TransGrItem*);

    /** \brief Adds translation from Edge to EdgeGrItem */
    void addTranslation(EdgeWithPtr*, EdgeGrItem*);

private:
    VTMinePetriNet*         _pn;            ///< PetriNet of the PNGraphicalLayout
    QString                 _name;          ///< Name of the PNGraphicalLayout


    QGraphicsScene*         _scene;         ///< QGraphicsScene of the PNGraphicalLayout
    Mode                    _mode;          ///< Mode of PNEditor
    QString                 _rendererId;    ///< Id of the renderer

    PosToPosGrItemMap       _posToItem;     ///< Map from Position to graphical representation (PosGrItem) of the Position
    TransToTransGrItemMap   _transToItem;   ///< Map from Transition to graphical representation (TransGrItem) of the Transition
    EdgeToEdgeGrItemMap     _edgeToItem;    ///< Map from Edge to graphical representation (EdgeGrItem) of the Edge

    PosGrItemsList          _positions;     ///< List of PosGrItems of PNGraphicalLayout
    TransGrItemsList        _transitions;   ///< List of TransGrItems of PNGraphicalLayout
    PosGrIToEdgeGrIMap      _posToEdges;    ///< Map from PosGrItem to EdgeGrItem of PNGraphicalLayout
    TransGrIToEdgeGrIMap    _transToEdges;  ///< Map from TransGrItem to EdgeGrItem of PNGraphicalLayout

    IVTMinePNRenderer::IVTMinePositionRenderer*      _posRenderer;   ///< Position renderer
    IVTMinePNRenderer::IVTMineTransitionRenderer*    _transRenderer; ///< Transition renderer
    IVTMinePNRenderer::IVTMineEdgeRenderer*          _edgeRenderer;  ///< Edge renderer

}; // class PNGraphicalLayout

#endif