#ifndef ABFORMODEL_H_
#define ABFORMODEL_H_

#define ABFORINITIAL_ ABFORinitial
#define ABFORFORPART1_ ABFORforpart1
#define ABFORFORPART2_ ABFORforpart2
#define ABFORFORPART3_ ABFORforpart3
#define ABFORMJRTY1_ ABFORmjrty1
#define ABFORMJRTY2_ ABFORmjrty2
#define ABFORMJRTY3_ ABFORmjrty3
#define ABFORMJRTY4_ ABFORmjrty4
#define ABFORMJRTY5_ ABFORmjrty5
#define ABFORMJRTY6_ ABFORmjrty6
#define ABFORMJRTY7_ ABFORmjrty7
#define ABFORCHD_ ABFORchd
#define ABFORCHD2_ ABFORchd2
#define ABFOREND_ ABFORend



char ABFORinitial[] = "\n\tpid_t pid;\n\tint pipe_fd_Voter[2];\n\tchar k[50]=\"kill -9 \";\n\tchar chpid[12];\n\tint finish=0;\n\tint respawn=0;";

char ABFORforpart1[] = "\n\tfor(int Num_Voter=0; Num_Voter<Total_Num_Voter, finish!=1; Num_Voter++){\n\t\tint chdpid;\n\t\tif (pipe(pipe_fd_Voter) == -1){\n\t\t\tfprintf(stderr, \"Error: Unable to create pipe.\\n\");\n\t\t\texit(EXIT_FAILURE);\n\t\t}\n\t\tif ((pid = fork()) < 0){\n\t\t\t	fprintf(stderr, \"Error: Unable to fork process.\\n\");\n\t\t\texit(EXIT_FAILURE);\n\t\t}\n\t\tif(pid>0)  //parent\n\t\t{\n\t\t\tprintf(\"Parent Process:%4d\\n\",getpid());\n\t\t\tint time_delay=0;\n\t\t\tclose(pipe_fd_Voter[1]);\n\t\t\tread(pipe_fd_Voter[0],  &chdpid, sizeof(int));\n\t\t\t	printf(\"---Child Process:%4d\\n\",chdpid);\n\t\t\tmemset( k, \'\\0\', strlen(k));\n\t\t\t	memset( chpid, \'\\0\', strlen(chpid));\n\t\t\tstrcpy(k, \"kill -9 \");\n\t\t\tsprintf(chpid, \"%d\", chdpid);\n\t\t\tstrcat(k, chpid);\n\n\t\t\tfor(;finish!=1;){//sleep(1)){\n\t\t\t\tint w_return = waitpid(-1, NULL, WNOHANG|WUNTRACED);\n\t\t\t\tif(w_return == 0 ){  //  >0 when child finish\n\t\t\t\t\tsleep(1);\n\t\t\t\t\ttime_delay++;\n\t\t\t\t\tprintf(\"time_delay++ = %d\\n\",time_delay);\n\t\t\t\t\tif(time_delay== ";

/**CHECK_TIME**/   

char ABFORforpart2[] = " )\n\t\t\t\t\t{\n\t\t\t\t\t\tprintf(\"\\t+++time_delay = %d\\n\",time_delay);\n\t\t\t\t\t\ttime_delay=0;\n\t\t\t\t\t\tsystem(k);//system(\"pgrep -f monitor_fork | xargs kill -9\");\n\t\t\t\t\t\trespawn=1;\n\t\t\t\t\t\tNum_Voter--;\n\t\t\t\t\t\tbreak;\n\t\t\t\t\t}\n\t\t\t\t\telse\n\t\t\t\t\t{\n\t\t\t\t\t\trespawn=0;\n\t\t\t\t\t}\n\t\t\t\t}\n\t\t\t\telse if(w_return > 0 && respawn !=1)// && (time_delay!=0 && time_delay!=CHECK_TIME))\n\t\t\t\t{\n\t\t\t\t\tclose(pipe_fd_Voter[1]);\n\t\t\t\t\t//struct Data *data_Voter = (struct Data *)malloc(sizeof(struct Data));\n\t\t\t\t\t//= malloc(sizeof(*Data));\n\t\t\t\t\tread(pipe_fd_Voter[0], &data[Num_Voter].";


/** #define VOTETYPE  **/

// ", sizeof(";

/** VoteType  **/


char ABFORforpart3[] = "));\n\n\t\t\t\t\tprintf(\"\\n\\trecv:%d, Num_Voter:%d\\n\\n\",data[Num_Voter].i, Num_Voter);\n\n\t\t\t\t\ttime_delay=0;\n\n";
		

char ABFORmjrty1[] = "//------find the candidate of majority voter------//\n\tif(Num_Voter==2){\n\t\tint num_Voter=0;\n\t\t";

	/** VoteType  **/ 

char ABFORmjrty2[] = " v_result;\n\t\tint i_Voter;\n\t\tfor( i_Voter=0; i_Voter<Total_Num_Voter; i_Voter++){\n\t\t\tif(num_Voter==0) {\n\t\t\t\tv_result = data[i_Voter].";

/** #define VOTETYPE  **/

char ABFORmjrty3[] = "; //sprintf( v_result, \"%d\", data[i_Voter]./** #define VOTETYPE  **/ );	//int? float? char?\n\t\t\t\tnum_Voter=1;\n\t\t\t}\n\t\t\telse{  //still be the majority voter\n\t\t\t\tif(data[i_Voter].";

/** #define VOTETYPE  **/

char ABFORmjrty4[] = " !=v_result) num_Voter--;\n\t\t\t\telse num_Voter++;\n\t\t\t}\n\t\t}\n//confirm that the v_result is a really majority voter\n\tnum_Voter = Num_Voter;\n\tfor(i_Voter=0; i_Voter < Total_Num_Voter; i_Voter++) if(data[i_Voter].";

/** #define VOTETYPE  **/

char ABFORmjrty5[] = "!=v_result) num_Voter--;\n\t//if v_result is the majority voter, correct the answer to v_result\n\tif(num_Voter>=(Num_Voter+1)/2) {\n\t\tprintf(\"\\33\\[1;33m \\n\\tCorrect the answer to :\\n\\t%f \\33\\[0m \\n\\n\", v_result);\n\t\t";

		 /** voteName **/

char ABFORmjrty6[] = " = v_result; //return ;  //successful ////p = v_result;\n\n";


//if(Num_Voter==2){
	//for(int dep_i=0; dep_i< /*depVar.size()*/; dep_i++){
//		close(pipe_fd_Voter[1]);
//		read(pipe_fd_Voter[0], &/*depVar[dep_i]*/, sizeof(/** depType  **/));
	//}
//}


char ABFORmjrty7[] = "\n\n\t\tprintf(\"FINISH\\n\");\n\t\tfinish=1;\n\t\trespawn=0;\n\t}\n\telse {\n\t\tprintf(\"\\33\\[1;31m \\n--There doesn't have a majority voter...-- \\33\\[0m \\n\");\n\t\tNum_Voter=0; //Doesn't have a majority voter\n\t}\n}\nelse\n{\n\ttime_delay=0;\n\trespawn=0;\n}\n//------find the candidate of majority voter------//\n\n\t\t\tbreak;\n\t\t}\n\t\telse if(w_return < 0)\n\t\t{\n\t\t\tbreak;\n\t\t}\n\t\t} //for\n\t}  //pid>0\n";

char ABFORchd[] = "\n\telse  // 0 child\n\t{\n\t\tclose(pipe_fd_Voter[0]);\n\t\tchdpid=getpid();\n\t\twrite(pipe_fd_Voter[1], &chdpid, sizeof(int));\n\t\tprintf(\"Child Process:%4d \\t%d\\n\",getpid() ,chdpid);\n\n";


/** work **/


char ABFORchd2[] = "\n\t\tstruct Data *data_chd = (struct Data *)malloc(sizeof(struct Data)); //= malloc(sizeof(*Data));\n\t\tdata_chd->";

/** #define VOTETYPE  **/ 

//	" = ";

/** voteName **/

//";";

//	"\n\t\twrite(pipe_fd_Voter[1], &";

/** voteName  **/

//	", sizeof(";

/** VoteType  **/


//	"));"


//if(Num_Voter==2){
	//for(int dep_i=0; dep_i< /*depVar.size()*/; dep_i++){
//		close(pipe_fd_Voter[0]);
//		write(pipe_fd_Voter[1], &/*depVar[dep_i]*/, sizeof(/** depType  **/));
	//}
//}



char ABFORend[] = "\n\n\t\tfinish=1;\n\t\texit(EXIT_SUCCESS);\n\t}\n}\n\n";


#endif
