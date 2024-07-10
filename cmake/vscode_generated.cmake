# This is converter generated file, and shall not be touched by user
#
# Use CMakeLists.txt to apply user changes
cmake_minimum_required(VERSION 3.22)

# Core MCU flags, CPU, instruction set and FPU setup
set(cpu_PARAMS ${cpu_PARAMS}
    -mthumb

    # Other parameters
    # -mcpu, -mfloat, -mfloat-abi, ...
    -mcpu=cortex-m3
	
)

add_compile_definitions(STM32F103xB)

# Linker script
set(linker_script_SRC ${linker_script_SRC}
    ${CMAKE_CURRENT_SOURCE_DIR}/src/bsp/ldscript/stm32f103c8tx_FLASH.ld
)

set(EXCLUDE_PATHS 
    "CMakeFiles"
    ${CMAKE_CURRENT_SOURCE_DIR}/cube_bootloader/Core
)

# Generate target paths
file(GLOB_RECURSE MY_SRC "*.c")
foreach(now_src ${MY_SRC})
    foreach(ex_path ${EXCLUDE_PATHS})
        string(FIND ${now_src} ${ex_path} RESULT)
        if(NOT ${RESULT} EQUAL -1)
            list(REMOVE_ITEM MY_SRC ${now_src})
        endif()
    endforeach(ex_path)
endforeach(now_src)

# Sources
set(sources_SRCS ${sources_SRCS}
    
    ${MY_SRC}

	${CMAKE_CURRENT_SOURCE_DIR}/src/bsp/startup/startup_stm32f103c8tx.s
)


# Include directories
set(include_c_DIRS ${include_c_DIRS}
    
	${CMAKE_CURRENT_SOURCE_DIR}/src/include
    ${CMAKE_CURRENT_SOURCE_DIR}/src/bsp/include
    ${CMAKE_CURRENT_SOURCE_DIR}/cube_bootloader/Drivers/CMSIS/Device/ST/STM32F1xx/Include
    ${CMAKE_CURRENT_SOURCE_DIR}/cube_bootloader/Drivers/CMSIS/Include
    ${CMAKE_CURRENT_SOURCE_DIR}/cube_bootloader/Middlewares/ST/STM32_USB_Device_Library/Class/DFU/Inc
    ${CMAKE_CURRENT_SOURCE_DIR}/cube_bootloader/Middlewares/ST/STM32_USB_Device_Library/Core/Inc
    ${CMAKE_CURRENT_SOURCE_DIR}/cube_bootloader/Drivers/STM32F1xx_HAL_Driver/Inc
    ${CMAKE_CURRENT_SOURCE_DIR}/cube_bootloader/USB_DEVICE/App
    ${CMAKE_CURRENT_SOURCE_DIR}/cube_bootloader/USB_DEVICE/Target
)
set(include_cxx_DIRS ${include_cxx_DIRS}
    
)
set(include_asm_DIRS ${include_asm_DIRS}
    
)

# Symbols definition
set(symbols_c_SYMB ${symbols_c_SYMB}

)
set(symbols_cxx_SYMB ${symbols_cxx_SYMB}
    
)
set(symbols_asm_SYMB ${symbols_asm_SYMB}
    
)

# Link directories
set(link_DIRS ${link_DIRS}
    
)

# Link libraries
set(link_LIBS ${link_LIBS}
    
)

# Compiler options
set(compiler_OPTS ${compiler_OPTS})

# Linker options
set(linker_OPTS ${linker_OPTS})
