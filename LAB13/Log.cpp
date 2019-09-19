#include "Parm.h"
#include "Error.h"
#pragma warning( disable : 4996 34; once : 4385; error : 164 )

#include "In.h"
#include "Log.h"
#include <ctime>
#include <time.h>

namespace Log {
	LOG getLog(wchar_t logfile[]) {
		LOG e;
		e.stream.open(logfile, std::ios::app);
		if (e.stream.fail()) throw ERROR_THROW(112);
		wcscpy_s(e.logfile, logfile);
		e.stream.close();
		return e;
	}

	void writeLine(LOG log, const char* c, ...) {
		const char **str = &c;
		log.stream.open(log.logfile);
		while (*str != "") {
			log.stream << *str;
			str++;
		}

		log.stream << endl;
	}
	void writeLine(LOG log, wchar_t* c, ...) {
		wchar_t **str = &c;
		log.stream.open(log.logfile);
		while (*str != L"") {
			log.stream << *str;
			str++;
		}
		log.stream << endl;
	}

	void writeLog(LOG log) {
		log.stream.open(log.logfile, std::ios::app);
		time_t rawtime;
		struct tm * timeinfo;
		char buffer[80];
		time(&rawtime);
		timeinfo = localtime(&rawtime);
		strftime(buffer, 80, "%X %x", timeinfo);

		log.stream << "------ " << "Протокол" << " ----- Дата: " << buffer << " ----------" << endl;
	}
	void writeParm(LOG log, Parm::PARM parm) {
		log.stream.open(log.logfile, std::ios::app);
		log.stream << "------ Параметры ----------" << endl;
		char *in = new char[IN_MAX_LEN_TEXT];
		char *out = new char[IN_MAX_LEN_TEXT];
		char *logg = new char[IN_MAX_LEN_TEXT];
		int x = wcstombs(in, parm.in, wcslen(parm.in));
		in[x] = '\0';
		x = wcstombs(out, parm.out, wcslen(parm.out));
		out[x] = '\0';
		x = wcstombs(logg, parm.log, wcslen(parm.log));
		logg[x] = '\0';
		log.stream << "-log: " << logg << endl;
		log.stream << "-out: " << out << endl;
		log.stream << "-in: " << in << endl;
	}
	void Log::writeIn(LOG log, In::IN in) {
		log.stream.open(log.logfile, std::ios::app);
		log.stream << "------ Исходные данные ----------" << endl;
		log.stream << "--------Текст----------" << endl << "___________" << endl << in.text << endl << "___________" << endl;
		log.stream << "Кол-во символов: " << in.size << endl;
		log.stream << "Проигнорированно: " << in.ignor << endl;
		log.stream << "Строк: " << in.lines << endl;
	}

	void Log::writeError(LOG log, Error::ERROR e) {
		log.stream.open(log.logfile, std::ios::app);
		log.stream << "Ошибка " << e.id << ":" << e.message << endl;
		if (e.inext.column >= 0 && e.inext.line >= 0) {
			log.stream << "Строка: " << e.inext.line << ", позиция: " << e.inext.column << endl;
		}
		log.stream.close();

	}


	void Log::writeOut(Parm::PARM parm, const char* c, ...) {
		ofstream fout;
		fout.open(parm.out);
		const char **str = &c;
		while (*str != "") {
			fout << *str;
			str++;
		}

		fout << endl;
		fout.close();
	}

	void Log::close(LOG log) {
		log.stream.close();
	}
};