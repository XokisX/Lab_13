
#include"fst.h"
#include"Recognize.h"
#include "In.h"
#include "Log.h"
using namespace Log;
void ChainRecognition(LOG& log, IN& in, PARM &parm) {
	char *strrr = new char[in.size];
	int i, j;
	FST::FST fst1(
		strrr, 21,//(char*)"start send show show wait stop"
		FST::NODE(1, FST::RELATION('s', 1)), //0
		FST::NODE(1, FST::RELATION('t', 2)), //1
		FST::NODE(1, FST::RELATION('a', 3)), //2
		FST::NODE(1, FST::RELATION('r', 4)), //3
		FST::NODE(1, FST::RELATION('t', 5)), //4
		FST::NODE(1, FST::RELATION(' ', 6)), //5
		FST::NODE(4, FST::RELATION(' ', 6), FST::RELATION('s', 7), FST::RELATION('w', 13), FST::RELATION(' ', 16)),//6
		FST::NODE(2, FST::RELATION('e', 8), FST::RELATION('h', 11)), //7
		FST::NODE(1, FST::RELATION('n', 9)), //8
		FST::NODE(1, FST::RELATION('d', 10)), //9
		FST::NODE(2, FST::RELATION(' ', 16), FST::RELATION(' ', 6)), //10
		FST::NODE(1, FST::RELATION('o', 12)), //11
		FST::NODE(1, FST::RELATION('w', 10)), //12

		FST::NODE(1, FST::RELATION('a', 14)), //13
		FST::NODE(1, FST::RELATION('i', 15)), //14
		FST::NODE(1, FST::RELATION('t', 10)), //15

		FST::NODE(2, FST::RELATION(' ', 16), FST::RELATION('s', 17)), //16
		FST::NODE(1, FST::RELATION('t', 18)), //17
		FST::NODE(1, FST::RELATION('o', 19)), //18
		FST::NODE(1, FST::RELATION('p', 20)) //19
	);
	for (i = j = 0; i < in.size; i++, j++)
		if (in.text[i] == '\\') {
			strrr[j] = '\0';
			if (strcmp(strrr, "") != 0) {
				FST::udpdate(fst1, strrr);
				if (FST::execute(fst1))
					writeOut(parm, "Цепочка ", fst1.string, " распознана", "");
				else
					writeOut(parm, "Цепочка ", fst1.string, " не распознана", "");
			}
			j = -1;
		}
		else
			strrr[j] = in.text[i];
	strrr[j] = '\0';
	if (strcmp(strrr, "") != 0) {
		FST::udpdate(fst1, strrr);
		if (FST::execute(fst1))
			writeOut(parm, "Цепочка ", fst1.string, " распознана", "");
		else
			writeOut(parm, "Цепочка ", fst1.string, " не распознана", "");
	}
}
