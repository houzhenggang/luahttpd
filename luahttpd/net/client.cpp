// Created by Nijie on 2014.07.23.
// Copyright (c) 2014 Nijie. All rights reserved.
// Use of this source code is governed by a GPL-2 license that can be found in the LICENSE file. 
//
#include "client.h"
#include "config.h"
#include "clientmgr.h"
#include "../http/httphandler.h"

Client::Client()
{
	m_handler = NULL;
}

Client::~Client()
{

}

bool Client::init()
{
	return true;
}

void Client::reset()
{
	m_handler = NULL;
}

void Client::OnConnect(void)
{

}

void Client::OnClose(void)
{

}

void Client::OnError(UINT32 dwErrorNo)
{

}

void Client::OnRecv(const char* pBuf, UINT32 dwLen)
{
	if (dwLen == 0 || pBuf[0] == 0)
	{
		Close();
		return;
	}

	m_handler = ClientMgr::Instance().CreateHttpHandler();
	if (NULL == m_handler)
	{
		Close();
		return;
	}

	if (!m_handler->init(this, pBuf))
	{
		Close();
		return;
	}

	m_handler->doing();
}

void Client::Release(void)
{
	if (NULL != m_handler)
	{
		ClientMgr::Instance().releaseHttpHandler(m_handler);
		m_handler = NULL;
	}
	ClientMgr::Instance().releaseSession(this);
}

char* Client::GetRecvBuf()
{
	static char s_buff[MAX_CLIENT_PACKET_LEN];
	return s_buff;
}

UINT32 Client::GetRecvSize()
{
	return MAX_CLIENT_PACKET_LEN;
}