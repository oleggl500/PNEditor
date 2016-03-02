#include "IPNBaseData.h"

//-----------------------------------------------------------------------------
// Constructs PNBaseDataDefaultImpl with empty QString name
//-----------------------------------------------------------------------------
PNBaseDataDefaultImpl::PNBaseDataDefaultImpl()
{
    _name = "";
}

//-----------------------------------------------------------------------------
// Constructs PNBaseDataDefaultImpl with with the given QString name
//-----------------------------------------------------------------------------
PNBaseDataDefaultImpl::PNBaseDataDefaultImpl(const QString& name)
{
    _name = name;
}

//-----------------------------------------------------------------------------
// Implements operator== function
//-----------------------------------------------------------------------------
//bool PNBaseDataDefaultImpl::operator==(const PNBaseDataDefaultImpl& comp)
//{
//    if (_name == comp._name)
//        return true;
//    return false;
//}
//-----------------------------------------------------------------------------
// Returns name of data
//-----------------------------------------------------------------------------
const QString& PNBaseDataDefaultImpl::getName() const
{
    return _name;
}

//-----------------------------------------------------------------------------
//Sets name of data
//-----------------------------------------------------------------------------
void PNBaseDataDefaultImpl::setName(const QString& name)
{
    _name = name; 
}