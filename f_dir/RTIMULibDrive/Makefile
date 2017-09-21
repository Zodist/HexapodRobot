# Compiler, tools and options

RTIMULIBPATH		= ../../lib_gyro/RTIMULib
CC    			= gcc
CXX   			= g++
DEFINES       		=
CFLAGS			= -pipe -O2 -Wall -W $(DEFINES)
CXXFLAGS      		= -pipe -O2 -Wall -W $(DEFINES)
INCPATH       		= -I. -I$(RTIMULIBPATH)
LINK  			= g++
LFLAGS			= -Wl,-O1
LIBS  			= -L/usr/lib/arm-linux-gnueabihf
DEL_FILE      		= rm -f
SYMLINK       		= ln -f -s

# Output directory
OBJECTS_DIR   = ../../objects

# Files

DEPS    = $(RTIMULIBPATH)/RTMath.h \
    $(RTIMULIBPATH)/RTIMULib.h \
    $(RTIMULIBPATH)/RTIMULibDefs.h \
    $(RTIMULIBPATH)/RTIMUHal.h \
    $(RTIMULIBPATH)/RTFusion.h \
    $(RTIMULIBPATH)/RTFusionKalman4.h \
    $(RTIMULIBPATH)/RTFusionRTQF.h \
    $(RTIMULIBPATH)/RTIMUSettings.h \
    $(RTIMULIBPATH)/RTIMUAccelCal.h \
    $(RTIMULIBPATH)/RTIMUMagCal.h \
    $(RTIMULIBPATH)/RTIMUCalDefs.h \
    $(RTIMULIBPATH)/IMUDrivers/RTIMU.h \
    $(RTIMULIBPATH)/IMUDrivers/RTIMUNull.h \
    $(RTIMULIBPATH)/IMUDrivers/RTIMUMPU9150.h \
    $(RTIMULIBPATH)/IMUDrivers/RTIMUMPU9250.h \
    $(RTIMULIBPATH)/IMUDrivers/RTIMUGD20HM303D.h \
    $(RTIMULIBPATH)/IMUDrivers/RTIMUGD20M303DLHC.h \
    $(RTIMULIBPATH)/IMUDrivers/RTIMUGD20HM303DLHC.h \
    $(RTIMULIBPATH)/IMUDrivers/RTIMULSM9DS0.h \
    $(RTIMULIBPATH)/IMUDrivers/RTIMULSM9DS1.h \
    $(RTIMULIBPATH)/IMUDrivers/RTIMUBMX055.h \
    $(RTIMULIBPATH)/IMUDrivers/RTIMUBNO055.h

OBJECTS = $(OBJECTS_DIR)/RTIMULibDrive.o \
    $(OBJECTS_DIR)/RTMath.o \
    $(OBJECTS_DIR)/RTIMUHal.o \
    $(OBJECTS_DIR)/RTFusion.o \
    $(OBJECTS_DIR)/RTFusionKalman4.o \
    $(OBJECTS_DIR)/RTFusionRTQF.o \
    $(OBJECTS_DIR)/RTIMUSettings.o \
    $(OBJECTS_DIR)/RTIMUAccelCal.o \
    $(OBJECTS_DIR)/RTIMUMagCal.o \
    $(OBJECTS_DIR)/RTIMU.o \
    $(OBJECTS_DIR)/RTIMUNull.o \
    $(OBJECTS_DIR)/RTIMUMPU9150.o \
    $(OBJECTS_DIR)/RTIMUMPU9250.o \
    $(OBJECTS_DIR)/RTIMUGD20HM303D.o \
    $(OBJECTS_DIR)/RTIMUGD20M303DLHC.o \
    $(OBJECTS_DIR)/RTIMUGD20HM303DLHC.o \
    $(OBJECTS_DIR)/RTIMULSM9DS0.o \
    $(OBJECTS_DIR)/RTIMULSM9DS1.o \
    $(OBJECTS_DIR)/RTIMUBMX055.o \
    $(OBJECTS_DIR)/RTIMUBNO055.o \

MAKE_TARGET	= RTIMULibDrive
DESTDIR	= ../../EXEC
TARGET		= ../../EXEC/$(MAKE_TARGET)

#Build rules
$(TARGET): $(OBJECTS)
	$(LINK) $(LFLAGS) -o $(TARGET) $(OBJECTS) $(LIBS)

# Compile
$(OBJECTS_DIR)/%.o : $(RTIMULIBPATH)/%.cpp $(DEPS)
	$(CXX) -c -o $@ $< $(CFLAGS) $(INCPATH)
	
$(OBJECTS_DIR)/%.o : $(RTIMULIBPATH)/IMUDrivers/%.cpp $(DEPS)
	$(CXX) -c -o $@ $< $(CFLAGS) $(INCPATH)

$(OBJECTS_DIR)/RTIMULibDrive.o : RTIMULibDrive.cpp $(DEPS)
	$(CXX) -c -o $@ RTIMULibDrive.cpp $(CFLAGS) $(INCPATH)


