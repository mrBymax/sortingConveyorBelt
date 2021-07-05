#include "button.h"

void Button::begin()
{
    pinMode(m_pin, m_puEnable ? INPUT_PULLUP : INPUT);
    m_state = digitalRead(m_pin);
    if (m_invert)
        m_state = !m_state;
    m_time = millis();
    m_lastChange = m_state;
    m_changed = false;
    m_lastChange = m_time;
}

bool Button::read()
{
    uint32_t ms = millis();
    bool pinVal = digitalRead(m_pin);
    if (m_invert)
        pinVal = !pinVal;
    if (ms - m_lastChange < m_dbTime)
    {
        m_changed = false;
    }
    else
    {
        m_lastState = m_state;
        m_state = pinVal;
        m_changed = (m_state != m_lastState);
        if (m_changed)
            m_lastChange = ms;
    }
    m_time = ms;
    return m_state;
}

bool Button::isPressed()
{
    return m_state;
}

bool Button::isReleased()
{
    return !m_state;
}

bool Button::pressedFor(uint32_t ms)
{
    return m_state && m_time - m_lastChange >= ms;
}

uint32_t Button::lastChange()
{
    return m_lastChange;
}