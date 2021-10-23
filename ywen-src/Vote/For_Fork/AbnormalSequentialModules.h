#ifndef ABNORMALSEQUENTIALMODULES_H_
#define ABNORMALSEQUENTIALMODULES_H_

#define ABSEQVARS_	abSeqVars
#define ABSEQINIT_	abSeqInit

#define ABSEQUENTIAL1_	abSequential1
#define ABSEQUENTIAL2_	abSequential2
#define ABSEQUENTIAL3_	abSequential3
#define ABSEQUENTIAL4_	abSequential4
#define ABSEQUENTIAL5_	abSequential5

#define ABSEQRECV1_	abSequentialRecv1
#define ABSEQRECV2_	abSequentialRecv2
#define ABSEQRECV3_	abSequentialRecv3
#define ABSEQRECV4_	abSequentialRecv4
#define ABSEQRECV5_	abSequentialRecv5
#define ABSEQRECV6_	abSequentialRecv6
#define ABSEQRECV7_	abSequentialRecv7
#define ABSEQRECV8_	abSequentialRecv8

#define ABSEQVV1_	abSequentialVoterVars1
#define ABSEQVV2_	abSequentialVoterVars2
#define ABSEQVV3_	abSequentialVoterVars3
#define ABSEQVV4_	abSequentialVoterVars4

#define ABSEQOPTCMP1_	abSeqOptimizeCompare1
#define ABSEQOPTCMP2_	abSeqOptimizeCompare2
#define ABSEQOPTCMP3_	abSeqOptimizeCompare3
#define ABSEQOPTCMP4_	abSeqOptimizeCompare4
#define ABSEQOPTCMP5_	abSeqOptimizeCompare5
#define ABSEQOPTCMP6_	abSeqOptimizeCompare6
#define ABSEQOPTCMP7_	abSeqOptimizeCompare7

#define ABSEQOPTCMPV1_	abSeqOptimizeCompareVars1
#define ABSEQOPTCMPV2_	abSeqOptimizeCompareVars2
#define ABSEQOPTCMPV3_	abSeqOptimizeCompareVars3
#define ABSEQOPTCMPV4_	abSeqOptimizeCompareVars4
#define ABSEQOPTCMPV5_	abSeqOptimizeCompareVars5
#define ABSEQOPTCMPV6_	abSeqOptimizeCompareVars6
#define ABSEQOPTCMPV7_	abSeqOptimizeCompareVars7
#define ABSEQOPTCMPV8_	abSeqOptimizeCompareVars8

#define ABSEQCMPVV1_	abSequentialCompareVoterVars1
#define ABSEQCMPVV2_	abSequentialCompareVoterVars2
#define ABSEQCMPVV3_	abSequentialCompareVoterVars3
#define ABSEQCMPVV4_	abSequentialCompareVoterVars4
#define ABSEQCMPVV5_	abSequentialCompareVoterVars5

#define ABSEQVOTER1_	abSequentialVoter1
#define ABSEQVOTER2_	abSequentialVoter2
#define ABSEQVOTER3_	abSequentialVoter3
#define ABSEQVOTER4_	abSequentialVoter4
#define ABSEQVOTER5_	abSequentialVoter5

#define ABSEQOPTFINISH1_	abSeqOptimizeFinish1
#define ABSEQOPTFINISH2_	abSeqOptimizeFinish2
#define ABSEQOPTFINISH3_	abSeqOptimizeFinish3
#define ABSEQOPTFINISH4_	abSeqOptimizeFinish4

#define ABSEQCORRECTOR1_	abSequentialCorrector1
#define ABSEQCORRECTOR2_	abSequentialCorrector2
#define ABSEQCORRECTOR3_	abSequentialCorrector3
#define ABSEQCORRECTOR4_	abSequentialCorrector4
#define ABSEQCORRECTOR5_	abSequentialCorrector5
#define ABSEQCORRECTOR6_	abSequentialCorrector6

#define ABSEQRDEPVAR1_	abSequentialReadDepVar1
#define ABSEQRDEPVAR2_	abSequentialReadDepVar2
#define ABSEQRDEPVAR3_	abSequentialReadDepVar3

#define ABSEQCLOSEPIPE_	abSequentialClosePipes

#define ABSEQFINISHFLAGS1_	abSequentialFinishFlags1
#define ABSEQFINISHFLAGS2_	abSequentialFinishFlags2

#define ABSEQWTARGETVAR1_	abSequentialWriteTargetVar1
#define ABSEQWTARGETVAR2_	abSequentialWriteTargetVar2
#define ABSEQWTARGETVAR3_	abSequentialWriteTargetVar3

#define ABSEQWDEPVAR1_	abSequentialWriteDepVar1
#define ABSEQWDEPVAR2_	abSequentialWriteDepVar2
#define ABSEQWDEPVAR3_	abSequentialWriteDepVar3

char abSeqVars[] = 	"\n\tpid_t pid;"
										"\n\tint pipe_fd_Voter[2];"
										"\n\tint pipe_fd_Voter2[2];"
										"\n\tchar k[50] = \"kill -9 \";"
										"\n\tchar chpid[12];"
										"\n\tint finish = 0;"
										"\n\tint respawn = 0;"
										"\n\tint child_cnt = 0;"
										"\n\tint RedundantFlag = 0;"
										"\n\tint process_cnt = 0;"
										"\n\tint GotoFlag = 0;";

char abSeqInit[] = 	"\n\tif (pipe(pipe_fd_Voter2) == -1) {"
										"\n\t\tfprintf(stderr, \"Error: Unable to create pipe.\\n\");"
										"\n\t\texit(EXIT_FAILURE);"
										"\n\t}";

char abSequential1[] = 	"\n\tfor (int Num_Voter = 0; finish != 1; Num_Voter++) {"
												"\n\t\tint chdpid;"
												"\n\t\tif (pipe(pipe_fd_Voter) == -1) {"
												"\n\t\t\tfprintf(stderr, \"Error: Unable to create pipe.\\n\");"
												"\n\t\t\texit(EXIT_FAILURE);"
												"\n\t\t}"
												"\n\t\tif ((pid = fork()) < 0) {"
												"\n\t\t\tfprintf(stderr, \"Error: Unable to fork process.\\n\");"
												"\n\t\t\texit(EXIT_FAILURE);"
												"\n\t\t}"
												"\n\t\tFORK:"
												"\n\t\twhile ((Pre_Num_Voter + process_cnt) <= MaxForkTimes && RedundantFlag == 1) {"
												"\n\t\t\tif (pid > 0) {"
												"\n\t\t\t\tif (pipe(pipe_fd_Voter) == -1) {"
												"\n\t\t\t\t\tfprintf(stderr, \"Error: Unable to create pipe.\\n\");"
												"\n\t\t\t\t\texit(EXIT_FAILURE);"
												"\n\t\t\t\t}"
												"\n\t\t\t\tpid = fork();"
												"\n\t\t\t\tchild_cnt++;"
												"\n\t\t\t\tif (pid == 0) {"
												"\n\t\t\t\t\tclose(pipe_fd_Voter[0]);"
												"\n\t\t\t\t\tchdpid = getpid();"
												"\n\t\t\t\t\twrite(pipe_fd_Voter[1], &chdpid, sizeof(int));"
												"\n\t\t\t\t\tprintf(\"\\n\\t\\33\\[1;31mNew Child Process be forked %d: %4d\\33\\[0m\\n\", child_cnt, chdpid);"
												"\n\t\t\t\t}"
												"\n\t\t\t\tGotoFlag = 0;"
												"\n\t\t\t\tbreak;"
												"\n\t\t\t}"
												"\n\t\t}"
												"\n\t\tif (pid > 0) {"
												"\n\t\t\tprintf(\"==================== Parent Process %d ====================\\n\", getpid());"
												"\n\t\t\tint time_delay = 0;"
												"\n\t\t\tclose(pipe_fd_Voter[1]);"
												"\n\t\t\tread(pipe_fd_Voter[0], &chdpid, sizeof(int));"
												"\n\t\t\tprintf(\"---Child Process:%4d\\n\", chdpid);"
												"\n\t\t\tmemset(k, '\\0', strlen(k));"
												"\n\t\t\tmemset(chpid, '\\0', strlen(chpid));"
												"\n\t\t\tstrcpy(k, \"kill -9 \");"
												"\n\t\t\tsprintf(chpid, \"%d\", chdpid);"
												"\n\t\t\tstrcat(k, chpid);"
												"\n\t\t\tfor (; finish != 1;) {"
												"\n\t\t\t\tint w_return = waitpid(-1, NULL, WNOHANG | WUNTRACED);"
												"\n\t\t\t\tif (w_return == 0) {"
												"\n\t\t\t\t\tsleep(1);"
												"\n\t\t\t\t\ttime_delay++;"
												"\n\t\t\t\t\tprintf(\"time_delay++ = %d\\n\", time_delay);"
												"\n\t\t\t\t\tif (time_delay == 5) {"
												"\n\t\t\t\t\t\tprintf(\"\\t+++time_delay = %d\\n\", time_delay);"
												"\n\t\t\t\t\t\ttime_delay = 0;"
												"\n\t\t\t\t\t\tsystem(k);"
												"\n\t\t\t\t\t\trespawn = 1;"
												"\n\t\t\t\t\t\tNum_Voter--;"
												"\n\t\t\t\t\t\tbreak;"
												"\n\t\t\t\t\t} else {"
												"\n\t\t\t\t\t\trespawn = 0;"
												"\n\t\t\t\t\t}"
												"\n\t\t\t\t} else if (w_return > 0 && respawn != 1) {"
												"\n\t\t\t\t\tif (RedundantFlag == 1) {"
												"\n\t\t\t\t\t\t// receiver";

char abSequentialRecv1[] = 	"\n\t\t\t\t\t\t\treceiver_"; // + targetVar.siza()
char abSequentialRecv2[] = 	"(pipe_fd_Voter2[0], Num_Voter, &data_"; // + targetVar.size()
char abSequentialRecv3[] = 	"[process_cnt+1]."; // + tType
char abSequentialRecv4[] = 	");";


char abSequential2[] = 	"\n\t\t\t\t\t} else if (RedundantFlag == 0) {"
												"\n\t\t\t\t\t\t// receiver";

char abSequentialRecv5[] = 	"\n\t\t\t\t\t\t\treceiver_"; // + targetVar.size()
char abSequentialRecv6[] = 	"(pipe_fd_Voter2[0], Num_Voter, &data_"; // + targetVar.size()
char abSequentialRecv7[] = 	"[Num_Voter]."; // + tType
char abSequentialRecv8[] = 	");";

char abSequential3[] = 	"\n\t\t\t\t\t}"
												"\n\t\t\t\t\ttime_delay = 0;"
												"\n\t\t\t\t\tif (Num_Voter == 1) {";

char abSequentialVoterVars1[] = 	"\n\t\t\t\t\t\t\t"; // + targetType
char abSequentialVoterVars2[] =		" v_result_"; // + targetVar.size()
char abSequentialVoterVars3[] = 	";"
																		"\n\t\t\t\t\t\t\tint num_Voter_"; // + targetVar.size()
char abSequentialVoterVars4[] = 	" = 0;";


char abSeqOptimizeCompare1[] = "\n\t\t\t\t\t\t\tif (( 0";

char abSeqOptimizeCompareVars1[] = "\n\t\t\t\t\t\t\t\t|| data_"; // + targetVar.size()
char abSeqOptimizeCompareVars2[] = "[0]."; // + tType
char abSeqOptimizeCompareVars3[] = " != data_"; // + targetVar.size()
char abSeqOptimizeCompareVars4[] = "[1]."; // + tType

char abSeqOptimizeCompare2[] = 	") && RedundantFlag == 0) {"
																"\n\t\t\t\t\t\t\t\tprocess_cnt++;"
																"\n\t\t\t\t\t\t\t\tRedundantFlag = 1;"
																"\n\t\t\t\t\t\t\t\tGotoFlag = 1;"
																"\n\t\t\t\t\t\t\t} else if ( 1";

char abSeqOptimizeCompareVars5[] = "\n\t\t\t\t\t\t\t\t&& data_"; // + targetVar.size()
char abSeqOptimizeCompareVars6[] = "[0]."; // + tType
char abSeqOptimizeCompareVars7[] = " == data_"; // + targetVar.size()
char abSeqOptimizeCompareVars8[] = "[1]."; // + tType

char abSeqOptimizeCompare3[] = ") {";

char abSequentialCompareVoterVars1[] = 	"\n\t\t\t\t\t\t\t\tv_result_"; // + targetVar.size()
char abSequentialCompareVoterVars2[] = 	" = data_"; // + targetVar.size()
char abSequentialCompareVoterVars3[] = 	"[0]."; // + tType
char abSequentialCompareVoterVars4[] = 	";"
																					"\n\t\t\t\t\t\t\t\tnum_Voter_"; // + targetVar.size()
char abSequentialCompareVoterVars5[] = 	"++;";

char abSeqOptimizeCompare4[] = 	"\n\t\t\t\t\t\t\t}"
																"\n\t\t\t\t\t\t\tif (RedundantFlag == 1 && GotoFlag == 1) {"
																"\n\t\t\t\t\t\t\t\tgoto FORK;               "
																"\n\t\t\t\t\t\t\t}"
																"\n\t\t\t\t\t\t\tif (RedundantFlag == 1 && GotoFlag == 0) {"
																"\n\t\t\t\t\t\t\t\t// voter";

char abSequentialVoter1[] = "\n\t\t\t\t\t\t\t\tvoter_"; // + targetType.size()
char abSequentialVoter2[] = "(&num_Voter_"; // + targetVar.size()
char abSequentialVoter3[] = ", process_cnt, &v_result_"; // + targetVar.size()
char abSequentialVoter4[] = ", data_"; // + targetVar.size()
char abSequentialVoter5[] = ");";

char abSeqOptimizeCompare5[] = "\n\t\t\t\t\t\t\t}"
													"\n\t\t\t\t\t\t\tif (RedundantFlag == 0";

char abSeqOptimizeFinish1[] = "\n\t\t\t\t\t\t\t\t&& num_Voter_"; // + targetVar.size()
char abSeqOptimizeFinish2[] = " >= (Pre_Num_Voter + 1) / 2";

char abSeqOptimizeCompare6[] = ") {";

char abSequentialCorrector1[] = "\n\t\t\t\t\t\t\t\t// corrector";
char abSequentialCorrector2[] = "\n\t\t\t\t\t\t\t\tcorrector_"; // + targetType.size()
char abSequentialCorrector3[] = "(process_cnt, &v_result_"; // + targetVar.size()
char abSequentialCorrector4[] = ", &"; // + targetVar
char abSequentialCorrector5[] = ", data_"; // + targetType.size()
char abSequentialCorrector6[] = ");";

char abSequentialReadDepVar1[] = "\n\t\t\t\t\t\t\t\tread(pipe_fd_Voter[0], &"; // + depVar
char abSequentialReadDepVar2[] = ", sizeof("; // + depVarType
char abSequentialReadDepVar3[] = "));";

char abSequentialClosePipes[] = 	"\n\t\t\t\t\t\t\t\tclose(pipe_fd_Voter[0]);"
																	"\n\t\t\t\t\t\t\t\tclose(pipe_fd_Voter[1]);"
																	"\n\t\t\t\t\t\t\t\tclose(pipe_fd_Voter2[0]);"
																	"\n\t\t\t\t\t\t\t\tclose(pipe_fd_Voter2[1]);";
char abSequentialFinishFlags1[] = 	"\n\t\t\t\t\t\t\t\tprintf(\"FINISH\\n\");"
																		"\n\t\t\t\t\t\t\t\tfinish = 1;"
																		"\n\t\t\t\t\t\t\t\trespawn = 0;";

char abSeqOptimizeCompare7[] = "\n\t\t\t\t\t\t\t} else if (RedundantFlag == 1";

char abSeqOptimizeFinish3[] = "\n\t\t\t\t\t\t\t\t&& num_Voter_"; // + targetVar.size()
char abSeqOptimizeFinish4[] = " >= (Pre_Num_Voter + process_cnt + 1) / 2";

char abSequentialFinishFlags2[] = 	"\n\t\t\t\t\t\t\t\tprintf(\"FINISH\\n\");"
																		"\n\t\t\t\t\t\t\t\tRedundantFlag = 0;"
																		"\n\t\t\t\t\t\t\t\tGotoFlag = 0;"
																		"\n\t\t\t\t\t\t\t\tfinish = 1;"
																		"\n\t\t\t\t\t\t\t\trespawn = 0;";
										
char abSequential4[] = 	"\n\t\t\t\t\t\t} else {"
												"\n\t\t\t\t\t\t\tprintf(\"\\33\\[1;31m \\n\\t -- There doesn't exist a majority voter -- \\33\\[0m \\n\\n\");"
												"\n\t\t\t\t\t\t\tNum_Voter = 0;"
												"\n\t\t\t\t\t\t\tprocess_cnt++;"
												"\n\t\t\t\t\t\t\tRedundantFlag = 1;"
												"\n\t\t\t\t\t\t\tGotoFlag = 1;"
												"\n\t\t\t\t\t\t}"
												"\n\t\t\t\t\t} else {"
												"\n\t\t\t\t\t\ttime_delay = 0;"
												"\n\t\t\t\t\t\trespawn = 0;"
												"\n\t\t\t\t\t}"
												"\n\t\t\t\t\tbreak;"
												"\n\t\t\t\t} else if (w_return < 0) {"
												"\n\t\t\t\t\tbreak;"
												"\n\t\t\t\t}"
												"\n\t\t\t}"
												"\n\t\t} else {"
												"\n\t\t\tchdpid = getpid();"
												"\n\t\t\twrite(pipe_fd_Voter[1], &chdpid, sizeof(int));"
												"\n\t\t\tprintf(\"------------>Child Process has arrived: %4d\\n\", getpid());";

char abSequentialWriteTargetVar1[] = 	"\n\t\t\t\twrite(pipe_fd_Voter2[1], &"; // + targetVar
char abSequentialWriteTargetVar2[] = 	", sizeof("; // + targetType
char abSequentialWriteTargetVar3[] = 	"));";


char abSequentialWriteDepVar1[] = "\n\t\t\t\twrite(pipe_fd_Voter[1], &"; // + depVar
char abSequentialWriteDepVar2[] = ", sizeof("; // + depType
char abSequentialWriteDepVar3[] = "));";

char abSequential5[] = 	"\n\t\t\tprintf(\"------------>Child Process has done: %4d\\n\", getpid());"
												"\n\t\t\tfinish = 1;"
												"\n\t\t\texit(EXIT_SUCCESS);"
												"\n\t\t}"
												"\n\t}";

#endif