cmake_minimum_required(VERSION 3.10)
project(MyProject CXX)

add_executable(hms main.cpp IOAble.cpp Menu.cpp Patient.cpp PreTriage.cpp TestPatient.cpp Ticket.cpp Time.cpp TriagePatient.cpp Utils.cpp)

target_compile_options(hms PRIVATE -Wall -Wextra)
