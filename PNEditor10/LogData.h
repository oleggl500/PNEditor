#ifndef LOGDATA_H

///////////////////////////////////////////////////////////////////////////////
/// \file
/// \brief Contains PNRendererDef1 implementation.
/// \author Oleg Bulanov
/// \version 0.1.0
/// \date 18.08.2014
///////////////////////////////////////////////////////////////////////////////

#define LOGDATA_H

#include"IPNBaseData.h"
#include"qdatetime.h"

/** \brief Log data implementation
*   
*   
*/
class LogData : public IPNBaseData
{
public:
    //LogData() {}
    /** \brief Constructs LogData with the given name, timestamp and resource */
    LogData(const QString& name = "no name", const QDateTime& ts = QDateTime(QDate(2000,1,1)), const QString& res = "UNDEFINED");
public:
    /** \brief Returns name of the data */
    const QString& getName() const;

    /** \brief Returns timestamp of the data */
    const QDateTime& getTimestamp() const;

    /** \brief Returns resource of the data */
    const QString& getResource() const;

    /** \brief Sets timestamp of the data */
    void setTimestamp(const QDateTime& ts);

    /** \brief Sets resource of the data */
    void setResource(const QString& res);

    /** \brief Sets name of the data */
    void setName(const QString& name);

protected:
    QString     _name;      ///< Name of the data
private:
    QDateTime   _timestamp; ///< Timestamp of the data
    QString     _resource;  ///< Resource of the data
}; // class LogData

#endif