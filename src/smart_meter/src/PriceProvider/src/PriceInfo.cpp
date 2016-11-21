

#include "PriceInfo.h"
#include <cassert>
#include <sstream>

namespace spark
{

PriceInfo::PriceInfo():
    m_hourPrice(0.0),
    m_timeLimit(0),
    m_resolution(0)
{
}


PriceInfo::PriceInfo(float pricePerHour, int timeLimit, int resolution):
    m_hourPrice(pricePerHour),
    m_timeLimit(timeLimit),
    m_resolution(resolution)
{
    assert(timeLimit >= 0 && resolution > 0);
}


float PriceInfo::pricePerHour() const
{
    return m_hourPrice;
}

int PriceInfo::timeLimit() const
{
    return m_timeLimit;
}

int PriceInfo::timeResolution() const
{
    return m_resolution;
}

bool PriceInfo::isValid() const
{
    return m_resolution != 0;
}

std::string PriceInfo::toString() const
{
    std::ostringstream oss;
    oss << m_hourPrice << ";" << m_timeLimit << ";" << m_resolution;
    return oss.str();
}


} // spark
