CC = g++
TARGET = ./EXEC/hexa
DIR_HED = ./h_dir/
DIR_FUNC = ./f_dir/
DIR_OBJECTS = ./objects
OBJECTS_DIR = ./objects

OBJS = $(DIR_OBJECTS)/main.o \
 $(DIR_OBJECTS)/ultraSonic.o \
 $(DIR_OBJECTS)/movement.o \
 $(DIR_OBJECTS)/server.o

# GYRO_sensor
GYROOBJECTS = $(OBJECTS_DIR)/RTIMULibDrive.o \
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
 $(OBJECTS_DIR)/RTPressure.o \
 $(OBJECTS_DIR)/RTPressureBMP180.o \
 $(OBJECTS_DIR)/RTPressureLPS25H.o \
 $(OBJECTS_DIR)/RTPressureMS5611.o \
 $(OBJECTS_DIR)/RTPressureMS5637.o 

.SUFFIXES : .c .o

$(TARGET) : $(OBJS)
	$(CC) -o $@ $(OBJS) $(GYROOBJECTS) RoboPiLib.o -lstdc++

clean:
	rm -f $(OBJS) $(GYROOBJECTS)

$(DIR_OBJECTS)/main.o : main.c
	gcc -c -o $@ main.c -I $(DIR_HED)

$(DIR_OBJECTS)/ultraSonic.o : $(DIR_FUNC)ultraSonic.c
	gcc -c -o $@ $(DIR_FUNC)ultraSonic.c -I $(DIR_HED)

$(DIR_OBJECTS)/movement.o : $(DIR_FUNC)movement.c
	gcc -c -o $@ $(DIR_FUNC)movement.c -I $(DIR_HED)

$(DIR_OBJECTS)/servoer.o : $(DIR_FUNC)server.c
	gcc -c -o $@ $(DIR_FUNC)server.c -I $(DIR_HED)
