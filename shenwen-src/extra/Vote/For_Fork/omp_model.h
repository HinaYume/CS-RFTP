#ifndef OMPMODEL_H_
#define OMPMODEL_H_
#define OMPINCLUEDE_ OMPiclud
#define OMPDEFINE_ OMPdfn
#define OMPDEFINE2_ OMPdfn2
#define OMPSTRUCT_ OMPstruc
#define OMPPIPE_ OMPfrpipe
#define OMPERR_ OMPfrkerr
#define OMPCHD_ OMPchd

#define OMPCHDSEND1_ OMPchdsnd1
#define OMPCHDSEND2_ OMPchdsnd2
#define OMPCHDSEND3_ OMPchdsnd3
#define OMPCHDSEND4_ OMPchdsnd4
#define OMPCHDSEND5_ OMPchdsnd5

#define OMPCHDEXIT_ OMPchdexit

#define OMPDEPWRITE_ OMPdepwrite
#define OMPDEPWRITE2_ OMPdepwrite2
#define OMPDEPWRITE3_ OMPdepwrite3
#define OMPDEPWRITE4_ OMPdepwrite4
#define OMPDEPWRITE5_ OMPdepwrite5

#define OMPDERPREAD_ OMPdepread
#define OMPDERPREAD2_ OMPdepread2
#define OMPDERPREAD3_ OMPdepread3
#define OMPDERPREAD4_ OMPdepread4
#define OMPDERPREAD5_ OMPdepread5


#define OMPPARENTRECEIVE_ OMPparntrcv
#define OMPPARENTRECEIVE2_ OMPparntrcv2
#define OMPPARENTRECEIVE3_ OMPparntrcv3

#define OMPVOTE_MAJORITY_ OMPvotmjrt
#define OMPVOTE_MAJORITY2_ OMPvotmjrt2
#define OMPVOTE_MAJORITY3_ OMPvotmjrt3
#define OMPVOTE_MAJORITY4_ OMPvotmjrt4
#define OMPVOTE_MAJORITY5_ OMPvotmjrt5

#define OMPVOTE_RESULT_ OMPvotresult
#define OMPVOTE_RESULT2_ OMPvotresult2
#define OMPVOTE_RESULT3_ OMPvotresult3
#define OMPVOTE_RESULT4_ OMPvotresult4

#define OMPMAINCALLVOTE_ OMPmainvot


char OMPiclud[] = "#include <stdio.h>\n#include <stdlib.h>\n#include <string.h>\n#include <unistd.h>\n#include <sys/wait.h>\n\n#include <omp.h>\n\n";

char OMPdfn[] = "#define VOTETYPE1 int\n#define VOTETYPE2 float\n#define VOTETYPE3 short\n#define VOTETYPE4 double\n#define VOTETYPE5 long\n#define VOTETYPE6 char\n";

char OMPdfn2[] = "\n#define Total_Num_Voter 3\n\n";

char OMPstruc[] = "struct Data{\n\tVOTETYPE1 i;\n\tVOTETYPE2 f;\n\tVOTETYPE3 s;\n\tVOTETYPE4 d;\n\tVOTETYPE5 l;\n\tVOTETYPE6 c;\n};\nstruct Data data[Total_Num_Voter];\n\n";

char OMPfrpipe[] = "\n//void Calculation_and_Vote(){\n\tint pipe_fd_Voter[2];\n\nint Num_Voter;\nint FINISH=0;\nwhile(FINISH==0){\n//for(int Num_Voter=0; Num_Voter<Total_Num_Voter; Num_Voter++){\n\tif (pipe(pipe_fd_Voter) == -1){\n\t\t\tfprintf(stderr, \"Error: Unable to create pipe.\\n\");\n\t\texit(EXIT_FAILURE);\n\t}\n\n";

char OMPfrkerr[] = "\tpid_t pid_Voter;\n\tif ((pid_Voter = fork()) < 0){\n\t\tfprintf(stderr, \"Error: Unable to fork process.\\n\");\n\t\texit(EXIT_FAILURE);\n\t}\n";


char OMPchd[] = "\telse if (pid_Voter == 0) /*-- Child --*/\n\t{\n\t\tclose(pipe_fd_Voter[0]);\n\n#pragma omp parallel for num_threads(4)\nfor(Num_Voter=0; Num_Voter<Total_Num_Voter; Num_Voter++){\n";

char OMPchdsnd1[] = "\t\tint p=1; printf(\"p:%d\\n\",p);\n\t\tstruct Data *data_chd = (struct Data *)malloc(sizeof(struct Data)); //= malloc(sizeof(*Data));\n\t\t//data_chd[Num_Voter].";///** vType  **/

char OMPchdsnd2[] = " = ";/** voteName **/

char OMPchdsnd3[] = ";\n\t\twrite(pipe_fd_Voter[1], &";/** voteName **/   //data_chd[Num_Voter].";///** vType  **/

char OMPchdsnd4[] = ", sizeof(";//VOTETYPE

char OMPchdsnd5[] = "));\n}";


char OMPdepwrite[] = "\t\t//if(Num_Voter==2){";

char OMPdepwrite2[] = "\n\t\t\tclose(pipe_fd_Voter[0]);\n\t\t\twrite(pipe_fd_Voter[1], &";///*depVar[dep_i]*/
char OMPdepwrite3[] = ", sizeof(";///** depType  **/
char OMPdepwrite4[] = "));";

char OMPdepwrite5[] = "\n\t\t//}\n";


char OMPchdexit[] = "\n\t\texit(EXIT_SUCCESS);\n\t}\n\n";



char OMPparntrcv[] = "\telse /*-- Parent --*/\n\t{\n\t\tclose(pipe_fd_Voter[1]);\n\t\t//struct Data *data_Voter = (struct Data *)malloc(sizeof(struct Data)); //= malloc(sizeof(*Data));\nfor(Num_Voter=0; Num_Voter<Total_Num_Voter; Num_Voter++){\n\t\tread(pipe_fd_Voter[0], &data[Num_Voter].";///** vType  **/

char OMPparntrcv2[] = ", sizeof(";//VOTETYPE 

char OMPparntrcv3[] = "));\n}\n\n";


char OMPdepread[] = "\t\t//if(Num_Voter==2){";

char OMPdepread2[] = "\n\t\t\tclose(pipe_fd_Voter[1]);\n\t\t\tread(pipe_fd_Voter[0],  &";///*depVar[dep_i]*/
char OMPdepread3[] = ", sizeof(";///** depType  **/
char OMPdepread4[] = "));";

char OMPdepread5[] ="\n\t\t//}\n";


char OMPvotmjrt[] = "//------find the candidate of majority voter------//\nNum_Voter=2;//if(Num_Voter==2){\n\tint num_Voter=0;\n\t";//VOTETYPE 
char OMPvotmjrt2[] = " v_result;\n\t//char v_result[1024];\n\tint i_Voter;\n\tfor( i_Voter=0; i_Voter<Total_Num_Voter; i_Voter++){\n\t\tif(num_Voter==0) {\n\t\t\tv_result = data[i_Voter].";///** vType  **/
char OMPvotmjrt3[] = "; //sprintf( v_result, \"%d\", data[i_Voter].";///** vType  **/

char OMPvotmjrt4[] = " );	//int? float? char?\n\t\t\tnum_Voter=1;\n\t\t}\n\t\telse{  //still be the majority voter\n\t\tif(data[i_Voter].";///** vType  **/

char OMPvotmjrt5[] = "!=v_result) num_Voter--;\n\t\t\telse num_Voter++;\n\t\t}\n\t}\n";

char OMPvotresult[] = "\t//confirm that the v_result is a really majority voter\n\tnum_Voter = Num_Voter;\n\tfor(i_Voter=0; i_Voter < Total_Num_Voter; i_Voter++) if(data[i_Voter].";///** vType  **/

char OMPvotresult2[] = "!=v_result) num_Voter--;\n\t//if v_result is the majority voter, correct the answer to v_result\n\tif(num_Voter>=(Num_Voter+1)/2) {\n\t\tprintf(\"\\33\\[1;33m \\n\\tCorrect the answer to :\\n\\t%f \\33\\[0m \\n\\n\", v_result);\n\t\tFINISH=1;\n"; /** voteName **/

char OMPvotresult3[] = " = v_result;//return ;  //successful\n\n";

char OMPvotresult4[] = "\n\t}\n \telse {\n\t\tprintf(\"\\33\\[1;31m \\n--There doesn't have a majority voter...-- \\33\\[0m \\n\");\n\t\tNum_Voter=0; //Doesn't have a majority voter\n\t}\n//}\n//------find the candidate of majority voter------//\n\n\t}\n}\n\n";



char OMPmainvot[] = "\nint main()\n{\n\tCalculation_and_Vote();\n\tprintf(\"END\\n\");\nreturn 0;\n}\n\n";



#endif
