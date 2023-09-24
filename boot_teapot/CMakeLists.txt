cmake_minimum_required(VERSION 3.16)

project (mbr_kernel.bin)

enable_language(ASM_NASM CXX)

set(CMAKE_CXX_FLAGS "-m32 -ffreestanding -fno-PIC")


include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)



set(MBR_SOURCES
	${CMAKE_CURRENT_SOURCE_DIR}/src/mbr_boot_sect.asm
)	


set(MAIN_SOURCES
	${CMAKE_CURRENT_SOURCE_DIR}/src/start.cpp
)	


add_library(mbr_boot.bin OBJECT ${MBR_SOURCES})

set_target_properties(mbr_boot.bin PROPERTIES NASM_OBJ_FORMAT bin)
set(CMAKE_ASM_NASM_COMPILE_OBJECT "<CMAKE_ASM_NASM_COMPILER> <INCLUDES> <FLAGS> -o <OBJECT> <SOURCE>")
add_compile_options(
	"$<$<COMPILE_LANGUAGE:ASM_NASM>:-f $<TARGET_PROPERTY:NASM_OBJ_FORMAT>>"
)

set(objs_list  "$<TARGET_OBJECTS:mbr_boot.bin>")
string(REPLACE ";" " " myobjs0 "${objs_list}")
add_custom_target(mbr_boot.bin.mv ALL
  
    COMMAND cp -fr  "${myobjs0}" ${CMAKE_CURRENT_SOURCE_DIR}/build/mbr_boot.bin        
    DEPENDS mbr_boot.bin 
    COMMAND_EXPAND_LISTS
)


add_library(main_o OBJECT ${MAIN_SOURCES})
SET_TARGET_PROPERTIES(main_o PROPERTIES PREFIX "")
set(objs_list2  "$<TARGET_OBJECTS:main_o>")
string(REPLACE ";" " " myobjs1 "${objs_list2}")

add_custom_target(main_o_bin ALL
  
    COMMAND $(LD) -m elf_i386 -T ${CMAKE_CURRENT_SOURCE_DIR}/link.ld --oformat binary -o ${CMAKE_CURRENT_SOURCE_DIR}/build/kernel.bin
     "${myobjs1}"
    DEPENDS main_o
    COMMAND_EXPAND_LISTS 
)


add_custom_target(mbr_kernel.bin ALL
  
    COMMAND cat ${CMAKE_CURRENT_SOURCE_DIR}/build/mbr_boot.bin ${CMAKE_CURRENT_SOURCE_DIR}/build/kernel.bin > ${CMAKE_CURRENT_SOURCE_DIR}/build/mbr_kernel.bin
    DEPENDS main_o_bin mbr_boot.bin.mv
    COMMAND_EXPAND_LISTS 
)

#run
# qemu-system-i386 -fda ./mbr_kernel.bin
















