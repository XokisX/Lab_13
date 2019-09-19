
#include"fst.h"
#include"Recognize.h"
#include "In.h"
#include "Log.h"
using namespace Log;
void ChainRecognition(LOG& log, IN& in, PARM &parm) {
	char *strrr = new char[in.size];
	int i, j;
	FST::FST fst1(
		strrr, 24,//(char*)"start send show show wait stop"
		FST::NODE(1, FST::RELATION('b', 1)),    //0
		FST::NODE(1, FST::RELATION('e', 2)),    //1
		FST::NODE(1, FST::RELATION('g', 3)),    //2
		FST::NODE(1, FST::RELATION('i', 4)),    //3
		FST::NODE(1, FST::RELATION('n', 5)),    //4
		FST::NODE(1, FST::RELATION(';', 6)),    //5
		FST::NODE(4, FST::RELATION(' ', 6), FST::RELATION('r', 7), FST::RELATION('c', 12), FST::RELATION('p', 15)),    //6
		FST::NODE(1, FST::RELATION('e', 8)),    //7
		FST::NODE(1, FST::RELATION('a', 9)),    //8
		FST::NODE(1, FST::RELATION('d', 10)),    //9

		FST::NODE(1, FST::RELATION(';', 11)),    //10
		FST::NODE(2, FST::RELATION(' ', 19), FST::RELATION(' ', 6)),    //11

		FST::NODE(1, FST::RELATION('a', 13)),    //12
		FST::NODE(1, FST::RELATION('l', 14)),    //13
		FST::NODE(1, FST::RELATION('c', 10)),    //14
		FST::NODE(1, FST::RELATION('r', 16)),    //15
		FST::NODE(1, FST::RELATION('i', 17)),    //16
		FST::NODE(1, FST::RELATION('n', 18)),    //17
		FST::NODE(1, FST::RELATION('t', 10)),    //18

		FST::NODE(2, FST::RELATION(' ', 19), FST::RELATION('e', 20)),    //19
		FST::NODE(1, FST::RELATION('n', 21)),    //20
		FST::NODE(1, FST::RELATION('d', 22)),    //21
		FST::NODE(1, FST::RELATION(';', 23))  //22
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
