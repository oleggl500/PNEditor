#include "PNEditor.h"

//=============================================================================
// class Grid
//=============================================================================

//-----------------------------------------------------------------------------
// Constructs Grid for the given number of PetriNet items and given width and 
// height of the node
//-----------------------------------------------------------------------------
PNEditor::Grid::Grid(int numEl, qreal width, qreal height)
{
    _nodeXSize = width;
    _nodeYSize = height;
    //_curCol = numEl;
    QPointF startPoint(- numEl * _nodeXSize, 0);
    for(int i = 0; i < 2 * numEl; i++)
    {
        Node sq;
        std::vector<Node> colSq;
        for(int j = 0; j < numEl; j++)
        {
            sq.empty = true;
            sq.point = startPoint;
            colSq.push_back(sq);
            startPoint += QPointF(0, _nodeYSize);
        }
        _gridVec.push_back(colSq);
        startPoint.setY(0);
        startPoint += QPointF(_nodeXSize,0);
    }
}

//-----------------------------------------------------------------------------
// Returns first empty Node QPointF in the given column
//-----------------------------------------------------------------------------
QPointF PNEditor::Grid::getPoint(int curCol)
{
    //curCol--;
    QPointF point;
    //if(curCol > 0 && curCol < 2*_gridVec.size())
    {
        for(int i = 0; i < _gridVec[curCol].size(); i++)
        {
            if(_gridVec[curCol][i].empty)
            {
                point = _gridVec[curCol][i].point;
                _gridVec[curCol][i].empty = false;
                return point;
            }
        }
        //return point;
    }
    //else
    //return QPointF();
}

//-----------------------------------------------------------------------------
// Sets width of the node
//-----------------------------------------------------------------------------
void PNEditor::Grid::setWidth(qreal width)
{
    _nodeXSize = width;
}

//-----------------------------------------------------------------------------
// Sets height of the node
//-----------------------------------------------------------------------------
void PNEditor::Grid::setHeight(qreal height)
{
    _nodeYSize = height;
}

//-----------------------------------------------------------------------------
// Returns width of the node
//-----------------------------------------------------------------------------
qreal PNEditor::Grid::getWidth()
{
    return _nodeXSize;
}

//-----------------------------------------------------------------------------
// Returns height of the node
//-----------------------------------------------------------------------------
qreal PNEditor::Grid::getHeight()
{
    return _nodeYSize;
}

//QPointF PNEditor::Grid::getAfterNode(int curCol)
//{
//   curCol++;
//   QPointF point;
//   if(curCol >= 0 && curCol < _gridVec.size())
//   {
//      for(int i = 0; i < _gridVec[curCol].size(); i++)
//      {
//         if(_gridVec[curCol][i].empty)
//         {
//            point = _gridVec[curCol][i].point;
//            _gridVec[curCol][i].empty = false;
//            break;
//         }
//      }
//      return point;
//   }
//   else
//      return QPointF();
//}

//=============================================================================
// class PNEditor
//=============================================================================

//-----------------------------------------------------------------------------
// Constructs PNEditor with menus, tab widgets and toolbox
//-----------------------------------------------------------------------------
PNEditor::PNEditor()
{
    _grid = Grid(0, 0, 0);

    //QTabWidget* myWidget = new QTabWidget(this);

    _centralWidget = new QWidget();//_centralWidget = new QWidget(this);!!

    _editorMenu = new QMenu("Editor");
    _changeRendAct = new QAction("Change renderer", _editorMenu);
    QObject::connect(_changeRendAct,SIGNAL(triggered()), this, SLOT(changeRenderer()));
    _editorMenu->addAction(_changeRendAct);
    _importAct = new QAction("Import", _editorMenu);
    _exportPNAct = new QAction("Petri Net", _editorMenu);
    _exportPNLAct = new QAction("Layout", _editorMenu);
    QObject::connect(_importAct,SIGNAL(triggered()), this, SLOT(importing()));
    QObject::connect(_exportPNAct,SIGNAL(triggered()), this, SLOT(exportPn()));
    QObject::connect(_exportPNLAct,SIGNAL(triggered()), this, SLOT(exportPNL()));
    _editorMenu->addAction(_importAct);
    auto importMenu = _editorMenu->addMenu("Export");
    importMenu->addAction(_exportPNAct);
    importMenu->addAction(_exportPNLAct);
    _modeMenu = _editorMenu->addMenu("Mode");
    _viewAct = new QAction("View", _modeMenu);
    _moveAct = new QAction("Move", _modeMenu);
    _editAct = new QAction("Edit", _modeMenu);
    QObject::connect(_viewAct,SIGNAL(triggered()), this, SLOT(setViewMode()));
    QObject::connect(_moveAct,SIGNAL(triggered()), this, SLOT(setMoveMode()));
    QObject::connect(_editAct,SIGNAL(triggered()), this, SLOT(setEditMode()));
    _modeMenu->addAction(_viewAct);
    _modeMenu->addAction(_moveAct);
    _modeMenu->addAction(_editAct);

    _tabWidget = new QTabWidget(_centralWidget);
    _tabWidget->setTabsClosable(true);
    QObject::connect(_tabWidget,SIGNAL(tabCloseRequested(int)), this, SLOT(tabClosed(int)));
    QObject::connect(_tabWidget,SIGNAL(currentChanged(int)), this, SLOT(tabChanged(int)));
    
    
    //QWidget* myTabWidgetContents = new QWidget();
    //_tabWidget->addTab(myTabWidgetContents, "PNLayoytExample.pnl");
    
   
    auto horizontalLayout = new QHBoxLayout(_centralWidget);//QHBoxLayout
    horizontalLayout->setSpacing(6);
    horizontalLayout->setContentsMargins(11, 11, 11, 11);
    horizontalLayout->addWidget(_tabWidget);

    // создание тулбокса
    _dockToolBox = new QDockWidget(_centralWidget);
    horizontalLayout->addWidget(_dockToolBox);
    _dockToolBox->setMaximumWidth(150);
    _dockToolBox->setMinimumWidth(150);
    QWidget* dockToolBoxContents = new QWidget(_dockToolBox);
    _dockToolBox->setWindowTitle("ToolBox");
    _dockToolBox->setWidget(dockToolBoxContents);

    auto toolBox = new QToolBox(dockToolBoxContents);
    toolBox->setMaximumSize(150,200);
    toolBox->setMinimumSize(150,200);
    QWidget* tools = new QWidget(toolBox);
    tools->setGeometry(QRect(0, 0, 98, 28));

    _addPosButton = new QPushButton("Add place", tools);
    _addTransButton = new QPushButton("Add transition", tools);
    _addingEdgesCheckBox = new QCheckBox("Adding edges",tools);
    QObject::connect(_addPosButton, SIGNAL(clicked()),
        this, SLOT(pushAddPosButton()));
    QObject::connect(_addTransButton, SIGNAL(clicked()),
        this, SLOT(pushAddTransButton()));
    QObject::connect(_addingEdgesCheckBox, SIGNAL(stateChanged(int)),
        this, SLOT(allowAddingEdges(int)));
    auto verticalLayout = new QVBoxLayout(tools);
    verticalLayout->setSpacing(6);
    verticalLayout->setContentsMargins(11, 11, 11, 11);
    verticalLayout->addWidget(_addPosButton);
    verticalLayout->addWidget(_addTransButton);
    verticalLayout->addWidget(_addingEdgesCheckBox);
    toolBox->addItem(tools, "Options");

    // создание менеджеров
    _PNManager = new PetriNetsManager;
    _PNLManager = new PNGraphicalLayoutsManager;
    //создание менеджера рендереров и регистрация всех известных рендереров
    _rendManager = new PNRenderersManager(new PNRendererDefaultImpl); 
    _rendManager->registerRenderer(new PNRendererWithLogData);
    
    _vertDist = defaultVertDist;
    _horizDist = defaultHorizDist;
}

//-----------------------------------------------------------------------------
// Destructor of the class
//-----------------------------------------------------------------------------
PNEditor::~PNEditor()
{
    delete _rendManager;
    delete _centralWidget;
    delete _editorMenu;
}

//-----------------------------------------------------------------------------
// Imports and visualize given PetriNet
//-----------------------------------------------------------------------------
QWidget* PNEditor::import(VTMinePetriNet* pn) // добвавить рисовалку сети из одного перехода
{
    if(!pn)
        return nullptr;
    _PNManager->registerPN(pn);
    _curGrLayout = new PNGraphicalLayout(pn, _rendManager->getDefaultRenderer());
    _curGrLayout->setName("newLayout.pnl");
    createNewTab(_curGrLayout);

    auto id = _curGrLayout->getRendererId();
    auto rec1 = _rendManager->getRendererPosDefaultRect(_curGrLayout->getRendererId());
    auto rec2 = _rendManager->getRendererTransDefaultSizeRect(_curGrLayout->getRendererId());
    qreal wid = 0;
    qreal hig = 0;
    if (rec1.height() < rec2.height())
        hig = rec2.height();
    else
        hig = rec1.height();
    if (rec1.width() < rec2.width())
        wid = rec2.width();
    else
        wid = rec1.width();

    // дальше пошла визуализация
    auto PN = _curGrLayout->getPN();
    int numEl = pn->getPositions().size() + pn->getTransitions().size();
    _grid = Grid(numEl, _horizDist + wid, _vertDist + hig);

    std::vector<PositionWithPtr*> notDrawnPos;
    // попытка найти входную позицию
    bool findIn = false;
    for(auto i = PN->getPositions().begin(); i != PN->getPositions().end(); ++i)
    {
        PositionWithPtr* pos = *i;
        auto edgesToPos = PN->getToPosEdges(pos);
        
        if(edgesToPos.size() == 0)
        {
            findIn = true;
            notDrawnPos.push_back(pos);
            break;
        }
    }


    QSet<PositionWithPtr*> allNotDrawnPos;
    QSet<TransitionWithPtr*> allNotDrawnTrans;
    for (auto i = PN->getPositions().begin(); i != PN->getPositions().end(); ++i)
        allNotDrawnPos.insert(*i);
    for (auto i = PN->getTransitions().begin(); i != PN->getTransitions().end(); ++i)
        allNotDrawnTrans.insert(*i);


    if(!findIn)
        notDrawnPos.push_back(PN->getPositions().front());
    drawPos(notDrawnPos, numEl, allNotDrawnPos, allNotDrawnTrans);

    if(!allNotDrawnPos.isEmpty())
    {
        auto notDrawn = allNotDrawnPos.toList();
        for (auto i = notDrawn.begin(); i != notDrawn.end(); ++i)
        {
            QPointF coordPoint = _grid.getPoint(numEl);
            auto pItem = _curGrLayout->addPos(*i, QRectF(coordPoint, coordPoint + QPointF(1,1)));
        }
    }

    if(!allNotDrawnTrans.isEmpty())
    {
        auto notDrawn = allNotDrawnTrans.toList();
        for (auto i = notDrawn.begin(); i != notDrawn.end(); ++i)
        {
            QPointF coordPoint = _grid.getPoint(numEl);
            auto pItem = _curGrLayout->addTrans(*i, QRectF(coordPoint, coordPoint + QPointF(1,1)));
        }
    }

    //рисует рёбра
    for(auto i = PN->getPosToEdges().begin(); i != PN->getPosToEdges().end(); ++i)
    {
        auto edgeGrI = _curGrLayout->addEdge(i->second);
        edgeGrI->rearrange();
    }
    return _centralWidget;
}

//-----------------------------------------------------------------------------
// Imports given PNGraphicalLayout
//-----------------------------------------------------------------------------
QWidget* PNEditor::import(PNGraphicalLayout* layout)
{
    if(!layout)
        return nullptr;
    _PNLManager->registerPNGrLayout(layout);
    _curGrLayout = new PNGraphicalLayout(layout);
    createNewTab(_curGrLayout);
    //_graphicsView->setGrLayout(_grLayout);
    return _centralWidget;
}

//-----------------------------------------------------------------------------
// Exports PetriNet
//-----------------------------------------------------------------------------
PNGraphicalLayout* PNEditor::exportLayout()
{
    _PNLManager->registerPNGrLayout(_curGrLayout);
    

    return _curGrLayout;
}

//-----------------------------------------------------------------------------
// Exports PNGraphicalLayout
//-----------------------------------------------------------------------------
VTMinePetriNet* PNEditor::exportPN()
{
    _PNManager->registerPN(_curGrLayout->getPN());
    return _curGrLayout->getPN();
}

//-----------------------------------------------------------------------------
// Sets distance between PetriNet items on y axis
//-----------------------------------------------------------------------------
void PNEditor::setVertDist(qreal dist)
{
    _vertDist = dist;
}

//-----------------------------------------------------------------------------
// Sets distance between PetriNet items on x axis 
//-----------------------------------------------------------------------------
void PNEditor::setHorizDist(qreal dist)
{
    _horizDist = dist;
}

//-----------------------------------------------------------------------------
// Returns distance between PetriNet items on y axis
//-----------------------------------------------------------------------------
qreal PNEditor::getVertDist()
{
    return _vertDist;
}

//-----------------------------------------------------------------------------
// Returns distance between PetriNet items on x axis
//-----------------------------------------------------------------------------
qreal PNEditor::getHorizDist()
{
    return _horizDist;
}

//-----------------------------------------------------------------------------
// Returns main menu of the PNEditor
//-----------------------------------------------------------------------------
QMenu* PNEditor::getMenu()
{
    return _editorMenu;
}

//-----------------------------------------------------------------------------
// Draws given Positions in the given column
//-----------------------------------------------------------------------------
void PNEditor::drawPos(std::vector<PositionWithPtr*>& notDrawn, int curCol, QSet<PositionWithPtr*>& allNotDrawnPos, QSet<TransitionWithPtr*>& allNotDrawnTrans)
{
    if(notDrawn.size() <= 0)
        return;

    std::vector <TransitionWithPtr*> beforeTrans;
    std::vector <TransitionWithPtr*> afterTrans;

    beforeTrans.clear();
    afterTrans.clear();
    auto PN = _curGrLayout->getPN();

    for(int i = 0; i < notDrawn.size(); i++)
    {
        //QString convStr = QString::fromStdString(notDrawn[i]->getName());
        QPointF coordPoint = _grid.getPoint(curCol);
        auto pItem = _curGrLayout->addPos(notDrawn[i],QRectF(coordPoint, coordPoint + QPointF(1,1)));
        allNotDrawnPos.erase(allNotDrawnPos.find(notDrawn[i]));

        auto posEdges = PN->getPosEdges(notDrawn[i]);
        for(auto j = posEdges.begin(); j != posEdges.end(); ++j)
        {
            if((*j)->getDir() == EdgeWithPtr::fromPosToTrans)
                if(allNotDrawnTrans.contains((*j)->getTrans()))
                    afterTrans.push_back((*j)->getTrans());

            if((*j)->getDir() == EdgeWithPtr::fromTransToPos)
                if(allNotDrawnTrans.contains((*j)->getTrans()))
                    beforeTrans.push_back((*j)->getTrans());
        }
    }

    drawTrans(afterTrans, curCol + 1, allNotDrawnPos, allNotDrawnTrans);
    drawTrans(beforeTrans, curCol - 1, allNotDrawnPos, allNotDrawnTrans);
    //drawTrans(afterTrans, curCol + 1);
}

//-----------------------------------------------------------------------------
// Draws given Transitions in the given column
//-----------------------------------------------------------------------------
void PNEditor::drawTrans(std::vector<TransitionWithPtr*>& notDrawn, int curCol, QSet<PositionWithPtr*>& allNotDrawnPos, QSet<TransitionWithPtr*>& allNotDrawnTrans)
{
    if(notDrawn.size() <= 0)
        return;

    std::vector <PositionWithPtr*> beforePos;
    std::vector <PositionWithPtr*> afterPos;
    beforePos.clear();
    afterPos.clear();
    auto PN = _curGrLayout->getPN();
    for(int i = 0;i < notDrawn.size(); i++)
    {
        QPointF coordPoint = _grid.getPoint(curCol);
        auto tItem = _curGrLayout->addTrans(notDrawn[i], QRectF(coordPoint, coordPoint + QPointF(1,1)));
        allNotDrawnTrans.erase(allNotDrawnTrans.find(notDrawn[i]));

        auto transEdges = PN->getTransEdges(notDrawn[i]);
        for (auto j = transEdges.begin(); j != transEdges.end(); ++j)
        {
            if((*j)->getDir() == EdgeWithPtr::fromTransToPos)
            {
                if (allNotDrawnPos.contains((*j)->getPos()))
                    afterPos.push_back((*j)->getPos());
            }
            if((*j)->getDir() == EdgeWithPtr::fromPosToTrans)
            {
                if(allNotDrawnPos.contains((*j)->getPos()))
                    beforePos.push_back((*j)->getPos());
            }
        }
    }

    drawPos(afterPos, curCol + 1, allNotDrawnPos, allNotDrawnTrans);
    drawPos(beforePos, curCol - 1, allNotDrawnPos, allNotDrawnTrans);
    //drawPos(afterPos, curCol + 1);
}

//-----------------------------------------------------------------------------
// Creates new tab in tab widget with PNGaphicsView and the given PNGraphicalLayout
//-----------------------------------------------------------------------------
void PNEditor::createNewTab(PNGraphicalLayout* pnl)
{
    QWidget* myTabWidgetContents = new QWidget();
    
    //_tabWidget->setCurrentIndex(curIndex);
    

    auto horizontalLayout = new QHBoxLayout(myTabWidgetContents);
    horizontalLayout->setSpacing(6);
    horizontalLayout->setContentsMargins(11, 11, 11, 11);
    auto graphicsView = new PNGraphicsView(pnl, myTabWidgetContents);
    _curGrView = graphicsView;
    _tabToView.insert(myTabWidgetContents, _curGrView);
    horizontalLayout->addWidget(graphicsView);
    _tabWidget->addTab(myTabWidgetContents, pnl->getName());
    
}
/*
void PNEditor::drawPos(PNLayout* layout)
{
    auto positions = layout->getPN()->getPositions();
    for (auto i = positions.begin(); i != positions.end(); ++i)
    {
        _grLayout->addPos(i->second, layout->getCoord(i->second));
    }
}
void PNEditor::drawTrans(PNLayout* layout)
{
    auto transitions = layout->getPN()->getTransitions();
    for (auto i = transitions.begin(); i != transitions.end(); ++i)
    {
        _grLayout->addTrans(i->second, layout->getCoord(i->second));
    }
}
*/

//-----------------------------------------------------------------------------
// Adding new Position slot
//-----------------------------------------------------------------------------
void PNEditor::pushAddPosButton()
{
    bool ok;
    QWidget wid;
    QString text = QInputDialog::getText(&wid, "Enter position name", "Position name", QLineEdit::Normal, QString(), &ok);


    if(ok)
    {
        IPNBaseData::IPNBaseDataPtr data(new PNBaseDataDefaultImpl(text));
        PositionWithPtr* pos = _curGrLayout->getPN()->addPos(data);
        QRectF coords(0,0,10,10);
        if(_curGrLayout->addPos(pos, coords) == nullptr)
        {
            QMessageBox msgBox;
            msgBox.setText(tr("Position with this name exists.\n"
                "Position have not been added.\n"
                "Try again"));
            msgBox.exec();
        }

    }

}

//-----------------------------------------------------------------------------
// Adding new Transition slot
//-----------------------------------------------------------------------------
void PNEditor::pushAddTransButton()
{
    bool ok;
    QWidget wid;
    QString text = QInputDialog::getText(&wid, "Enter Transition name", "Transition name", QLineEdit::Normal, QString(), &ok);


    if(ok)
    {
        IPNBaseData::IPNBaseDataPtr data(new PNBaseDataDefaultImpl(text));
        TransitionWithPtr* trans = _curGrLayout->getPN()->addTrans(data);
        QRectF coords(0,0,10,10);
        if(_curGrLayout->addTrans(trans, coords) == nullptr)
        {
            QMessageBox msgBox1;
            msgBox1.setText(tr("Transition with this name exists.\n"
                "Transition have not been added.\n"
                "Try again"));
            msgBox1.exec();
        }

    }

}

//-----------------------------------------------------------------------------
// Allowing/forbiding adding new edges slot
//-----------------------------------------------------------------------------
void PNEditor::allowAddingEdges(int state)
{
    if(state == Qt::Checked)
    {
        _curGrView->setAddingEdgesAllowed(true);
    }
    else
    {
        _curGrView->setAddingEdgesAllowed(false);
    }
}

//-----------------------------------------------------------------------------
// Setting PNEditor in View mode slot
//-----------------------------------------------------------------------------
void PNEditor::setViewMode()
{
    _addPosButton->setEnabled(false);
    _addTransButton->setEnabled(false);
    _addingEdgesCheckBox->setEnabled(false);
    _curGrLayout->setMode(PNGraphicalLayout::mdView);
}

//-----------------------------------------------------------------------------
// Setting PNEditor in Move mode slot
//-----------------------------------------------------------------------------
void PNEditor::setMoveMode()
{
    _addPosButton->setEnabled(false);
    _addTransButton->setEnabled(false);
    _addingEdgesCheckBox->setEnabled(false);
    _curGrLayout->setMode(PNGraphicalLayout::mdMove);
}

//-----------------------------------------------------------------------------
// Setting PNEditor in Edit mode slot
//-----------------------------------------------------------------------------
void PNEditor::setEditMode()
{
    _addPosButton->setEnabled(true);
    _addTransButton->setEnabled(true);
    _addingEdgesCheckBox->setEnabled(true);
    _curGrLayout->setMode(PNGraphicalLayout::mdEdit);
}

//-----------------------------------------------------------------------------
// Changing renderer of current PNGraphicalLayout slot
//-----------------------------------------------------------------------------
void PNEditor::changeRenderer()
{
    auto rendList = _rendManager->getListOfRenderers();
    QMap<QString, IVTMinePNRenderer*> nameToRend;
    QStringList rendNameList;
    for(auto i = rendList.begin(); i != rendList.end(); i++)
    {
        rendNameList.push_back((*i)->getName());
        nameToRend.insert((*i)->getName(), (*i));
    }

    QInputDialog* dialog = new QInputDialog(_centralWidget);
    dialog->setComboBoxItems(rendNameList);
    dialog->setOption(QInputDialog::UseListViewForComboBoxItems, true);
    dialog->setLabelText("Choose renderer:");
    
    if(dialog->exec())
    {
        auto rendName = dialog->textValue();
        auto rend = nameToRend[rendName];
        _curGrLayout->setRenderer(rend);
    }
}

//-----------------------------------------------------------------------------
// Import slot
//-----------------------------------------------------------------------------
void PNEditor::importing()
{
    auto pnList = _PNManager->getListOfPN();
    auto layoutList = _PNLManager->getListOfPNGrLayouts();
    QMap<QString, VTMinePetriNet*> nameToPN;
    QMap<QString, PNGraphicalLayout*> nameToLayout;
    QStringList namesList;
    for (auto i = pnList.begin(); i != pnList.end(); i++)
    {
        namesList.push_back((*i)->getName());
        nameToPN.insert((*i)->getName(), *i);
    }
    for (auto i = layoutList.begin(); i != layoutList.end(); i++)
    {
        namesList.push_back((*i)->getName());
        nameToLayout.insert((*i)->getName(), *i);
    }
    
    QInputDialog* dialog = new QInputDialog(_centralWidget);
    dialog->setComboBoxItems(namesList);
    dialog->setOption(QInputDialog::UseListViewForComboBoxItems, true);
    dialog->setLabelText("Import: ");

    if(dialog->exec())
    {
        auto name = dialog->textValue();
        auto pnIt = nameToPN.find(name);
        auto layIt = nameToLayout.find(name);
        if(pnIt == nameToPN.end())
        {
            import(layIt.value());
        }
        else
            import(pnIt.value());
    }

}

//-----------------------------------------------------------------------------
// Export current PetriNet slot
//-----------------------------------------------------------------------------
void PNEditor::exportPn()
{
    bool ok;
    QString name = QInputDialog::getText(_centralWidget, "Enter Petri net name", "Petri net name:", QLineEdit::Normal, QString(), &ok);
    name += ".pn";

    if(ok)
    {
        _curGrLayout->getPN()->setName(name);
        exportPN();
    }
}

//-----------------------------------------------------------------------------
// Export current PNGraphicalLayout slot
//-----------------------------------------------------------------------------
void PNEditor::exportPNL()
{
    bool ok;
    QString name = QInputDialog::getText(_centralWidget, "Enter Layout name", "Layout name:", QLineEdit::Normal, QString(), &ok);
    name += ".pnl";

    if(ok)
    {
        _curGrLayout->setName(name);
        exportLayout();
    }
}

//-----------------------------------------------------------------------------
// Tab page close slot
//-----------------------------------------------------------------------------
void PNEditor::tabClosed(int index)
{
    //_addPosButton->setParent(_centralWidget);
    //_addTransButton->setParent(_centralWidget);
    //_addingEdgesCheckBox->setParent(_centralWidget);
    if(!_PNManager->isRegistered(_curGrLayout->getPN()) || !_PNLManager->isRegistered(_curGrLayout))
    {
        // message box не забыть удалить петрю и лэйаут
        QMessageBox msgb(QMessageBox::Icon::Warning, QString("PNEditor"),
            QString("Current Petri net hasn't been exported.\nDo you want to export current Petri net?"),
            QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
        int ret = msgb.exec();
        switch (ret)
        {
        case QMessageBox::Yes:
            {
                bool ok;
                QString name = QInputDialog::getText(_centralWidget, "Enter Petri net name", "Petri net name:", QLineEdit::Normal, QString(), &ok);
                name += ".pn";

                if(ok)
                {
                    _curGrLayout->getPN()->setName(name);
                    exportPN();
                }
                else
                    return;
                name = QInputDialog::getText(_centralWidget, "Enter Layout name", "Layout name:", QLineEdit::Normal, QString(), &ok);
                name += ".pnl";

                if(ok)
                {
                    _curGrLayout->setName(name);
                    exportLayout();
                }
                else
                    return;

            }
            break;
        case QMessageBox::No:
            {
                delete _curGrLayout->getPN();
                delete _curGrLayout;
            }
            break;
        case QMessageBox::Cancel:
            return;
            break;
        }
    }
    auto wid = _tabWidget->widget(index);
    _tabToView.remove(_tabWidget->widget(index));
    delete _tabWidget->widget(index);
    _tabWidget->removeTab(index);
    if(_tabWidget->count() <= 0)
    {
        _addPosButton->setEnabled(false);
        _addTransButton->setEnabled(false);
        _addingEdgesCheckBox->setEnabled(false);
    }
}

//-----------------------------------------------------------------------------
// Tab page changed slot
//-----------------------------------------------------------------------------
void PNEditor::tabChanged(int index) // здесь меняем кур
{
    if(_tabWidget->count() > 0)
    {
        if(_curGrLayout->mode() == PNGraphicalLayout::mdEdit )
        {
            _addPosButton->setEnabled(true);
            _addTransButton->setEnabled(true);
            _addingEdgesCheckBox->setEnabled(true);
        }
        auto tabPage = _tabWidget->widget(index);
        _curGrView = _tabToView[tabPage];
        _curGrLayout = _curGrView->getGrLayout();
    }

}