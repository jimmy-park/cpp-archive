#include "log.h"

Logger::Logger()
    : release_(false)
    , levels_(LogLevel::kNone)
{
    fut = std::async(std::launch::async, &Logger::LogPop, this);
}

Logger::~Logger()
{
    release_ = true;
    fut.wait();
}

void Logger::LogPush(std::string output)
{
    std::lock_guard<std::mutex> lock(mutex_);

    std::ostringstream oss;
    oss << GetTimestamp() << output;
    queue_.push(oss.str());

    data_cond_.notify_one();
}

void Logger::LogPop()
{
    while (!release_ || !queue_.empty()) {
        std::unique_lock<std::mutex> lock(mutex_);

        //  data_cond_.wait(lock, [](bool result){return !queue_.empty();});
        while (queue_.empty()) {
            data_cond_.wait(lock);
        }

        file_ << queue_.front() << std::endl;
        queue_.pop();
    }
}

std::string Logger::GetTimestamp()
{
    const auto now = std::chrono::system_clock::now();
    const auto now_time_t = std::chrono::system_clock::to_time_t(now);
    const auto now_us = std::chrono::duration_cast<std::chrono::microseconds>(now.time_since_epoch()) % 1000000;

    std::ostringstream oss;
    oss << std::put_time(std::localtime(&now_time_t), "%F %a %T") << "." << std::setfill('0') << std::setw(6) << now_us.count() << " ";

    return oss.str();
}

std::string Logger::GetLevelLabel(const LogLevel& level)
{
    switch (level) {
    case LogLevel::kError:
        return "[ERROR] ";
    case LogLevel::kWarn:
        return "[WARN]  ";
    case LogLevel::kDebug:
        return "[DEBUG] ";
    case LogLevel::kInfo:
        return "[INFO]  ";
    default:
        return "[UNKNOWN] ";
    }
}

void Logger::SetPath(const char* path)
{
    file_.open(path, std::ios::out | std::ios::binary);

    if (!file_.is_open()) {
#ifdef _MSC_VER
        CreateDirectoryA("log", nullptr);
#else
        mkdir("log", 0777);
#endif // _MSC_VER
        const auto now = std::chrono::system_clock::now();
        const auto now_time_t = std::chrono::system_clock::to_time_t(now);

        std::ostringstream oss;
        oss << "log/" << std::put_time(std::localtime(&now_time_t), "[%y%m%d %a] %H-%M-%S") << ".log";

        const auto str = oss.str();
        file_.open(str.c_str(), std::ios::out | std::ios::binary);
    }
}

void print(LogLevel level)
{
    for (int i = 0; i < 100; ++i)
        LOG(level, i);
}

int main()
{
    LOG_LEVEL(LogLevel::kLevelAll);
    // LOG_LEVEL(LogLevel::kPrefixLevel | LogLevel::kInfo | LogLevel::kError);
    LOG_PATH("temp.log");

    auto fut1 = std::async(print, LogLevel::kInfo);
    auto fut2 = std::async(print, LogLevel::kDebug);
    auto fut3 = std::async(print, LogLevel::kWarn);
    auto fut4 = std::async(print, LogLevel::kError);

    // std::string msg{ "message" };
    // LOG_ERROR("error " << msg);
    // LOG_WARN("warn " << msg);
    // LOG_DEBUG("debug " << msg);
    // LOG_INFO("info " << msg);
}