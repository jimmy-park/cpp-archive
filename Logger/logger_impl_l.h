#pragma once

#include "logger_impl.h"

namespace mds {

class LoggerImplL : public LoggerImpl {
public:
    LoggerImplL(void);
    virtual ~LoggerImplL(void) override;

    virtual void Log() override;
};

} // namespace mds