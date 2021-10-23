#ifndef RPMODEL_H_
#define RPMODEL_H_

#define RPPIPE_ RPpipe
#define RPINITIAL_ RPinitial
#define RPWHILEPART1_ RPwhilepart1
#define RPWHILEPART2_ RPwhilepart2




char RPpipe[] = "\n\tint pipe_fd_Voter[2];\n\tif (pipe(pipe_fd_Voter) == -1){\n\t\tfprintf(stderr, \"Error: Unable to create pipe.\\n\");\n\t\texit(EXIT_FAILURE);\n\t}\n\n";

char RPinitial[] = "\tchar k[50]=\"kill -9 \";\n\tchar chpid[12];\n\t pid_t pid;\n\tpid = fork();\n";


char RPwhilepart1[] = "\n\twhile(1){\n\t\tint chdpid;\n\t\tif(pid<0)\t\t{\n\t\t\tfprintf(stderr, \"Fork Failed\\n\");\n\t\t\treturn 1;\n\t\t}\n\t\tif(pid>0)  //parent\n\t\t{\n\t\t\tprintf(\"\\nParent Process:%4d\\n\",getpid());\n\t\t\tint time_delay=0;\n\t\t\tclose(pipe_fd_Voter[1]);\n\t\t\tread(pipe_fd_Voter[0],  &chdpid, sizeof(int));\n\t\t\tprintf(\"---Receive Child PID:%4d\\n\",chdpid);\n\t\t\tmemset( k, \'\\0\', strlen(k));\n\t\t\tmemset( chpid, \'\\0\', strlen(chpid));\n\t\t\tstrcpy(k, \"kill -9 \");\n\t\t\tsprintf(chpid, \"%d\", chdpid);\n\t\t\tstrcat(k, chpid);\n\t\t\t//printf(\"\\t\\t\\t\\tCMD:%s\\n\",k);\n\t\t\tfor(;;){\n\t\t\t\tsleep(1);\n\t\t\t\t	time_delay++;\n\t\t\t\tprintf(\"time_count = %d\\n\",time_delay);\n\t\t\t\tint status;\n\t\t\t\t    int w_return = waitpid(chdpid, &status, WNOHANG|WUNTRACED); //(-1, NULL, WNOHANG|WUNTRACED);\n\t\t\t\tif(w_return > 0 ){  //  > child finish\n\t\t\t\t\ttime_delay=0;\n\t\t\t\t\tsystem(k);//system(\"pgrep -f monitor_fork | xargs kill -9\");\n\t\t\t\t\tif (pipe(pipe_fd_Voter) == -1){\n\t\t\t\t\t\tfprintf(stderr, \"Error: Unable to create pipe.\\n\");\n\t\t\t\t\t\texit(EXIT_FAILURE);\n\t\t\t\t\t}\n\t\t\t\t\tpid = fork();\n\t\t\t\t\tbreak;\n\t\t\t\t}\n\t\t\t} //for\n\t\t}  //pid>0\n\t\telse  // 0 child\n\t\t{\n\t\t\tclose(pipe_fd_Voter[0]);\n\t\t\tchdpid=getpid();\n\t\t\twrite(pipe_fd_Voter[1], &chdpid, sizeof(int));\n\t\t\tprintf(\"Child Process:%d\\n\",getpid());\n\n";

		/**work**/

char RPwhilepart2[] = "\n\t\t\texit(EXIT_SUCCESS);\n\t\t }\n\t} \n";  


#endif
