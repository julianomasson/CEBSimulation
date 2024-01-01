cmake_minimum_required(VERSION 3.14)
project(CEBSimulation)

set(CMAKE_CXX_STANDARD 20)

set(SRCS			src/main.cpp
					src/Edge.h
					src/Fog.h
					src/Communication.h
					src/Sensor.h
					src/Error.h
					src/SimpleError.h
					src/TemperatureSensor.h
					src/GaussianNoise.h)

add_executable(${PROJECT_NAME} ${SRCS})

add_definitions(-DNOMINMAX
		-D_SCR_SECURE_NO_WARNINGS
		-D_CRT_SECURE_NO_WARNINGS)

