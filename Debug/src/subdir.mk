################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Dilate-trial.cpp \
../src/line_separate.cpp \
../src/opencv_v1.cpp 

OBJS += \
./src/Dilate-trial.o \
./src/line_separate.o \
./src/opencv_v1.o 

CPP_DEPS += \
./src/Dilate-trial.d \
./src/line_separate.d \
./src/opencv_v1.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++14 -I/usr/local/include -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


