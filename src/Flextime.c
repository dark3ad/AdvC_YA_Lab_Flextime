/* =====================================================================
 * Copyright (c) 2019 YrkesAkademin YH AB
 * Assignment: AdvC_YA_Lab_Flextime (Flextime.c)
 * Student: Patrik Gustafsson
 * All rights reserved.
 * Confidential and Proprietary - YrkesAkademin YH AB
 * =====================================================================
 *
 */

#include "Flextime.h"

extern _Bool DEBUG;

/********************************* Source file **********************************/

void calculate(Stamp time_table[WEEKS][DAYS][STAMPS], Time sum[WEEKS][DAYS]){

	float sum_pos = 0, sum_neg = 0, result = 0;
	int w, d, sp, sn;

	for(w=0; w<WEEKS; w++){
		for(d=0; d<DAYS; d++){
			for(sp=0; sp<STAMPS; sp++){
				sum_pos += time_table[w][d][sp].hour * HOUR_MINUTES_CONV + time_table[w][d][sp].min; // All stamps added to sum
			}
			for(sn=1; sn<STAMPS; sn++, ++sn){
				sum_neg += time_table[w][d][sn].hour * HOUR_MINUTES_CONV + time_table[w][d][sn].min; // Time negative placed in holder
			} sum_pos -= sum_neg; // Remove the negative stamps from sum

			result = (sum_neg - sum_pos) / HOUR_MINUTES_CONV; // Calculate actual working time and result
			result = fabsf(result);
			sum[w][d].day = d+1; // Daynumber
			sum[w][d].time = result; // Time of day stamped in
			result = 0, sum_pos = 0, sum_neg = 0; // Reset counter
		}
	}

}

void output(Time sum[WEEKS][DAYS], Person employee[IDENTIFY]){

	float period = 0, diff = 0;
	int w, d;

	printf("\n***********************************************************");
	printf("\nPrintout imported file\n");
	printf("***********************************************************\n");
	printf("\nName: %s \tEmployee no: %s \tPeriod: %s\n\n", employee->name, employee->no, employee->period);
	printf("Overview\tDay1\tDay2\tDay3\tDay4\tDay5\n");
	for(w=0; w<WEEKS; w++){
		printf("\nWeek %d\t\t", w+1);
		for(d=0; d<DAYS; d++){
			printf("%0.2f\t", sum[w][d].time);
			period += sum[w][d].time; // Collect all positive stamp time, actual working time
		}
		diff = period - 2*WORKING_HOURS_PER_WEEK; // Remove 2 * 40h weeks and get the diff in time
	}
	printf("\n\nPeriod time: \t%0.2f (%0.2f)\n", period, diff); // Presentation
	printf("\n***********************************************************\n");

}

void input(char *str, Stamp time_table[WEEKS][DAYS][STAMPS]){

	int a, b, c, w, d, s, sx, step = 0, counter = 0, temp_table[WEEKS][DAYS][STAMPS][ONE_STAMP] = {0};
	char *part_table[WEEKS][DAYS], *input_str[strlen(str)];
	char *part_day_str = NULL, *p1 = NULL, *p2 = NULL;
	const char *dummy_stamp = "000,00,00;";
	char *dummy_string = "000,07,00;000,11,00;000,12,00;000,16,00;";

	for(w=0; w<WEEKS; w++){
		for(d=0; d<DAYS; ++d){
			part_day_str = malloc(sizeof(char) * (strlen(str)/(DAYS*WEEKS)) );
			part_day_str = strsep(&str, LF_LINE_FEED); // Each day/line marker of day input

			part_table[w][d] = malloc(sizeof(char) * (WEEKS*DAYS*STAMPS*ONE_STAMP) );
			strcpy(part_table[w][d],part_day_str); // Copy whatever one day holds
			strtok((char *)part_table[w][d], CR_CARRIAGE_RETURN); // remove CARRIAGE RETURN \r

			p1 = strchr(part_table[w][d], STAMP_SEPERATOR); // search for ; seperator of stamps, if empty
			if(p1 == NULL) part_table[w][d] = dummy_string; // If whole string is absent/missing stamp

			p2 = strchr(part_table[w][d], STAMP_SEPERATOR);// search for ; seperator of stamps, if not empty
			while(p2 != NULL){ // Checking each stamp
				p2 = strchr(p2+ONE_STEP, STAMP_SEPERATOR); // check how many they are
				++counter;
			}
			while(p2 == NULL && counter < STAMPS){ // If part of the stamps is absent/missing (under 4)
				strcat(part_table[w][d],dummy_stamp); // then add a dummy-stamp for now
				++counter;
			}
			strcat(input_str,part_table[w][d]); // when its done, send it to the input_str (which is next below)
			counter=0; part_day_str=NULL; p1=NULL, p2=NULL;
		}
	}

	char* part_string = strtok((char *)input_str, NULL_CHAR); // load the corrected indata from block above
	for(w=0; w<WEEKS; w++){
		for(d=0; d<DAYS; d++){
			for(s=0; s<STAMPS; s++){
				step = 0;
				for(sx=0; sx<ONE_STAMP; sx++){
					strsep(&part_string, PART_STAMP_SEPERATOR); // now seperate parts by stamp, and also daynumber/hour/minutes ;,
					if(step == FIRST_STEP)
						for(a=FIRST_STEP; a<FIRST_STEP+ONE_STEP; a++){
							temp_table[w][d][s][a] = atoi(part_string); // input to a temp_table
							time_table[w][d][s].hour = temp_table[w][d][s][a]; // downsize it to appropriate 3-dim table , for HOUR
						}
					if(step == SECOND_STEP)
						for(b=SECOND_STEP; b<SECOND_STEP+ONE_STEP; b++){
							temp_table[w][d][s][b] = atoi(part_string);
							time_table[w][d][s].min = temp_table[w][d][s][b]; // as above, for MINUTES
						}
					if(step == THIRD_STEP)
						for(c=THIRD_STEP; c<THIRD_STEP+ONE_STEP; c++){
							temp_table[w][d][s][c] = atoi(part_string);
							time_table[w][d][s].dayNum = temp_table[w][d][s][c]; // as above, for DAYNUMBER
						}
					step++;
				}
			}
		}
	}
	check_daynumber(time_table); // function to check and correct if any daynumber is missing or as a dummy

}

void* generic_read(char *file, char *fileconfig){ // function for reading. generic that can be typecasted as wanted datatype from caller.

	void *buf = NULL;
	int file_size, read_size;
	FILE *fpnt;

	if((fpnt=fopen(file, fileconfig)) == NULL ){
		printf("\n Cannot access or find the requested file!");
		exit(1);
	}

	if(fpnt){
		fseek(fpnt, 0, SEEK_END);
		file_size = ftell(fpnt);
		rewind(fpnt);

		buf = malloc(sizeof(char) * (file_size + 1) );
		read_size = fread(buf, sizeof(char), file_size, fpnt);

		if(file_size != read_size){
			free(buf);
			buf = NULL;
		}

	} fclose(fpnt);

	printf("\n<- File %s has been imported\n", file);

	return buf;
}

char* handler(char *argv[], Person employee[IDENTIFY]){ // function take care of Filename and handle collect this/its details/information

	const char *end_part_str = "DONE.dat";
	char *name = NULL, *holder_str = NULL;
	int str_size, str_read;

	if((name = (char *) malloc(sizeof(char) * (strlen(ARGUMENT_FILE) + 1))) == NULL ){
		printf("\n Cannot allocate memory !!!");
		exit(1);
	} name = ARGUMENT_FILE;

	str_read = strlen(name) + 1;

	strtok((char *)name, FILE_ENDING);

	holder_str = strsep(&name, FILENAME_PART_SEPERATOR);
	str_size = strlen(holder_str);
	employee->name = malloc(sizeof(char) * (str_size + 1) );
	employee->name = holder_str;

	holder_str = strsep(&name, FILENAME_PART_SEPERATOR);
	str_size = strlen(holder_str);
	employee->no = malloc(sizeof(char) * (str_size + 1) );
	employee->no = holder_str;

	holder_str = strsep(&name, FILENAME_PART_SEPERATOR);
	str_size = strlen(holder_str);
	employee->period = malloc(sizeof(char) * (str_size + 1) );
	employee->period = holder_str;

	char *filename = malloc(sizeof(char) * (str_read + strlen(end_part_str)) );

	strcpy(filename,employee->name);
	strcat(filename,FILENAME_PART_SEPERATOR);
	strcat(filename,employee->no);
	strcat(filename,FILENAME_PART_SEPERATOR);
	strcat(filename,employee->period);
	strcat(filename,end_part_str);

	return filename;
}

float* exporter(float *export, Time sum[WEEKS][DAYS]){ // function to prepare exportvalues

	int w, d;

	export = malloc(sizeof(float) * (WORKINGDAYS_TWO_WEEKS) );

	for(w=0; w<WEEKS; w++){
		for(d=0; d<DAYS; d++){
			export[w*DAYS+d] = sum[w][d].time;
			if(DEBUG){
				printf("\n *** DEBUG *** exporter value %0.2f\n", export[w*DAYS+d]);
				if (_Generic(export[w*DAYS+d], float: 1, default: 0)){
					printf(" *** DEBUG *** datatype float\n");
				}
			}
		}
	}

	return export;
}

void importer(Time sum[WEEKS][DAYS], float *bin){ // function to import values into program from bin file

	int w, d;

	for(w=0; w<WEEKS; w++){
		for(d=0; d<DAYS; d++){
			sum[w][d].time = bin[w*DAYS+d];
			if(DEBUG){
				printf("\n *** DEBUG *** importer value %0.2f\n", sum[w][d].time);
				if (_Generic(sum[w][d].time, float: 1, default: 0)){
					printf(" *** DEBUG *** datatype float\n");
				}
			}
		}
	}

}

void write_file(float *export, char *file, char *fileconfig){

	FILE *fpnt;

	fpnt=fopen(file, fileconfig);
	fwrite(export, sizeof(float), WORKINGDAYS_TWO_WEEKS, fpnt);
	fclose(fpnt);

	printf("\n-> File %s has been exported\n", file);

}

void check_daynumber(Stamp time_table[WEEKS][DAYS][STAMPS]){

	int *first_day = &time_table[FROM_FIRST_START][FROM_FIRST_START][FROM_FIRST_START].dayNum;
	int i, counter = 0, first_day_ret = 0;

	if (*first_day == 0){
		while(*first_day == 0){
			counter++;
			if(counter == WORKINGDAYS_TWO_WEEKS/WEEKS) counter += SATURDAY_AND_SUNDAY;
			first_day += (WORKINGDAYS_TWO_WEEKS+SATURDAY_AND_SUNDAY);
		}
		first_day_ret = *first_day - counter;
	}
	else{
		first_day_ret = *first_day;
	}

	first_day = &time_table[FROM_FIRST_START][FROM_FIRST_START][FROM_FIRST_START].dayNum;
	for(i = 0; i < WORKINGDAYS_TWO_WEEKS+2 ; i++){
		if(i == (WORKINGDAYS_TWO_WEEKS/WEEKS)) i += SATURDAY_AND_SUNDAY;
		*first_day = first_day_ret + i;
		first_day += (WORKINGDAYS_TWO_WEEKS+SATURDAY_AND_SUNDAY);
	}

	for(int w=0; w<WEEKS; w++){
		for(int d=0; d<DAYS; d++){
			for(int s=0; s<STAMPS; s++){
				if(time_table[w][d][SECOND_STAMP].dayNum != time_table[w][d][FIRST_STAMP].dayNum)
				time_table[w][d][SECOND_STAMP].dayNum = time_table[w][d][FIRST_STAMP].dayNum; // correct all other stamps that day
				if(time_table[w][d][THIRD_STAMP].dayNum != time_table[w][d][FIRST_STAMP].dayNum)
				time_table[w][d][THIRD_STAMP].dayNum = time_table[w][d][FIRST_STAMP].dayNum;  // correct all other stamps that day
				if(time_table[w][d][FOURTH_STAMP].dayNum != time_table[w][d][FIRST_STAMP].dayNum)
				time_table[w][d][FOURTH_STAMP].dayNum = time_table[w][d][FIRST_STAMP].dayNum;  // correct all other stamps that day
				if(DEBUG){
					printf("\n *** DEBUG *** daynumber values per stamp %d\n", time_table[w][d][s].dayNum);
					if (_Generic(time_table[w][d][s].dayNum, int: 1, default: 0)){
						printf(" *** DEBUG *** datatype int\n");
					}
				}
			}
		}
	}

}
