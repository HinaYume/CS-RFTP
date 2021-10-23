#ifndef ABMFMODEL_H_
#define ABMFMODEL_H_

#define ABMFINITIAL_ ABMFinitial
#define ABMFWHILEPART1_ ABMFforpart1
#define ABMFWHILEPART2_ ABMFforpart2
#define ABMFWHILEPART3_ ABMFforpart3
#define ABMFWHILEPART4_ ABMFforpart4
#define ABMFWHILEPART5_ ABMFforpart5
#define ABMFMJRTY1_ ABMFmjrty1
#define ABMFMJRTY2_ ABMFmjrty2
#define ABMFMJRTY3_ ABMFmjrty3
#define ABMFMJRTY4_ ABMFmjrty4
#define ABMFMJRTY5_ ABMFmjrty5
#define ABMFMJRTY6_ ABMFmjrty6
#define ABMFMJRTY7_ ABMFmjrty7
#define ABMFEND_ ABMFPend


char ABMFinitial[] = "\n\tpid_t pid;\n\tint pipe_fd_Voter[2];\n\tint pipe_fd_Voter2[2];\n\tchar k[3][50];\n\tchar chpid[3][12];\n\tint finish=0;\n\tint respawn=0;\n\tint process_num=Total_Num_Voter+1;\n\tint wait_chd;\n\tint round_num=0;\n\tint dep_process=0;\n\tint kill_count=0;\n\tint chdpid;\n";

char ABMFforpart1[] = "\n\tif (pipe(pipe_fd_Voter2) == -1){\n\t\tfprintf(stderr, \"Error: Unable to create pipe.\\n\");\n\t\texit(EXIT_FAILURE);\n\t}\n\tif ((pid = fork()) < 0){\n\t\tfprintf(stderr, \"Error: Unable to fork process.\\n\");\n\t\texit(EXIT_FAILURE);\n\t}\n\tfor(round_num=0; round_num<2, finish==0; round_num++){\n\t\tif(pid>0)  //parent\n\t\t{\n\n\tif(round_num==0){\n\t\tfor(int num=0; num<Total_Num_Voter; num++){\n\t\t\tif(pid > 0){\n\n\t\tif (pipe(pipe_fd_Voter) == -1){\n\t\t\tfprintf(stderr, \"Error: Unable to create pipe.\\n\");\n\t\t\texit(EXIT_FAILURE);\n\t\t}\n\t\tpid = fork();\n\t\tif(num==(Total_Num_Voter-1) && pid == 0) dep_process=1;\n\tif(pid==0){\n\t\t\tclose(pipe_fd_Voter[0]);\n\t\t\tchdpid=getpid();\n\t\t\twrite(pipe_fd_Voter[1], &chdpid, sizeof(int));\n\t\t\t//chdpid = getpid();\n\t\t\tprintf(\"\\n\\t***Child Process:%4d\\n\",chdpid);\n\t}\n\telse if(pid > 0){\n\t\tclose(pipe_fd_Voter[1]);\n\t\tread(pipe_fd_Voter[0],  &chdpid, sizeof(int));\n\t\tprintf(\"\\n\\t---Child Process:%4d\\n\",chdpid);\n\t\tmemset( k[num], \'\\0\', strlen(k[num]));\n\t\tmemset( chpid[num], \'\\0\', strlen(chpid[num]));\n\t\tstrcpy(k[num], \"kill -9 \");\n\t\tsprintf(chpid[num], \"%d\", chdpid);\n\t\tstrcat(k[num], chpid[num]);\n\t\t//printf(\"\\t\\t\\t\\tCMD:%s\\n\",k[num]);\n\t}\n\t\t\t}\n\t\t}\n\t} //if(round_num==0){\n\n\tif(pid > 0){//if(round_num==1){\n\t\tprintf(\"Parent Process:%4d\\n\",getpid());\n\t\tint time_delay=0;\n\t\tfor(;finish!=1;){\n\t\t\tint w_return = waitpid(-1, NULL, WNOHANG|WUNTRACED);\n\t\t\tif(w_return == 0 ){  //  >0 when child finish\n\t\t\t\tsleep(1);\n\t\t\t\ttime_delay++;\n\t\t\t\tprintf(\"time_delay++ = %d\\n\",time_delay);\n\t\t\t\tif(time_delay == ";

	/**CHECK_TIME**/	

char ABMFforpart2[] = " )\n\t\t\t\t{\n\t\t\t\t\tprintf(\"\\t+++time_delay = %d\\n\",time_delay);\n\t\t\t\t\ttime_delay=0;\n\n\t\tfor(int num=0; num<Total_Num_Voter; num++){\n\t\t\tsystem(k[num]);//system(\"pgrep -f monitor_fork | xargs kill -9\");\n\t\t\tprintf(\"\\t\\t\\t\\tEnd:%s\\n\",k[num]);\n\t\t}\n\n\t\t\t\tkill_count=0;\n\t\t\t\trespawn=1;\n\t\t\t\tprocess_num=Total_Num_Voter;\n\t\t\t\tround_num=-1;\n\t\t\t\tdep_process=0;\n\t\t\t\tbreak;\n\t\t\t}\n\t\t\telse\n\t\t\t{\n\t\t\t\trespawn=0;\n\t\t\t}\n\t\t}\n\t\telse if(w_return > 0 && respawn !=1)// && (time_delay!=0 && time_delay!=CHECK_TIME))\n\t\t{\n\t\t\tprocess_num--;\n\t\t\tprintf(\"\\n\\t\\t\\t+++ process_num:%d\\n\\n\", process_num);\n\t\t\tif(process_num != Total_Num_Voter)\n\t\t\t{\n\t\t\t\tclose(pipe_fd_Voter2[1]);\n\t\t\t\t//struct Data *data_Voter = (struct Data *)malloc(sizeof(struct Data));\n\t\t\t\t//= malloc(sizeof(*Data));\n\t\t\t\tread(pipe_fd_Voter2[0], &data[process_num].";

/** #define VOTETYPE  **/

//	", sizeof(";

/** VoteType  **/

//	"));\n";

char ABMFforpart3[] = "\n\t\t\t\tprintf(\"\\n\\trecv:%d, process_num:%d\\n\\n\",data[process_num].i, process_num);\n\t\t\t}\n\t\t\ttime_delay=0;\n\t\t\tif(process_num==0){ //(Total_Num_Voter-1)){";


char ABMFmjrty1[] = "\n\n//------find the candidate of majority voter------//\n//if(Num_Voter==2){\n\tint num_Voter=0;\n\t";

/** VoteType  **/

char ABMFmjrty2[] = " v_result;\n\n\tint i_Voter;\n\tfor( i_Voter=0; i_Voter<Total_Num_Voter; i_Voter++){\n\t\tif(num_Voter==0) {\n\t\t\tv_result = data[i_Voter].";

/** #define VOTETYPE  **/

char ABMFmjrty3[] = "; //sprintf( v_result, \"%d\", data[i_Voter]./** #define VOTETYPE  **/ );	//int? float? char?\n\t\t\tnum_Voter=1;\n\t\t}\n\t\telse{  //still be the majority voter\n\t\t\tif(data[i_Voter].";

/** #define VOTETYPE  **/

char ABMFmjrty4[] = " != v_result) num_Voter--;\n\t\t\telse num_Voter++;\n\t\t}\n\t}\n\t//confirm that the v_result is a really majority voter\n\tnum_Voter = Total_Num_Voter;\n\tfor(i_Voter=0; i_Voter < Total_Num_Voter; i_Voter++) if(data[i_Voter].";

/** #define VOTETYPE  **/

char ABMFmjrty5[] = "!=v_result) num_Voter--;\n\n\t//if v_result is the majority voter, correct the answer to v_result\n\tif(num_Voter>=(Total_Num_Voter+1)/2) {\n\t\tprintf(\"\\33\\[1;33m \\n\\tCorrect the answer to :\\n\\t%f \\33\\[0m \\n\\n\", v_result);\n\n";

		/** voteName **/

char ABMFmjrty6[] = " = v_result; //return ;  //successful\n\n";


//if(Num_Voter==2){
	//for(int dep_i=0; dep_i< /*depVar.size()*/; dep_i++){
//		close(pipe_fd_Voter[1]);
//		read(pipe_fd_Voter[0], &/*depVar[dep_i]*/, sizeof(/** depType  **/));
	//}
//}


char ABMFmjrty7[] = "\n\tprintf(\"FINISH\\n\");\n\tfinish=1;\n\trespawn=0;\n\t}\n\telse {\n\t\tprintf(\"\\33\\[1;31m \\n--There doesn't have a majority voter...-- \\33\\[0m \\n\");\n//	Num_Voter=0; //Doesn't have a majority voter\n\t\tprocess_num=Total_Num_Voter;\n\t\tround_num=-1;\n\t\tdep_process=0;\n\t\ttime_delay=0;\n\t\trespawn=0;\n\t}\n}\n//------find the candidate of majority voter------//";


char ABMFforpart4[] = "\n\t\t\t\t\tbreak;\n\t\t\t\t}\n\t\t\t\telse if(w_return > 0 && respawn ==1)\n\t\t\t\t{\n\tkill_count+=1;\n\tprintf(\"\\n\\tkill_count:%d\\n\",kill_count);	\n\tif(kill_count == Total_Num_Voter){\n\t\ttime_delay=0;\n\t\trespawn=0;\n\t\t//kill_count=0;\n\t}\n\t\t\t\t}\n\t\t\t\telse if(w_return < 0)\n\t\t\t\t{\n\t\t\t\t\tfinish=1;\n\t\t\t\t\tprocess_num=Total_Num_Voter;\n\t\t\t\t\tround_num=-1;\n\t\t\t\t\tdep_process=0;\n\t\t\t\t\ttime_delay=0;\n\t\t\t\t\trespawn=0;\n\t\t\t\t\tbreak;\n\t\t\t\t}\n\t\t\t} //for\n\t\t}//if(pid_Voter > 0){\n\t\t}  //pid>0\n\t\telse  // 0 child\n\t\t{\n\t\t\tprintf(\"Child Process:%4d \\n\",getpid());\n\t\t\tif(round_num!=0){\n\t\t\t\tclose(pipe_fd_Voter2[0]);\n\n";


/** work **/


char ABMFforpart5[] = "\n\t\t\t\tstruct Data *data_chd = (struct Data *)malloc(sizeof(struct Data));\n\t\t\t\tdata_chd->";

/** #define VOTETYPE  **/

//	" = ";

/** voteName **/;

//	"\n\t\t\t\twrite(pipe_fd_Voter2[1], &";

/** voteName  **/

//	", sizeof(";

/** VoteType  **/

//	"));";



//if(dep_process!=0){
	//for(int dep_i=0; dep_i< /*depVar.size()*/; dep_i++){
//		close(pipe_fd_Voter[0]);
//		write(pipe_fd_Voter[1], &/*depVar[dep_i]*/, sizeof(/** depType  **/));
	//}
//}



char ABMFPend[] = "\n\t\t\t} //if(round_num!=0){\n\t\t\tfinish=1;\n\t\t\texit(EXIT_SUCCESS);\n\t\t}\n\t}";



#endif
