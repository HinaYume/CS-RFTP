#ifndef RPFORMODEL_H_
#define RPFORMODEL_H_

//#define RPFORINITIAL_ RPFORinitial
#define RPFORWHILE1_ RPFORwhile1
#define RPFORWHILE2_ RPFORwhile2
#define RPFORWHILE3_ RPFORwhile3
#define RPFORWHILE4_ RPFORwhile4
#define RPFORWHILE5_ RPFORwhile5
#define RPFORWHILE6_ RPFORwhile6

#define RPFORMJRTY1_ RPFORmjrty1
#define RPFORMJRTY2_ RPFORmjrty2
#define RPFORMJRTY3_ RPFORmjrty3
#define RPFORMJRTY4_ RPFORmjrty4
#define RPFORMJRTY5_ RPFORmjrty5
#define RPFORMJRTY6_ RPFORmjrty6

#define RPFORCHD_ RPFORchd
#define RPFOREND_ RPFORend



char RPFORwhile1[] = "\n\tpid_t pid;\n\tint pipe_fd_Voter[2];\n\tchar k[3][50];\n\tchar chpid[12];\n\tint chdpid_i[3];\n\tint finish=0;\n\twhile(1){\n\n\tfinish=0;\n\n\tfor(int Num_Voter=0; Num_Voter<Total_Num_Voter, finish!=1; Num_Voter++){\n\t\tint chdpid;\n\t\tif (pipe(pipe_fd_Voter) == -1){\n\t\t\tfprintf(stderr, \"Error: Unable to create pipe.\\n\");\n\t\t\texit(EXIT_FAILURE);\n\t\t}\n\t\tif ((pid = fork()) < 0){\n\t\t\tfprintf(stderr, \"Error: Unable to fork process.\\n\");\n\t\t\texit(EXIT_FAILURE);\n\t\t}\n\t\tif(pid>0)  //parent\n\t\t{\n\t\t\tprintf(\"Parent Process:%4d\\n\",getpid());\n\t\t\tclose(pipe_fd_Voter[1]);\n\t\t\tread(pipe_fd_Voter[0],  &chdpid_i[Num_Voter], sizeof(int));\n\t\t\tprintf(\"---Child Process:%4d\\n\",chdpid_i[Num_Voter]);\n\t\t\tmemset( k[Num_Voter], \'\\0\', strlen(k[Num_Voter]));\n\t\t\tmemset( chpid, \'\\0\', strlen(chpid));\n\t\t\tstrcpy(k[Num_Voter], \"kill -9 \");\n\t\t\tsprintf(chpid, \"%d\", chdpid_i[Num_Voter]);\n\t\t\tstrcat(k[Num_Voter], chpid);\n\n\t\t\tfor(;finish!=1;){//sleep(1)){\n\t\t\tsleep(1);\n\n\t\t\tint status;\n\t\t\tint w_return = waitpid(-1, &status, WNOHANG|WUNTRACED); //(chdpid, NULL, WNOHANG|WUNTRACED);\n\n\t\t\tif(w_return > 0 )//&& respawn !=1)// && (time_delay!=0 && time_delay!=CHECK_TIME))\n\t\t\t{\n\n\t\t\t\tif(WIFEXITED(status)){\n\n\t\tclose(pipe_fd_Voter[1]);\n\t\t//struct Data *data_Voter = (struct Data *)malloc(sizeof(struct Data));\n\t\t//= malloc(sizeof(*Data));\n\t\tread(pipe_fd_Voter[0], &data[Num_Voter].";

/** #define VOTETYPE  **/

//	", sizeof(";

/** VoteType  **/

char RPFORwhile2[] = "));\n\t\tprintf(\"\\n\\trecv:%f, Num_Voter:%d\\n\\n\",data[Num_Voter].";

/** #define VOTETYPE  **/

char RPFORwhile3[] = ", Num_Voter);\n";

		

char RPFORmjrty1[] = "\n//------find the candidate of majority voter------//\nif(Num_Voter==2){\n\tint num_Voter=0;";

/** VoteType  **/

char RPFORmjrty2[] = " v_result;\n\n\tint i_Voter;\n\tfor( i_Voter=0; i_Voter<Total_Num_Voter; i_Voter++){\n\t\tif(num_Voter==0) {\n\t\t\tv_result = data[i_Voter].";

/** #define VOTETYPE  **/

char RPFORmjrty3[] = ";\n\t\t\tnum_Voter=1;\n\t\t}\n\t\telse{  //still be the majority voter\n\t\t\tif(data[i_Voter].";

/** #define VOTETYPE  **/

char RPFORmjrty4[] = " != v_result) num_Voter--;\n\t\t\telse num_Voter++;\n\t\t}\n\t}\n\t//confirm that the v_result is a really majority voter\n\tnum_Voter = Num_Voter;\n\tfor(i_Voter=0; i_Voter < Total_Num_Voter; i_Voter++) if(data[i_Voter].";

/** #define VOTETYPE  **/

char RPFORmjrty5[] = " != v_result) num_Voter--;\n\t//if v_result is the majority voter, correct the answer to v_result\n\tif(num_Voter>=(Num_Voter+1)/2) {\n\t\tprintf(\"\\33\\[1;33m \\n\\tCorrect the answer to :\\n\\t%f \\33\\[0m \\n\\n\", v_result);";


//if(Num_Voter==2){
	//for(int dep_i=0; dep_i< /*depVar.size()*/; dep_i++){
//		close(pipe_fd_Voter[1]);
//		read(pipe_fd_Voter[0], &/*depVar[dep_i]*/, sizeof(/** depType  **/));
	//}
//}


char RPFORmjrty6[] = "\n\t\tprintf(\"FINISH\\n\");\n\t\tfinish=1;\n\t}\n\telse {\n\t\tprintf(\"\\33\\[1;31m \\n--There doesn't have a majority voter...-- \\33\\[0m \\n\");\n\t\tNum_Voter=0; //Doesn't have a majority voter\n\t}\n}\n//------find the candidate of majority voter------//";


char RPFORwhile4[] = "\n\t\tbreak;\n\n\t\t\t\t} //if(WIFEXITED(status))\n\t\t\t\telse// if (Num_Voter!=Total_Num_Voter)\n\t\t\t\t{\n\t\t\t\t\tfor(int num=0; num<Num_Voter; num++){\n\t\t\t\t\t\tsystem(k[num]);\n\t\t\t\t\t\tprintf(\"\\t\\t\\t\\tEnd:%s\\n\",k[num]);\n\t\t\t\t\t}\n\t\t\t\t\tfinish=1;\n\t\t\t\t\tbreak;\n\t\t\t\t}\n\t\t\t} //if(w_return > 0 )\n\t\t\telse if((WIFSIGNALED(status)) || (WIFSIGNALED(status)))\n\t\t\t{\n\t\t\t\tfor(int num=0; num<Num_Voter; num++){\n\t\t\t\t\tsystem(k[num]);\n\t\t\t\t\tprintf(\"\\t\\t\\t\\tEnd:%s\\n\",k[num]);\n\t\t\t\t}\n\t\t\t\tfinish=1;\n\t\t\t\tbreak;\n\t\t\t}\n\t\t\telse if(w_return < 0)\n\t\t\t{\n\t\t\t\tfor(int num=0; num<Num_Voter; num++){\n\t\t\t\t\tsystem(k[num]);\n\t\t\t\t\tprintf(\"\\t\\t\\t\\tEnd:%s\\n\",k[num]);\n\t\t\t\t}\n\t\t\t\tfinish=1;\n\t\t\t\tbreak;\n\t\t\t}  \n\t\t\t} //for\n\t\t}  //pid>0";

char RPFORwhile5[] = "\n\t\telse  // 0 child\n\t\t{\n\t\t\tclose(pipe_fd_Voter[0]);\n\t\t\tchdpid=getpid();\n\t\t\twrite(pipe_fd_Voter[1], &chdpid, sizeof(int));\n\t\t\tprintf(\"Child Process:%4d \\t%d\\n\",getpid() ,chdpid);\n\n";


/** work **/


char RPFORwhile6[] = "\n\t\t\tstruct Data *data_chd = (struct Data *)malloc(sizeof(struct Data)); //= malloc(sizeof(*Data));\n\t\t\tdata_chd->";

/** #define VOTETYPE  **/

//	" = ";

/** voteName **/

//	";\n\t\t\twrite(pipe_fd_Voter[1], &";

/** #define VOTETYPE  **/

//	", sizeof(";

/** VoteType  **/

//	"));\n";



//if(Num_Voter==2){
	//for(int dep_i=0; dep_i< /*depVar.size()*/; dep_i++){
//		close(pipe_fd_Voter[0]);
//		write(pipe_fd_Voter[1], &/*depVar[dep_i]*/, sizeof(/** depType  **/));
	//}
//}


char RPFORend[] = "\n\t\t\tfinish=1;\n\t\t\texit(EXIT_SUCCESS);\n\t\t}\n\n\t}\n\n\t} //while(1)";


#endif
