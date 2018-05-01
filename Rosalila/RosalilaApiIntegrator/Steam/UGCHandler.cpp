#include "UGCHandler.h"

UGCHandler::UGCHandler()
{
  //SteamAPICall_t create_item_call = SteamUGC()->CreateItem( 517510, k_EWorkshopFileTypeCommunity);
  //CCallResult<UGCHandler, CreateItemResult_t> *create_item_callback = new CCallResult<UGCHandler, CreateItemResult_t>();
  //create_item_callback->Set(create_item_call, this,&UGCHandler::onItemCreated);

  //AccountID_t account_id = SteamUser()->GetSteamID().GetAccountID();
  //EUserUGCList eListType = (EUserUGCList)6; /*subscribed items*/
  //EUGCMatchingUGCType eMatchingUGCType = (EUGCMatchingUGCType)0; /* k_EUGCMatchingUGCType_Items */
  //EUserUGCListSortOrder eSortOrder = (EUserUGCListSortOrder)4; /* k_EUserUGCListSortOrder_SubscriptionDateDesc */
  //UGCQueryHandle_t ugc_query_handle = SteamUGC()->CreateQueryUserUGCRequest(account_id, eListType, eMatchingUGCType, eSortOrder, (AppId_t)517510, (AppId_t)517510, (uint32)1 );
  //CCallResult<UGCHandler, SteamUGCQueryCompleted_t> *steam_ugc_query_completed_callback = new CCallResult<UGCHandler,  SteamUGCQueryCompleted_t>();
  //steam_ugc_query_completed_callback->Set(ugc_query_handle, this,&UGCHandler::onUGCQueryCompleted);
}

void UGCHandler::onItemCreated(CreateItemResult_t *pCallback,	bool bIOFailure)
{
  if(pCallback->m_eResult != k_EResultOK || bIOFailure)
  {
    cout<<"error"<<endl;
      rosalila()->utility->writeLogLine("Error creating UGC item");
      this->state="error";
      return;
  }

  this->published_file_id = pCallback->m_nPublishedFileId;

  if(pCallback->m_bUserNeedsToAcceptWorkshopLegalAgreement)
  {
    //TODO: Test this
    SteamFriends()->ActivateGameOverlayToWebPage("steam://url/CommunityFilePage/");
  }
  rosalila()->utility->writeLogLine("UGC item creation complete");
/*AppId_t nConsumerAppId*/
  UGCUpdateHandle_t ugc_update_handle = SteamUGC()->StartItemUpdate(517510, pCallback->m_nPublishedFileId);

  SteamUGC()->SetItemTitle(ugc_update_handle, "Title test");
  SteamUGC()->SetItemDescription(ugc_update_handle, "Description test");
  SteamUGC()->SetItemUpdateLanguage(ugc_update_handle, "None");
  SteamUGC()->SetItemMetadata(ugc_update_handle, "Test metadata");
  ERemoteStoragePublishedFileVisibility eVisibility = (ERemoteStoragePublishedFileVisibility)0;/*public*/
  SteamUGC()->SetItemVisibility(ugc_update_handle, eVisibility);

  SteamParamStringArray_t *pTags = new SteamParamStringArray_t();
  pTags->m_ppStrings = new const char*[1];
  pTags->m_ppStrings[0] = "stage";
  pTags->m_nNumStrings = 1;
  SteamUGC()->SetItemTags(ugc_update_handle, pTags);
  SteamUGC()->AddItemKeyValueTag(ugc_update_handle, "test_key", "test_value");
  string mod_directory = rosalila()->utility->getAbsolutePath() + assets_directory +"mods/stages/Mod1";
  SteamUGC()->SetItemContent(ugc_update_handle, mod_directory.c_str());
  string preview_image = rosalila()->utility->getAbsolutePath() + assets_directory+"mods/stages/Mod1/images/preview.png";
  SteamUGC()->SetItemPreview(ugc_update_handle, preview_image.c_str());

  SteamAPICall_t submit_item_call = SteamUGC()->SubmitItemUpdate(ugc_update_handle, NULL /*No notes*/);
  CCallResult<UGCHandler, SubmitItemUpdateResult_t> *submit_item_callback = new CCallResult<UGCHandler, SubmitItemUpdateResult_t>();
  submit_item_callback->Set(submit_item_call, this,&UGCHandler::onItemSubmitted);
}

void UGCHandler::onItemSubmitted(SubmitItemUpdateResult_t *pCallback,	bool bIOFailure)
{
  if(pCallback->m_eResult != k_EResultOK || bIOFailure)
  {
    cout<<"error"<<pCallback->m_eResult<<endl;
    rosalila()->utility->writeLogLine("Error submitting UGC item");
    this->state="error";
    return;
  }
  cout<<"Succsexxx"<<endl;
}

void UGCHandler::onUGCQueryCompleted(SteamUGCQueryCompleted_t *pCallback,	bool bIOFailure)
{
  if(pCallback->m_eResult != k_EResultOK || bIOFailure)
  {
    cout<<"error"<<pCallback->m_eResult<<endl;
    rosalila()->utility->writeLogLine("Error on UGC query");
    this->state="error";
    return;
  }
  cout<<"Succsexxx"<<endl;
}
