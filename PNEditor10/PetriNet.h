#ifndef PETRINET_H

///////////////////////////////////////////////////////////////////////////////
/// \file
/// \brief Contains default implementation of PetriNet and its components.
/// \author Oleg Bulanov
/// \version 0.1.0
/// \date 05.07.2014
///////////////////////////////////////////////////////////////////////////////

#define PETRINET_H

#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <iterator>
#include <map>
#include <fstream>
#include <utility>

//using namespace std;


namespace xi {
    namespace PetriNet {

        
        /** \brief Implementation of transition of Petri net.
        *   
        *  Template class Transition contains data of transition. The data can be different types.
        */
        template <class T>
        class Transition
        {
        public:
            /** \brief Constructs Transition with the given data */
            Transition(const T& data)
            {
                _data = data;
            }
            
            /** \brief Constructs Transition with the data of the Transition*/
            Transition(Transition* trans)
            {
                Transition(trans->getData());
            }
            
            /** \brief Copy constructor */
            Transition(const Transition& trans)
            {
                Transition( trans.getData() );
            }

            /** \brief Destructor of the class */
            virtual ~Transition() {}                     
        
        public:
            /** \brief Sets data of Transition */
            void setData(const T& data)
            {
                _data = data;
            }
            
            /** \brief Returns data of Transition */
            const T& getData() const { return _data; };
            
            /** \brief Returns data of Transition */
            T& getData() { return _data; };                 

        private:
            T _data; ///< Data of Transition                         

        }; // class Transition

        
        /** \brief Implementation of position of Petri net.
        *   
        *  Template class Position contains data of position. The data can be different types.
        */
        template <class T>
        class Position
        {
        public:
            /** \brief Constructs Position with the given data */
            Position(const T& data)
            {
                _data = data;
            }
            
            /** \brief Constructs Position with the data of the Position*/ 
            Position(Position* pos)
            {
                Position(pos->getData())
            }
            
            /** \brief Copy constructor */
            Position(const Position& pos)
            {
                Position(pos.getData());
            }
            /** \brief Destructor of the class */
            virtual ~Position() {}                      
        
        public:
            /** \brief Sets data of Position */
            void setData(const T& data)
            {
                _data = data;
            }
            
            /** \brief Returns data of Position */
            const T& getData() const { return _data; }     
            
            /** \brief Returns data of Position */
            T& getData() { return _data; }                 

        private:
            T _data; ///< Data of Position 

        }; // class Position


        /** \brief Implementation of edge of Petri net.
        *   
        *  Template class Edge contains data of Edge. The data can be different types.
        *  Class Edge also stores Position, Transition and direction (Dir) of the Edge
        */

        template<class TPos, class TTrans, class TEdge>
        class Edge
        {
        public:
            /** \brief Varieties of directions of Edges */
            enum Dir
            {
                fromPosToTrans,     ///< Edge from Position to Transition
                fromTransToPos      ///< Edge from Transition to Position
            }; // enum Dir
        
        public:
            /** \brief Constructs Edge with the given Position, Transition and direction (Dir) */
            Edge(Position<TPos>* pos, Transition<TTrans>* trans, Dir dir, const TEdge& data = TEdge()) 
            {
                _pos = pos;
                _trans = trans;
                _dir = dir;
                _data = data;
            }
        public:
            /** \brief Sets Position of the Edge */
            void setPos(Position<TPos>* pos)
            {
                _pos = pos;
            }

            /** \brief Sets Transition of the Edge */
            void setTrans(Transition<TTrans>* trans)
            {
                _trans = trans;
            }
            
            /** \brief Sets direction (Dir) of the Edge */
            void setDir(Dir dir)
            {
                _dir = dir;
            }

            /** \brief Sets data of the Edge */
            void setData(TEdge& data)
            {
                _data = data;
            }
        public:
            /** \brief Returns Position of the Edge */
            Position<TPos>* getPos()
            {
                return _pos;
            }
            
            /** \brief Returns Transition of the Edge */
            Transition<TTrans>* getTrans()
            {
                return _trans;
            }

            /** \brief Returns direction (Dir) of the Edge */
            Dir getDir()
            {
                return _dir;
            }

            /** \brief Returns data of Edge */
            const TEdge& getData() const { return _data; };
            
            /** \brief Returns data of Edge */
            TEdge& getData() { return _data; };

        private:
            Position<TPos>*     _pos;   ///< Position of the Edge         
            Transition<TTrans>* _trans; ///< Transition of the Edge   
            Dir                 _dir;   ///< Direction (Dir) of the Edge
            TEdge               _data;  ///< Data of the Edge

        }; // class Edge


        /** \brief Implementation of Petri net.
        *   
        *  PetriNet class stores list of Positions, list of Transitions and two
        *  maps of Edges.
        */

        //template <class TPos, class TTrans, class TEdge>
        template <class TPos, class TTrans, class TEdge>//, class TPosComparator = ElComparator<TPos> >
        class PetriNet
        {

        //protected:
        //    TPosComparator comp;
        //    TPos pos1;
        //    TPos pos2;

        //    if(comp.compare(pos1, pos2) )


        public:






            /** \brief Type definition for List of Positions */
            typedef std::list<Position<TPos>*> PosList;
            
            /** \brief Type definition for List of Transitions */
            typedef std::list<Transition<TTrans>*> TransList;
            
            /** \brief Type definition for Map from Position to Edges */
            typedef std::multimap<Position<TPos>*, Edge<TPos, TTrans, TEdge>*> PosToEdgeMap;
            
            /** \brief Type definition for Map from Transition to Edges */
            typedef std::multimap<Transition<TTrans>*, Edge<TPos, TTrans, TEdge>*> TransToEdgeMap;

            /** \brief Type definition for PetriNet Edges */
            typedef Edge<TPos, TTrans, TEdge> PNEdge;

            /** \brief Struct that identifies whether T is a shared_ptr type. */
            template<typename T>
            struct is_shared_ptr { static const bool value = false; };

            /** \brief Struct that identifies whether T is a shared_ptr type. */
            template<typename T>
            struct is_shared_ptr<std::shared_ptr<T>> { static const bool value = true; };

            /** \brief Struct that identifies whether T is a pointer type. */
            template<typename T>
            struct is_pointer { static const bool value = false; };

            /** \brief Struct that identifies whether T is a pointer type. */
            template<typename T>
            struct is_pointer<T*> { static const bool value = true; };
        public:
            /** \brief Constructs empty PetriNet */
            PetriNet() { }                         

            /** \brief Constructs PetriNet with the given PetriNet */
            PetriNet(PetriNet<TPos, TTrans, TEdge>* pn)
            {
                for ( auto i = pn->_positions.begin(); i != pn->_positions.end(); ++i )
                {
                    addPos((*i)->getData());
                }

                for ( auto i = pn->_transitions.begin(); i != pn->_transitions.end(); ++i )
                {
                    addTrans((*i)->getData());
                }

                for ( auto i = pn->_posToEdges.begin(); i != pn->_posToEdges.end(); ++i )
                {
                    auto posData = i->second->getPos()->getData();
                    auto transData = i->second->getTrans()->getData();
                    auto pos = searchPos(posData);
                    auto trans = searchTrans(transData);
                    addEdge(pos, trans, i->second->getDir(), i->second->getData());
                }
            }

            /** \brief Copy constructor */
            PetriNet(const PetriNet<TPos, TTrans, TEdge>& pn)
            {
                for ( auto i = pn._positions.begin(); i != pn._positions.end(); ++i )
                {
                    addPos((*i)->getData());
                }

                for ( auto i = pn._transitions.begin(); i != pn._transitions.end(); ++i )
                {
                    addTrans((*i)->getData());
                }

                for ( auto i = pn._posToEdges.begin(); i != pn._posToEdges.end(); ++i )
                {
                    auto posData = i->second->getPos()->getData();
                    auto transData = i->second->getTrans()->getData();
                    auto pos = searchPos(posData);
                    auto trans = searchTrans(transData);
                    addEdge(pos, trans, i->second->getDir(), i->second->getData());
                }
            }

            /** \brief Destructor of the class */
            ~PetriNet()
            {
                //cout << "Destructor of class PetriNet " << endl;
                clearNet();
            }

        public:
            /** \brief Clears PetriNet */
            void clearNet()
            {

                for (auto iter = _posToEdges.begin(); iter != _posToEdges.end(); ++iter)
                    delete iter->second;
                _posToEdges.clear();
                _transToEdges.clear();

                for (auto i = _positions.begin(); i != _positions.end(); i++)
                {
                    delete *i;
                }
                _positions.clear();

                for (auto i = _transitions.begin(); i != _transitions.end(); i++)
                {
                    delete *i;
                }
                _transitions.clear();
            }

        public:
            /** \brief Returns list of Positions of the PetriNet */
            const PosList& getPositions()
            {
                return _positions;
            }

            /** \brief Returns list of Transitions of the PetriNet */
            const TransList& getTransitions()
            {
                return _transitions;
            }

            /** \brief Returns map from Position to Edges of the PetriNet*/
            const PosToEdgeMap& getPosToEdges()
            {
                return _posToEdges;
            }

            /** \brief Returns map from Transition to Edges of the PetriNet*/
            const TransToEdgeMap& getTransToEdges()
            {
                return _transToEdges;
            }

        public:
                // TODO: появляется тип данных T:
            
            /** \brief Adds Position to the PetriNet with the given data*/
            Position<TPos>* addPos(const TPos& data)
            {
                if (searchPos(data) == nullptr)
                {
                    Position<TPos>* pos = new Position<TPos>(data);
                    _positions.push_back(pos);
                    return pos;
                }
                return nullptr;
            }
            
            /** \brief Adds the given Position to the PetriNet*/
            Position<TPos>* addPos(Position<TPos>* pos)
            {
                if (searchPos(pos->getData()) == nullptr)
                {
                    _positions.push_back(pos);
                    return pos;
                }
                return nullptr;            
            }

            /** \brief Finds Position in PetriNet with given data. TPos has to have operator== overloading.
            *  Returns nullptr if Position with the given data has not been found.
            */
            Position<TPos>* searchPos(const TPos& data)
            {
                for ( auto i = _positions.begin(); i != _positions.end(); i++ )
                {
                    if(is_shared_ptr<TPos>::value)
                        if(*(*i)->getData() == *data)
                            return (*i);
                    if(is_pointer<TPos>::value)
                    {
                        if(*(*i)->getData() == *data)
                            return (*i);
                    }   
                    else
                        if((*i)->getData() == data)
                            return (*i);
                }
                return nullptr;
            }


        public:
            /** \brief Adds Transition to the PetriNet with the given data */
            Transition<TTrans>* addTrans(const TTrans& data)
            {
                if (searchTrans(data) == nullptr)
                {
                    Transition<TTrans>* trans = new Transition<TTrans>(data);
                    _transitions.push_back(trans);
                    return trans;
                }
                return nullptr;
            }

            /** \brief Adds the given Transition to the PetriNet*/
            Transition<TTrans>* addTrans(Transition<TTrans>* trans)
            {
                if (searchTrans(trans->getData()) == nullptr)
                {
                    _transitions.push_back(trans);
                    return trans;
                }
                return nullptr;    
            }
            
            /** \brief Finds Transition in PetriNet with given data. TTrans has to have operator== overloading.
            *  Returns nullptr if Transition with given data has not been found.
            */
            Transition<TTrans>* searchTrans(const TTrans& data)
            {
                for ( auto i = _transitions.begin(); i != _transitions.end(); ++i )
                {
                    if(is_shared_ptr<TTrans>::value)
                        if(*(*i)->getData() == *data)
                            return (*i);
                    if(is_pointer<TTrans>::value)
                    {
                        if(*(*i)->getData() == *data)
                        {
                            return (*i);
                        }
                    }
                    else
                        if(*(*i)->getData() == *data)
                        {
                            return (*i);
                        }

                }
                return nullptr;
            }
            
        public:
            /** \brief Removes Position from the PetriNet */
            void removePos(Position<TPos>* pos)
            {
                for ( auto j = _positions.begin(); j != _positions.end(); ++j )
                {
                    if ((*j) == pos)
                    {
                        // удаляем все рёбра связанные с вершиной из 2х мапов
                        removePosEdges(pos);
                        delete pos;
                        _positions.erase(j);
                        break;
                    }
                }
            }

            /** \brief Removes Edges with the given Position from the PetriNet */
            void removePosEdges(Position<TPos>* pos)
            {
                // удаляем все рёбра связанные с вершиной из 2х мапов
                auto retPos = _posToEdges.equal_range(pos);
                for ( auto iter = retPos.first; iter != retPos.second; ++iter)
                {
                    auto temp = iter->second->getTrans();
                    auto retTr = _transToEdges.equal_range(temp);
                    for ( auto i = retTr.first; i != retTr.second; ++i)
                        if (i->second->getPos() == pos)
                        {
                            delete i->second;
                            _transToEdges.erase(i);
                            break;
                        }
                }
                _posToEdges.erase(retPos.first, retPos.second);
            }

            /** \brief Removes Transition from the PetriNet */
            void removeTrans(Transition<TTrans>* trans)
            {
                for ( auto j = _transitions.begin(); j != _transitions.end(); ++j )
                {
                    if ((*j) == trans)
                    {
                        
                        delete trans;
                        _transitions.erase(j);
                        break;
                    }
                }
            }

            /** \brief Removes Edges with the given Transition from the PetriNet */
            void removeTransEdges(Transition<TTrans>* trans)
            {
                // удаляем все рёбра связанные с вершиной из 2х мапов
                auto retTrans = _transToEdges.equal_range(trans);
                for ( auto iter = retTrans.first; iter != retTrans.second; ++iter)
                {
                    auto temp = iter->second->getPos();
                    auto retPos = _posToEdges.equal_range(temp);
                    for ( auto i = retPos.first; i != retPos.second; ++i)
                        if (i->second->getTrans() == trans)
                        {
                            delete i->second;
                            _posToEdges.erase(i);
                            break;
                        }
                }
                _transToEdges.erase(retTrans.first, retTrans.second);
            }

            /** \brief Removes Edge (from the given Position to the given Transition) from the PetriNet */
            void removeEdge(Position<TPos>* pos, Transition<TTrans>* trans)
            {
                auto fromTo = _posToEdges.equal_range(pos);
                for ( auto i = fromTo.first; i != fromTo.second; ++i )
                {
                    if (i->second->getTrans() == trans && i->second->getDir() == PNEdge::Dir::fromPosToTrans)
                    {
                        removeEdge(i->second);
                        break;
                    }
                }
            }

            /** \brief Removes Edge (from the given Transition to the given Position) from the PetriNet */
            void removeEdge(Transition<TPos>* trans, Position<TTrans>* pos)
            {
                auto fromTo = _posToEdges.equal_range(pos);
                for ( auto i = fromTo.first; i != fromTo.second; ++i )
                {
                    if (i->second->getTrans() == trans && i->second->getDir() == PNEdge::Dir::fromTransToPos)
                    {
                        removeEdge(i->second);
                        break;
                    }
                }
            }

            /** \brief Removes the given Edge from the PetriNet */
            void removeEdge(PNEdge* edge)      // TODO: реализовать и свести верхние два к этому
            {
                auto delIt1 = _posToEdges.equal_range(edge->getPos());
                for ( auto i = delIt1.first; i != delIt1.second; ++i )
                {
                    if (i->second == edge)
                    {
                        _posToEdges.erase(i);
                        break;
                    }
                }

                auto delIt2 = _transToEdges.equal_range(edge->getTrans());
                for ( auto i = delIt2.first; i != delIt2.second; ++i )
                {
                    if (i->second == edge)
                    {
                        _transToEdges.erase(i);
                        break;
                    }
                }
                delete edge;
            }

                // TODO: методы, возвращающие для данной позиции список всех входящих/И-ИЛИ/исходящих ребер:
                // 1) методы нужны!
                // 2) названия д.б. адекватные!
                // 3) добавить недостающие два метода

        public:
            /** \brief Returns  Edges that contains the given Position */
            std::vector<PNEdge*> getPosEdges(Position<TPos>* pos)
            {
                auto fromTo = _posToEdges.equal_range(pos);
                std::vector<PNEdge*> vecEdges;
                for ( auto i = fromTo.first; i != fromTo.second; ++i )
                {
                    vecEdges.push_back(i->second);
                }
                return vecEdges;
            }
            
            /** \brief Returns  Edges that contains the given Transition */
            std::vector<PNEdge*> getTransEdges(Transition<TTrans>* trans)
            {
                auto fromTo = _transToEdges.equal_range(trans);
                std::vector<PNEdge*> vecEdges;
                for ( auto i = fromTo.first; i != fromTo.second; ++i )
                {
                    vecEdges.push_back(i->second);
                }
                return vecEdges;
            }

            /** \brief Returns  Edges that contains the given Position and Dir is equal fromPosToTrans */
            std::vector<PNEdge*> getFromPosEdges(Position<TPos>* pos)
            {
                auto fromTo = _posToEdges.equal_range(pos);
                std::vector<PNEdge*> vecEdges;
                for ( auto i = fromTo.first; i != fromTo.second; ++i )
                {
                    if(i->second->getDir() == PNEdge::fromPosToTrans)
                        vecEdges.push_back(i->second);
                }
                return vecEdges;
            }

            /** \brief Returns  Edges that contains the given Position and Dir is equal fromTransToPos */
            std::vector<PNEdge*> getToPosEdges(Position<TPos>* pos)
            {
                auto fromTo = _posToEdges.equal_range(pos);
                std::vector<PNEdge*> vecEdges;
                for ( auto i = fromTo.first; i != fromTo.second; ++i )
                {
                    if(i->second->getDir() == PNEdge::fromTransToPos)
                        vecEdges.push_back(i->second);
                }
                return vecEdges;
            }

            /** \brief Returns  Edges that contains the given Transition and Dir is equal fromTransToPos */
            std::vector<PNEdge*> getFromTransEdges(Transition<TTrans>* trans)
            {
                auto fromTo = _transToEdges.equal_range(trans);
                std::vector<PNEdge*> vecEdges;
                for ( auto i = fromTo.first; i != fromTo.second; ++i )
                {
                    if(i->second->getDir() == PNEdge::fromTransToPos)
                        vecEdges.push_back(i->second);
                }
                return vecEdges;
            }

            /** \brief Returns  Edges that contains the given Transition and Dir is equal fromPosToTrans */
            std::vector<PNEdge*> getToTransEdges(Transition<TTrans>* trans)
            {
                auto fromTo = _transToEdges.equal_range(trans);
                std::vector<PNEdge*> vecEdges;
                for ( auto i = fromTo.first; i != fromTo.second; ++i )
                {
                    if(i->second->getDir() == PNEdge::fromPosToTrans)
                        vecEdges.push_back(i->second);
                }
                return vecEdges;
            }

        public:
            /** \brief Adds Edge (from the given Position to given Transition) to the PetriNet with the given data */
            PNEdge* addEdge(Position<TPos>* pos, Transition<TTrans>* trans, const TEdge& data = TEdge())
            {
                PNEdge* newEdge = new PNEdge(pos, trans, PNEdge::fromPosToTrans, data);
                return addEdge(newEdge);
            }
            
            /** \brief Adds Edge (from the given Transition to given Position) to the PetriNet with the given data */
            PNEdge* addEdge(Transition<TTrans>* trans, Position<TPos>* pos, const TEdge& data = TEdge())
            {
                PNEdge* newEdge = new PNEdge(pos, trans, PNEdge::fromTransToPos, data);
                return addEdge(newEdge);
            }

            /** \brief Adds Edge to the PetriNet with the given Position, Transition, direction (Dir), data */
            PNEdge* addEdge(Position<TPos>* pos, Transition<TTrans>* trans, typename PNEdge::Dir dir, const TEdge& data = TEdge())
            {
                PNEdge* newEdge = new PNEdge(pos, trans, dir, data);
                return addEdge(newEdge);
            }

            /** \brief Adds new Edge to the PetriNet with infomation from the given Edge */
            PNEdge* addEdge(PNEdge* edge)
            {
                auto pos = edge->getPos();
                auto trans = edge->getTrans();
                if (searchPos(pos->getData()) == nullptr)
                    return nullptr;
                if (searchTrans(trans->getData()) == nullptr)
                    return nullptr;
                auto pairPE = std::pair<Position<TPos>*, PNEdge*> (pos, edge);
                auto pairTE = std::pair<Transition<TTrans>*, PNEdge*> (trans, edge);
                _posToEdges.insert(pairPE);
                _transToEdges.insert(pairTE);
                return edge;
            }

            /** \brief Finds Edge in PetriNet with the given Position, Transition and direction (Dir).
            *  Returns nullptr if Edge with given parameters has not been found.
            */
            PNEdge* searchEdge(Position<TPos>* pos, Transition<TTrans>* trans, typename PNEdge::Dir dir)
            {
                auto edgesWithPos = _posToEdges.equal_range(pos);
                for(auto i = edgesWithPos.first; i != edgesWithPos.second; ++i)
                {
                    if(i->second->getPos() == pos && i->second->getTrans() == trans && i->second->getDir() == dir)
                    {
                        return i->second;
                    }
                }
                return nullptr;
            }

        public:
            /** \brief Replaces the given Position data with the given data*/
            //void changePosData(Position<TPos>* pos, TPos& data);

            /** \brief Replaces the given Transition data with the given data*/
            //void changeTransData(Transition<TTrans>* trans, TTrans& data);
        

        private:
            PosList         _positions;     ///< List of Positions 
            TransList       _transitions;   ///< List of Transitions
            PosToEdgeMap    _posToEdges;    ///< Map from Position to Edges that contains the Position
            TransToEdgeMap  _transToEdges;  ///< Map from Transition to Edges that contains the Transition

        };

    }; // namespace PetriNet 
}; // namespace xi 


#endif

