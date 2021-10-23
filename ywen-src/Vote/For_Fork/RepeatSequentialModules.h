#ifndef REPEATSEQUENTIALMODULES_H_
#define REPEATSEQUENTIALMODULES_H_

#define RPSEQVARS_		rpSeqVars
#define RPSEQWHILE1_	rpSeqWhile1
#define RPSEQWHILE2_	rpSeqWhile2

#define RPSEQUENTIAL1_	rpSequential1
#define RPSEQUENTIAL2_	rpSequential2
#define RPSEQUENTIAL3_	rpSequential3
#define RPSEQUENTIAL4_	rpSequential4
#define RPSEQUENTIAL5_	rpSequential5

#define RPSEQRECV1_	rpSequentialRecv1
#define RPSEQRECV2_	rpSequentialRecv2
#define RPSEQRECV3_	rpSequentialRecv3
#define RPSEQRECV4_	rpSequentialRecv4
#define RPSEQRECV5_	rpSequentialRecv5
#define RPSEQRECV6_	rpSequentialRecv6
#define RPSEQRECV7_	rpSequentialRecv7
#define RPSEQRECV8_	rpSequentialRecv8

#define RPSEQVV1_	rpSequentialVoterVars1
#define RPSEQVV2_	rpSequentialVoterVars2
#define RPSEQVV3_	rpSequentialVoterVars3
#define RPSEQVV4_	rpSequentialVoterVars4

#define RPSEQOPTCMP1_	rpSeqOptimizeCompare1
#define RPSEQOPTCMP2_	rpSeqOptimizeCompare2
#define RPSEQOPTCMP3_	rpSeqOptimizeCompare3
#define RPSEQOPTCMP4_	rpSeqOptimizeCompare4
#define RPSEQOPTCMP5_	rpSeqOptimizeCompare5
#define RPSEQOPTCMP6_	rpSeqOptimizeCompare6
#define RPSEQOPTCMP7_	rpSeqOptimizeCompare7

#define RPSEQOPTCMPV1_	rpSeqOptimizeCompareVars1
#define RPSEQOPTCMPV2_	rpSeqOptimizeCompareVars2
#define RPSEQOPTCMPV3_	rpSeqOptimizeCompareVars3
#define RPSEQOPTCMPV4_	rpSeqOptimizeCompareVars4
#define RPSEQOPTCMPV5_	rpSeqOptimizeCompareVars5
#define RPSEQOPTCMPV6_	rpSeqOptimizeCompareVars6
#define RPSEQOPTCMPV7_	rpSeqOptimizeCompareVars7
#define RPSEQOPTCMPV8_	rpSeqOptimizeCompareVars8

#define RPSEQCMPVV1_	rpSequentialCompareVoterVars1
#define RPSEQCMPVV2_	rpSequentialCompareVoterVars2
#define RPSEQCMPVV3_	rpSequentialCompareVoterVars3
#define RPSEQCMPVV4_	rpSequentialCompareVoterVars4
#define RPSEQCMPVV5_	rpSequentialCompareVoterVars5

#define RPSEQVOTER1_	rpSequentialVoter1
#define RPSEQVOTER2_	rpSequentialVoter2
#define RPSEQVOTER3_	rpSequentialVoter3
#define RPSEQVOTER4_	rpSequentialVoter4
#define RPSEQVOTER5_	rpSequentialVoter5

#define RPSEQOPTFINISH1_	rpSeqOptimizeFinish1
#define RPSEQOPTFINISH2_	rpSeqOptimizeFinish2
#define RPSEQOPTFINISH3_	rpSeqOptimizeFinish3
#define RPSEQOPTFINISH4_	rpSeqOptimizeFinish4

#define RPSEQCORRECTOR1_	rpSequentialCorrector1
#define RPSEQCORRECTOR2_	rpSequentialCorrector2
#define RPSEQCORRECTOR3_	rpSequentialCorrector3
#define RPSEQCORRECTOR4_	rpSequentialCorrector4
#define RPSEQCORRECTOR5_	rpSequentialCorrector5
#define RPSEQCORRECTOR6_	rpSequentialCorrector6

#define RPSEQRDEPVAR1_	rpSequentialReadDepVar1
#define RPSEQRDEPVAR2_	rpSequentialReadDepVar2
#define RPSEQRDEPVAR3_	rpSequentialReadDepVar3

#define RPSEQCLOSEPIPE_	rpSequentialClosePipes

#define RPSEQFINISHFLAGS1_	rpSequentialFinishFlags1
#define RPSEQFINISHFLAGS2_	rpSequentialFinishFlags2

#define RPSEQWTARGETVAR1_	rpSequentialWriteTargetVar1
#define RPSEQWTARGETVAR2_	rpSequentialWriteTargetVar2
#define RPSEQWTARGETVAR3_	rpSequentialWriteTargetVar3

#define RPSEQWDEPVAR1_	rpSequentialWriteDepVar1
#define RPSEQWDEPVAR2_	rpSequentialWriteDepVar2
#define RPSEQWDEPVAR3_	rpSequentialWriteDepVar3

char rpSeqVars[] = 	"\n\tpid_t pid;"
										"\n\tint pipe_fd_Voter[2];"
										"\n\tint pipe_fd_Voter2[2];"
										"\n\tchar k[3][50];"
										"\n\tchar chpid[12];"
										"\n\tint chdpid_i[3];"
										"\n\tint finish = 0;"
										"\n\tint child_cnt = 0;"
										"\n\tint RedundantFlag = 0;"
										"\n\tint process_cnt = 0;"
										"\n\tint GotoFlag = 0;";

char rpSeqWhile1[] = "\n\twhile (1) {";

char rpSequential1[] = 	"\n\t\tfinish = 0;"
												"\n\t\tfor (int Num_Voter = 0; finish != 1; Num_Voter++) {"
												"\n\t\t\tint chdpid;"
												"\n\t\t\tif (pipe(pipe_fd_Voter) == -1) {"
												"\n\t\t\t\tfprintf(stderr, \"Error: Unable to create pipe.\\n\");"
												"\n\t\t\t\texit(EXIT_FAILURE);"
												"\n\t\t\t}"
												"\n\t\t\tif (pipe(pipe_fd_Voter2) == -1) {"
												"\n\t\t\t\tfprintf(stderr, \"Error: Unable to create pipe.\\n\");"
												"\n\t\t\t\texit(EXIT_FAILURE);"
												"\n\t\t\t}"
												"\n\t\t\tif ((pid = fork()) < 0) {"
												"\n\t\t\t\tfprintf(stderr, \"Error: Unable to fork process.\\n\");"
												"\n\t\t\t\texit(EXIT_FAILURE);"
												"\n\t\t\t}"
												"\n\t\tFORK:"
												"\n\t\t\twhile ((Pre_Num_Voter + process_cnt) <= MaxForkTimes &&"
												"\n\t\t\t\t\t\t RedundantFlag == 1) {"
												"\n\t\t\t\tif (pid > 0) {"
												"\n\t\t\t\t\tif (pipe(pipe_fd_Voter) == -1) {"
												"\n\t\t\t\t\t\tfprintf(stderr, \"Error: Unable to create pipe.\\n\");"
												"\n\t\t\t\t\t\texit(EXIT_FAILURE);"
												"\n\t\t\t\t\t}"
												"\n\t\t\t\t\tpid = fork();"
												"\n\t\t\t\t\tchild_cnt++;"
												"\n\t\t\t\t\tif (pid == 0) {"
												"\n\t\t\t\t\t\tclose(pipe_fd_Voter[0]);"
												"\n\t\t\t\t\t\tchdpid = getpid();"
												"\n\t\t\t\t\t\twrite(pipe_fd_Voter[1], &chdpid, sizeof(int));"
												"\n\t\t\t\t\t\tprintf(\"\\n\\t\\33\\[1;31mNew Child Process be forked %d: %4d\\33\\[0m\\n\", child_cnt, chdpid);"
												"\n\t\t\t\t\t}"
												"\n\t\t\t\t\tGotoFlag = 0;"
												"\n\t\t\t\t\tbreak;"
												"\n\t\t\t\t}"
												"\n\t\t\t}"
												"\n\t\t\tif (pid > 0) {"
												"\n\t\t\t\tprintf(\"==================== Parent Process %d ====================\\n\", getpid());"
												"\n\t\t\t\tclose(pipe_fd_Voter[1]);"
												"\n\t\t\t\tread(pipe_fd_Voter[0], &chdpid_i[Num_Voter], sizeof(int));"
												"\n\t\t\t\tprintf(\"---Child Process:%4d\\n\", chdpid_i[Num_Voter]);"
												"\n\t\t\t\tmemset(k[Num_Voter], '\\0', strlen(k[Num_Voter]));"
												"\n\t\t\t\tmemset(chpid, '\\0', strlen(chpid));"
												"\n\t\t\t\tstrcpy(k[Num_Voter], \"kill -9 \");"
												"\n\t\t\t\tsprintf(chpid, \"%d\", chdpid_i[Num_Voter]);"
												"\n\t\t\t\tstrcat(k[Num_Voter], chpid);"
												"\n\t\t\t\tfor (; finish != 1;) {"
												"\n\t\t\t\t\tsleep(1);"
												"\n\t\t\t\t\tint status;"
												"\n\t\t\t\t\tint w_return = waitpid(-1, &status, WNOHANG | WUNTRACED);"
												"\n\t\t\t\t\tif (w_return > 0) {"
												"\n\t\t\t\t\t\tif (WIFEXITED(status)) {"
												"\n\t\t\t\t\t\t\tif (RedundantFlag == 1) {"
												"\n\t\t\t\t\t\t\t\t// receiver";

char rpSequentialRecv1[] = 	"\n\t\t\t\t\t\t\treceiver_"; // + targetVar.siza()
char rpSequentialRecv2[] = 	"(pipe_fd_Voter2[0], Num_Voter, &data_"; // + targetVar.size()
char rpSequentialRecv3[] = 	"[process_cnt+1]."; // + tType
char rpSequentialRecv4[] = 	");";


char rpSequential2[] = 	"\n\t\t\t\t\t} else if (RedundantFlag == 0) {"
												"\n\t\t\t\t\t\t// receiver";

char rpSequentialRecv5[] = 	"\n\t\t\t\t\t\t\treceiver_"; // + targetVar.size()
char rpSequentialRecv6[] = 	"(pipe_fd_Voter2[0], Num_Voter, &data_"; // + targetVar.size()
char rpSequentialRecv7[] = 	"[Num_Voter]."; // + tType
char rpSequentialRecv8[] = 	");";

char rpSequential3[] = 	"\n\t\t\t\t\t\t\t}"
												"\n\t\t\t\t\t\t\tif (Num_Voter == 1) {";

char rpSequentialVoterVars1[] = 	"\n\t\t\t\t\t\t\t"; // + targetType
char rpSequentialVoterVars2[] =		" v_result_"; // + targetVar.size()
char rpSequentialVoterVars3[] = 	";"
																		"\n\t\t\t\t\t\t\tint num_Voter_"; // + targetVar.size()
char rpSequentialVoterVars4[] = 	" = 0;";

char rpSeqOptimizeCompare1[] = "\n\t\t\t\t\t\t\tif (( 0";

char rpSeqOptimizeCompareVars1[] = "\n\t\t\t\t\t\t\t\t|| data_"; // + targetVar.size()
char rpSeqOptimizeCompareVars2[] = "[0]."; // + tType
char rpSeqOptimizeCompareVars3[] = " != data_"; // + targetVar.size()
char rpSeqOptimizeCompareVars4[] = "[1]."; // + tType

char rpSeqOptimizeCompare2[] = 	") && RedundantFlag == 0) {"
																"\n\t\t\t\t\t\t\t\tprocess_cnt++;"
																"\n\t\t\t\t\t\t\t\tRedundantFlag = 1;"
																"\n\t\t\t\t\t\t\t\tGotoFlag = 1;"
																"\n\t\t\t\t\t\t\t} else if ( 1";

char rpSeqOptimizeCompareVars5[] = "\n\t\t\t\t\t\t\t\t&& data_"; // + targetVar.size()
char rpSeqOptimizeCompareVars6[] = "[0]."; // + tType
char rpSeqOptimizeCompareVars7[] = " == data_"; // + targetVar.size()
char rpSeqOptimizeCompareVars8[] = "[1]."; // + tType

char rpSeqOptimizeCompare3[] = ") {";

char rpSequentialCompareVoterVars1[] = 	"\n\t\t\t\t\t\t\t\tv_result_"; // + targetVar.size()
char rpSequentialCompareVoterVars2[] = 	" = data_"; // + targetVar.size()
char rpSequentialCompareVoterVars3[] = 	"[0]."; // + tType
char rpSequentialCompareVoterVars4[] = 	";"
																					"\n\t\t\t\t\t\t\t\tnum_Voter_"; // + targetVar.size()
char rpSequentialCompareVoterVars5[] = 	"++;";

char rpSeqOptimizeCompare4[] = 	"\n\t\t\t\t\t\t\t}"
																"\n\t\t\t\t\t\t\tif (RedundantFlag == 1 && GotoFlag == 1) {"
																"\n\t\t\t\t\t\t\t\tgoto FORK;               "
																"\n\t\t\t\t\t\t\t}"
																"\n\t\t\t\t\t\t\tif (RedundantFlag == 1 && GotoFlag == 0) {"
																"\n\t\t\t\t\t\t\t\t// voter";

char rpSequentialVoter1[] = "\n\t\t\t\t\t\t\t\tvoter_"; // + targetType.size()
char rpSequentialVoter2[] = "(&num_Voter_"; // + targetVar.size()
char rpSequentialVoter3[] = ", process_cnt, &v_result_"; // + targetVar.size()
char rpSequentialVoter4[] = ", data_"; // + targetVar.size()
char rpSequentialVoter5[] = ");";

char rpSeqOptimizeCompare5[] = "\n\t\t\t\t\t\t\t}"
													"\n\t\t\t\t\t\t\tif (RedundantFlag == 0";

char rpSeqOptimizeFinish1[] = "\n\t\t\t\t\t\t\t\t&& num_Voter_"; // + targetVar.size()
char rpSeqOptimizeFinish2[] = " >= (Pre_Num_Voter + 1) / 2";

char rpSeqOptimizeCompare6[] = ") {";

char rpSequentialCorrector1[] = "\n\t\t\t\t\t\t\t\t// corrector";
char rpSequentialCorrector2[] = "\n\t\t\t\t\t\t\t\tcorrector_"; // + targetType.size()
char rpSequentialCorrector3[] = "(process_cnt, &v_result_"; // + targetVar.size()
char rpSequentialCorrector4[] = ", &"; // + targetVar
char rpSequentialCorrector5[] = ", data_"; // + targetType.size()
char rpSequentialCorrector6[] = ");";

char rpSequentialReadDepVar1[] = "\n\t\t\t\t\t\t\t\tread(pipe_fd_Voter[0], &"; // + depVar
char rpSequentialReadDepVar2[] = ", sizeof("; // + depVarType
char rpSequentialReadDepVar3[] = "));";

char rpSequentialClosePipes[] = 	"\n\t\t\t\t\t\t\t\tclose(pipe_fd_Voter[0]);"
																	"\n\t\t\t\t\t\t\t\tclose(pipe_fd_Voter[1]);"
																	"\n\t\t\t\t\t\t\t\tclose(pipe_fd_Voter2[0]);"
																	"\n\t\t\t\t\t\t\t\tclose(pipe_fd_Voter2[1]);";
char rpSequentialFinishFlags1[] = 	"\n\t\t\t\t\t\t\t\tprintf(\"FINISH\\n\");"
																		"\n\t\t\t\t\t\t\t\tfinish = 1;";

char rpSeqOptimizeCompare7[] = "\n\t\t\t\t\t\t\t} else if (RedundantFlag == 1";

char rpSeqOptimizeFinish3[] = "\n\t\t\t\t\t\t\t\t&& num_Voter_"; // + targetVar.size()
char rpSeqOptimizeFinish4[] = " >= (Pre_Num_Voter + process_cnt + 1) / 2";

char rpSequentialFinishFlags2[] = 	"\n\t\t\t\t\t\t\t\tprintf(\"FINISH\\n\");"
																		"\n\t\t\t\t\t\t\t\tRedundantFlag = 0;"
																		"\n\t\t\t\t\t\t\t\tGotoFlag = 0;"
																		"\n\t\t\t\t\t\t\t\tfinish = 1;";

char rpSequential4[] = 	"\n\t\t\t\t\t\t\t\t} else {"
												"\n\t\t\t\t\t\t\t\t\tprintf(\"\\33\\[1;31m \\n\\t -- There doesn't exist a majority voter -- \\33\\[0m \\n\\n\");"
												"\n\t\t\t\t\t\t\t\t\tNum_Voter = 0;"
												"\n\t\t\t\t\t\t\t\t\tprocess_cnt++;"
												"\n\t\t\t\t\t\t\t\t\tRedundantFlag = 1;"
												"\n\t\t\t\t\t\t\t\t\tGotoFlag = 1;"
												"\n\t\t\t\t\t\t\t\t}"
												"\n\t\t\t\t\t\t\t}"
												"\n\t\t\t\t\t\t\tbreak;"
												"\n\t\t\t\t\t\t} else {"
												"\n\t\t\t\t\t\t\tfor (int num = 0; num < Num_Voter; num++) {"
												"\n\t\t\t\t\t\t\t\tsystem(k[num]);"
												"\n\t\t\t\t\t\t\t\tprintf(\"\\t\\t\\t\\tEnd:%s\\n\", k[num]);"
												"\n\t\t\t\t\t\t\t}"
												"\n\t\t\t\t\t\t\tfinish = 1;"
												"\n\t\t\t\t\t\t\tbreak;"
												"\n\t\t\t\t\t\t}"
												"\n\t\t\t\t\t} else if (w_return < 0) {"
												"\n\t\t\t\t\t\tfor (int num = 0; num < Num_Voter; num++) {"
												"\n\t\t\t\t\t\t\tsystem(k[num]);"
												"\n\t\t\t\t\t\t\tprintf(\"\\t\\t\\t\\tEnd:%s\\n\", k[num]);"
												"\n\t\t\t\t\t\t}"
												"\n\t\t\t\t\t\tfinish = 1;"
												"\n\t\t\t\t\t\tbreak;"
												"\n\t\t\t\t\t}"
												"\n\t\t\t\t}"
												"\n\t\t\t} else {"
												"\n\t\t\t\tchdpid = getpid();"
												"\n\t\t\t\twrite(pipe_fd_Voter[1], &chdpid, sizeof(int));"
												"\n\t\t\t\tprintf(\"------------>Child Process arrived: %4d\\n\", getpid());";



char rpSequentialWriteTargetVar1[] = 	"\n\t\t\t\twrite(pipe_fd_Voter2[1], &"; // + targetVar
char rpSequentialWriteTargetVar2[] = 	", sizeof("; // + targetType
char rpSequentialWriteTargetVar3[] = 	"));";


char rpSequentialWriteDepVar1[] = "\n\t\t\t\twrite(pipe_fd_Voter[1], &"; // + depVar
char rpSequentialWriteDepVar2[] = ", sizeof("; // + depType
char rpSequentialWriteDepVar3[] = "));";

char rpSequential5[] = 	"\n\t\t\t\tprintf(\"------------>Child Process done: %4d\\n\", getpid());"
												"\n\t\t\t\tfinish = 1;"
												"\n\t\t\t\texit(EXIT_SUCCESS);"
												"\n\t\t\t}"
												"\n\t\t}";

char rpSeqWhile2[] = "\n\t}";

#endif