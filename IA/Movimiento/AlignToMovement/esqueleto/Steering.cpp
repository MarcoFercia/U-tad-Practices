
//#include <tinyxml.h>
#include <stdafx.h>
#include "Steering.h"

Steering::~Steering()
{
    delete m_delegate;
}

ResultSteering Steering::CallDelegate() const
{
    if (m_delegate)
    {
        return m_delegate->GetSteering();
    }
    return ResultSteering({ 0.f,0.f }, 0.f);
}
