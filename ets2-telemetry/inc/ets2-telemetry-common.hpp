#ifndef ETS2_TELEMETRY_COMMON_HPP
#define ETS2_TELEMETRY_COMMON_HPP

// This file contains "Common definitions" for this ETS2 telemetry plug-in.
// This includes:
// - Debug logging detail options
// - Shared memory map struct layout
// - [..]

#define ETS2_PLUGIN_REVID					10

#define ETS2_PLUGIN_LOGGING_ON				_DEBUG
#define ETS2_PLUGIN_LOGGING_SHAREDMEMORY	1
#define ETS2_PLUGIN_FILENAME_PREFIX "C:\ets2telem_"

#if ETS2_PLUGIN_LOGGING_ON == 1
#define SDK_ENABLE_LOGGING
#endif

#define ETS2_PLUGIN_MMF_NAME TEXT("Local\\Ets2TelemetryServer")
#define ETS2_PLUGIN_MMF_SIZE (16*1024)

#define TRUCK_STRING_OFFSET 15*1024
#define TRAILER_STRING_OFFSET TRUCK_STRING_OFFSET+64

#define GENERAL_STRING_SIZE 64

#include <cstdint>

typedef struct
{
    float trailerMass;
    char trailerId[GENERAL_STRING_SIZE];
    char trailerName[GENERAL_STRING_SIZE];    
    int32_t jobIncome;
    int32_t time_abs_delivery;
    char citySrc[GENERAL_STRING_SIZE];
    char cityDst[GENERAL_STRING_SIZE];
    char compSrc[GENERAL_STRING_SIZE];
    char compDst[GENERAL_STRING_SIZE];
    float wearTrailer;
} job_buffer_struct;

extern job_buffer_struct job_buffer;

typedef struct ets2TelemetryMap_s
{
	uint32_t time;
	uint32_t paused;
	
	struct
	{
               uint32_t ets2_telemetry_plugin_revision;
               uint32_t ets2_version_major;
               uint32_t ets2_version_minor;
	} tel_revId;

	// All variables per revision are packed into 1 struct.
	// Newer revisions must contain identical struct layouts/lengths, even if variabeles become deprecated.
	// Replaced/new variabeles should be added in seperate structs
	struct
	{
		uint8_t engine_enabled;	// deprecated and removed since rev 5
		uint8_t trailer_attached;

		// vehicle dynamics
		float speed;
		
		float accelerationX;
		float accelerationY;
		float accelerationZ;
	
		float coordinateX;
		float coordinateY;
		float coordinateZ;
	
		float rotationX;
		float rotationY;
		float rotationZ;
	
		// drivetrain essentials
		int32_t gear;
               int32_t gears;
               int32_t gearRanges;			//TODO:fix
               int32_t gearRangeActive;	//TODO:fix

		float engineRpm;
		float engineRpmMax;
		
		float fuel;
		float fuelCapacity;
		float fuelRate;				// ! Not working
		float fuelAvgConsumption;
		
		// user input
		float userSteer;
		float userThrottle;
		float userBrake;
		float userClutch;
		
		float gameSteer;
		float gameThrottle;
		float gameBrake;
		float gameClutch;
	
		// truck & trailer
		float truckWeight;		//TODO:fix
		float trailerWeight;

               int32_t modelType[2];
               int32_t trailerType[2];			// ! deprecated

	} tel_rev1;

	struct
	{
		uint64_t time_abs;
		int gears_reverse;

		// Trailer ID & display name
		float trailerMass;
		char trailerId[GENERAL_STRING_SIZE];
		char trailerName[GENERAL_STRING_SIZE];
		
		// Job information
               int32_t jobIncome;
               int32_t time_abs_delivery;
		char citySrc[GENERAL_STRING_SIZE];
		char cityDst[GENERAL_STRING_SIZE];
		char compSrc[GENERAL_STRING_SIZE];
		char compDst[GENERAL_STRING_SIZE];

	} tel_rev2;	

	struct
	{
               int32_t retarderBrake;
               int32_t shifterSlot;
               int32_t shifterToggle;
               int32_t fill;

		uint8_t cruiseControl;
               uint8_t wipers;

               uint8_t parkBrake;
               uint8_t motorBrake;

               uint8_t electricEnabled;
               uint8_t engineEnabled;

               uint8_t blinkerLeftActive;
               uint8_t blinkerRightActive;
               uint8_t blinkerLeftOn;
               uint8_t blinkerRightOn;

               uint8_t lightsParking;
               uint8_t lightsBeamLow;
               uint8_t lightsBeamHigh;
               uint32_t lightsAuxFront;
               uint32_t lightsAuxRoof;
               uint8_t lightsBeacon;
               uint8_t lightsBrake;
               uint8_t lightsReverse;

               uint8_t batteryVoltageWarning;
               uint8_t airPressureWarning;
               uint8_t airPressureEmergency;
               uint8_t adblueWarning;
               uint8_t oilPressureWarning;
               uint8_t waterTemperatureWarning;

		float airPressure;
		float brakeTemperature;
		int32_t fuelWarning;
		float adblue;
		float adblueConsumption;
		float oilPressure;
		float oilTemperature;
		float waterTemperature;
		float batteryVoltage;
		float lightsDashboard;
		float wearEngine;
		float wearTransmission;
		float wearCabin;
		float wearChassis;
		float wearWheels;
		float wearTrailer;
		float truckOdometer;
		float cruiseControlSpeed;

		// General info about the truck etc;
		char truckMake[GENERAL_STRING_SIZE];
		char truckMakeId[GENERAL_STRING_SIZE];
		char truckModel[GENERAL_STRING_SIZE];


	} tel_rev3;

#define MAX_SHIFTER_TYPE_STRING_SIZE 16
#define MAX_WHEEL_COUNT 20
#define MAX_SLOT_COUNT 32

	struct
	{
		float fuelWarningFactor;
		float adblueCapacity;
		float airPressureWarningValue;
		float airPressureEmergencyValue;
		float oilPressureWarningValue;
		float waterTemperatureWarningValue;
		float batteryVoltageWarningValue;

               uint32_t retarderStepCount;
		
		float cabinPositionX;
		float cabinPositionY;
		float cabinPositionZ;
		float headPositionX;
		float headPositionY;
		float headPositionZ;
		float hookPositionX;
		float hookPositionY;
		float hookPositionZ;
		
		char shifterType[MAX_SHIFTER_TYPE_STRING_SIZE]; // "arcade", "automatic", "manual", "hshifter"

		float localScale; // time scale
		int32_t nextRestStop; // in minutes
		float trailerCoordinateX;
		float trailerCoordinateY;
		float trailerCoordinateZ;
		float trailerRotationX;
		float trailerRotationY;
		float trailerRotationZ;
		
		int32_t displayedGear;
		float navigationDistance;
		float navigationTime;
		float navigationSpeedLimit;

		/*
		unsigned char truckWheelCount;
		unsigned char trailerWheelCount;

		unsigned int wheelCount;
		float wheelPositionX[MAX_WHEEL_COUNT];
		float wheelPositionY[MAX_WHEEL_COUNT];
		float wheelPositionZ[MAX_WHEEL_COUNT];
		bool wheelSteerable[MAX_WHEEL_COUNT];
		bool wheelSimulated[MAX_WHEEL_COUNT];
		float wheelRadius[MAX_WHEEL_COUNT];
		bool wheelPowered[MAX_WHEEL_COUNT];
		bool wheelLiftable[MAX_WHEEL_COUNT];

		float wheelRotation[MAX_WHEEL_COUNT];
		float wheelAngularVelocity[MAX_WHEEL_COUNT];
		unsigned int wheelSubstance[MAX_WHEEL_COUNT];
		
		unsigned int selectorCount;
		int slotGear[MAX_SLOT_COUNT];
		unsigned int slotHandlePosition[MAX_SLOT_COUNT];
		unsigned int slotSelectors[MAX_SLOT_COUNT];
		*/
		
	} tel_rev4;

} ets2TelemetryMap_t;

#endif
