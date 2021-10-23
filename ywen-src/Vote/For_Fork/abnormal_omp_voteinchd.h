#ifndef ABOMPMODEL_H_
#define ABOMPMODEL_H_

#define ABOMPWHILEPART1_ ABOMPwhilepart1
#define ABOMPWHILEPART2_ ABOMPwhilepart2
#define ABOMPWHILEPART3_ ABOMPwhilepart3
#define ABOMPWHILEPART4_ ABOMPwhilepart4
#define ABOMPMJRTY1_ ABOMPmjrty1
#define ABOMPMJRTY2_ ABOMPmjrty2
#define ABOMPMJRTY3_ ABOMPmjrty3
#define ABOMPMJRTY4_ ABOMPmjrty4
#define ABOMPMJRTY5_ ABOMPmjrty5
#define ABOMPMJRTY6_ ABOMPmjrty6
#define ABOMPCHD_ ABOMPchd
#define ABOMPEND_ ABOMPend



char ABOMPwhilepart1[] = "\n\tpid_t pid;\n\tint pipe_fd_Voter[2];\n\tchar k[50]=\"kill -9 \";\n\tchar chpid[12];\n\tint finish=0;\n\tint respawn=0;\n\tint Num_Voter=0;\n\twhile(finish!=1){\n\t\tint chdpid;\n\t\tif (pipe(pipe_fd_Voter) == -1){\n\t\t\tfprintf(stderr, \"Error: Unable to create pipe.\\n\");\n\t\t\texit(EXIT_FAILURE);\n\t\t}\n\t\tif ((pid = fork()) < 0){\n\t\t\tfprintf(stderr, \"Error: Unable to fork process.\\n\");\n\t\t\texit(EXIT_FAILURE);\n\t\t}\n\t\tif(pid>0)  //parent\n\t\t{\n\t\t\tprintf(\"Parent Process:%4d\\n\",getpid());\n\t\t\tint time_delay=0;\n\t\t\tclose(pipe_fd_Voter[1]);\n\t\t\tread(pipe_fd_Voter[0],  &chdpid, sizeof(int));\n\t\t\tprintf(\"---Child Process:%4d\\n\",chdpid);\n\t\t\tmemset( k, \'\\0\', strlen(k));\n\t\t\tmemset( chpid, \'\\0\', strlen(chpid));\n\t\t\tstrcpy(k, \"kill -9 \");\n\t\t\tsprintf(chpid, \"%d\", chdpid);\n\t\t\tstrcat(k, chpid);\n\t\t\t//printf(\"\\t\\t\\t\\tCMD:%s\\n\",k);\n\t\t\tfor(;finish!=1;){\n\t\t\t\tint w_return = waitpid(-1, NULL, WNOHANG|WUNTRACED);\n\t\t\t\tif(w_return == 0 ){  //  >0 when child finish\n\t\t\t\t\tsleep(1);\n\t\t\t\t\ttime_delay++;\n\t\t\t\t\tprintf(\"time_delay++ = %d\\n\",time_delay);\n\t\t\t\t\tif(time_delay== ";

		/**CHECK_TIME**/	

char ABOMPwhilepart2[] = " )\n\n\t\t\t\t\t{\n\t\t\t\t\t\tprintf(\"\\t+++time_delay = %d\\n\",time_delay);\n\t\t\t\t\t\ttime_delay=0;\n\t\t\t\t\t\tsystem(k);//system(\"pgrep -f monitor_fork | xargs kill -9\");\n\t\t\t\t\t\trespawn=1;\n\t\t\t\t\t\tbreak;\n\t\t\t\t\t}\n\t\t\t\t\telse\n\t\t\t\t\t{\n\t\t\t\t\t\trespawn=0;\n\t\t\t\t\t}\n\t\t\t\t}\n\t\t\t\telse if(w_return > 0 && respawn !=1)\n\t\t\t\t{\n\t\t\t\t\tclose(pipe_fd_Voter[1]);\n\t\t\t\t\tstruct Data *data_Voter = (struct Data *)malloc(sizeof(struct Data));\n\t\t\t\t\tread(pipe_fd_Voter[0], &data_Voter->";

/** #define VOTETYPE  **/

//	", sizeof(";

/** VoteType  **/

//	"));\n\t\t\t\t\ttime_delay=0;\n\t\t\t\t\t"
		
/** voteName **/

//	" = data_Voter->"

/** #define VOTETYPE  **/

//	";\n"


//if(Num_Voter==2){
	//for(int dep_i=0; dep_i< /*depVar.size()*/; dep_i++){
//		close(pipe_fd_Voter[1]);
//		read(pipe_fd_Voter[0], &/*depVar[dep_i]*/, sizeof(/** depType  **/));
	//}
//}


char ABOMPwhilepart3[] = "\n\t\t\tfinish=1;\n\t\t\tbreak;\n\t\t\t\t}\n\t\t\t\telse if(w_return < 0)\n\t\t\t\t{\n\t\t\t\t\tbreak;\n\t\t\t\t}\n\t\t\t} //for\n\t\t}  //pid>0\n\t\telse  // 0 child\n\t\t{\n\t\t\tclose(pipe_fd_Voter[0]);\n\t\t\tchdpid=getpid();\n\t\t\twrite(pipe_fd_Voter[1], &chdpid, sizeof(int));\n\t\t\tprintf(\"Child Process:%4d \\t%d\\n\",getpid() ,chdpid);\n\t\t\t#pragma omp parallel for num_threads(4)\n\t\t\tfor(Num_Voter=0; Num_Voter<Total_Num_Voter; Num_Voter++){\n\n";


		/**work**/


char ABOMPwhilepart4[] = "\n\t\t\t\tstruct Data *data_chd = (struct Data *)malloc(sizeof(struct Data));\n\t\t\t\tdata[Num_Voter].";


/** #define VOTETYPE  **/

//	" = ";

/** voteName **/

//	";\n\t\t\t}";



char ABOMPmjrty1[] = "\n//------find the candidate of majority voter------//\n\tNum_Voter=2;//if(Num_Voter==2){\n\tint num_Voter=0;\n\t";

/** VoteType  **/ 

char ABOMPmjrty2[] = " v_result;\n\tint i_Voter;\n\tfor( i_Voter=0; i_Voter<Total_Num_Voter; i_Voter++){\n\t\tif(num_Voter==0) {\n\t\t\tv_result = data[i_Voter].";

/** #define VOTETYPE  **/

char ABOMPmjrty3[] = "; //sprintf( v_result, \"%d\", data[i_Voter]./** #define VOTETYPE  **/ );	//int? float? char?\n\t\t\tnum_Voter=1;\n\t\t}\n\t\telse{  //still be the majority voter\n\t\t\tif(data[i_Voter].";

/** #define VOTETYPE  **/

char ABOMPmjrty4[] = "!=v_result) num_Voter--;\n\t\t\telse num_Voter++;\n\t\t}\n\t}\n\t//confirm that the v_result is a really majority voter\n\tnum_Voter = Num_Voter;\n\tfor(i_Voter=0; i_Voter < Total_Num_Voter; i_Voter++) if(data[i_Voter].";

/** #define VOTETYPE  **/

char ABOMPmjrty5[] = "!=v_result) num_Voter--;\n\t//if v_result is the majority voter, correct the answer to v_result\n\tif(num_Voter>=(Num_Voter+1)/2) {\n\t\tprintf(\"\\33\\[1;33m \\n\\tCorrect the answer to :\\n\\t%f \\33\\[0m \\n\\n\", v_result);\n\t\tclose(pipe_fd_Voter[0]);\n\t\twrite(pipe_fd_Voter[1], &v_result , sizeof(";

/** VoteType  **/ 

char ABOMPmjrty6[] = "));\n\t\tprintf(\"FINISH\\n\");\n\t\tfinish=1;\n\t\trespawn=0;\n\t}\n\telse {\n\t\tprintf(\"\\33\\[1;31m \\n--There doesn't have a majority voter...-- \\33\\[0m \\n\");\n\t\tNum_Voter=0; //Doesn't have a majority voter\n\t}\n//------find the candidate of majority voter------//";

//if(Num_Voter==2){
	//for(int dep_i=0; dep_i< /*depVar.size()*/; dep_i++){
//		close(pipe_fd_Voter[0]);
//		write(pipe_fd_Voter[1], &/*depVar[dep_i]*/, sizeof(/** depType  **/));
	//}
//}

char ABOMPend[] = "\n\t\t\tfinish=1;\n\t\t\texit(EXIT_SUCCESS);\n\t\t}\n\t}";



#endif
