#pragma once
#include <string>
#include <memory>
#include <list>
using namespace std;


//log level
class LogLevel {
public:
	enum LEVEL {
		DEBUG = 1, INFO, WARNING, ERROR, FATAL
	};
};
//log data
class LogEvent {
public:
	typedef shared_ptr<LogEvent> ptr;
	LogEvent();
private:
	const char* FileName = nullptr;
	int LineNumber = 0;
	unsigned int ThreadId = 0;
	unsigned int FiberId = 0;
	unsigned int Time;
	unsigned int Elapse = 0; //启动到现在的毫秒数
	string MessageContent;
};


//where the log will be displayed
class Appender {
public:
	typedef shared_ptr<Appender> ptr;
	virtual ~Appender() {};
	void log(LogLevel::LEVEL level, LogEvent::ptr event);
private:
	LogLevel::LEVEL level;
};


//logger
class Logger {
public:
	typedef shared_ptr<Logger> ptr; //using smart pointer
	void log(LogLevel::LEVEL level, LogEvent::ptr event);
	void debug(LogEvent::ptr event);
	void info(LogEvent::ptr event);
	void warn(LogEvent::ptr event);
	void error(LogEvent::ptr event);
	void fatal(LogEvent::ptr event);

	Logger(const string& name = "root");
	void addAppender(Appender::ptr appender);
	void delAppender(Appender::ptr appender);
	LogLevel::LEVEL getlevel()const { return level_m; }
	void setLevel(LogLevel::LEVEL val) { level_m = val; }

private:
	string name;								//log name
	LogLevel::LEVEL level_m;					//log level
	list <Appender::ptr> appenders;				//appenders set
};



//format log
class Formatter {
public:
	typedef shared_ptr<Formatter> ptr;
	string format(LogEvent::ptr event);
private:

};


//log to console
class StdoutLogAppender : public Appender {

};

// log to file
class FileoutAppender : public Appender {

};