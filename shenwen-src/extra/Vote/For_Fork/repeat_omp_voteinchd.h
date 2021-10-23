#ifndef RPOMPMODEL_H_
#define RPOMPMODEL_H_

#define RPOMPINITIAL_ RPOMPinitial
#define RPOMPWHILE1_ RPOMPwhile1
#define RPOMPWHILE1PART2_ RPOMPwhile1part2
#define RPOMPWHILE2_ RPOMPwhile2
#define RPOMPWHILE3_ RPOMPwhile3
#define RPOMPMJRTY1_ RPOMPmjrty1
#define RPOMPMJRTY2_ RPOMPmjrty2
#define RPOMPMJRTY3_ RPOMPmjrty3
#define RPOMPMJRTY4_ RPOMPmjrty4
#define RPOMPMJRTY5_ RPOMPmjrty5
#define RPOMPMJRTY6_ RPOMPmjrty6
#define RPOMPEND_ RPOMPend



char RPOMPinitial[] = "\n\tpid_t pid;\n\tint pipe_fd_Voter[2];\n\tchar k[50]=\"kill -9 \";\n\tchar chpid[12];\n\tint finish=0;\n\tint Num_Voter=0;\n\tint result;\n\twhile(1){\n\tfinish=0;\n\twhile(finish!=1){ //for(int Num_Voter=0; Num_Voter<Total_Num_Voter, finish!=1; Num_Voter++){//\n\tint chdpid;\n\tif (pipe(pipe_fd_Voter) == -1){\n\t\tfprintf(stderr, \"Error: Unable to create pipe.\\n\");\n\t\texit(EXIT_FAILURE);\n\t}\n\tif ((pid = fork()) < 0){\n\t\tfprintf(stderr, \"Error: Unable to fork process.\\n\");\n\t\texit(EXIT_FAILURE);\n\t}\n\tif(pid>0)  //parent\n\t{\n\t\tprintf(\"Parent Process:%4d\\n\",getpid());\n\tclose(pipe_fd_Voter[1]);\n\tread(pipe_fd_Voter[0],  &chdpid, sizeof(int));\n\tprintf(\"---Child Process:%4d\\n\",chdpid);\n\tmemset( k, \'\\0\', strlen(k));\n\tmemset( chpid, \'\\0\', strlen(chpid));\n\tstrcpy(k, \"kill -9 \");\n\tsprintf(chpid, \"%d\", chdpid);\n\tstrcat(k, chpid);\n\tfor(;finish!=1;){//sleep(1)){\n\t\tsleep(1);\n\t\tint status;\n\t\tint w_return = waitpid(chdpid, &status, WNOHANG|WUNTRACED); //(-1, NULL, WNOHANG|WUNTRACED);\n\t\tif(w_return > 0 )//&& respawn !=1)// && (time_delay!=0 && time_delay!=CHECK_TIME))\n\t\t{\n\t\t\tif(WIFEXITED(status)){\n\t\t\t\tclose(pipe_fd_Voter[1]);\n\t\t\t\tstruct Data *data_Voter = (struct Data *)malloc(sizeof(struct Data));\n\t\t\t\tread(pipe_fd_Voter[0], &data_Voter->";

/** #define VOTETYPE  **/

//	 ", sizeof(";

/** VoteType  **/

//	 "));\n";		
		
//	"\t\t\t\tresult = data_Voter->";

/** #define VOTETYPE  **/

char RPOMPwhile1[] = ";\n\t\t\t\tprintf(\"\\n\\trecv:%d\\n\\n\",result);";

//if(Num_Voter==2){
	//for(int dep_i=0; dep_i< /*depVar.size()*/; dep_i++){
//		close(pipe_fd_Voter[1]);
//		read(pipe_fd_Voter[0], &/*depVar[dep_i]*/, sizeof(/** depType  **/));
	//}
//}

char RPOMPwhile1part2[] = "\n\t\t\t\tbreak;\n\t\t\t} //if(WIFEXITED(status))\n\t\t\telse //if((WIFSIGNALED(status)) || (WIFSIGNALED(status)))\n\t\t\t{\n\t\t\t\tfinish=1;\n\t\t\t\tbreak;\n\t\t\t}\n\t\t} //if(w_return > 0 )\n\t\telse if((WIFSIGNALED(status)) || (WIFSIGNALED(status)))\n\t\t{\n\t\t\tsystem(k);\n\t\t\tprintf(\"\\n\\t\\t\\t\\tEnd:%s\\n\",k);\n\t\t\tfinish=1;\n\t\t\tbreak;\n\t\t}\n\t\telse if(w_return < 0)\n\t\t{\n\t\t\tsystem(k);\n\t\t\tprintf(\"\\n\\t\\t\\t\\tEnd:%s\\n\",k);\n\t\t\tfinish=1;\n\t\t\tbreak;\n\t\t}\n\t} //for\n\t}  //pid>0";

char RPOMPwhile2[] = "\n\telse  // 0 child\n\t{\n\t\tclose(pipe_fd_Voter[0]);\n\t\tchdpid=getpid();\n\t\twrite(pipe_fd_Voter[1], &chdpid, sizeof(int));\n\t\tprintf(\"Child Process:%4d \\t%d\\n\",getpid() ,chdpid);\n\t\t#pragma omp parallel for num_threads(4) \n\t\tfor(Num_Voter=0; Num_Voter<Total_Num_Voter; Num_Voter++){\n\n";


/** work **/


char RPOMPwhile3[] = "\n\t\t\tstruct Data *data_chd = (struct Data *)malloc(sizeof(struct Data)); //= malloc(sizeof(*Data));\n\t\t\tdata[Num_Voter].";

 /** #define VOTETYPE  **/

//	 " = "

/** voteName **/


char RPOMPmjrty1[] = ";\n\t\t\t\n\t\t}\n//------find the candidate of majority voter------//\nNum_Voter=2;//if(Num_Voter==2){\n\tint num_Voter=0;\n\t";

	/** VoteType  **/ 

char RPOMPmjrty2[] = " v_result;\n\tint i_Voter;\n\tfor( i_Voter=0; i_Voter<Total_Num_Voter; i_Voter++){\n\t\tif(num_Voter==0) {\n\t\t\tv_result = data[i_Voter].";

			 /** #define VOTETYPE  **/

char RPOMPmjrty3[] = "; \n\t\t\tnum_Voter=1;\n\t\t}\n\t\telse{  //still be the majority voter\n\t\t\tif(data[i_Voter].";
			
			/** #define VOTETYPE  **/

char RPOMPmjrty4[] = " != v_result) num_Voter--;\n\t\t\telse num_Voter++;\n\t\t}\n\t}\n\t//confirm that the v_result is a really majority voter\n\tnum_Voter = Num_Voter;\n\tfor(i_Voter=0; i_Voter < Total_Num_Voter; i_Voter++) if(data[i_Voter].";
	 
	 /** #define VOTETYPE  **/

char RPOMPmjrty5[] = " != v_result) num_Voter--;\n\t//if v_result is the majority voter, correct the answer to v_result\n\tif(num_Voter>=(Num_Voter+1)/2) {\n\t\tprintf(\"\\33\\[1;33m \\n\\tCorrect the answer to :\\n\\t%f \\33\\[0m \\n\\n\", v_result);\n\t//p = v_result; // /** voteName **/=v_result; //return ;  //successful";





char RPOMPmjrty6[] = "\n\tclose(pipe_fd_Voter[0]);\n\twrite(pipe_fd_Voter[1], &v_result , sizeof(int));\n\tprintf(\"FINISH\\n\");\n\tfinish=1;\n\t}\n\telse {\n\t\tprintf(\"\\33\\[1;31m \\n--There doesn't have a majority voter...-- \\33\\[0m \\n\");\n\t\tNum_Voter=0; //Doesn't have a majority voter\n\t}\n//------find the candidate of majority voter------//";

    

//if(Num_Voter==2){
	//for(int dep_i=0; dep_i< /*depVar.size()*/; dep_i++){
//		close(pipe_fd_Voter[0]);
//		write(pipe_fd_Voter[1], &/*depVar[dep_i]*/, sizeof(/** depType  **/));
	//}
//}


char RPOMPend[] = "\n\t\t\t\tfinish=1;\n\t\t\t\texit(EXIT_SUCCESS);\n\t\t\t}\n\t\t}\n\t} //while(1)";



#endif
