#ifndef IPNBASEDATA_H

///////////////////////////////////////////////////////////////////////////////
/// \file
/// \brief Contains interface and default implementation of PetriNet base data.
/// \author Oleg Bulanov
/// \version 0.1.0
/// \date 25.07.2014
///////////////////////////////////////////////////////////////////////////////

#define IPNBASEDATA_H

#include <QString>



/** \brief Interface of PetriNet base data.
*   
*  PetriNet base data has to have name (QString) 
*/
class IPNBaseData 
{
public:
    /** \brief Type definition for smart pointer on IPNBaseDataPtr */
    typedef std::shared_ptr<IPNBaseData> IPNBaseDataPtr;
public:
    /** \brief Implements operator== function */
    bool operator==(const IPNBaseData& comp) 
    { 
        if(comp._name == _name)
            return true; 
        return false;
    }
public:
    /** \brief Returns name of data */
    virtual const QString& getName() const = 0;
    /** \brief Sets name of data */
    virtual void setName(const QString& name) = 0;
protected:
    QString _name; ///< Name of data

}; // class IPNBaseData


/** \brief Default implementation of PetriNet base data.
*   
*   
*/
class PNBaseDataDefaultImpl 
    : public IPNBaseData
{
public:
    /** \brief Constructs PNBaseDataDefaultImpl with empty string name */
    PNBaseDataDefaultImpl();
    /** \brief Constructs PNBaseDataDefaultImpl with with the given string name */
    PNBaseDataDefaultImpl(const QString& name);
public:
    /** \brief Returns name of data */
    const QString& getName() const;
    /** \brief Sets name of data */
    void setName(const QString& name); 
}; // class PNBaseDataDefaultImpl

#endif