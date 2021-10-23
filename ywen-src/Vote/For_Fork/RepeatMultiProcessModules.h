#ifndef REPEATMULTIPROCESSMODULES_H_
#define REPEATMULTIPROCESSMODULES_H_

#define RPMPVARS_			rpMpVars
#define RPMPWHILE1_		rpMpWhile1
#define RPMPWHILE2_		rpMpWhile2
#define RPMPINIT_			rpMpInit

#define RPMULTIPROCESS1_	rpMultiprocess1
#define RPMULTIPROCESS2_	rpMultiprocess2
#define RPMULTIPROCESS3_	rpMultiprocess3
#define RPMULTIPROCESS4_	rpMultiprocess4
#define RPMULTIPROCESS5_	rpMultiprocess5

#define RPMPRECV1_	rpMultiprocessRecv1
#define RPMPRECV2_	rpMultiprocessRecv2
#define RPMPRECV3_	rpMultiprocessRecv3
#define RPMPRECV4_	rpMultiprocessRecv4
#define RPMPRECV5_	rpMultiprocessRecv5
#define RPMPRECV6_	rpMultiprocessRecv6
#define RPMPRECV7_	rpMultiprocessRecv7
#define RPMPRECV8_	rpMultiprocessRecv8

#define RPMPVV1_	rpMultiprocessVoterVars1
#define RPMPVV2_	rpMultiprocessVoterVars2
#define RPMPVV3_	rpMultiprocessVoterVars3
#define RPMPVV4_	rpMultiprocessVoterVars4

#define RPMPOPTCMP1_	rpMpOptimizeCompare1
#define RPMPOPTCMP2_	rpMpOptimizeCompare2
#define RPMPOPTCMP3_	rpMpOptimizeCompare3
#define RPMPOPTCMP4_	rpMpOptimizeCompare4
#define RPMPOPTCMP5_	rpMpOptimizeCompare5
#define RPMPOPTCMP6_	rpMpOptimizeCompare6
#define RPMPOPTCMP7_	rpMpOptimizeCompare7

#define RPMPOPTCMPV1_	rpMpOptimizeCompareVars1
#define RPMPOPTCMPV2_	rpMpOptimizeCompareVars2
#define RPMPOPTCMPV3_	rpMpOptimizeCompareVars3
#define RPMPOPTCMPV4_	rpMpOptimizeCompareVars4
#define RPMPOPTCMPV5_	rpMpOptimizeCompareVars5
#define RPMPOPTCMPV6_	rpMpOptimizeCompareVars6
#define RPMPOPTCMPV7_	rpMpOptimizeCompareVars7
#define RPMPOPTCMPV8_	rpMpOptimizeCompareVars8

#define RPMPCMPVV1_	rpMultiprocessCompareVoterVars1
#define RPMPCMPVV2_	rpMultiprocessCompareVoterVars2
#define RPMPCMPVV3_	rpMultiprocessCompareVoterVars3
#define RPMPCMPVV4_	rpMultiprocessCompareVoterVars4
#define RPMPCMPVV5_	rpMultiprocessCompareVoterVars5

#define RPMPVOTER1_	rpMultiprocessVoter1
#define RPMPVOTER2_	rpMultiprocessVoter2
#define RPMPVOTER3_	rpMultiprocessVoter3
#define RPMPVOTER4_	rpMultiprocessVoter4
#define RPMPVOTER5_	rpMultiprocessVoter5

#define RPMPOPTFINISH1_ rpMpOptimizeFinish1
#define RPMPOPTFINISH2_ rpMpOptimizeFinish2

#define RPMPCORRECTOR1_	rpMultiprocessCorrector1
#define RPMPCORRECTOR2_	rpMultiprocessCorrector2
#define RPMPCORRECTOR3_	rpMultiprocessCorrector3
#define RPMPCORRECTOR4_	rpMultiprocessCorrector4
#define RPMPCORRECTOR5_	rpMultiprocessCorrector5
#define RPMPCORRECTOR6_	rpMultiprocessCorrector6

#define RPMPRDEPVAR1_	rpMultiprocessReadDepVar1
#define RPMPRDEPVAR2_	rpMultiprocessReadDepVar2
#define RPMPRDEPVAR3_	rpMultiprocessReadDepVar3

#define RPMPCLOSEPIPE_	rpMultiprocessClosePipes

#define RPMPFINISHFLAGS1_	rpMultiprocessFinishFlags1
#define RPMPFINISHFLAGS2_	rpMultiprocessFinishFlags2

#define RPMPWTARGETVAR1_	rpMultiprocessWriteTargetVar1
#define RPMPWTARGETVAR2_	rpMultiprocessWriteTargetVar2
#define RPMPWTARGETVAR3_	rpMultiprocessWriteTargetVar3

#define RPMPWDEPVAR1_	rpMultiprocessWriteDepVar1
#define RPMPWDEPVAR2_	rpMultiprocessWriteDepVar2
#define RPMPWDEPVAR3_	rpMultiprocessWriteDepVar3
 


char rpMpVars[] = "\n\tpid_t pid;"
							"\n\tint pipe_fd_Voter[2];"
							"\n\tint pipe_fd_Voter2[2];"
							"\n\tchar k[3][50];"
							"\n\tchar chpid[3][12];"
							"\n\tint finish = 0;"
							"\n\tint process_num = Pre_Num_Voter + 1;"
							"\n\tint round_num = 0;"
							"\n\tint dep_process = 0;"
							"\n\tint kill_count = 0;"
							"\n\tint chdpid;"
							"\n\tint chdpid_i[3];"
							"\n\tint child_cnt = 0;"
							"\n\tint RedundantFlag = 0;"
							"\n\tint process_cnt = 0;"
							"\n\tint GotoFlag = 0;";

char rpMpWhile1[] = "\n\twhile (1) {";

char rpMpInit[] = "\n\t\tfinish = 0;"
								"\n\t\tprocess_num = Pre_Num_Voter + 1;"
								"\n\t\tround_num = 0;"
								"\n\t\tdep_process = 0;"
								"\n\t\tkill_count = 0;"
								"\n\t\tif (pipe(pipe_fd_Voter) == -1) {"
								"\n\t\t\tfprintf(stderr, \"Error: Unable to create pipe.\\n\");"
								"\n\t\t\texit(EXIT_FAILURE);"
								"\n\t\t}"
								"\n\t\tif (pipe(pipe_fd_Voter2) == -1) {"
								"\n\t\t\tfprintf(stderr, \"Error: Unable to create pipe.\\n\");"
								"\n\t\t\texit(EXIT_FAILURE);"
								"\n\t\t}"
								"\n\t\tif ((pid = fork()) < 0) {"
								"\n\t\t\tfprintf(stderr, \"Error: Unable to fork process.\\n\");"
								"\n\t\t\texit(EXIT_FAILURE);"
								"\n\t\t}";

char rpMultiprocess1[] = 	"\n\t\tfor (round_num = 0; finish == 0; round_num++) {"
													"\n\t\t\tif (pid > 0) {"
													"\n\t\t\t\tprintf(\"==================== Parent Process %d ====================\\n\", getpid());"
													"\n\t\t\t\tif (round_num == 0) {"
													"\n\t\t\t\t\tFORK:"
													"\n\t\t\t\t\tif (RedundantFlag == 0 && GotoFlag == 0) {"
													"\n\t\t\t\t\t\tfor (int num = 0; num < Pre_Num_Voter; num++) {"
													"\n\t\t\t\t\t\t\tif (pid > 0) {"
													"\n\t\t\t\t\t\t\t\tif ((pid = fork()) < 0) {"
													"\n\t\t\t\t\t\t\t\t\tfprintf(stderr, \"Error: Unable to fork process.\\n\");"
													"\n\t\t\t\t\t\t\t\t\texit(EXIT_FAILURE);"
													"\n\t\t\t\t\t\t\t\t}"
													"\n\t\t\t\t\t\t\t\tif (num == (Pre_Num_Voter - 1) && pid == 0)"
													"\n\t\t\t\t\t\t\t\t\tdep_process = 1;"
													"\n\t\t\t\t\t\t\t\tif (pid == 0) {"
													"\n\t\t\t\t\t\t\t\t\tclose(pipe_fd_Voter[0]);"
													"\n\t\t\t\t\t\t\t\t\tchdpid = getpid();"
													"\n\t\t\t\t\t\t\t\t\twrite(pipe_fd_Voter[1], &chdpid, sizeof(int));"
													"\n\t\t\t\t\t\t\t\t\tprintf(\"\\n\\t***Child Process:%4d\\n\", chdpid);"
													"\n\t\t\t\t\t\t\t\t} else if (pid > 0) {"
													"\n\t\t\t\t\t\t\t\t\tclose(pipe_fd_Voter[1]);"
													"\n\t\t\t\t\t\t\t\t\tread(pipe_fd_Voter[0], &chdpid_i[num], sizeof(int));"
													"\n\t\t\t\t\t\t\t\t\tprintf(\"\\n\\t---Child Process:%4d\\n\", chdpid_i[num]);"
													"\n\t\t\t\t\t\t\t\t\tmemset(k[num], '\\0', strlen(k[num]));"
													"\n\t\t\t\t\t\t\t\t\tmemset(chpid[num], '\\0', strlen(chpid[num]));"
													"\n\t\t\t\t\t\t\t\t\tstrcpy(k[num], \"kill -9 \");"
													"\n\t\t\t\t\t\t\t\t\tsprintf(chpid[num], \"%d\", chdpid_i[num]);"
													"\n\t\t\t\t\t\t\t\t\tstrcat(k[num], chpid[num]);"
													"\n\t\t\t\t\t\t\t\t}"
													"\n\t\t\t\t\t\t\t}"
													"\n\t\t\t\t\t\t}"
													"\n\t\t\t\t\t}"
													"\n\t\t\t\t\twhile ((Pre_Num_Voter + process_cnt) <= MaxForkTimes &&"
													"\n\t\t\t\t\t\t\t\t RedundantFlag == 1) {"
													"\n\t\t\t\t\t\tif (pid > 0) {"
													"\n\t\t\t\t\t\t\tif (pipe(pipe_fd_Voter) == -1) {"
													"\n\t\t\t\t\t\t\t\tfprintf(stderr, \"Error: Unable to create pipe.\\n\");"
													"\n\t\t\t\t\t\t\t\texit(EXIT_FAILURE);"
													"\n\t\t\t\t\t\t\t}"
													"\n\t\t\t\t\t\t\tpid = fork();"
													"\n\t\t\t\t\t\t\tchild_cnt++;"
													"\n\t\t\t\t\t\t\tif (pid == 0) {"
													"\n\t\t\t\t\t\t\t\tclose(pipe_fd_Voter[0]);"
													"\n\t\t\t\t\t\t\t\tchdpid = getpid();"
													"\n\t\t\t\t\t\t\t\twrite(pipe_fd_Voter[1], &chdpid, sizeof(int));"
													"\n\t\t\t\t\t\t\t\tprintf(\"\\n\\t\\33\\[1;31mNew Child Process be forked %d: %4d\\33\\[0m\\n\", child_cnt, chdpid);"
													"\n\t\t\t\t\t\t\t}"
													"\n\t\t\t\t\t\t\tGotoFlag = 0;"
													"\n\t\t\t\t\t\t\tbreak;"
													"\n\t\t\t\t\t\t}"
													"\n\t\t\t\t\t}"
													"\n\t\t\t\t}"
													"\n\t\t\t\tif (pid > 0) {"
													"\n\t\t\t\t\tprintf(\"  ==========> Parent Process ONLY at round_num %d <==========\\n\\n\", round_num);"
													"\n\t\t\t\t\tint time_delay = 0;"
													"\n\t\t\t\t\tfor (; finish != 1;) {"
													"\n\t\t\t\t\t\tsleep(1);"
													"\n\t\t\t\t\t\tint status;"
													"\n\t\t\t\t\t\tint w_return = waitpid(-1, &status, WNOHANG | WUNTRACED);"
													"\n\t\t\t\t\t\tif (w_return > 0) {"
													"\n\t\t\t\t\t\t\tif (WIFEXITED(status)) {"
													"\n\t\t\t\t\t\t\t\tprocess_num--;"
													"\n\t\t\t\t\t\t\t\tprintf(\"\\n\\t\\t\\t+++ process_num:%d\\n\\n\", process_num);"
													"\n\t\t\t\t\t\t\t\tif (process_num != Pre_Num_Voter) {"
													"\n\t\t\t\t\t\t\t\t\tif (RedundantFlag == 1) {"
													"\n\t\t\t\t\t\t\t\t\t\t// receiver";

char rpMultiprocessRecv1[] = 	"\n\t\t\t\t\t\t\t\t\t\treceiver_"; // + targetVar.siza()
char rpMultiprocessRecv2[] = 	"(pipe_fd_Voter2[0], process_num, &data_"; // + targetVar.size()
char rpMultiprocessRecv3[] = 	"[Pre_Num_Voter+process_cnt-1]."; // + tType
char rpMultiprocessRecv4[] = 	");";

char rpMultiprocess2[] = "\n\t\t\t\t\t\t\t\t\t} else if (RedundantFlag == 0) {"
									"\n\t\t\t\t\t\t\t\t\t\t// receiver";

char rpMultiprocessRecv5[] = 	"\n\t\t\t\t\t\t\t\t\t\treceiver_"; // + targetVar.size()
char rpMultiprocessRecv6[] = 	"(pipe_fd_Voter2[0], process_num, &data_"; // + targetVar.size()
char rpMultiprocessRecv7[] = 	"[Pre_Num_Voter-process_num-1]."; // + tType
char rpMultiprocessRecv8[] = 	");";

char rpMultiprocess3[] = 	"\n\t\t\t\t\t\t\t\t\t}"
													"\n\t\t\t\t\t\t\t\t}"
													"\n\t\t\t\t\t\t\t\tif (process_num == 0) {";

char rpMultiprocessVoterVars1[] = 	"\n\t\t\t\t\t\t\t\t\t"; // + targetType
char rpMultiprocessVoterVars2[] =		" v_result_"; // + targetVar.size()
char rpMultiprocessVoterVars3[] = 	";"
																		"\n\t\t\t\t\t\t\t\t\tint num_Voter_"; // + targetVar.size()
char rpMultiprocessVoterVars4[] = 	" = 0;";

char rpMpOptimizeCompare1[] = "\n\t\t\t\t\t\t\t\t\tif (( 0";

char rpMpOptimizeCompareVars1[] = "\n\t\t\t\t\t\t\t\t\t\t|| data_"; // + targetVar.size()
char rpMpOptimizeCompareVars2[] = "[0]."; // + tType
char rpMpOptimizeCompareVars3[] = " != data_"; // + targetVar.size()
char rpMpOptimizeCompareVars4[] = "[1]."; // + tType

char rpMpOptimizeCompare2[] = ") && RedundantFlag == 0) {"
													"\n\t\t\t\t\t\t\t\t\t\t\tprocess_num++;"
													"\n\t\t\t\t\t\t\t\t\t\t\tprocess_cnt++;"
													"\n\t\t\t\t\t\t\t\t\t\t\tRedundantFlag = 1;"
													"\n\t\t\t\t\t\t\t\t\t\t\tGotoFlag = 1;"
													"\n\t\t\t\t\t\t\t\t\t} else if ( 1";

char rpMpOptimizeCompareVars5[] = "\n\t\t\t\t\t\t\t\t\t\t&& data_"; // + targetVar.size()
char rpMpOptimizeCompareVars6[] = "[0]."; // + tType
char rpMpOptimizeCompareVars7[] = " == data_"; // + targetVar.size()
char rpMpOptimizeCompareVars8[] = "[1]."; // + tType

char rpMpOptimizeCompare3[] = ") {";

char rpMultiprocessCompareVoterVars1[] = 	"\n\t\t\t\t\t\t\t\t\t\t\tv_result_"; // + targetVar.size()
char rpMultiprocessCompareVoterVars2[] = 	" = data_"; // + targetVar.size()
char rpMultiprocessCompareVoterVars3[] = 	"[0]."; // + tType
char rpMultiprocessCompareVoterVars4[] = 	";"
																					"\n\t\t\t\t\t\t\t\t\t\t\tnum_Voter_"; // + targetVar.size()
char rpMultiprocessCompareVoterVars5[] = 	"++;";

char rpMpOptimizeCompare4[] = "\n\t\t\t\t\t\t\t\t\t}"
														"\n\t\t\t\t\t\t\t\t\tif (RedundantFlag == 1 && GotoFlag == 1) {"
														"\n\t\t\t\t\t\t\t\t\t\tgoto FORK;               "
														"\n\t\t\t\t\t\t\t\t\t}"
														"\n\t\t\t\t\t\t\t\t\tif (RedundantFlag == 1 && GotoFlag == 0) {"
														"\n\t\t\t\t\t\t\t\t\t\t// voter";

char rpMultiprocessVoter1[] = "\n\t\t\t\t\t\t\t\t\t\tvoter_"; // + targetType.size()
char rpMultiprocessVoter2[] = "(&num_Voter_"; // + targetVar.size()
char rpMultiprocessVoter3[] = ", process_cnt, &v_result_"; // + targetVar.size()
char rpMultiprocessVoter4[] = ", data_"; // + targetVar.size()
char rpMultiprocessVoter5[] = ");";

char rpMpOptimizeCompare5[] = "\n\t\t\t\t\t\t\t\t\t}"
														"\n\t\t\t\t\t\t\t\t\tif (RedundantFlag == 0";

char rpMpOptimizeFinish1[] = "\n\t\t\t\t\t\t\t\t\t\t&& num_Voter_"; // + targetVar.size()
char rpMpOptimizeFinish2[] = " >= (Pre_Num_Voter+process_cnt + 1) / 2";

char rpMpOptimizeCompare6[] = ") {";

char rpMultiprocessCorrector1[] = "\n\t\t\t\t\t\t\t\t\t\t// corrector";
char rpMultiprocessCorrector2[] = "\n\t\t\t\t\t\t\t\t\t\tcorrector_"; // + targetType.size()
char rpMultiprocessCorrector3[] = "(process_cnt, &v_result_"; // + targetVar.size()
char rpMultiprocessCorrector4[] = ", &"; // + targetVar
char rpMultiprocessCorrector5[] = ", data_"; // + targetType.size()
char rpMultiprocessCorrector6[] = ");";

char rpMultiprocessReadDepVar1[] = "\n\t\t\t\t\t\t\t\t\t\tread(pipe_fd_Voter[0], &"; // + depVar
char rpMultiprocessReadDepVar2[] = ", sizeof("; // + depVarType
char rpMultiprocessReadDepVar3[] = "));";

char rpMultiprocessClosePipes[] = "\n\t\t\t\t\t\t\t\t\t\tclose(pipe_fd_Voter[0]);"
																	"\n\t\t\t\t\t\t\t\t\t\tclose(pipe_fd_Voter[1]);"
																	"\n\t\t\t\t\t\t\t\t\t\tclose(pipe_fd_Voter2[0]);"
																	"\n\t\t\t\t\t\t\t\t\t\tclose(pipe_fd_Voter2[1]);";

char rpMultiprocessFinishFlags1[] = "\n\t\t\t\t\t\t\t\t\t\tprintf(\"FINISH\\n\\n\");"
																		"\n\t\t\t\t\t\t\t\t\t\tfinish = 1;";

char rpMpOptimizeCompare7[] = "\n\t\t\t\t\t\t\t\t\t} else if (RedundantFlag == 1";

char rpMultiprocessFinishFlags2[] = "\n\t\t\t\t\t\t\t\t\t\tRedundantFlag = 0;"
																		"\n\t\t\t\t\t\t\t\t\t\tGotoFlag = 0;"
																		"\n\t\t\t\t\t\t\t\t\t\tprintf(\"FINISH\\n\\n\");"
																		"\n\t\t\t\t\t\t\t\t\t\tfinish = 1;";

char rpMultiprocess4[] = 	"\n\t\t\t\t\t\t\t\t\t} else {"
													"\n\t\t\t\t\t\t\t\t\t\tprintf(\"\\33\\[1;31m \\n\\t-- There doesn't exist a majority voter -- \\33\\[0m \\n\\n\");"
													"\n\t\t\t\t\t\t\t\t\t\tprocess_num++;"
													"\n\t\t\t\t\t\t\t\t\t\tprocess_cnt++;"
													"\n\t\t\t\t\t\t\t\t\t\tRedundantFlag = 1;"
													"\n\t\t\t\t\t\t\t\t\t\tGotoFlag = 1;"
													"\n\t\t\t\t\t\t\t\t\t\tfinish = 1;"
													"\n\t\t\t\t\t\t\t\t\t\tdep_process = 0;"
													"\n\t\t\t\t\t\t\t\t\t}"
													"\n\t\t\t\t\t\t\t\t}"
													"\n\t\t\t\t\t\t\t\tbreak;"
													"\n\t\t\t\t\t\t\t} else if (process_num != Pre_Num_Voter + 1) {"
													"\n\t\t\t\t\t\t\t\tfor (int num = 0; num < Pre_Num_Voter; num++) {"
													"\n\t\t\t\t\t\t\t\t\tsystem(k[num]);"
													"\n\t\t\t\t\t\t\t\t\tprintf(\"\\t\\t\\t\\tEnd:%s\\n\", k[num]);"
													"\n\t\t\t\t\t\t\t\t}"
													"\n\t\t\t\t\t\t\t\tfinish = 1;"
													"\n\t\t\t\t\t\t\t\tbreak;"
													"\n\t\t\t\t\t\t\t}"
													"\n\t\t\t\t\t\t} else if (w_return < 0) {"
													"\n\t\t\t\t\t\t\tfor (int num = 0; num < Pre_Num_Voter; num++) {"
													"\n\t\t\t\t\t\t\t\tsystem(k[num]);"
													"\n\t\t\t\t\t\t\t\tprintf(\"\\t\\t\\t\\tEnd:%s\\n\", k[num]);"
													"\n\t\t\t\t\t\t\t}"
													"\n\t\t\t\t\t\t\tfinish = 1;"
													"\n\t\t\t\t\t\t\tprocess_num = Pre_Num_Voter;"
													"\n\t\t\t\t\t\t\tround_num = -1;"
													"\n\t\t\t\t\t\t\tdep_process = 0;"
													"\n\t\t\t\t\t\t\tbreak;"
													"\n\t\t\t\t\t\t}"
													"\n\t\t\t\t\t}"
													"\n\t\t\t\t}"
													"\n\t\t\t} else {"
													"\n\t\t\t\tprintf(\"------------>Child Process arrived: %4d\\n\", getpid());"
													"\n\t\t\t\tif (round_num != 0) {";

char rpMultiprocessWriteTargetVar1[] =	"\n\t\t\t\t\twrite(pipe_fd_Voter2[1], &"; // + targetVar
char rpMultiprocessWriteTargetVar2[] =	", sizeof("; // + targetType
char rpMultiprocessWriteTargetVar3[] = 	"));";

char rpMultiprocessWriteDepVar1[] =	"\n\t\t\t\t\twrite(pipe_fd_Voter[1], &"; // + depVar
char rpMultiprocessWriteDepVar2[] =	", sizeof("; // + depType
char rpMultiprocessWriteDepVar3[] = "));";
					
char rpMultiprocess5[] = 	"\n\t\t\t\t\tprintf(\"------------>Child Process done: %4d\\n\", getpid());"
													"\n\t\t\t\t}"
													"\n\t\t\t\tfinish = 1;"
													"\n\t\t\t\treturn 0;"
													"\n\t\t\t}"
													"\n\t\t}";

char rpMpWhile2[] = "\n\t}";							

#endif