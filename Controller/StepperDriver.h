#include "SPI.h"

enum ParamName {
    ABS_POS = 0x01,
    EL_POS = 0x02,
    MARK = 0x03,
    SPEED = 0x04,
    ACC = 0x05,
    DEC = 0x06,
    MAX_SPEED = 0x07,
    MIN_SPEED = 0x08,
    KVAL_HOLD = 0x09,
    KVAL_RUN = 0x0A,
    KVAL_ACC = 0x0B,
    KVAL_DEC = 0x0C,
    INT_SPEED = 0x0D,
    ST_SLP = 0x0E,
    FN_SLP_ACC = 0x0F,
    FN_SLP_DEC = 0x10,
    K_THERM = 0x11,
    ADC_OUT = 0x12,
    OCD_TH = 0x13,
    STALL_TH = 0x14,
    FS_SPD = 0x15,
    STEP_MODE = 0x16,
    ALARM_EN = 0x17,
    CONFIG = 0x18,
    STATUS = 0x19
};

const uint8_t paramSize[] = {
    0,
    22, //ABS_POS
    9, //EL_POS
    22, //MARK
    20, //SPEED
    12, //ACC
    12, //DEC
    10, //MAX_SPEED
    13, //MIN_SPEED
    8, //KVAL_HOLD
    8, //KVAL_RUN
    8, //KVAL_ACC
    8, //KVAL_DEC
    14, //INT_SPEED
    8, //ST_SLP
    8, //FN_SLP_ACC
    8, //FN_SLP_DEC
    4, //K_THERM
    5, //ADC_OUT
    4, //OCD_TH
    7, //STALL_TH
    10, //FS_SPD
    8, //STEP_MODE
    8, //ALARM_EN
    16, //CONFIG
    16 //STATUS
};

class StepperDriver {
    bool set(uint8_t len, uint8_t key, uint32_t value);
    bool get(uint8_t len, uint8_t key, uint32_t& value);
    public:
    SPI* bus;
    size_t slaveIndex;
    StepperDriver(SPI* bus, size_t slaveIndex);
    bool setParam(uint8_t key, uint32_t value);
    bool getParam(uint8_t key, uint32_t& value);
};
