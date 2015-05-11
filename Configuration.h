#pragma once

#include <iostream>
#include <string.h>
using namespace std;

enum CODEC_TYPE_E{
	CODEC_TYPE_H264 = 0,
	CODEC_TYPE_H265,
	CODEC_TYPE_VP8,
	CODEC_TYPE_VP9
};

enum BITRATE_METHOD_E{
	BITRATE_METHOD_CBR = 0,
	BITRATE_METHOD_VBR
};

typedef struct _CodecAttribute
{
	CODEC_TYPE_E codecType;
	int iWidth;
	int iHeight;
	int iFps;
	BITRATE_METHOD_E bitrateMethod;
	int iBitrate;
	int iInternal;
}CodecAttribute;

enum MEDIA_FILE_TYPE_E
{
	MEDIA_FILE_TYPE_MP4 = 0,
	MEDIA_FILE_TYPE_FLV,
	MEDIA_FILE_TYPE_AVI,
	MEDIA_FILE_TYPE_RAW,
	MEDIA_FILE_TYPE_YUV
};

typedef struct _RecordAttribute 
{
	MEDIA_FILE_TYPE_E fileType;
	string recordPath;
	string filenamePattern;
	int m_iAutoSplitTime;
}RecordAttribute;

typedef struct _LiveAttribute
{
	bool EnableRtmp;
	unsigned short RtmpPort;
	bool EnableRtsp;
	unsigned short RtspPort;
	bool EnableWdm;
	unsigned short WdmPort;
	bool EnableP2p;
	unsigned short P2pPort;
	bool EnableMulticast;
	unsigned short MulticastPort;
	unsigned int MulticastIP;
}LiveAttribute;

typedef struct _PushStreamAttribute
{
	bool EnableMajor;
	bool EnableMinor;
	string MajorUrl;
	string MinorUrl;
}PushStreamAttribute;

class Configuration
{
private:
	static Configuration * instance;
	Configuration();

	CodecAttribute majorCodecConfig;
	CodecAttribute minorCodecConfig;
	RecordAttribute recordConfig;
	LiveAttribute liveConfig;
	PushStreamAttribute pushstreamConfig;

	bool m_bCloseQuit;
	bool m_bAutoHide;
	bool m_bAutoRecord;
	bool m_bAutoLive;
	bool m_bAutoPushstream;
public:
	~Configuration();
	static Configuration * GetInstance();
	bool Load();
	bool Save();

	CodecAttribute * GetMajorCodecCoinfig();
	CodecAttribute * GetMinorCodecCoinfig();
	RecordAttribute * GetRecordConfig();
	LiveAttribute * GetLiveConfig();
	PushStreamAttribute * GetPushstramConfig();

	bool IsQuitApp();
	void SetQuitApp(bool val);
	bool IsAutoHideWindow();
	void SetAutoHideWindow(bool val);
	bool IsAutoRecord();
	void SetAutoRecord(bool val);
	bool IsAutoLive();
	void SetAutoLive(bool val);
	bool IsAutoPushstream();
	void SetAutoPushstream(bool val);
};
