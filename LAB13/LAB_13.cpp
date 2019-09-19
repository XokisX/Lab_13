#include <iostream>
#include <locale>
#include <cwchar>
//#define EE(id)get(id)
#include "Error.h"
#include "Parm.h"
#include "Log.h"
#include "In.h"
#include "FST.h"
#include "Recognize.h"
using namespace Log;
using namespace std;
int main(int argc, const wchar_t* argv[])
{

	setlocale(LC_ALL, "rus");

	argv[0] = L"-in:D:\\Labs\\2\\LP\\ANALIZATOR\\LAB13\\LAB13\\In.txt";



	LOG log;
	Parm::PARM parm;
	try {
		parm = Parm::getParm(1, argv);


		writeLine(getLog(parm.log), "Текст ", "без ", "ошибок ", "");
		writeLog(getLog(parm.log));
		writeParm(getLog(parm.log), parm);
		In::IN in = In::getIn(parm.in);
		writeIn(getLog(parm.log), in);
		ChainRecognition(log, in, parm);
		close(getLog(parm.log));

	}
	catch (Error::ERROR e) {

		writeError(getLog(parm.log), e);

	}
	system("pause");
}