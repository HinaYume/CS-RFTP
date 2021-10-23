#ifndef REPEATMULTITHREADMODULES_H_
#define REPEATMULTITHREADMODULES_H_

#define RPMTVARS_	rpMtVars
#define RPMTWHILE1_	rpMtWhile1
#define RPMTWHILE2_	rpMtWhile2

#define RPMULTITHREAD1_	rpMultithread1
#define RPMULTITHREAD2_	rpMultithread2
#define RPMULTITHREAD3_	rpMultithread3

#define RPMTRECV1_	rpMultithreadRecv1
#define RPMTRECV2_	rpMultithreadRecv2
#define RPMTRECV3_	rpMultithreadRecv3
#define RPMTRECV4_	rpMultithreadRecv4
#define RPMTRECV5_	rpMultithreadRecv5

#define RPMTWDEPVAR1_	rpMultithreadWriteDepVar1
#define RPMTWDEPVAR2_	rpMultithreadWriteDepVar2
#define RPMTWDEPVAR3_	rpMultithreadWriteDepVar3
#define RPMTWDEPVAR4_	rpMultithreadWriteDepVar4

#define RPMTVV1_	rpMultithreadVoterVars1
#define RPMTVV2_	rpMultithreadVoterVars2
#define RPMTVV3_	rpMultithreadVoterVars3
#define RPMTVV4_	rpMultithreadVoterVars4

#define RPMTOPTCMP1_	rpMtOptimizeCompare1
#define RPMTOPTCMP2_	rpMtOptimizeCompare2
#define RPMTOPTCMP3_	rpMtOptimizeCompare3
#define RPMTOPTCMP4_	rpMtOptimizeCompare4
#define RPMTOPTCMP5_	rpMtOptimizeCompare5
#define RPMTOPTCMP6_	rpMtOptimizeCompare6
#define RPMTOPTCMP7_	rpMtOptimizeCompare7

#define RPMTOPTCMPV1_	rpMtOptimizeCompareVars1
#define RPMTOPTCMPV2_	rpMtOptimizeCompareVars2
#define RPMTOPTCMPV3_	rpMtOptimizeCompareVars3
#define RPMTOPTCMPV4_	rpMtOptimizeCompareVars4
#define RPMTOPTCMPV5_	rpMtOptimizeCompareVars5
#define RPMTOPTCMPV6_	rpMtOptimizeCompareVars6
#define RPMTOPTCMPV7_	rpMtOptimizeCompareVars7
#define RPMTOPTCMPV8_	rpMtOptimizeCompareVars8

#define RPMTCMPVV1_	rpMultithreadCompareVoterVars1
#define RPMTCMPVV2_	rpMultithreadCompareVoterVars2
#define RPMTCMPVV3_	rpMultithreadCompareVoterVars3
#define RPMTCMPVV4_	rpMultithreadCompareVoterVars4
#define RPMTCMPVV5_	rpMultithreadCompareVoterVars5

#define RPMTVOTER1_	rpMultithreadVoter1
#define RPMTVOTER2_	rpMultithreadVoter2
#define RPMTVOTER3_	rpMultithreadVoter3
#define RPMTVOTER4_	rpMultithreadVoter4
#define RPMTVOTER5_	rpMultithreadVoter5

#define RPMTOPTFINISH1_	rpMtOptimizeFinish1
#define RPMTOPTFINISH2_	rpMtOptimizeFinish2
#define RPMTOPTFINISH3_	rpMtOptimizeFinish3
#define RPMTOPTFINISH4_	rpMtOptimizeFinish4

#define RPMTCORRECTOR1_	rpMultithreadCorrector1
#define RPMTCORRECTOR2_	rpMultithreadCorrector2
#define RPMTCORRECTOR3_	rpMultithreadCorrector3
#define RPMTCORRECTOR4_	rpMultithreadCorrector4
#define RPMTCORRECTOR5_	rpMultithreadCorrector5
#define RPMTCORRECTOR6_	rpMultithreadCorrector6

#define RPMTRDEPVAR1_	rpMultithreadReadDepVar1
#define RPMTRDEPVAR2_	rpMultithreadReadDepVar2
#define RPMTRDEPVAR3_	rpMultithreadReadDepVar3

#define RPMTCLOSEREAD_	rpMultithreadCloseRead
#define RPMTCLOSEWRITE_	rpMultithreadCloseWrite
#define RPMTCLOSEPIPE_	rpMultithreadClosePipes

#define RPMTFINISHFLAGS1_	rpMultithreadFinishFlags1
#define RPMTFINISHFLAGS2_	rpMultithreadFinishFlags2

char rpMtVars[] = "\n\tpid_t pid;"
									"\n\tint pipe_fd_Voter[2];"
									"\n\tchar k[50] = \"kill -9 \";"
									"\n\tchar chpid[12];"
									"\n\tint finish = 0;"
									"\n\tint result;"
									"\n\tint process_cnt = 0;"
									"\n\tint RedundantFlag = 0;"
									"\n\tint GotoFlag = 0;"
									"\n\tint iterator = 0;"
									"\n\tint ThreadCtrl = 0;";

char rpMtWhile1[] = "\n\twhile (1) {";

char rpMultithread1[] = "\n\t\tfinish = 0;"
												"\n\t\twhile (finish != 1) {"
												"\n\t\t\tint chdpid;"
												"\n\t\t\tif (pipe(pipe_fd_Voter) == -1) {"
												"\n\t\t\t\tfprintf(stderr, \"Error: Unable to create pipe.\\n\");"
												"\n\t\t\t\texit(EXIT_FAILURE);"
												"\n\t\t\t}"
												"\n\t\t\tif ((pid = fork()) < 0) {"
												"\n\t\t\t\tfprintf(stderr, \"Error: Unable to fork process.\\n\");"
												"\n\t\t\t\texit(EXIT_FAILURE);"
												"\n\t\t\t}"
												"\n\t\t\tif (pid > 0) {"
												"\n\t\t\t\tprintf(\"==================== Parent Process %d ====================\\n\", getpid());"
												"\n\t\t\t\tclose(pipe_fd_Voter[1]);"
												"\n\t\t\t\tread(pipe_fd_Voter[0], &chdpid, sizeof(int));"
												"\n\t\t\t\tprintf(\"---Child Process:%4d\\n\", chdpid);"
												"\n\t\t\t\tmemset(k, '\\0', strlen(k));"
												"\n\t\t\t\tmemset(chpid, '\\0', strlen(chpid));"
												"\n\t\t\t\tstrcpy(k, \"kill -9 \");"
												"\n\t\t\t\tsprintf(chpid, \"%d\", chdpid);"
												"\n\t\t\t\tstrcat(k, chpid);"
												"\n\t\t\t\tfor (; finish != 1;) {"
												"\n\t\t\t\t\tsleep(1);"
												"\n\t\t\t\t\tint status;"
												"\n\t\t\t\t\tint w_return = waitpid(chdpid, &status, WNOHANG | WUNTRACED);"
												"\n\t\t\t\t\tif (w_return > 0) {"
												"\n\t\t\t\t\t\tif (WIFEXITED(status)) {"
												"\n\t\t\t\t\t\t\tbreak;"
												"\n\t\t\t\t\t\t} else {"
												"\n\t\t\t\t\t\t\tprintf(\"==================== Parent Process %d  done ====================\\n\", getpid());"
												"\n\t\t\t\t\t\t\tfinish = 1;"
												"\n\t\t\t\t\t\t\tbreak;"
												"\n\t\t\t\t\t\t}"
												"\n\t\t\t\t\t} else if (w_return < 0) {"
												"\n\t\t\t\t\t\tsystem(k);"
												"\n\t\t\t\t\t\tprintf(\"\\n\\t\\t\\t\\tEnd:%s\\n\", k);"
												"\n\t\t\t\t\t\tfinish = 1;"
												"\n\t\t\t\t\t\tbreak;"
												"\n\t\t\t\t\t}"
												"\n\t\t\t\t}"
												"\n\t\t\t} else {"
												"\n\t\t\t\tclose(pipe_fd_Voter[0]);"
												"\n\t\t\t\tchdpid = getpid();"
												"\n\t\t\t\twrite(pipe_fd_Voter[1], &chdpid, sizeof(int));"
												"\n\t\t\t\tprintf(\"------------>Child Process arrived: %4d\\n\", getpid());"
												"\n\t\t\t\tNEW_THREAD:"
												"\n\t\t\t\tif (RedundantFlag == 1 && GotoFlag == 1) {"
												"\n\t\t\t\t\tprintf(\"\\n\\t\\33\\[1;31mNew Thread be created\\33\\[0m\\n\");"
												"\n\t\t\t\t\tGotoFlag = 0;"
												"\n\t\t\t\t}"
												"\n\t\t\t\t#pragma omp parallel for if (RedundantFlag == 0) num_threads(2)"
												"\n\t\t\t\t{"
												"\n\t\t\t\t\tfor (int i = 0; i < Pre_Num_Voter + ThreadCtrl; i++) {"
												"\n\t\t\t\t\t\t#pragma omp critical"
												"\n\t\t\t\t\t\t{";

char rpMultithreadRecv1[] = "\n\t\t\t\t\t\t\t// receive data";
char rpMultithreadRecv2[] = "\n\t\t\t\t\t\t\tdata_"; // + targetVar.size()
char rpMultithreadRecv3[] = "[iterator]."; // + tType
char rpMultithreadRecv4[] = " = "; // + targetVar
char rpMultithreadRecv5[] = ";";

char rpMultithreadCloseRead[] = "\n\t\t\t\t\t\t\tclose(pipe_fd_Voter[0]);";

char rpMultithreadWriteDepVar1[] = "\n\t\t\t\t\t\t\t// write dep variables";
char rpMultithreadWriteDepVar2[] = "\n\t\t\t\t\t\t\twrite(pipe_fd_Voter[1], &"; // + depVar
char rpMultithreadWriteDepVar3[] = ", sizeof("; // + depType
char rpMultithreadWriteDepVar4[] = "));";

char rpMultithread2[] = "\n\t\t\t\t\t\t\t#pragma omp atomic"
												"\n\t\t\t\t\t\t\titerator++;"
												"\n\t\t\t\t\t\t}"
												"\n\t\t\t\t\t}"
												"\n\t\t\t\t}";

char rpMultithreadVoterVars1[] = 	"\n\t\t\t\t"; // + targetType
char rpMultithreadVoterVars2[] =		" v_result_"; // + targetVar.size()
char rpMultithreadVoterVars3[] = 	";"
																		"\n\t\t\t\tint num_Voter_"; // + targetVar.size()
char rpMultithreadVoterVars4[] = 	" = 0;";



char rpMtOptimizeCompare1[] = "\n\t\t\t\tif (( 0";

char rpMtOptimizeCompareVars1[] = "\n\t\t\t\t\t|| data_"; // + targetVar.size()
char rpMtOptimizeCompareVars2[] = "[0]."; // + tType
char rpMtOptimizeCompareVars3[] = " != data_"; // + targetVar.size()
char rpMtOptimizeCompareVars4[] = "[1]."; // + tType

char rpMtOptimizeCompare2[] = ") && RedundantFlag == 0) {"
													"\n\t\t\t\t\tprocess_cnt = MaxForkTimes-Pre_Num_Voter;"
													"\n\t\t\t\t\tRedundantFlag = 1;"
													"\n\t\t\t\t\tGotoFlag = 1;"
													"\n\t\t\t\t\tThreadCtrl = 1;"
													"\n\t\t\t\t\t} else if ( 1";

char rpMtOptimizeCompareVars5[] = "\n\t\t\t\t\t&& data_"; // + targetVar.size()
char rpMtOptimizeCompareVars6[] = "[0]."; // + tType
char rpMtOptimizeCompareVars7[] = " == data_"; // + targetVar.size()
char rpMtOptimizeCompareVars8[] = "[1]."; // + tType

char rpMtOptimizeCompare3[] = ") {";

char rpMultithreadCompareVoterVars1[] = 	"\n\t\t\t\t\tv_result_"; // + targetVar.size()
char rpMultithreadCompareVoterVars2[] = 	" = data_"; // + targetVar.size()
char rpMultithreadCompareVoterVars3[] = 	"[0]."; // + tType
char rpMultithreadCompareVoterVars4[] = 	";"
																					"\n\t\t\t\t\tnum_Voter_"; // + targetVar.size()
char rpMultithreadCompareVoterVars5[] = 	"++;";


char rpMtOptimizeCompare4[] = "\n\t\t\t\t}"
															"\n\t\t\t\tif (RedundantFlag == 1 && GotoFlag == 1) {"
															"\n\t\t\t\t\tgoto NEW_THREAD;               "
															"\n\t\t\t\t}"
															"\n\t\t\t\tif (RedundantFlag == 1 && GotoFlag == 0) {"
															"\n\t\t\t\t\t// voter";

char rpMultithreadVoter1[] = "\n\t\t\t\t\tvoter_"; // + targetType.size()
char rpMultithreadVoter2[] = "(&num_Voter_"; // + targetVar.size()
char rpMultithreadVoter3[] = ", process_cnt, &v_result_"; // + targetVar.size()
char rpMultithreadVoter4[] = ", data_"; // + targetVar.size()
char rpMultithreadVoter5[] = ");";

char rpMtOptimizeCompare5[] = "\n\t\t\t\t}"
															"\n\t\t\t\tif (RedundantFlag == 0";

char rpMtOptimizeFinish1[] = "\n\t\t\t\t\t&& num_Voter_"; // + targetVar.size()
char rpMtOptimizeFinish2[] = " >= 1";

char rpMtOptimizeCompare6[] = ") {";

char rpMultithreadCorrector1[] = "\n\t\t\t\t\t\t// corrector";
char rpMultithreadCorrector2[] = "\n\t\t\t\t\t\tcorrector_"; // + targetType.size()
char rpMultithreadCorrector3[] = "(process_cnt, &v_result_"; // + targetVar.size()
char rpMultithreadCorrector4[] = ", &"; // + targetVar
char rpMultithreadCorrector5[] = ", data_"; // + targetType.size()
char rpMultithreadCorrector6[] = ");";

char rpMultithreadCloseWrite[] = 	"\n\t\t\t\t\t\tclose(pipe_fd_Voter[1]);";

char rpMultithreadReadDepVar1[] = "\n\t\t\t\t\t\tread(pipe_fd_Voter[0], &"; // + depVar
char rpMultithreadReadDepVar2[] = ", sizeof("; // + depVarType
char rpMultithreadReadDepVar3[] = "));";

char rpMultithreadClosePipes[] = 	"\n\t\t\t\t\t\tclose(pipe_fd_Voter[0]);"
																	"\n\t\t\t\t\t\tclose(pipe_fd_Voter[1]);";
																	
char rpMultithreadFinishFlags1[] = 	"\n\t\t\t\t\t\tprintf(\"FINISH\\n\");"
																		"\n\t\t\t\t\t\tfinish = 1;";

char rpMtOptimizeCompare7[] = "\n\t\t\t\t} else if (RedundantFlag == 1";

char rpMtOptimizeFinish3[] = "\n\t\t\t\t\t&& num_Voter_"; // + targetVar.size()
char rpMtOptimizeFinish4[] = " >= (Pre_Num_Voter+process_cnt+1) / 2";

char rpMultithreadFinishFlags2[] = 	"\n\t\t\t\t\t\tprintf(\"FINISH\\n\");"
																		"\n\t\t\t\t\t\tRedundantFlag = 0;"
																		"\n\t\t\t\t\t\tGotoFlag = 0;"
																		"\n\t\t\t\t\t\tprocess_cnt = 0;"
																		"\n\t\t\t\t\t\tThreadCtrl = 0;"
																		"\n\t\t\t\t\t\tfinish = 1;";

char rpMultithread3[] = "\n\t\t\t\t} else {"
												"\n\t\t\t\t\tprintf(\"\\33\\[1;31m \\n\\t -- There doesn't exist a majority voter -- \\33\\[0m \\n\\n\");"
												"\n\t\t\t\t\tbreak;"
												"\n\t\t\t\t}"
												"\n\t\t\t\tprintf(\"------------>Child Process done: %4d\\n\", getpid());"
												"\n\t\t\t\tfinish = 1;"
												"\n\t\t\t\texit(EXIT_SUCCESS);"
												"\n\t\t\t}"
												"\n\t\t}";

char rpMtWhile2[] = "\n\t}";

#endif