################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Core/Inc/UART_Services/uart_services.cpp 

OBJS += \
./Core/Inc/UART_Services/uart_services.o 

CPP_DEPS += \
./Core/Inc/UART_Services/uart_services.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Inc/UART_Services/%.o Core/Inc/UART_Services/%.su Core/Inc/UART_Services/%.cyclo: ../Core/Inc/UART_Services/%.cpp Core/Inc/UART_Services/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++14 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Inc-2f-UART_Services

clean-Core-2f-Inc-2f-UART_Services:
	-$(RM) ./Core/Inc/UART_Services/uart_services.cyclo ./Core/Inc/UART_Services/uart_services.d ./Core/Inc/UART_Services/uart_services.o ./Core/Inc/UART_Services/uart_services.su

.PHONY: clean-Core-2f-Inc-2f-UART_Services

