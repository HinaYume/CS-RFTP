#ifndef ABMODEL_H_
#define ABMODEL_H_
#define ABPIPE_ ABpipe
#define ABINITIAL_ ABinitial
#define ABWHILEPART1_ ABwhilepart1
#define ABWHILEPART2_ ABwhilepart2
#define ABWHILEPART3_ ABwhilepart3
#define ABWHILEPART4_ ABwhilepart4
    
#define ABDERPREAD2_  ABdepread2
#define ABDERPREAD3_  ABdepread3
#define ABDERPREAD4_  ABdepread4

#define ABDEPWRITE2_  ABdepwrite2
#define ABDEPWRITE3_  ABdepwrite3
#define ABDEPWRITE4_  ABdepwrite4


char ABpipe[] = 
"\n\tint pipe_fd_Voter[2];
\n\tif (pipe(pipe_fd_Voter) == -1){
	\n\t\tfprintf(stderr, \"Error: Unable to create pipe.\\n\");
	\n\t\texit(EXIT_FAILURE);
	\n\t}\n\n";

char ABinitial[] = 
"\tchar k[50]=\"kill -9 \";
\n\tchar chpid[12];
\n\tint finish=0;
\n\tint respawn=0;
\n\t pid_t pid;
\n\tpid = fork();\n";

char ABwhilepart1[] = "
\n\twhile(finish!=1){
	\n\t\tint chdpid;
	\n\t\tif(pid<0)
	\n\t\t{
		\n\t\t\tfprintf(stderr, \"Fork Failed\\n\");
		\n\t\t\treturn 1;
		\n\t\t}
		\n\t\tif(pid>0)  //parent
		\n\t\t{
			\n\t\t\tprintf(\"\\nParent Process:%4d\\n\",getpid());
			\n\t\t\tint time_delay=0;
			\n\t\t\tclose(pipe_fd_Voter[1]);
			\n\t\t\tread(pipe_fd_Voter[0],  &chdpid, sizeof(int));
			\n\t\t\tprintf(\"---Receive Child PID:%4d\\n\",chdpid);
			\n\t\t\tmemset( k, \'\\0\', strlen(k));
			\n\t\t\tmemset( chpid, \'\\0\', strlen(chpid));
			\n\t\t\tstrcpy(k, \"kill -9 \");
			\n\t\t\tsprintf(chpid, \"%d\", chdpid);
			\n\t\t\tstrcat(k, chpid);
			\n\t\t\t//printf(\"\\t\\t\\t\\tCMD:%s\\n\",k);
			\n\t\t\tfor(;finish!=1;){
				\n\t\t\t\tsleep(1);
				\n\t\t\t\t	time_delay++;
				\n\t\t\t\tprintf(\"time_count = %d\\n\",time_delay);
				\n\t\t\t\tint status;
				\n\t\t\t\t    int w_return = waitpid(chdpid, &status, WNOHANG|WUNTRACED); //(-1, NULL, WNOHANG|WUNTRACED);
				\n\t\t\t\tif(w_return == 0 ){ //  >0 when child finish
					\n\t\t\t\t\tif(time_delay== ";

		/**CHECK_TIME**/	

char ABwhilepart2[] = "\t)
\n\t\t\t\t\t{
	\n\t\t\t\t\t\tprintf(\"\\ttime_count = %d\\n\",time_delay);
	\n\t\t\t\t\t\ttime_delay=0;
	\n\t\t\t\t\t\tsystem(k);//system(\"pgrep -f monitor_fork | xargs kill -9\");
	\n\t\t\t\t\t\tif (pipe(pipe_fd_Voter) == -1){
		\n\t\t\t\t\t\t\tfprintf(stderr, \"Error: Unable to create pipe.\\n\");
		\n\t\t\t\t\t\t\texit(EXIT_FAILURE);
		\n\t\t\t\t\t\t}\n\t\t\t\t\t\tpid = fork();
		\n\t\t\t\t\t\trespawn=1;
		\n\t\t\t\t\t\tbreak;
		\n\t\t\t\t\t}
		\n\t\t\t\t}
		\n\t\t\telse if(w_return > 0 && respawn !=1)// && (time_delay!=0 && time_delay!=CHECK_TIME))
		\n\t\t\t{\n\n";


char ABdepread2[] = "
\n\t\t\tclose(pipe_fd_Voter[1]);
\n\t\t\tread(pipe_fd_Voter[0],  &";///*depVar[dep_i]*/
char ABdepread3[] = ", sizeof(";///** depType  **/
char ABdepread4[] = "));\n\n";


char ABwhilepart3[] = "
\n\t\t\t\tprintf(\"FINISH\\n\");
\n\t\t\t\tfinish=1;
\n\t\t\t\trespawn=0;
\n\t\t\t\tbreak;
\n\t\t\t}
\n\t\t\telse if(w_return < 0)
\n\t\t\t {
	\n\t\t\t\tfinish=1;
	\n\t\t\t\tbreak;
	\n\t\t\t}
	\n\t\t} //for
	\n\t}  //pid>0
	\n\t\telse  // 0 child
	\n\t\t{
		\n\t\tclose(pipe_fd_Voter[0]);
		\n\t\tchdpid=getpid();
		\n\t\twrite(pipe_fd_Voter[1], &chdpid, sizeof(int));
		\n\t\t\tprintf(\"Child Process:%4d\\n\",getpid());\n";

		/**work**/

char ABdepwrite2[] = "
\n\t\t\tclose(pipe_fd_Voter[0]);
\n\t\t\twrite(pipe_fd_Voter[1], &";///*depVar[dep_i]*/
char ABdepwrite3[] = ", sizeof(";///** depType  **/
char ABdepwrite4[] = "));\n\n";

char ABwhilepart4[] = "
\n\t\t\texit(EXIT_SUCCESS);
\n\t\t }\n\t} \n";



#endif
