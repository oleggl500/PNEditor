#include "MainWindow.h"
#include <QtGui/QApplication>
#include "PNEditor.h"

VTMinePetriNet* createTestPN();

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    VTMinePetriNet* PN = createTestPN();
    PNEditor p;
    w.setCentralWidget(p.import(PN));
    w.menuBar()->addMenu(p.getMenu());
    //delete PN;


    
    return a.exec();
}



VTMinePetriNet* createTestPN()
{
    VTMinePetriNet* PN = new VTMinePetriNet();
    /*WF->addEdge(WF->addPos("in"),WF->addTrans("a"));
    WF->addEdge(WF->getTrans("a"), WF->addPos("p1"));
    WF->addEdge(WF->getPos("p1"),WF->addTrans("b"));
    WF->addEdge(WF->getTrans("b"), WF->addPos("p2"));
    WF->addEdge(WF->getPos("p2"),WF->addTrans("c"));
    WF->addEdge(WF->getTrans("c"), WF->addPos("p3"));
    WF->addEdge(WF->getPos("p2"),WF->addTrans("d"));
    WF->addEdge(WF->getTrans("d"), WF->getPos("p1"));
    WF->setInPosition(WF->getPos("in"));
    */
    typedef std::shared_ptr<PNBaseDataDefaultImpl> Data;
    PN->addEdge(PN->addPos(Data(new PNBaseDataDefaultImpl("in"))),PN->addTrans(std::shared_ptr<LogData>(new LogData("adding Pos"))));
    PN->addEdge(PN->searchTrans(std::shared_ptr<LogData>(new LogData("adding Pos"))),PN->addPos(Data(new PNBaseDataDefaultImpl("c1"))));


    /*PN->addEdge(PN->getTrans("a"),PN->addPos("c2"));
    PN->addEdge(PN->getPos("c1"),PN->addTrans("b"));
    PN->addEdge(PN->getPos("c1"),PN->addTrans("c"));
    PN->addEdge(PN->getPos("c2"),PN->addTrans("d"));

    PN->addEdge(PN->getTrans("b"),PN->addPos("out"));
    PN->addEdge(PN->getTrans("c"),PN->getPos("out"));
    PN->addEdge(PN->getTrans("d"),PN->getPos("out"));*/
    //PN->addEdge(PN->getTrans("d"),PN->addPos("c4"));
    //PN->addEdge(PN->getTrans("b"),PN->addPos("c3"));
    //PN->addEdge(PN->getTrans("c"),PN->getPos("c3"));
    //PN->addEdge(PN->getPos("c3"),PN->addTrans("e"));
    //PN->addEdge(PN->getPos("c4"),PN->getTrans("e"));
    //PN->addEdge(PN->getTrans("e"),PN->addPos("c5"));
    //PN->addEdge(PN->getPos("c5"),PN->addTrans("f"));
    //PN->addEdge(PN->getPos("c5"),PN->addTrans("g"));
    //PN->addEdge(PN->getPos("c5"),PN->addTrans("h"));
    ////PN->addEdge(PN->getTrans("f"),PN->getPos("c1"));
    ////PN->addEdge(PN->getTrans("f"),PN->getPos("c2"));
    //PN->addEdge(PN->getTrans("g"),PN->addPos("out"));
    //PN->addEdge(PN->getTrans("h"),PN->getPos("c2"));
    //PN->addEdge(PN->getTrans("h"),PN->getPos("out"));


    // TODO:
    //if(!WF->checkIntegrity())
    //гневное сообщение
    PN->setName("PN1.pn");
    return PN;
}