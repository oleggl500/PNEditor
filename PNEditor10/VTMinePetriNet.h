#ifndef VTMINEPETRINET_H

///////////////////////////////////////////////////////////////////////////////
/// \file
/// \brief Contains type definitions for special PetriNet that will be used in VTMine framework.
/// \author Oleg Bulanov
/// \version 0.1.0
/// \date 25.07.2014
///////////////////////////////////////////////////////////////////////////////

#define VTMINEPETRINET_H

#include "PetriNet.h"
#include "IPNBaseData.h"

/** \brief Type definition for PetriNet's Position with smart pointer data */
typedef xi::PetriNet::Position<IPNBaseData::IPNBaseDataPtr> PositionWithPtr;

/** \brief Type definition for PetriNet's Transition with smart pointer data */
typedef xi::PetriNet::Transition<IPNBaseData::IPNBaseDataPtr> TransitionWithPtr;

/** \brief Type definition for PetriNet's Edge with smart pointers data */
typedef xi::PetriNet::Edge<IPNBaseData::IPNBaseDataPtr, IPNBaseData::IPNBaseDataPtr, IPNBaseData::IPNBaseDataPtr> EdgeWithPtr;

/** \brief Special PetriNet that will be used in VTMine framework
*   
*  
*/
class VTMinePetriNet 
    : public xi::PetriNet::PetriNet<IPNBaseData::IPNBaseDataPtr, IPNBaseData::IPNBaseDataPtr, IPNBaseData::IPNBaseDataPtr>
{
public:
    /** \brief Constructs empty VTMinePetriNet */
    VTMinePetriNet() { }
    
    /** \brief Calls PetriNet constructor */
    VTMinePetriNet(VTMinePetriNet* pn)
        : xi::PetriNet::PetriNet<IPNBaseData::IPNBaseDataPtr, IPNBaseData::IPNBaseDataPtr, IPNBaseData::IPNBaseDataPtr>(pn) 
    {
        _name = pn->_name;
    }
    
    /** \brief Calls PetriNet constructor */
    VTMinePetriNet(const VTMinePetriNet& pn)
        : xi::PetriNet::PetriNet<IPNBaseData::IPNBaseDataPtr, IPNBaseData::IPNBaseDataPtr, IPNBaseData::IPNBaseDataPtr>(pn) 
    { 
        _name = pn._name;
    }

    /** \brief Returns name of the PetriNet */
    const QString& getName() const
    {
        return _name;
    }

    /** \brief Sets name of the PetriNet */
    void setName(const QString& name)
    {
        _name = name;
    }
private:
    QString     _name; ///< Name of PetriNet
}; // class VTMinePetriNet





#endif