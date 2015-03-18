#ifndef __MWFRAMEWORK__
#define __MWFRAMEWORK__

// framework base.
#include "base/mwbase.h"

// core scheme.
#include "scheme/MWGameScene.h"
#include "scheme/MWViewController.h"
#include "scheme/MWGameView.h"

// db operations.
#include "db/sqlite/MWSqliteDb.h"

// json.
#include "json/MWJsonElement.h"
#include "json/MWJsonStructure.h"
#include "json/MWJsonFormatter.h"
#include "json/MWJsonParser.h"

// utils.
#include "utils/MWIOUtils.h"

// net.
#include "net/MWNetService.h"
#include "net/MWNetHandler.h"
#include "net/MWNetFilter.h"
#include "net/MWNetRequest.h"
#include "net/MWNetResponse.h"
#include "net/MWNetProtocol.h"
#include "net/MWNetCenter.h"
#include "net/http/MWHttpForm.h"
#include "net/http/MWHttpTransferStrategy.h"
#include "net/http/MWHttpService.h"
#include "net/http/MWHttpDownloader.h"

// lua related.
#include "lua/MWLuaUtils.h"

#endif
