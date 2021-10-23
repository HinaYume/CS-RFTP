#ifndef ABNORMALTEST_H_
#define ABNORMALTEST_H_

#define	ABVARS_ 			AbVars
#define ABCHECK_			AbCheck
#define ABFORROUNDHEAD_		AbForRoundHead
#define ABFORKPPI_			AbForkParentParentIf
#define ABFORKPPFH_ 		AbForkParentParentFinishHead
#define ABFORKPPFEIH_ 		AbForkParentParentFinishElseIfHead
#define ABFORKPPFEIB_ 		AbForkParentParentFinishElseIfBody
#define ABFORKPPFEIE_ 		AbForkParentParentFinishElseIfEnd
#define ABFORKPPFEIO_ 		AbForkParentParentFinishElseIfOthers
#define ABFORKPIE_ 			AbForkParentIfEnd
#define ABPORTECTEDBIE_ 	AbProtectedBodyIfEnd

char AbVars[] = 								"\n\tpid_t pid;"
												"\n\tint pipe_fd_Voter[2];"
												"\n\tint pipe_fd_Voter2[2];"
												"\n\tchar k[3][50];"
												"\n\tchar chpid[3][12];"
												"\n\tint finish = 0;"
												"\n\tint respawn = 0;"
												"\n\tint wait_chd;"
												"\n\tint round_num = 0;"
												"\n\tint dep_process = 0;"
												"\n\tint kill_count = 0;"
												"\n\tint chdpid;"
												"\n\tint cnt = 0;"
												;
char AbCheck[] = 								"\n\tif (pipe(pipe_fd_Voter2) == -1) {"
												"\n\t\tfprintf(stderr, "Error: Unable to create pipe.\n");"
												"\n\t\texit(EXIT_FAILURE);"
												"\n\t}"
												"\n\tif ((pid = fork()) < 0) {"
												"\n\t\tfprintf(stderr, "Error: Unable to fork process.\n");"
												"\n\t\texit(EXIT_FAILURE);"
												"\n\t}"
												;
char AbForRoundHead[] = 						"\n\tfor (round_num = 0; round_num < 2, finish == 0; round_num++) {"
												"\n\t\tif (pid > 0) {"
												"\n\t\t\tprintf("==================== Parent Process %d ====================\n", getpid());"
												"\n\t\t\tif (round_num == 0) {"
												"\n\t\t\t\tfor (int num = 0; num < Total_Num_Voter; num++) {"
												"\n\t\t\t\t\tif (pid > 0) {"
												"\n\t\t\t\t\t\tif (pipe(pipe_fd_Voter) == -1) {"
												"\n\t\t\t\t\t\t\tfprintf(stderr, "Error: Unable to create pipe.\n");"
												"\n\t\t\t\t\t\t\texit(EXIT_FAILURE);"
		                      					"\n\t\t\t\t\t\t}"
												"\n\t\t\t\t\t\tpid = fork();"
												"\n\t\t\t\t\t\tcnt++;"
												"\n\t\t\t\t\t\tif (num == (Total_Num_Voter - 1) && pid == 0)"										
												"\n\t\t\t\t\t\t\tdep_process = 1;"
												"\n\t\t\t\t\t\tif (pid == 0) {"
												"\n\t\t\t\t\t\t\tclose(pipe_fd_Voter[0]);"
												"\n\t\t\t\t\t\t\tchdpid = getpid();"
												"\n\t\t\t\t\t\t\twrite(pipe_fd_Voter[1], &chdpid, sizeof(int));"
												"\n\t\t\t\t\t\t\tprintf("\n\t***Child Process %d: %4d\n", cnt, chdpid);"
												"\n\t\t\t\t\t\t} else if (pid > 0) {"
												"\n\t\t\t\t\t\t\tclose(pipe_fd_Voter[1]);"
												"\n\t\t\t\t\t\t\tread(pipe_fd_Voter[0], &chdpid, sizeof(int));"
												"\n\t\t\t\t\t\t\tprintf("\n\t---Child Process %d: %4d\n", cnt, chdpid);"
												"\n\t\t\t\t\t\t\tmemset(k[num], '\0', strlen(k[num]));"
												"\n\t\t\t\t\t\t\tmemset(chpid[num], '\0', strlen(chpid[num]));"
												"\n\t\t\t\t\t\t\tstrcpy(k[num], "kill -9 ");"
												"\n\t\t\t\t\t\t\tsprintf(chpid[num], "%d", chdpid);"
												"\n\t\t\t\t\t\t\tstrcat(k[num], chpid[num]);"
												"\n\t\t\t\t\t\t}"
												"\n\t\t\t\t\t}"
												"\n\t\t\t\t}"      
												"\n\t\t\t}"
												;
char AbForkParentParentIf[] = 					"\n\t\t\tif (pid > 0) {"
												"\n\t\t\t\tprintf("  ==========> Parent Process ONLY at round_num %d <==========\n\n", round_num);"
												"\n\t\t\t\tint time_delay = 0;"
												;     
        
char AbForkParentParentFinishHead[] = 			"\n\t\t\t\tfor (; finish != 1;) {"
												"\n\t\t\t\t\tint w_return = waitpid(-1, NULL, WNOHANG | WUNTRACED);"
												"\n\t\t\t\t\tif (w_return == 0) {"
												"\n\t\t\t\t\t\tsleep(1);"
												"\n\t\t\t\t\t\ttime_delay++;"
												"\n\t\t\t\t\t\tprintf("time_delay++ = %d\n", time_delay);"
												"\n\t\t\t\t\t\tif (time_delay == 5) {"
												"\n\t\t\t\t\t\t\tprintf("\t+++time_delay = %d\n", time_delay);"
												"\n\t\t\t\t\t\t\ttime_delay = 0;"
												"\n\t\t\t\t\t\t\tfor (int num = 0; num < Total_Num_Voter; num++) {"
												"\n\t\t\t\t\t\t\t\tsystem(k[num]);"
												"\n\t\t\t\t\t\t\t\tprintf("\t\t\t\tEnd:%s\n", k[num]);"
												"\n\t\t\t\t\t\t\t}"
												"\n\t\t\t\t\t\t\tkill_count = 0;"
												"\n\t\t\t\t\t\t\trespawn = 1;"
												"\n\t\t\t\t\t\t\tprocess_num = Total_Num_Voter;"
												"\n\t\t\t\t\t\t\tround_num = -1;"
												"\n\t\t\t\t\t\t\tdep_process = 0;"
												"\n\t\t\t\t\t\t\tbreak;"
												"\n\t\t\t\t\t\t\t} else {"
												"\n\t\t\t\t\t\t\t\trespawn = 0;"
												"\n\t\t\t\t\t\t\t}"
												;
char AbForkParentParentFinishElseIfHead[] = 	"\n\t\t\t\t\t} else if (w_return > 0 && respawn != 1) {"
												;           	// receiver
char AbForkParentParentFinishElseIfBody[] = 	"\n\t\t\t\t\t\ttime_delay = 0;"
																// voter
																// corrector
												;             
char AbForkParentParentFinishElseIfEnd[] = 		"\n\t\t\t\t\t}"
												;   			        
char AbForkParentParentFinishElseIfOthers[] =	"\n\t\t\t\t\telse if (w_return > 0 && respawn == 1) {"
												"\n\t\t\t\t\t\tkill_count += 1;"
												"\n\t\t\t\t\t\tprintf("\n\tkill_count:%d\n", kill_count);"
												"\n\t\t\t\t\t\tif (kill_count == Total_Num_Voter) {"
												"\n\t\t\t\t\t\t\ttime_delay = 0;"
												"\n\t\t\t\t\t\t\trespawn = 0;"
												"\n\t\t\t\t\t\t}"
												"\n\t\t\t\t\t} else if (w_return < 0) {"
												"\n\t\t\t\t\t\tfinish = 1;"
												"\n\t\t\t\t\t\tprocess_num = Total_Num_Voter;"
												"\n\t\t\t\t\t\tround_num = -1;"
												"\n\t\t\t\t\t\tdep_process = 0;"
												"\n\t\t\t\t\t\ttime_delay = 0;"
												"\n\t\t\t\t\t\trespawn = 0;"
												"\n\t\t\t\t\t\tbreak;"
												"\n\t\t\t\t\t}"
												"\n\t\t\t\t}"
												"\n\t\t\t}"
												;      
char AbForkParentIfEnd[] =						"\n\t\t} else {"
												"\n\t\t\tprintf("------------>Child Process has arrived: %4d\n", getpid());"
												"\n\t\t\tif (round_num != 0) {"
												;			// Protected Body     
char AbProtectedBodyIfEnd[]  =					"\n\t\t\t}"
												"\n\t\t\tfinish = 1;"     
							    				"\n\t\t\texit(EXIT_SUCCESS);"
							    				"\n\t\t}"
												"\n\t}"
												"\n\t//*** ENDD_____   }"
												;
#endif