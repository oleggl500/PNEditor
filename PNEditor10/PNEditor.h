#ifndef PNEDITOR_H

///////////////////////////////////////////////////////////////////////////////
/// \file
/// \brief Contains implementation of PNEditor.
/// \author Oleg Bulanov
/// \version 0.1.0
/// \date 14.08.2014
///////////////////////////////////////////////////////////////////////////////

#define PNEDITOR_H

#include <QtGui/QMainWindow>
#include <map>
#include "qset.h"
#include <QInputDialog>
//#include "IPNEditor.h"
#include "PNGraphicsView.h"
#include "PNRenderersManager.h"
#include "PetriNetsManager.h"
#include "PNGraphicalLayoutsManager.h"
#include "PNRendererWithLogData.h"


/** \brief Imports (visualize) and exports (after editing) PetriNet and PNGraphicalLayout 
* 
*   
*
*/
class PNEditor : public QObject //, public IPNEditor
{
    Q_OBJECT
    //Q_INTERFACES(IPNEditor)

public:
    /** \brief Contains grid for visualizing PetriNet 
    * 
    *   
    *
    */
    class Grid
    {
    public:
        /** \brief Node of Grid */
        struct Node
        {
            QPointF point;  ///< QPointF on scene
            bool empty;     ///< Flag that is true if node does not contains PetriNet item false otherwise
        }; // struct Node

    public:
        /** \brief Default constructor */
        Grid() {};

        /** \brief Constructs Grid for the given number of PetriNet items and given width and height of the node */
        Grid(int numEl, qreal width, qreal height);

        /** \brief Returns first empty Node QPointF in the given column */
        QPointF getPoint(int curCol);

        /** \brief Sets width of the node */
        void setWidth(qreal width);

        /** \brief Sets height of the node */
        void setHeight(qreal height);

        /** \brief Returns width of the node */
        qreal getWidth();

        /** \brief Returns height of the node */
        qreal getHeight();
    private:
        std::vector<std::vector<Node>>  _gridVec;   ///< 2d vector that stores grid nodes

        qreal                           _nodeXSize; ///< Width of the node 
        qreal                           _nodeYSize; ///< Height of the node
    }; // class Grid

    /** \brief Type definition for Map from QWidget to PNGraphicsView */
    typedef QMap<QWidget*, PNGraphicsView*> WidToViewMap;
public:

    static const int defaultVertDist = 30;      ///< Const that defines default distance between PetriNet items on y axis
    static const int defaultHorizDist = 100;    ///< Const that defines default distance between PetriNet items on x axis

public:
    /** \brief Constructs PNEditor with menus, tab widgets and toolbox */
    PNEditor();

    /** \brief Destructor of the class */
    ~PNEditor();

    /** \brief Imports and visualize given PetriNet */
    QWidget* import(VTMinePetriNet* PN);

    /** \brief Imports given PNGraphicalLayout */
    QWidget* import(PNGraphicalLayout* layout);

    /** \brief Exports PetriNet */
    VTMinePetriNet* exportPN();

    /** \brief Exports PNGraphicalLayout */
    PNGraphicalLayout* exportLayout();//нужен конструктор копий

    /** \brief Sets distance between PetriNet items on y axis  */
    void setVertDist(qreal dist);

    /** \brief Sets distance between PetriNet items on x axis  */
    void setHorizDist(qreal dist);

    /** \brief Returns distance between PetriNet items on y axis  */
    qreal getVertDist();

    /** \brief Returns distance between PetriNet items on x axis  */
    qreal getHorizDist();

    /** \brief Returns main menu of the PNEditor */
    QMenu* getMenu();

private:
    /** \brief Draws given Positions in the given column */
    void drawPos(std::vector<PositionWithPtr*>& notDrawn, int curGridCol, QSet<PositionWithPtr*>& allNotDrawnPos, QSet<TransitionWithPtr*>& allNotDrawnTrans);
    
    /** \brief Draws given Transitions in the given column */
    void drawTrans(std::vector<TransitionWithPtr*>& notDrawn, int curGridCol, QSet<PositionWithPtr*>& allNotDrawnPos, QSet<TransitionWithPtr*>& allNotDrawnTrans);

    /** \brief Creates new tab in tab widget with PNGaphicsView and the given PNGraphicalLayout */
    void createNewTab(PNGraphicalLayout* pnl);
    
    //void drawPos(PNGraphicalLayout* layout);
    //void drawTrans(PNGraphicalLayout* layout);

private slots:
    /** \brief Adding new Position slot */
    void pushAddPosButton();
    
    /** \brief Adding new Transition slot */
    void pushAddTransButton();

    /** \brief Allowing/forbiding adding new edges slot */
    void allowAddingEdges(int);

    /** \brief Setting PNEditor in View mode slot */
    void setViewMode();

    /** \brief Setting PNEditor in Move mode slot */
    void setMoveMode();

    /** \brief Setting PNEditor in Edit mode slot */
    void setEditMode();

    /** \brief Changing renderer of current PNGraphicalLayout slot */
    void changeRenderer();

    /** \brief Import slot */
    void importing();

    /** \brief Export current PetriNet slot */
    void exportPn();

    /** \brief Export current PNGraphicalLayout slot */
    void exportPNL();

    /** \brief Tab page close slot */
    void tabClosed(int); // не забыть про _addPosBut поменять пэрента

    /** \brief Tab page changed slot */
    void tabChanged(int); // здесь меняем кур

private:
    PNGraphicalLayout*  _curGrLayout;   ///< Current PNGraphicalLayout of PNEditor
    PNGraphicsView*     _curGrView;     ///< Current PNGraphicsView of PNEditor
    Grid                _grid;          ///< Grid of PNEditor
    qreal               _vertDist;      ///< Distance between PetriNet items on y axis
    qreal               _horizDist;     ///< Distance between PetriNet items on x axis

    PNRenderersManager*         _rendManager;   ///< PNRenderersManager of PNEditor
    PetriNetsManager*           _PNManager;     ///< PetriNetsManager of PNEditor
    PNGraphicalLayoutsManager*  _PNLManager;    ///< PNGraphicalLayoutsManager of PNEditor

    QWidget*            _centralWidget; ///< Central widget of PNEditor
    QTabWidget*         _tabWidget;     ///< QTabWidget of PNEditor
    QMenu*              _editorMenu;    ///< Main menu of PNEditor

    WidToViewMap        _tabToView;     ///< Map from tab page content to PNGraphicsView of the tab page content
    
    // удаляется вместе с _editorMenu
    QMenu*              _modeMenu;      ///< Mode menu of PNEditor
    QAction*            _viewAct;       ///< Change Mode to view mode action
    QAction*            _moveAct;       ///< Change Mode to move mode action
    QAction*            _editAct;       ///< Change Mode to edit mode action
    QAction*            _changeRendAct; ///< Change Renderer action
    QAction*            _importAct;     ///< Import action
    QAction*            _exportPNAct;   ///< Export PetriNet action
    QAction*            _exportPNLAct;  ///< Export PNGraphicalLayout action

    // удаляется вмете с _centralWidget
    QDockWidget*        _dockToolBox;           ///< QDockWidget with toolbox
    QPushButton*        _addPosButton;          ///< Adding new Position button in toolbox
    QPushButton*        _addTransButton;        ///< Adding new Transition button in toolbox
    QCheckBox*          _addingEdgesCheckBox;   ///< Allow/forbid adding edges checkbox in toolbox

}; // class PNEditor

#endif