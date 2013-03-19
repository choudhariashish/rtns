################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../PriorityScheduler.cpp \
../RM_DM_Scheduler.cpp \
../Scheduler.cpp \
../main.cpp \
../task.cpp 

OBJS += \
./PriorityScheduler.o \
./RM_DM_Scheduler.o \
./Scheduler.o \
./main.o \
./task.o 

CPP_DEPS += \
./PriorityScheduler.d \
./RM_DM_Scheduler.d \
./Scheduler.d \
./main.d \
./task.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -DNULL=0 -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


