/* =====================================================================
 * Copyright (c) 2019 YrkesAkademin YH AB
 * Assignment: AdvC_YA_Lab_Flextime (Flextime.h)
 * Student: Patrik Gustafsson
 * All rights reserved.
 * Confidential and Proprietary - YrkesAkademin YH AB
 * =====================================================================
 *
 */

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/********************************* Header file **********************************/

#ifndef FLEXTIME_H_
#define FLEXTIME_H_

#define WEEKS					2
#define DAYS					5
#define DAYS_PER_YEAR			365
#define STAMPS					4
#define FIRST_STAMP				0
#define SECOND_STAMP			1
#define THIRD_STAMP				2
#define FOURTH_STAMP			3
#define ONE_STAMP				3
#define HOUR_MINUTES_CONV		60
#define WORKING_HOURS_PER_WEEK	40
#define FIRST_STEP				0
#define SECOND_STEP				1
#define THIRD_STEP				2
#define WORKINGDAYS_TWO_WEEKS	10
#define FROM_FIRST_START		0
#define IDENTIFY				1
#define ONE_STEP				1
#define SATURDAY_AND_SUNDAY		2
#define STAMP_SEPERATOR			';'
#define PARAMETER_WRITEBIN		"wb"
#define PARAMETER_READBIN		"rb"
#define PARAMETER_READTXT		"rt"
#define CR_CARRIAGE_RETURN		"\r"
#define LF_LINE_FEED			"\n"
#define FILE_ENDING				"."
#define NULL_CHAR				"\0"
#define PART_STAMP_SEPERATOR	",;"
#define FILENAME_PART_SEPERATOR	"_"
#define ARGUMENT_FILE			argv[1]
#define ARGUMENT_DEBUG			argv[2]
#define FILENAME_DATA			argv

typedef struct{
int dayNum;
int hour;
int min;
}Stamp;

typedef struct{
int day;
float time;
}Time;

typedef struct{
char *name;
char *no;
char *period;
}Person;

/* ------------------- function calculate --------------------------
calculate actual working time for each day, sum up for the entire period.
input - 3-dim time_table struct(Stamp), 3-dim sum struct(Time)
output - none
-------------------------------------------------------------------- */
void calculate(Stamp time_table[WEEKS][DAYS][STAMPS], Time sum[WEEKS][DAYS]);

/* ------------------- function output -----------------------------
presentation of actual working time for each day, sum up for the entire period.
input - employee struct(Person), 3-dim sum struct(Time)
output - none
-------------------------------------------------------------------- */
void output(Time sum[WEEKS][DAYS], Person employee[IDENTIFY]);

/* ------------------- function input ------------------------------
converts raw data into a multi dimensional array holding indexes for week, day, time.
input - char *str pointer, 3-dim time_table struct(Stamp)
output - none
-------------------------------------------------------------------- */
void input(char *str, Stamp time_table[WEEKS][DAYS][STAMPS]);

/* ------------------- function generic_read -----------------------
generic function to read filecontent and typecast as desired datatype
input - char *file pointer(filename), char *fileconfig pointer(read/write/x parameter)
output - void pointer, typecast as desired (in)datatype
-------------------------------------------------------------------- */
void* generic_read(char *file, char *fileconfig);

/* ------------------- function handler ----------------------------
handler for filedetails in/from filename and assign the details from its parts into a struct.
simplifying a 'filename' variable for to reach the desired file-address(set by argument)
and for handling new filename to be exported as *DONE.dat.
input - char *file pointer(argv[1])[FILE-ARGUMENT], MACRO parameter as char *fileconfig
output - char filename, holder of the new filename to be exported as *DONE.dat
-------------------------------------------------------------------- */
char* handler(char *argv[], Person employee[IDENTIFY]);

/* ------------------- function exporter ---------------------------
export function to export period worktime for days to a .dat file.
input - float export(local var in Main-program), 3-dim sum struct(Time)
output - float export, sum of workingtime per day
-------------------------------------------------------------------- */
float* exporter(float *export, Time sum[WEEKS][DAYS]);

/* ------------------- function importer ---------------------------
import details from a .dat file into 3-dim sum struct(Time)
input - 3-dim sum struct(Time), float *bin pointer
output - none
-------------------------------------------------------------------- */
void importer(Time sum[WEEKS][DAYS], float *bin);

/* ------------------- function write_file -------------------------
write file according to parameter selection, filled with preselected
datatype float (as per assignment) and values from variable export
input - float export(local var in Main-program), char *file pointer(filename), MACRO parameter as char *fileconfig
output - none              (actual file-output argument 1 *DONE.dat-file)
-------------------------------------------------------------------- */
void write_file(float *export, char *file, char *fileconfig);

/* ------------------- function check_daynumber --------------------
check daynumber if correct, else corrects it
input - 3-dim time_table struct(Stamp)
output - none
-------------------------------------------------------------------- */
void check_daynumber(Stamp time_table[WEEKS][DAYS][STAMPS]);


#endif /* FLEXTIME_H_ */
