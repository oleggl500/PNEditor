#include "LogData.h"

//=============================================================================
// class LogData
//=============================================================================

//-----------------------------------------------------------------------------
// Constructs LogData with the given name, timestamp and resource
//-----------------------------------------------------------------------------
LogData::LogData(const QString& name, const QDateTime& ts, const QString& res)
{
    _name = name;
    _timestamp = ts;
    _resource = res;
}

//-----------------------------------------------------------------------------
// Returns name of the data
//-----------------------------------------------------------------------------
const QString& LogData::getName() const
{
    return _name;
}

//-----------------------------------------------------------------------------
// Returns timestamp of the data
//-----------------------------------------------------------------------------
const QDateTime& LogData::getTimestamp() const
{
    return _timestamp;
}

//-----------------------------------------------------------------------------
// Returns resource of the data
//-----------------------------------------------------------------------------
const QString& LogData::getResource() const
{
    return _resource;
}

//-----------------------------------------------------------------------------
// Sets timestamp of the data
//-----------------------------------------------------------------------------
void LogData::setTimestamp(const QDateTime& ts)
{
    _timestamp = ts;
}

//-----------------------------------------------------------------------------
// Sets resource of the data
//-----------------------------------------------------------------------------
void LogData::setResource(const QString& res)
{
    _resource = res;
}

//-----------------------------------------------------------------------------
// Sets name of the data
//-----------------------------------------------------------------------------
void LogData::setName(const QString& name)
{
    _name = name;
}