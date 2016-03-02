#ifndef PNGRAPHICALLAYOUTSMANAGER_H

///////////////////////////////////////////////////////////////////////////////
/// \file
/// \brief Contains PNGraphicalLayoutsManager
/// \author Oleg Bulanov
/// \version 0.1.0
/// \date 20.08.2014
///////////////////////////////////////////////////////////////////////////////

#define PNGRAPHICALLAYOUTSMANAGER_H

#include "PNGraphicalLayout.h"

/** \brief PNGraphicalLayoutsManager manages PNGraphicalLayouts 
  * 
  *
  *
*/
class PNGraphicalLayoutsManager
{
public:
    /** \brief Type definition for List of PNGraphicalLayouts */
    typedef std::list<PNGraphicalLayout*> PNGrLList;
public:
    // пока так, но думаю это не должно быть так
    ~PNGraphicalLayoutsManager()
    {
        for (auto i = _listOfPNL.begin(); i != _listOfPNL.end(); ++i)
        {
            delete *i;
        }
    }

    /** \brief Registers PNGraphicalLayout  */
    void registerPNGrLayout(PNGraphicalLayout* pnl)
    {
        if (!isRegistered(pnl))
            _listOfPNL.push_back(pnl);
    }

    /** \brief Returns true if the given PNGraphicalLayout has been already registered */
    bool isRegistered(PNGraphicalLayout* pnl)
    {
        for (auto i = _listOfPNL.begin(); i != _listOfPNL.end(); ++i)
        {
            if (pnl == *i)
                return true;
        }
        return false;
    }

    /** \brief Returns List of VTMine PetriNets */
    PNGrLList getListOfPNGrLayouts()
    {
        return _listOfPNL;
    }
private:
    PNGrLList _listOfPNL;   ///< List of PNGraphicalLayouts
}; // class PNGraphicalLayoutsManager

#endif