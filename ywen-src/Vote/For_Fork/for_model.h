#ifndef FORMODEL_H_
#define FORMODEL_H_
#define INCLUEDE_ iclud
#define DEFINE_ dfn
#define DEFINE2_ dfn2
#define STRUCT_ struc
#define FORPIPE_ frpipe
#define FORKERR_ frkerr
#define FORKCHD_ chd
#define CHDSEND1_ chdsnd1
#define CHDSEND2_ chdsnd2
#define CHDSEND3_ chdsnd3
#define CHDSEND4_ CHDSEND4_
#define CHDSEND5_ chdsnd5

#define DEPWRITE_ depwrite
#define DEPWRITE2_ depwrite2
#define DEPWRITE3_ depwrite3
#define DEPWRITE4_ depwrite4
#define DEPWRITE5_ depwrite5

#define DERPREAD_ depread
#define DERPREAD2_ depread2
#define DERPREAD3_ depread3
#define DERPREAD4_ depread4
#define DERPREAD5_ depread5

#define CHDEXIT_ chdexit
#define PARENTRECEIVE_ parntrcv
#define PARENTRECEIVE2_ parntrcv2
#define PARENTRECEIVE3_ parntrcv3
#define VOTE_MAJORITY_ votmjrt
#define VOTE_MAJORITY2_ votmjrt2
#define VOTE_MAJORITY3_ votmjrt3
#define VOTE_MAJORITY4_ votmjrt4
#define VOTE_MAJORITY5_ votmjrt5
#define VOTE_RESULT_ votresult
#define VOTE_RESULT2_ votresult2
#define VOTE_RESULT3_ votresult3
#define VOTE_RESULT4_ votresult4
#define MAINCALLVOTE_ mainvot


char iclud[] = "#include <stdio.h>\n#include <stdlib.h>\n#include <string.h>\n#include <unistd.h>\n#include <sys/wait.h>\n#include <omp.h>\n\n";

char dfn[] = "#define VOTETYPE1 int\n#define VOTETYPE2 float\n#define VOTETYPE3 short\n#define VOTETYPE4 double\n#define VOTETYPE5 long\n#define VOTETYPE6 char\n";

char dfn2[] = "\n#define Total_Num_Voter 3\n\n";

char struc[] = "struct Data{\n\tVOTETYPE1 i;\n\tVOTETYPE2 f;\n\tVOTETYPE3 s;\n\tVOTETYPE4 d;\n\tVOTETYPE5 l;\n\tVOTETYPE6 c;\n};\nstruct Data data[Total_Num_Voter];\n\n";

char frpipe[] = "\n\tint pipe_fd_Voter[2];\n\nfor(int Num_Voter=0; Num_Voter<Total_Num_Voter; Num_Voter++){\n\tif (pipe(pipe_fd_Voter) == -1){\n\t\t\tfprintf(stderr, \"Error: Unable to create pipe.\\n\");\n\t\texit(EXIT_FAILURE);\n\t}\n\n";

char frkerr[] = "\tpid_t pid_Voter;\n\tif ((pid_Voter = fork()) < 0){\n\t\tfprintf(stderr, \"Error: Unable to fork process.\\n\");\n\t\texit(EXIT_FAILURE);\n\t}\n";


char chd[] = "\telse if (pid_Voter == 0) /*-- Child --*/\n\t{\n\t\tclose(pipe_fd_Voter[0]);\n";

char chdsnd1[] = "\t\tint p=1; printf(\"p:%d\\n\",p);\n\t\tstruct Data *data_chd = (struct Data *)malloc(sizeof(struct Data)); //= malloc(sizeof(*Data));\n\t\tdata_chd->";///** vType  **/

char chdsnd2[] = " = ";/** voteName **/;

char chdsnd3[] = ";\n\t\twrite(pipe_fd_Voter[1], &data_chd->";///** vType  **/

char chdsnd4[] = ", sizeof(";//VOTETYPE 

char chdsnd5[] = "));\n";


char depwrite[] = "\t\tif(Num_Voter==2){";

char depwrite2[] = "\n\t\t\tclose(pipe_fd_Voter[0]);\n\t\t\twrite(pipe_fd_Voter[1], &";///*depVar[dep_i]*/
char depwrite3[] = ", sizeof(";///** depType  **/
char depwrite4[] = "));";

char depwrite5[] = "\n\t\t}\n";

char chdexit[] = "\n\t\texit(EXIT_SUCCESS);\n\t}\n\n";


char parntrcv[] = "\telse /*-- Parent --*/\n\t{\n\t\tclose(pipe_fd_Voter[1]);\n\t\t//struct Data *data_Voter = (struct Data *)malloc(sizeof(struct Data)); //= malloc(sizeof(*Data));\n\t\tread(pipe_fd_Voter[0], &data[Num_Voter].";///** vType  **/

char parntrcv2[] = ", sizeof(";//VOTETYPE 

char parntrcv3[] = "));\n\n";


char depread[] = "\t\t//if(Num_Voter==2){";

char depread2[] = "\n\t\t\tclose(pipe_fd_Voter[1]);\n\t\t\tread(pipe_fd_Voter[0],  &";///*depVar[dep_i]*/
char depread3[] = ", sizeof(";///** depType  **/
char depread4[] = "));";

char depread5[] ="\n\t\t//}\n";


char votmjrt[] = "//------find the candidate of majority voter------//\nif(Num_Voter==2){\n\tint num_Voter=0;\n\t";//VOTETYPE 

char votmjrt2[] = " v_result;\n\t//char v_result[1024];\n\tint i_Voter;\n\tfor( i_Voter=0; i_Voter<Total_Num_Voter; i_Voter++){\n\t\tif(num_Voter==0) {\n\t\t\tv_result = data[i_Voter].";///** vType  **/

char votmjrt3[] = "; //sprintf( v_result, \"%d\", data[i_Voter].";///** vType  **/

char votmjrt4[] = " );	//int? float? char?\n\t\tnum_Voter=1;\n\t\t}\n\t\telse{  //still be the majority voter\n\t\t\tif(data[i_Voter].";///** vType  **/

char votmjrt5[] = "!=v_result) num_Voter--;\n\t\t\telse num_Voter++;\n\t\t}\n\t}\n";

char votresult[] = "\t//confirm that the v_result is a really majority voter\n\tnum_Voter = Num_Voter;\n\tfor(i_Voter=0; i_Voter < Total_Num_Voter; i_Voter++) if(data[i_Voter].";///** vType  **/

char votresult2[] = "!=v_result) num_Voter--;\n\t//if v_result is the majority voter, correct the answer to v_result\n\tif(num_Voter>=(Num_Voter+1)/2) {\n\t\tprintf(\"\\33\\[1;33m \\n\\tCorrect the answer to :\\n\\t%f \\33\\[0m \\n\\n\", v_result);\n\t\t"; /** voteName **/

char votresult3[] = " = v_result;//return ;  //successful\n\n";

char votresult4[] = "\n\t}\n \telse {\n\t\tprintf(\"\\33\\[1;31m \\n--There doesn't have a majority voter...-- \\33\\[0m \\n\");\n\t\tNum_Voter=0; //Doesn't have a majority voter\n\t}\n}\n//------find the candidate of majority voter------//\n\n\t}\n}\n\n";



char mainvot[] = "\nint main()\n{\n\tCalculation_and_Vote();\n\tprintf(\"END\\n\");\nreturn 0;\n}\n\n";



#endif
