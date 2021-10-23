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
#include "for_model.h"
#include "omp_model.h"
#include "multi_fork_model.h"

#include "abnormal_model.h"
#include "repeat_model.h"

#include "repeat_for.h"
#include "repeat_omp_voteinchd.h"
#include "repeat_multi_fork_model.h"

#include "abnormal_for.h"
#include "abnormal_omp_voteinchd.h"
#include "abnormal_multi_fork.h"

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
//errs() << a << g_argv[a] << "\n";
    }  
}

int numFunctions = 0;

string vote_TYPE;


static llvm::cl::OptionCategory StatCategory("For_Fork");

class VoteVisitor : public RecursiveASTVisitor<VoteVisitor> {
private:
    ASTContext *astContext; // get additional AST info

public:
    explicit VoteVisitor(CompilerInstance *CI): astContext(&(CI->getASTContext())) {  // initialize private members
        rewriter.setSourceMgr(astContext->getSourceManager(), astContext->getLangOpts());
    }



 virtual bool VisitPragmaVoteDecl(PragmaVoteDecl *pvd){

errs() << "VisitPragmaVoteDecl  " << "\t"<< numFunctions <<"\n";

	string voteName = pvd->getName();//.getAsString(); //pvd.getName().getAsString();
	errs() << "==> VOTE pragma: " << voteName << "\n";

    string voteType = pvd->getVoteType();//.getAsString();
	errs() << "==> VOTE type: " << voteType << "\n";
	vote_TYPE = vote_TYPE + voteType;

	string vType;
		 if((voteType.compare("int"))==0){	vType = vType + "i";}
	else if ((voteType.compare("float"))==0){	vType = vType + "f";}
	else if ((voteType.compare("short"))==0){	vType = vType + "s";}
	else if ((voteType.compare("double"))==0){	vType = vType + "d";}
	else if ((voteType.compare("long"))==0){	vType = vType + "l";}
	else if ((voteType.compare("char"))==0){	vType = vType + "c";}
	errs() << "==> vType: " << vType << "\n";

	vector <string> depVar = pvd->getDep();
	for(int i=0; i <depVar.size() ; i++)
	errs() << "==> DEP var: " << depVar.size() << "\t" << depVar[i] << "\n";//<< "\t" << depVar[1] << "\n";

	vector <string> depType = pvd->getDepType();
	for(int i=0; i <depType.size() ; i++)
	errs() << "==> DEP Type: " << depType.size() << "\t" << depType[i] << "\n";//<< "\t" << depType[1] << "\n";

	string voteMethod = pvd->getVoteMethod();//.getAsString();
	errs() << "==> VOTE Method: " << voteMethod << "\n";
	//voteMethod = voteMethod + voteType;

    string MonitorMode = pvd->getMonitorMode(); //the first argument,MAY be MonitorMode, OR max time limit.
	errs() << "==> MONITOR MaxTimeLimit: " << MonitorMode << "\n";

    string MaxTimeLimit = pvd->getMaxTimeLimit(); //the second argument,it's MonitorMode, NOT max time limit.
	errs() << "==> MONITOR mode: " << MaxTimeLimit << "\n";


	//--------------  Monitor_Vote Set --------------//
	if((voteMethod.compare(""))!=0 && (MonitorMode.compare(""))!=0)
	{
		errs() << "==> MONITOR_VOTE set: "<< voteMethod << "\t"<< MonitorMode << "\n";

		SourceLocation SW =  pvd->getLocation();
		rewriter.ReplaceText(SW.getLocWithOffset(-8),"//");
		rewriter.ReplaceText(pvd->getLBraceLoc()," "); //delete "{" 
		rewriter.InsertTextBefore(pvd->getRBraceLoc(),"\n//*** ENDD_____\t\t");

		string mon1("repeat");
		string mon2("abnormal");

		string vm1("seq");
		string vm2("multithread");
		string vm3("multiprocess");

		if((MonitorMode.compare(mon1))==0) //***  repeat mode ***//
		{
			//-- seq --//
			if((voteMethod.compare(vm1))==0) 
			{

					rewriter.InsertTextAfterToken(pvd->getLBraceLoc(),RPFORWHILE1_);
					rewriter.InsertTextAfterToken(pvd->getLBraceLoc(),vType+", sizeof("+voteType);
					rewriter.InsertTextAfterToken(pvd->getLBraceLoc(),RPFORWHILE2_+vType);
					rewriter.InsertTextAfterToken(pvd->getLBraceLoc(),RPFORWHILE3_);

					rewriter.InsertTextAfterToken(pvd->getLBraceLoc(),RPFORMJRTY1_+voteType);
					rewriter.InsertTextAfterToken(pvd->getLBraceLoc(),RPFORMJRTY2_+vType);
					rewriter.InsertTextAfterToken(pvd->getLBraceLoc(),RPFORMJRTY3_+vType);
					rewriter.InsertTextAfterToken(pvd->getLBraceLoc(),RPFORMJRTY4_+vType);
					rewriter.InsertTextAfterToken(pvd->getLBraceLoc(),RPFORMJRTY5_);

				if(depVar.size()!=0){
					//rewriter.InsertTextBefore(pvd->getLocEnd(),DERPREAD5_);
					for(int i=depVar.size()-1; i >= 0; i--){
						rewriter.InsertTextAfterToken(pvd->getLBraceLoc(),ABDERPREAD2_ + depVar[i]);
						rewriter.InsertTextAfterToken(pvd->getLBraceLoc(),ABDERPREAD3_);
						rewriter.InsertTextAfterToken(pvd->getLBraceLoc(),depType[i]);  //depType
						rewriter.InsertTextAfterToken(pvd->getLBraceLoc(),ABDERPREAD4_);
					}
					//rewriter.InsertTextBefore(pvd->getLocEnd(),DERPREAD_);
				}

					rewriter.InsertTextAfterToken(pvd->getLBraceLoc(),RPFORMJRTY6_);
					rewriter.InsertTextAfterToken(pvd->getLBraceLoc(),RPFORWHILE4_);
					rewriter.InsertTextAfterToken(pvd->getLBraceLoc(),RPFORWHILE5_);

			//reverse

					rewriter.InsertTextBefore(pvd->getLocEnd(),RPFOREND_);

				if(depVar.size()!=0){
					for(int i=0; i <depVar.size() ; i++){
						rewriter.InsertTextBefore(pvd->getLocEnd(),ABDEPWRITE4_);
						rewriter.InsertTextBefore(pvd->getLocEnd(),depType[i]); //depType
						rewriter.InsertTextBefore(pvd->getLocEnd(),ABDEPWRITE3_);
						rewriter.InsertTextBefore(pvd->getLocEnd(),ABDEPWRITE2_ + depVar[i] );
					}
				}
					rewriter.InsertTextBefore(pvd->getLocEnd(),voteName+", sizeof("+voteType+"));\n\n");
					rewriter.InsertTextBefore(pvd->getLocEnd(),";\n\t\t\twrite(pipe_fd_Voter[1], &");
					rewriter.InsertTextBefore(pvd->getLocEnd(),vType+" = "+voteName);
					rewriter.InsertTextBefore(pvd->getLocEnd(),RPFORWHILE6_);
			}
			//-- seq END --//
			//-- multithread --//
			else if((voteMethod.compare(vm2))==0) 
			{
					rewriter.InsertTextAfterToken(pvd->getLBraceLoc(),RPOMPINITIAL_);
					rewriter.InsertTextAfterToken(pvd->getLBraceLoc(),vType+", sizeof("+voteType);
					rewriter.InsertTextAfterToken(pvd->getLBraceLoc(),"));\n\t\t\t\tresult = data_Voter->"+vType);
					rewriter.InsertTextAfterToken(pvd->getLBraceLoc(),RPOMPWHILE1_);

			if(depVar.size()!=0){
				//rewriter.InsertTextBefore(pvd->getLocEnd(),DERPREAD5_);
				for(int i=depVar.size()-1; i >= 0; i--){
					rewriter.InsertTextAfterToken(pvd->getLBraceLoc(),ABDERPREAD2_ + depVar[i]);
					rewriter.InsertTextAfterToken(pvd->getLBraceLoc(),ABDERPREAD3_);
					rewriter.InsertTextAfterToken(pvd->getLBraceLoc(),depType[i]);  //depType
					rewriter.InsertTextAfterToken(pvd->getLBraceLoc(),ABDERPREAD4_);
				}
				//rewriter.InsertTextBefore(pvd->getLocEnd(),DERPREAD_);
			}

					rewriter.InsertTextAfterToken(pvd->getLBraceLoc(),RPOMPWHILE1PART2_);
					rewriter.InsertTextAfterToken(pvd->getLBraceLoc(),RPOMPWHILE2_);

			//reverse

					rewriter.InsertTextBefore(pvd->getLocEnd(),RPOMPEND_);

			if(depVar.size()!=0){
				//rewriter.InsertTextBefore(pvd->getLocEnd(),DEPWRITE5_);
				for(int i=0; i <depVar.size() ; i++){
					rewriter.InsertTextBefore(pvd->getLocEnd(),ABDEPWRITE4_);
					rewriter.InsertTextBefore(pvd->getLocEnd(),depType[i]); //depType
					rewriter.InsertTextBefore(pvd->getLocEnd(),ABDEPWRITE3_);
					rewriter.InsertTextBefore(pvd->getLocEnd(),ABDEPWRITE2_ + depVar[i] );
				}
				//rewriter.InsertTextBefore(pvd->getLocEnd(),DEPWRITE_);
			}

					rewriter.InsertTextBefore(pvd->getLocEnd(),RPOMPMJRTY6_);
					rewriter.InsertTextBefore(pvd->getLocEnd(),RPOMPMJRTY5_);
					rewriter.InsertTextBefore(pvd->getLocEnd(),RPOMPMJRTY4_+vType);
					rewriter.InsertTextBefore(pvd->getLocEnd(),RPOMPMJRTY3_+vType);
					rewriter.InsertTextBefore(pvd->getLocEnd(),RPOMPMJRTY2_+vType);
					rewriter.InsertTextBefore(pvd->getLocEnd(),RPOMPMJRTY1_+voteType);

					rewriter.InsertTextBefore(pvd->getLocEnd(),vType+" = "+voteName);
					rewriter.InsertTextBefore(pvd->getLocEnd(),RPOMPWHILE3_);

			}
			//-- multithread END --//
			//-- multiprocess --//
			else if((voteMethod.compare(vm3))==0) 
			{
					rewriter.InsertTextAfterToken(pvd->getLBraceLoc(),RPMFINITIAL_);
					rewriter.InsertTextAfterToken(pvd->getLBraceLoc(),RPMFWHILE1_);
					rewriter.InsertTextAfterToken(pvd->getLBraceLoc(),vType+", sizeof("+voteType);
					rewriter.InsertTextAfterToken(pvd->getLBraceLoc(),"));\n\t\t\t\t\tprintf(\"\\n\\trecv:%");
					rewriter.InsertTextAfterToken(pvd->getLBraceLoc(),vType+", process_num:%d\\n\\n\",data[process_num].");
					rewriter.InsertTextAfterToken(pvd->getLBraceLoc(),vType+", process_num);\n\t\t\t\t}");

					rewriter.InsertTextAfterToken(pvd->getLBraceLoc(),RPMFMJRTY1_+voteType);
					rewriter.InsertTextAfterToken(pvd->getLBraceLoc(),RPMFMJRTY2_+vType);
					rewriter.InsertTextAfterToken(pvd->getLBraceLoc(),RPMFMJRTY3_+vType);
					rewriter.InsertTextAfterToken(pvd->getLBraceLoc(),RPMFMJRTY4_+vType);
					rewriter.InsertTextAfterToken(pvd->getLBraceLoc(),RPMFMJRTY5_);
					rewriter.InsertTextAfterToken(pvd->getLBraceLoc(),voteName+RPMFMJRTY6_);

			if(depVar.size()!=0){
				//rewriter.InsertTextBefore(pvd->getLocEnd(),DERPREAD5_);
				for(int i=depVar.size()-1; i >= 0; i--){
					rewriter.InsertTextAfterToken(pvd->getLBraceLoc(),ABDERPREAD2_ + depVar[i]);
					rewriter.InsertTextAfterToken(pvd->getLBraceLoc(),ABDERPREAD3_);
					rewriter.InsertTextAfterToken(pvd->getLBraceLoc(),depType[i]);  //depType
					rewriter.InsertTextAfterToken(pvd->getLBraceLoc(),ABDERPREAD4_);
				}
				//rewriter.InsertTextBefore(pvd->getLocEnd(),DERPREAD_);
			}

					rewriter.InsertTextAfterToken(pvd->getLBraceLoc(),RPMFMJRTY7_);
					rewriter.InsertTextAfterToken(pvd->getLBraceLoc(),RPMFWHILE2_);
					rewriter.InsertTextAfterToken(pvd->getLBraceLoc(),RPMFCHD_);

			//reverse

					rewriter.InsertTextBefore(pvd->getLocEnd(),RPMFEND_);

			if(depVar.size()!=0){
				//rewriter.InsertTextBefore(pvd->getLocEnd(),DEPWRITE5_);
				for(int i=0; i <depVar.size() ; i++){
					rewriter.InsertTextBefore(pvd->getLocEnd(),ABDEPWRITE4_);
					rewriter.InsertTextBefore(pvd->getLocEnd(),depType[i]); //depType
					rewriter.InsertTextBefore(pvd->getLocEnd(),ABDEPWRITE3_);
					rewriter.InsertTextBefore(pvd->getLocEnd(),ABDEPWRITE2_ + depVar[i] );
				}
				//rewriter.InsertTextBefore(pvd->getLocEnd(),DEPWRITE_);
			}

					rewriter.InsertTextBefore(pvd->getLocEnd(),"\n\t\t\twrite(pipe_fd_Voter2[1], &"+voteName+", sizeof("+voteType+"));");
					rewriter.InsertTextBefore(pvd->getLocEnd(),vType+" = "+voteName+";");
					rewriter.InsertTextBefore(pvd->getLocEnd(),RPMFCHD2_);

			}
			//-- multiprocess END --//
		}
		//***  repeat mode END ***//

		//***  abnormal mode ***//
		else if((MaxTimeLimit.compare(mon2))==0) 
		{
			//-- seq --//
			if((voteMethod.compare(vm1))==0) 
			{

					rewriter.InsertTextAfterToken(pvd->getLBraceLoc(),ABFORINITIAL_);
					rewriter.InsertTextAfterToken(pvd->getLBraceLoc(),ABFORFORPART1_+MonitorMode);
					rewriter.InsertTextAfterToken(pvd->getLBraceLoc(),ABFORFORPART2_);
					rewriter.InsertTextAfterToken(pvd->getLBraceLoc(),vType+", sizeof("+voteType);
					rewriter.InsertTextAfterToken(pvd->getLBraceLoc(),ABFORFORPART3_);

					rewriter.InsertTextAfterToken(pvd->getLBraceLoc(),ABFORMJRTY1_+voteType);
					rewriter.InsertTextAfterToken(pvd->getLBraceLoc(),ABFORMJRTY2_+vType);
					rewriter.InsertTextAfterToken(pvd->getLBraceLoc(),ABFORMJRTY3_+vType);
					rewriter.InsertTextAfterToken(pvd->getLBraceLoc(),ABFORMJRTY4_+vType);
					rewriter.InsertTextAfterToken(pvd->getLBraceLoc(),ABFORMJRTY5_+voteName);
					rewriter.InsertTextAfterToken(pvd->getLBraceLoc(),ABFORMJRTY6_);

				if(depVar.size()!=0){
					for(int i=depVar.size()-1; i >= 0; i--){
						rewriter.InsertTextAfterToken(pvd->getLBraceLoc(),ABDERPREAD2_ + depVar[i]);
						rewriter.InsertTextAfterToken(pvd->getLBraceLoc(),ABDERPREAD3_);
						rewriter.InsertTextAfterToken(pvd->getLBraceLoc(),depType[i]);  //depType
						rewriter.InsertTextAfterToken(pvd->getLBraceLoc(),ABDERPREAD4_);
					}
				}
					rewriter.InsertTextAfterToken(pvd->getLBraceLoc(),ABFORMJRTY7_);
					rewriter.InsertTextAfterToken(pvd->getLBraceLoc(),ABFORCHD_);

			//reverse

					rewriter.InsertTextBefore(pvd->getLocEnd(),ABFOREND_);
				if(depVar.size()!=0){
					for(int i=0; i <depVar.size() ; i++){
						rewriter.InsertTextBefore(pvd->getLocEnd(),ABDEPWRITE4_);
						rewriter.InsertTextBefore(pvd->getLocEnd(),depType[i]); //depType
						rewriter.InsertTextBefore(pvd->getLocEnd(),ABDEPWRITE3_);
						rewriter.InsertTextBefore(pvd->getLocEnd(),ABDEPWRITE2_ + depVar[i] );
					}
				}
					rewriter.InsertTextBefore(pvd->getLocEnd(),"\n\t\twrite(pipe_fd_Voter[1], &"+voteName+", sizeof("+voteType+"));");
					rewriter.InsertTextBefore(pvd->getLocEnd(),vType+" = "+voteName+";");
					rewriter.InsertTextBefore(pvd->getLocEnd(),ABFORCHD2_);
			}
			//-- seq END --//
			//-- multithread --//
			else if((voteMethod.compare(vm2))==0) 
			{
					rewriter.InsertTextAfterToken(pvd->getLBraceLoc(),ABOMPWHILEPART1_+MonitorMode);
					rewriter.InsertTextAfterToken(pvd->getLBraceLoc(),ABOMPWHILEPART2_);

					rewriter.InsertTextAfterToken(pvd->getLBraceLoc(),vType+", sizeof("+voteType);
					rewriter.InsertTextAfterToken(pvd->getLBraceLoc(),"));\n\t\t\t\t\ttime_delay=0;\n\t\t\t\t\t");
					rewriter.InsertTextAfterToken(pvd->getLBraceLoc(),voteName+" = data_Voter->"+vType+";\n");
				if(depVar.size()!=0){
					for(int i=depVar.size()-1; i >= 0; i--){
						rewriter.InsertTextAfterToken(pvd->getLBraceLoc(),ABDERPREAD2_ + depVar[i]);
						rewriter.InsertTextAfterToken(pvd->getLBraceLoc(),ABDERPREAD3_);
						rewriter.InsertTextAfterToken(pvd->getLBraceLoc(),depType[i]);  //depType
						rewriter.InsertTextAfterToken(pvd->getLBraceLoc(),ABDERPREAD4_);
					}
				}
					rewriter.InsertTextAfterToken(pvd->getLBraceLoc(),ABOMPWHILEPART3_);

			//reverse

					rewriter.InsertTextBefore(pvd->getLocEnd(),ABOMPEND_);
				if(depVar.size()!=0){
					for(int i=0; i <depVar.size() ; i++){
						rewriter.InsertTextBefore(pvd->getLocEnd(),ABDEPWRITE4_);
						rewriter.InsertTextBefore(pvd->getLocEnd(),depType[i]); //depType
						rewriter.InsertTextBefore(pvd->getLocEnd(),ABDEPWRITE3_);
						rewriter.InsertTextBefore(pvd->getLocEnd(),ABDEPWRITE2_ + depVar[i] );
					}
				}
					rewriter.InsertTextBefore(pvd->getLocEnd(),ABOMPMJRTY6_);
					rewriter.InsertTextBefore(pvd->getLocEnd(),ABOMPMJRTY5_+voteType);
					rewriter.InsertTextBefore(pvd->getLocEnd(),ABOMPMJRTY4_+vType);
					rewriter.InsertTextBefore(pvd->getLocEnd(),ABOMPMJRTY3_+vType);
					rewriter.InsertTextBefore(pvd->getLocEnd(),ABOMPMJRTY2_+vType);
					rewriter.InsertTextBefore(pvd->getLocEnd(),ABOMPMJRTY1_+voteType);

					rewriter.InsertTextBefore(pvd->getLocEnd(),vType+" = "+voteName+";\n\t\t\t}\n");
					rewriter.InsertTextBefore(pvd->getLocEnd(),ABOMPWHILEPART4_);
			}
			//-- multithread END --//
			//-- multiprocess --//
			else if((voteMethod.compare(vm3))==0) 
			{
					rewriter.InsertTextAfterToken(pvd->getLBraceLoc(),ABMFINITIAL_);
					rewriter.InsertTextAfterToken(pvd->getLBraceLoc(),ABMFWHILEPART1_+MonitorMode);
					rewriter.InsertTextAfterToken(pvd->getLBraceLoc(),ABMFWHILEPART2_);
					rewriter.InsertTextAfterToken(pvd->getLBraceLoc(),vType+", sizeof(");
					rewriter.InsertTextAfterToken(pvd->getLBraceLoc(),voteType+"));\n");
					rewriter.InsertTextAfterToken(pvd->getLBraceLoc(),ABMFWHILEPART3_);

					rewriter.InsertTextAfterToken(pvd->getLBraceLoc(),ABMFMJRTY1_+voteType);
					rewriter.InsertTextAfterToken(pvd->getLBraceLoc(),ABMFMJRTY2_+vType);
					rewriter.InsertTextAfterToken(pvd->getLBraceLoc(),ABMFMJRTY3_+vType);
					rewriter.InsertTextAfterToken(pvd->getLBraceLoc(),ABMFMJRTY4_+vType);
					rewriter.InsertTextAfterToken(pvd->getLBraceLoc(),ABMFMJRTY5_+voteName);
					rewriter.InsertTextAfterToken(pvd->getLBraceLoc(),ABMFMJRTY6_);

				if(depVar.size()!=0){
					for(int i=depVar.size()-1; i >= 0; i--){
						rewriter.InsertTextAfterToken(pvd->getLBraceLoc(),ABDERPREAD2_ + depVar[i]);
						rewriter.InsertTextAfterToken(pvd->getLBraceLoc(),ABDERPREAD3_);
						rewriter.InsertTextAfterToken(pvd->getLBraceLoc(),depType[i]);  //depType
						rewriter.InsertTextAfterToken(pvd->getLBraceLoc(),ABDERPREAD4_);
					}
				}
					rewriter.InsertTextAfterToken(pvd->getLBraceLoc(),ABMFMJRTY7_);
					rewriter.InsertTextAfterToken(pvd->getLBraceLoc(),ABMFWHILEPART4_);

			//reverse

					rewriter.InsertTextBefore(pvd->getLocEnd(),ABMFEND_);
				if(depVar.size()!=0){
					for(int i=0; i <depVar.size() ; i++){
						rewriter.InsertTextBefore(pvd->getLocEnd(),ABDEPWRITE4_);
						rewriter.InsertTextBefore(pvd->getLocEnd(),depType[i]); //depType
						rewriter.InsertTextBefore(pvd->getLocEnd(),ABDEPWRITE3_);
						rewriter.InsertTextBefore(pvd->getLocEnd(),ABDEPWRITE2_ + depVar[i] );
					}
				}
					rewriter.InsertTextBefore(pvd->getLocEnd(),"\n\t\t\t\twrite(pipe_fd_Voter2[1], &"+voteName+", sizeof("+voteType+"));");
					rewriter.InsertTextBefore(pvd->getLocEnd(),vType+" = "+voteName+";\n\t\t\t");
					rewriter.InsertTextBefore(pvd->getLocEnd(),ABMFWHILEPART5_);
			}
			//-- multiprocess END --//
		}
		//***  abnormal mode END***//
	}
	//--------------  Monitor_Vote Set END--------------//


	//--------------  Monitor Set --------------//
	else if((MonitorMode.compare(""))!=0)
	{
		errs() << "==> MONITOR set... " << "\n";

		SourceLocation SW =  pvd->getLocation();
		rewriter.ReplaceText(SW.getLocWithOffset(-8),"//");
		rewriter.ReplaceText(pvd->getLBraceLoc()," "); //delete "{" 
		rewriter.InsertTextBefore(pvd->getRBraceLoc(),"\n//*** ENDD_____\t\t");

		string mon1("repeat");
		string mon2("abnormal");

		//***  repeat mode ***//
		if((MonitorMode.compare(mon1))==0) 
		{
			rewriter.InsertTextAfterToken(pvd->getLBraceLoc(),RPPIPE_);
			rewriter.InsertTextAfterToken(pvd->getLBraceLoc(),RPINITIAL_);
			rewriter.InsertTextAfterToken(pvd->getLBraceLoc(),RPWHILEPART1_);
			rewriter.InsertTextBefore(pvd->getLocEnd(),RPWHILEPART2_);
		}
		//***  repeat mode  END ***//
		//***  abnormal mode ***//
		else if((MaxTimeLimit.compare(mon2))==0) 
		{

			rewriter.InsertTextAfterToken(pvd->getLBraceLoc(),ABPIPE_);
			rewriter.InsertTextAfterToken(pvd->getLBraceLoc(),ABINITIAL_);
			rewriter.InsertTextAfterToken(pvd->getLBraceLoc(),ABWHILEPART1_);
			rewriter.InsertTextAfterToken(pvd->getLBraceLoc(),MonitorMode); //MaxTimeLimit
			rewriter.InsertTextAfterToken(pvd->getLBraceLoc(),ABWHILEPART2_);

			if(depVar.size()!=0){
				for(int i=depVar.size()-1; i >= 0; i--){
					rewriter.InsertTextAfterToken(pvd->getLBraceLoc(),ABDERPREAD2_ + depVar[i]);
					rewriter.InsertTextAfterToken(pvd->getLBraceLoc(),ABDERPREAD3_);
					rewriter.InsertTextAfterToken(pvd->getLBraceLoc(),depType[i]);  //depType
					rewriter.InsertTextAfterToken(pvd->getLBraceLoc(),ABDERPREAD4_);
				}
			}
				rewriter.InsertTextAfterToken(pvd->getLBraceLoc(),ABWHILEPART3_);
				rewriter.InsertTextBefore(pvd->getLocEnd(),ABWHILEPART4_);

			if(depVar.size()!=0){
				for(int i=0; i <depVar.size() ; i++){
					rewriter.InsertTextBefore(pvd->getLocEnd(),ABDEPWRITE4_);
					rewriter.InsertTextBefore(pvd->getLocEnd(),depType[i]); //depType
					rewriter.InsertTextBefore(pvd->getLocEnd(),ABDEPWRITE3_);
					rewriter.InsertTextBefore(pvd->getLocEnd(),ABDEPWRITE2_ + depVar[i] );
				}
			}
		}
		//***  abnormal mode  END ***//
		else
		{
			errs() << "==> MONITOR set WRONG. " << "\n";
		}
	}
	//--------------  Monitor Set END--------------//


	//--------------  Vote Set --------------//
	else if((voteMethod.compare(""))!=0)
	{
		errs() << "==> VOTE set... " << "\n";

		string vm1("seq");
		string vm2("multithread");
		string vm3("multiprocess");
	
		//***  seq mode  ***//
		if((voteMethod.compare(vm1))==0)
		{

			SourceLocation SW =  pvd->getLocation();
			rewriter.ReplaceText(SW.getLocWithOffset(-8),"//");
			rewriter.ReplaceText(pvd->getLBraceLoc()," "); //delete "{" 
			rewriter.InsertTextAfterToken(pvd->getLBraceLoc(),FORPIPE_);
			rewriter.InsertTextAfterToken(pvd->getLBraceLoc(),FORKERR_);
			rewriter.InsertTextAfterToken(pvd->getLBraceLoc(),FORKCHD_);
			rewriter.InsertTextBefore(pvd->getRBraceLoc(),"\n//*** ENDD_____\t\t");
			rewriter.InsertTextBefore(pvd->getLocEnd(),VOTE_RESULT4_);

		if(depVar.size()!=0){
			for(int i=0; i <depVar.size() ; i++){
				rewriter.InsertTextBefore(pvd->getLocEnd(),DERPREAD4_);
				rewriter.InsertTextBefore(pvd->getLocEnd(),depType[i]);  //depType
				rewriter.InsertTextBefore(pvd->getLocEnd(),DERPREAD3_);
				rewriter.InsertTextBefore(pvd->getLocEnd(),DERPREAD2_ + depVar[i]);
			}
		}

			rewriter.InsertTextBefore(pvd->getLocEnd(),VOTE_RESULT3_);
			rewriter.InsertTextBefore(pvd->getLocEnd(),VOTE_RESULT2_+ voteName);
			rewriter.InsertTextBefore(pvd->getLocEnd(),VOTE_RESULT_ + vType);

			rewriter.InsertTextBefore(pvd->getLocEnd(),vType + VOTE_MAJORITY5_);
			rewriter.InsertTextBefore(pvd->getLocEnd(),vType + VOTE_MAJORITY4_);
			rewriter.InsertTextBefore(pvd->getLocEnd(),vType + VOTE_MAJORITY3_);
			rewriter.InsertTextBefore(pvd->getLocEnd(),voteType+VOTE_MAJORITY2_);
			rewriter.InsertTextBefore(pvd->getLocEnd(),VOTE_MAJORITY_);

			rewriter.InsertTextBefore(pvd->getLocEnd(),PARENTRECEIVE3_);	
			rewriter.InsertTextBefore(pvd->getLocEnd(),PARENTRECEIVE2_ + voteType);
			rewriter.InsertTextBefore(pvd->getLocEnd(),PARENTRECEIVE_ + vType);

			rewriter.InsertTextBefore(pvd->getLocEnd(),CHDEXIT_);

		if(depVar.size()!=0){
			rewriter.InsertTextBefore(pvd->getLocEnd(),DEPWRITE5_);
			for(int i=0; i <depVar.size() ; i++){
				rewriter.InsertTextBefore(pvd->getLocEnd(),DEPWRITE4_);
				rewriter.InsertTextBefore(pvd->getLocEnd(),depType[i]); //depType
				rewriter.InsertTextBefore(pvd->getLocEnd(),DEPWRITE3_);
				rewriter.InsertTextBefore(pvd->getLocEnd(),DEPWRITE2_ + depVar[i] );
			}
			rewriter.InsertTextBefore(pvd->getLocEnd(),DEPWRITE_);
		}

			std::string VarForProtect(voteName);
				rewriter.InsertTextBefore(pvd->getLocEnd(),CHDSEND5_);
				rewriter.InsertTextBefore(pvd->getLocEnd(),CHDSEND4_ + voteType);
				rewriter.InsertTextBefore(pvd->getLocEnd(),CHDSEND3_ + vType);
				rewriter.InsertTextBefore(pvd->getLocEnd(),CHDSEND2_ + VarForProtect);
				rewriter.InsertTextBefore(pvd->getLocEnd(),CHDSEND1_ + vType);

		} 
		//***  seq mode  END ***//
		//***  multithread mode  ***//
		else if ((voteMethod.compare(vm2))==0)
		{

			SourceLocation SW =  pvd->getLocation();
			rewriter.ReplaceText(SW.getLocWithOffset(-8),"//");
			rewriter.ReplaceText(pvd->getLBraceLoc()," "); //delete "{" 
			rewriter.InsertTextAfterToken(pvd->getLBraceLoc(),OMPPIPE_);
			rewriter.InsertTextAfterToken(pvd->getLBraceLoc(),OMPERR_);
			rewriter.InsertTextAfterToken(pvd->getLBraceLoc(),OMPCHD_);
			rewriter.InsertTextBefore(pvd->getRBraceLoc(),"\n//*** ENDD_____\t\t");
			rewriter.InsertTextBefore(pvd->getLocEnd(),OMPVOTE_RESULT4_);

		if(depVar.size()!=0){
			for(int i=0; i <depVar.size() ; i++){
				rewriter.InsertTextBefore(pvd->getLocEnd(),OMPDERPREAD4_);
				rewriter.InsertTextBefore(pvd->getLocEnd(),depType[i]);  //depType
				rewriter.InsertTextBefore(pvd->getLocEnd(),OMPDERPREAD3_);
				rewriter.InsertTextBefore(pvd->getLocEnd(),OMPDERPREAD2_ + depVar[i]);
			}
		}
			rewriter.InsertTextBefore(pvd->getLocEnd(),OMPVOTE_RESULT3_);
			rewriter.InsertTextBefore(pvd->getLocEnd(),OMPVOTE_RESULT2_+ voteName);
			rewriter.InsertTextBefore(pvd->getLocEnd(),OMPVOTE_RESULT_ + vType);

			rewriter.InsertTextBefore(pvd->getLocEnd(),vType + OMPVOTE_MAJORITY5_);
			rewriter.InsertTextBefore(pvd->getLocEnd(),vType + OMPVOTE_MAJORITY4_);
			rewriter.InsertTextBefore(pvd->getLocEnd(),vType + OMPVOTE_MAJORITY3_);
			rewriter.InsertTextBefore(pvd->getLocEnd(),voteType+OMPVOTE_MAJORITY2_);
			rewriter.InsertTextBefore(pvd->getLocEnd(),OMPVOTE_MAJORITY_);

			rewriter.InsertTextBefore(pvd->getLocEnd(),OMPPARENTRECEIVE3_);	
			rewriter.InsertTextBefore(pvd->getLocEnd(),OMPPARENTRECEIVE2_ + voteType);
			rewriter.InsertTextBefore(pvd->getLocEnd(),OMPPARENTRECEIVE_ + vType);

			rewriter.InsertTextBefore(pvd->getLocEnd(),OMPCHDEXIT_);

		if(depVar.size()!=0){
			rewriter.InsertTextBefore(pvd->getLocEnd(),OMPDEPWRITE5_);
			for(int i=0; i <depVar.size() ; i++){
				rewriter.InsertTextBefore(pvd->getLocEnd(),OMPDEPWRITE4_);
				rewriter.InsertTextBefore(pvd->getLocEnd(),depType[i]); //depType
				rewriter.InsertTextBefore(pvd->getLocEnd(),OMPDEPWRITE3_);
				rewriter.InsertTextBefore(pvd->getLocEnd(),OMPDEPWRITE2_ + depVar[i] );
			}
			rewriter.InsertTextBefore(pvd->getLocEnd(),OMPDEPWRITE_);
		}

			std::string VarForProtect(voteName);
				rewriter.InsertTextBefore(pvd->getLocEnd(),OMPCHDSEND5_);
				rewriter.InsertTextBefore(pvd->getLocEnd(),OMPCHDSEND4_ + voteType);
				rewriter.InsertTextBefore(pvd->getLocEnd(),OMPCHDSEND3_ + VarForProtect);
				rewriter.InsertTextBefore(pvd->getLocEnd(),OMPCHDSEND2_ + VarForProtect);
				rewriter.InsertTextBefore(pvd->getLocEnd(),OMPCHDSEND1_ + vType);

		} 
		//***  multithread mode  END ***//
		//***  multiprocess mode  ***//
		else if ((voteMethod.compare(vm3))==0)
		{

			SourceLocation SW =  pvd->getLocation();
			rewriter.ReplaceText(SW.getLocWithOffset(-8),"//");
			rewriter.ReplaceText(pvd->getLBraceLoc()," "); //delete "{" 
			rewriter.InsertTextAfterToken(pvd->getLBraceLoc(),MFPIPE_);
			rewriter.InsertTextAfterToken(pvd->getLBraceLoc(),MFERR_);
			rewriter.InsertTextAfterToken(pvd->getLBraceLoc(),MFCHD_);
			rewriter.InsertTextBefore(pvd->getRBraceLoc(),"\n//*** ENDD_____\t\t");
			rewriter.InsertTextBefore(pvd->getLocEnd(),MFVOTE_RESULT4_);

		if(depVar.size()!=0){
			for(int i=0; i <depVar.size() ; i++){
				rewriter.InsertTextBefore(pvd->getLocEnd(),MFDERPREAD4_);
				rewriter.InsertTextBefore(pvd->getLocEnd(),depType[i]);  //depType
				rewriter.InsertTextBefore(pvd->getLocEnd(),MFDERPREAD3_);
				rewriter.InsertTextBefore(pvd->getLocEnd(),MFDERPREAD2_ + depVar[i]);
			}
		}

			rewriter.InsertTextBefore(pvd->getLocEnd(),MFVOTE_RESULT3_);
			rewriter.InsertTextBefore(pvd->getLocEnd(),MFVOTE_RESULT2_ + voteName);
			rewriter.InsertTextBefore(pvd->getLocEnd(),MFVOTE_RESULT_ + vType);

			rewriter.InsertTextBefore(pvd->getLocEnd(),vType + MFVOTE_MAJORITY5_);
			rewriter.InsertTextBefore(pvd->getLocEnd(),vType + MFVOTE_MAJORITY4_);
			rewriter.InsertTextBefore(pvd->getLocEnd(),vType + MFVOTE_MAJORITY3_);
			rewriter.InsertTextBefore(pvd->getLocEnd(),voteType+MFVOTE_MAJORITY2_);
			rewriter.InsertTextBefore(pvd->getLocEnd(),MFVOTE_MAJORITY_);

			rewriter.InsertTextBefore(pvd->getLocEnd(),MFPARENTRECEIVE3_);	
			rewriter.InsertTextBefore(pvd->getLocEnd(),MFPARENTRECEIVE2_ + voteType);
			rewriter.InsertTextBefore(pvd->getLocEnd(),MFPARENTRECEIVE_ + vType);

			rewriter.InsertTextBefore(pvd->getLocEnd(),MFPARENTFORK_);

			rewriter.InsertTextBefore(pvd->getLocEnd(),MFCHDEXIT_);

		if(depVar.size()!=0){
			rewriter.InsertTextBefore(pvd->getLocEnd(),MFDEPWRITE5_);
		for(int i=0; i <depVar.size() ; i++){
			rewriter.InsertTextBefore(pvd->getLocEnd(),MFDEPWRITE4_);
			rewriter.InsertTextBefore(pvd->getLocEnd(),depType[i]); //depType
			rewriter.InsertTextBefore(pvd->getLocEnd(),MFDEPWRITE3_);
			rewriter.InsertTextBefore(pvd->getLocEnd(),MFDEPWRITE2_ + depVar[i] );
		}
			rewriter.InsertTextBefore(pvd->getLocEnd(),MFDEPWRITE_);
		}

			std::string VarForProtect(voteName);
				rewriter.InsertTextBefore(pvd->getLocEnd(),MFCHDSEND5_);
				rewriter.InsertTextBefore(pvd->getLocEnd(),MFCHDSEND4_ + voteType);
				rewriter.InsertTextBefore(pvd->getLocEnd(),MFCHDSEND3_ + vType);
				rewriter.InsertTextBefore(pvd->getLocEnd(),MFCHDSEND2_ + VarForProtect);
				rewriter.InsertTextBefore(pvd->getLocEnd(),MFCHDSEND1_ + vType);

		} 
		//***  multiprocess mode  END***//
	}
	//--------------  Vote Set END--------------//

        return true;
}



    virtual bool VisitFunctionDecl(FunctionDecl *func) {

        string funcName = func->getNameInfo().getName().getAsString();

	if(funcName =="main")//if (func->isMain())
    {	
		SourceLocation S =  func->getSourceRange().getBegin();//func->getBeginLoc();//funcbody->getLocStart().getLocWithOffset(-1*funcName.length());
		rewriter.InsertTextBefore(S,STRUCT_);
		rewriter.InsertTextBefore(S,DEFINE2_);
		rewriter.InsertTextBefore(S,DEFINE_);
		rewriter.InsertTextBefore(S,INCLUEDE_);	
	}



//------2017/11/14------//
if (func->hasBody()) { 
	if (func->isVoteFunction()) {
    	//voteAnnotator->TraverseDecl(fd->getMostRecentDecl()); // process the function
//    	errs() << "==> pragma: " << funcName << "\n";

	//string param = func->getParamDecl().getAsString();
	//errs() << "--> param: " << param << "\n";

    	}
}
//------2017/11/14------//
    
        return true;
    }

	
    virtual bool VisitStmt(Stmt *st) {
 
        if (ReturnStmt *ret = dyn_cast<ReturnStmt>(st)) {
/*
	//FunctionDecl *func=st->get;
	    rewriter.InsertTextBefore(st->getLocStart(),VOTE_RESULT_);
	    rewriter.InsertTextBefore(st->getLocStart(),VOTE_MAJORITY_);
	    rewriter.InsertTextBefore(st->getLocStart(),PARENTRECEIVE_);

	std::string VarForProtect(g_argv[4]);
	    rewriter.InsertTextBefore(st->getLocStart(),VarForProtect+";"+CHDSEND2_);
	    rewriter.InsertTextBefore(st->getLocStart(),CHDSEND1_);

            rewriter.ReplaceText(ret->getRetValue()->getLocStart(), 6, "; //"+VarForProtect+"; //");//"val; //");
//            errs() << "** Rewrote ReturnStmt\n";

//		errs() << "@@@ : " << st << "\n";

*/

        }        
        if (CallExpr *call = dyn_cast<CallExpr>(st)) {
//            rewriter.ReplaceText(call->getLocStart(), 7, "add5");
//            errs() << "** Rewrote function call\n";
        }
        
        return true;
    }
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

    //parse the parameters
    arg_parse(argc, argv);

    // parse the command-line args passed to your code
    CommonOptionsParser op(argc, argv, StatCategory);        
    // create a new Clang Tool instance (a LibTooling environment)
    ClangTool Tool(op.getCompilations(), op.getSourcePathList());

    // run the Clang Tool, creating a new FrontendAction (explained below)
    int result = Tool.run(newFrontendActionFactory<VoteFrontendAction>().get());

//    errs() << "\nFound " << numFunctions << " functions.\n\n";
    // print out the rewritten source code ("rewriter" is a global var.)
    rewriter.getEditBuffer(rewriter.getSourceMgr().getMainFileID()).write(outs());	//errs() can't output to file
    return result;
}
