#include "SPI.h"

const uint8_t ParamSize[] = {
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

class L6470 {
    SPI* bus;
    size_t slaveIndex, motorSteps;
    int64_t absPos;

    bool set(uint8_t len, uint8_t key, uint32_t value);
    bool get(uint8_t len, uint8_t key, uint32_t& value);

    public:
    enum class ParamName {
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

    enum class DriverStatus {
        HiZ = 1<<0,
        BUSY = 1<<1,
        SW_F = 1<<2,
        SW_EVN = 1<<3,
        DIR = 1<<4,
        MOT_STATUS = 3<<5,
        NOTPERF_CMD = 1<<7,
        WRONG_CMD = 1<<8,
        UVLO = 1<<9,
        TH_WRN = 1<<10,
        TH_SD = 1<<11,
        OCD = 1<<12,
        STEP_LOSS_A = 1<<13,
        STEP_LOSS_B = 1<<14,
        SCK_MOD = 1<<15
    };

    enum class MotorStatus {
        Stopped = 0,
        Acceleration = 1,
        Deceleration = 2,
        ConstantSpeed = 3
    };

    L6470(SPI* bus, size_t slaveIndex);

    //Param register commands
    bool setParam(ParamName param, uint32_t value);
    bool getParam(ParamName param, uint32_t& value);

    //Constant speed commands
    bool run(uint32_t speed, bool forward);
    bool goUntil(uint32_t speed, bool forward, bool mark);
    bool releaseSW(bool forward, bool mark);

    //Absolute positioning commands
    bool goHome(bool mark);
    bool goTo(uint32_t position);
    bool goTo(uint32_t position, bool forward);

    //Motion commands
    bool stepClock(bool forward);
    bool move(uint32_t microSteps, bool forward);

    //Stop commands
    bool stop(bool immediately);
    bool setIdle(bool immediately);

    //Reset commands
    bool resetHome();
    bool resetDevice();
    bool resetFlags(uint32_t& status);

    //High level
    bool runInHz(float speed);
    bool goToInTurns(float position);
    const char* getStatus();
    bool updatePosition();
    float getSpeedInHz();
    float getPositionInTurns();
    bool isAtPositionInTurns(float position);
};
