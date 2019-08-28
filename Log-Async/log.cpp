#include "log.h"

Logger::Logger()
    : release_(false)
    , levels_(LogLevel::kNone)
{
}

Logger::~Logger()
{
    release_ = true;
    thd_.join();
}

void Logger::AppendTimePrefix(std::ostringstream& message_stream, const LogFormat& log_format)
{
    const auto now = std::chrono::system_clock::now();
    const auto now_time_t = std::chrono::system_clock::to_time_t(now);
    const auto now_us = std::chrono::duration_cast<std::chrono::microseconds>(now.time_since_epoch()) % 1000000;

    message_stream << std::put_time(std::localtime(&now_time_t), "%F %T") << "." << std::setfill('0') << std::setw(6) << now_us.count() << " ";
}

void Logger::AppendLevelPrefix(std::ostringstream& message_stream, const LogFormat& log_format)
{
    switch (log_format.level) {
    case LogLevel::kError:
        message_stream << "[ERROR] ";
        return;
    case LogLevel::kWarn:
        message_stream << "[WARN]  ";
        return;
    case LogLevel::kDebug:
        message_stream << "[DEBUG] ";
        return;
    case LogLevel::kInfo:
        message_stream << "[INFO]  ";
        return;
    default:
        message_stream << "[UNKNOWN] ";
        return;
    }
}

void Logger::AppendFuncPrefix(std::ostringstream& message_stream, const LogFormat& log_format)
{
    if (IsLevelEnabled(LogLevel::kPrefixFunc))
        message_stream << log_format.file << "(" << log_format.line << "):" << log_format.function << "| ";
}

void Logger::LogFlush()
{
    while (!release_) {
        using namespace std::chrono_literals;
        std::this_thread::sleep_for(100ms);

        while (!queue_.empty())
            LogPop();
    }
}

void Logger::LogPop()
{
    std::unique_lock<std::mutex> lock(mutex_);

    data_cond_.wait(lock, [this] { return !queue_.empty(); });

    file_ << queue_.front() << std::endl;
    queue_.pop();
}

void Logger::LogPush(const LogFormat& log_format)
{
    std::lock_guard<std::mutex> lock(mutex_);

    std::ostringstream output;
    AppendTimePrefix(output, log_format);
    AppendLevelPrefix(output, log_format);
    AppendFuncPrefix(output, log_format);
    output << log_format.message;

    queue_.push(output.str());
    data_cond_.notify_one();
}

void Logger::SetLevel(const LogLevel& level)
{
    levels_ |= level;
    thd_ = std::thread(&Logger::LogFlush, this);
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
    for (int i = 0; i < 100; ++i) {
        LOG(__FILENAME__, __LINE__, __PRETTY_FUNCTION__, level, i);
    }
}

int main()
{
    LOG_LEVEL(LogLevel::kAll);
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