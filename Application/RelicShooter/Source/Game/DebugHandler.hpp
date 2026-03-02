#ifndef DEBUGHANDLER_H
#define DEBUGHANDLER_H

// For output
#include <iostream>
#include <string>

// For date & time
#include <sstream>
#include <chrono>
#include <iomanip>

/**
 * Easy debug to console including important information such as:
 *
 * - Time
 * - Message State (Info, Warning, Error)
 * - Message
 *
**/

class DebugHandler {
public:
    template <typename A, typename B>
    static void PrintLog(const A &process, const B& content) {
        std::cout << GetTimeAndDate() << process << "]: " << content << std::endl;
    }

private:
    static std::string GetTimeAndDate() {
        using namespace std::chrono;
        // Get current time with high resolution
        const auto now = system_clock::now();

        // Convert to time_t for calendar time (seconds)
        const auto in_time_t = system_clock::to_time_t(now);

        // Extract milliseconds
        const auto milliseconds = duration_cast<std::chrono::milliseconds>(
            now.time_since_epoch()) % 1000;

        // Format date and time
        std::tm buf = *std::localtime(&in_time_t);
        std::ostringstream output;
        output << "[" << std::put_time(&buf, "%d/%m/%Y") << "] ";
        output << "[" << std::put_time(&buf, "%H:%M:%S") << "] [";

        return output.str();
    }
};

/* https://stackoverflow.com/questions/8487986/file-macro-shows-full-path */
#define __FILENAME__ (strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__)

// MSVC
#ifdef _DEBUG
#define LOG(content)    DebugHandler::PrintLog(__FILENAME__, content);
// Remove macros if not in debug mode
#else
	#define LOG(content)
#endif



#endif