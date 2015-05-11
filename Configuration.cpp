#include "stdafx.h"
#include "Configuration.h"

Configuration * Configuration::instance = NULL;

Configuration::Configuration()
{

	this->m_bCloseQuit = true;
	this->m_bAutoHide = false;
	this->m_bAutoRecord = false;
	this->m_bAutoLive = false;
	this->m_bAutoPushstream = false;

	this->majorCodecConfig.codecType = CODEC_TYPE_H264;
	this->majorCodecConfig.iWidth = 1280;
	this->majorCodecConfig.iHeight = 720;
	this->majorCodecConfig.iFps = 30;
	this->majorCodecConfig.bitrateMethod = BITRATE_METHOD_CBR;
	this->majorCodecConfig.iBitrate = 4096;
	this->majorCodecConfig.iInternal = this->majorCodecConfig.iFps;

	this->minorCodecConfig.codecType = CODEC_TYPE_H264;
	this->minorCodecConfig.iWidth = 960;
	this->minorCodecConfig.iHeight = 540;
	this->minorCodecConfig.iFps = 30;
	this->minorCodecConfig.bitrateMethod = BITRATE_METHOD_CBR;
	this->minorCodecConfig.iBitrate = 1024;
	this->minorCodecConfig.iInternal = this->minorCodecConfig.iFps;

	this->recordConfig.fileType = MEDIA_FILE_TYPE_MP4;
	this->recordConfig.filenamePattern = "record_%year%%month%%day%%hour%%minute%%second%";
	this->recordConfig.recordPath = "D:\\ScreenVideo\\record";
	this->recordConfig.m_iAutoSplitTime = 60;

	this->liveConfig.EnableRtmp = false;
	this->liveConfig.RtmpPort = 1935;
	this->liveConfig.EnableRtsp = false;
	this->liveConfig.RtspPort = 554;
	this->liveConfig.EnableWdm = true;
	this->liveConfig.WdmPort = 1989;
	this->liveConfig.EnableP2p = false;
	this->liveConfig.P2pPort = 2015;
	this->liveConfig.EnableMulticast = false;
	this->liveConfig.MulticastPort = 1990;
	this->liveConfig.EnableMulticast = 0;

	this->pushstreamConfig.EnableMajor = false;
	this->pushstreamConfig.EnableMinor = true;
	this->pushstreamConfig.MajorUrl = "rtmp://127.0.0.1:1935/live/screen";
	this->pushstreamConfig.MinorUrl = "rtmp://127.0.0.1:1935/live/screen_sub";

}


Configuration::~Configuration()
{
}

Configuration * Configuration::GetInstance()
{
	if (instance==NULL)
	{
		instance = new Configuration();
	}
	return instance;
}

CodecAttribute * Configuration::GetMajorCodecCoinfig()
{
	return &(this->majorCodecConfig);
}

CodecAttribute * Configuration::GetMinorCodecCoinfig()
{
	return &(this->minorCodecConfig);
}

RecordAttribute * Configuration::GetRecordConfig()
{
	return &(this->recordConfig);
}

LiveAttribute * Configuration::GetLiveConfig()
{
	return &(this->liveConfig);
}

PushStreamAttribute * Configuration::GetPushstramConfig()
{
	return &(this->pushstreamConfig);
}

bool Configuration::Load()
{
	return true;
}

bool Configuration::Save()
{
	return true;
}

bool Configuration::IsQuitApp()
{
	return m_bCloseQuit;
}

void Configuration::SetQuitApp(bool val)
{
	m_bCloseQuit = val;
}

bool Configuration::IsAutoHideWindow()
{
	return m_bAutoHide;
}

void Configuration::SetAutoHideWindow(bool val)
{
	m_bAutoHide = val;
}

bool Configuration::IsAutoRecord()
{
	return m_bAutoRecord;
}

void Configuration::SetAutoRecord(bool val)
{
	m_bAutoRecord = val;
}

bool Configuration::IsAutoLive()
{
	return m_bAutoLive;
}

void Configuration::SetAutoLive(bool val)
{
	m_bAutoLive = val;
}

bool Configuration::IsAutoPushstream()
{
	return m_bAutoPushstream;
}

void Configuration::SetAutoPushstream(bool val)
{
	m_bAutoPushstream = val;
}
