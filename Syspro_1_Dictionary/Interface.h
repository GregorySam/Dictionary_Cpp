/*
 * Interface.h
 *
 *  Created on: Mar 3, 2018
 *      Author: greg
 */

#ifndef INTERFACE_H_
#define INTERFACE_H_

#include "Data_Structures/Data_Structures.h"


enum ReturnCode{error,exit_program,success};

class Interface {
	Data_Structures D;
	int results_num;
public:
	ReturnCode Search_Words(char*);
	ReturnCode Read_Input(char*);
	Interface(char*,unsigned int);
	~Interface();
};

#endif /* INTERFACE_H_ */
