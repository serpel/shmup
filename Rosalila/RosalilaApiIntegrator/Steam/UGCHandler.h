#ifndef UGCHANDLER_HANDLER_H
#define UGCHANDLER_HANDLER_H

#include <map>
#include <vector>
#include <string>
#include <iostream>
#include "include/steam_api.h"
#include "include/isteamuserstats.h"
#include "../../RosalilaUtility/RosalilaUtility.h"

#include <limits.h> //TODO: Make this on windows and OSX

using namespace std;

class UGCHandler
{
public:
  string state;

  PublishedFileId_t published_file_id;

  UGCHandler();

  void onItemCreated(CreateItemResult_t *pCallback,	bool bIOFailure);
  void onItemSubmitted(SubmitItemUpdateResult_t *pCallback,	bool bIOFailure);
  void onUGCQueryCompleted(SteamUGCQueryCompleted_t *pCallback,	bool bIOFailure);
};

#endif
