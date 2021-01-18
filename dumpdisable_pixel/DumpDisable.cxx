#include "Bits/Bits.h"
#include "PixDbInterface/PixDbInterface.h"
#include "RootDb/RootDb.h"
#include "RCCVmeInterface.h"
#include "PixConnectivity/PartitionConnectivity.h"
#include "PixConnectivity/RodCrateConnectivity.h"
#include "PixConnectivity/RodBocConnectivity.h"
#include "PixConnectivity/OBConnectivity.h"
#include "PixConnectivity/Pp0Connectivity.h"
#include "RCCVmeInterface.h"
#include "PixConnectivity/ModuleConnectivity.h"
#include "PixConnectivity/TimConnectivity.h"
#include "PixConnectivity/PixConnectivity.h"
#include "PixConnectivity/PixDisable.h"
#include "PixTrigController/TimPixTrigController.h"
#include "PixController/PixRunConfig.h"
#include "PixModule/PixModule.h"
#include "PixUtilities/PixISManager.h"
#include "Config/Config.h"
#include "Config/ConfGroup.h"
#include "Config/ConfObj.h"

#include <iostream>
#include <sstream>
#include <iomanip>
#include <sys/time.h>

#include <oks/kernel.h>
#include <oks/object.h>
#include <oks/class.h>
#include <oks/index.h>
#include <oks/attribute.h>
#include <oks/relationship.h>

using namespace std;

unsigned int revision = 0;
int nDis_pay=0;
int nDis_dis=0;
int nDis=0;
int npp0=0;

PixConnectivity* conn;
PixDisable* disableConfig = NULL;
PixDbServerInterface* DbServer = NULL;
IPCPartition* ipcPartition = NULL;

std::string serverName       = "PixelDbServer";
std::string ipcPartitionName =     "PixelInfr";

std::string disConf = "";
std::string connTag =   "Def";
std::string  cfgTag =   "Def";
std::string idTag   = "PIXEL";
bool verbose = true;
bool showPayload = true;
bool showDis = true;
bool print =false;

enum mainMode { NORMAL, HELP  };
enum mainMode mode;

void getParams(int argc, char **argv) {
  int ip = 1;
  mode = NORMAL;
  while (ip < argc) {
    if (std::string(argv[ip]).substr(0,2) == "--") {
      if (std::string(argv[ip]) == "--help") {
	mode = HELP;
	break;
      } else if (std::string(argv[ip]) == "--dbPart") {
	if (ip+1 < argc && std::string(argv[ip+1]).substr(0,2) != "--") {
	  ipcPartitionName = argv[ip+1];
	  ip += 2; 
	} else {
	  mode = HELP;
	  std::cout << std::endl << "No partition name inserted" << std::endl << std::endl;
	  break;
	}
      } else if (std::string(argv[ip]) == "--dbServ") {
	if (ip+1 < argc && std::string(argv[ip+1]).substr(0,2) != "--") {
	  serverName = argv[ip+1];
	  ip += 2; 
	} else {
	  mode = HELP;
	  std::cout << std::endl << "No dbServer name inserted" << std::endl << std::endl;
	  break;
	}
      } else if (std::string(argv[ip]) == "--idTag") {
	if (ip+1 < argc && std::string(argv[ip+1]).substr(0,2) != "--") {
	  idTag = argv[ip+1];
	  ip += 2; 
	} else {
	  mode = HELP;
	  std::cout << std::endl << "No idTag name inserted" << std::endl << std::endl;
	  break;
	}
      } else if (std::string(argv[ip]) == "--connTag") {
	if (ip+1 < argc && std::string(argv[ip+1]).substr(0,2) != "--") {
	  connTag = argv[ip+1];
	  ip += 2; 
	} else {
	  mode = HELP;
	  std::cout << std::endl << "No connTag name inserted" << std::endl << std::endl;
	  break;
	}
      } else if (std::string(argv[ip]) == "--cfgTag") {
	if (ip+1 < argc && std::string(argv[ip+1]).substr(0,2) != "--") {
	  cfgTag = argv[ip+1];
	  ip += 2; 
	} else {
	  mode = HELP;
	  std::cout << std::endl << "No cfgTag name inserted" << std::endl << std::endl;
	  break;
	}
      } else if (std::string(argv[ip]) == "--disConf") {
	if (ip+1 < argc && std::string(argv[ip+1]).substr(0,2) != "--") {
	  disConf = argv[ip+1];
	  ip += 2; 
	} else {
	  mode = HELP;
	  std::cout << std::endl << "No PixRunConfig name inserted" << std::endl << std::endl;
	  break;
	}
      } else if (std::string(argv[ip]) == "--rev") {
	if (ip+1 < argc && std::string(argv[ip+1]).substr(0,2) != "--" ) {
	  revision = atoi(argv[ip+1]);
	  std::cout << "Global revision is: " << revision << std::endl;
	  ip++; 
	} else  {
	  mode = HELP;
	  std::cout << std::endl << "No revision inserted" << std::endl << std::endl;
	  break;
	}
        ip++; 
      } else if (std::string(argv[ip]) == "--NoRod") {
	verbose = false;
	ip++; 
      } else if (std::string(argv[ip]) == "--NoPayload") {
	showPayload = false;
	ip++; 
      } else if (std::string(argv[ip]) == "--NoDisable") {
	showDis = false;
	ip++; 
      } else if (std::string(argv[ip]) == "--print") {
	print = true;
	ip++; 
      } else {
	std::cout << std::endl << "COMMAND: '" << std::string(argv[ip]) << "' unknown!!!" << std::endl << std::endl;
	mode = HELP;
	break;
      }
    }
  }
}

void help() {
  cout << endl;
  cout << "This program gives informations about the objects that are disable in PixConnectivity "<< endl;
  cout << endl; 
  std::cout << "Usage: DumpDisable2 --help\n"
	    << "            // prints this message\n"
	    <<std::endl;
  cout << "Mandatory Options:" << endl;
  cout << "  --idTag     <id tag>     id DB tag           (def. PIXEL)" << endl;
  cout << "  --connTag   <conn tag>   Connectivity DB tag (def. Def)" << endl;
  cout << "  --cfgTag    <cfg tag>    Config DB tag       (def. Def)" << endl;
  cout << "  --disConf <disable config> PixDisable name   (def. GlobalDis)" << endl << endl;
  cout << "optionale switches:" << endl;
  cout << "  --dbPart <part>      IPC Partition (def. PixelInfr)" << endl;
  cout << "  --dbServ <dbServer>  DbServer name (def. PixelDbServer)" << endl;
  cout << "  --rev    <revision>  Disable revision    (def. MOST UPDATED)" << endl;
  cout << "  --NoPayload  shows only objects disabled in the disable object" << endl;
  cout << "  --NoDisable  shows only objects disabled in the payload" << endl;
  cout << "  --print      printable version of the dump" << endl;
  cout << endl;
  cout << endl;
  exit(0);
}



int main(int argc, char** argv) {
  getParams(argc, argv);
  if(mode == HELP) {
    help();
  }

  // Start IPCCore    
  IPCCore::init(argc, argv); 
  // Create IPCPartition constructors                                                              
  std::cout << "Connecting to partition " << ipcPartitionName << std::endl;
  try {
    ipcPartition = new IPCPartition(ipcPartitionName);
  } catch(...) {
    std::cout << "RunConfigEditor: ERROR!! problems while searching for the partition, cannot continue" << std::endl;
    ipcPartition = NULL;
    return -1;
  }
  
  bool ready=false;
  int nTry=0;
  
  if(ipcPartition != NULL) {
    std::cout << "Trying to connect to DbServer with name " << serverName << std::endl;
    do {
      sleep(1);
      DbServer = new PixDbServerInterface(ipcPartition, serverName, PixDbServerInterface::CLIENT, ready);
      if(!ready) delete DbServer;
      else break;
      std::cout << " ..... attempt number: " << nTry << std::endl;
      nTry++;
    } while(nTry<20);
    if(!ready) {
      std::cout << "Impossible to connect to DbServer " << serverName << std::endl;
      exit(-1);
    } else {
      std::cout << "Successfully connected to DbServer with name " << serverName << std::endl;
    }
    sleep(2);
    DbServer->ready();
  } else {
    cout << "No dbserver is created: no IPC partition were correctly handled!!!" << endl;
  }
  
  cout << "Initializing PixConnectivity db" << endl;
  try {
    conn = new PixConnectivity(DbServer, connTag, connTag, connTag, cfgTag, idTag);
  }  
  catch(PixConnectivityExc& e) { 
    std::cout <<"PixConnectivity: "<<e.getDescr()<<std::endl; 
    return -1;
  }
  catch(...) { 
    std::cout <<"Unknown exception caught in RunConfigEditor.cxx while creating PixConnectivity"<<std::endl; 
    return -1;
  }
  try {
    conn->loadConn();
  }
  catch (...) {
    std::cout <<"Error reading PixConnectivity; tag " << connTag << std::endl; 
    return -1;
  }
  
  std::vector<std::string> tagCfglist;
  DbServer->listTagsRem("Configuration-"+idTag,tagCfglist);
  bool foundCfg=false;
  for (unsigned int i=0; i<tagCfglist.size(); i++) {
    if (tagCfglist[i]==cfgTag) foundCfg=true;
  }
  if (!foundCfg) {
    std::cout << std::endl << "FATAL: cfgTag " << cfgTag << " not found in the DbServer!!!" << std::endl << std::endl;
    exit(-1);
  }

  // Look into DbServer for PixDisable objects
  if (disConf!="") {
    disableConfig = new PixDisable(disConf);
    try {
      if(revision!=0) disableConfig->readConfig(DbServer,"Configuration-"+idTag,cfgTag,revision);
      else disableConfig->readConfig(DbServer,"Configuration-"+idTag,cfgTag);
    } catch (...) {
      std::cout << "PixDisable " << disConf << " probably does not exist in DbServer!!!" << std::endl;
      exit(-1);
    }
    disableConfig->put(conn);
  }
  
  PartitionConnectivity* PartConn = NULL;
  RodCrateConnectivity* RodCrateConn = NULL;
  RodBocConnectivity* RodBocConn = NULL;
  OBConnectivity* OBConn = NULL;
  Pp0Connectivity* Pp0Conn = NULL;
  ModuleConnectivity* ModConn = NULL;
  
  map<string,PartitionConnectivity*>::iterator part_iterator;
  map<string,RodCrateConnectivity*>::iterator crate_iterator;
  map<int,RodBocConnectivity*>::iterator rod_iterator;
  
  string part_name, crate_name, rod_name, ob_name, Pp0_name, mod_name;

  if (!print) {
    for (part_iterator=conn->parts.begin(); part_iterator!=conn->parts.end(); part_iterator++){
      PartConn = part_iterator->second;
      if (PartConn==NULL) continue;
      bool partition_active = PartConn->active();
      if (!partition_active){
	if (PartConn->name()!="PIXEL_DET") std::cout << std::endl << "--> Found partition: " << PartConn->name() << " DISABLED !!" << std::endl;  
      }
      
      // loop over crates
      for (crate_iterator=PartConn->rodCrates().begin();crate_iterator!=PartConn->rodCrates().end(); crate_iterator++){
	RodCrateConn = crate_iterator->second;
	if (RodCrateConn==NULL) continue;
	crate_name = RodCrateConn->name();
	bool crate_active = RodCrateConn->active(); 
	bool crate_enabled = RodCrateConn->enableReadout;
	if (!crate_active || !crate_enabled){
	  if (!crate_active && showDis)  std::cout << std::endl << "--> CRATE : " << crate_name << " is DISABLE in PixDisable" << std::endl;
	  if (!crate_enabled && showPayload)  std::cout << std::endl << "--> CRATE : " << crate_name << " is DISABLE in payload" << std::endl;
	}
	// loop over RODs
	for (rod_iterator=RodCrateConn->rodBocs().begin();rod_iterator!=RodCrateConn->rodBocs().end(); rod_iterator++){
	  RodBocConn = rod_iterator->second;
	  if (RodBocConn==NULL) continue;
	  rod_name = RodBocConn->name();
	  bool rod_active = RodBocConn->active();
	  bool rod_enabled = RodBocConn->enableReadout;
	  if (!rod_active || !rod_enabled){
	    if (!rod_active && showDis)  std::cout << std::endl << "--> ROD : " << rod_name << " is DISABLE in PixDisable" << std::endl;
	    if (!rod_enabled && showPayload)  std::cout << std::endl << "--> ROD : " << rod_name << " is DISABLE in payload" << std::endl;
	  }
	  
	  for (int ob_number=0; ob_number<=3; ob_number++){
	    OBConn = RodBocConn->obs(ob_number);
	    if (OBConn==NULL) continue;
	    ob_name = OBConn->name();
	    bool ob_active = OBConn->active(); 
	    //  std::cout << std::endl << "--> Found OptoBoard: " << ob_name <<  " (in position " << ob_number << ")   "; 
	    if (!ob_active){
	      //   std::cout << "DISABLED !!" << std::endl;  
	      continue;
	    } else {
	      //std::cout << "ENABLED !!" << std::endl;  
	    }
	    //get pp0
	    Pp0Conn = OBConn->pp0();
	    if (Pp0Conn==NULL) continue;
	    Pp0_name = Pp0Conn->name();
	    bool pp0_active = Pp0Conn->active(); 
	    if (!pp0_active){
	      if (showDis) std::cout << std::endl << "  >>  Pp0: " << ob_name << " is DISABLED in PixDisable  (ROD : " << rod_name << " ) " << std::endl;  
	      npp0++;
	      // continue;
	    } 
	    
	    // loop over modules: 1..7
	    for (int mod_number=0; mod_number<=8; mod_number++){
	      ModConn = Pp0Conn->modules(mod_number);
	      if (ModConn==NULL) continue;
	      mod_name = ModConn->name();
	      bool mod_active = ModConn->active();
	      bool mod_enabled = ModConn->enableReadout;
	      if (!mod_active || !mod_enabled){
		nDis++;
		if (!mod_active)  {
		  nDis_dis++;
		  //		  if (showDis && pp0_active) std::cout << std::endl << "  --> MODULE : " << mod_name << " is DISABLE in PixDisable (ROD : " << rod_name << " ) " << std::endl;
		  // more convenient to show all disabled modules
		  if (showDis) std::cout << std::endl << "  --> MODULE : " << mod_name << " is DISABLE in PixDisable (ROD : " << rod_name << " ) " << std::endl;
		}
		if (!mod_enabled)  {
		  //		  if (showPayload && pp0_active) std::cout << std::endl << "  --> MODULE : " << mod_name << " is DISABLE in payload (ROD : " << rod_name << " ) " << std::endl;;
		  // more convenient to show all disabled modules
		  if (showPayload) std::cout << std::endl << "  --> MODULE : " << mod_name << " is DISABLE in payload (ROD : " << rod_name << " ) " << std::endl;;
		  nDis_pay++;
		} 
	      }
	    }
	  }
	}
      }
    }
  } else { 
    for (part_iterator=conn->parts.begin(); part_iterator!=conn->parts.end(); part_iterator++){
      PartConn = part_iterator->second;
      if (PartConn==NULL) continue;
      bool partition_active = PartConn->active();
      if (!partition_active){
	if (PartConn->name()!="PIXEL_DET") std::cout << PartConn->name() << " --> PixDisable" << std::endl;  
      }
      
      // loop over crates
      for (crate_iterator=PartConn->rodCrates().begin();crate_iterator!=PartConn->rodCrates().end(); crate_iterator++){
	RodCrateConn = crate_iterator->second;
	if (RodCrateConn==NULL) continue;
	crate_name = RodCrateConn->name();
	bool crate_active = RodCrateConn->active(); 
	bool crate_enabled = RodCrateConn->enableReadout;
	if (!crate_active || !crate_enabled){
	  if (!crate_active && showDis)  std::cout << crate_name << " --> PixDisable" << std::endl;
	  if (!crate_enabled && showPayload)  std::cout << crate_name << " --> PayLoad" << std::endl; 
	  continue;
	}
	// loop over RODs
	for (rod_iterator=RodCrateConn->rodBocs().begin();rod_iterator!=RodCrateConn->rodBocs().end(); rod_iterator++){
	  RodBocConn = rod_iterator->second;
	  if (RodBocConn==NULL) continue;
	  rod_name = RodBocConn->name();
	  bool rod_active = RodBocConn->active();
	  bool rod_enabled = RodBocConn->enableReadout;
	  if (!rod_active || !rod_enabled){
	    if (!rod_active && showDis)  std::cout << rod_name << " --> PixDisable" << std::endl;
	    if (!rod_enabled && showPayload)  std::cout << rod_name << " --> PayLoad" << std::endl;
	  }
	  
	  for (int ob_number=0; ob_number<=3; ob_number++){
	    OBConn = RodBocConn->obs(ob_number);
	    if (OBConn==NULL) continue;
	    ob_name = OBConn->name();
	    bool ob_active = OBConn->active(); 
	    //  std::cout << std::endl << "--> Found OptoBoard: " << ob_name <<  " (in position " << ob_number << ")   "; 
	    if (!ob_active){
	      //   std::cout << "DISABLED !!" << std::endl;  
	      continue;
	    } else {
	      //std::cout << "ENABLED !!" << std::endl;  
	    }
	    //get pp0
	    Pp0Conn = OBConn->pp0();
	    if (Pp0Conn==NULL) continue;
	    Pp0_name = Pp0Conn->name();
	    bool pp0_active = Pp0Conn->active(); 
	    if (!pp0_active){
	      if (showDis) std::cout << ob_name << " --> PixDisable  (ROD : " << rod_name << " ) " << std::endl;  
	      npp0++;
	      // continue;
	    } 
	    
	    // loop over modules: 1..7
	    for (int mod_number=0; mod_number<=8; mod_number++){
	      ModConn = Pp0Conn->modules(mod_number);
	      if (ModConn==NULL) continue;
	      mod_name = ModConn->name();
	      bool mod_active = ModConn->active();
	      bool mod_enabled = ModConn->enableReadout;
	      if (!mod_active || !mod_enabled){
		nDis++;
		if (!mod_active)  {
		  nDis_dis++;
		  if (showDis && pp0_active) std::cout << mod_name << " --> PixDisable (ROD : " << rod_name << " ) " << std::endl;
		}
		if (!mod_enabled)  {
		  if (showPayload && pp0_active) std::cout << mod_name << " --> PayLoad (ROD : " << rod_name << " ) " << std::endl;;
		  nDis_pay++;
		} 
	      }
	    }
	  }
	}
      }
    }
  }
  std::cout << std::endl << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << std::endl;
  std::cout << std::endl  << nDis << " Modules are DISABLED:"<< std::endl;
  std::cout << std::endl << "--> " << nDis_pay << " Modules in the payLoad"<< std::endl;
  std::cout << std::endl << "--> " << nDis_dis << " Modules in the disable object ( "<< npp0 << " pp0 ) " <<  std::endl;
  std::cout << std::endl << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << std::endl << std::endl;
}
  
  
  
