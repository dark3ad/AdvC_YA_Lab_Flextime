/* =====================================================================
 * Copyright (c) 2019 YrkesAkademin YH AB
 * Assignment: AdvC_YA_Lab_Flextime (FlextimeMain.c)
 * Student: Patrik Gustafsson
 * All rights reserved.
 * Confidential and Proprietary - YrkesAkademin YH AB
 * =====================================================================
 *
 */

#include "Flextime.h"

 /* ********************************************************************
  * PROGRAM INSTRUCTIONS
  * ********************************************************************
  * Arguments supported: 				2
  * Example arguments usage:			Bjork_209_201945.txt DEBUG
  *
  * Bjork_209_201945.txt				filename of inputfile
  * DEBUG 								debug option switched on
  * *******************************************************************/

_Bool DEBUG = false;

/********************************* Start of Main Program **********************************/

int main(int argc, char* argv[]){

	Stamp time_table[WEEKS][DAYS][STAMPS] = {0};
	Time sum[WEEKS][DAYS] = {0};
	Person employee[IDENTIFY] = {0};
	char *str = NULL, *filename = NULL;
	float *bin = NULL, *export = NULL;
	DEBUG = ARGUMENT_DEBUG;

	printf("\n███████╗██╗     ███████╗██╗  ██╗████████╗██╗███╗   ███╗███████╗\n");
	printf("██╔════╝██║     ██╔════╝╚██╗██╔╝╚══██╔══╝██║████╗ ████║██╔════╝\n");
	printf("█████╗  ██║     █████╗   ╚███╔╝    ██║   ██║██╔████╔██║█████╗\n");
	printf("██╔══╝  ██║     ██╔══╝   ██╔██╗    ██║   ██║██║╚██╔╝██║██╔══╝\n");
	printf("██║     ███████╗███████╗██╔╝ ██╗   ██║   ██║██║ ╚═╝ ██║███████╗\n");
	printf("╚═╝     ╚══════╝╚══════╝╚═╝  ╚═╝   ╚═╝   ╚═╝╚═╝     ╚═╝╚══════╝\n");

	str 		 	=	generic_read(ARGUMENT_FILE, PARAMETER_READTXT);

	filename 		=	handler(FILENAME_DATA, employee);

						input(str, time_table);
	free(str);
						calculate(time_table, sum);

						output(sum, employee);

	export			=	exporter(export,sum);

						write_file(export, filename, PARAMETER_WRITEBIN);
	free(export);

	bin			 	=	generic_read(filename, PARAMETER_READBIN);

	free(filename);
						importer(sum,bin);
	free(bin);
						output(sum, employee);

	return 0;
}
