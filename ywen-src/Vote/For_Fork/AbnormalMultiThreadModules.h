#ifndef ABNORMALMULTITHREADMODULES_H_
#define ABNORMALMULTITHREADMODULES_H_

#define ABMTVARS_	abMtVars

#define ABMULTITHREAD1_	abMultithread1
#define ABMULTITHREAD2_	abMultithread2
#define ABMULTITHREAD3_	abMultithread3

#define ABMTRECV1_	abMultithreadRecv1
#define ABMTRECV2_	abMultithreadRecv2
#define ABMTRECV3_	abMultithreadRecv3
#define ABMTRECV4_	abMultithreadRecv4
#define ABMTRECV5_	abMultithreadRecv5

#define ABMTWDEPVAR1_	abMultithreadWriteDepVar1
#define ABMTWDEPVAR2_	abMultithreadWriteDepVar2
#define ABMTWDEPVAR3_	abMultithreadWriteDepVar3
#define ABMTWDEPVAR4_	abMultithreadWriteDepVar4

#define ABMTVV1_	abMultithreadVoterVars1
#define ABMTVV2_	abMultithreadVoterVars2
#define ABMTVV3_	abMultithreadVoterVars3
#define ABMTVV4_	abMultithreadVoterVars4

#define ABMTOPTCMP1_	abMtOptimizeCompare1
#define ABMTOPTCMP2_	abMtOptimizeCompare2
#define ABMTOPTCMP3_	abMtOptimizeCompare3
#define ABMTOPTCMP4_	abMtOptimizeCompare4
#define ABMTOPTCMP5_	abMtOptimizeCompare5
#define ABMTOPTCMP6_	abMtOptimizeCompare6
#define ABMTOPTCMP7_	abMtOptimizeCompare7

#define ABMTOPTCMPV1_	abMtOptimizeCompareVars1
#define ABMTOPTCMPV2_	abMtOptimizeCompareVars2
#define ABMTOPTCMPV3_	abMtOptimizeCompareVars3
#define ABMTOPTCMPV4_	abMtOptimizeCompareVars4
#define ABMTOPTCMPV5_	abMtOptimizeCompareVars5
#define ABMTOPTCMPV6_	abMtOptimizeCompareVars6
#define ABMTOPTCMPV7_	abMtOptimizeCompareVars7
#define ABMTOPTCMPV8_	abMtOptimizeCompareVars8

#define ABMTCMPVV1_	abMultithreadCompareVoterVars1
#define ABMTCMPVV2_	abMultithreadCompareVoterVars2
#define ABMTCMPVV3_	abMultithreadCompareVoterVars3
#define ABMTCMPVV4_	abMultithreadCompareVoterVars4
#define ABMTCMPVV5_	abMultithreadCompareVoterVars5

#define ABMTVOTER1_	abMultithreadVoter1
#define ABMTVOTER2_	abMultithreadVoter2
#define ABMTVOTER3_	abMultithreadVoter3
#define ABMTVOTER4_	abMultithreadVoter4
#define ABMTVOTER5_	abMultithreadVoter5

#define ABMTOPTFINISH1_	abMtOptimizeFinish1
#define ABMTOPTFINISH2_	abMtOptimizeFinish2
#define ABMTOPTFINISH3_	abMtOptimizeFinish3
#define ABMTOPTFINISH4_	abMtOptimizeFinish4

#define ABMTCORRECTOR1_	abMultithreadCorrector1
#define ABMTCORRECTOR2_	abMultithreadCorrector2
#define ABMTCORRECTOR3_	abMultithreadCorrector3
#define ABMTCORRECTOR4_	abMultithreadCorrector4
#define ABMTCORRECTOR5_	abMultithreadCorrector5
#define ABMTCORRECTOR6_	abMultithreadCorrector6

#define ABMTRDEPVAR1_	abMultithreadReadDepVar1
#define ABMTRDEPVAR2_	abMultithreadReadDepVar2
#define ABMTRDEPVAR3_	abMultithreadReadDepVar3

#define ABMTCLOSEREAD_	abMultithreadCloseRead
#define ABMTCLOSEWRITE_	abMultithreadCloseWrite
#define ABMTCLOSEPIPE_	abMultithreadClosePipes

#define ABMTFINISHFLAGS1_	abMultithreadFinishFlags1
#define ABMTFINISHFLAGS2_	abMultithreadFinishFlags2

char abMtVars[] = "\n\tpid_t pid;"
									"\n\tint pipe_fd_Voter[2];"
									"\n\tchar k[50] = \"kill -9 \";"
									"\n\tchar chpid[12];"
									"\n\tint finish = 0;"
									"\n\tint respawn = 0;"
									"\n\tint child_cnt = 0;"
									"\n\tint process_cnt = 0;"
									"\n\tint RedundantFlag = 0;"
									"\n\tint GotoFlag = 0;"
									"\n\tint iterator = 0;"
									"\n\tint ThreadCtrl = 0;";

char abMultithread1[] = "\n\tfor (; finish != 1;) {"
												"\n\t\tif (pid > 0) {"
												"\n\t\t\tprintf(\"==================== Parent Process %d ====================\\n\", getpid());"
												"\n\t\t\tif (pipe(pipe_fd_Voter) == -1) {"
												"\n\t\t\t\tfprintf(stderr, \"Error: Unable to create pipe.\\n\");"
												"\n\t\t\t\texit(EXIT_FAILURE);"
												"\n\t\t\t}"												
												"\n\t\t\tif ((pid = fork()) < 0) {"
												"\n\t\t\t\tfprintf(stderr, \"Error: Unable to fork process.\\n\");"
												"\n\t\t\t\texit(EXIT_FAILURE);"
												"\n\t\t\t}"
												"\n\t\t\tint time_delay = 0;"
												"\n\t\t\tmemset(k, '\\0', strlen(k));"
												"\n\t\t\tmemset(chpid, '\\0', strlen(chpid));"
												"\n\t\t\tstrcpy(k, \"kill -9 \");"
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
												"\n\t\t\t\t\t\tbreak;"
												"\n\t\t\t\t\t} else {"
												"\n\t\t\t\t\t\trespawn = 0;"
												"\n\t\t\t\t\t}"
												"\n\t\t\t\t} else if (w_return > 0 && respawn != 1) {"
												"\n\t\t\t\t\tprintf(\"==================== Parent Process %d  done ====================\\n\", getpid());"
												"\n\t\t\t\t\tfinish = 1;"
												"\n\t\t\t\t\ttime_delay = 0;"
												"\n\t\t\t\t\tbreak;"
												"\n\t\t\t\t} else if (w_return < 0) {"
												"\n\t\t\t\t\tbreak;"
												"\n\t\t\t\t}"
												"\n\t\t\t}"
												"\n\t\t} else {"
												"\n\t\t\tprintf(\"------------>Child Process arrived: %4d\\n\", getpid());"
												"\n\t\t\tNEW_THREAD:"
												"\n\t\t\tif (RedundantFlag == 1 && GotoFlag == 1) {"
												"\n\t\t\t\tprintf(\"\\n\\t\\33\\[1;31mNew Thread be created\\33\\[0m\\n\");"
												"\n\t\t\t\tGotoFlag = 0;"
												"\n\t\t\t}"
												"\n\t\t\t#pragma omp parallel for if (RedundantFlag == 0) num_threads(2)"
												"\n\t\t\t{"
												"\n\t\t\t\tfor (int i_mt = 0; i_mt < Pre_Num_Voter + process_cnt; i_mt++) {"
												"\n\t\t\t\t\t#pragma omp critical"
												"\n\t\t\t\t\t{";

char abMultithreadRecv1[] = "\n\t\t\t\t\t\t// receive data";
char abMultithreadRecv2[] = "\n\t\t\t\t\t\tdata_"; // + targetVar.size()
char abMultithreadRecv3[] = "[iterator]."; // + tType
char abMultithreadRecv4[] = " = "; // + targetVar
char abMultithreadRecv5[] = ";";

char abMultithreadCloseRead[] = "\n\t\t\t\t\t\tclose(pipe_fd_Voter[0]);";

char abMultithreadWriteDepVar1[] = "\n\t\t\t\t\t\t// write dep variables";
char abMultithreadWriteDepVar2[] = "\n\t\t\t\t\t\twrite(pipe_fd_Voter[1], &"; // + depVar
char abMultithreadWriteDepVar3[] = ", sizeof("; // + depType
char abMultithreadWriteDepVar4[] = "));";

char abMultithread2[] = "\n\t\t\t\t\t\t#pragma omp atomic"
												"\n\t\t\t\t\t\titerator++;"
												"\n\t\t\t\t\t}"
												"\n\t\t\t\t}"
												"\n\t\t\t}";

char abMultithreadVoterVars1[] = 	"\n\t\t\t"; // + targetType
char abMultithreadVoterVars2[] =		" v_result_"; // + targetVar.size()
char abMultithreadVoterVars3[] = 	";"
																		"\n\t\t\tint num_Voter_"; // + targetVar.size()
char abMultithreadVoterVars4[] = 	" = 0;";


char abMtOptimizeCompare1[] = "\n\t\t\tif (( 0";

char abMtOptimizeCompareVars1[] = "\n\t\t\t\t|| data_"; // + targetVar.size()
char abMtOptimizeCompareVars2[] = "[0]."; // + tType
char abMtOptimizeCompareVars3[] = " != data_"; // + targetVar.size()
char abMtOptimizeCompareVars4[] = "[1]."; // + tType

char abMtOptimizeCompare2[] = ") && RedundantFlag == 0) {"
													"\n\t\t\t\tprocess_cnt = MaxForkTimes-Pre_Num_Voter;"
													"\n\t\t\t\tRedundantFlag = 1;"
													"\n\t\t\t\tGotoFlag = 1;"
													"\n\t\t\t\tThreadCtrl = 1;"
													"\n\t\t\t} else if ( 1";

char abMtOptimizeCompareVars5[] = "\n\t\t\t\t&& data_"; // + targetVar.size()
char abMtOptimizeCompareVars6[] = "[0]."; // + tType
char abMtOptimizeCompareVars7[] = " == data_"; // + targetVar.size()
char abMtOptimizeCompareVars8[] = "[1]."; // + tType

char abMtOptimizeCompare3[] = ") {";

char abMultithreadCompareVoterVars1[] = 	"\n\t\t\t\tv_result_"; // + targetVar.size()
char abMultithreadCompareVoterVars2[] = 	" = data_"; // + targetVar.size()
char abMultithreadCompareVoterVars3[] = 	"[0]."; // + tType
char abMultithreadCompareVoterVars4[] = 	";"
																					"\n\t\t\t\tnum_Voter_"; // + targetVar.size()
char abMultithreadCompareVoterVars5[] = 	"++;";


char abMtOptimizeCompare4[] = "\n\t\t\t}"
															"\n\t\t\tif (RedundantFlag == 1 && GotoFlag == 1) {"
															"\n\t\t\t\tgoto NEW_THREAD;               "
															"\n\t\t\t}"
															"\n\t\t\tif (RedundantFlag == 1 && GotoFlag == 0) {"
															"\n\t\t\t\t// voter";

char abMultithreadVoter1[] = "\n\t\t\t\tvoter_"; // + targetType.size()
char abMultithreadVoter2[] = "(&num_Voter_"; // + targetVar.size()
char abMultithreadVoter3[] = ", process_cnt, &v_result_"; // + targetVar.size()
char abMultithreadVoter4[] = ", data_"; // + targetVar.size()
char abMultithreadVoter5[] = ");";

char abMtOptimizeCompare5[] = "\n\t\t\t}"
															"\n\t\t\tif (RedundantFlag == 0";

char abMtOptimizeFinish1[] = "\n\t\t\t\t&& num_Voter_"; // + targetVar.size()
char abMtOptimizeFinish2[] = " >= 1";

char abMtOptimizeCompare6[] = ") {";

char abMultithreadCorrector1[] = "\n\t\t\t\t\t// corrector";
char abMultithreadCorrector2[] = "\n\t\t\t\t\tcorrector_"; // + targetType.size()
char abMultithreadCorrector3[] = "(process_cnt, &v_result_"; // + targetVar.size()
char abMultithreadCorrector4[] = ", &"; // + targetVar
char abMultithreadCorrector5[] = ", data_"; // + targetType.size()
char abMultithreadCorrector6[] = ");";

char abMultithreadCloseWrite[] = 	"\n\t\t\t\t\tclose(pipe_fd_Voter[1]);";

char abMultithreadReadDepVar1[] = "\n\t\t\t\t\tread(pipe_fd_Voter[0], &"; // + depVar
char abMultithreadReadDepVar2[] = ", sizeof("; // + depVarType
char abMultithreadReadDepVar3[] = "));";

char abMultithreadClosePipes[] = "\n\t\t\t\t\tclose(pipe_fd_Voter[0]);"
																	"\n\t\t\t\t\tclose(pipe_fd_Voter[1]);";
																	
char abMultithreadFinishFlags1[] = "\n\t\t\t\t\tprintf(\"FINISH\\n\");"
																		"\n\t\t\t\t\tfinish = 1;"
																		"\n\t\t\t\t\trespawn = 0;";

char abMtOptimizeCompare7[] = "\n\t\t\t} else if (RedundantFlag == 1";

char abMtOptimizeFinish3[] = "\n\t\t\t\t&& num_Voter_"; // + targetVar.size()
char abMtOptimizeFinish4[] = " >= (Pre_Num_Voter+process_cnt+1) / 2";

char abMultithreadFinishFlags2[] = 	"\n\t\t\t\t\tprintf(\"FINISH\\n\");"
																		"\n\t\t\t\t\tRedundantFlag = 0;"
																		"\n\t\t\t\t\tGotoFlag = 0;"
																		"\n\t\t\t\t\tprocess_cnt = 0;"
																		"\n\t\t\t\t\tThreadCtrl = 0;"
																		"\n\t\t\t\t\tfinish = 1;"
																		"\n\t\t\t\t\trespawn = 0;";

char abMultithread3[] = "\n\t\t\t} else {"
												"\n\t\t\t\tprintf(\"\\33\\[1;31m \\n\\t -- There doesn't exist a majority voter -- \\33\\[0m \\n\\n\");"
												"\n\t\t\t\tbreak;"
												"\n\t\t\t}"
												"\n\t\t\tprintf(\"------------>Child Process done: %4d\\n\", getpid());"
												"\n\t\t\tfinish = 1;"
												"\n\t\t\texit(EXIT_SUCCESS);"
												"\n\t\t}"
												"\n\t}";

#endif