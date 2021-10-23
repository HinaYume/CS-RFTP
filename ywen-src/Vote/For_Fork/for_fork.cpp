#include "clang/Driver/Options.h"
#include "clang/AST/AST.h"
#include "clang/AST/ASTContext.h"
#include "clang/AST/ASTConsumer.h"
#include "clang/AST/RecursiveASTVisitor.h"
#include "clang/Frontend/ASTConsumers.h"
#include "clang/Frontend/FrontendActions.h"
#include "clang/Frontend/CompilerInstance.h"
#include "clang/Tooling/CommonOptionsParser.h"
#include "clang/Tooling/Tooling.h"
#include "clang/Rewrite/Core/Rewriter.h"

#include "llvm/Support/raw_ostream.h"
#include <sstream>
#include <string>
#include <cstdio>
#include <iostream>
#include <stdio.h>
//#include "for_model.h"
//#include "omp_model.h"
//#include "multi_fork_model.h"

//#include "abnormal_model.h"
//#include "repeat_model.h"

//#include "repeat_for.h"
//#include "repeat_omp_voteinchd.h"
//#include "repeat_multi_fork_model.h"

//#include "abnormal_for.h"
//#include "abnormal_omp_voteinchd.h"
//#include "abnormal_multi_fork.h"

#include "BasicModules.h"
#include "AbnormalMultiProcessModules.h"
#include "AbnormalSequentialModules.h"
#include "AbnormalMultiThreadModules.h"
#include "RepeatMultiProcessModules.h"
#include "RepeatSequentialModules.h"
#include "RepeatMultiThreadModules.h"

using namespace std;
using namespace clang;
using namespace clang::driver;
using namespace clang::tooling;
using namespace llvm;

Rewriter rewriter;
int g_argc=0;
const char *g_argv[10];
int B = 0;

void arg_parse(int argc,const char *argv[]){
    int a=0;
    g_argc = argc;
    for(a=1; a <argc;a++){
        g_argv[a] = argv[a];
    }  
}

SourceLocation S;
SourceLocation E;
int numFunctions = 0;

static llvm::cl::OptionCategory StatCategory("For_Fork");

class VoteVisitor : public RecursiveASTVisitor<VoteVisitor> {
private:
    ASTContext *astContext; // get additional AST info

public:
    explicit VoteVisitor(CompilerInstance *CI) : astContext(&(CI->getASTContext())) {  // initialize private members
        rewriter.setSourceMgr(astContext->getSourceManager(), astContext->getLangOpts());
    }

	virtual bool VisitPragmaVoteDecl(PragmaVoteDecl *pvd) {

		errs() << "******************************\n";
		errs() << "VisitPragmaVoteDecl\t" << numFunctions <<"\n";

		string Name = pvd->getName();
		errs () << "==> NAME: \t\t" << Name << "\n";

		string voteMethod = pvd->getVoteMethod();
		errs() << "==> VOTE Method:\t" << voteMethod << "\n";

    string MaxTimeLimit = pvd->getMaxTimeLimit();
		errs() << "==> MONITOR MTL:\t" << MaxTimeLimit << "\n";

		string MonitorMode = pvd->getMonitorMode();
		errs() << "==> MONITOR mode:\t" << MonitorMode << "\n";

		vector <string> targetVar = pvd->getTarget();
		vector <string> targetType = pvd->getTargetType();
		errs() << "==> TARGET length:\t" << targetVar.size() << "\n";

		for(unsigned int i = 0; i < targetVar.size(); i++) {
			errs() << "==> TARGET var" << i+1 << ":\t" << targetVar[i] << "\n";
			errs() << "==> TARGET type:\t" << targetType[i] << "\n";
		}

		// get the type's flag
		vector <string> tType;
		// %type
		// i.g. %d, %f, %c
		vector <string> perType;
		for(unsigned int i = 0; i < targetType.size(); i++) {
				 if(targetType[i] == "int")   	{ tType.push_back("i"); perType.push_back("d");}
			else if(targetType[i] == "float") { tType.push_back("f"); perType.push_back("f");}
			else if(targetType[i] == "short") { tType.push_back("s"); perType.push_back("f"); }
			else if(targetType[i] == "double"){ tType.push_back("d"); perType.push_back("lf"); }
			else if(targetType[i] == "long")  { tType.push_back("l"); perType.push_back("f"); }
			else if(targetType[i] == "char")  { tType.push_back("c"); perType.push_back("c"); }

			errs () << "==> tType" << i+1 << ":\t\t" << tType[i] << "\n";
		}

		vector <string> depVar = pvd->getDep();
		vector <string> depType = pvd->getDepType();
		errs() << "==> DEP length:\t\t" << depVar.size() << "\n";

		for(unsigned int i=0; i < depVar.size() ; i++) {
			errs() << "==> DEP var" << i+1 << ":\t\t"<< depVar[i] << "\n";
			errs() << "==> DEP Type:\t\t" << depType[i] << "\n";
		}

		string mon1("abnormal");
		string mon2("repeat");

		string vm1("multiprocess");
		string vm2("sequential");
		string vm3("multithread");

		// Insert Global scope
		// corrector decl
		rewriter.InsertTextBefore(S, "\n\n");
		for (int i = targetType.size() - 1; i >= 0; i--) {
			rewriter.InsertTextBefore(S, CORRECTORDECL1_ + to_string(i+1) +
																	 CORRECTORDECL2_ + targetType[i] +
																	 CORRECTORDECL3_ + targetType[i] + 
																	 CORRECTORDECL4_);
		}

		// voter decl
		rewriter.InsertTextBefore(S, "\n");
		for (int i = targetType.size() - 1; i >= 0; i--) {
			rewriter.InsertTextBefore(S, VOTERDECL1_ + to_string(i+1) +
																	 VOTERDECL2_ + targetType[i] +
																	 VOTERDECL3_);
		}

		if (voteMethod.compare(vm3) != 0) {
			// receiver decl
			rewriter.InsertTextBefore(S, "\n");
			for (int i = targetType.size() - 1; i >= 0; i--) {
				rewriter.InsertTextBefore(S, RECEIVERDECL1_ + to_string(i+1) +
																		 RECEIVERDECL2_ + targetType[i] +
																		 RECEIVERDECL3_);
			}			
		}

		rewriter.InsertTextBefore(S, "\n");
		// data decl
		for (int i = targetVar.size() - 1; i >= 0; i--) {
			rewriter.InsertTextBefore(S, DATADECL1_ + to_string(i+1) + DATADECL2_);
		}
		rewriter.InsertTextBefore(S, "\n");
		rewriter.InsertTextBefore(S,DATASTRUCT_);
		rewriter.InsertTextBefore(S,DATATYPE_);
		rewriter.InsertTextBefore(S,GLOBALVARS_);
		if (voteMethod.compare(vm3) == 0)
			rewriter.InsertTextBefore(S,OMPLIBRARY_);
		rewriter.InsertTextBefore(S,LIBRARY_);

		// function implement
		rewriter.InsertTextAfter(E, "\n// Function Implement (´・ω・`)ｼﾝｼﾞﾝｸﾝﾊﾔｸﾆｹﾞﾃ");		

		if (voteMethod.compare(vm1) == 0) {
			// receiver
			for (unsigned int i = 0; i < targetType.size(); i++) {
				rewriter.InsertTextAfter(E, MPRECEIVERFUNC1_ + to_string(i+1) +
																		MPRECEIVERFUNC2_ + targetType[i] +
																		MPRECEIVERFUNC3_ + targetType[i] +
																		MPRECEIVERFUNC4_ + perType[i] +
																		MPRECEIVERFUNC5_);
			}		
		} else if (voteMethod.compare(vm2) == 0) {
			// receiver
			for (unsigned int i = 0; i < targetType.size(); i++) {
				rewriter.InsertTextAfter(E, SEQRECEIVERFUNC1_ + to_string(i+1) +
																		SEQRECEIVERFUNC2_ + targetType[i] +
																		SEQRECEIVERFUNC3_ + targetType[i] +
																		SEQRECEIVERFUNC4_ + perType[i] +
																		SEQRECEIVERFUNC5_);
			}			
		}

		// voter
		for (unsigned int i = 0; i < targetType.size(); i++) {
			rewriter.InsertTextAfter(E, MPVOTERFUNC1_ + to_string(i+1) + 
																	MPVOTERFUNC2_ + targetType[i] +
																	MPVOTERFUNC3_ + tType[i] +
																	MPVOTERFUNC4_ + tType[i] +
																	MPVOTERFUNC5_ + perType[i] +
																	MPVOTERFUNC6_ + tType[i] +
																	MPVOTERFUNC7_ + tType[i] +									
																	MPVOTERFUNC8_ + perType[i] +
																	MPVOTERFUNC9_);
		}
		// corrector
		for (unsigned int i = 0; i < targetType.size(); i++) {
			rewriter.InsertTextAfter(E, MPCORRECTORFUNC1_ + to_string(i+1) +
																	MPCORRECTORFUNC2_ + targetType[i] +
																	MPCORRECTORFUNC3_ + targetType[i] +
																	MPCORRECTORFUNC4_ + tType[i] +
																	MPCORRECTORFUNC5_ + perType[i] +
																	MPCORRECTORFUNC6_ + tType[i] +
																	MPCORRECTORFUNC7_ + perType[i] +
																	MPCORRECTORFUNC8_);
		}

		if((voteMethod.compare(""))!=0 && (MaxTimeLimit.compare(""))!=0) {

			errs() << "==> MonitorVoting set:\t"<< MonitorMode << " " << voteMethod << "\n";

			SourceLocation SW =  pvd->getLocation();
			rewriter.ReplaceText(SW.getLocWithOffset(-8),"// ");
			//rewriter.ReplaceText(pvd->getLBraceLoc()," ");
			rewriter.ReplaceText(pvd->getLBraceLoc(),"// THE SCOPE OF PRAGMA PROTECT __BEGIN");
			rewriter.ReplaceText(pvd->getRBraceLoc(),"// THE SCOPE OF PRAGMA PROTECT __END");

			// abnormal mode
			if (MonitorMode.compare(mon1) == 0) {
				// multiprocess
				if (voteMethod.compare(vm1) == 0) {
					rewriter.InsertTextAfterToken(pvd->getLBraceLoc(), ABMPVARS_);
					rewriter.InsertTextAfterToken(pvd->getLBraceLoc(), ABMPINIT_);					
					rewriter.InsertTextAfterToken(pvd->getLBraceLoc(), ABMULTIPROCESS1_);
					// receiver
					for (unsigned int i = 0; i < targetVar.size(); i++) {
						rewriter.InsertTextAfterToken(pvd->getLBraceLoc(), ABMPRECV1_ + to_string(i+1) +
																															 ABMPRECV2_ + to_string(i+1) +
																															 ABMPRECV3_ + tType[i] +
																															 ABMPRECV4_);
					}
					rewriter.InsertTextAfterToken(pvd->getLBraceLoc(), ABMULTIPROCESS2_);
					for (unsigned int i = 0; i < targetVar.size(); i++) {
						rewriter.InsertTextAfterToken(pvd->getLBraceLoc(), ABMPRECV5_ + to_string(i+1) +
																															 ABMPRECV6_ + to_string(i+1) +
																															 ABMPRECV7_ + tType[i] +
																															 ABMPRECV8_);
					}
					rewriter.InsertTextAfterToken(pvd->getLBraceLoc(), ABMULTIPROCESS3_);
					// voter variables
					for (unsigned int i = 0; i < targetVar.size(); i++) {
						rewriter.InsertTextAfterToken(pvd->getLBraceLoc(), ABMPVV1_ + targetType[i] +
																															 ABMPVV2_ + to_string(i+1) + 
																															 ABMPVV3_ + to_string(i+1) +
																															 ABMPVV4_);

					}
					// optimize compare
					rewriter.InsertTextAfterToken(pvd->getLBraceLoc(), ABMPOPTCMP1_);
					for (unsigned int i = 0; i < targetVar.size(); i++) {
						rewriter.InsertTextAfterToken(pvd->getLBraceLoc(), ABMPOPTCMPV1_ + to_string(i+1) +
																															 ABMPOPTCMPV2_ + tType[i] +
																															 ABMPOPTCMPV3_ + to_string(i+1) +
																															 ABMPOPTCMPV4_ + tType[i]);

					}
					rewriter.InsertTextAfterToken(pvd->getLBraceLoc(), ABMPOPTCMP2_);
					for (unsigned int i = 0; i < targetVar.size(); i++) {
						rewriter.InsertTextAfterToken(pvd->getLBraceLoc(), ABMPOPTCMPV5_ + to_string(i+1) +
																															 ABMPOPTCMPV6_ + tType[i] +
																															 ABMPOPTCMPV7_ + to_string(i+1) +
																															 ABMPOPTCMPV8_ + tType[i]);

					}
					rewriter.InsertTextAfterToken(pvd->getLBraceLoc(), ABMPOPTCMP3_);
					for (unsigned int i = 0; i < targetVar.size(); i++) {
						rewriter.InsertTextAfterToken(pvd->getLBraceLoc(), ABMPCMPVV1_ + to_string(i+1) + 
																															 ABMPCMPVV2_ + to_string(i+1) +
																															 ABMPCMPVV3_ + tType[i] +
																															 ABMPCMPVV4_ + to_string(i+1) +
																															 ABMPCMPVV5_);

					}
					rewriter.InsertTextAfterToken(pvd->getLBraceLoc(), ABMPOPTCMP4_);
					// voter
					for (unsigned int i = 0; i < targetVar.size(); i++) {
						rewriter.InsertTextAfterToken(pvd->getLBraceLoc(), ABMPVOTER1_ + to_string(i+1) +
																															 ABMPVOTER2_ + to_string(i+1) +
																															 ABMPVOTER3_ + to_string(i+1) +
																															 ABMPVOTER4_ + to_string(i+1) +
																															 ABMPVOTER5_);

					}
					rewriter.InsertTextAfterToken(pvd->getLBraceLoc(), ABMPOPTCMP5_);
					for (unsigned int i = 0; i < targetVar.size(); i++) {
						rewriter.InsertTextAfterToken(pvd->getLBraceLoc(), ABMPOPTFINISH1_ + to_string(i+1) +
																														 	 ABMPOPTFINISH2_);
					}
					rewriter.InsertTextAfterToken(pvd->getLBraceLoc(), ABMPOPTCMP6_);
					// corrector
					rewriter.InsertTextAfterToken(pvd->getLBraceLoc(), ABMPCORRECTOR1_);
					for (unsigned int i = 0; i < targetVar.size(); i++) {
						rewriter.InsertTextAfterToken(pvd->getLBraceLoc(), ABMPCORRECTOR2_ + to_string(i+1) +
																															 ABMPCORRECTOR3_ + to_string(i+1) +
																															 ABMPCORRECTOR4_ + targetVar[i] +
																															 ABMPCORRECTOR5_ + to_string(i+1) +
																															 ABMPCORRECTOR6_);
					}				
					for (unsigned int i = 0; i < depVar.size(); i++) {
						rewriter.InsertTextAfterToken(pvd->getLBraceLoc(), ABMPRDEPVAR1_ + depVar[i] +
																															 ABMPRDEPVAR2_ + depType[i] +
																															 ABMPRDEPVAR3_);
					}
					rewriter.InsertTextAfterToken(pvd->getLBraceLoc(), ABMPCLOSEPIPE_);
					rewriter.InsertTextAfterToken(pvd->getLBraceLoc(), ABMPFINISHFLAGS1_);
					rewriter.InsertTextAfterToken(pvd->getLBraceLoc(), ABMPOPTCMP7_);
					for (unsigned int i = 0; i < targetVar.size(); i++) {
						rewriter.InsertTextAfterToken(pvd->getLBraceLoc(), ABMPOPTFINISH1_ + to_string(i+1) +
																														 	 ABMPOPTFINISH2_);
					}
					rewriter.InsertTextAfterToken(pvd->getLBraceLoc(), ABMPOPTCMP6_);					
					// corrector
					rewriter.InsertTextAfterToken(pvd->getLBraceLoc(), ABMPCORRECTOR1_);
					for (unsigned int i = 0; i < targetVar.size(); i++) {
						rewriter.InsertTextAfterToken(pvd->getLBraceLoc(), ABMPCORRECTOR2_ + to_string(i+1) +
																															 ABMPCORRECTOR3_ + to_string(i+1) +
																															 ABMPCORRECTOR4_ + targetVar[i] +
																															 ABMPCORRECTOR5_ + to_string(i+1) +
																															 ABMPCORRECTOR6_);
					}
					for (unsigned int i = 0; i < depVar.size(); i++) {
						rewriter.InsertTextAfterToken(pvd->getLBraceLoc(), ABMPRDEPVAR1_ + depVar[i] +
																															 ABMPRDEPVAR2_ + depType[i] +
																															 ABMPRDEPVAR3_);
					}					
					rewriter.InsertTextAfterToken(pvd->getLBraceLoc(), ABMPCLOSEPIPE_);															
					rewriter.InsertTextAfterToken(pvd->getLBraceLoc(), ABMPFINISHFLAGS2_);
					rewriter.InsertTextAfterToken(pvd->getLBraceLoc(), ABMULTIPROCESS4_);

					// RBrace
					for (unsigned int i = 0; i < targetVar.size(); i++) {
						rewriter.InsertTextAfterToken(pvd->getLocEnd(), ABMPWTARGETVAR1_ + targetVar[i] +
																													  ABMPWTARGETVAR2_ + targetType[i] +
																													  ABMPWTARGETVAR3_);
					}
					for (unsigned int i = 0; i < depVar.size(); i++) {
						rewriter.InsertTextAfterToken(pvd->getLocEnd(), ABMPWDEPVAR1_ + depVar[i] + 
																														ABMPWDEPVAR2_ + depType[i] +
																														ABMPWDEPVAR3_);
					}
					rewriter.InsertTextAfterToken(pvd->getLocEnd(), ABMULTIPROCESS5_);

				} else if (voteMethod.compare(vm2) == 0) {
					rewriter.InsertTextAfterToken(pvd->getLBraceLoc(), ABSEQVARS_);
					rewriter.InsertTextAfterToken(pvd->getLBraceLoc(), ABSEQINIT_);					
					rewriter.InsertTextAfterToken(pvd->getLBraceLoc(), ABSEQUENTIAL1_);
					// receiver
					for (unsigned int i = 0; i < targetVar.size(); i++) {
						rewriter.InsertTextAfterToken(pvd->getLBraceLoc(), ABSEQRECV1_ + to_string(i+1) +
																															 ABSEQRECV2_ + to_string(i+1) +
																															 ABSEQRECV3_ + tType[i] +
																															 ABSEQRECV4_);
					}
					rewriter.InsertTextAfterToken(pvd->getLBraceLoc(), ABSEQUENTIAL2_);
					for (unsigned int i = 0; i < targetVar.size(); i++) {
						rewriter.InsertTextAfterToken(pvd->getLBraceLoc(), ABSEQRECV5_ + to_string(i+1) +
																															 ABSEQRECV6_ + to_string(i+1) +
																															 ABSEQRECV7_ + tType[i] +
																															 ABSEQRECV8_);
					}
					rewriter.InsertTextAfterToken(pvd->getLBraceLoc(), ABSEQUENTIAL3_);
					// voter variables
					for (unsigned int i = 0; i < targetVar.size(); i++) {
						rewriter.InsertTextAfterToken(pvd->getLBraceLoc(), ABSEQVV1_ + targetType[i] +
																															 ABSEQVV2_ + to_string(i+1) + 
																															 ABSEQVV3_ + to_string(i+1) +
																															 ABSEQVV4_);

					}
					// optimize compare
					rewriter.InsertTextAfterToken(pvd->getLBraceLoc(), ABSEQOPTCMP1_);
					for (unsigned int i = 0; i < targetVar.size(); i++) {
						rewriter.InsertTextAfterToken(pvd->getLBraceLoc(), ABSEQOPTCMPV1_ + to_string(i+1) +
																															 ABSEQOPTCMPV2_ + tType[i] +
																															 ABSEQOPTCMPV3_ + to_string(i+1) +
																															 ABSEQOPTCMPV4_ + tType[i]);

					}
					rewriter.InsertTextAfterToken(pvd->getLBraceLoc(), ABSEQOPTCMP2_);
					for (unsigned int i = 0; i < targetVar.size(); i++) {
						rewriter.InsertTextAfterToken(pvd->getLBraceLoc(), ABSEQOPTCMPV5_ + to_string(i+1) +
																															 ABSEQOPTCMPV6_ + tType[i] +
																															 ABSEQOPTCMPV7_ + to_string(i+1) +
																															 ABSEQOPTCMPV8_ + tType[i]);

					}
					rewriter.InsertTextAfterToken(pvd->getLBraceLoc(), ABSEQOPTCMP3_);
					for (unsigned int i = 0; i < targetVar.size(); i++) {
						rewriter.InsertTextAfterToken(pvd->getLBraceLoc(), ABSEQCMPVV1_ + to_string(i+1) + 
																															 ABSEQCMPVV2_ + to_string(i+1) +
																															 ABSEQCMPVV3_ + tType[i] +
																															 ABSEQCMPVV4_ + to_string(i+1) +
																															 ABSEQCMPVV5_);

					}
					rewriter.InsertTextAfterToken(pvd->getLBraceLoc(), ABSEQOPTCMP4_);
					// voter
					for (unsigned int i = 0; i < targetVar.size(); i++) {
						rewriter.InsertTextAfterToken(pvd->getLBraceLoc(), ABSEQVOTER1_ + to_string(i+1) +
																															 ABSEQVOTER2_ + to_string(i+1) +
																															 ABSEQVOTER3_ + to_string(i+1) +
																															 ABSEQVOTER4_ + to_string(i+1) +
																															 ABSEQVOTER5_);

					}
					rewriter.InsertTextAfterToken(pvd->getLBraceLoc(), ABSEQOPTCMP5_);
					for (unsigned int i = 0; i < targetVar.size(); i++) {
						rewriter.InsertTextAfterToken(pvd->getLBraceLoc(), ABSEQOPTFINISH1_ + to_string(i+1) +
																														 	 ABSEQOPTFINISH2_);
					}
					rewriter.InsertTextAfterToken(pvd->getLBraceLoc(), ABSEQOPTCMP6_);
					// corrector
					rewriter.InsertTextAfterToken(pvd->getLBraceLoc(), ABSEQCORRECTOR1_);
					for (unsigned int i = 0; i < targetVar.size(); i++) {
						rewriter.InsertTextAfterToken(pvd->getLBraceLoc(), ABSEQCORRECTOR2_ + to_string(i+1) +
																															 ABSEQCORRECTOR3_ + to_string(i+1) +
																															 ABSEQCORRECTOR4_ + targetVar[i] +
																															 ABSEQCORRECTOR5_ + to_string(i+1) +
																															 ABSEQCORRECTOR6_);
					}				
					for (unsigned int i = 0; i < depVar.size(); i++) {
						rewriter.InsertTextAfterToken(pvd->getLBraceLoc(), ABSEQRDEPVAR1_ + depVar[i] +
																															 ABSEQRDEPVAR2_ + depType[i] +
																															 ABSEQRDEPVAR3_);
					}
					rewriter.InsertTextAfterToken(pvd->getLBraceLoc(), ABSEQCLOSEPIPE_);
					rewriter.InsertTextAfterToken(pvd->getLBraceLoc(), ABSEQFINISHFLAGS1_);
					rewriter.InsertTextAfterToken(pvd->getLBraceLoc(), ABSEQOPTCMP7_);
					for (unsigned int i = 0; i < targetVar.size(); i++) {
						rewriter.InsertTextAfterToken(pvd->getLBraceLoc(), ABSEQOPTFINISH3_ + to_string(i+1) +
																														 	 ABSEQOPTFINISH4_);
					}
					rewriter.InsertTextAfterToken(pvd->getLBraceLoc(), ABSEQOPTCMP6_);					
					// corrector
					rewriter.InsertTextAfterToken(pvd->getLBraceLoc(), ABSEQCORRECTOR1_);
					for (unsigned int i = 0; i < targetVar.size(); i++) {
						rewriter.InsertTextAfterToken(pvd->getLBraceLoc(), ABSEQCORRECTOR2_ + to_string(i+1) +
																															 ABSEQCORRECTOR3_ + to_string(i+1) +
																															 ABSEQCORRECTOR4_ + targetVar[i] +
																															 ABSEQCORRECTOR5_ + to_string(i+1) +
																															 ABSEQCORRECTOR6_);
					}
					for (unsigned int i = 0; i < depVar.size(); i++) {
						rewriter.InsertTextAfterToken(pvd->getLBraceLoc(), ABSEQRDEPVAR1_ + depVar[i] +
																															 ABSEQRDEPVAR2_ + depType[i] +
																															 ABSEQRDEPVAR3_);
					}					
					rewriter.InsertTextAfterToken(pvd->getLBraceLoc(), ABSEQCLOSEPIPE_);															
					rewriter.InsertTextAfterToken(pvd->getLBraceLoc(), ABSEQFINISHFLAGS2_);
					rewriter.InsertTextAfterToken(pvd->getLBraceLoc(), ABSEQUENTIAL4_);

					// RBrace
					for (unsigned int i = 0; i < targetVar.size(); i++) {
						rewriter.InsertTextAfterToken(pvd->getLocEnd(), ABSEQWTARGETVAR1_ + targetVar[i] +
																													  ABSEQWTARGETVAR2_ + targetType[i] +
																													  ABSEQWTARGETVAR3_);
					}
					for (unsigned int i = 0; i < depVar.size(); i++) {
						rewriter.InsertTextAfterToken(pvd->getLocEnd(), ABSEQWDEPVAR1_ + depVar[i] + 
																														ABSEQWDEPVAR2_ + depType[i] +
																														ABSEQWDEPVAR3_);
					}
					rewriter.InsertTextAfterToken(pvd->getLocEnd(), ABSEQUENTIAL5_);

				} else if (voteMethod.compare(vm3) == 0) {
					rewriter.InsertTextAfterToken(pvd->getLBraceLoc(), ABMTVARS_);
					rewriter.InsertTextAfterToken(pvd->getLBraceLoc(), ABMULTITHREAD1_);

					// RBrace
					rewriter.InsertTextAfterToken(pvd->getLocEnd(), ABMTRECV1_);
					for (unsigned int i = 0; i < targetVar.size(); i++) {
						rewriter.InsertTextAfterToken(pvd->getLocEnd(), ABMTRECV2_ + to_string(i+1) + 
																														ABMTRECV3_ + tType[i] + 
																														ABMTRECV4_ + targetVar[i] +
																														ABMTRECV5_);
					}
					rewriter.InsertTextAfterToken(pvd->getLocEnd(), ABMTCLOSEREAD_);					
					rewriter.InsertTextAfterToken(pvd->getLocEnd(), ABMTWDEPVAR1_);
					for (unsigned int i = 0; i < depVar.size(); i++) {
						rewriter.InsertTextAfterToken(pvd->getLocEnd(), ABMTWDEPVAR2_ + depVar[i] +
																														ABMTWDEPVAR3_ + depType[i] +
																														ABMTWDEPVAR4_);
					}
					rewriter.InsertTextAfterToken(pvd->getLocEnd(), ABMULTITHREAD2_);

					// voter variables
					for (unsigned int i = 0; i < targetVar.size(); i++) {
						rewriter.InsertTextAfterToken(pvd->getLocEnd(), ABMTVV1_ + targetType[i] +
																														ABMTVV2_ + to_string(i+1) + 
																														ABMTVV3_ + to_string(i+1) +
																														ABMTVV4_);

					}
					// optimize compare
					rewriter.InsertTextAfterToken(pvd->getLocEnd(), ABMTOPTCMP1_);
					for (unsigned int i = 0; i < targetVar.size(); i++) {
						rewriter.InsertTextAfterToken(pvd->getLocEnd(), ABMTOPTCMPV1_ + to_string(i+1) +
																														ABMTOPTCMPV2_ + tType[i] +
																														ABMTOPTCMPV3_ + to_string(i+1) +
																														ABMTOPTCMPV4_ + tType[i]);

					}
					rewriter.InsertTextAfterToken(pvd->getLocEnd(), ABMTOPTCMP2_);
					for (unsigned int i = 0; i < targetVar.size(); i++) {
						rewriter.InsertTextAfterToken(pvd->getLocEnd(), ABMTOPTCMPV5_ + to_string(i+1) +
																														ABMTOPTCMPV6_ + tType[i] +
																														ABMTOPTCMPV7_ + to_string(i+1) +
																														ABMTOPTCMPV8_ + tType[i]);

					}
					rewriter.InsertTextAfterToken(pvd->getLocEnd(), ABMTOPTCMP3_);
					for (unsigned int i = 0; i < targetVar.size(); i++) {
						rewriter.InsertTextAfterToken(pvd->getLocEnd(), ABMTCMPVV1_ + to_string(i+1) + 
																														ABMTCMPVV2_ + to_string(i+1) +
																														ABMTCMPVV3_ + tType[i] +
																														ABMTCMPVV4_ + to_string(i+1) +
																														ABMTCMPVV5_);

					}
					rewriter.InsertTextAfterToken(pvd->getLocEnd(), ABMTOPTCMP4_);
					// voter
					for (unsigned int i = 0; i < targetVar.size(); i++) {
						rewriter.InsertTextAfterToken(pvd->getLocEnd(), ABMTVOTER1_ + to_string(i+1) +
																														ABMTVOTER2_ + to_string(i+1) +
																														ABMTVOTER3_ + to_string(i+1) +
																														ABMTVOTER4_ + to_string(i+1) +
																														ABMTVOTER5_);

					}
					rewriter.InsertTextAfterToken(pvd->getLocEnd(), ABMTOPTCMP5_);
					for (unsigned int i = 0; i < targetVar.size(); i++) {
						rewriter.InsertTextAfterToken(pvd->getLocEnd(), ABMTOPTFINISH1_ + to_string(i+1) +
																														ABMTOPTFINISH2_);
					}
					rewriter.InsertTextAfterToken(pvd->getLocEnd(), ABMTOPTCMP6_);
					// corrector
					rewriter.InsertTextAfterToken(pvd->getLocEnd(), ABMTCORRECTOR1_);
					for (unsigned int i = 0; i < targetVar.size(); i++) {
						rewriter.InsertTextAfterToken(pvd->getLocEnd(), ABMTCORRECTOR2_ + to_string(i+1) +
																														ABMTCORRECTOR3_ + to_string(i+1) +
																														ABMTCORRECTOR4_ + targetVar[i] +
																														ABMTCORRECTOR5_ + to_string(i+1) +
																														ABMTCORRECTOR6_);
					}
					rewriter.InsertTextAfterToken(pvd->getLocEnd(), ABMTCLOSEWRITE_);				
					for (unsigned int i = 0; i < depVar.size(); i++) {
						rewriter.InsertTextAfterToken(pvd->getLocEnd(), ABMTRDEPVAR1_ + depVar[i] +
																															 ABMTRDEPVAR2_ + depType[i] +
																															 ABMTRDEPVAR3_);
					}
					rewriter.InsertTextAfterToken(pvd->getLocEnd(), ABMTCLOSEPIPE_);
					rewriter.InsertTextAfterToken(pvd->getLocEnd(), ABMTFINISHFLAGS1_);
					rewriter.InsertTextAfterToken(pvd->getLocEnd(), ABMTOPTCMP7_);
					for (unsigned int i = 0; i < targetVar.size(); i++) {
						rewriter.InsertTextAfterToken(pvd->getLocEnd(), ABMTOPTFINISH3_ + to_string(i+1) +
																														ABMTOPTFINISH4_);
					}
					rewriter.InsertTextAfterToken(pvd->getLocEnd(), ABMTOPTCMP6_);					
					// corrector
					rewriter.InsertTextAfterToken(pvd->getLocEnd(), ABMTCORRECTOR1_);
					for (unsigned int i = 0; i < targetVar.size(); i++) {
						rewriter.InsertTextAfterToken(pvd->getLocEnd(), ABMTCORRECTOR2_ + to_string(i+1) +
																														ABMTCORRECTOR3_ + to_string(i+1) +
																														ABMTCORRECTOR4_ + targetVar[i] +
																														ABMTCORRECTOR5_ + to_string(i+1) +
																														ABMTCORRECTOR6_);
					}
					rewriter.InsertTextAfterToken(pvd->getLocEnd(), ABMTCLOSEWRITE_);
					for (unsigned int i = 0; i < depVar.size(); i++) {
						rewriter.InsertTextAfterToken(pvd->getLocEnd(), ABMTRDEPVAR1_ + depVar[i] +
																														ABMTRDEPVAR2_ + depType[i] +
																														ABMTRDEPVAR3_);
					}					
					rewriter.InsertTextAfterToken(pvd->getLocEnd(), ABMTCLOSEPIPE_);															
					rewriter.InsertTextAfterToken(pvd->getLocEnd(), ABMTFINISHFLAGS2_);
					rewriter.InsertTextAfterToken(pvd->getLocEnd(), ABMULTITHREAD3_);
				}

			// repeat mode	
			}	else if (MonitorMode.compare(mon2) == 0) { 
				// multiprocess
				if (voteMethod.compare(vm1) == 0) {
					rewriter.InsertTextAfterToken(pvd->getLBraceLoc(), RPMPVARS_);

					rewriter.InsertTextAfterToken(pvd->getLBraceLoc(), RPMPWHILE1_);	

					rewriter.InsertTextAfterToken(pvd->getLBraceLoc(), RPMPINIT_);					
					rewriter.InsertTextAfterToken(pvd->getLBraceLoc(), RPMULTIPROCESS1_);
					// receiver
					for (unsigned int i = 0; i < targetVar.size(); i++) {
						rewriter.InsertTextAfterToken(pvd->getLBraceLoc(), RPMPRECV1_ + to_string(i+1) +
																															 RPMPRECV2_ + to_string(i+1) +
																															 RPMPRECV3_ + tType[i] +
																															 RPMPRECV4_);
					}
					rewriter.InsertTextAfterToken(pvd->getLBraceLoc(), RPMULTIPROCESS2_);
					for (unsigned int i = 0; i < targetVar.size(); i++) {
						rewriter.InsertTextAfterToken(pvd->getLBraceLoc(), RPMPRECV5_ + to_string(i+1) +
																															 RPMPRECV6_ + to_string(i+1) +
																															 RPMPRECV7_ + tType[i] +
																															 RPMPRECV8_);
					}
					rewriter.InsertTextAfterToken(pvd->getLBraceLoc(), RPMULTIPROCESS3_);
					// voter variables
					for (unsigned int i = 0; i < targetVar.size(); i++) {
						rewriter.InsertTextAfterToken(pvd->getLBraceLoc(), RPMPVV1_ + targetType[i] +
																															 RPMPVV2_ + to_string(i+1) + 
																															 RPMPVV3_ + to_string(i+1) +
																															 RPMPVV4_);

					}
					// optimize compare
					rewriter.InsertTextAfterToken(pvd->getLBraceLoc(), RPMPOPTCMP1_);
					for (unsigned int i = 0; i < targetVar.size(); i++) {
						rewriter.InsertTextAfterToken(pvd->getLBraceLoc(), RPMPOPTCMPV1_ + to_string(i+1) +
																															 RPMPOPTCMPV2_ + tType[i] +
																															 RPMPOPTCMPV3_ + to_string(i+1) +
																															 RPMPOPTCMPV4_ + tType[i]);

					}
					rewriter.InsertTextAfterToken(pvd->getLBraceLoc(), RPMPOPTCMP2_);
					for (unsigned int i = 0; i < targetVar.size(); i++) {
						rewriter.InsertTextAfterToken(pvd->getLBraceLoc(), RPMPOPTCMPV5_ + to_string(i+1) +
																															 RPMPOPTCMPV6_ + tType[i] +
																															 RPMPOPTCMPV7_ + to_string(i+1) +
																															 RPMPOPTCMPV8_ + tType[i]);

					}
					rewriter.InsertTextAfterToken(pvd->getLBraceLoc(), RPMPOPTCMP3_);
					for (unsigned int i = 0; i < targetVar.size(); i++) {
						rewriter.InsertTextAfterToken(pvd->getLBraceLoc(), RPMPCMPVV1_ + to_string(i+1) + 
																															 RPMPCMPVV2_ + to_string(i+1) +
																															 RPMPCMPVV3_ + tType[i] +
																															 RPMPCMPVV4_ + to_string(i+1) +
																															 RPMPCMPVV5_);

					}
					rewriter.InsertTextAfterToken(pvd->getLBraceLoc(), RPMPOPTCMP4_);
					// voter
					for (unsigned int i = 0; i < targetVar.size(); i++) {
						rewriter.InsertTextAfterToken(pvd->getLBraceLoc(), RPMPVOTER1_ + to_string(i+1) +
																															 RPMPVOTER2_ + to_string(i+1) +
																															 RPMPVOTER3_ + to_string(i+1) +
																															 RPMPVOTER4_ + to_string(i+1) +
																															 RPMPVOTER5_);

					}
					rewriter.InsertTextAfterToken(pvd->getLBraceLoc(), RPMPOPTCMP5_);
					for (unsigned int i = 0; i < targetVar.size(); i++) {
						rewriter.InsertTextAfterToken(pvd->getLBraceLoc(), RPMPOPTFINISH1_ + to_string(i+1) +
																														 	 RPMPOPTFINISH2_);
					}
					rewriter.InsertTextAfterToken(pvd->getLBraceLoc(), RPMPOPTCMP6_);
					// corrector
					rewriter.InsertTextAfterToken(pvd->getLBraceLoc(), RPMPCORRECTOR1_);
					for (unsigned int i = 0; i < targetVar.size(); i++) {
						rewriter.InsertTextAfterToken(pvd->getLBraceLoc(), RPMPCORRECTOR2_ + to_string(i+1) +
																															 RPMPCORRECTOR3_ + to_string(i+1) +
																															 RPMPCORRECTOR4_ + targetVar[i] +
																															 RPMPCORRECTOR5_ + to_string(i+1) +
																															 RPMPCORRECTOR6_);
					}				
					for (unsigned int i = 0; i < depVar.size(); i++) {
						rewriter.InsertTextAfterToken(pvd->getLBraceLoc(), RPMPRDEPVAR1_ + depVar[i] +
																															 RPMPRDEPVAR2_ + depType[i] +
																															 RPMPRDEPVAR3_);
					}
					rewriter.InsertTextAfterToken(pvd->getLBraceLoc(), RPMPCLOSEPIPE_);
					rewriter.InsertTextAfterToken(pvd->getLBraceLoc(), RPMPFINISHFLAGS1_);
					rewriter.InsertTextAfterToken(pvd->getLBraceLoc(), RPMPOPTCMP7_);
					for (unsigned int i = 0; i < targetVar.size(); i++) {
						rewriter.InsertTextAfterToken(pvd->getLBraceLoc(), RPMPOPTFINISH1_ + to_string(i+1) +
																														 	 RPMPOPTFINISH2_);
					}
					rewriter.InsertTextAfterToken(pvd->getLBraceLoc(), RPMPOPTCMP6_);					
					// corrector
					rewriter.InsertTextAfterToken(pvd->getLBraceLoc(), RPMPCORRECTOR1_);
					for (unsigned int i = 0; i < targetVar.size(); i++) {
						rewriter.InsertTextAfterToken(pvd->getLBraceLoc(), RPMPCORRECTOR2_ + to_string(i+1) +
																															 RPMPCORRECTOR3_ + to_string(i+1) +
																															 RPMPCORRECTOR4_ + targetVar[i] +
																															 RPMPCORRECTOR5_ + to_string(i+1) +
																															 RPMPCORRECTOR6_);
					}
					for (unsigned int i = 0; i < depVar.size(); i++) {
						rewriter.InsertTextAfterToken(pvd->getLBraceLoc(), RPMPRDEPVAR1_ + depVar[i] +
																															 RPMPRDEPVAR2_ + depType[i] +
																															 RPMPRDEPVAR3_);
					}					
					rewriter.InsertTextAfterToken(pvd->getLBraceLoc(), RPMPCLOSEPIPE_);															
					rewriter.InsertTextAfterToken(pvd->getLBraceLoc(), RPMPFINISHFLAGS2_);
					rewriter.InsertTextAfterToken(pvd->getLBraceLoc(), RPMULTIPROCESS4_);

					// RBrace
					for (unsigned int i = 0; i < targetVar.size(); i++) {
						rewriter.InsertTextAfterToken(pvd->getLocEnd(), RPMPWTARGETVAR1_ + targetVar[i] +
																													  RPMPWTARGETVAR2_ + targetType[i] +
																													  RPMPWTARGETVAR3_);
					}
					for (unsigned int i = 0; i < depVar.size(); i++) {
						rewriter.InsertTextAfterToken(pvd->getLocEnd(), RPMPWDEPVAR1_ + depVar[i] + 
																														RPMPWDEPVAR2_ + depType[i] +
																														RPMPWDEPVAR3_);
					}
					rewriter.InsertTextAfterToken(pvd->getLocEnd(), RPMULTIPROCESS5_);
					rewriter.InsertTextAfterToken(pvd->getLocEnd(), RPMPWHILE2_);													
				} else if (voteMethod.compare(vm2) == 0) {
					rewriter.InsertTextAfterToken(pvd->getLBraceLoc(), RPSEQVARS_);
					rewriter.InsertTextAfterToken(pvd->getLBraceLoc(), RPSEQWHILE1_);
					rewriter.InsertTextAfterToken(pvd->getLBraceLoc(), RPSEQUENTIAL1_);
					// receiver
					for (unsigned int i = 0; i < targetVar.size(); i++) {
						rewriter.InsertTextAfterToken(pvd->getLBraceLoc(), RPSEQRECV1_ + to_string(i+1) +
																															 RPSEQRECV2_ + to_string(i+1) +
																															 RPSEQRECV3_ + tType[i] +
																															 RPSEQRECV4_);
					}
					rewriter.InsertTextAfterToken(pvd->getLBraceLoc(), RPSEQUENTIAL2_);
					for (unsigned int i = 0; i < targetVar.size(); i++) {
						rewriter.InsertTextAfterToken(pvd->getLBraceLoc(), RPSEQRECV5_ + to_string(i+1) +
																															 RPSEQRECV6_ + to_string(i+1) +
																															 RPSEQRECV7_ + tType[i] +
																															 RPSEQRECV8_);
					}
					rewriter.InsertTextAfterToken(pvd->getLBraceLoc(), RPSEQUENTIAL3_);
					// voter variables
					for (unsigned int i = 0; i < targetVar.size(); i++) {
						rewriter.InsertTextAfterToken(pvd->getLBraceLoc(), RPSEQVV1_ + targetType[i] +
																															 RPSEQVV2_ + to_string(i+1) +
																															 RPSEQVV3_ + to_string(i+1) +
																															 RPSEQVV4_);

					}
					// optimize compare
					rewriter.InsertTextAfterToken(pvd->getLBraceLoc(), RPSEQOPTCMP1_);
					for (unsigned int i = 0; i < targetVar.size(); i++) {
						rewriter.InsertTextAfterToken(pvd->getLBraceLoc(), RPSEQOPTCMPV1_ + to_string(i+1) +
																															 RPSEQOPTCMPV2_ + tType[i] +
																															 RPSEQOPTCMPV3_ + to_string(i+1) +
																															 RPSEQOPTCMPV4_ + tType[i]);

					}
					rewriter.InsertTextAfterToken(pvd->getLBraceLoc(), RPSEQOPTCMP2_);
					for (unsigned int i = 0; i < targetVar.size(); i++) {
						rewriter.InsertTextAfterToken(pvd->getLBraceLoc(), RPSEQOPTCMPV5_ + to_string(i+1) +
																															 RPSEQOPTCMPV6_ + tType[i] +
																															 RPSEQOPTCMPV7_ + to_string(i+1) +
																															 RPSEQOPTCMPV8_ + tType[i]);

					}
					rewriter.InsertTextAfterToken(pvd->getLBraceLoc(), RPSEQOPTCMP3_);
					for (unsigned int i = 0; i < targetVar.size(); i++) {
						rewriter.InsertTextAfterToken(pvd->getLBraceLoc(), RPSEQCMPVV1_ + to_string(i+1) +
																															 RPSEQCMPVV2_ + to_string(i+1) +
																															 RPSEQCMPVV3_ + tType[i] +
																															 RPSEQCMPVV4_ + to_string(i+1) +
																															 RPSEQCMPVV5_);

					}
					rewriter.InsertTextAfterToken(pvd->getLBraceLoc(), RPSEQOPTCMP4_);
					// voter
					for (unsigned int i = 0; i < targetVar.size(); i++) {
						rewriter.InsertTextAfterToken(pvd->getLBraceLoc(), RPSEQVOTER1_ + to_string(i+1) +
																															 RPSEQVOTER2_ + to_string(i+1) +
																															 RPSEQVOTER3_ + to_string(i+1) +
																															 RPSEQVOTER4_ + to_string(i+1) +
																															 RPSEQVOTER5_);

					}
					rewriter.InsertTextAfterToken(pvd->getLBraceLoc(), RPSEQOPTCMP5_);
					for (unsigned int i = 0; i < targetVar.size(); i++) {
						rewriter.InsertTextAfterToken(pvd->getLBraceLoc(), RPSEQOPTFINISH1_ + to_string(i+1) +
																														 	 RPSEQOPTFINISH2_);
					}
					rewriter.InsertTextAfterToken(pvd->getLBraceLoc(), RPSEQOPTCMP6_);
					// corrector
					rewriter.InsertTextAfterToken(pvd->getLBraceLoc(), RPSEQCORRECTOR1_);
					for (unsigned int i = 0; i < targetVar.size(); i++) {
						rewriter.InsertTextAfterToken(pvd->getLBraceLoc(), RPSEQCORRECTOR2_ + to_string(i+1) +
																															 RPSEQCORRECTOR3_ + to_string(i+1) +
																															 RPSEQCORRECTOR4_ + targetVar[i] +
																															 RPSEQCORRECTOR5_ + to_string(i+1) +
																															 RPSEQCORRECTOR6_);
					}
					for (unsigned int i = 0; i < depVar.size(); i++) {
						rewriter.InsertTextAfterToken(pvd->getLBraceLoc(), RPSEQRDEPVAR1_ + depVar[i] +
																															 RPSEQRDEPVAR2_ + depType[i] +
																															 RPSEQRDEPVAR3_);
					}
					rewriter.InsertTextAfterToken(pvd->getLBraceLoc(), RPSEQCLOSEPIPE_);
					rewriter.InsertTextAfterToken(pvd->getLBraceLoc(), RPSEQFINISHFLAGS1_);
					rewriter.InsertTextAfterToken(pvd->getLBraceLoc(), RPSEQOPTCMP7_);
					for (unsigned int i = 0; i < targetVar.size(); i++) {
						rewriter.InsertTextAfterToken(pvd->getLBraceLoc(), RPSEQOPTFINISH3_ + to_string(i+1) +
																														 	 RPSEQOPTFINISH4_);
					}
					rewriter.InsertTextAfterToken(pvd->getLBraceLoc(), RPSEQOPTCMP6_);
					// corrector
					rewriter.InsertTextAfterToken(pvd->getLBraceLoc(), RPSEQCORRECTOR1_);
					for (unsigned int i = 0; i < targetVar.size(); i++) {
						rewriter.InsertTextAfterToken(pvd->getLBraceLoc(), RPSEQCORRECTOR2_ + to_string(i+1) +
																															 RPSEQCORRECTOR3_ + to_string(i+1) +
																															 RPSEQCORRECTOR4_ + targetVar[i] +
																															 RPSEQCORRECTOR5_ + to_string(i+1) +
																															 RPSEQCORRECTOR6_);
					}
					for (unsigned int i = 0; i < depVar.size(); i++) {
						rewriter.InsertTextAfterToken(pvd->getLBraceLoc(), RPSEQRDEPVAR1_ + depVar[i] +
																															 RPSEQRDEPVAR2_ + depType[i] +
																															 RPSEQRDEPVAR3_);
					}
					rewriter.InsertTextAfterToken(pvd->getLBraceLoc(), RPSEQCLOSEPIPE_);
					rewriter.InsertTextAfterToken(pvd->getLBraceLoc(), RPSEQFINISHFLAGS2_);
					rewriter.InsertTextAfterToken(pvd->getLBraceLoc(), RPSEQUENTIAL4_);

					// RBrace
					for (unsigned int i = 0; i < targetVar.size(); i++) {
						rewriter.InsertTextAfterToken(pvd->getLocEnd(), RPSEQWTARGETVAR1_ + targetVar[i] +
																													  RPSEQWTARGETVAR2_ + targetType[i] +
																													  RPSEQWTARGETVAR3_);
					}
					for (unsigned int i = 0; i < depVar.size(); i++) {
						rewriter.InsertTextAfterToken(pvd->getLocEnd(), RPSEQWDEPVAR1_ + depVar[i] +
																														RPSEQWDEPVAR2_ + depType[i] +
																														RPSEQWDEPVAR3_);
					}
					rewriter.InsertTextAfterToken(pvd->getLocEnd(), RPSEQUENTIAL5_);
					rewriter.InsertTextAfterToken(pvd->getLocEnd(), RPSEQWHILE2_);

				} else if (voteMethod.compare(vm3) == 0) {
					rewriter.InsertTextAfterToken(pvd->getLBraceLoc(), RPMTVARS_);
					rewriter.InsertTextAfterToken(pvd->getLBraceLoc(), RPMTWHILE1_);			
					rewriter.InsertTextAfterToken(pvd->getLBraceLoc(), RPMULTITHREAD1_);

					// RBrace
					rewriter.InsertTextAfterToken(pvd->getLocEnd(), RPMTRECV1_);
					for (unsigned int i = 0; i < targetVar.size(); i++) {
						rewriter.InsertTextAfterToken(pvd->getLocEnd(), RPMTRECV2_ + to_string(i+1) + 
																														RPMTRECV3_ + tType[i] + 
																														RPMTRECV4_ + targetVar[i] +
																														RPMTRECV5_);
					}
					rewriter.InsertTextAfterToken(pvd->getLocEnd(), RPMTCLOSEREAD_);					
					rewriter.InsertTextAfterToken(pvd->getLocEnd(), RPMTWDEPVAR1_);
					for (unsigned int i = 0; i < depVar.size(); i++) {
						rewriter.InsertTextAfterToken(pvd->getLocEnd(), RPMTWDEPVAR2_ + depVar[i] +
																														RPMTWDEPVAR3_ + depType[i] +
																														RPMTWDEPVAR4_);
					}
					rewriter.InsertTextAfterToken(pvd->getLocEnd(), RPMULTITHREAD2_);

					// voter variables
					for (unsigned int i = 0; i < targetVar.size(); i++) {
						rewriter.InsertTextAfterToken(pvd->getLocEnd(), RPMTVV1_ + targetType[i] +
																														RPMTVV2_ + to_string(i+1) + 
																														RPMTVV3_ + to_string(i+1) +
																														RPMTVV4_);

					}
					// optimize compare
					rewriter.InsertTextAfterToken(pvd->getLocEnd(), RPMTOPTCMP1_);
					for (unsigned int i = 0; i < targetVar.size(); i++) {
						rewriter.InsertTextAfterToken(pvd->getLocEnd(), RPMTOPTCMPV1_ + to_string(i+1) +
																														RPMTOPTCMPV2_ + tType[i] +
																														RPMTOPTCMPV3_ + to_string(i+1) +
																														RPMTOPTCMPV4_ + tType[i]);

					}
					rewriter.InsertTextAfterToken(pvd->getLocEnd(), RPMTOPTCMP2_);
					for (unsigned int i = 0; i < targetVar.size(); i++) {
						rewriter.InsertTextAfterToken(pvd->getLocEnd(), RPMTOPTCMPV5_ + to_string(i+1) +
																														RPMTOPTCMPV6_ + tType[i] +
																														RPMTOPTCMPV7_ + to_string(i+1) +
																														RPMTOPTCMPV8_ + tType[i]);

					}
					rewriter.InsertTextAfterToken(pvd->getLocEnd(), RPMTOPTCMP3_);
					for (unsigned int i = 0; i < targetVar.size(); i++) {
						rewriter.InsertTextAfterToken(pvd->getLocEnd(), RPMTCMPVV1_ + to_string(i+1) + 
																														RPMTCMPVV2_ + to_string(i+1) +
																														RPMTCMPVV3_ + tType[i] +
																														RPMTCMPVV4_ + to_string(i+1) +
																														RPMTCMPVV5_);

					}
					rewriter.InsertTextAfterToken(pvd->getLocEnd(), RPMTOPTCMP4_);
					// voter
					for (unsigned int i = 0; i < targetVar.size(); i++) {
						rewriter.InsertTextAfterToken(pvd->getLocEnd(), RPMTVOTER1_ + to_string(i+1) +
																														RPMTVOTER2_ + to_string(i+1) +
																														RPMTVOTER3_ + to_string(i+1) +
																														RPMTVOTER4_ + to_string(i+1) +
																													 	RPMTVOTER5_);

					}
					rewriter.InsertTextAfterToken(pvd->getLocEnd(), RPMTOPTCMP5_);
					for (unsigned int i = 0; i < targetVar.size(); i++) {
						rewriter.InsertTextAfterToken(pvd->getLocEnd(), RPMTOPTFINISH1_ + to_string(i+1) +
																														RPMTOPTFINISH2_);
					}
					rewriter.InsertTextAfterToken(pvd->getLocEnd(), RPMTOPTCMP6_);
					// corrector
					rewriter.InsertTextAfterToken(pvd->getLocEnd(), RPMTCORRECTOR1_);
					for (unsigned int i = 0; i < targetVar.size(); i++) {
						rewriter.InsertTextAfterToken(pvd->getLocEnd(), RPMTCORRECTOR2_ + to_string(i+1) +
																														RPMTCORRECTOR3_ + to_string(i+1) +
																														RPMTCORRECTOR4_ + targetVar[i] +
																														RPMTCORRECTOR5_ + to_string(i+1) +
																														RPMTCORRECTOR6_);
					}
					rewriter.InsertTextAfterToken(pvd->getLocEnd(), RPMTCLOSEWRITE_);				
					for (unsigned int i = 0; i < depVar.size(); i++) {
						rewriter.InsertTextAfterToken(pvd->getLocEnd(), RPMTRDEPVAR1_ + depVar[i] +
																														RPMTRDEPVAR2_ + depType[i] +
																														RPMTRDEPVAR3_);
					}
					rewriter.InsertTextAfterToken(pvd->getLocEnd(), RPMTCLOSEPIPE_);
					rewriter.InsertTextAfterToken(pvd->getLocEnd(), RPMTFINISHFLAGS1_);
					rewriter.InsertTextAfterToken(pvd->getLocEnd(), RPMTOPTCMP7_);
					for (unsigned int i = 0; i < targetVar.size(); i++) {
						rewriter.InsertTextAfterToken(pvd->getLocEnd(), RPMTOPTFINISH3_ + to_string(i+1) +
																														 	 RPMTOPTFINISH4_);
					}
					rewriter.InsertTextAfterToken(pvd->getLocEnd(), RPMTOPTCMP6_);					
					// corrector
					rewriter.InsertTextAfterToken(pvd->getLocEnd(), RPMTCORRECTOR1_);
					for (unsigned int i = 0; i < targetVar.size(); i++) {
						rewriter.InsertTextAfterToken(pvd->getLocEnd(), RPMTCORRECTOR2_ + to_string(i+1) +
																														RPMTCORRECTOR3_ + to_string(i+1) +
																														RPMTCORRECTOR4_ + targetVar[i] +
																														RPMTCORRECTOR5_ + to_string(i+1) +
																														RPMTCORRECTOR6_);
					}
					rewriter.InsertTextAfterToken(pvd->getLocEnd(), RPMTCLOSEWRITE_);
					for (unsigned int i = 0; i < depVar.size(); i++) {
						rewriter.InsertTextAfterToken(pvd->getLocEnd(), RPMTRDEPVAR1_ + depVar[i] +
																														RPMTRDEPVAR2_ + depType[i] +
																														RPMTRDEPVAR3_);
					}					
					rewriter.InsertTextAfterToken(pvd->getLocEnd(), RPMTCLOSEPIPE_);															
					rewriter.InsertTextAfterToken(pvd->getLocEnd(), RPMTFINISHFLAGS2_);
					rewriter.InsertTextAfterToken(pvd->getLocEnd(), RPMULTITHREAD3_);
					rewriter.InsertTextAfterToken(pvd->getLocEnd(), RPMTWHILE2_);									
				}
			}
		}
        return true;
	}

	// Comment by Y-Wen
	// Insert includes, defines, and struct
    virtual bool VisitFunctionDecl(FunctionDecl *func) {

    string funcName = func->getNameInfo().getName().getAsString();

		if(funcName =="main") {	
			S = func->getSourceRange().getBegin();
			E = func->getSourceRange().getEnd(); 
			E = E.getLocWithOffset(1);
		}

		/*
		//------2017/11/14------//
		if (func->hasBody()) { 
			if (func->isVoteFunction()) {}
		}*/
		//------2017/11/14------//  
        return true;
    }
		/*
    virtual bool VisitStmt(Stmt *st) {
 
        if (ReturnStmt *ret = dyn_cast<ReturnStmt>(st)) {}        
        if (CallExpr *call = dyn_cast<CallExpr>(st)) {}
     
        return true;
    }
		*/
};

class VoteASTConsumer : public ASTConsumer {
private:
    VoteVisitor *visitor; // doesn't have to be private

public:
    // override the constructor in order to pass CI
    explicit VoteASTConsumer(CompilerInstance *CI): visitor(new VoteVisitor(CI)) {}// initialize the visitor

    // override this to call our VoteVisitor on the entire source file
    virtual void HandleTranslationUnit(ASTContext &Context) {
        /* we can use ASTContext to get the TranslationUnitDecl, which is
             a single Decl that collectively represents the entire source file */
        visitor->TraverseDecl(Context.getTranslationUnitDecl());
    }
};

class VoteFrontendAction : public ASTFrontendAction {
public:
    VoteFrontendAction() {}

    //Note that unique pointer is used.
    virtual std::unique_ptr<ASTConsumer> CreateASTConsumer(CompilerInstance &CI, StringRef file) {
        return  llvm::make_unique<VoteASTConsumer>(&CI); // pass CI pointer to ASTConsumer
    }
};

int main(int argc, const char **argv) {

    // parse the parameters
    arg_parse(argc, argv);

    // parse the command-line args passed to your code
    CommonOptionsParser op(argc, argv, StatCategory);        
    // create a new Clang Tool instance (a LibTooling environment)
    ClangTool Tool(op.getCompilations(), op.getSourcePathList());

    // run the Clang Tool, creating a new FrontendAction (explained below)
    int result = Tool.run(newFrontendActionFactory<VoteFrontendAction>().get());

	//errs() << "\nFound " << numFunctions << " functions.\n\n";
    // print out the rewritten source code ("rewriter" is a global var.)
    rewriter.getEditBuffer(rewriter.getSourceMgr().getMainFileID()).write(outs());	//errs() can't output to file
    return result;
}
