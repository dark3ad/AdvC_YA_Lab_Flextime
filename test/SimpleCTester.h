/* =====================================================================
 * Copyright (c) 2019 YrkesAkademin YH AB
 * All rights reserved.
 * Confidential and Proprietary - YrkesAkademin YH AB
 * =====================================================================
 *
 */

#ifndef SRC_SIMPLECTESTER_H_
#define SRC_SIMPLECTESTER_H_

/********************************* Includes **********************************/
#include <string.h>
#include <stdio.h>

/**************************** Constants and Types ****************************/
#define TRUE 1
#define FALSE 0

/********************************* Variables *********************************/
extern int SimpleTestCounter;
extern int SimpleTestFailCounter;


/***************************** Exported Functions ****************************/
#define SimpleTest_AssertInteger(IntA, IntB, Message) { SimpleTestCounter++; if(IntA != IntB) { ++SimpleTestFailCounter; return Message; } }
#define SimpleTest_AssertString(StringA, StringB, Message) { SimpleTestCounter++; if (strcmp(StringA, StringB) != 0) { ++SimpleTestFailCounter; return Message; } }
#define SimpleTest_AssertTrue(Condition, Message) { SimpleTestCounter++; if(Condition != TRUE) { ++SimpleTestFailCounter; return Message; } }
#define SimpleTest_AssertFalse(Condition, Message) { SimpleTestCounter++; if(Condition != FALSE) { ++SimpleTestFailCounter; return Message; } }
#define SimpleTest_RunTest(test) do{ char *message = test(); printf("\n * Test no %d ", SimpleTestCounter); if(message) { printf("failed %s\n", message); }else{ printf(" passed\n"); } }while(FALSE);
#define SimpleTest_Initialize() int SimpleTestCounter = 0u; int SimpleTestFailCounter = 0u;
#define SimpleTest_CreateTest(Name) static char* Name(void) {
#define SimpleTest_FinalizeTest() return NULL; }


#endif /* SRC_SIMPLECTESTER_H_ */
