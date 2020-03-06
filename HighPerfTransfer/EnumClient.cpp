#include "stdafx.h"

#include "EnumClient.h"


CEnumClient::CEnumClient(IFileDevice * pSender, IFileDevice * pReceiver, IEumCallback * pEumCallback, CONST BODY_BEGIN_ENUM_FILE_REQ & body_begin_enum_file_req) :
m_RefCount(0),
m_pSender(pSender),
m_pReceiver(pReceiver),
m_pEumCallback(pEumCallback),
m_body_begin_enum_file_req(body_begin_enum_file_req),
m_hSendReceiverMonitorThread(NULL)
{

}

HRESULT CEnumClient::CreateMember()
{
	HRESULT hr = S_OK;
	DWORD LastError = 0;

	BEGIN_BLOCK(0);
	//////////////////////////////////////////////////////////////////////////
	hr = CreateInstanceCEnumClientHandler(m_pEumCallback, &m_spIHPTHandlerClient, TRUE);
	if (FAILED(hr))
	{
		D_API_ERR(0, TEXT("CreateInstanceCDownloadClientHandler"), hr, TEXT(""));
		LEAVE_BLOCK(0);
	}

	hr = CreateInstanceCHPTSendReceive(
		m_pSender,//IFileDevice * pSender,
		m_pReceiver,//IFileDevice * pReceiver,
		FALSE,//BOOL bAttachSenderReceiver,
		NULL,//IHPTServerHandlerFactory * pHPTNewHandlerFactory,
		FALSE,//BOOL bServer,
		&m_spIHPTSendReceive,//IHPTSendReceive  ** ppIHPTSendReceive,
		TRUE//BOOL bCreateMember
		);
	if (FAILED(hr))
	{
		D_API_ERR(0, TEXT("CreateInstanceCHPTSendReceive"), hr, TEXT(""));
		LEAVE_BLOCK(0);
	}

	hr = m_spIHPTSendReceive->SetClientHandler(m_spIHPTHandlerClient.p);
	if (FAILED(hr))
	{
		D_API_ERR(0, TEXT("IHPTSendReceive->SetClientHandler"), hr, TEXT(""));
		LEAVE_BLOCK(0);
	}

	m_hSendReceiverMonitorThread = CreateSendReceiverMonitorThread(m_spIHPTSendReceive.p);
	if (NULL == m_hSendReceiverMonitorThread)
	{
		hr = E_FAIL;
		D_API_ERR(0, TEXT(""), hr, TEXT(""));
		LEAVE_BLOCK(0);
	}

	//////////////////////////////////////////////////////////////////////////
	END_BLOCK(0);

	return hr;
}

HRESULT CEnumClient::DestroyMember()
{
	HRESULT hr = S_OK;
	DWORD LastError = 0;

	BEGIN_BLOCK(0);
	//////////////////////////////////////////////////////////////////////////
	m_spIHPTSendReceive.Release();
	m_spIHPTHandlerClient.Release();

	if (m_hSendReceiverMonitorThread)
	{
		CloseHandle(m_hSendReceiverMonitorThread);
		m_hSendReceiverMonitorThread = NULL;
	}
	//////////////////////////////////////////////////////////////////////////
	END_BLOCK(0);

	return hr;
}

HRESULT CEnumClient::Main()
{
	HRESULT hr = S_OK;
	DWORD LastError = 0;
	DWORD WaitIndex = -1;

	BOOL bReceiveServerStat = FALSE;

	CONST LONG __15min = 1000 * 60 * 15;
	CONST LONG __30min = 1000 * 60 * 30;
	CONST LONG __60min = 1000 * 60 * 60;

	//////////////////////////////////////////////////////////////////////////
	HPTHeader HeaderTemp;
	HPTBody BodyTemp;

	BEGIN_BLOCK(0);
	//////////////////////////////////////////////////////////////////////////
	CONST LONG __2M = 1024 * 1024 * 2;
	hr = BodyTemp.Allocate(__2M);
	if (FAILED(hr))
	{
		D_API_ERR(0, TEXT("Allocate"), hr, TEXT(""));
		LEAVE_BLOCK(0);
	}

	//////////////////////////////////////////////////////////////////////////
	CString strXml;

	BodyTemp.Allocate(0);

	HeaderTemp.Init();
	//HeaderTemp.m_HeaderSize;
	//HeaderTemp.m_HeaderVersion;
	HeaderTemp.m_CommandCode = CMD_CREATE_ENUM_FILE_SESSION_REQ;
	//HeaderTemp.m_FlagOrEnum;
	HeaderTemp.m_PayloadLength = BodyTemp.m_DataSize;
	//HeaderTemp.m_PayloadFileOffset;
	HeaderTemp.m_ClientHandler = PtrToUll<IHPTHandler>(m_spIHPTHandlerClient.p);
	//HeaderTemp.m_ServerHandler;
	//HeaderTemp.m_Data64;

	hr = m_spIHPTSendReceive->PutCommandToSend(HeaderTemp, BodyTemp);
	if (FAILED(hr))
	{
		D_API_ERR(0, TEXT("PutCommandToSend"), hr, TEXT(""));
		LEAVE_BLOCK(0);
	}

	WaitIndex = m_spIHPTHandlerClient->WaitAny(__15min);
	if (NS_MultipleEventHelper::SYNC_INDEX != WaitIndex - WAIT_OBJECT_0)
	{
		//HRESULT hrTmp = m_spIHPTHandlerClient->GetStatusStatistic()->m_Error.m_LastStatus;
		D_API_ERR(0, TEXT("Wait"), hr, TEXT("WaitIndex=%d"), WaitIndex);
		LEAVE_BLOCK(0);
	}

	ULONGLONG ServerHandlerTemp = m_spIHPTHandlerClient->GetServerHandler();
	ATLASSERT(ServerHandlerTemp);


	//////////////////////////////////////////////////////////////////////////
	strXml.Empty();
	m_body_begin_enum_file_req.ToString(MethodString(BODY_BEGIN_ENUM_FILE_REQ), strXml);

	hr = BodyTemp.Allocate(strXml.GetLength() * sizeof(TCHAR)+sizeof(TCHAR));
	if (FAILED(hr))
	{
		D_API_ERR(0, TEXT("Allocate"), hr, TEXT(""));
		LEAVE_BLOCK(0);
	}
	CopyMemory(BodyTemp.m_pData, strXml.GetString(), BodyTemp.m_DataSize);

	HeaderTemp.Init();
	//HeaderTemp.m_HeaderSize;
	//HeaderTemp.m_HeaderVersion;
	HeaderTemp.m_CommandCode = CMD_BEGIN_ENUM_FILE_REQ;
	//HeaderTemp.m_FlagOrEnum;
	HeaderTemp.m_PayloadLength = BodyTemp.m_DataSize;
	//HeaderTemp.m_PayloadFileOffset;
	HeaderTemp.m_ClientHandler = PtrToUll<IHPTHandler>(m_spIHPTHandlerClient.p);;
	HeaderTemp.m_ServerHandler = ServerHandlerTemp;
	//HeaderTemp.m_Data64;

	hr = m_spIHPTSendReceive->PutCommandToSend(HeaderTemp, BodyTemp);
	if (FAILED(hr))
	{
		D_API_ERR(0, TEXT("PutCommandToSend"), hr, TEXT(""));
		LEAVE_BLOCK(0);
	}

	WaitIndex = m_spIHPTHandlerClient->WaitAny(INFINITE);
	if (NS_MultipleEventHelper::SYNC_INDEX != WaitIndex - WAIT_OBJECT_0)
	{
		//HRESULT hrTmp = m_spIHPTHandlerClient->GetStatusStatistic()->m_Error.m_LastStatus;
		D_API_ERR(0, TEXT("Wait"), hr, TEXT("WaitIndex=%d"), WaitIndex);
		LEAVE_BLOCK(0);
	}


	//////////////////////////////////////////////////////////////////////////
	BodyTemp.Allocate(0); //<sonmi01>2014-2-9 ###???

	HeaderTemp.Init();
	//HeaderTemp.m_HeaderSize;
	//HeaderTemp.m_HeaderVersion;
	HeaderTemp.m_CommandCode = CMD_HANDLER_STATUS_STATISTIC_TOTAL_REQ;
	//HeaderTemp.m_FlagOrEnum;
	//HeaderTemp.m_PayloadLength;
	//HeaderTemp.m_PayloadFileOffset;
	HeaderTemp.m_ClientHandler = PtrToUll<IHPTHandler>(m_spIHPTHandlerClient.p);;
	HeaderTemp.m_ServerHandler = ServerHandlerTemp;
	//HeaderTemp.m_Data64;

	hr = m_spIHPTSendReceive->PutCommandToSend(HeaderTemp, BodyTemp);
	if (FAILED(hr))
	{
		D_API_ERR(0, TEXT("PutCommandToSend"), hr, TEXT(""));
		LEAVE_BLOCK(0);
	}

	WaitIndex = m_spIHPTHandlerClient->WaitAny(__15min);
	if (NS_MultipleEventHelper::SYNC_INDEX != WaitIndex - WAIT_OBJECT_0)
	{
		//HRESULT hrTmp = m_spIHPTHandlerClient->GetStatusStatistic()->m_Error.m_LastStatus;
		D_API_ERR(0, TEXT("Wait"), hr, TEXT("WaitIndex=%d"), WaitIndex);
		LEAVE_BLOCK(0);
	}
	//m_hSendReceiverMonitorThread(NULL)
	bReceiveServerStat = TRUE;


	//////////////////////////////////////////////////////////////////////////
	END_BLOCK(0);

	//////////////////////////////////////////////////////////////////////////
	BodyTemp.Allocate(0);

	HeaderTemp.Init();
	//HeaderTemp.m_HeaderSize;
	//HeaderTemp.m_HeaderVersion;
	HeaderTemp.m_CommandCode = CMD_END_SESSION_REQ;
	//HeaderTemp.m_FlagOrEnum;
	//HeaderTemp.m_PayloadLength;
	//HeaderTemp.m_PayloadFileOffset;
	HeaderTemp.m_ClientHandler = PtrToUll<IHPTHandler>(m_spIHPTHandlerClient.p);
	//HeaderTemp.m_ServerHandler;
	//HeaderTemp.m_Data64;

	//hr = m_spIHPTHandlerClient->ResetAll();
	//if (FAILED(hr))
	//{
	//	D_API_ERR(0, TEXT("ResetAll"), hr, TEXT(""));
	//	//LEAVE_BLOCK(0);
	//}
	for (LONG ii = 0; ii <= NS_MultipleEventHelper::DONE_INDEX; ++ii) //<sonmi01>2014-3-28 ###???
	{
		HRESULT hrTemp = m_spIHPTHandlerClient->Reset(ii);
		if (FAILED(hrTemp))
		{
			hr = hrTemp;
			D_API_ERR(0, TEXT("Reset"), hr, TEXT(""));
		}
	}


	hr = m_spIHPTSendReceive->PutCommandToSend(HeaderTemp, BodyTemp);
	if (FAILED(hr))
	{
		D_API_ERR(0, TEXT("PutCommandToSend"), hr, TEXT(""));
		//LEAVE_BLOCK(0);
	}

	WaitIndex = m_spIHPTHandlerClient->WaitAny(__15min);
	if (NS_MultipleEventHelper::SYNC_INDEX != WaitIndex - WAIT_OBJECT_0)
	{
		//HRESULT hrTmp = m_spIHPTHandlerClient->GetStatusStatistic()->m_Error.m_LastStatus;
		D_API_ERR(0, TEXT("Wait"), hr, TEXT("WaitIndex=%d"), WaitIndex);
		//LEAVE_BLOCK(0);
	}


	//////////////////////////////////////////////////////////////////////////
	hr = m_spIHPTSendReceive->Set(FAILED(hr) ? NS_MultipleEventHelper::ERROR_INDEX : NS_MultipleEventHelper::DONE_INDEX);
	if (FAILED(hr))
	{
		D_API_ERR(0, TEXT("IHPTSendReceive->Set"), hr, TEXT(""));
		//LEAVE_BLOCK(0);
	}


	DWORD dwWait = WaitForSingleObject(m_hSendReceiverMonitorThread, __30min);
	if (WAIT_OBJECT_0 == dwWait)
	{
		D_INFO(0, TEXT("SendReceiverMonitorThread ended"));
	}
	else if (WAIT_TIMEOUT == dwWait)
	{
		TerminateThread(m_hSendReceiverMonitorThread, E_FAIL);
		D_INFO(0, TEXT("SendReceiverMonitorThread terminated"));
	}
	else
	{
		LastError = GetLastError();
		hr = HRESULT_FROM_WIN32(LastError);
		D_API_ERR(0, TEXT("WaitForSingleObject"), hr, TEXT(""));
	}

	//////////////////////////////////////////////////////////////////////////
	HRESULT FinalStatus = S_OK;
	if (FAILED(hr))
	{
		FinalStatus = hr;
		D_API_ERR(0, TEXT("Main"), FinalStatus, TEXT(""));
	}
	else if (FAILED(m_spIHPTHandlerClient->GetStatusStatistic()->m_Error.m_LastStatus))
	{
		FinalStatus = m_spIHPTHandlerClient->GetStatusStatistic()->m_Error.m_LastStatus;
		D_API_ERR(0, TEXT("ClientHandler"), FinalStatus, TEXT(""));
	}
	else
	{
		if (!bReceiveServerStat)
		{
			FinalStatus = E_FAIL;
			D_API_ERR(0, TEXT("FinalStatus not received"), FinalStatus, TEXT(""));
		}
		if (FAILED(m_spIHPTHandlerClient->GetStatusStatisticServer()->m_Error.m_LastStatus))
		{
			FinalStatus = m_spIHPTHandlerClient->GetStatusStatisticServer()->m_Error.m_LastStatus;
			D_API_ERR(0, TEXT("ServerHandler"), FinalStatus, TEXT(""));
		}
	}
	//////////////////////////////////////////////////////////////////////////

	return FinalStatus;
}

HRESULT CreateInstanceCEnumClient(IFileDevice * pSender, IFileDevice * pReceiver, IEumCallback * pEumCallback, CONST BODY_BEGIN_ENUM_FILE_REQ & body_begin_enum_file_req, IJobMainFlow ** ppIJobMainFlow, BOOL bCreateMember)
{
	return CREATE_INSTCANCE_COBJECT(
		new CEnumClient(pSender, pReceiver, pEumCallback, body_begin_enum_file_req),
		ppIJobMainFlow,
		bCreateMember
		);
}

HRESULT HPTEnumClient(IFileDevice * pSender, IFileDevice * pReceiver, IEumCallback * pEumCallback, CONST BODY_BEGIN_ENUM_FILE_REQ & body_begin_enum_file_req)
{
	HRESULT hr = S_OK;
	DWORD LastError = 0;

	BEGIN_BLOCK(0);
	//////////////////////////////////////////////////////////////////////////
	CComPtr<IJobMainFlow> spIJobMainFlow;
	hr = CreateInstanceCEnumClient(
		pSender,//IFileDevice * pSender, 
		pReceiver,//IFileDevice * pReceiver,
		pEumCallback,
		body_begin_enum_file_req,//CONST BODY_CREATE_DOWNLOAD_SESSION_REQ & data_creae_download_session_req,
		&spIJobMainFlow,//IJobMainFlow ** ppIJobMainFlow, 
		TRUE//BOOL bCreateMember
		);
	if (FAILED(hr))
	{
		D_API_ERR(0, TEXT("CreateInstanceCDowloadClient"), hr, TEXT(""));
		LEAVE_BLOCK(0);
	}

	hr = spIJobMainFlow->Main();
	if (FAILED(hr))
	{
		D_API_ERR(0, TEXT("IJobMainFlow->Main"), hr, TEXT(""));
		LEAVE_BLOCK(0);
	}

	//////////////////////////////////////////////////////////////////////////
	END_BLOCK(0);

	return hr;
}

HRESULT HPTEnumClient(LPCTSTR pServer, LPCTSTR pPort, IEumCallback * pEumCallback, CONST BODY_BEGIN_ENUM_FILE_REQ & body_begin_enum_file_req)
{
	HRESULT hr = S_OK;
	DWORD LastError = 0;

	BEGIN_BLOCK(0);
	//////////////////////////////////////////////////////////////////////////
	CComPtr<ISocketClient> spISocketClient;
	hr = CreateInstanceCSocketClient(pServer, pPort, &spISocketClient, FALSE, FALSE, TRUE);
	if (FAILED(hr))
	{
		D_API_ERR(0, TEXT("CreateInstanceCSocketClient"), hr, TEXT(""));
		LEAVE_BLOCK(0);
	}

	//////////////////////////////////////////////////////////////////////////
	hr = HPTEnumClient(spISocketClient.p, spISocketClient.p, pEumCallback, body_begin_enum_file_req);
	if (FAILED(hr))
	{
		D_API_ERR(0, TEXT("HPTDownloadClient"), hr, TEXT(""));
		LEAVE_BLOCK(0);
	}

	//////////////////////////////////////////////////////////////////////////
	END_BLOCK(0);

	return hr;
}
