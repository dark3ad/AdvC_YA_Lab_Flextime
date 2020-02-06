/* =====================================================================
 * Copyright (c) 2019 YrkesAkademin YH AB
 * Assignment: AdvC_YA_Lab_Flextime (FlextimeTestMain.c)
 * Student: Patrik Gustafsson
 * All rights reserved.
 * Confidential and Proprietary - YrkesAkademin YH AB
 * =====================================================================
 *
 */

#include "SimpleCTester.h"

/// supply path to .h file holding function headers of your test target
#include "../src/Flextime.h"


SimpleTest_Initialize()		// Counters for all tests are reset here


/*************************************** Test ******************************************/

/// supply name of your test as parameter
SimpleTest_CreateTest(Test_generic_read)  	// Single test defined
{
	_Bool checker = false;
	int ret;

	char *check_input_string =
	"308,07,23;308,11,44;308,12,31;308,16,30;\r\n309,08,00;309,11,52;309,12,55;309,16,38;\r\n310,07,24;310,11,30;310,12,30;310,16,14;\r\n311,07,45;311,11,58;311,12,26;311,16,27;\r\n312,07,42;312,11,37;312,12,10;312,16,12;\r\n\r\n316,07,15;316,11,39;316,12,31;316,16,53;\r\n317,07,29;317,11,34;317,12,18;317,15,42;\r\n318,07,22;318,11,41;318,12,10;318,16,52;\r\n319,07,23;319,11,32;\r\n";

	char *str 	 =	generic_read("Bjork_209_201945.txt", PARAMETER_READTXT);

	ret = strcmp(str, check_input_string);

	if(ret < 0) {
		checker = false;
		printf("str is less than check_input_string");
	}
	else if(ret > 0) {
		checker = false;
		printf("check_input_string is less than str1");
	}
	else {
		checker = true;
		printf("str is equal to check_input_string");
	}

	free(str);

	/// assert that the outcome of your call matches expected outcome
	SimpleTest_AssertTrue(checker, "generic_read function fault");

}
SimpleTest_FinalizeTest()				// End of test

/***************************************************************************************/
/*************************************** Test ******************************************/

/// supply name of your test as parameter
SimpleTest_CreateTest(Test_generic_read_V2)  	// Single test defined
{
	_Bool checker = false;
	float *export = NULL, *bin = NULL;
	Time sum[WEEKS][DAYS] = {0};

	Stamp time_table[WEEKS][DAYS][STAMPS] ={ {		{{308,07,23},{308,11,44},{308,12,31},{308,16,30}},
													{{309,8,00},{309,11,52},{309,12,55},{309,16,38}},
													{{310,07,24},{310,11,30},{310,12,30},{310,16,14}},
													{{311,07,45},{311,11,58},{311,12,26},{311,16,27}},
													{{312,07,42},{312,11,37},{312,12,10},{312,16,12}} },

											  {		{{0,0,0},{0,0,0},{0,0,0},{0,0,0}},
													{{316,07,15},{316,11,39},{316,12,31},{316,16,53}},
													{{317,07,29},{317,11,34},{317,12,18},{317,15,42}},
													{{318,07,22},{318,11,41},{318,12,10},{318,16,52}},
													{{319,07,23},{319,11,32},{0,0,0},{0,0,0}} } };  // "Bjork_209_201945.txt"
	calculate(time_table, sum);


	export			=	exporter(export,sum);

	bin 	 		=	generic_read("Bjork_209_201945DONE.dat", PARAMETER_READBIN);

	for(int w=0; w<WEEKS; w++){
		for(int d=0; d<DAYS; d++){
			if(fabsf(sum[w][d].time) == fabsf(bin[w*DAYS+d])){
				checker = true;
				printf("sum[%d][%d].time: %0.2f <--> bin[%d]: %0.2f\n", w, d, sum[w][d].time, w*DAYS+d, bin[w*DAYS+d]);

			} else {
				checker = false;
			}

		}
	}

	free(export); free(bin);

	/// assert that the outcome of your call matches expected outcome
	SimpleTest_AssertTrue(checker, "generic_read function fault");
}
SimpleTest_FinalizeTest()				// End of test

/***************************************************************************************/
/*************************************** Test ******************************************/

/// supply name of your test as parameter
SimpleTest_CreateTest(Test_input)  	// Single test defined
{
	typedef struct{
	int dayNum;
	int hour;
	int min;
	}TestStamp;

	_Bool checker = false;
	Stamp time_table[WEEKS][DAYS][STAMPS] = {0};
	TestStamp check_table[WEEKS][DAYS][STAMPS] ={ {		{{308,07,23},{308,11,44},{308,12,31},{308,16,30}},
													{{309,8,00},{309,11,52},{309,12,55},{309,16,38}},
													{{310,07,24},{310,11,30},{310,12,30},{310,16,14}},
													{{311,07,45},{311,11,58},{311,12,26},{311,16,27}},
													{{312,07,42},{312,11,37},{312,12,10},{312,16,12}} },

											  {		{{0,0,0},{0,0,0},{0,0,0},{0,0,0}},
													{{316,07,15},{316,11,39},{316,12,31},{316,16,53}},
													{{317,07,29},{317,11,34},{317,12,18},{317,15,42}},
													{{318,07,22},{318,11,41},{318,12,10},{318,16,52}},
													{{319,07,23},{319,11,32},{0,0,0},{0,0,0}} } };  // "Bjork_209_201945.txt"
	char str[] =
	"308,07,23;308,11,44;308,12,31;308,16,30;\r\n"
	"309,08,00;309,11,52;309,12,55;309,16,38;\r\n"
	"310,07,24;310,11,30;310,12,30;310,16,14;\r\n"
	"311,07,45;311,11,58;311,12,26;311,16,27;\r\n"
	"312,07,42;312,11,37;312,12,10;312,16,12;\r\n"
	"\r\n"
	"316,07,15;316,11,39;316,12,31;316,16,53;\r\n"
	"317,07,29;317,11,34;317,12,18;317,15,42;\r\n"
	"318,07,22;318,11,41;318,12,10;318,16,52;\r\n"
	"319,07,23;319,11,32;\r\n"; // "Bjork_209_201945.txt"

	input(str, time_table);

	printf("Minutes every day crosscheck - Hardcoded manual input / tables\n");
	for(int w=0; w<WEEKS; w++){
		for(int d=0; d<DAYS; d++){
			for(int s=0; s<STAMPS; s++){
				if(time_table[w][d][s].min == check_table[w][d][s].min){
					printf("time_table[%d][%d][%d].min: %d <--> check_table[%d][%d][%d].min: %d\n", w,w*DAYS+d,s, time_table[w][d][s].min, w,w*DAYS+d,s, check_table[w][d][s].min);
					checker = true;
				} else {
					checker = false;
				}
			}
		}
	}

	/// assert that the outcome of your call matches expected outcome
	SimpleTest_AssertTrue(checker, "input function fault");

}
SimpleTest_FinalizeTest()				// End of test

/***************************************************************************************/
/*************************************** Test ******************************************/

/// supply name of your test as parameter
SimpleTest_CreateTest(Test_check_daynumber)  	// Single test defined
{
	_Bool checker = false;
	Stamp time_table[WEEKS][DAYS][STAMPS] ={ {		{{308,07,23},{308,11,44},{308,12,31},{308,16,30}},
													{{309,8,00},{309,11,52},{309,12,55},{309,16,38}},
													{{310,07,24},{310,11,30},{310,12,30},{310,16,14}},
													{{311,07,45},{311,11,58},{311,12,26},{311,16,27}},
													{{312,07,42},{312,11,37},{312,12,10},{312,16,12}} },

											  {		{{0,0,0},{0,0,0},{0,0,0},{0,0,0}},
													{{316,07,15},{316,11,39},{316,12,31},{316,16,53}},
													{{317,07,29},{317,11,34},{317,12,18},{317,15,42}},
													{{318,07,22},{318,11,41},{318,12,10},{318,16,52}},
													{{319,07,23},{319,11,32},{0,0,0},{0,0,0}} } };  // "Bjork_209_201945.txt"

	check_daynumber(time_table);

	if(time_table[1][0][0].dayNum == 315 && time_table[1][0][3].dayNum == 315){
		checker = true;
	}
	else{
		checker = false;
	}

	printf("Daynumber: time_table[1][0][0].dayNum: %d", time_table[1][0][0].dayNum);


	/// assert that the outcome of your call matches expected outcome
	SimpleTest_AssertTrue(checker, "input/check_daynumber function fault");

}
SimpleTest_FinalizeTest()				// End of test

/***************************************************************************************/
/*************************************** Test ******************************************/

/// supply name of your test as parameter
SimpleTest_CreateTest(Test_calculate)  	// Single test defined
{
	_Bool checker = false;
	Time sum[WEEKS][DAYS] = {0};

	Stamp time_table[WEEKS][DAYS][STAMPS] ={ {		{{308,07,23},{308,11,44},{308,12,31},{308,16,30}},
													{{309,8,00},{309,11,52},{309,12,55},{309,16,38}},
													{{310,07,24},{310,11,30},{310,12,30},{310,16,14}},
													{{311,07,45},{311,11,58},{311,12,26},{311,16,27}},
													{{312,07,42},{312,11,37},{312,12,10},{312,16,12}} },

											  {		{{0,8,0},{0,0,0},{0,0,0},{0,16,0}},
													{{316,07,15},{316,11,39},{316,12,31},{316,16,53}},
													{{317,07,29},{317,11,34},{317,12,18},{317,15,42}},
													{{318,07,22},{318,11,41},{318,12,10},{318,16,52}},
													{{319,07,23},{319,11,32},{0,0,0},{0,0,0}} } };  // "Bjork_209_201945.txt"

	sum[1][0].day = 2;
	sum[1][0].time = 9;

	float correct_time = 8;

	calculate(time_table, sum);

	if(fabsf(sum[1][0].time) == fabsf(correct_time)){
		if(sum[1][0].day == 1)
		checker = true;
	}
	else{
		checker = false;
	}

	printf("Day: sum[1][0].day: %d\n", sum[1][0].day);
	printf("Time: sum[1][0].time: %0.2f (crosschecked w/  correct_time: %0.2f)", sum[1][0].time, correct_time);

	/// assert that the outcome of your call matches expected outcome
	SimpleTest_AssertTrue(checker, "calculate function fault");

}
SimpleTest_FinalizeTest()				// End of test

/***************************************************************************************/
/*************************************** Test ******************************************/

/// supply name of your test as parameter
SimpleTest_CreateTest(Test_exporter)  	// Single test defined
{
	_Bool checker = false;
	Time sum[WEEKS][DAYS] = {0};
	float *export = NULL;

	Stamp time_table[WEEKS][DAYS][STAMPS] ={ {		{{308,07,23},{308,11,44},{308,12,31},{308,16,30}},
													{{309,8,00},{309,11,52},{309,12,55},{309,16,38}},
													{{310,07,24},{310,11,30},{310,12,30},{310,16,14}},
													{{311,07,45},{311,11,58},{311,12,26},{311,16,27}},
													{{312,07,42},{312,11,37},{312,12,10},{312,16,12}} },

											  {		{{0,8,0},{0,0,0},{0,0,0},{0,16,0}},
													{{316,07,15},{316,11,39},{316,12,31},{316,16,53}},
													{{317,07,29},{317,11,34},{317,12,18},{317,15,42}},
													{{318,07,22},{318,11,41},{318,12,10},{318,16,52}},
													{{319,07,23},{319,11,32},{0,0,0},{0,0,0}} } };  // "Bjork_209_201945.txt"

	calculate(time_table, sum);


	export			=	exporter(export,sum);

	for(int w=0; w<WEEKS; w++){
		for(int d=0; d<DAYS; d++){
				if(fabsf(export[w*DAYS+d]) == fabsf(sum[w][d].time)){
					checker = true;
					printf("export[%d]: %0.2f <--> sum[%d][%d].time: %0.2f\n", export[w*DAYS+d], w*DAYS+d, w*1, d, sum[w][d].time);

				} else{
					checker = false;
				}

		}
	}

	free(export);

	/// assert that the outcome of your call matches expected outcome
	SimpleTest_AssertTrue(checker, "exporter function fault");

}
SimpleTest_FinalizeTest()				// End of test

/***************************************************************************************/
/*************************************** Test ******************************************/

/// supply name of your test as parameter
SimpleTest_CreateTest(Test_write_file)  	// Single test defined
{
	_Bool checker = false;
	Time sum[WEEKS][DAYS] = {0};
	float *export = NULL, *bin = NULL;
	size_t n = WORKINGDAYS_TWO_WEEKS;

	Stamp time_table[WEEKS][DAYS][STAMPS] ={ {		{{308,07,23},{308,11,44},{308,12,31},{308,16,30}},
													{{309,8,00},{309,11,52},{309,12,55},{309,16,38}},
													{{310,07,24},{310,11,30},{310,12,30},{310,16,14}},
													{{311,07,45},{311,11,58},{311,12,26},{311,16,27}},
													{{312,07,42},{312,11,37},{312,12,10},{312,16,12}} },

											  {		{{0,8,0},{0,0,0},{0,0,0},{0,16,0}},
													{{316,07,15},{316,11,39},{316,12,31},{316,16,53}},
													{{317,07,29},{317,11,34},{317,12,18},{317,15,42}},
													{{318,07,22},{318,11,41},{318,12,10},{318,16,52}},
													{{319,07,23},{319,11,32},{0,0,0},{0,0,0}} } };  // "Bjork_209_201945.txt"

	calculate(time_table, sum);

	export			=	exporter(export,sum);


	write_file(export, "Bjork_forTEST.dat", PARAMETER_WRITEBIN);
	printf("write-file success: Bjork_forTEST.dat was created\n");

	bin 	 		=	generic_read("Bjork_forTEST.dat", PARAMETER_READBIN);

	checker = (! memcmp(export, bin, n * sizeof(float)));

	for(int w=0; w<WEEKS; w++){
		for(int d=0; d<DAYS; d++){
				if(checker == true){
					printf("write-file success: values match! export[%d]: %0.2f <--> bin[%d]: %0.2f\n", w*DAYS+d, export[w*DAYS+d], w*DAYS+d, bin[w*DAYS+d]);

				} else{
					checker = false;
				}

		}
	}

	free(export);	free(bin);


	/// assert that the outcome of your call matches expected outcome
	SimpleTest_AssertTrue(checker, "write_file function fault");

}
SimpleTest_FinalizeTest()				// End of test

/***************************************************************************************/
/*************************************** Test ******************************************/

/// supply name of your test as parameter
SimpleTest_CreateTest(Test_importer)  	// Single test defined
{
	_Bool checker = false;
	Time sum[WEEKS][DAYS] = {0};
	float *bin=NULL;

	bin 	 		=	generic_read("Bjork_forTEST.dat", PARAMETER_READBIN);

	importer(sum,bin);

	if(fabsf(sum[1][0].time) != 0){
		checker = true;
		printf("import: success! values have been imported\n");
		for(int w=0; w<WEEKS; w++){
			for(int d=0; d<DAYS; d++){
				printf("imported values: sum[%d][%d].time: %0.2f\n", w*1, d, sum[w][d].time);
			}
		}
	} else{
		checker = false;
	}


	free(bin);

	/// assert that the outcome of your call matches expected outcome
	SimpleTest_AssertTrue(checker, "importer function fault");

}
SimpleTest_FinalizeTest()				// End of test

/***************************************************************************************/



/*#########################################################################################
  #####################################				#######################################
  #####################################    BATCH 	#######################################
  #####################################				#######################################
  #########################################################################################*/

// This is where we add up all tests to be run
static char* test_batch()
{
	/// supply info for presentation of outcome of test batch
	printf("\n Running tests for %s \n\n", "Flextime project");

	/// supply name of each test as parameter
	SimpleTest_RunTest(Test_generic_read);		// One test runs
	SimpleTest_RunTest(Test_generic_read_V2);		// One test runs
	SimpleTest_RunTest(Test_input);		// One test runs
	SimpleTest_RunTest(Test_check_daynumber);		// One test runs
	SimpleTest_RunTest(Test_calculate);		// One test runs
	SimpleTest_RunTest(Test_exporter);		// One test runs
	SimpleTest_RunTest(Test_write_file);		// One test runs
	SimpleTest_RunTest(Test_importer);		// One test runs



	return NULL;
}

/******************************************************************************************/
/********************************* Test Application Main **********************************/
/******************************************************************************************/

_Bool DEBUG = false; // Flextime project

int main(int argc, char* argv[])
{

	test_batch();						// complete batch of tests will be run

	printf("\n\n Tests completed: %d", SimpleTestCounter);	// always present total number of tests run

	if( SimpleTestFailCounter == 0){
		printf("\n All tests passed!"); 			// if batch is successful
	}
	else{
		printf("\n Tests failed: %d", SimpleTestFailCounter); 	// otherwise the first failed test will be presented
	}

	return 0;
}
