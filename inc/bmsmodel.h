#ifndef BMSMODEL_H
#define BMSMODEL_H

#include <QObject>
#include "podstate.h"

#define INITIAL_BATPACK_CURRENT -1.0f
#define BATPACK_CURRENT_TIMEOUT_MS (1000*7) // 7 seconds
#define INITIAL_CELL_TEMP -1.0f
#define CELL_TEMP_TIMEOUT_MS (1000*7) // 7 seconds

/*!
 * \brief The BMSmodel class
 * The BMS model class is responsible for storing Up To Date
 * information about the state of the BMS system.
 * Health Check timeouts will be handled by this class and signals
 * will be sent from this class if BMS health checks miss their allotted checkins
 */
class BmsModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(float batteryPackCurrent READ getBatteryPackCurrent NOTIFY sig_batteryPackCurrentUpdated)
    Q_PROPERTY(float cellTempurature READ getCellTempurature NOTIFY sig_cellTempuratureUpdated)
public:
    explicit BmsModel(QObject* parent=nullptr);

    float getBatteryPackCurrent();
    float getCellTempurature();

private:
    // Values that come from health check
    PodState<float> m_batteryPackCurrent;
    PodState<float> m_cellTempurature;

signals:
    void sig_batteryPackCurrentUpdated();
    void sig_cellTempuratureUpdated();
    void sig_bmsHealthCheckFailure();

public slots:
    void slot_bmsBatteryPackCurrentReceived(float batteryPackCurrent);
    void slot_bmsCellTempuratureReceived(float cellTempurature);
};

#endif // BMSMODEL_H
