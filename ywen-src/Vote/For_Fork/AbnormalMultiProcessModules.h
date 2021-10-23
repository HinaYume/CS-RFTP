#ifndef ABNORMALMULTIPROCESSMODULES_H_
#define ABNORMALMULTIPROCESSMODULES_H_

// Multiprocess
#define ABMPVARS_ 		abMpVars
#define ABMPINIT_ 		abMpInit

#define ABMULTIPROCESS1_ abMultiprocess1
#define ABMULTIPROCESS2_ abMultiprocess2
#define ABMULTIPROCESS3_ abMultiprocess3
#define ABMULTIPROCESS4_ abMultiprocess4
#define ABMULTIPROCESS5_ abMultiprocess5

#define ABMPRECV1_ abMultiprocessRecv1
#define ABMPRECV2_ abMultiprocessRecv2
#define ABMPRECV3_ abMultiprocessRecv3
#define ABMPRECV4_ abMultiprocessRecv4
#define ABMPRECV5_ abMultiprocessRecv5
#define ABMPRECV6_ abMultiprocessRecv6
#define ABMPRECV7_ abMultiprocessRecv7
#define ABMPRECV8_ abMultiprocessRecv8

#define ABMPVV1_ abMultiprocessVoterVars1
#define ABMPVV2_ abMultiprocessVoterVars2
#define ABMPVV3_ abMultiprocessVoterVars3
#define ABMPVV4_ abMultiprocessVoterVars4

#define ABMPOPTCMP1_ abMpOptimizeCompare1
#define ABMPOPTCMP2_ abMpOptimizeCompare2
#define ABMPOPTCMP3_ abMpOptimizeCompare3
#define ABMPOPTCMP4_ abMpOptimizeCompare4
#define ABMPOPTCMP5_ abMpOptimizeCompare5
#define ABMPOPTCMP6_ abMpOptimizeCompare6
#define ABMPOPTCMP7_ abMpOptimizeCompare7

#define ABMPOPTCMPV1_ abMpOptimizeCompareVars1
#define ABMPOPTCMPV2_ abMpOptimizeCompareVars2
#define ABMPOPTCMPV3_ abMpOptimizeCompareVars3
#define ABMPOPTCMPV4_ abMpOptimizeCompareVars4
#define ABMPOPTCMPV5_ abMpOptimizeCompareVars5
#define ABMPOPTCMPV6_ abMpOptimizeCompareVars6
#define ABMPOPTCMPV7_ abMpOptimizeCompareVars7
#define ABMPOPTCMPV8_ abMpOptimizeCompareVars8

#define ABMPCMPVV1_ abMultiprocessCompareVoterVars1
#define ABMPCMPVV2_ abMultiprocessCompareVoterVars2
#define ABMPCMPVV3_ abMultiprocessCompareVoterVars3
#define ABMPCMPVV4_ abMultiprocessCompareVoterVars4
#define ABMPCMPVV5_ abMultiprocessCompareVoterVars5

#define ABMPVOTER1_ abMultiprocessVoter1
#define ABMPVOTER2_ abMultiprocessVoter2
#define ABMPVOTER3_ abMultiprocessVoter3
#define ABMPVOTER4_ abMultiprocessVoter4
#define ABMPVOTER5_ abMultiprocessVoter5

#define ABMPOPTFINISH1_ abMpOptimizeFinish1
#define ABMPOPTFINISH2_ abMpOptimizeFinish2

#define ABMPCORRECTOR1_ abMultiprocessCorrector1
#define ABMPCORRECTOR2_ abMultiprocessCorrector2
#define ABMPCORRECTOR3_ abMultiprocessCorrector3
#define ABMPCORRECTOR4_ abMultiprocessCorrector4
#define ABMPCORRECTOR5_ abMultiprocessCorrector5
#define ABMPCORRECTOR6_ abMultiprocessCorrector6

#define ABMPRDEPVAR1_ abMultiprocessReadDepVar1
#define ABMPRDEPVAR2_ abMultiprocessReadDepVar2
#define ABMPRDEPVAR3_ abMultiprocessReadDepVar3

#define ABMPCLOSEPIPE_ abMultiprocessClosePipes

#define ABMPFINISHFLAGS1_ abMultiprocessFinishFlags1
#define ABMPFINISHFLAGS2_ abMultiprocessFinishFlags2

#define ABMPWTARGETVAR1_ abMultiprocessWriteTargetVar1
#define ABMPWTARGETVAR2_ abMultiprocessWriteTargetVar2
#define ABMPWTARGETVAR3_ abMultiprocessWriteTargetVar3

#define ABMPWDEPVAR1_ abMultiprocessWriteDepVar1
#define ABMPWDEPVAR2_ abMultiprocessWriteDepVar2
#define ABMPWDEPVAR3_ abMultiprocessWriteDepVar3

char abMpVars[] = "\n\tpid_t pid;"
								"\n\tint pipe_fd_Voter[2];"
								"\n\tint pipe_fd_Voter2[2];"
								"\n\tchar k[3][50];"
								"\n\tchar chpid[3][12];"
								"\n\tint finish = 0;"
								"\n\tint respawn = 0;"
								"\n\tint process_num = Pre_Num_Voter + 1;"
								"\n\tint wait_chd;"
								"\n\tint round_num = 0;"
								"\n\tint dep_process = 0;"
								"\n\tint kill_count = 0;"
								"\n\tint chdpid;"
								"\n\tint child_cnt = 0;"
								"\n\tint RedundantFlag = 0;"
								"\n\tint process_cnt = 0;"
								"\n\tint GotoFlag = 0;";

char abMpInit[] = 	"\n\tif (pipe(pipe_fd_Voter) == -1) {"
										"\n\t\tfprintf(stderr, \"Error: Unable to create pipe.\\n\");"
										"\n\t\texit(EXIT_FAILURE);"
										"\n\t}"
										"\n\tif (pipe(pipe_fd_Voter2) == -1) {"
										"\n\t\tfprintf(stderr, \"Error: Unable to create pipe.\\n\");"
										"\n\t\texit(EXIT_FAILURE);"
										"\n\t}"
										"\n\tif ((pid = fork()) < 0) {"
										"\n\t\tfprintf(stderr, \"Error: Unable to fork process.\\n\");"
										"\n\t\texit(EXIT_FAILURE);"
										"\n\t}";

char abMultiprocess1[] = 	"\n\tfor (round_num = 0; finish == 0; round_num++) {"
													"\n\t\tif (pid > 0) {"
													"\n\t\t\tprintf(\"==================== Parent Process %d ====================\\n\", getpid());"
													"\n\t\t\tif (round_num == 0) {"
													"\n\t\t\t\tFORK:"
													"\n\t\t\t\tif (RedundantFlag == 0 && GotoFlag == 0) {"
													"\n\t\t\t\t\tfor (int num = 0; num < Pre_Num_Voter; num++) { "
													"\n\t\t\t\t\t\tif (pid > 0) {"
													"\n\t\t\t\t\t\t\tif (pipe(pipe_fd_Voter) == -1) {"
													"\n\t\t\t\t\t\t\t\tfprintf(stderr, \"Error: Unable to create pipe.\\n\");"
													"\n\t\t\t\t\t\t\t\texit(EXIT_FAILURE);"
													"\n\t\t\t\t\t\t\t}"
													"\n\t\t\t\t\t\t\tpid = fork(); "
													"\n\t\t\t\t\t\t\tchild_cnt++;"
													"\n\t\t\t\t\t\t\tif (num == (Pre_Num_Voter - 1) && pid == 0)"
													"\n\t\t\t\t\t\t\t\tdep_process = 1;"
													"\n\t\t\t\t\t\t\tif (pid == 0) {"
													"\n\t\t\t\t\t\t\t\tclose(pipe_fd_Voter[0]);"
													"\n\t\t\t\t\t\t\t\tchdpid = getpid();"
													"\n\t\t\t\t\t\t\t\twrite(pipe_fd_Voter[1], &chdpid, sizeof(int));"
													"\n\t\t\t\t\t\t\t\tprintf(\"\\n\\t***Child Process %d: %4d\\n\", child_cnt, chdpid);"
													"\n\t\t\t\t\t\t\t} else if (pid > 0) {"
													"\n\t\t\t\t\t\t\t\tclose(pipe_fd_Voter[1]);"
													"\n\t\t\t\t\t\t\t\tread(pipe_fd_Voter[0], &chdpid, sizeof(int));"
													"\n\t\t\t\t\t\t\t\tprintf(\"\\n\\t---Child Process %d: %4d\\n\", child_cnt, chdpid);"
													"\n\t\t\t\t\t\t\t\tmemset(k[num], '\\0', strlen(k[num]));"
													"\n\t\t\t\t\t\t\t\tmemset(chpid[num], '\\0', strlen(chpid[num]));"
													"\n\t\t\t\t\t\t\t\tstrcpy(k[num], \"kill -9 \");"
													"\n\t\t\t\t\t\t\t\tsprintf(chpid[num], \"%d\", chdpid);"
													"\n\t\t\t\t\t\t\t\tstrcat(k[num], chpid[num]);"
													"\n\t\t\t\t\t\t\t}"
													"\n\t\t\t\t\t\t}"
													"\n\t\t\t\t\t}"
													"\n\t\t\t\t}"
													"\n\t\t\t\twhile ((Pre_Num_Voter+process_cnt) <= MaxForkTimes && RedundantFlag == 1) {"
													"\n\t\t\t\t\tif (pid > 0) {"
													"\n\t\t\t\t\t\tif (pipe(pipe_fd_Voter) == -1) {"
													"\n\t\t\t\t\t\t\tfprintf(stderr, \"Error: Unable to create pipe.\\n\");"
													"\n\t\t\t\t\t\t\texit(EXIT_FAILURE);"
													"\n\t\t\t\t\t\t}"
													"\n\t\t\t\t\t\tpid = fork();"
													"\n\t\t\t\t\t\tchild_cnt++;"
													"\n\t\t\t\t\t\tif (pid == 0) {"
													"\n\t\t\t\t\t\t\tclose(pipe_fd_Voter[0]);"
													"\n\t\t\t\t\t\t\tchdpid = getpid();"
													"\n\t\t\t\t\t\t\twrite(pipe_fd_Voter[1], &chdpid, sizeof(int));"
													"\n\t\t\t\t\t\t\tprintf(\"\\n\\t\\33\\[1;31mNew Child Process be forked %d: %4d\\33\\[0m\\n\", child_cnt, chdpid);"
													"\n\t\t\t\t\t\t}"
													"\n\t\t\t\t\t\tGotoFlag = 0;"
													"\n\t\t\t\t\t\tbreak;"
													"\n\t\t\t\t\t}"
													"\n\t\t\t\t}"
													"\n\t\t\t}"
													"\n\t\t\tif (pid > 0) {"
													"\n\t\t\t\tprintf(\"  ==========> Parent Process ONLY at round_num %d <==========\\n\\n\", round_num);"
													"\n\t\t\t\tint time_delay = 0;"
													"\n\t\t\t\tfor (; finish != 1;) {"
													"\n\t\t\t\t\tint w_return = waitpid(-1, NULL, WNOHANG | WUNTRACED);"
													"\n\t\t\t\t\tif (w_return == 0) {"
													"\n\t\t\t\t\t\tsleep(1);"
													"\n\t\t\t\t\t\ttime_delay++;"
													"\n\t\t\t\t\t\tprintf(\"time_delay++ = %d\\n\", time_delay);"
													"\n\t\t\t\t\t\tif (time_delay == 5) {"
													"\n\t\t\t\t\t\t\tprintf(\"\\t+++time_delay = %d\\n\", time_delay);"
													"\n\t\t\t\t\t\t\ttime_delay = 0;"
													"\n\t\t\t\t\t\t\tfor (int num = 0; num < Pre_Num_Voter; num++) {"
													"\n\t\t\t\t\t\t\t\tsystem(k[num]);"
													"\n\t\t\t\t\t\t\t\tprintf(\"\\t\\t\\t\\tEnd:%s\\n\", k[num]);"
													"\n\t\t\t\t\t\t\t}"
													"\n\t\t\t\t\t\t\tkill_count = 0;"
													"\n\t\t\t\t\t\t\trespawn = 1;"
													"\n\t\t\t\t\t\t\tprocess_num = Pre_Num_Voter;"
													"\n\t\t\t\t\t\t\tround_num = -1;"
													"\n\t\t\t\t\t\t\tdep_process = 0;"
													"\n\t\t\t\t\t\t\tbreak;"
													"\n\t\t\t\t\t\t} else {"
													"\n\t\t\t\t\t\t\trespawn = 0;"
													"\n\t\t\t\t\t\t}"
													"\n\t\t\t\t\t} else if (w_return > 0 && respawn != 1) {"
													"\n\t\t\t\t\t\tprocess_num--;         "
													"\n\t\t\t\t\t\tif (process_num != Pre_Num_Voter) {"
													"\n\t\t\t\t\t\t\tif (RedundantFlag == 1) {"
													"\n\t\t\t\t\t\t\t\t// receiver";

char abMultiprocessRecv1[] = 	"\n\t\t\t\t\t\t\t\treceiver_"; // + targetVar.siza()
char abMultiprocessRecv2[] = 	"(pipe_fd_Voter2[0], process_num, &data_"; // + targetVar.size()
char abMultiprocessRecv3[] = 	"[Pre_Num_Voter+process_cnt-1]."; // + tType
char abMultiprocessRecv4[] = 	");";

char abMultiprocess2[] = 	"\n\t\t\t\t\t\t\t} else if (RedundantFlag == 0) {"
													"\n\t\t\t\t\t\t\t\t// receiver";

char abMultiprocessRecv5[] = 	"\n\t\t\t\t\t\t\t\treceiver_"; // + targetVar.size()
char abMultiprocessRecv6[] = 	"(pipe_fd_Voter2[0], process_num, &data_"; // + targetVar.size()
char abMultiprocessRecv7[] = 	"[Pre_Num_Voter-process_num-1]."; // + tType
char abMultiprocessRecv8[] = 	");";

char abMultiprocess3[] = 	"\n\t\t\t\t\t\t\t}"
													"\n\t\t\t\t\t\t}"
													"\n\t\t\t\t\t\ttime_delay = 0;"
													"\n\t\t\t\t\t\tif (process_num == 0) {";

char abMultiprocessVoterVars1[] = 	"\n\t\t\t\t\t\t\t"; // + targetType
char abMultiprocessVoterVars2[] =		" v_result_"; // + targetVar.size()
char abMultiprocessVoterVars3[] = 	";"
																		"\n\t\t\t\t\t\t\tint num_Voter_"; // + targetVar.size()
char abMultiprocessVoterVars4[] = 	" = 0;";

char abMpOptimizeCompare1[] = "\n\t\t\t\t\t\t\tif (( 0";

char abMpOptimizeCompareVars1[] = "\n\t\t\t\t\t\t\t\t|| data_"; // + targetVar.size()
char abMpOptimizeCompareVars2[] = "[0]."; // + tType
char abMpOptimizeCompareVars3[] = " != data_"; // + targetVar.size()
char abMpOptimizeCompareVars4[] = "[1]."; // + tType

char abMpOptimizeCompare2[] = ") && RedundantFlag == 0) {"
													"\n\t\t\t\t\t\t\t\tprocess_num++;"
													"\n\t\t\t\t\t\t\t\tprocess_cnt++;"
													"\n\t\t\t\t\t\t\t\tRedundantFlag = 1;"
													"\n\t\t\t\t\t\t\t\tGotoFlag = 1;"
													"\n\t\t\t\t\t\t\t} else if ( 1";

char abMpOptimizeCompareVars5[] = "\n\t\t\t\t\t\t\t\t&& data_"; // + targetVar.size()
char abMpOptimizeCompareVars6[] = "[0]."; // + tType
char abMpOptimizeCompareVars7[] = " == data_"; // + targetVar.size()
char abMpOptimizeCompareVars8[] = "[1]."; // + tType

char abMpOptimizeCompare3[] = ") {";

char abMultiprocessCompareVoterVars1[] = 	"\n\t\t\t\t\t\t\t\tv_result_"; // + targetVar.size()
char abMultiprocessCompareVoterVars2[] = 	" = data_"; // + targetVar.size()
char abMultiprocessCompareVoterVars3[] = 	"[0]."; // + tType
char abMultiprocessCompareVoterVars4[] = 	";"
																					"\n\t\t\t\t\t\t\t\tnum_Voter_"; // + targetVar.size()
char abMultiprocessCompareVoterVars5[] = 	"++;";

char abMpOptimizeCompare4[] = "\n\t\t\t\t\t\t\t}"
															"\n\t\t\t\t\t\t\tif (RedundantFlag == 1 && GotoFlag == 1) {"
															"\n\t\t\t\t\t\t\t\tgoto FORK;               "
															"\n\t\t\t\t\t\t\t}"
															"\n\t\t\t\t\t\t\tif (RedundantFlag == 1 && GotoFlag == 0) {"
															"\n\t\t\t\t\t\t\t\t// voter";

char abMultiprocessVoter1[] = "\n\t\t\t\t\t\t\t\tvoter_"; // + targetType.size()
char abMultiprocessVoter2[] = "(&num_Voter_"; // + targetVar.size()
char abMultiprocessVoter3[] = ", process_cnt, &v_result_"; // + targetVar.size()
char abMultiprocessVoter4[] = ", data_"; // + targetVar.size()
char abMultiprocessVoter5[] = ");";

char abMpOptimizeCompare5[] = "\n\t\t\t\t\t\t\t}"
															"\n\t\t\t\t\t\t\tif (RedundantFlag == 0";

char abMpOptimizeFinish1[] = "\n\t\t\t\t\t\t\t\t&& num_Voter_"; // + targetVar.size()
char abMpOptimizeFinish2[] = " >= (Pre_Num_Voter+process_cnt + 1) / 2";

char abMpOptimizeCompare6[] = ") {";

char abMultiprocessCorrector1[] = "\n\t\t\t\t\t\t\t\t// corrector";
char abMultiprocessCorrector2[] = "\n\t\t\t\t\t\t\t\tcorrector_"; // + targetType.size()
char abMultiprocessCorrector3[] = "(process_cnt, &v_result_"; // + targetVar.size()
char abMultiprocessCorrector4[] = ", &"; // + targetVar
char abMultiprocessCorrector5[] = ", data_"; // + targetType.size()
char abMultiprocessCorrector6[] = ");";

char abMultiprocessReadDepVar1[] = "\n\t\t\t\t\t\t\t\tread(pipe_fd_Voter[0], &"; // + depVar
char abMultiprocessReadDepVar2[] = ", sizeof("; // + depVarType
char abMultiprocessReadDepVar3[] = "));";

char abMultiprocessClosePipes[] = "\n\t\t\t\t\t\t\t\tclose(pipe_fd_Voter[0]);"
																	"\n\t\t\t\t\t\t\t\tclose(pipe_fd_Voter[1]);"
																	"\n\t\t\t\t\t\t\t\tclose(pipe_fd_Voter2[0]);"
																	"\n\t\t\t\t\t\t\t\tclose(pipe_fd_Voter2[1]);";
																	
char abMultiprocessFinishFlags1[] = "\n\t\t\t\t\t\t\t\tprintf(\"FINISH\\n\");"
																		"\n\t\t\t\t\t\t\t\tfinish = 1;"
																		"\n\t\t\t\t\t\t\t\trespawn = 0;";

char abMpOptimizeCompare7[] = "\n\t\t\t\t\t\t\t} else if (RedundantFlag == 1";

char abMultiprocessFinishFlags2[] = "\n\t\t\t\t\t\t\t\tprintf(\"FINISH\\n\");"
																		"\n\t\t\t\t\t\t\t\tRedundantFlag = 0;"
																		"\n\t\t\t\t\t\t\t\tGotoFlag = 0;"
																		"\n\t\t\t\t\t\t\t\tfinish = 1;"
																		"\n\t\t\t\t\t\t\t\trespawn = 0;";

char abMultiprocess4[] = 	"\n\t\t\t\t\t\t\t} else {"
													"\n\t\t\t\t\t\t\t\tprintf(\"\\33\\[1;31m \\n\\t-- There doesn't exist a majority voter -- \\33\\[0m \\n\\n\");"
													"\n\t\t\t\t\t\t\t\tprocess_num++;"
													"\n\t\t\t\t\t\t\t\tprocess_cnt++;"
													"\n\t\t\t\t\t\t\t\tRedundantFlag = 1;"
													"\n\t\t\t\t\t\t\t\tGotoFlag = 1;"
													"\n\t\t\t\t\t\t\t\tround_num = -1;"
													"\n\t\t\t\t\t\t\t\tdep_process = 0;"
													"\n\t\t\t\t\t\t\t\ttime_delay = 0;"
													"\n\t\t\t\t\t\t\t\trespawn = 0;"
													"\n\t\t\t\t\t\t\t}"
													"\n\t\t\t\t\t\t}"
													"\n\t\t\t\t\t\tbreak;"
													"\n\t\t\t\t\t} else if (w_return > 0 && respawn == 1) {"
													"\n\t\t\t\t\t\tkill_count += 1;"
													"\n\t\t\t\t\t\tprintf(\"\\n\\tkill_count:%d\\n\", kill_count);"
													"\n\t\t\t\t\t\tif (kill_count == Pre_Num_Voter) {"
													"\n\t\t\t\t\t\t\ttime_delay = 0;"
													"\n\t\t\t\t\t\t\trespawn = 0;"
													"\n\t\t\t\t\t\t}"
													"\n\t\t\t\t\t} else if (w_return < 0) {"
													"\n\t\t\t\t\t\tfinish = 1;"
													"\n\t\t\t\t\t\tprocess_num = Pre_Num_Voter;"
													"\n\t\t\t\t\t\tround_num = -1;"
													"\n\t\t\t\t\t\tdep_process = 0;"
													"\n\t\t\t\t\t\ttime_delay = 0;"
													"\n\t\t\t\t\t\trespawn = 0;"
													"\n\t\t\t\t\t\tbreak;"
													"\n\t\t\t\t\t}"
													"\n\t\t\t\t}"
													"\n\t\t\t}"
													"\n\t\t} else {"
													"\n\t\t\tprintf(\"------------>Child Process arrived: %4d\\n\", getpid());"
													"\n\t\t\tif (round_num != 0) {";

char abMultiprocessWriteTargetVar1[] = 	"\n\t\t\t\twrite(pipe_fd_Voter2[1], &"; // + targetVar
char abMultiprocessWriteTargetVar2[] = 	", sizeof("; // + targetType
char abMultiprocessWriteTargetVar3[] = 	"));";


char abMultiprocessWriteDepVar1[] = "\n\t\t\t\twrite(pipe_fd_Voter[1], &"; // + depVar
char abMultiprocessWriteDepVar2[] = ", sizeof("; // + depType
char abMultiprocessWriteDepVar3[] = "));";

char abMultiprocess5[] = "\n\t\t\t\tprintf(\"------------>Child Process done: %4d\\n\", getpid());"
										"\n\t\t\t}"
										"\n\t\t\tfinish = 1;"
										"\n\t\t\texit(EXIT_SUCCESS);"
										"\n\t\t}"
										"\n\t}";


#endif