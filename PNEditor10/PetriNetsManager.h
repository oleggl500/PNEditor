#ifndef PETRINETSMANAGER_H

///////////////////////////////////////////////////////////////////////////////
/// \file
/// \brief Contains PetriNetsManager
/// \author Oleg Bulanov
/// \version 0.1.0
/// \date 20.08.2014
///////////////////////////////////////////////////////////////////////////////

#define PETRINETSMANAGER_H

#include "VTMinePetriNet.h"

/** \brief PNRenderersManager manages PetriNets 
  * 
  *
  *
*/
class PetriNetsManager
{
public:
    /** \brief Type definition for List of VTMinePetriNets */
    typedef std::list<VTMinePetriNet*> PNList;
public:
    // пока так, но думаю это не должно быть так
    ~PetriNetsManager()
    {
        for (auto i = _listOfPN.begin(); i != _listOfPN.end(); ++i)
        {
            delete *i;
        }
    }

    /** \brief Returns true if the given VTMinePetriNet has been already registered */
    bool isRegistered(VTMinePetriNet* pn)
    {
        for (auto i = _listOfPN.begin(); i != _listOfPN.end(); ++i)
            if (*i == pn)
                return true;
        return false;
    }

    /** \brief Registers VTMinePetriNet  */
    void registerPN(VTMinePetriNet* pn)
    {
        if(!isRegistered(pn))
            _listOfPN.push_back(pn);
    }

    /** \brief Returns List of VTMine PetriNets */
    PNList getListOfPN()
    {
        return _listOfPN;
    }
private:
    PNList _listOfPN;   ///< List of VTMinePetriNets
}; // class PetriNetsManager

#endif