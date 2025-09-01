#include <QtEndian>
#include "efekta.h"

QVariant ActionsEfekta::ReadInterval::request(const QString &, const QVariant &data)
{
    quint16 value = qToLittleEndian <quint16> (data.toInt());
    return writeAttribute(DATA_TYPE_16BIT_UNSIGNED, &value, sizeof(value));
}

QVariant ActionsEfekta::TemperatureSettings::request(const QString &name, const QVariant &data)
{
    int index = m_actions.indexOf(name);

    switch (index)
    {
        case 0: // temperatureOffset
        {
            qint16 value = qToLittleEndian <qint16> (data.toDouble() * 10);
            return writeAttribute(0x0210, DATA_TYPE_16BIT_SIGNED, &value, sizeof(value));
        }

        case 1: // temperatureHigh
        case 2: // temperatureLow
        {
            qint16 value = qToLittleEndian <qint16> (data.toInt());
            return writeAttribute(index == 1 ? 0x0221 : 0x0222, DATA_TYPE_16BIT_SIGNED, &value, sizeof(value));
        }

        case 3: // temperatureRelay
        case 4: // temperatureRelayInvert
        {
            quint8 value = data.toBool() ? 0x01 : 0x00;
            return writeAttribute(index == 3 ? 0x0220 : 0x0225, DATA_TYPE_BOOLEAN, &value, sizeof(value));
        }
    }

    return QByteArray();
}

QVariant ActionsEfekta::HumiditySettings::request(const QString &name, const QVariant &data)
{
    int index = m_actions.indexOf(name);

    switch (index)
    {
        case 0: // humidityOffset
        {
            qint16 value = qToLittleEndian <qint16> (data.toInt());
            return writeAttribute(0x0210, DATA_TYPE_16BIT_SIGNED, &value, sizeof(value));
        }

        case 1: // humidityHigh
        case 2: // humidityLow
        {
            quint8 value = qToLittleEndian <quint8> (data.toInt());
            return writeAttribute(index == 1 ? 0x0221 : 0x0222, DATA_TYPE_16BIT_UNSIGNED, &value, sizeof(value));
        }

        case 3: // humidityRelay
        case 4: // humidityRelayInvert
        {
            quint8 value = data.toBool() ? 0x01 : 0x00;
            return writeAttribute(index == 3 ? 0x0220 : 0x0225, DATA_TYPE_BOOLEAN, &value, sizeof(value));
        }
    }

    return QByteArray();
}

QVariant ActionsEfekta::CO2Settings::request(const QString &name, const QVariant &data)
{
    int index = m_actions.indexOf(name);

    switch (index)
    {
        case 0 ... 3:
        {
            quint16 attributeId, value = qToLittleEndian <quint16> (data.toInt());

            switch (index)
            {
                case 0:  attributeId = 0x0205; break; // altitude
                case 1:  attributeId = 0x0207; break; // co2ManualCalibration
                case 2:  attributeId = 0x0221; break; // co2High
                case 3:  attributeId = 0x0222; break; // co2Low
            }

            return writeAttribute(attributeId, DATA_TYPE_16BIT_UNSIGNED, &value, sizeof(value));
        }

        case 4: // indicatorLevel
        {
            quint8 value = qToLittleEndian <quint8> (data.toInt());
            return writeAttribute(0x0209, DATA_TYPE_8BIT_UNSIGNED, &value, sizeof(value));
        }

        default:
        {
            quint16 attributeId;
            quint8 value = data.toBool() ? 0x01 : 0x00;

            switch (index)
            {
                case 5:  attributeId = 0x0202; break; // co2ForceCalibration
                case 6:  attributeId = 0x0203; break; // autoBrightness
                case 7:  attributeId = 0x0204; break; // co2LongChart
                case 8:  attributeId = 0x0206; break; // co2FactoryReset
                case 9:  attributeId = 0x0211; break; // indicator
                case 10: attributeId = 0x0220; break; // co2Relay
                case 11: attributeId = 0x0225; break; // co2RelayInvert
                case 12: attributeId = 0x0244; break; // pressureLongChart
                case 13: attributeId = 0x0401; break; // backlight
                case 14: attributeId = 0x0402; break; // co2AutoCalibration
                default: return QByteArray();
            }

            return writeAttribute(attributeId, DATA_TYPE_BOOLEAN, &value, sizeof(value));
        }
    }
}

QVariant ActionsEfekta::PMSensor::request(const QString &name, const QVariant &data)
{
    int index = m_actions.indexOf(name);

    switch (index)
    {
        case 0 ... 2:
        {
            quint16 attributeId, value = qToLittleEndian <quint16> (data.toInt());

            switch (index)
            {
                case 0: attributeId = 0x0201; break; // readInterval
                case 1: attributeId = 0x0221; break; // pm25High
                case 2: attributeId = 0x0222; break; // pm25Low
            }

            return writeAttribute(attributeId, DATA_TYPE_16BIT_UNSIGNED, &value, sizeof(value));
        }

        case 3: // pm25Relay
        case 4: // pm25RelayInvert
        {
            quint8 value = data.toBool() ? 0x01 : 0x00;
            return writeAttribute(index == 3 ? 0x0220 : 0x0225, DATA_TYPE_BOOLEAN, &value, sizeof(value));
        }
    }

    return QByteArray();
}

QVariant ActionsEfekta::VOCSensor::request(const QString &name, const QVariant &data)
{
    int index = m_actions.indexOf(name);

    switch (index)
    {
        case 0: // vocHigh
        case 1: // vocLow
        {
            quint16 value = qToLittleEndian <quint16> (data.toInt());
            return writeAttribute(index == 0 ? 0x0221 : 0x0222, DATA_TYPE_16BIT_UNSIGNED, &value, sizeof(value));
        }

        case 2: // vocRelay
        case 3: // vocRelayInvert
        {
            quint8 value = data.toBool() ? 0x01 : 0x00;
            return writeAttribute(index == 2 ? 0x0220 : 0x0225, DATA_TYPE_BOOLEAN, &value, sizeof(value));
        }
    }

    return QByteArray();
}
