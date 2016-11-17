#ifndef __MWFRAMEWORK__
#define __MWFRAMEWORK__

// framework base.
#include "base/mwbase.h"

// platform.
#include "platform/MWSystemHelperStrategy.h"
#include "platform/MWSystemHelper.h"
#include "platform/MWIOUtilsStrategy.h"
#include "platform/MWIOUtils.h"

// custom controls
#include "controls/MWSmoothRope.h"

// core scheme.
#include "scheme/MWGameScene.h"
#include "scheme/MWViewController.h"
#include "scheme/MWGameView.h"
#include "scheme/MWViewSegue.h"

// db operations.
#include "db/sqlite/MWSqliteDb.h"

// compression
#include "compression/MWZipData.h"

// texture extensions
#include "texture/gif/MWGifFrame.h"
#include "texture/gif/MWGifSprite.h"
#include "texture/gif/MWGifFramesCache.h"
#include "texture/svg/MWSvgSprite.h"

// json.
#include "json/MWJsonStructure.h"

// protobuf
#include "protobuf/pbc/pbc.h"

// encryption.
#include "encryption/MWCrypto.h"

// ai
#include "ai/astar/MWAStarPathFinder.h"

// utils
#include "utils/MWUUIDGenerator.h"
#include "utils/MWAssetManager.h"

// net.
#include "net/MWNetService.h"
#include "net/MWNetHandler.h"
#include "net/MWNetFilter.h"
#include "net/MWNetRequest.h"
#include "net/MWNetResponse.h"
#include "net/MWNetProtocol.h"
#include "net/MWNetCenter.h"

// http
#include "net/http/MWHttpForm.h"
#include "net/http/IHttpTransferStrategy.h"
#include "net/http/MWHttpGetService.h"
#include "net/http/MWHttpPostService.h"
#include "net/http/MWHttpDownloader.h"

// socket
#include "net/socketio/MWSocketIOService.h"

// lua related.
#if MW_ENABLE_SCRIPT_BINDING
#include "lua/MWLuaUtils.h"
#include "lua/auto/lua_mwframework_auto.hpp"
#include "lua/manual/lua_mwframework_manual.hpp"
#include "protobuf/pbc/pbc-lua.h"
#endif

#endif
