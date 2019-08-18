#pragma once

#include <memory>

namespace mds {

class LoggerImpl {

public:
    template <typename T>
    LoggerImpl(const T& logger_impl_os)
        : logger_impl_(std::make_shared<Model<T>>(std::move(logger_impl_os)))
    {
    }

    void Log() const
    {
        return logger_impl_->Log();
    }

    struct Concept {
        virtual ~Concept() {}
        virtual void Log() const = 0;
    };

    template <typename T>
    struct Model : Concept {
        Model(const T& t)
            : logger_impl_os(t)
        {
        }

        void Log() const override
        {
            return logger_impl_os.Log();
        }

    private:
        T logger_impl_os;
    };

    std::shared_ptr<const Concept> logger_impl_;
};

} // namespace mds