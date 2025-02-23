################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Core/Src/stm32-hal-mcp2515/mcp2515.cpp 

OBJS += \
./Core/Src/stm32-hal-mcp2515/mcp2515.o 

CPP_DEPS += \
./Core/Src/stm32-hal-mcp2515/mcp2515.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/stm32-hal-mcp2515/%.o Core/Src/stm32-hal-mcp2515/%.su Core/Src/stm32-hal-mcp2515/%.cyclo: ../Core/Src/stm32-hal-mcp2515/%.cpp Core/Src/stm32-hal-mcp2515/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++14 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xC -c -I../Core/Inc -IC:/Users/bharg/STM32Cube/Repository/STM32Cube_FW_F4_V1.28.1/Drivers/STM32F4xx_HAL_Driver/Inc -IC:/Users/bharg/STM32Cube/Repository/STM32Cube_FW_F4_V1.28.1/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -IC:/Users/bharg/STM32Cube/Repository/STM32Cube_FW_F4_V1.28.1/Drivers/CMSIS/Device/ST/STM32F4xx/Include -IC:/Users/bharg/STM32Cube/Repository/STM32Cube_FW_F4_V1.28.1/Drivers/CMSIS/Include -I../USB_DEVICE/App -I../USB_DEVICE/Target -IC:/Users/bharg/STM32Cube/Repository/STM32Cube_FW_F4_V1.28.1/Middlewares/ST/STM32_USB_Device_Library/Core/Inc -IC:/Users/bharg/STM32Cube/Repository/STM32Cube_FW_F4_V1.28.1/Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-stm32-2d-hal-2d-mcp2515

clean-Core-2f-Src-2f-stm32-2d-hal-2d-mcp2515:
	-$(RM) ./Core/Src/stm32-hal-mcp2515/mcp2515.cyclo ./Core/Src/stm32-hal-mcp2515/mcp2515.d ./Core/Src/stm32-hal-mcp2515/mcp2515.o ./Core/Src/stm32-hal-mcp2515/mcp2515.su

.PHONY: clean-Core-2f-Src-2f-stm32-2d-hal-2d-mcp2515

