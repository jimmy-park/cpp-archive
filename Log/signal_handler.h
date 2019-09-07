#pragma once

#include <csignal>
#include <iostream>
#include <sstream>
#include <string>

std::string SignalName(int signal)
{
    switch (signal) {
    case SIGINT:
        return "SIGINT";
    case SIGILL:
        return "SIGILL";
    case SIGFPE:
        return "SIGFPE";
    case SIGSEGV:
        return "SIGSEGV";
    case SIGTERM:
        return "SIGTERM";
    case SIGABRT:
        return "SIGABRT";
    default:
        std::ostringstream oss;
        oss << "UNKNOWN (" << signal << ")";
        return oss.str();
    }
}

void SignalHandler(int signal)
{
    std::cout << "Received " << SignalName(signal) << " signal" << std::endl;
}