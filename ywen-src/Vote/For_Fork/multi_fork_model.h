#ifndef MFMODEL_H_
#define MFMODEL_H_
#define MFINCLUEDE_ MFiclud
#define MFDEFINE_ MFdfn
#define MFDEFINE2_ MFdfn2
#define MFSTRUCT_ MFstruc
#define MFPIPE_ MFfrpipe
#define MFERR_ MFfrkerr
#define MFCHD_ MFchd

#define MFCHDSEND1_ MFchdsnd1
#define MFCHDSEND2_ MFchdsnd2
#define MFCHDSEND3_ MFchdsnd3
#define MFCHDSEND4_ MFchdsnd4
#define MFCHDSEND5_ MFchdsnd5

#define MFCHDEXIT_ MFchdexit

#define MFDEPWRITE_ MFdepwrite
#define MFDEPWRITE2_ MFdepwrite2
#define MFDEPWRITE3_ MFdepwrite3
#define MFDEPWRITE4_ MFdepwrite4
#define MFDEPWRITE5_ MFdepwrite5

#define MFDERPREAD_ MFdepread
#define MFDERPREAD2_ MFdepread2
#define MFDERPREAD3_ MFdepread3
#define MFDERPREAD4_ MFdepread4
#define MFDERPREAD5_ MFdepread5

#define MFPARENTFORK_ MFparntfork

#define MFPARENTRECEIVE_ MFparntrcv
#define MFPARENTRECEIVE2_ MFparntrcv2
#define MFPARENTRECEIVE3_ MFparntrcv3

#define MFVOTE_MAJORITY_ MFvotmjrt
#define MFVOTE_MAJORITY2_ MFvotmjrt2
#define MFVOTE_MAJORITY3_ MFvotmjrt3
#define MFVOTE_MAJORITY4_ MFvotmjrt4
#define MFVOTE_MAJORITY5_ MFvotmjrt5

#define MFVOTE_RESULT_ MFvotresult
#define MFVOTE_RESULT2_ MFvotresult2
#define MFVOTE_RESULT3_ MFvotresult3
#define MFVOTE_RESULT4_ MFvotresult4

#define MFMAINCALLVOTE_ MFmainvot


char MFiclud[] = "#include <stdio.h>\n#include <stdlib.h>\n#include <string.h>\n#include <unistd.h>\n#include <sys/wait.h>\n\n//#include <omp.h>\n\n";

char MFdfn[] = "#define VOTETYPE1 int\n#define VOTETYPE2 float\n#define VOTETYPE3 short\n#define VOTETYPE4 double\n#define VOTETYPE5 long\n#define VOTETYPE6 char\n";

char MFdfn2[] = "\n#define Total_Num_Voter 3\n\n";

char MFstruc[] = "struct Data{\n\tVOTETYPE1 i;\n\tVOTETYPE2 f;\n\tVOTETYPE3 s;\n\tVOTETYPE4 d;\n\tVOTETYPE5 l;\n\tVOTETYPE6 c;\n};\nstruct Data data[Total_Num_Voter];\n\n";

char MFfrpipe[] = "\n//void Calculation_and_Vote(){\n\tint pipe_fd_Voter[2];\n\n\tint process_num=0;\n\tint wait_chd;\n\tint FINISH=0;\n\tint round_num=0;\n\tint dep_process=0;\n\n\tif (pipe(pipe_fd_Voter) == -1){\n\t\t\tfprintf(stderr, \"Error: Unable to create pipe.\\n\");\n\t\texit(EXIT_FAILURE);\n\t}\n\n";

char MFfrkerr[] = "\tpid_t pid_Voter;\n\tif ((pid_Voter = fork()) < 0){\n\t\tfprintf(stderr, \"Error: Unable to fork process.\\n\");\n\t\texit(EXIT_FAILURE);\n\t}\n";


char MFchd[] = "\n\twhile(FINISH==0){\n\tfor(round_num=0; round_num<2, FINISH==0; round_num++){\n\t if(pid_Voter == 0) /*-- Child --*/\n\t{\n\t\tclose(pipe_fd_Voter[0]);\n\n\t\tif(round_num!=0){\n\n";

char MFchdsnd1[] = "\t\tint p=1; printf(\"p:%d\\n\",p);\n\t\tstruct Data *data_chd = (struct Data *)malloc(sizeof(struct Data)); //= malloc(sizeof(*Data));\n\t\tdata_chd->";///** vType  **/

char MFchdsnd2[] = " = ";/** voteName **/;

char MFchdsnd3[] = ";\n\t\twrite(pipe_fd_Voter[1], &data_chd->";///** vType  **/

char MFchdsnd4[] = ", sizeof(";//VOTETYPE

char MFchdsnd5[] = "));\n";


char MFdepwrite[] = "\t\tif(dep_process!=0){\n\t\t\tsleep(1);\n\n";

char MFdepwrite2[] = "\n\t\t\tclose(pipe_fd_Voter[0]);\n\t\t\twrite(pipe_fd_Voter[1], &";///*depVar[dep_i]*/
char MFdepwrite3[] = ", sizeof(";///** depType  **/
char MFdepwrite4[] = "));";

char MFdepwrite5[] = "\n\t\t}\n";


char MFchdexit[] = "\n\t\t}//if(round_num==0)sleep(1);\n\t\texit(EXIT_SUCCESS);\n\t}\n\n";


char MFparntfork[] = "\telse /*-- Parent --*/\n\t{\n\t\tif(round_num==0){\n\t\t\tfor(int num=0; num<Total_Num_Voter; num++){\n\t\t\t\tif(pid_Voter > 0){\n\t\t\t\t\tpid_Voter = fork();\n\t\t\t\t\tif(num==(Total_Num_Voter-1) && pid_Voter == 0) dep_process=1;\n\t\t\t\t}\n\t\t\t}\n\t\t}";


char MFparntrcv[] = "\n\n\tif(pid_Voter > 0){\n\twhile(1){\n\n\t\tclose(pipe_fd_Voter[1]);\n\t\t//struct Data *data_Voter = (struct Data *)malloc(sizeof(struct Data)); //= malloc(sizeof(*Data));\n\t\tread(pipe_fd_Voter[0], &data[process_num].";///** vType  **/

char MFparntrcv2[] = ", sizeof(";//VOTETYPE 

char MFparntrcv3[] = "));\n\tif( (wait_chd= waitpid(-1, NULL, WNOHANG)) >0 ){\n\t\tprocess_num++;\n\t\t\tif(process_num==Total_Num_Voter){\n\n";


char MFdepread[] = "\t\t//if(Num_Voter==2){";

char MFdepread2[] = "\n\t\t\tclose(pipe_fd_Voter[1]);\n\t\t\tread(pipe_fd_Voter[0],  &";///*depVar[dep_i]*/
char MFdepread3[] = ", sizeof(";///** depType  **/
char MFdepread4[] = "));";

char MFdepread5[] ="\n\t\t//}\n";


char MFvotmjrt[] = "\n//------find the candidate of majority voter------//\n//Num_Voter=2;//if(Num_Voter==2){\n\tint num_Voter=0;\n\t";//VOTETYPE 
char MFvotmjrt2[] = " v_result;\n\t//char v_result[1024];\n\tint i_Voter;\n\tfor( i_Voter=0; i_Voter<Total_Num_Voter; i_Voter++){\n\t\tif(num_Voter==0) {\n\t\t\tv_result = data[i_Voter].";///** vType  **/
char MFvotmjrt3[] = "; //sprintf( v_result, \"%d\", data[i_Voter].";///** vType  **/

char MFvotmjrt4[] = " );	//int? float? char?\n\t\t\tnum_Voter=1;\n\t\t}\n\t\telse{  //still be the majority voter\n\t\tif(data[i_Voter].";///** vType  **/

char MFvotmjrt5[] = "!=v_result) num_Voter--;\n\t\t\telse num_Voter++;\n\t\t}\n\t}\n";

char MFvotresult[] = "\t//confirm that the v_result is a really majority voter\n\tnum_Voter = Total_Num_Voter;\n\tfor(i_Voter=0; i_Voter < Total_Num_Voter; i_Voter++) if(data[i_Voter].";///** vType  **/

char MFvotresult2[] = "!=v_result) num_Voter--;\n\t//if v_result is the majority voter, correct the answer to v_result\n\tif(num_Voter>=(Total_Num_Voter+1)/2) {\n\t\tprintf(\"\\33\\[1;33m \\n\\tCorrect the answer to :\\n\\t%f \\33\\[0m \\n\\n\", v_result);\n\t\tFINISH=1;\n"; /** voteName **/

char MFvotresult3[] = " = v_result;//return ;  //successful\n\n";

char MFvotresult4[] = "\n\t}\n \telse {\n\t\tprintf(\"\\33\\[1;31m \\n--There doesn't have a majority voter...-- \\33\\[0m \\n\");\n\t\tround_num=0; //Doesn't have a majority voter\n\t}\n//}\n//------find the candidate of majority voter------//\n\n\t\tbreak;\n\n\t}\n}\n\n}}}}}";



char MFmainvot[] = "\nint main()\n{\n\tCalculation_and_Vote();\n\tprintf(\"END\\n\");\nreturn 0;\n}\n\n";



#endif
