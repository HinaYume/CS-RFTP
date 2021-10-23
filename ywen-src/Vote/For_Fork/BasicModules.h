#ifndef BASICMODULES_H_
#define BASICMODULES_H_

#define LIBRARY_	library
#define OMPLIBRARY_	ompLibrary

#define GLOBALVARS_	globalVars

#define DATATYPE_	dataType
#define DATASTRUCT_	dataStruct
#define DATADECL1_	dataDecl1
#define DATADECL2_	dataDecl2

#define RECEIVERDECL1_	receiverDecl1
#define RECEIVERDECL2_	receiverDecl2
#define RECEIVERDECL3_	receiverDecl3
#define MPRECEIVERFUNC1_	mpReceiveFunc1
#define MPRECEIVERFUNC2_	mpReceiveFunc2
#define MPRECEIVERFUNC3_	mpReceiveFunc3
#define MPRECEIVERFUNC4_	mpReceiveFunc4
#define MPRECEIVERFUNC5_	mpReceiveFunc5

#define VOTERDECL1_	voterDecl1
#define	VOTERDECL2_ voterDecl2
#define VOTERDECL3_	voterDecl3
#define	MPVOTERFUNC1_	mpVoteFunc1
#define	MPVOTERFUNC2_	mpVoteFunc2
#define	MPVOTERFUNC3_	mpVoteFunc3
#define	MPVOTERFUNC4_	mpVoteFunc4
#define	MPVOTERFUNC5_	mpVoteFunc5
#define	MPVOTERFUNC6_	mpVoteFunc6
#define	MPVOTERFUNC7_	mpVoteFunc7
#define	MPVOTERFUNC8_	mpVoteFunc8
#define	MPVOTERFUNC9_	mpVoteFunc9

#define CORRECTORDECL1_	correctorDecl1
#define CORRECTORDECL2_	correctorDecl2
#define CORRECTORDECL3_	correctorDecl3
#define CORRECTORDECL4_	correctorDecl4
#define MPCORRECTORFUNC1_	mpCorrectorFunc1
#define MPCORRECTORFUNC2_	mpCorrectorFunc2
#define MPCORRECTORFUNC3_	mpCorrectorFunc3
#define MPCORRECTORFUNC4_	mpCorrectorFunc4
#define MPCORRECTORFUNC5_	mpCorrectorFunc5
#define MPCORRECTORFUNC6_	mpCorrectorFunc6
#define MPCORRECTORFUNC7_	mpCorrectorFunc7
#define MPCORRECTORFUNC8_	mpCorrectorFunc8

#define SEQRECEIVERFUNC1_	seqReceiveFunc1
#define SEQRECEIVERFUNC2_	seqReceiveFunc2
#define SEQRECEIVERFUNC3_	seqReceiveFunc3
#define SEQRECEIVERFUNC4_	seqReceiveFunc4
#define SEQRECEIVERFUNC5_	seqReceiveFunc5



char library[] = "#include <string.h>"
									"\n#include <unistd.h>"
									"\n#include <sys/wait.h>";
char ompLibrary[] = "\n#include <omp.h>";

char globalVars[] = "\n\n#define Pre_Num_Voter   2"
										"\n#define MaxForkTimes    5";

char dataType[]	=	"\n\n#define VOTETYPE1 int"
									"\n#define VOTETYPE2 float"
									"\n#define VOTETYPE3 short"
									"\n#define VOTETYPE4 double"
									"\n#define VOTETYPE5 long"
									"\n#define VOTETYPE6 char";
char dataStruct[]	= "\n\nstruct Data {"
									 "\n\tVOTETYPE1 i;"
									 "\n\tVOTETYPE2 f;"
									 "\n\tVOTETYPE3 s;"
									 "\n\tVOTETYPE4 d;"
									 "\n\tVOTETYPE5 l;"
									 "\n\tVOTETYPE6 c;"
									 "\n};";

char dataDecl1[] = "\nstruct Data data_"; // + targetVar.size()
char dataDecl2[] = "[MaxForkTimes];";

char receiverDecl1[]	= "\nvoid receiver_"; // + targetType.size()
char receiverDecl2[]  = "(int, int, "; // + targetType
char receiverDecl3[]	= "*);";
char mpReceiveFunc1[]	= "\nvoid receiver_"; // + targetType.size()
char mpReceiveFunc2[]  = "(int pipe_fd_Voter_2_read, int process_num, "; // + targetType *
char mpReceiveFunc3[]	= "* dataElement) {"
												"\n\tread(pipe_fd_Voter_2_read, dataElement, sizeof("; // + targetType
char mpReceiveFunc4[]	= "));"
												"\n\tprintf(\"\\n\\t+++ recv: %"; // + perType
char mpReceiveFunc5[]  = " from child process\" , *dataElement);"
												"\n\tprintf(\"\\n\\t+++ remaining process num: %d\\n\\n\", process_num);"
												"\n}";

char voterDecl1[] = "\nvoid voter_"; // + targetType.size()
char voterDecl2[] = "(int*, int, "; // + targetType
char voterDecl3[] = "*, struct Data[]);";
char mpVoteFunc1[]	= "\nvoid voter_"; // + targetType.size()
char mpVoteFunc2[] = "(int* num_Voter, int process_cnt, "; // + targetType
char mpVoteFunc3[] = "* v_result, struct Data data[]) {"
										"\n\tprintf(\"\\tCandiates of data:\\n\");"
										"\n\tfor (int i_Voter = 0; i_Voter < Pre_Num_Voter+process_cnt; i_Voter++) {"
										"\n\t\tif (*num_Voter == 0) {"
										"\n\t\t\t*v_result = data[i_Voter]."; // + tType
char mpVoteFunc4[] = ";"										
										"\n\t\t\t*num_Voter = 1;"
										"\n\t\t}"
										"\n\t\telse { "
										"\n\t\t\tif(data[i_Voter]."; // + tType
char mpVoteFunc5[] = " != *v_result) (*num_Voter)--;"
										"\n\t\t\telse (*num_Voter)++;"
										"\n\t\t}"
 										"\n\t\tprintf(\"\\tdata[%d]: %"; // + perType
char mpVoteFunc6[] =	"\\n\", i_Voter, data[i_Voter]."; // + tType
char mpVoteFunc7[]	= ");"										
										"\n\t}"
										"\n\t*num_Voter = Pre_Num_Voter+process_cnt;"
										"\n\tfor (int i_Voter = 0; i_Voter < Pre_Num_Voter+process_cnt; i_Voter++)"
										"\n\t\tif (data[i_Voter]."; // + tType
char mpVoteFunc8[]	=	" != *v_result) (*num_Voter)--;"
										"\n\tprintf(\"\\n\\tThe Voting rate of \\\"%"; // + perType
char mpVoteFunc9[] = "\\\" is %.2f%%\\n\", *v_result, 100.0 * *num_Voter / (Pre_Num_Voter+process_cnt));  "
										"\n\tprintf(\"\\t===> num_Voter: %d, Pre_Num_Voter+process_cnt: %d\\n\\n\", *num_Voter, Pre_Num_Voter+process_cnt);   "
										"\n}";

char correctorDecl1[]	= "\nvoid corrector_"; // + targetType.size()
char correctorDecl2[] = "(int, "; // + targetType
char correctorDecl3[]	= "*, "; // + targetType
char correctorDecl4[] = "*, struct Data[]);";
char mpCorrectorFunc1[] = "\nvoid corrector_"; // + targetType.size()
char mpCorrectorFunc2[] = "(int process_cnt, "; // + targetType
char mpCorrectorFunc3[] = "* v_result, "; // + targetType
char mpCorrectorFunc4[] = "* targetVar, struct Data data[]) {"
												"\n\t*targetVar = *v_result;"
												"\n\tfor(int i_Voter = 0; i_Voter < (Pre_Num_Voter+process_cnt); i_Voter++) {"
												"\n\t\tdata[i_Voter]."; // + tType
char mpCorrectorFunc5[] = " = *v_result;"												
												"\n\t\tprintf(\"\\tdata[%d]: %"; // + perType
char mpCorrectorFunc6[] = "\\n\", i_Voter, data[i_Voter]."; // + tType
char mpCorrectorFunc7[] = ");"
												"\n\t}"
												"\n\tprintf(\"\\33\\[1;33m \\n\\tCorrect the answer to :\\n\\t%"; // + perType
char mpCorrectorFunc8[] =	" \\33\\[0m \\n\\n\", *v_result);"
												"\n}";

char seqReceiveFunc1[] =  "\nvoid receiver_"; // + targetType.size()
char seqReceiveFunc2[] =  "(int pipe_fd_Voter_2_read, int Num_Voter, "; // + targetType *
char seqReceiveFunc3[] =  "* dataElement) {"
                          "\n\tread(pipe_fd_Voter_2_read, dataElement, sizeof("; // + targetType
char seqReceiveFunc4[] =  "));"
                          "\n\tprintf(\"\\n\\t+++ recv: %"; // + perType
char seqReceiveFunc5[] =  " from child process, Num_Voter:%d\\n\\n\" , *dataElement, Num_Voter);"
                          "\n}";
#endif
