#ifndef RPMFMODEL_H_
#define RPMFMODEL_H_

#define RPMFINITIAL_ RPMFinitial
#define RPMFWHILE1_ RPMFwhile1
#define RPMFWHILE2_ RPMFwhile2
#define RPMFMJRTY1_ RPMFmjrty1
#define RPMFMJRTY2_ RPMFmjrty2
#define RPMFMJRTY3_ RPMFmjrty3
#define RPMFMJRTY4_ RPMFmjrty4
#define RPMFMJRTY5_ RPMFmjrty5
#define RPMFMJRTY6_ RPMFmjrty6
#define RPMFMJRTY7_ RPMFmjrty7
#define RPMFCHD_ RPMFchd
#define RPMFCHD2_ RPMFchd2
#define RPMFEND_ RPMFend




//#include <signal.h>


char RPMFinitial[] = "\n\tpid_t pid;\n\tint pipe_fd_Voter[2];\n\tint pipe_fd_Voter2[2];\n\tchar k[3][50];\n\tchar chpid[3][12];\n\tint finish=0;\n\tint process_num=Total_Num_Voter+1;\n\tint round_num=0;\n\tint dep_process=0;\n\tint kill_count=0;\n\tint chdpid;\n\tint chdpid_i[3];";

char RPMFwhile1[] = "\n\twhile(1){\n\tfinish=0;\n\tprocess_num=Total_Num_Voter+1;\n\tround_num=0;\n\tdep_process=0;\n\tkill_count=0;\n\tif (pipe(pipe_fd_Voter2) == -1){\n\t\tfprintf(stderr, \"Error: Unable to create pipe.\\n\");\n\t\texit(EXIT_FAILURE);\n\t}\n\tif ((pid = fork()) < 0){\n\t\tfprintf(stderr, \"Error: Unable to fork process.\\n\");\n\t\texit(EXIT_FAILURE);\n\t}\n\tfor(round_num=0; round_num<2, finish==0; round_num++){\n\t\tif(pid>0)  //parent\n\t\t{\n\t\t\tif(round_num==0){\n\t\t\t\tfor(int num=0; num<Total_Num_Voter; num++){\n\t\t\t\t\tif(pid > 0){\n\n\t\tif (pipe(pipe_fd_Voter) == -1){\n\t\t\tfprintf(stderr, \"Error: Unable to create pipe.\\n\");\n\t\t\texit(EXIT_FAILURE);\n\t\t}\n\t\tif ((pid = fork()) < 0){\n\t\t\tfprintf(stderr, \"Error: Unable to fork process.\\n\");\n\t\t\texit(EXIT_FAILURE);\n\t\t}\n\t\tif(num==(Total_Num_Voter-1) && pid == 0) dep_process=1;\n\t\tif(pid==0){\n\t\t\tclose(pipe_fd_Voter[0]);\n\t\t\tchdpid=getpid();\n\t\t\twrite(pipe_fd_Voter[1], &chdpid, sizeof(int));\n\t\t\tprintf(\"\\n\\t***Child Process:%4d\\n\",chdpid);\n\t\t}\n\t\telse if(pid > 0){\n\t\t\tclose(pipe_fd_Voter[1]);\n\t\t\tread(pipe_fd_Voter[0],  &chdpid_i[num], sizeof(int));\n\t\t\tprintf(\"\\n\\t---Child Process:%4d\\n\",chdpid_i[num]);\n\t\t\tmemset( k[num], \'\\0\', strlen(k[num]));\n\t\t\tmemset( chpid[num], \'\\0\', strlen(chpid[num]));\n\t\t\tstrcpy(k[num], \"kill -9 \");\n\t\t\tsprintf(chpid[num], \"%d\", chdpid_i[num]);\n\t\t\tstrcat(k[num], chpid[num]);\n\t\t}\n\n\t\t\t\t\t}\n\t\t\t\t}\n\t\t\t} //if(round_num==0){\n\n\t\t\tif(pid > 0){\n\n\t\tprintf(\"Parent Process:%4d\\n\",getpid());\n\t\tint time_delay=0;\n\t\tfor(;finish!=1;){\n\n\t\tsleep(1);\n\t\tint status;//[3];\n\t\tint w_return;//[3];\n\t\tw_return = waitpid(-1, &status, WNOHANG|WUNTRACED);\n\t\tif(w_return > 0 )\n\t\t{\n\t\t\tif(WIFEXITED(status)){\n\t\t\t\tprocess_num--;\n\t\t\t\tprintf(\"\\n\\t\\t\\t+++ process_num:%d\\n\\n\", process_num);\n\t\t\t\tif(process_num != Total_Num_Voter)\n\t\t\t\t{\n\t\t\t\t\tclose(pipe_fd_Voter2[1]);\n\t\t\t\t\tread(pipe_fd_Voter2[0], &data[process_num].";

/** #define VOTETYPE  **/

//	", sizeof(";

/** VoteType  **/

//	"));\n\t\t\t\t\tprintf(\"\\n\\trecv:%d, process_num:%d\\n\\n\",data[process_num].";

/** #define VOTETYPE  **/

//	", process_num);\n\t\t\t\t}";



char RPMFmjrty1[] = "\n\n//------find the candidate of majority voter------//\nif(process_num==0){ //(Total_Num_Voter-1)){\n\tint num_Voter=0;\n\t";

/** VoteType  **/

char RPMFmjrty2[] = " v_result;\n\tint i_Voter;\n\tfor( i_Voter=0; i_Voter<Total_Num_Voter; i_Voter++){\n\t\tif(num_Voter==0) {\n\t\t\tv_result = data[i_Voter].";

/** #define VOTETYPE  **/

char RPMFmjrty3[] = ";\n\t\tnum_Voter=1;\n\t}\n\telse{  //still be the majority voter\n\t\tif(data[i_Voter].";

/** #define VOTETYPE  **/

char RPMFmjrty4[] = " != v_result) num_Voter--;\n\t\telse num_Voter++;\n\t}\n}\n\n\t\t//confirm that the v_result is a really majority voter\n\t\tnum_Voter = Total_Num_Voter;\n\t\tfor(i_Voter=0; i_Voter < Total_Num_Voter; i_Voter++) if(data[i_Voter].";

/** #define VOTETYPE  **/

char RPMFmjrty5[] = " != v_result) num_Voter--;\n\t\t//if v_result is the majority voter, correct the answer to v_result\n\t\tif(num_Voter>=(Total_Num_Voter+1)/2) {\n\t\t\tprintf(\"\\33\\[1;33m \\n\\tCorrect the answer to :\\n\\t%f \\33\\[0m \\n\\n\", v_result);";
		
/** voteName **/

char RPMFmjrty6[] = " = v_result; //return ;  //successful";


//if(Num_Voter==2){
	//for(int dep_i=0; dep_i< /*depVar.size()*/; dep_i++){
//		close(pipe_fd_Voter[1]);
//		read(pipe_fd_Voter[0], &/*depVar[dep_i]*/, sizeof(/** depType  **/));
	//}
//}


char RPMFmjrty7[] = "\n\t\t\tprintf(\"FINISH\\n\\n\");\n\t\t\tfinish=1;\n\t\t}\n\t\telse {\n\t\t\tprintf(\"\\33\\[1;31m \\n--There doesn't have a majority voter...-- \\33\\[0m \\n\");\n\t\t\t//Doesn't have a majority voter\n\t\t\tfinish=1;\n\t\t\tdep_process=0;\n\t\t}\n\t}\n//------find the candidate of majority voter------//";


char RPMFwhile2[] = "\n\t\t\t\tbreak;\n\t\t\t} //if(WEXITSTATUS(status))\n\t\t\telse if (process_num!=Total_Num_Voter+1 )\n\t\t\t{	\n\t\t\t\tfor(int num=0; num<Total_Num_Voter; num++){\n\t\t\t\t\tsystem(k[num]);\n\t\t\t\t\tprintf(\"\\t\\t\\t\\tEnd:%s\\n\",k[num]);\n\t\t\t\t}\n\t\t\t\tfinish=1;\n\t\t\t\tbreak;\n\t\t\t}\n\t\t} //else if(w_return > 0 )//\n\t\telse if(w_return < 0)\n\t\t{\n\t\t\tfor(int num=0; num<Total_Num_Voter; num++){\n\t\t\t\tsystem(k[num]);\n\t\t\t\tprintf(\"\\t\\t\\t\\tEnd:%s\\n\",k[num]);\n\t\t\t}\n\t\t\tfinish=1;\n\t\t\tprocess_num=Total_Num_Voter;\n\t\t\tround_num=-1;\n\t\t\tdep_process=0;\n\t\t\tbreak;\n\t\t}\n\t} //for\n}//if(pid_Voter > 0){\n}  //pid>0";


char RPMFchd[] = "\n\n\telse  // 0 child\n\t{\n\t\tprintf(\"Child Process:%4d \\n\",getpid());\n\t\tif(round_num!=0){\n\t\t\tclose(pipe_fd_Voter2[0]);";

/** work **/

char RPMFchd2[] = "\n\t\t\tstruct Data *data_chd = (struct Data *)malloc(sizeof(struct Data));\n\t\t\tdata_chd->";

/** #define VOTETYPE  **/

//	" = ";

/** voteName **/

//	";\n\t\t\twrite(pipe_fd_Voter2[1], &";

/** #define VOTETYPE  **/

//	", sizeof(";

/** VoteType  **/

//	"));";


//if(dep_process!=0){
	//for(int dep_i=0; dep_i< /*depVar.size()*/; dep_i++){
//		close(pipe_fd_Voter[0]);
//		write(pipe_fd_Voter[1], &/*depVar[dep_i]*/, sizeof(/** depType  **/));
	//}
//}



char RPMFend[] = "\n\t\t} //if(round_num!=0){\n\t\t\tfinish=1;\n\t\t\treturn 0; //_exit(2); //exit(3); //return 0;//exit(EXIT_SUCCESS);\n\t\t}\n\t}\n} //while(1){//FINISH==0){";



#endif

