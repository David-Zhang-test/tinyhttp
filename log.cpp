#include "log.h"




Logger::Logger(const string& name) :name(name) {}

void Logger::addAppender(Appender::ptr appender) {
	appenders.push_back(appender);

}
void Logger::delAppender(Appender::ptr appender) {
	for (auto i = appenders.begin(); i != appenders.end(); ++i) {
		if (*i == appender) {
			appenders.erase(i);
			break;
		}
	}
}
void Logger::log(LogLevel::LEVEL level, LogEvent::ptr event) {
	if (level > level_m) {
		for (auto& i : appenders) {
			i->log(level, event);
		}
	}
}
void Logger::debug(LogEvent::ptr event) {
	log(LogLevel::LEVEL::DEBUG, event);
}
void Logger::info(LogEvent::ptr event) {
	log(LogLevel::LEVEL::INFO, event);
}
void Logger::warn(LogEvent::ptr event) {
	log(LogLevel::LEVEL::WARNING, event);
}
void Logger::error(LogEvent::ptr event) {
	log(LogLevel::LEVEL::ERROR, event);
}
void Logger::fatal(LogEvent::ptr event) {
	log(LogLevel::LEVEL::FATAL, event);
}