################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/STM32-MCP2515/Inc/mcp2515.c 

C_DEPS += \
./Drivers/STM32-MCP2515/Inc/mcp2515.d 

OBJS += \
./Drivers/STM32-MCP2515/Inc/mcp2515.o 


# Each subdirectory must supply rules for building sources it contributes
Drivers/STM32-MCP2515/Inc/%.o Drivers/STM32-MCP2515/Inc/%.su Drivers/STM32-MCP2515/Inc/%.cyclo: ../Drivers/STM32-MCP2515/Inc/%.c Drivers/STM32-MCP2515/Inc/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xC -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -I"C:/Users/bharg/STM32CubeIDE/workspace_1.17.0/stm-accelerometer/Drivers/STM32-MCP2515/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-STM32-2d-MCP2515-2f-Inc

clean-Drivers-2f-STM32-2d-MCP2515-2f-Inc:
	-$(RM) ./Drivers/STM32-MCP2515/Inc/mcp2515.cyclo ./Drivers/STM32-MCP2515/Inc/mcp2515.d ./Drivers/STM32-MCP2515/Inc/mcp2515.o ./Drivers/STM32-MCP2515/Inc/mcp2515.su

.PHONY: clean-Drivers-2f-STM32-2d-MCP2515-2f-Inc

