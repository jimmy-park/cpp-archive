#pragma once

#include <csignal>
#include <sstream>
#include <string>

#include "log_sync.h"

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
    LOG_FATAL("Received " << SignalName(signal) << " signal");
}