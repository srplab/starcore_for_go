/*
vsopenapi_c stub header file
create by srplab            
create date: 2018-3-23
*/

#include "vsopenapi_c_stub.h"

struct StructOfVSStarCoreInterfaceTable *g_star_CoreFunctionTbl;

void Star_SRPComm_Release(void *c_this)
{
    g_star_CoreFunctionTbl->SRPComm_Release(c_this);
}

VS_HANDLE Star_SRPComm_CreateMsgQueue(void *c_this,VS_INT32 ControlMsgSize,VS_INT32 DataMsgSize)
{
    return g_star_CoreFunctionTbl->SRPComm_CreateMsgQueue(c_this,ControlMsgSize,DataMsgSize);
}

void Star_SRPComm_DeleteMsgQueue(void *c_this,VS_HANDLE MsgHandle)
{
    g_star_CoreFunctionTbl->SRPComm_DeleteMsgQueue(c_this,MsgHandle);
}

VS_INT8 *Star_SRPComm_GetControlMsgBuf(void *c_this,VS_HANDLE MsgHandle)
{
    return g_star_CoreFunctionTbl->SRPComm_GetControlMsgBuf(c_this,MsgHandle);
}

VS_INT8 *Star_SRPComm_GetDataMsgBuf(void *c_this,VS_HANDLE MsgHandle)
{
    return g_star_CoreFunctionTbl->SRPComm_GetDataMsgBuf(c_this,MsgHandle);
}

void Star_SRPComm_FreeMsgBuf(void *c_this,VS_HANDLE MsgHandle,VS_INT8 *MsgBuf)
{
    g_star_CoreFunctionTbl->SRPComm_FreeMsgBuf(c_this,MsgHandle,MsgBuf);
}

VS_INT32 Star_SRPComm_AddMsgToQueue(void *c_this,VS_HANDLE MsgHandle,VS_INT8 *MsgBuf)
{
    return g_star_CoreFunctionTbl->SRPComm_AddMsgToQueue(c_this,MsgHandle,MsgBuf);
}

VS_INT8 *Star_SRPComm_GetMsgFromQueue(void *c_this,VS_HANDLE MsgHandle,VS_INT32 WaitMark)
{
    return g_star_CoreFunctionTbl->SRPComm_GetMsgFromQueue(c_this,MsgHandle,WaitMark);
}

VS_HANDLE Star_SRPComm_GetKernelMsgQueue(void *c_this)
{
    return g_star_CoreFunctionTbl->SRPComm_GetKernelMsgQueue(c_this);
}

VS_UINT16 Star_SRPComm_AllocKernelMsgClass(void *c_this)
{
    return g_star_CoreFunctionTbl->SRPComm_AllocKernelMsgClass(c_this);
}

void Star_SRPComm_FreeKernelMsgClass(void *c_this,VS_UINT16 MsgClass)
{
    g_star_CoreFunctionTbl->SRPComm_FreeKernelMsgClass(c_this,MsgClass);
}

VS_BOOL Star_SRPComm_RegKernelMsgProc(void *c_this,VS_UINT16 MsgClass,VS_KernelMsgProc KernelMsgProc,VS_UWORD Para)
{
    return g_star_CoreFunctionTbl->SRPComm_RegKernelMsgProc(c_this,MsgClass,KernelMsgProc,Para);
}

void Star_SRPComm_UnRegKernelMsgProc(void *c_this,VS_UINT16 MsgClass,VS_KernelMsgProc KernelMsgProc,VS_UWORD Para)
{
    g_star_CoreFunctionTbl->SRPComm_UnRegKernelMsgProc(c_this,MsgClass,KernelMsgProc,Para);
}

VS_BOOL Star_SRPComm_RegWebServerMsgProc(void *c_this,VS_WebServerMsgProc WebServerMsgProc,VS_UWORD Para,VS_BOOL RunInKernel,VS_ULONG BufSize)
{
    return g_star_CoreFunctionTbl->SRPComm_RegWebServerMsgProc(c_this,WebServerMsgProc,Para,RunInKernel,BufSize);
}

VS_BOOL Star_SRPComm_UnRegWebServerMsgProc(void *c_this,VS_WebServerMsgProc WebServerMsgProc,VS_UWORD Para)
{
    return g_star_CoreFunctionTbl->SRPComm_UnRegWebServerMsgProc(c_this,WebServerMsgProc,Para);
}

void Star_SRPComm_WebServerRelease(void *c_this,VS_ULONG ConnectionID)
{
    g_star_CoreFunctionTbl->SRPComm_WebServerRelease(c_this,ConnectionID);
}

VS_ULONG Star_SRPComm_TCPSetupServer(void *c_this,VS_HANDLE MsgHandle,VS_INT32 BufferPkgNum,const VS_INT8 *LocalServerName,VS_UINT16 PortNumber,VS_ULONG ConnectionGroup,VS_UINT16 MsgClass,SOCKADDR_IN *SocketAddr)
{
    return g_star_CoreFunctionTbl->SRPComm_TCPSetupServer(c_this,MsgHandle,BufferPkgNum,LocalServerName,PortNumber,ConnectionGroup,MsgClass,SocketAddr);
}

VS_ULONG Star_SRPComm_TCPSetupClient(void *c_this,VS_HANDLE MsgHandle,VS_INT32 BufferPkgNum,const VS_INT8 *ServerName,VS_UINT16 PortNumber,VS_ULONG ConnectionGroup,VS_UINT16 MsgClass)
{
    return g_star_CoreFunctionTbl->SRPComm_TCPSetupClient(c_this,MsgHandle,BufferPkgNum,ServerName,PortNumber,ConnectionGroup,MsgClass);
}

VS_INT32 Star_SRPComm_TCPSend(void *c_this,VS_ULONG ConnectionID,VS_INT32 Length,const VS_INT8 *FrameBuf,VS_BOOL MoreData)
{
    return g_star_CoreFunctionTbl->SRPComm_TCPSend(c_this,ConnectionID,Length,FrameBuf,MoreData);
}

VS_INT32 Star_SRPComm_TCPRecv(void *c_this,VS_ULONG ConnectionID,VS_INT32 Length,VS_INT8 *FrameBuf)
{
    return g_star_CoreFunctionTbl->SRPComm_TCPRecv(c_this,ConnectionID,Length,FrameBuf);
}

VS_INT32 Star_SRPComm_TCPRecvLine(void *c_this,VS_ULONG SocketIDOfClient,VS_INT32 Length,VS_CHAR *FrameBuf,VS_INT32 *ModeDataSize)
{
    return g_star_CoreFunctionTbl->SRPComm_TCPRecvLine(c_this,SocketIDOfClient,Length,FrameBuf,ModeDataSize);
}

VS_INT32 Star_SRPComm_TCPPreview(void *c_this,VS_ULONG SocketIDOfClient,VS_INT32 Length,VS_INT8 *FrameBuf)
{
    return g_star_CoreFunctionTbl->SRPComm_TCPPreview(c_this,SocketIDOfClient,Length,FrameBuf);
}

VS_INT32 Star_SRPComm_TCPDisacrd(void *c_this,VS_ULONG SocketIDOfClient,VS_INT32 Length)
{
    return g_star_CoreFunctionTbl->SRPComm_TCPDisacrd(c_this,SocketIDOfClient,Length);
}

void Star_SRPComm_TCPRelease(void *c_this,VS_ULONG ConnectionID)
{
    g_star_CoreFunctionTbl->SRPComm_TCPRelease(c_this,ConnectionID);
}

VS_ULONG Star_SRPComm_UDPSetupServer(void *c_this,VS_HANDLE MsgHandle,VS_INT32 BufferPkgNum,const VS_INT8 *LocalServerName,VS_UINT16 PortNumber,VS_ULONG ConnectionGroup,VS_UINT16 MsgClass,SOCKADDR_IN *SocketAddr)
{
    return g_star_CoreFunctionTbl->SRPComm_UDPSetupServer(c_this,MsgHandle,BufferPkgNum,LocalServerName,PortNumber,ConnectionGroup,MsgClass,SocketAddr);
}

VS_ULONG Star_SRPComm_UDPSetupClient(void *c_this,VS_HANDLE MsgHandle,VS_INT32 BufferPkgNum,VS_ULONG ConnectionGroup,VS_UINT16 MsgClass)
{
    return g_star_CoreFunctionTbl->SRPComm_UDPSetupClient(c_this,MsgHandle,BufferPkgNum,ConnectionGroup,MsgClass);
}

VS_INT32 Star_SRPComm_UDPSend(void *c_this,VS_ULONG ConnectionID,VS_INT32 Length,const VS_INT8 *FrameBuf,VSSOCKADDR_IN *SockAddr)
{
    return g_star_CoreFunctionTbl->SRPComm_UDPSend(c_this,ConnectionID,Length,FrameBuf,SockAddr);
}

VS_BOOL Star_SRPComm_UDPRecv(void *c_this,VS_ULONG ConnectionID,VS_INT32 *Length,VS_INT8 *FrameBuf,VSSOCKADDR_IN *SockAddr)
{
    return g_star_CoreFunctionTbl->SRPComm_UDPRecv(c_this,ConnectionID,Length,FrameBuf,SockAddr);
}

void Star_SRPComm_UDPRelease(void *c_this,VS_ULONG ConnectionID)
{
    g_star_CoreFunctionTbl->SRPComm_UDPRelease(c_this,ConnectionID);
}

VS_BOOL Star_SRPComm_UDPSetSockAddr(void *c_this,const VS_CHAR *Name,VS_UINT16 Port,VSSOCKADDR_IN *SockAddr)
{
    return g_star_CoreFunctionTbl->SRPComm_UDPSetSockAddr(c_this,Name,Port,SockAddr);
}

VS_ULONG Star_SRPComm_HttpDownLoad( void *c_this,VS_HANDLE MsgHandle,const VS_CHAR *Url,const VS_CHAR *FileName,VS_ULONG ConnectionGroup,VS_UINT16 MsgClass )
{
    return g_star_CoreFunctionTbl->SRPComm_HttpDownLoad(c_this,MsgHandle,Url,FileName,ConnectionGroup,MsgClass);
}

VS_ULONG Star_SRPComm_HttpUpLoad( void *c_this,VS_HANDLE MsgHandle,const VS_CHAR *Url,const VS_CHAR *FileName,VS_UINT64 FileSize,const VS_CHAR *ContentType,VS_BOOL MultiPartFlag,const VS_CHAR *SaveFileName,VS_ULONG ConnectionGroup,VS_UINT16 MsgClass )
{
    return g_star_CoreFunctionTbl->SRPComm_HttpUpLoad(c_this,MsgHandle,Url,FileName,FileSize,ContentType,MultiPartFlag,SaveFileName,ConnectionGroup,MsgClass);
}

VS_ULONG Star_SRPComm_HttpDownLoadEx( void *c_this,VS_HANDLE MsgHandle,const VS_CHAR *Url,const VS_CHAR *FileName,const VS_CHAR *RequestHeader,VS_ULONG ConnectionGroup,VS_UINT16 MsgClass )
{
    return g_star_CoreFunctionTbl->SRPComm_HttpDownLoadEx(c_this,MsgHandle,Url,FileName,RequestHeader,ConnectionGroup,MsgClass);
}

VS_ULONG Star_SRPComm_HttpUpLoadEx( void *c_this,VS_HANDLE MsgHandle,const VS_CHAR *Url,const VS_CHAR *FileName,VS_UINT64 FileSize,const VS_CHAR *RequestHeader,VS_ULONG ConnectionGroup,VS_UINT16 MsgClass )
{
    return g_star_CoreFunctionTbl->SRPComm_HttpUpLoadEx(c_this,MsgHandle,Url,FileName,FileSize,RequestHeader,ConnectionGroup,MsgClass);
}

VS_INT32 Star_SRPComm_HttpSend(void *c_this,VS_ULONG ConnectionID,VS_INT32 Length,const VS_INT8 *FrameBuf,VS_BOOL MoreData)
{
    return g_star_CoreFunctionTbl->SRPComm_HttpSend(c_this,ConnectionID,Length,FrameBuf,MoreData);
}

VS_INT32 Star_SRPComm_HttpRecv(void *c_this,VS_ULONG ConnectionID,VS_INT32 Length,VS_INT8 *FrameBuf)
{
    return g_star_CoreFunctionTbl->SRPComm_HttpRecv(c_this,ConnectionID,Length,FrameBuf);
}

void Star_SRPComm_HttpRelease( void *c_this,VS_ULONG ConnectionID )
{
    g_star_CoreFunctionTbl->SRPComm_HttpRelease(c_this,ConnectionID);
}

VS_ULONG Star_SRPComm_HttpServer( void *c_this,VS_HANDLE MsgHandle,const VS_INT8 *LocalServerName,VS_UINT16 PortNumber,VS_ULONG ConnectionGroup,VS_UINT16 MsgClass,SOCKADDR_IN *SocketAddr, VS_ULONG MaxPostSize )
{
    return g_star_CoreFunctionTbl->SRPComm_HttpServer(c_this,MsgHandle,LocalServerName,PortNumber,ConnectionGroup,MsgClass,SocketAddr,MaxPostSize);
}

void Star_SRPComm_FormatRspHeader(void *c_this,const VS_CHAR *RspInfo,const VS_CHAR *ServerInfo,const VS_CHAR *Connection,const VS_CHAR *ContentType,VS_UINT64 ContentLength,VS_CHAR *Buf)
{
    g_star_CoreFunctionTbl->SRPComm_FormatRspHeader(c_this,RspInfo,ServerInfo,Connection,ContentType,ContentLength,Buf);
}

VS_BOOL Star_SRPComm_ParsePara(void *c_this,const VS_CHAR *Info,const VS_CHAR *ParaName,VS_CHAR *ParaBuf,VS_INT32 ParaBufSize)
{
    return g_star_CoreFunctionTbl->SRPComm_ParsePara(c_this,Info,ParaName,ParaBuf,ParaBufSize);
}

VS_INT32 Star_SRPComm_GetResponseCode(void *c_this,VS_INT8 *Response,VS_CHAR *RspInfo,VS_INT32 RspInfoSize)
{
    return g_star_CoreFunctionTbl->SRPComm_GetResponseCode(c_this,Response,RspInfo,RspInfoSize);
}

VS_BOOL Star_SRPComm_GetResponseStr(void *c_this,VS_INT8 *Response,const VS_CHAR *Title,VS_CHAR *Buf,VS_INT32 BufSize)
{
    return g_star_CoreFunctionTbl->SRPComm_GetResponseStr(c_this,Response,Title,Buf,BufSize);
}

VS_INT8 *Star_SRPComm_GetResponseBody(void *c_this,VS_INT8 *Response)
{
    return g_star_CoreFunctionTbl->SRPComm_GetResponseBody(c_this,Response);
}

VS_ULONG Star_SRPComm_HttpLocalRequest(void *c_this,VS_HANDLE MsgHandle,VS_ULONG ConnectionGroup,VS_UINT16 MsgClass,VS_UINT8 RequestType,VS_UINT8 BoundaryNumber,VS_UINT64 FileSize,const VS_CHAR  *FileName,const VS_CHAR  *ContentType,const VS_CHAR  *Cookie,VS_ULONG  *BoundaryInfo,const VS_CHAR  *RequestHeader,const VS_CHAR  *RequestBody)
{
    return g_star_CoreFunctionTbl->SRPComm_HttpLocalRequest(c_this,MsgHandle,ConnectionGroup,MsgClass,RequestType,BoundaryNumber,FileSize,FileName,ContentType,Cookie,BoundaryInfo,RequestHeader,RequestBody);
}

VS_ULONG Star_SRPComm_HttpLocalRequestEx(void *c_this,VS_HANDLE MsgHandle,VS_ULONG ConnectionGroup,VS_UINT16 MsgClass,const VS_CHAR *HtmlRequestPlain)
{
    return g_star_CoreFunctionTbl->SRPComm_HttpLocalRequestEx(c_this,MsgHandle,ConnectionGroup,MsgClass,HtmlRequestPlain);
}

VS_ULONG Star_SRPComm_SetupTimer(void *c_this,VS_INT32 Interval,VS_INT32 NumberOfValid,VS_HANDLE MsgHandle,VS_ULONG ConnectionGroup,VS_UINT16 MsgClass)
{
    return g_star_CoreFunctionTbl->SRPComm_SetupTimer(c_this,Interval,NumberOfValid,MsgHandle,ConnectionGroup,MsgClass);
}

void Star_SRPComm_KillTimer(void *c_this,VS_ULONG TimerID)
{
    g_star_CoreFunctionTbl->SRPComm_KillTimer(c_this,TimerID);
}

void *Star_SRPComm_Dup(void *c_this)
{
    return g_star_CoreFunctionTbl->SRPComm_Dup(c_this);
}

void Star_SRPComm_HookManagerMsgProc(void *c_this,VS_ManagerMsgProc ManagerMsgProc)
{
    g_star_CoreFunctionTbl->SRPComm_HookManagerMsgProc(c_this,ManagerMsgProc);
}

VS_BOOL Star_SRPComm_UnHookManagerMsgProc(void *c_this)
{
    return g_star_CoreFunctionTbl->SRPComm_UnHookManagerMsgProc(c_this);
}

VS_ULONG Star_SRPComm_SetupManagerTimer(void *c_this,VS_INT32 Interval,VS_INT32 NumberOfValid,VS_ULONG ConnectionGroup,VS_UINT16 MsgClass)
{
    return g_star_CoreFunctionTbl->SRPComm_SetupManagerTimer(c_this,Interval,NumberOfValid,ConnectionGroup,MsgClass);
}

void Star_SRPComm_FormatRspHeaderEx(void *c_this,const VS_CHAR *RspInfo,const VS_CHAR *ServerInfo,const VS_CHAR *Connection,const VS_CHAR *ContentType,VS_UINT64 ContentLength,const VS_CHAR *ExtendInfo,VS_CHAR *Buf)
{
    g_star_CoreFunctionTbl->SRPComm_FormatRspHeaderEx(c_this,RspInfo,ServerInfo,Connection,ContentType,ContentLength,ExtendInfo,Buf);
}

VS_BOOL Star_SRPComm_Http_GetHeaderItem(void *c_this,const VS_INT8 *Header,VS_INT32 ItemIndex,const VS_CHAR *ItemName,VS_CHAR *RetBuf,VS_INT32 RetBufSize)
{
    return g_star_CoreFunctionTbl->SRPComm_Http_GetHeaderItem(c_this,Header,ItemIndex,ItemName,RetBuf,RetBufSize);
}

VS_BOOL Star_SRPComm_Http_GetHeaderSubItem(void *c_this,const VS_CHAR *Item,VS_INT32 SubItemIndex,const VS_CHAR *SubItemName,VS_CHAR *RetBuf,VS_INT32 RetBufSize )
{
    return g_star_CoreFunctionTbl->SRPComm_Http_GetHeaderSubItem(c_this,Item,SubItemIndex,SubItemName,RetBuf,RetBufSize);
}

VS_BOOL Star_SRPComm_Http_GetNVValue(void *c_this,const VS_CHAR *Buf,const VS_CHAR *Name,VS_CHAR *RetBuf,VS_INT32 RetBufSize)
{
    return g_star_CoreFunctionTbl->SRPComm_Http_GetNVValue(c_this,Buf,Name,RetBuf,RetBufSize);
}

void Star_SRPComm_Http_TimeToHttpTime(void *c_this,VS_TIME_T *Time,VS_CHAR *HttpTimeBuf)
{
    g_star_CoreFunctionTbl->SRPComm_Http_TimeToHttpTime(c_this,Time,HttpTimeBuf);
}

void Star_SRPComm_Http_HttpTimeToTime(void *c_this,VS_CHAR *HttpTimeBuf,VS_TIME_T *Time)
{
    g_star_CoreFunctionTbl->SRPComm_Http_HttpTimeToTime(c_this,HttpTimeBuf,Time);
}

void Star_SRPComm_Http_SetCookie(void *c_this,const VS_CHAR *Domain,const VS_CHAR *Path,const VS_CHAR *Cookie,VS_BOOL Secure)
{
    g_star_CoreFunctionTbl->SRPComm_Http_SetCookie(c_this,Domain,Path,Cookie,Secure);
}

void Star_SRPComm_Http_ClearCookie(void *c_this,const VS_CHAR *Domain,const VS_CHAR *Path,const VS_CHAR *Cookie)
{
    g_star_CoreFunctionTbl->SRPComm_Http_ClearCookie(c_this,Domain,Path,Cookie);
}

VS_CHAR *Star_SRPComm_Http_GetMediaType(void *c_this,const VS_CHAR *FileName)
{
    return g_star_CoreFunctionTbl->SRPComm_Http_GetMediaType(c_this,FileName);
}

void Star_SRPComm_Http_SetMaxPostSize(void *c_this,VS_ULONG ConnectionID,VS_ULONG MaxPostSize)
{
    g_star_CoreFunctionTbl->SRPComm_Http_SetMaxPostSize(c_this,ConnectionID,MaxPostSize);
}

VS_INT8 *Star_SRPComm_Http_GetMultiPart(void *c_this,VS_INT8 *RequestBody,VS_UINT8 Index,VS_UINT8 BoundaryNumber,VS_ULONG  *BoundaryInfo,VS_UINT64 *RetMultiPartBodySize,VS_CHAR *RetBuf,VS_INT32 RetBufSize)
{
    return g_star_CoreFunctionTbl->SRPComm_Http_GetMultiPart(c_this,RequestBody,Index,BoundaryNumber,BoundaryInfo,RetMultiPartBodySize,RetBuf,RetBufSize);
}

void Star_SRPComm_LuaPushHttpOnRequest(void *c_this,VS_ULONG ServiceGroupIndex,struct StructOfSRPComm_HttpOnRequest *HttpOnRequest)
{
    g_star_CoreFunctionTbl->SRPComm_LuaPushHttpOnRequest(c_this,ServiceGroupIndex,HttpOnRequest);
}

VS_BOOL Star_SRPComm_IsTCPConnect(void *c_this,VS_ULONG ConnectionID)
{
    return g_star_CoreFunctionTbl->SRPComm_IsTCPConnect(c_this,ConnectionID);
}

VS_BOOL Star_SRPComm_IsHttpConnect(void *c_this,VS_ULONG ConnectionID)
{
    return g_star_CoreFunctionTbl->SRPComm_IsHttpConnect(c_this,ConnectionID);
}

VS_BOOL Star_SRPComm_FileDownLoad( void *c_this,const VS_CHAR *Url,const VS_CHAR *LocalFileName,VS_BOOL WaitFlag,VS_WebDownInfoProc CallBackProc, VS_UWORD Para)
{
    return g_star_CoreFunctionTbl->SRPComm_FileDownLoad(c_this,Url,LocalFileName,WaitFlag,CallBackProc,Para);
}

VS_BOOL Star_SRPComm_FileUpLoad( void *c_this,const VS_CHAR *Url,const VS_CHAR *LocalFileName,const VS_CHAR *RemoteFileName,void *RetBinBuf,VS_BOOL MultiPartFlag,const VS_CHAR *ContentType,VS_BOOL WaitFlag,VS_WebDownInfoProc CallBackProc, VS_UWORD Para )
{
    return g_star_CoreFunctionTbl->SRPComm_FileUpLoad(c_this,Url,LocalFileName,RemoteFileName,RetBinBuf,MultiPartFlag,ContentType,WaitFlag,CallBackProc,Para);
}

VS_BOOL Star_SRPComm_BufDownLoad( void *c_this,const VS_CHAR *Url,void *BinBuf,VS_BOOL WaitFlag,VS_WebDownInfoProc CallBackProc, VS_UWORD Para )
{
    return g_star_CoreFunctionTbl->SRPComm_BufDownLoad(c_this,Url,BinBuf,WaitFlag,CallBackProc,Para);
}

VS_BOOL Star_SRPComm_BufUpLoad( void *c_this,const VS_CHAR *Url,void *BinBuf,const VS_CHAR *RemoteFileName,void *RetBinBuf,VS_BOOL MultiPartFlag,const VS_CHAR *ContentType,VS_BOOL WaitFlag,VS_WebDownInfoProc CallBackProc, VS_UWORD Para )
{
    return g_star_CoreFunctionTbl->SRPComm_BufUpLoad(c_this,Url,BinBuf,RemoteFileName,RetBinBuf,MultiPartFlag,ContentType,WaitFlag,CallBackProc,Para);
}

void Star_SRPComm_AddRef(void *c_this)
{
    g_star_CoreFunctionTbl->SRPComm_AddRef(c_this);
}

VS_INT32 Star_SRPComm_GetRef(void *c_this)
{
    return g_star_CoreFunctionTbl->SRPComm_GetRef(c_this);
}

void Star_SRPComm_ReleaseOwner(void *c_this)
{
    g_star_CoreFunctionTbl->SRPComm_ReleaseOwner(c_this);
}

void Star_SRPSXML_Release(void *c_this)
{
    g_star_CoreFunctionTbl->SRPSXML_Release(c_this);
}

VS_BOOL Star_SRPSXML_LoadFromFile(void *c_this,const VS_CHAR *FileName,VS_CHAR **ErrorInfo)
{
    return g_star_CoreFunctionTbl->SRPSXML_LoadFromFile(c_this,FileName,ErrorInfo);
}

VS_BOOL Star_SRPSXML_LoadFromBuf(void *c_this,const VS_INT8 *Buf,VS_CHAR **ErrorInfo)
{
    return g_star_CoreFunctionTbl->SRPSXML_LoadFromBuf(c_this,Buf,ErrorInfo);
}

VS_BOOL Star_SRPSXML_SaveToFile(void *c_this,const VS_CHAR *FileName)
{
    return g_star_CoreFunctionTbl->SRPSXML_SaveToFile(c_this,FileName);
}

VS_BOOL Star_SRPSXML_SaveToBuf(void *c_this,void *BinBuf)
{
    return g_star_CoreFunctionTbl->SRPSXML_SaveToBuf(c_this,BinBuf);
}

VS_CHAR *Star_SRPSXML_GetStandalone(void *c_this)
{
    return g_star_CoreFunctionTbl->SRPSXML_GetStandalone(c_this);
}

VS_CHAR *Star_SRPSXML_GetVersion(void *c_this)
{
    return g_star_CoreFunctionTbl->SRPSXML_GetVersion(c_this);
}

VS_CHAR *Star_SRPSXML_GetEncoding(void *c_this)
{
    return g_star_CoreFunctionTbl->SRPSXML_GetEncoding(c_this);
}

void *Star_SRPSXML_FindElement(void *c_this,const VS_CHAR *Value)
{
    return g_star_CoreFunctionTbl->SRPSXML_FindElement(c_this,Value);
}

void *Star_SRPSXML_FindElementEx(void *c_this,void *ParentElement,const VS_CHAR *Value)
{
    return g_star_CoreFunctionTbl->SRPSXML_FindElementEx(c_this,ParentElement,Value);
}

void *Star_SRPSXML_FirstElement(void *c_this,void *ParentElement)
{
    return g_star_CoreFunctionTbl->SRPSXML_FirstElement(c_this,ParentElement);
}

void *Star_SRPSXML_NextElement(void *c_this,void *Element)
{
    return g_star_CoreFunctionTbl->SRPSXML_NextElement(c_this,Element);
}

void *Star_SRPSXML_ParentElement(void *c_this,void *Element)
{
    return g_star_CoreFunctionTbl->SRPSXML_ParentElement(c_this,Element);
}

VS_CHAR *Star_SRPSXML_GetElement(void *c_this,void *Element)
{
    return g_star_CoreFunctionTbl->SRPSXML_GetElement(c_this,Element);
}

void Star_SRPSXML_GetElementEx(void *c_this,void *Element,VS_CHAR *Buf,VS_INT32 BufSize)
{
    g_star_CoreFunctionTbl->SRPSXML_GetElementEx(c_this,Element,Buf,BufSize);
}

VS_BOOL Star_SRPSXML_GetNs(void *c_this,void *Element,VS_CHAR *nsName,VS_INT32 nsNameBufSize,VS_CHAR **nsValue)
{
    return g_star_CoreFunctionTbl->SRPSXML_GetNs(c_this,Element,nsName,nsNameBufSize,nsValue);
}

VS_CHAR *Star_SRPSXML_GetNsValue(void *c_this,void *Element,const VS_CHAR *nsName)
{
    return g_star_CoreFunctionTbl->SRPSXML_GetNsValue(c_this,Element,nsName);
}

void Star_SRPSXML_SetNs(void *c_this,void *Element,const VS_CHAR *nsName,const VS_CHAR *nsValue)
{
    g_star_CoreFunctionTbl->SRPSXML_SetNs(c_this,Element,nsName,nsValue);
}

void *Star_SRPSXML_FindAttribute(void *c_this,void *Element,const VS_CHAR *Name)
{
    return g_star_CoreFunctionTbl->SRPSXML_FindAttribute(c_this,Element,Name);
}

void *Star_SRPSXML_FirstAttribute(void *c_this,void *Element)
{
    return g_star_CoreFunctionTbl->SRPSXML_FirstAttribute(c_this,Element);
}

void *Star_SRPSXML_NextAttribute(void *c_this,void *Attribute)
{
    return g_star_CoreFunctionTbl->SRPSXML_NextAttribute(c_this,Attribute);
}

VS_CHAR *Star_SRPSXML_GetAttributeName(void *c_this,void *Attribute)
{
    return g_star_CoreFunctionTbl->SRPSXML_GetAttributeName(c_this,Attribute);
}

VS_CHAR *Star_SRPSXML_GetAttributeValue(void *c_this,void *Attribute)
{
    return g_star_CoreFunctionTbl->SRPSXML_GetAttributeValue(c_this,Attribute);
}

VS_CHAR *Star_SRPSXML_GetSingleText(void *c_this,void *Element)
{
    return g_star_CoreFunctionTbl->SRPSXML_GetSingleText(c_this,Element);
}

void *Star_SRPSXML_FirstText(void *c_this,void *Element)
{
    return g_star_CoreFunctionTbl->SRPSXML_FirstText(c_this,Element);
}

void *Star_SRPSXML_NextText(void *c_this,void *Text)
{
    return g_star_CoreFunctionTbl->SRPSXML_NextText(c_this,Text);
}

VS_CHAR *Star_SRPSXML_GetText(void *c_this,void *Text)
{
    return g_star_CoreFunctionTbl->SRPSXML_GetText(c_this,Text);
}

void Star_SRPSXML_SetDeclaration(void *c_this,const VS_CHAR *Version,const VS_CHAR *Encoding,const VS_CHAR *Standalone)
{
    g_star_CoreFunctionTbl->SRPSXML_SetDeclaration(c_this,Version,Encoding,Standalone);
}

void Star_SRPSXML_RemoveDeclaration(void *c_this)
{
    g_star_CoreFunctionTbl->SRPSXML_RemoveDeclaration(c_this);
}

void *Star_SRPSXML_InsertElementBefore(void *c_this,void *ParentElement,void *Element,const VS_CHAR *Value)
{
    return g_star_CoreFunctionTbl->SRPSXML_InsertElementBefore(c_this,ParentElement,Element,Value);
}

void *Star_SRPSXML_InsertElementAfter(void *c_this,void *ParentElement,void *Element,const VS_CHAR *Value)
{
    return g_star_CoreFunctionTbl->SRPSXML_InsertElementAfter(c_this,ParentElement,Element,Value);
}

void Star_SRPSXML_RemoveElement(void *c_this,void *Element)
{
    g_star_CoreFunctionTbl->SRPSXML_RemoveElement(c_this,Element);
}

void Star_SRPSXML_SetElement(void *c_this,void *Element,const VS_CHAR *Value)
{
    g_star_CoreFunctionTbl->SRPSXML_SetElement(c_this,Element,Value);
}

void *Star_SRPSXML_InsertTextBefore(void *c_this,void *ParentElement,void *Text,const VS_CHAR *Value,VS_BOOL CDataFlag)
{
    return g_star_CoreFunctionTbl->SRPSXML_InsertTextBefore(c_this,ParentElement,Text,Value,CDataFlag);
}

void *Star_SRPSXML_InsertTextAfter(void *c_this,void *ParentElement,void *Text,const VS_CHAR *Value,VS_BOOL CDataFlag)
{
    return g_star_CoreFunctionTbl->SRPSXML_InsertTextAfter(c_this,ParentElement,Text,Value,CDataFlag);
}

void Star_SRPSXML_RemoveText(void *c_this,void *Text)
{
    g_star_CoreFunctionTbl->SRPSXML_RemoveText(c_this,Text);
}

void Star_SRPSXML_SetText(void *c_this,void *Text,const VS_CHAR *Value,VS_BOOL CDataFlag)
{
    g_star_CoreFunctionTbl->SRPSXML_SetText(c_this,Text,Value,CDataFlag);
}

void *Star_SRPSXML_InsertCommentBefore(void *c_this,void *ParentElement,void *Comment,const VS_CHAR *Value)
{
    return g_star_CoreFunctionTbl->SRPSXML_InsertCommentBefore(c_this,ParentElement,Comment,Value);
}

void *Star_SRPSXML_InsertCommentAfter(void *c_this,void *ParentElement,void *Comment,const VS_CHAR *Value)
{
    return g_star_CoreFunctionTbl->SRPSXML_InsertCommentAfter(c_this,ParentElement,Comment,Value);
}

void Star_SRPSXML_RemoveComment(void *c_this,void *Comment)
{
    g_star_CoreFunctionTbl->SRPSXML_RemoveComment(c_this,Comment);
}

void Star_SRPSXML_SetComment(void *c_this,void *Comment,const VS_CHAR *Value)
{
    g_star_CoreFunctionTbl->SRPSXML_SetComment(c_this,Comment,Value);
}

void Star_SRPSXML_SetAttribute(void *c_this,void *Element,const VS_CHAR *Name,const VS_CHAR *Value)
{
    g_star_CoreFunctionTbl->SRPSXML_SetAttribute(c_this,Element,Name,Value);
}

void Star_SRPSXML_RemoveAttribute(void *c_this,void *Element,const VS_CHAR *Name)
{
    g_star_CoreFunctionTbl->SRPSXML_RemoveAttribute(c_this,Element,Name);
}

VS_INT32 Star_SRPSXML_GetRow(void *c_this,void *Node)
{
    return g_star_CoreFunctionTbl->SRPSXML_GetRow(c_this,Node);
}

VS_INT32 Star_SRPSXML_GetCol(void *c_this,void *Node)
{
    return g_star_CoreFunctionTbl->SRPSXML_GetCol(c_this,Node);
}

void *Star_SRPSXML_Dup(void *c_this)
{
    return g_star_CoreFunctionTbl->SRPSXML_Dup(c_this);
}

VS_BOOL Star_SRPSXML_Copy(void *c_this,void *SrcSXML)
{
    return g_star_CoreFunctionTbl->SRPSXML_Copy(c_this,SrcSXML);
}

void *Star_SRPSXML_CopyElementBefore(void *c_this,void *ParentElement,void *Element,void *SrcElement)
{
    return g_star_CoreFunctionTbl->SRPSXML_CopyElementBefore(c_this,ParentElement,Element,SrcElement);
}

void *Star_SRPSXML_CopyElementAfter(void *c_this,void *ParentElement,void *Element,void *SrcElement)
{
    return g_star_CoreFunctionTbl->SRPSXML_CopyElementAfter(c_this,ParentElement,Element,SrcElement);
}

VS_BOOL Star_SRPSXML_CopyChild(void *c_this,void *DesElement,void *SrcElement)
{
    return g_star_CoreFunctionTbl->SRPSXML_CopyChild(c_this,DesElement,SrcElement);
}

VS_BOOL Star_SRPSXML_LoadFromAnsiBuf(void *c_this,const VS_INT8 *Buf,VS_CHAR **ErrorInfo)
{
    return g_star_CoreFunctionTbl->SRPSXML_LoadFromAnsiBuf(c_this,Buf,ErrorInfo);
}

VS_BOOL Star_SRPSXML_SaveToAnsiBuf(void *c_this,void *BinBuf)
{
    return g_star_CoreFunctionTbl->SRPSXML_SaveToAnsiBuf(c_this,BinBuf);
}

void Star_SRPSXML_AddRef(void *c_this)
{
    g_star_CoreFunctionTbl->SRPSXML_AddRef(c_this);
}

VS_INT32 Star_SRPSXML_GetRef(void *c_this)
{
    return g_star_CoreFunctionTbl->SRPSXML_GetRef(c_this);
}

void Star_SRPSXML_ReleaseOwner(void *c_this)
{
    g_star_CoreFunctionTbl->SRPSXML_ReleaseOwner(c_this);
}

void Star_SRPControl_Release(void *c_this)
{
    g_star_CoreFunctionTbl->SRPControl_Release(c_this);
}

void Star_SRPControl_SRPLock( void *c_this)
{
    g_star_CoreFunctionTbl->SRPControl_SRPLock(c_this);
}

void Star_SRPControl_SRPUnLock( void *c_this)
{
    g_star_CoreFunctionTbl->SRPControl_SRPUnLock(c_this);
}

VS_UINT32 Star_SRPControl_GetOsType( void *c_this)
{
    return g_star_CoreFunctionTbl->SRPControl_GetOsType(c_this);
}

VS_BOOL Star_SRPControl_SRPDispatch(void *c_this,VS_BOOL WaitFlag)
{
    return g_star_CoreFunctionTbl->SRPControl_SRPDispatch(c_this,WaitFlag);
}

VS_BOOL Star_SRPControl_SRPIdle(void *c_this)
{
    return g_star_CoreFunctionTbl->SRPControl_SRPIdle(c_this);
}

void Star_SRPControl_SRPAppActive(void *c_this)
{
    g_star_CoreFunctionTbl->SRPControl_SRPAppActive(c_this);
}

void Star_SRPControl_SRPAppDeactive(void *c_this)
{
    g_star_CoreFunctionTbl->SRPControl_SRPAppDeactive(c_this);
}

VS_BOOL Star_SRPControl_IsAppActive(void *c_this)
{
    return g_star_CoreFunctionTbl->SRPControl_IsAppActive(c_this);
}

void Star_SRPControl_CaptureLuaDisp(void *c_this,void *DispProc,VS_UWORD Para)
{
    g_star_CoreFunctionTbl->SRPControl_CaptureLuaDisp(c_this,DispProc,Para);
}

void Star_SRPControl_ReleaseLuaDisp(void *c_this,void *DispProc,VS_UWORD Para)
{
    g_star_CoreFunctionTbl->SRPControl_ReleaseLuaDisp(c_this,DispProc,Para);
}

VS_BOOL Star_SRPControl_PreCompile(void *c_this,const VS_CHAR *ScriptInterface,const VS_INT8 *ScriptBuf,VS_INT32 ScriptBufSize, const VS_CHAR *Name, VS_CHAR **ErrorInfo)
{
    return g_star_CoreFunctionTbl->SRPControl_PreCompile(c_this,ScriptInterface,ScriptBuf,ScriptBufSize,Name,ErrorInfo);
}

VS_BOOL Star_SRPControl_OpenLuaEdit(void *c_this,const VS_CHAR *Module,VS_ULONG Config,VS_BOOL CloseEnable)
{
    return g_star_CoreFunctionTbl->SRPControl_OpenLuaEdit(c_this,Module,Config,CloseEnable);
}

void Star_SRPControl_LuaEditDisp(void *c_this,const VS_CHAR *Info)
{
    g_star_CoreFunctionTbl->SRPControl_LuaEditDisp(c_this,Info);
}

void Star_SRPControl_CloseLuaEdit(void *c_this)
{
    g_star_CoreFunctionTbl->SRPControl_CloseLuaEdit(c_this);
}

void Star_SRPControl_ClearService(void *c_this )
{
    g_star_CoreFunctionTbl->SRPControl_ClearService(c_this);
}

VS_BOOL Star_SRPControl_DoBuffer( void *c_this,const VS_CHAR *ScriptInterface,const VS_INT8 *ScriptBuf,VS_INT32 ScriptBufSize,VS_BOOL IsUTF8,const VS_CHAR *ModuleName )
{
    return g_star_CoreFunctionTbl->SRPControl_DoBuffer(c_this,ScriptInterface,ScriptBuf,ScriptBufSize,IsUTF8,ModuleName);
}

void Star_SRPControl_PostDoBuffer( void *c_this,const VS_CHAR *ScriptInterface,const VS_INT8 *ScriptBuf,VS_INT32 ScriptBufSize,VS_BOOL IsUTF8,const VS_CHAR *ModuleName )
{
    g_star_CoreFunctionTbl->SRPControl_PostDoBuffer(c_this,ScriptInterface,ScriptBuf,ScriptBufSize,IsUTF8,ModuleName);
}

VS_BOOL Star_SRPControl_DoFile( void *c_this,const VS_CHAR *ScriptInterface,const VS_CHAR *FileName, VS_CHAR **ErrorInfo, const VS_CHAR *WorkDirectory, VS_BOOL IsUTF8 )
{
    return g_star_CoreFunctionTbl->SRPControl_DoFile(c_this,ScriptInterface,FileName,ErrorInfo,WorkDirectory,IsUTF8);
}

VS_BOOL Star_SRPControl_PostDoFile( void *c_this,const VS_CHAR *ScriptInterface,const VS_CHAR *FileName, VS_CHAR **ErrorInfo, const VS_CHAR *WorkDirectory, VS_BOOL IsUTF8 )
{
    return g_star_CoreFunctionTbl->SRPControl_PostDoFile(c_this,ScriptInterface,FileName,ErrorInfo,WorkDirectory,IsUTF8);
}

void Star_SRPControl_LuaEditHelp(void *c_this,VS_INT32 Type,const VS_CHAR *HelpInfo)
{
    g_star_CoreFunctionTbl->SRPControl_LuaEditHelp(c_this,Type,HelpInfo);
}

void *Star_SRPControl_QueryBasicInterface( void *c_this,VS_ULONG ServiceGroupID )
{
    return g_star_CoreFunctionTbl->SRPControl_QueryBasicInterface(c_this,ServiceGroupID);
}

void *Star_SRPControl_CreateBasicInterface( void *c_this,VS_ULONG ServiceGroupID, VS_UINT16 ProgramRunType )
{
    return g_star_CoreFunctionTbl->SRPControl_CreateBasicInterface(c_this,ServiceGroupID,ProgramRunType);
}

void Star_SRPControl_DeleteBasicInterface( void *c_this,VS_ULONG ServiceGroupID )
{
    g_star_CoreFunctionTbl->SRPControl_DeleteBasicInterface(c_this,ServiceGroupID);
}

VS_ULONG Star_SRPControl_QueryFirstServiceGroup( void *c_this)
{
    return g_star_CoreFunctionTbl->SRPControl_QueryFirstServiceGroup(c_this);
}

VS_ULONG Star_SRPControl_QueryNextServiceGroup( void *c_this)
{
    return g_star_CoreFunctionTbl->SRPControl_QueryNextServiceGroup(c_this);
}

void *Star_SRPControl_GetLuaStack( void *c_this)
{
    return g_star_CoreFunctionTbl->SRPControl_GetLuaStack(c_this);
}

VS_UINT32 Star_SRPControl_LuaGetTableInt( void *c_this,void *L, VS_INT32 Index, const VS_CHAR *ValueName )
{
    return g_star_CoreFunctionTbl->SRPControl_LuaGetTableInt(c_this,L,Index,ValueName);
}

VS_UINT32 Star_SRPControl_LuaGetInt( void *c_this,void *L, VS_INT32 Index )
{
    return g_star_CoreFunctionTbl->SRPControl_LuaGetInt(c_this,L,Index);
}

VS_INT32 Star_SRPControl_LuaUpValueIndex( void *c_this,void *L, VS_INT32 Index )
{
    return g_star_CoreFunctionTbl->SRPControl_LuaUpValueIndex(c_this,L,Index);
}

VS_ULONG Star_SRPControl_GetObjectServiceGroupID( void *c_this,void *Object )
{
    return g_star_CoreFunctionTbl->SRPControl_GetObjectServiceGroupID(c_this,Object);
}

void Star_SRPControl_GetUrl(void *c_this,VS_CHAR *Buf,VS_INT32 BufSize)
{
    g_star_CoreFunctionTbl->SRPControl_GetUrl(c_this,Buf,BufSize);
}

void Star_SRPControl_SetProgramType(void *c_this,VS_UINT16 Type)
{
    g_star_CoreFunctionTbl->SRPControl_SetProgramType(c_this,Type);
}

VS_UINT16 Star_SRPControl_GetProgramType(void *c_this)
{
    return g_star_CoreFunctionTbl->SRPControl_GetProgramType(c_this);
}

VS_BOOL Star_SRPControl_SRPBuild_QueryPublicService(void *c_this,void *QueryPublicServiceCallBackProc,VS_UWORD CallBackPara,VS_BOOL FillUpdateInfo,void *PrintProc,VS_UWORD Para)
{
    return g_star_CoreFunctionTbl->SRPControl_SRPBuild_QueryPublicService(c_this,QueryPublicServiceCallBackProc,CallBackPara,FillUpdateInfo,PrintProc,Para);
}

VS_BOOL Star_SRPControl_SRPBuild_QueryPublicServiceEx(void *c_this,const VS_CHAR *Url,void *QueryPublicServiceCallBackProc,VS_UWORD CallBackPara,VS_BOOL FillUpdateInfo,void *PrintProc,VS_UWORD Para)
{
    return g_star_CoreFunctionTbl->SRPControl_SRPBuild_QueryPublicServiceEx(c_this,Url,QueryPublicServiceCallBackProc,CallBackPara,FillUpdateInfo,PrintProc,Para);
}

VS_BOOL Star_SRPControl_SRPBuild_Start(void *c_this,const VS_CHAR *Name,const VS_CHAR *Path,VS_BOOL SingleFlag,VS_BOOL ForceToDownLoadPublicService,void *PrintProc,VS_UWORD Para,struct VSPublicServiceDef *PublicServiceList,VS_BOOL ExeFileFlag,const VS_CHAR *ScriptInterface,VS_UINT32 SupportOsType)
{
    return g_star_CoreFunctionTbl->SRPControl_SRPBuild_Start(c_this,Name,Path,SingleFlag,ForceToDownLoadPublicService,PrintProc,Para,PublicServiceList,ExeFileFlag,ScriptInterface,SupportOsType);
}

void Star_SRPControl_SRPBuild_InsertServiceFile(void *c_this,const VS_CHAR *DiskFileName,const VS_CHAR *OutFileName,VS_BOOL StartFileFlag,VS_BOOL ToUTF8,VS_UINT32 SupportOsType)
{
    g_star_CoreFunctionTbl->SRPControl_SRPBuild_InsertServiceFile(c_this,DiskFileName,OutFileName,StartFileFlag,ToUTF8,SupportOsType);
}

void Star_SRPControl_SRPBuild_InsertDependFile(void *c_this,const VS_CHAR *Path,const VS_CHAR *DependName)
{
    g_star_CoreFunctionTbl->SRPControl_SRPBuild_InsertDependFile(c_this,Path,DependName);
}

void Star_SRPControl_SRPBuild_InsertStaticDataFile(void *c_this,const VS_CHAR *DiskFileName,const VS_CHAR *OutFileName,VS_BOOL ToUTF8)
{
    g_star_CoreFunctionTbl->SRPControl_SRPBuild_InsertStaticDataFile(c_this,DiskFileName,OutFileName,ToUTF8);
}

void Star_SRPControl_SRPBuild_InsertDynaDataFile(void *c_this,const VS_CHAR *DiskFileName,const VS_CHAR *OutFileName,VS_BOOL ToUTF8)
{
    g_star_CoreFunctionTbl->SRPControl_SRPBuild_InsertDynaDataFile(c_this,DiskFileName,OutFileName,ToUTF8);
}

VS_BOOL Star_SRPControl_SRPBuild_Execute(void *c_this)
{
    return g_star_CoreFunctionTbl->SRPControl_SRPBuild_Execute(c_this);
}

VS_BOOL Star_SRPControl_StringToUuid(void *c_this,const VS_INT8 *String,VS_UUID *Uuid)
{
    return g_star_CoreFunctionTbl->SRPControl_StringToUuid(c_this,String,Uuid);
}

VS_INT8 *Star_SRPControl_UuidToString(void *c_this,VS_UUID *Uuid)
{
    return g_star_CoreFunctionTbl->SRPControl_UuidToString(c_this,Uuid);
}

VS_BOOL Star_SRPControl_MD5ToUuid(void *c_this,const VS_INT8 *String,VS_UUID *Uuid)
{
    return g_star_CoreFunctionTbl->SRPControl_MD5ToUuid(c_this,String,Uuid);
}

VS_INT8 *Star_SRPControl_UuidToMD5(void *c_this,VS_UUID *Uuid)
{
    return g_star_CoreFunctionTbl->SRPControl_UuidToMD5(c_this,Uuid);
}

VS_INT8 *Star_SRPControl_GetMD5(void *c_this,VS_INT8 *Buf,VS_INT32 BufSize)
{
    return g_star_CoreFunctionTbl->SRPControl_GetMD5(c_this,Buf,BufSize);
}

void Star_SRPControl_CreateUuid(void *c_this,VS_UUID *UuidPtr)
{
    g_star_CoreFunctionTbl->SRPControl_CreateUuid(c_this,UuidPtr);
}

void *Star_SRPControl_GetSXMLInterface(void *c_this)
{
    return g_star_CoreFunctionTbl->SRPControl_GetSXMLInterface(c_this);
}

void *Star_SRPControl_GetCommInterface(void *c_this)
{
    return g_star_CoreFunctionTbl->SRPControl_GetCommInterface(c_this);
}

void *Star_SRPControl_GetCoreShellInterface(void *c_this)
{
    return g_star_CoreFunctionTbl->SRPControl_GetCoreShellInterface(c_this);
}

VS_BOOL Star_SRPControl_RegScriptInterface(void *c_this,const VS_CHAR *ScriptInterface,struct StructOfVSScriptContext *ScriptContext,VS_UWORD Para,void *TermProc)
{
    return g_star_CoreFunctionTbl->SRPControl_RegScriptInterface(c_this,ScriptInterface,ScriptContext,Para,TermProc);
}

VS_BOOL Star_SRPControl_UnRegScriptInterface(void *c_this,const VS_CHAR *ScriptInterface,struct StructOfVSScriptContext *ScriptContext,VS_UWORD Para,void *TermProc)
{
    return g_star_CoreFunctionTbl->SRPControl_UnRegScriptInterface(c_this,ScriptInterface,ScriptContext,Para,TermProc);
}

VS_BOOL Star_SRPControl_ActiveScriptInterface(void *c_this,const VS_CHAR *ScriptInterface,VS_BOOL *OnLineScriptFlag,void *VirtualMachine)
{
    return g_star_CoreFunctionTbl->SRPControl_ActiveScriptInterface(c_this,ScriptInterface,OnLineScriptFlag,VirtualMachine);
}

VS_CHAR *Star_SRPControl_FirstScriptInterface(void *c_this,VS_QUERYRECORD *QueryRecord)
{
    return g_star_CoreFunctionTbl->SRPControl_FirstScriptInterface(c_this,QueryRecord);
}

VS_CHAR *Star_SRPControl_NextScriptInterface(void *c_this,VS_QUERYRECORD *QueryRecord)
{
    return g_star_CoreFunctionTbl->SRPControl_NextScriptInterface(c_this,QueryRecord);
}

VS_BOOL Star_SRPControl_RegTempFile(void *c_this,const VS_CHAR *TempFileName,const VS_CHAR *OriFileName)
{
    return g_star_CoreFunctionTbl->SRPControl_RegTempFile(c_this,TempFileName,OriFileName);
}

VS_CHAR *Star_SRPControl_GetRegTempFile(void *c_this,const VS_CHAR *OriFileName,VS_CHAR *Buf,VS_INT32 BufSize)
{
    return g_star_CoreFunctionTbl->SRPControl_GetRegTempFile(c_this,OriFileName,Buf,BufSize);
}

void Star_SRPControl_UnRegTempFile(void *c_this,const VS_CHAR *TempFileName)
{
    g_star_CoreFunctionTbl->SRPControl_UnRegTempFile(c_this,TempFileName);
}

void Star_SRPControl_GetConfigResult(void *c_this,VS_BOOL *DebugCfgResult,VS_BOOL *DirectClientCfgResult,VS_BOOL *TelnetCfgResult,VS_BOOL *WebServerCfgResult)
{
    g_star_CoreFunctionTbl->SRPControl_GetConfigResult(c_this,DebugCfgResult,DirectClientCfgResult,TelnetCfgResult,WebServerCfgResult);
}

VS_CHAR *Star_SRPControl_GetConfigEnvTag( void *c_this)
{
    return g_star_CoreFunctionTbl->SRPControl_GetConfigEnvTag(c_this);
}

void *Star_SRPControl_Dup(void *c_this)
{
    return g_star_CoreFunctionTbl->SRPControl_Dup(c_this);
}

void *Star_SRPControl_QueryInterface( void *c_this,VS_UUID *InterfaceID )
{
    return g_star_CoreFunctionTbl->SRPControl_QueryInterface(c_this,InterfaceID);
}

void Star_SRPControl_AddRef(void *c_this)
{
    g_star_CoreFunctionTbl->SRPControl_AddRef(c_this);
}

VS_INT32 Star_SRPControl_GetRef(void *c_this)
{
    return g_star_CoreFunctionTbl->SRPControl_GetRef(c_this);
}

void Star_SRPControl_SetLogFile(void *c_this,const VS_CHAR *FileName,VS_BOOL LogAll)
{
    g_star_CoreFunctionTbl->SRPControl_SetLogFile(c_this,FileName,LogAll);
}

void Star_SRPControl_GetSystemRegCode(void *c_this,VS_CHAR *Buf)
{
    g_star_CoreFunctionTbl->SRPControl_GetSystemRegCode(c_this,Buf);
}

VS_BOOL Star_SRPControl_SetRegisterCode(void *c_this,const VS_CHAR *Buf,VS_BOOL Single)
{
    return g_star_CoreFunctionTbl->SRPControl_SetRegisterCode(c_this,Buf,Single);
}

VS_BOOL Star_SRPControl_IsRegistered(void *c_this)
{
    return g_star_CoreFunctionTbl->SRPControl_IsRegistered(c_this);
}

VS_ULONG Star_SRPControl_GetHashValue(void *c_this,void *Key,VS_ULONG Length,VS_ULONG InitValue)
{
    return g_star_CoreFunctionTbl->SRPControl_GetHashValue(c_this,Key,Length,InitValue);
}

void Star_SRPControl_ScriptStarcoreRecord(void *c_this,const VS_CHAR *ScriptInterface,VS_HANDLE SharelibHandle)
{
    g_star_CoreFunctionTbl->SRPControl_ScriptStarcoreRecord(c_this,ScriptInterface,SharelibHandle);
}

void Star_SRPControl_ScriptStarcoreUnRecord(void *c_this,const VS_CHAR *ScriptInterface,VS_HANDLE SharelibHandle)
{
    g_star_CoreFunctionTbl->SRPControl_ScriptStarcoreUnRecord(c_this,ScriptInterface,SharelibHandle);
}

VS_BOOL Star_SRPControl_ScriptStarcoreIsRecord(void *c_this,const VS_CHAR *ScriptInterface)
{
    return g_star_CoreFunctionTbl->SRPControl_ScriptStarcoreIsRecord(c_this,ScriptInterface);
}

VS_UWORD Star_SRPControl_FindWindow(void *c_this,const VS_CHAR *Caption)
{
    return g_star_CoreFunctionTbl->SRPControl_FindWindow(c_this,Caption);
}

VS_BOOL Star_SRPControl_WinMsgLoop(void *c_this,VS_BOOL *QuitFlag)
{
    return g_star_CoreFunctionTbl->SRPControl_WinMsgLoop(c_this,QuitFlag);
}

void Star_SRPControl_RegScriptObject(void *c_this,VS_UWORD ScriptObject,void *FreeScriptObjectProc,VS_UWORD Para)
{
    g_star_CoreFunctionTbl->SRPControl_RegScriptObject(c_this,ScriptObject,FreeScriptObjectProc,Para);
}

void Star_SRPControl_UnRegScriptObject(void *c_this,VS_UWORD ScriptObject,void *FreeScriptObjectProc,VS_UWORD Para)
{
    g_star_CoreFunctionTbl->SRPControl_UnRegScriptObject(c_this,ScriptObject,FreeScriptObjectProc,Para);
}

void Star_SRPControl_ClearScriptObject(void *c_this,void *FreeScriptObjectProc,VS_UWORD Para)
{
    g_star_CoreFunctionTbl->SRPControl_ClearScriptObject(c_this,FreeScriptObjectProc,Para);
}

VS_BOOL Star_SRPControl_PreAuthorize(void *c_this,const VS_CHAR *ServiceName,VS_UUID *ServiceID,const VS_CHAR *Buf,VS_BOOL Single)
{
    return g_star_CoreFunctionTbl->SRPControl_PreAuthorize(c_this,ServiceName,ServiceID,Buf,Single);
}

void Star_SRPControl_SetLocale(void *c_this,const VS_CHAR *Lang)
{
    g_star_CoreFunctionTbl->SRPControl_SetLocale(c_this,Lang);
}

VS_CHAR *Star_SRPControl_GetLocale(void *c_this)
{
    return g_star_CoreFunctionTbl->SRPControl_GetLocale(c_this);
}

void Star_SRPControl_SetScriptInterfaceIndex(void *c_this,const VS_CHAR *ScriptInterfaceName)
{
    g_star_CoreFunctionTbl->SRPControl_SetScriptInterfaceIndex(c_this,ScriptInterfaceName);
}

VS_INT32 Star_SRPControl_GetScriptInterfaceIndex(void *c_this,const VS_CHAR *ScriptInterfaceName)
{
    return g_star_CoreFunctionTbl->SRPControl_GetScriptInterfaceIndex(c_this,ScriptInterfaceName);
}

void Star_SRPControl_DetachCurrentThread(void *c_this)
{
    g_star_CoreFunctionTbl->SRPControl_DetachCurrentThread(c_this);
}

VS_BOOL Star_SRPControl_DoFileEx( void *c_this,const VS_CHAR *ScriptInterface,const VS_CHAR *FileName, VS_CHAR **ErrorInfo, const VS_CHAR *WorkDirectory, VS_BOOL IsUTF8,const VS_CHAR *ModuleName )
{
    return g_star_CoreFunctionTbl->SRPControl_DoFileEx(c_this,ScriptInterface,FileName,ErrorInfo,WorkDirectory,IsUTF8,ModuleName);
}

VS_BOOL Star_SRPControl_PostDoFileEx( void *c_this,const VS_CHAR *ScriptInterface,const VS_CHAR *FileName, VS_CHAR **ErrorInfo, const VS_CHAR *WorkDirectory, VS_BOOL IsUTF8,const VS_CHAR *ModuleName )
{
    return g_star_CoreFunctionTbl->SRPControl_PostDoFileEx(c_this,ScriptInterface,FileName,ErrorInfo,WorkDirectory,IsUTF8,ModuleName);
}

void Star_SRPControl_ReleaseOwner(void *c_this)
{
    g_star_CoreFunctionTbl->SRPControl_ReleaseOwner(c_this);
}

VS_INT32 Star_SRPControl_GetLastError(void *c_this)
{
    return g_star_CoreFunctionTbl->SRPControl_GetLastError(c_this);
}

VS_CHAR *Star_SRPControl_GetLastErrorInfo(void *c_this,VS_UINT32 *LineIndex,VS_CHAR **SourceName)
{
    return g_star_CoreFunctionTbl->SRPControl_GetLastErrorInfo(c_this,LineIndex,SourceName);
}

VS_BOOL Star_SRPControl_SetScriptInterface(void *c_this,const VS_CHAR *ScriptInterface,const VS_CHAR *Module,const VS_CHAR *Para)
{
    return g_star_CoreFunctionTbl->SRPControl_SetScriptInterface(c_this,ScriptInterface,Module,Para);
}

VS_CHAR *Star_SRPControl_SetCoreOperationPath(void *c_this,const VS_CHAR *Path)
{
    return g_star_CoreFunctionTbl->SRPControl_SetCoreOperationPath(c_this,Path);
}

void *Star_SRPControl_GetCFunctionTable(void *c_this)
{
    return g_star_CoreFunctionTbl->SRPControl_GetCFunctionTable(c_this);
}

VS_UINT64 Star_SRPControl_LuaGetTableInt64(void *c_this, void *L, VS_INT32 Index, const VS_CHAR *ValueName)
{
    return g_star_CoreFunctionTbl->SRPControl_LuaGetTableInt64(c_this,L,Index,ValueName);
}

VS_UINT64 Star_SRPControl_LuaGetInt64(void *c_this, void *L, VS_INT32 Index)
{
    return g_star_CoreFunctionTbl->SRPControl_LuaGetInt64(c_this,L,Index);
}

VS_UWORD Star_SRPControl_LuaGetTableUWord(void *c_this, void *L, VS_INT32 Index, const VS_CHAR *ValueName)
{
    return g_star_CoreFunctionTbl->SRPControl_LuaGetTableUWord(c_this,L,Index,ValueName);
}

VS_UWORD Star_SRPControl_LuaGetUWord(void *c_this, void *L, VS_INT32 Index)
{
    return g_star_CoreFunctionTbl->SRPControl_LuaGetUWord(c_this,L,Index);
}

void *Star_SRPControl_RegisterProc(void *c_this,VS_CHAR *FunctionName,void *FunctionProc)
{
    return g_star_CoreFunctionTbl->SRPControl_RegisterProc(c_this,FunctionName,FunctionProc);
}

VS_UWORD Star_SRPControl_RunInMainThread(void *c_this,void* CallBack, VS_UWORD Para1, VS_UWORD Para2, VS_UWORD Para3, VS_UWORD Para4)
{
    return g_star_CoreFunctionTbl->SRPControl_RunInMainThread(c_this,CallBack,Para1,Para2,Para3,Para4);
}

void Star_SRPControl_RegDispatchRequest(void *c_this,void *CallBack,VS_UWORD Para)
{
    g_star_CoreFunctionTbl->SRPControl_RegDispatchRequest(c_this,CallBack,Para);
}

void Star_SRPControl_UnRegDispatchRequest(void *c_this,void *CallBack,VS_UWORD Para)
{
    g_star_CoreFunctionTbl->SRPControl_UnRegDispatchRequest(c_this,CallBack,Para);
}

void Star_SRPBasic_Release(void *c_this)
{
    g_star_CoreFunctionTbl->SRPBasic_Release(c_this);
}

VS_UINT32 Star_SRPBasic_GetOsType(void *c_this )
{
    return g_star_CoreFunctionTbl->SRPBasic_GetOsType(c_this);
}

void Star_SRPBasic_SetPrintToLua(void *c_this,VS_BOOL PrintFlag)
{
    g_star_CoreFunctionTbl->SRPBasic_SetPrintToLua(c_this,PrintFlag);
}

void Star_SRPBasic_CaptureLuaDisp(void *c_this,void *DispProc,VS_UWORD Para)
{
    g_star_CoreFunctionTbl->SRPBasic_CaptureLuaDisp(c_this,DispProc,Para);
}

void Star_SRPBasic_ReleaseLuaDisp(void *c_this,void *DispProc,VS_UWORD Para)
{
    g_star_CoreFunctionTbl->SRPBasic_ReleaseLuaDisp(c_this,DispProc,Para);
}

void Star_SRPBasic_SetDefaultPath(void *c_this,const VS_CHAR *DefaultPath)
{
    g_star_CoreFunctionTbl->SRPBasic_SetDefaultPath(c_this,DefaultPath);
}

void Star_SRPBasic_GetDefaultPath(void *c_this,VS_CHAR *DefaultPath,VS_INT32 BufSize)
{
    g_star_CoreFunctionTbl->SRPBasic_GetDefaultPath(c_this,DefaultPath,BufSize);
}

VS_BOOL Star_SRPBasic_DefaultPathIsSet(void *c_this)
{
    return g_star_CoreFunctionTbl->SRPBasic_DefaultPathIsSet(c_this);
}

VS_ULONG Star_SRPBasic_Connect(void *c_this,const VS_CHAR *ServerInterface,const VS_CHAR *ServerName,VS_UINT16 ServerPortNumber,VS_INT32 RetrySecond,void *ParaPkg,void *ClientConnectCallBack,VS_UWORD Para,const VS_CHAR *LoginName,const VS_CHAR *LoginPassword)
{
    return g_star_CoreFunctionTbl->SRPBasic_Connect(c_this,ServerInterface,ServerName,ServerPortNumber,RetrySecond,ParaPkg,ClientConnectCallBack,Para,LoginName,LoginPassword);
}

VS_ULONG Star_SRPBasic_ConnectEx(void *c_this,const VS_CHAR *ServiceName,VS_INT32 RetrySecond,void *ParaPkg,void *ClientConnectCallBack,VS_UWORD Para,const VS_CHAR *LoginName,const VS_CHAR *LoginPassword)
{
    return g_star_CoreFunctionTbl->SRPBasic_ConnectEx(c_this,ServiceName,RetrySecond,ParaPkg,ClientConnectCallBack,Para,LoginName,LoginPassword);
}

VS_ULONG Star_SRPBasic_SConnect(void *c_this,const VS_CHAR *ServerInterface,const VS_CHAR *ServerName,VS_UINT16 ServerPortNumber,void *ParaPkg,const VS_CHAR *LoginName,const VS_CHAR *LoginPassword)
{
    return g_star_CoreFunctionTbl->SRPBasic_SConnect(c_this,ServerInterface,ServerName,ServerPortNumber,ParaPkg,LoginName,LoginPassword);
}

VS_ULONG Star_SRPBasic_SConnectEx(void *c_this,const VS_CHAR *ServiceName,void *ParaPkg,const VS_CHAR *LoginName,const VS_CHAR *LoginPassword)
{
    return g_star_CoreFunctionTbl->SRPBasic_SConnectEx(c_this,ServiceName,ParaPkg,LoginName,LoginPassword);
}

void *Star_SRPBasic_Connect2(void *c_this, const VS_CHAR *ServerInterface,const VS_CHAR *ServerName,VS_UINT16 ServerPortNumber,void *ParaPkg,const VS_CHAR *LoginName,const VS_CHAR *LoginPassword, const VS_CHAR *SysRootItemName )
{
    return g_star_CoreFunctionTbl->SRPBasic_Connect2(c_this,ServerInterface,ServerName,ServerPortNumber,ParaPkg,LoginName,LoginPassword,SysRootItemName);
}

void *Star_SRPBasic_ConnectEx2(void *c_this, const VS_CHAR *ServiceName,void *ParaPkg,const VS_CHAR *LoginName,const VS_CHAR *LoginPassword, const VS_CHAR *SysRootItemName )
{
    return g_star_CoreFunctionTbl->SRPBasic_ConnectEx2(c_this,ServiceName,ParaPkg,LoginName,LoginPassword,SysRootItemName);
}

void Star_SRPBasic_DisConnectEx(void *c_this,VS_ULONG ConnectionID)
{
    g_star_CoreFunctionTbl->SRPBasic_DisConnectEx(c_this,ConnectionID);
}

void Star_SRPBasic_DisConnect(void *c_this)
{
    g_star_CoreFunctionTbl->SRPBasic_DisConnect(c_this);
}

VS_BOOL Star_SRPBasic_IsConnect(void *c_this)
{
    return g_star_CoreFunctionTbl->SRPBasic_IsConnect(c_this);
}

void *Star_SRPBasic_GetLua(void *c_this )
{
    return g_star_CoreFunctionTbl->SRPBasic_GetLua(c_this);
}

VS_BOOL Star_SRPBasic_DoBuffer(void *c_this, const VS_CHAR *ScriptInterface,const VS_INT8 *ScriptBuf,VS_INT32 ScriptBufSize,VS_BOOL IsUTF8,const VS_CHAR *ModuleName )
{
    return g_star_CoreFunctionTbl->SRPBasic_DoBuffer(c_this,ScriptInterface,ScriptBuf,ScriptBufSize,IsUTF8,ModuleName);
}

VS_BOOL Star_SRPBasic_LuaToBool(void *c_this, VS_INT32 Index )
{
    return g_star_CoreFunctionTbl->SRPBasic_LuaToBool(c_this,Index);
}

VS_CHAR *Star_SRPBasic_LuaToString(void *c_this, VS_INT32 Index )
{
    return g_star_CoreFunctionTbl->SRPBasic_LuaToString(c_this,Index);
}

VS_DOUBLE Star_SRPBasic_LuaToNumber(void *c_this, VS_INT32 Index )
{
    return g_star_CoreFunctionTbl->SRPBasic_LuaToNumber(c_this,Index);
}

VS_INT32 Star_SRPBasic_LuaToInt(void *c_this, VS_INT32 Index )
{
    return g_star_CoreFunctionTbl->SRPBasic_LuaToInt(c_this,Index);
}

VS_BOOL Star_SRPBasic_LuaIsBool(void *c_this, VS_INT32 Index )
{
    return g_star_CoreFunctionTbl->SRPBasic_LuaIsBool(c_this,Index);
}

VS_BOOL Star_SRPBasic_LuaIsString(void *c_this, VS_INT32 Index )
{
    return g_star_CoreFunctionTbl->SRPBasic_LuaIsString(c_this,Index);
}

VS_BOOL Star_SRPBasic_LuaIsNumber(void *c_this, VS_INT32 Index )
{
    return g_star_CoreFunctionTbl->SRPBasic_LuaIsNumber(c_this,Index);
}

void Star_SRPBasic_LuaGetGlobal(void *c_this, const VS_CHAR *Name )
{
    g_star_CoreFunctionTbl->SRPBasic_LuaGetGlobal(c_this,Name);
}

void Star_SRPBasic_LuaGetSrvGroupTable(void *c_this, const VS_CHAR *Name )
{
    g_star_CoreFunctionTbl->SRPBasic_LuaGetSrvGroupTable(c_this,Name);
}

void Star_SRPBasic_LuaPop(void *c_this, VS_INT32 Index )
{
    g_star_CoreFunctionTbl->SRPBasic_LuaPop(c_this,Index);
}

void Star_SRPBasic_LuaPushBool(void *c_this, VS_BOOL Value )
{
    g_star_CoreFunctionTbl->SRPBasic_LuaPushBool(c_this,Value);
}

void Star_SRPBasic_LuaPushString(void *c_this, const VS_CHAR *Value )
{
    g_star_CoreFunctionTbl->SRPBasic_LuaPushString(c_this,Value);
}

void Star_SRPBasic_LuaPushNumber(void *c_this, VS_DOUBLE Value )
{
    g_star_CoreFunctionTbl->SRPBasic_LuaPushNumber(c_this,Value);
}

void Star_SRPBasic_LuaPushInt(void *c_this, VS_INT32 Value )
{
    g_star_CoreFunctionTbl->SRPBasic_LuaPushInt(c_this,Value);
}

void Star_SRPBasic_LuaPushNil(void *c_this )
{
    g_star_CoreFunctionTbl->SRPBasic_LuaPushNil(c_this);
}

void Star_SRPBasic_LuaSetGlobal(void *c_this, const VS_CHAR *Name )
{
    g_star_CoreFunctionTbl->SRPBasic_LuaSetGlobal(c_this,Name);
}

void Star_SRPBasic_LuaSetSrvGroupTable(void *c_this, const VS_CHAR *Name )
{
    g_star_CoreFunctionTbl->SRPBasic_LuaSetSrvGroupTable(c_this,Name);
}

VS_BOOL Star_SRPBasic_LuaIsNil(void *c_this, VS_INT32 Index )
{
    return g_star_CoreFunctionTbl->SRPBasic_LuaIsNil(c_this,Index);
}

void Star_SRPBasic_LuaNewTable(void *c_this )
{
    g_star_CoreFunctionTbl->SRPBasic_LuaNewTable(c_this);
}

VS_BOOL Star_SRPBasic_LuaIsTable(void *c_this, VS_INT32 Index )
{
    return g_star_CoreFunctionTbl->SRPBasic_LuaIsTable(c_this,Index);
}

VS_INT32 Star_SRPBasic_LuaGetTop(void *c_this)
{
    return g_star_CoreFunctionTbl->SRPBasic_LuaGetTop(c_this);
}

VS_INT32 Star_SRPBasic_LuaObjLen(void *c_this,VS_INT32 TableIndex)
{
    return g_star_CoreFunctionTbl->SRPBasic_LuaObjLen(c_this,TableIndex);
}

void Star_SRPBasic_LuaPushLString(void *c_this, const VS_CHAR *Value, VS_ULONG Len )
{
    g_star_CoreFunctionTbl->SRPBasic_LuaPushLString(c_this,Value,Len);
}

VS_BOOL Star_SRPBasic_LuaPushParaPkg(void *c_this, void *ParaPkg, VS_BOOL AutoRelease )
{
    return g_star_CoreFunctionTbl->SRPBasic_LuaPushParaPkg(c_this,ParaPkg,AutoRelease);
}

VS_BOOL Star_SRPBasic_LuaPushQueryRecord(void *c_this, VS_QUERYRECORD *QueryRecord, VS_BOOL AutoRelease )
{
    return g_star_CoreFunctionTbl->SRPBasic_LuaPushQueryRecord(c_this,QueryRecord,AutoRelease);
}

void *Star_SRPBasic_LuaToParaPkg(void *c_this, VS_INT32 Index )
{
    return g_star_CoreFunctionTbl->SRPBasic_LuaToParaPkg(c_this,Index);
}

VS_QUERYRECORD *Star_SRPBasic_LuaToQueryRecord(void *c_this, VS_INT32 Index )
{
    return g_star_CoreFunctionTbl->SRPBasic_LuaToQueryRecord(c_this,Index);
}

VS_BOOL Star_SRPBasic_LuaIsParaPkg(void *c_this, VS_INT32 Index )
{
    return g_star_CoreFunctionTbl->SRPBasic_LuaIsParaPkg(c_this,Index);
}

VS_BOOL Star_SRPBasic_LuaIsQueryRecord(void *c_this, VS_INT32 Index )
{
    return g_star_CoreFunctionTbl->SRPBasic_LuaIsQueryRecord(c_this,Index);
}

VS_BOOL Star_SRPBasic_LuaPushBinBuf(void *c_this, void *BinBuf, VS_BOOL AutoRelease )
{
    return g_star_CoreFunctionTbl->SRPBasic_LuaPushBinBuf(c_this,BinBuf,AutoRelease);
}

void *Star_SRPBasic_LuaToBinBuf(void *c_this, VS_INT32 Index )
{
    return g_star_CoreFunctionTbl->SRPBasic_LuaToBinBuf(c_this,Index);
}

VS_BOOL Star_SRPBasic_LuaIsBinBuf(void *c_this, VS_INT32 Index )
{
    return g_star_CoreFunctionTbl->SRPBasic_LuaIsBinBuf(c_this,Index);
}

VS_BOOL Star_SRPBasic_LuaPushSXml(void *c_this, void *SXml, VS_BOOL AutoRelease )
{
    return g_star_CoreFunctionTbl->SRPBasic_LuaPushSXml(c_this,SXml,AutoRelease);
}

void *Star_SRPBasic_LuaToSXml(void *c_this, VS_INT32 Index )
{
    return g_star_CoreFunctionTbl->SRPBasic_LuaToSXml(c_this,Index);
}

VS_BOOL Star_SRPBasic_LuaIsSXml(void *c_this, VS_INT32 Index )
{
    return g_star_CoreFunctionTbl->SRPBasic_LuaIsSXml(c_this,Index);
}

VS_BOOL Star_SRPBasic_LuaPushFunctionPara(void *c_this, void *FunctionPara, VS_BOOL AutoRelease )
{
    return g_star_CoreFunctionTbl->SRPBasic_LuaPushFunctionPara(c_this,FunctionPara,AutoRelease);
}

void *Star_SRPBasic_LuaToFunctionPara(void *c_this, VS_INT32 Index )
{
    return g_star_CoreFunctionTbl->SRPBasic_LuaToFunctionPara(c_this,Index);
}

VS_BOOL Star_SRPBasic_LuaIsFunctionPara(void *c_this, VS_INT32 Index )
{
    return g_star_CoreFunctionTbl->SRPBasic_LuaIsFunctionPara(c_this,Index);
}

VS_BOOL Star_SRPBasic_LuaPushCommInterface(void *c_this, void *CommInterface, VS_BOOL AutoRelease )
{
    return g_star_CoreFunctionTbl->SRPBasic_LuaPushCommInterface(c_this,CommInterface,AutoRelease);
}

void *Star_SRPBasic_LuaToCommInterface(void *c_this, VS_INT32 Index )
{
    return g_star_CoreFunctionTbl->SRPBasic_LuaToCommInterface(c_this,Index);
}

VS_BOOL Star_SRPBasic_LuaIsCommInterface(void *c_this, VS_INT32 Index )
{
    return g_star_CoreFunctionTbl->SRPBasic_LuaIsCommInterface(c_this,Index);
}

void Star_SRPBasic_ClearLuaGlobal(void *c_this)
{
    g_star_CoreFunctionTbl->SRPBasic_ClearLuaGlobal(c_this);
}

VS_BOOL Star_SRPBasic_PreCompile(void *c_this,const VS_CHAR *ScriptInterface,const VS_INT8 *ScriptBuf,VS_INT32 ScriptBufSize, const VS_CHAR *Name, VS_CHAR **ErrorInfo)
{
    return g_star_CoreFunctionTbl->SRPBasic_PreCompile(c_this,ScriptInterface,ScriptBuf,ScriptBufSize,Name,ErrorInfo);
}

void Star_SRPBasic_GCCollect(void *c_this)
{
    g_star_CoreFunctionTbl->SRPBasic_GCCollect(c_this);
}

void Star_SRPBasic_PostDoBuffer(void *c_this, const VS_CHAR *ScriptInterface,const VS_INT8 *ScriptBuf,VS_INT32 ScriptBufSize,VS_BOOL IsUTF8,const VS_CHAR *ModuleName )
{
    g_star_CoreFunctionTbl->SRPBasic_PostDoBuffer(c_this,ScriptInterface,ScriptBuf,ScriptBufSize,IsUTF8,ModuleName);
}

void Star_SRPBasic_PostDoBufferEx(void *c_this, const VS_CHAR *ScriptInterface,const VS_INT8 *ScriptBuf,VS_INT32 ScriptBufSize,VS_LuaInfoDispProc DispProc,VS_UWORD Para,VS_BOOL IsUTF8,const VS_CHAR *ModuleName )
{
    g_star_CoreFunctionTbl->SRPBasic_PostDoBufferEx(c_this,ScriptInterface,ScriptBuf,ScriptBufSize,DispProc,Para,IsUTF8,ModuleName);
}

VS_BOOL Star_SRPBasic_DoFile(void *c_this, const VS_CHAR *ScriptInterface,const VS_CHAR *FileName, VS_CHAR **ErrorInfo, const VS_CHAR *WorkDirectory, VS_BOOL IsUTF8 )
{
    return g_star_CoreFunctionTbl->SRPBasic_DoFile(c_this,ScriptInterface,FileName,ErrorInfo,WorkDirectory,IsUTF8);
}

VS_BOOL Star_SRPBasic_PostDoFile(void *c_this, const VS_CHAR *ScriptInterface,const VS_CHAR *FileName, VS_CHAR **ErrorInfo, const VS_CHAR *WorkDirectory, VS_BOOL IsUTF8 )
{
    return g_star_CoreFunctionTbl->SRPBasic_PostDoFile(c_this,ScriptInterface,FileName,ErrorInfo,WorkDirectory,IsUTF8);
}

void Star_SRPBasic_LuaRegHook(void *c_this, void *FuncAddr )
{
    g_star_CoreFunctionTbl->SRPBasic_LuaRegHook(c_this,FuncAddr);
}

void Star_SRPBasic_LuaUnRegHook(void *c_this, void *FuncAddr )
{
    g_star_CoreFunctionTbl->SRPBasic_LuaUnRegHook(c_this,FuncAddr);
}

VS_BOOL Star_SRPBasic_RegGCProc(void *c_this, VS_GCProc GCProc, VS_UWORD Para )
{
    return g_star_CoreFunctionTbl->SRPBasic_RegGCProc(c_this,GCProc,Para);
}

void Star_SRPBasic_UnRegGCProc(void *c_this, VS_GCProc GCProc, VS_UWORD Para )
{
    g_star_CoreFunctionTbl->SRPBasic_UnRegGCProc(c_this,GCProc,Para);
}

VS_ULONG Star_SRPBasic_GetServiceGroupID(void *c_this )
{
    return g_star_CoreFunctionTbl->SRPBasic_GetServiceGroupID(c_this);
}

VS_CHAR *Star_SRPBasic_QueryFirstService(void *c_this, VS_UUID *RetUuid )
{
    return g_star_CoreFunctionTbl->SRPBasic_QueryFirstService(c_this,RetUuid);
}

VS_CHAR *Star_SRPBasic_QueryNextService(void *c_this, VS_UUID *RetUuid )
{
    return g_star_CoreFunctionTbl->SRPBasic_QueryNextService(c_this,RetUuid);
}

VS_CHAR *Star_SRPBasic_QueryActiveService(void *c_this, VS_UUID *RetUuid )
{
    return g_star_CoreFunctionTbl->SRPBasic_QueryActiveService(c_this,RetUuid);
}

VS_CHAR *Star_SRPBasic_GetServiceName(void *c_this,VS_UUID *ServiceID)
{
    return g_star_CoreFunctionTbl->SRPBasic_GetServiceName(c_this,ServiceID);
}

VS_BOOL Star_SRPBasic_GetServiceID(void *c_this,const VS_CHAR *ServiceName,VS_UUID *ServiceID)
{
    return g_star_CoreFunctionTbl->SRPBasic_GetServiceID(c_this,ServiceName,ServiceID);
}

VS_BOOL Star_SRPBasic_IsValidUser(void *c_this,const VS_CHAR *UserName,const VS_CHAR *UserPass)
{
    return g_star_CoreFunctionTbl->SRPBasic_IsValidUser(c_this,UserName,UserPass);
}

VS_BOOL Star_SRPBasic_ImportServiceEx(void *c_this, VS_UUID *ServiceID, VS_BOOL LoadRunModule )
{
    return g_star_CoreFunctionTbl->SRPBasic_ImportServiceEx(c_this,ServiceID,LoadRunModule);
}

VS_BOOL Star_SRPBasic_ImportServiceWithPath(void *c_this, const VS_CHAR *ServicePath,const VS_CHAR *ServiceName, VS_BOOL LoadRunModule )
{
    return g_star_CoreFunctionTbl->SRPBasic_ImportServiceWithPath(c_this,ServicePath,ServiceName,LoadRunModule);
}

VS_BOOL Star_SRPBasic_ImportService(void *c_this, const VS_CHAR *ServiceName, VS_BOOL LoadRunModule )
{
    return g_star_CoreFunctionTbl->SRPBasic_ImportService(c_this,ServiceName,LoadRunModule);
}

VS_CHAR *Star_SRPBasic_ImportDynaService(void *c_this, const VS_CHAR *Url )
{
    return g_star_CoreFunctionTbl->SRPBasic_ImportDynaService(c_this,Url);
}

VS_BOOL Star_SRPBasic_CreateService(void *c_this, const VS_CHAR *ServicePath,const VS_CHAR *ServiceName,VS_UUID *ServiceID,const VS_CHAR *RootPass,VS_INT32 FrameInterval,VS_INT32 NetPkgSize,VS_INT32 UploadPkgSize,VS_INT32 DownloadPkgSize,VS_INT32 DataUpPkgSize,VS_INT32 DataDownPkgSize)
{
    return g_star_CoreFunctionTbl->SRPBasic_CreateService(c_this,ServicePath,ServiceName,ServiceID,RootPass,FrameInterval,NetPkgSize,UploadPkgSize,DownloadPkgSize,DataUpPkgSize,DataDownPkgSize);
}

VS_BOOL Star_SRPBasic_CreateServiceEx(void *c_this, const VS_CHAR *ServicePath,const VS_CHAR *ServiceName,VS_UUID *ServiceID,const VS_CHAR *RootPass,VS_INT32 FrameInterval,VS_INT32 NetPkgSize,VS_INT32 UploadPkgSize,VS_INT32 DownloadPkgSize,VS_INT32 DataUpPkgSize,VS_INT32 DataDownPkgSize)
{
    return g_star_CoreFunctionTbl->SRPBasic_CreateServiceEx(c_this,ServicePath,ServiceName,ServiceID,RootPass,FrameInterval,NetPkgSize,UploadPkgSize,DownloadPkgSize,DataUpPkgSize,DataDownPkgSize);
}

VS_BOOL Star_SRPBasic_LoadServiceEx(void *c_this, VS_UUID *ServiceID,const VS_CHAR *UserName, const VS_CHAR *UserPass, VS_BOOL LoadRunModule )
{
    return g_star_CoreFunctionTbl->SRPBasic_LoadServiceEx(c_this,ServiceID,UserName,UserPass,LoadRunModule);
}

VS_BOOL Star_SRPBasic_LoadServiceWithPath(void *c_this, const VS_CHAR *ServicePath,const VS_CHAR *ServiceName,const VS_CHAR *UserName, const VS_CHAR *UserPass, VS_BOOL LoadRunModule )
{
    return g_star_CoreFunctionTbl->SRPBasic_LoadServiceWithPath(c_this,ServicePath,ServiceName,UserName,UserPass,LoadRunModule);
}

VS_BOOL Star_SRPBasic_LoadService(void *c_this, const VS_CHAR *ServiceName,const VS_CHAR *UserName, const VS_CHAR *UserPass, VS_BOOL LoadRunModule )
{
    return g_star_CoreFunctionTbl->SRPBasic_LoadService(c_this,ServiceName,UserName,UserPass,LoadRunModule);
}

VS_BOOL Star_SRPBasic_ExportServiceHeader(void *c_this, const VS_CHAR *ServiceName,const VS_CHAR *Path )
{
    return g_star_CoreFunctionTbl->SRPBasic_ExportServiceHeader(c_this,ServiceName,Path);
}

VS_BOOL Star_SRPBasic_ExportServiceDefine(void *c_this, const VS_CHAR *ServiceName,const VS_CHAR *FileName )
{
    return g_star_CoreFunctionTbl->SRPBasic_ExportServiceDefine(c_this,ServiceName,FileName);
}

void Star_SRPBasic_ClearService(void *c_this)
{
    g_star_CoreFunctionTbl->SRPBasic_ClearService(c_this);
}

void Star_SRPBasic_ClearServiceEx(void *c_this)
{
    g_star_CoreFunctionTbl->SRPBasic_ClearServiceEx(c_this);
}

VS_BOOL Star_SRPBasic_RegisterServer(void *c_this, const VS_CHAR *ServiceName )
{
    return g_star_CoreFunctionTbl->SRPBasic_RegisterServer(c_this,ServiceName);
}

void Star_SRPBasic_AllocCooperator(void *c_this, const VS_CHAR *ServiceName )
{
    g_star_CoreFunctionTbl->SRPBasic_AllocCooperator(c_this,ServiceName);
}

void Star_SRPBasic_FreeCooperator(void *c_this, const VS_CHAR *ServiceName )
{
    g_star_CoreFunctionTbl->SRPBasic_FreeCooperator(c_this,ServiceName);
}

void Star_SRPBasic_GetServerUrlInfo(void *c_this, struct StructOfVSServerUrlInfo *ServerUrlInfo)
{
    g_star_CoreFunctionTbl->SRPBasic_GetServerUrlInfo(c_this,ServerUrlInfo);
}

void Star_SRPBasic_WebServiceRefresh(void *c_this)
{
    g_star_CoreFunctionTbl->SRPBasic_WebServiceRefresh(c_this);
}

VS_BOOL Star_SRPBasic_GetWSDL(void *c_this,VS_ULONG WSDLVersion,const VS_CHAR *WebServiceHost,void *BinBuf)
{
    return g_star_CoreFunctionTbl->SRPBasic_GetWSDL(c_this,WSDLVersion,WebServiceHost,BinBuf);
}

void *Star_SRPBasic_XmlToService(void *c_this,void *SXMLInterface,const VS_CHAR *DataPath,const VS_CHAR *SegmentName,SRPParse_PrintProc PrintProc,VS_UWORD Para)
{
    return g_star_CoreFunctionTbl->SRPBasic_XmlToService(c_this,SXMLInterface,DataPath,SegmentName,PrintProc,Para);
}

void *Star_SRPBasic_GetSRPInterfaceEx(void *c_this, VS_UUID *ServiceID, const VS_CHAR *UserName, const VS_CHAR *UserPass )
{
    return g_star_CoreFunctionTbl->SRPBasic_GetSRPInterfaceEx(c_this,ServiceID,UserName,UserPass);
}

void *Star_SRPBasic_GetSRPInterface(void *c_this, const VS_CHAR *ServiceName, const VS_CHAR *UserName, const VS_CHAR *UserPass )
{
    return g_star_CoreFunctionTbl->SRPBasic_GetSRPInterface(c_this,ServiceName,UserName,UserPass);
}

void *Star_SRPBasic_GetSRPInterface2(void *c_this, const VS_CHAR *ServiceName, VS_GetUserInfoCallBackProc CallBackProc )
{
    return g_star_CoreFunctionTbl->SRPBasic_GetSRPInterface2(c_this,ServiceName,CallBackProc);
}

void *Star_SRPBasic_GetSRPInterfaceEx2(void *c_this, VS_UUID *ServiceID, VS_GetUserInfoCallBackProc CallBackProc )
{
    return g_star_CoreFunctionTbl->SRPBasic_GetSRPInterfaceEx2(c_this,ServiceID,CallBackProc);
}

VS_BOOL Star_SRPBasic_ChangeDepend(void *c_this, VS_UUID *OldDependServiceID,VS_UUID *NewDependServiceID,const VS_CHAR *NewServiceName )
{
    return g_star_CoreFunctionTbl->SRPBasic_ChangeDepend(c_this,OldDependServiceID,NewDependServiceID,NewServiceName);
}

VS_BOOL Star_SRPBasic_AddDepend(void *c_this, VS_UUID *DependServiceID,const VS_CHAR *NewServiceName )
{
    return g_star_CoreFunctionTbl->SRPBasic_AddDepend(c_this,DependServiceID,NewServiceName);
}

VS_EVENTPARAM_RUNPARAM *Star_SRPBasic_GetRequestBuf(void *c_this)
{
    return g_star_CoreFunctionTbl->SRPBasic_GetRequestBuf(c_this);
}

void Star_SRPBasic_FreeResponseBuf(void *c_this,VS_EVENTPARAM_RUNPARAM *ResponseParam)
{
    g_star_CoreFunctionTbl->SRPBasic_FreeResponseBuf(c_this,ResponseParam);
}

void Star_SRPBasic_FreeRequestBuf(void *c_this,VS_EVENTPARAM_RUNPARAM *RequestParam)
{
    g_star_CoreFunctionTbl->SRPBasic_FreeRequestBuf(c_this,RequestParam);
}

VS_EVENTPARAM_RUNPARAM *Star_SRPBasic_ProcessSysObjectEvent(void *c_this,VS_UUID *EventID,VS_EVENTPARAM_RUNPARAM *RequestParam)
{
    return g_star_CoreFunctionTbl->SRPBasic_ProcessSysObjectEvent(c_this,EventID,RequestParam);
}

void *Star_SRPBasic_GetSysObject(void *c_this)
{
    return g_star_CoreFunctionTbl->SRPBasic_GetSysObject(c_this);
}

VS_CHAR *Star_SRPBasic_GetName(void *c_this,VS_UUID *ObjectID)
{
    return g_star_CoreFunctionTbl->SRPBasic_GetName(c_this,ObjectID);
}

VS_INT8 *Star_SRPBasic_GetMD5(void *c_this,VS_INT8 *Buf,VS_INT32 BufSize)
{
    return g_star_CoreFunctionTbl->SRPBasic_GetMD5(c_this,Buf,BufSize);
}

VS_UWORD Star_SRPBasic_GetTickCount(void *c_this)
{
    return g_star_CoreFunctionTbl->SRPBasic_GetTickCount(c_this);
}

void Star_SRPBasic_GetID(void *c_this,void *Object,VS_UUID *UuidPtr)
{
    g_star_CoreFunctionTbl->SRPBasic_GetID(c_this,Object,UuidPtr);
}

VS_BOOL Star_SRPBasic_RegObjectIDChangeNotify(void *c_this,VS_ObjectIDChangeNotifyProc ChangeNotifyProc,VS_UWORD Para)
{
    return g_star_CoreFunctionTbl->SRPBasic_RegObjectIDChangeNotify(c_this,ChangeNotifyProc,Para);
}

void Star_SRPBasic_UnRegObjectIDChangeNotify(void *c_this,VS_ObjectIDChangeNotifyProc ChangeNotifyProc,VS_UWORD Para)
{
    g_star_CoreFunctionTbl->SRPBasic_UnRegObjectIDChangeNotify(c_this,ChangeNotifyProc,Para);
}

VS_BOOL Star_SRPBasic_RegObjectFreeNotify(void *c_this,VS_ObjectFreeNotifyProc FreeNotifyProc,VS_UWORD Para)
{
    return g_star_CoreFunctionTbl->SRPBasic_RegObjectFreeNotify(c_this,FreeNotifyProc,Para);
}

void Star_SRPBasic_UnRegObjectFreeNotify(void *c_this,VS_ObjectFreeNotifyProc FreeNotifyProc,VS_UWORD Para)
{
    g_star_CoreFunctionTbl->SRPBasic_UnRegObjectFreeNotify(c_this,FreeNotifyProc,Para);
}

VS_CHAR *Star_SRPBasic_GetRegStr(void *c_this,const VS_CHAR *SubKey,const VS_CHAR *ValueName,const VS_CHAR *DefaultValue)
{
    return g_star_CoreFunctionTbl->SRPBasic_GetRegStr(c_this,SubKey,ValueName,DefaultValue);
}

VS_UINT32 Star_SRPBasic_GetRegInt(void *c_this,const VS_CHAR *SubKey,const VS_CHAR *ValueName,VS_UINT32 DefaultValue)
{
    return g_star_CoreFunctionTbl->SRPBasic_GetRegInt(c_this,SubKey,ValueName,DefaultValue);
}

VS_ULONG Star_SRPBasic_SetupTimer(void *c_this,VS_INT32 Ticket,VS_TimerProc FunctionAddr,VS_UWORD Para1,VS_UWORD Para2,VS_UWORD Para3,VS_UWORD Para4 )
{
    return g_star_CoreFunctionTbl->SRPBasic_SetupTimer(c_this,Ticket,FunctionAddr,Para1,Para2,Para3,Para4);
}

void Star_SRPBasic_KillTimer(void *c_this,VS_ULONG TimerID)
{
    g_star_CoreFunctionTbl->SRPBasic_KillTimer(c_this,TimerID);
}

VS_ULONG Star_SRPBasic_SetupSocketServer(void *c_this, const VS_CHAR *Interface, VS_UINT16 PortNumber, VS_ULONG *LinkInterfaceStatus,VS_SockAcceptCallBackProc CallBackProc,VS_UWORD Para)
{
    return g_star_CoreFunctionTbl->SRPBasic_SetupSocketServer(c_this,Interface,PortNumber,LinkInterfaceStatus,CallBackProc,Para);
}

VS_ULONG Star_SRPBasic_SetupSocketClient(void *c_this, const VS_CHAR *ServerInterface, const VS_CHAR *ServerName, VS_UINT16 PortNumber, VS_SockEventCallBackProc CallBackProc,VS_UWORD Para )
{
    return g_star_CoreFunctionTbl->SRPBasic_SetupSocketClient(c_this,ServerInterface,ServerName,PortNumber,CallBackProc,Para);
}

void Star_SRPBasic_CloseSocketConnect(void *c_this, VS_ULONG ConnectionID )
{
    g_star_CoreFunctionTbl->SRPBasic_CloseSocketConnect(c_this,ConnectionID);
}

VS_BOOL Star_SRPBasic_SocketSend(void *c_this, VS_ULONG MachineID, void *ParaPkg, VS_BOOL Assure )
{
    return g_star_CoreFunctionTbl->SRPBasic_SocketSend(c_this,MachineID,ParaPkg,Assure);
}

VS_BOOL Star_SRPBasic_SocketSendBin(void *c_this, VS_ULONG MachineID, VS_INT32 BinDataSize, VS_INT8 *BinDataBuf, VS_BOOL Assure )
{
    return g_star_CoreFunctionTbl->SRPBasic_SocketSendBin(c_this,MachineID,BinDataSize,BinDataBuf,Assure);
}

VS_ULONG Star_SRPBasic_SetupSocketTimer(void *c_this, VS_ULONG MachineID, VS_INT32 Ticket,VS_INT32 Counter )
{
    return g_star_CoreFunctionTbl->SRPBasic_SetupSocketTimer(c_this,MachineID,Ticket,Counter);
}

void Star_SRPBasic_KillSocketTimer(void *c_this, VS_ULONG MachineID, VS_ULONG TimerIndex )
{
    g_star_CoreFunctionTbl->SRPBasic_KillSocketTimer(c_this,MachineID,TimerIndex);
}

VS_BOOL Star_SRPBasic_SetDataServerAddr(void *c_this,VS_BOOL DirectConnect,const VS_CHAR *DataServerInterface,const VS_CHAR *DataServerName,VS_UINT16 DataServerPort,const VS_CHAR *LocalDataServerInterface,VS_UINT16 LocalDataServerPort)
{
    return g_star_CoreFunctionTbl->SRPBasic_SetDataServerAddr(c_this,DirectConnect,DataServerInterface,DataServerName,DataServerPort,LocalDataServerInterface,LocalDataServerPort);
}

void Star_SRPBasic_RegQueryStaticDataProc(void *c_this, VS_QueryObjectStaticDataProc Proc,VS_UWORD Para)
{
    g_star_CoreFunctionTbl->SRPBasic_RegQueryStaticDataProc(c_this,Proc,Para);
}

void Star_SRPBasic_UnRegQueryStaticDataProc(void *c_this, VS_QueryObjectStaticDataProc Proc,VS_UWORD Para)
{
    g_star_CoreFunctionTbl->SRPBasic_UnRegQueryStaticDataProc(c_this,Proc,Para);
}

void Star_SRPBasic_RegSaveStaticDataProc(void *c_this, VS_SaveObjectStaticDataProc Proc,VS_UWORD Para)
{
    g_star_CoreFunctionTbl->SRPBasic_RegSaveStaticDataProc(c_this,Proc,Para);
}

void Star_SRPBasic_UnRegSaveStaticDataProc(void *c_this, VS_SaveObjectStaticDataProc Proc,VS_UWORD Para)
{
    g_star_CoreFunctionTbl->SRPBasic_UnRegSaveStaticDataProc(c_this,Proc,Para);
}

void Star_SRPBasic_RegClearStaticDataProc(void *c_this, VS_ClearObjectStaticDataProc Proc,VS_UWORD Para)
{
    g_star_CoreFunctionTbl->SRPBasic_RegClearStaticDataProc(c_this,Proc,Para);
}

void Star_SRPBasic_UnRegClearStaticDataProc(void *c_this, VS_ClearObjectStaticDataProc Proc,VS_UWORD Para)
{
    g_star_CoreFunctionTbl->SRPBasic_UnRegClearStaticDataProc(c_this,Proc,Para);
}

void Star_SRPBasic_SetServerPara(void *c_this,VS_INT32 MaxClientNumber,VS_INT32 MaxDataServerConnectionNumber,VS_INT32 DataServerOverTime)
{
    g_star_CoreFunctionTbl->SRPBasic_SetServerPara(c_this,MaxClientNumber,MaxDataServerConnectionNumber,DataServerOverTime);
}

void Star_SRPBasic_QuyeryStatisticInfo(void *c_this,void *Machine,VS_STATISTICINFO *InfoBuf)
{
    g_star_CoreFunctionTbl->SRPBasic_QuyeryStatisticInfo(c_this,Machine,InfoBuf);
}

VS_BOOL Star_SRPBasic_RegFileCallBack(void *c_this, VS_UUID *ServiceID,VS_FileUpDownLoadCallBackProc FileCallBackProc, VS_UWORD Para )
{
    return g_star_CoreFunctionTbl->SRPBasic_RegFileCallBack(c_this,ServiceID,FileCallBackProc,Para);
}

void Star_SRPBasic_UnRegFileCallBack(void *c_this, VS_UUID *ServiceID,VS_FileUpDownLoadCallBackProc FileCallBackProc, VS_UWORD Para )
{
    g_star_CoreFunctionTbl->SRPBasic_UnRegFileCallBack(c_this,ServiceID,FileCallBackProc,Para);
}

VS_BOOL Star_SRPBasic_RegFileReqCallBack(void *c_this, VS_FileUpDownLoadRequestCallBackProc FileCallBackProc, VS_UWORD Para )
{
    return g_star_CoreFunctionTbl->SRPBasic_RegFileReqCallBack(c_this,FileCallBackProc,Para);
}

void Star_SRPBasic_UnRegFileReqCallBack(void *c_this, VS_FileUpDownLoadRequestCallBackProc FileCallBackProc, VS_UWORD Para )
{
    g_star_CoreFunctionTbl->SRPBasic_UnRegFileReqCallBack(c_this,FileCallBackProc,Para);
}

void Star_SRPBasic_GetFileInfo(void *c_this, VS_UPDOWNFILEINFO *InfoPtr )
{
    g_star_CoreFunctionTbl->SRPBasic_GetFileInfo(c_this,InfoPtr);
}

VS_BOOL Star_SRPBasic_StringToUuid(void *c_this,const VS_INT8 *String,VS_UUID *Uuid)
{
    return g_star_CoreFunctionTbl->SRPBasic_StringToUuid(c_this,String,Uuid);
}

VS_INT8 *Star_SRPBasic_UuidToString(void *c_this,VS_UUID *Uuid)
{
    return g_star_CoreFunctionTbl->SRPBasic_UuidToString(c_this,Uuid);
}

VS_UINT16 Star_SRPBasic_GetProgramType(void *c_this)
{
    return g_star_CoreFunctionTbl->SRPBasic_GetProgramType(c_this);
}

VS_BOOL Star_SRPBasic_IsDefaultServer(void *c_this)
{
    return g_star_CoreFunctionTbl->SRPBasic_IsDefaultServer(c_this);
}

VS_BOOL Star_SRPBasic_IsWindowVisible(void *c_this)
{
    return g_star_CoreFunctionTbl->SRPBasic_IsWindowVisible(c_this);
}

void Star_SRPBasic_HideWindow(void *c_this)
{
    g_star_CoreFunctionTbl->SRPBasic_HideWindow(c_this);
}

void Star_SRPBasic_ShowWindow(void *c_this)
{
    g_star_CoreFunctionTbl->SRPBasic_ShowWindow(c_this);
}

void Star_SRPBasic_SetWindowCaption(void *c_this,const VS_CHAR *Caption)
{
    g_star_CoreFunctionTbl->SRPBasic_SetWindowCaption(c_this,Caption);
}

void Star_SRPBasic_ExitVSSystem(void *c_this,const VS_CHAR *ErrorInfo)
{
    g_star_CoreFunctionTbl->SRPBasic_ExitVSSystem(c_this,ErrorInfo);
}

VS_BOOL Star_SRPBasic_IsAppActive(void *c_this)
{
    return g_star_CoreFunctionTbl->SRPBasic_IsAppActive(c_this);
}

void Star_SRPBasic_SetIdleActive(void *c_this,VS_BOOL CreateFlag)
{
    g_star_CoreFunctionTbl->SRPBasic_SetIdleActive(c_this,CreateFlag);
}

void Star_SRPBasic_GetVersion(void *c_this,VS_UINT8 *MainVersion,VS_UINT8 *SubVersion,VS_UINT16 *BuildVersion)
{
    g_star_CoreFunctionTbl->SRPBasic_GetVersion(c_this,MainVersion,SubVersion,BuildVersion);
}

void Star_SRPBasic_GetVersionInfo(void *c_this,VS_CHAR *InfoBuf,VS_INT32 InfoBufSize)
{
    g_star_CoreFunctionTbl->SRPBasic_GetVersionInfo(c_this,InfoBuf,InfoBufSize);
}

VS_HWND Star_SRPBasic_GetWindowHandle(void *c_this)
{
    return g_star_CoreFunctionTbl->SRPBasic_GetWindowHandle(c_this);
}

void Star_SRPBasic_GetWindowSize(void *c_this, VS_INT32 *Width, VS_INT32 *Height )
{
    g_star_CoreFunctionTbl->SRPBasic_GetWindowSize(c_this,Width,Height);
}

void Star_SRPBasic_SetColor(void *c_this, VS_COLOR Text,VS_COLOR Explane,VS_COLOR ObjName,VS_COLOR AttrType,VS_COLOR Number,VS_COLOR Error )
{
    g_star_CoreFunctionTbl->SRPBasic_SetColor(c_this,Text,Explane,ObjName,AttrType,Number,Error);
}

void Star_SRPBasic_SetBkColor(void *c_this, VS_COLOR BkColor )
{
    g_star_CoreFunctionTbl->SRPBasic_SetBkColor(c_this,BkColor);
}

void Star_SRPBasic_ShowStatusMenu(void *c_this, VS_BOOL MenuShowFlag, VS_BOOL StatusShowFlag )
{
    g_star_CoreFunctionTbl->SRPBasic_ShowStatusMenu(c_this,MenuShowFlag,StatusShowFlag);
}

VS_HWND Star_SRPBasic_GetClientWndHandle(void *c_this)
{
    return g_star_CoreFunctionTbl->SRPBasic_GetClientWndHandle(c_this);
}

void Star_SRPBasic_GetClientWndSize(void *c_this, VS_INT32 *Width, VS_INT32 *Height )
{
    g_star_CoreFunctionTbl->SRPBasic_GetClientWndSize(c_this,Width,Height);
}

void Star_SRPBasic_SetClientWndSize(void *c_this, VS_INT32 Width, VS_INT32 Height )
{
    g_star_CoreFunctionTbl->SRPBasic_SetClientWndSize(c_this,Width,Height);
}

void Star_SRPBasic_SetClientWndFocus(void *c_this, VS_HWND hWnd, VS_BOOL NeedAction )
{
    g_star_CoreFunctionTbl->SRPBasic_SetClientWndFocus(c_this,hWnd,NeedAction);
}

void Star_SRPBasic_KillClientWndFocus(void *c_this, VS_HWND hWnd, VS_BOOL NeedAction )
{
    g_star_CoreFunctionTbl->SRPBasic_KillClientWndFocus(c_this,hWnd,NeedAction);
}

void Star_SRPBasic_ClearClientWnd(void *c_this)
{
    g_star_CoreFunctionTbl->SRPBasic_ClearClientWnd(c_this);
}

void Star_SRPBasic_HideClientWnd(void *c_this)
{
    g_star_CoreFunctionTbl->SRPBasic_HideClientWnd(c_this);
}

void Star_SRPBasic_ShowClientWnd(void *c_this)
{
    g_star_CoreFunctionTbl->SRPBasic_ShowClientWnd(c_this);
}

void Star_SRPBasic_SetClientBkColor(void *c_this, VS_COLOR BkColor )
{
    g_star_CoreFunctionTbl->SRPBasic_SetClientBkColor(c_this,BkColor);
}

VS_BOOL Star_SRPBasic_GetKeyState(void *c_this,VS_INT32 Key)
{
    return g_star_CoreFunctionTbl->SRPBasic_GetKeyState(c_this,Key);
}

void Star_SRPBasic_SetWindowStyle(void *c_this, VSWINDOWSTYLE *Style  )
{
    g_star_CoreFunctionTbl->SRPBasic_SetWindowStyle(c_this,Style);
}

void Star_SRPBasic_MoveWindow(void *c_this,VSWINDOWPOSITION *Position,VS_BOOL RepaintFlag)
{
    g_star_CoreFunctionTbl->SRPBasic_MoveWindow(c_this,Position,RepaintFlag);
}

void Star_SRPBasic_GetWindowPos(void *c_this,VSWINDOWPOSITION *Position)
{
    g_star_CoreFunctionTbl->SRPBasic_GetWindowPos(c_this,Position);
}

void Star_SRPBasic_SetWindowStatus(void *c_this,VS_INT32 Status)
{
    g_star_CoreFunctionTbl->SRPBasic_SetWindowStatus(c_this,Status);
}

void Star_SRPBasic_RegRunEnv_FromParentCallBack(void *c_this, VS_RunEnvCallBackProc CallBack,VS_UWORD Para)
{
    g_star_CoreFunctionTbl->SRPBasic_RegRunEnv_FromParentCallBack(c_this,CallBack,Para);
}

void Star_SRPBasic_UnRegRunEnv_FromParentCallBack(void *c_this, VS_RunEnvCallBackProc CallBack,VS_UWORD Para)
{
    g_star_CoreFunctionTbl->SRPBasic_UnRegRunEnv_FromParentCallBack(c_this,CallBack,Para);
}

VS_BOOL Star_SRPBasic_RunEnvToChild(void *c_this,VS_UUID *ObjectID,struct StructOfVSRunEnv *RunEnvInfo)
{
    return g_star_CoreFunctionTbl->SRPBasic_RunEnvToChild(c_this,ObjectID,RunEnvInfo);
}

VS_BOOL Star_SRPBasic_RunEnvToParent(void *c_this,struct StructOfVSRunEnv *RunEnvInfo)
{
    return g_star_CoreFunctionTbl->SRPBasic_RunEnvToParent(c_this,RunEnvInfo);
}

void Star_SRPBasic_SetMessageHook(void *c_this,VS_SRPMessageProcessHookProc HookProc)
{
    g_star_CoreFunctionTbl->SRPBasic_SetMessageHook(c_this,HookProc);
}

void *Star_SRPBasic_GetMessageHook(void *c_this)
{
    return g_star_CoreFunctionTbl->SRPBasic_GetMessageHook(c_this);
}

VS_BOOL Star_SRPBasic_IsInSync(void *c_this)
{
    return g_star_CoreFunctionTbl->SRPBasic_IsInSync(c_this);
}

VS_BOOL Star_SRPBasic_IsServiceSync(void *c_this)
{
    return g_star_CoreFunctionTbl->SRPBasic_IsServiceSync(c_this);
}

VS_BOOL Star_SRPBasic_WaitServiceSync(void *c_this,VS_INT32 WaitTimeMs)
{
    return g_star_CoreFunctionTbl->SRPBasic_WaitServiceSync(c_this,WaitTimeMs);
}

VS_BOOL Star_SRPBasic_SRPIdle(void *c_this)
{
    return g_star_CoreFunctionTbl->SRPBasic_SRPIdle(c_this);
}

void Star_SRPBasic_SRPAppActive(void *c_this)
{
    g_star_CoreFunctionTbl->SRPBasic_SRPAppActive(c_this);
}

void Star_SRPBasic_SRPAppDeactive(void *c_this)
{
    g_star_CoreFunctionTbl->SRPBasic_SRPAppDeactive(c_this);
}

void Star_SRPBasic_HyperLink(void *c_this,const VS_CHAR *HyperLink,VS_BOOL CreateNewWindow)
{
    g_star_CoreFunctionTbl->SRPBasic_HyperLink(c_this,HyperLink,CreateNewWindow);
}

void Star_SRPBasic_AppEvent(void *c_this,VS_ULONG EventID,const VS_CHAR *EventInfo)
{
    g_star_CoreFunctionTbl->SRPBasic_AppEvent(c_this,EventID,EventInfo);
}

void Star_SRPBasic_SetExceptHandler(void *c_this,VS_ExceptHandlerProc ExceptHandlerProc)
{
    g_star_CoreFunctionTbl->SRPBasic_SetExceptHandler(c_this,ExceptHandlerProc);
}

void *Star_SRPBasic_CreateIndex_Nor(void *c_this,VS_INT32 KeyNumber,VS_UINT16 HashTableBits)
{
    return g_star_CoreFunctionTbl->SRPBasic_CreateIndex_Nor(c_this,KeyNumber,HashTableBits);
}

void *Star_SRPBasic_CreateIndexCmp_Nor(void *c_this,VS_INT32 KeyNumber,VS_UINT16 HashTableBits,VS_IndexCompareProc CompareProc)
{
    return g_star_CoreFunctionTbl->SRPBasic_CreateIndexCmp_Nor(c_this,KeyNumber,HashTableBits,CompareProc);
}

void *Star_SRPBasic_CreateIDIndex_Nor(void *c_this,VS_UINT16 HashTableBits)
{
    return g_star_CoreFunctionTbl->SRPBasic_CreateIDIndex_Nor(c_this,HashTableBits);
}

void *Star_SRPBasic_CreateIDIndexEx_Nor(void *c_this,VS_UINT16 HashTableBits)
{
    return g_star_CoreFunctionTbl->SRPBasic_CreateIDIndexEx_Nor(c_this,HashTableBits);
}

void *Star_SRPBasic_CreateIndex_Dbg(void *c_this,VS_INT32 KeyNumber,VS_UINT16 HashTableBits,const VS_CHAR *FileName,VS_INT32 LineNumber)
{
    return g_star_CoreFunctionTbl->SRPBasic_CreateIndex_Dbg(c_this,KeyNumber,HashTableBits,FileName,LineNumber);
}

void *Star_SRPBasic_CreateIndexCmp_Dbg(void *c_this,VS_INT32 KeyNumber,VS_UINT16 HashTableBits,VS_IndexCompareProc CompareProc,const VS_CHAR *FileName,VS_INT32 LineNumber)
{
    return g_star_CoreFunctionTbl->SRPBasic_CreateIndexCmp_Dbg(c_this,KeyNumber,HashTableBits,CompareProc,FileName,LineNumber);
}

void *Star_SRPBasic_CreateIDIndex_Dbg(void *c_this,VS_UINT16 HashTableBits,const VS_CHAR *FileName,VS_INT32 LineNumber)
{
    return g_star_CoreFunctionTbl->SRPBasic_CreateIDIndex_Dbg(c_this,HashTableBits,FileName,LineNumber);
}

void *Star_SRPBasic_CreateIDIndexEx_Dbg(void *c_this,VS_UINT16 HashTableBits,const VS_CHAR *FileName,VS_INT32 LineNumber)
{
    return g_star_CoreFunctionTbl->SRPBasic_CreateIDIndexEx_Dbg(c_this,HashTableBits,FileName,LineNumber);
}

void Star_SRPBasic_InsertOneKey(void *c_this,void *IndexContext,VS_UWORD MainKey,VS_INT8 *Buf)
{
    g_star_CoreFunctionTbl->SRPBasic_InsertOneKey(c_this,IndexContext,MainKey,Buf);
}

VS_INT8 *Star_SRPBasic_FindOneKey(void *c_this,void *IndexContext,VS_UWORD MainKey)
{
    return g_star_CoreFunctionTbl->SRPBasic_FindOneKey(c_this,IndexContext,MainKey);
}

VS_INT8 *Star_SRPBasic_DelOneKey(void *c_this,void *IndexContext,VS_UWORD MainKey)
{
    return g_star_CoreFunctionTbl->SRPBasic_DelOneKey(c_this,IndexContext,MainKey);
}

VS_INT8 *Star_SRPBasic_QueryFirstOneKey(void *c_this,void *IndexContext,VS_QUERYRECORD *QueryRecord,VS_UWORD *MainKey)
{
    return g_star_CoreFunctionTbl->SRPBasic_QueryFirstOneKey(c_this,IndexContext,QueryRecord,MainKey);
}

VS_INT8 *Star_SRPBasic_QueryNextOneKey(void *c_this,void *IndexContext,VS_QUERYRECORD *QueryRecord,VS_UWORD *MainKey)
{
    return g_star_CoreFunctionTbl->SRPBasic_QueryNextOneKey(c_this,IndexContext,QueryRecord,MainKey);
}

VS_INT8 *Star_SRPBasic_QueryFirstOneKeyA(void *c_this,void *IndexContext,VS_QUERYRECORD *QueryRecord,VS_UWORD *MainKey)
{
    return g_star_CoreFunctionTbl->SRPBasic_QueryFirstOneKeyA(c_this,IndexContext,QueryRecord,MainKey);
}

VS_INT8 *Star_SRPBasic_QueryNextOneKeyA(void *c_this,void *IndexContext,VS_QUERYRECORD *QueryRecord,VS_UWORD *MainKey)
{
    return g_star_CoreFunctionTbl->SRPBasic_QueryNextOneKeyA(c_this,IndexContext,QueryRecord,MainKey);
}

void Star_SRPBasic_InsertTwoKey(void *c_this,void *IndexContext,VS_UWORD MainKey,VS_UWORD SecondKey,VS_INT8 *Buf)
{
    g_star_CoreFunctionTbl->SRPBasic_InsertTwoKey(c_this,IndexContext,MainKey,SecondKey,Buf);
}

VS_INT8 *Star_SRPBasic_FindTwoKey(void *c_this,void *IndexContext,VS_UWORD MainKey,VS_UWORD SecondKey)
{
    return g_star_CoreFunctionTbl->SRPBasic_FindTwoKey(c_this,IndexContext,MainKey,SecondKey);
}

VS_INT8 *Star_SRPBasic_DelTwoKey(void *c_this,void *IndexContext,VS_UWORD MainKey,VS_UWORD SecondKey)
{
    return g_star_CoreFunctionTbl->SRPBasic_DelTwoKey(c_this,IndexContext,MainKey,SecondKey);
}

VS_INT8 *Star_SRPBasic_QueryFirstTwoKey(void *c_this,void *IndexContext,VS_QUERYRECORD *QueryRecord,VS_UWORD *MainKey,VS_UWORD *SecondKey)
{
    return g_star_CoreFunctionTbl->SRPBasic_QueryFirstTwoKey(c_this,IndexContext,QueryRecord,MainKey,SecondKey);
}

VS_INT8 *Star_SRPBasic_QueryNextTwoKey(void *c_this,void *IndexContext,VS_QUERYRECORD *QueryRecord,VS_UWORD *MainKey,VS_UWORD *SecondKey)
{
    return g_star_CoreFunctionTbl->SRPBasic_QueryNextTwoKey(c_this,IndexContext,QueryRecord,MainKey,SecondKey);
}

VS_INT8 *Star_SRPBasic_QueryFirstTwoKeyA(void *c_this,void *IndexContext,VS_QUERYRECORD *QueryRecord,VS_UWORD *MainKey,VS_UWORD *SecondKey)
{
    return g_star_CoreFunctionTbl->SRPBasic_QueryFirstTwoKeyA(c_this,IndexContext,QueryRecord,MainKey,SecondKey);
}

VS_INT8 *Star_SRPBasic_QueryNextTwoKeyA(void *c_this,void *IndexContext,VS_QUERYRECORD *QueryRecord,VS_UWORD *MainKey,VS_UWORD *SecondKey)
{
    return g_star_CoreFunctionTbl->SRPBasic_QueryNextTwoKeyA(c_this,IndexContext,QueryRecord,MainKey,SecondKey);
}

VS_INT8 *Star_SRPBasic_QueryFirstTwoKey_F(void *c_this,void *IndexContext,VS_QUERYRECORD *QueryRecord,VS_UWORD MainKey,VS_UWORD *SecondKey)
{
    return g_star_CoreFunctionTbl->SRPBasic_QueryFirstTwoKey_F(c_this,IndexContext,QueryRecord,MainKey,SecondKey);
}

VS_INT8 *Star_SRPBasic_QueryNextTwoKey_F(void *c_this,void *IndexContext,VS_QUERYRECORD *QueryRecord,VS_UWORD MainKey,VS_UWORD *SecondKey)
{
    return g_star_CoreFunctionTbl->SRPBasic_QueryNextTwoKey_F(c_this,IndexContext,QueryRecord,MainKey,SecondKey);
}

VS_INT8 *Star_SRPBasic_QueryFirstTwoKeyA_F(void *c_this,void *IndexContext,VS_QUERYRECORD *QueryRecord,VS_UWORD MainKey,VS_UWORD *SecondKey)
{
    return g_star_CoreFunctionTbl->SRPBasic_QueryFirstTwoKeyA_F(c_this,IndexContext,QueryRecord,MainKey,SecondKey);
}

VS_INT8 *Star_SRPBasic_QueryNextTwoKeyA_F(void *c_this,void *IndexContext,VS_QUERYRECORD *QueryRecord,VS_UWORD MainKey,VS_UWORD *SecondKey)
{
    return g_star_CoreFunctionTbl->SRPBasic_QueryNextTwoKeyA_F(c_this,IndexContext,QueryRecord,MainKey,SecondKey);
}

void Star_SRPBasic_InsertThreeKey(void *c_this,void *IndexContext,VS_UWORD MainKey,VS_UWORD SecondKey,VS_UWORD ThirdKey,VS_INT8 *Buf)
{
    g_star_CoreFunctionTbl->SRPBasic_InsertThreeKey(c_this,IndexContext,MainKey,SecondKey,ThirdKey,Buf);
}

VS_INT8 *Star_SRPBasic_FindThreeKey(void *c_this,void *IndexContext,VS_UWORD MainKey,VS_UWORD SecondKey,VS_UWORD ThirdKey)
{
    return g_star_CoreFunctionTbl->SRPBasic_FindThreeKey(c_this,IndexContext,MainKey,SecondKey,ThirdKey);
}

VS_INT8 *Star_SRPBasic_DelThreeKey(void *c_this,void *IndexContext,VS_UWORD MainKey,VS_UWORD SecondKey,VS_UWORD ThirdKey)
{
    return g_star_CoreFunctionTbl->SRPBasic_DelThreeKey(c_this,IndexContext,MainKey,SecondKey,ThirdKey);
}

VS_INT8 *Star_SRPBasic_QueryFirstThreeKey(void *c_this,void *IndexContext,VS_QUERYRECORD *QueryRecord,VS_UWORD *MainKey,VS_UWORD *SecondKey,VS_UWORD *ThirdKey)
{
    return g_star_CoreFunctionTbl->SRPBasic_QueryFirstThreeKey(c_this,IndexContext,QueryRecord,MainKey,SecondKey,ThirdKey);
}

VS_INT8 *Star_SRPBasic_QueryNextThreeKey(void *c_this,void *IndexContext,VS_QUERYRECORD *QueryRecord,VS_UWORD *MainKey,VS_UWORD *SecondKey,VS_UWORD *ThirdKey)
{
    return g_star_CoreFunctionTbl->SRPBasic_QueryNextThreeKey(c_this,IndexContext,QueryRecord,MainKey,SecondKey,ThirdKey);
}

VS_INT8 *Star_SRPBasic_QueryFirstThreeKeyA(void *c_this,void *IndexContext,VS_QUERYRECORD *QueryRecord,VS_UWORD *MainKey,VS_UWORD *SecondKey,VS_UWORD *ThirdKey)
{
    return g_star_CoreFunctionTbl->SRPBasic_QueryFirstThreeKeyA(c_this,IndexContext,QueryRecord,MainKey,SecondKey,ThirdKey);
}

VS_INT8 *Star_SRPBasic_QueryNextThreeKeyA(void *c_this,void *IndexContext,VS_QUERYRECORD *QueryRecord,VS_UWORD *MainKey,VS_UWORD *SecondKey,VS_UWORD *ThirdKey)
{
    return g_star_CoreFunctionTbl->SRPBasic_QueryNextThreeKeyA(c_this,IndexContext,QueryRecord,MainKey,SecondKey,ThirdKey);
}

VS_INT8 *Star_SRPBasic_QueryFirstThreeKey_F(void *c_this,void *IndexContext,VS_QUERYRECORD *QueryRecord,VS_UWORD MainKey,VS_UWORD *SecondKey,VS_UWORD *ThirdKey)
{
    return g_star_CoreFunctionTbl->SRPBasic_QueryFirstThreeKey_F(c_this,IndexContext,QueryRecord,MainKey,SecondKey,ThirdKey);
}

VS_INT8 *Star_SRPBasic_QueryNextThreeKey_F(void *c_this,void *IndexContext,VS_QUERYRECORD *QueryRecord,VS_UWORD MainKey,VS_UWORD *SecondKey,VS_UWORD *ThirdKey)
{
    return g_star_CoreFunctionTbl->SRPBasic_QueryNextThreeKey_F(c_this,IndexContext,QueryRecord,MainKey,SecondKey,ThirdKey);
}

VS_INT8 *Star_SRPBasic_QueryFirstThreeKeyA_F(void *c_this,void *IndexContext,VS_QUERYRECORD *QueryRecord,VS_UWORD MainKey,VS_UWORD *SecondKey,VS_UWORD *ThirdKey)
{
    return g_star_CoreFunctionTbl->SRPBasic_QueryFirstThreeKeyA_F(c_this,IndexContext,QueryRecord,MainKey,SecondKey,ThirdKey);
}

VS_INT8 *Star_SRPBasic_QueryNextThreeKeyA_F(void *c_this,void *IndexContext,VS_QUERYRECORD *QueryRecord,VS_UWORD MainKey,VS_UWORD *SecondKey,VS_UWORD *ThirdKey)
{
    return g_star_CoreFunctionTbl->SRPBasic_QueryNextThreeKeyA_F(c_this,IndexContext,QueryRecord,MainKey,SecondKey,ThirdKey);
}

VS_INT8 *Star_SRPBasic_QueryFirstThreeKey_S(void *c_this,void *IndexContext,VS_QUERYRECORD *QueryRecord,VS_UWORD MainKey,VS_UWORD SecondKey,VS_UWORD *ThirdKey)
{
    return g_star_CoreFunctionTbl->SRPBasic_QueryFirstThreeKey_S(c_this,IndexContext,QueryRecord,MainKey,SecondKey,ThirdKey);
}

VS_INT8 *Star_SRPBasic_QueryNextThreeKey_S(void *c_this,void *IndexContext,VS_QUERYRECORD *QueryRecord,VS_UWORD MainKey,VS_UWORD SecondKey,VS_UWORD *ThirdKey)
{
    return g_star_CoreFunctionTbl->SRPBasic_QueryNextThreeKey_S(c_this,IndexContext,QueryRecord,MainKey,SecondKey,ThirdKey);
}

VS_INT8 *Star_SRPBasic_QueryFirstThreeKeyA_S(void *c_this,void *IndexContext,VS_QUERYRECORD *QueryRecord,VS_UWORD MainKey,VS_UWORD SecondKey,VS_UWORD *ThirdKey)
{
    return g_star_CoreFunctionTbl->SRPBasic_QueryFirstThreeKeyA_S(c_this,IndexContext,QueryRecord,MainKey,SecondKey,ThirdKey);
}

VS_INT8 *Star_SRPBasic_QueryNextThreeKeyA_S(void *c_this,void *IndexContext,VS_QUERYRECORD *QueryRecord,VS_UWORD MainKey,VS_UWORD SecondKey,VS_UWORD *ThirdKey)
{
    return g_star_CoreFunctionTbl->SRPBasic_QueryNextThreeKeyA_S(c_this,IndexContext,QueryRecord,MainKey,SecondKey,ThirdKey);
}

void Star_SRPBasic_InsertIDKey(void *c_this,void *IndexContext,VS_UUID *UuidKey,VS_INT8 *Buf )
{
    g_star_CoreFunctionTbl->SRPBasic_InsertIDKey(c_this,IndexContext,UuidKey,Buf);
}

VS_INT8 *Star_SRPBasic_FindIDKey(void *c_this,void *IndexContext,VS_UUID *UuidKey)
{
    return g_star_CoreFunctionTbl->SRPBasic_FindIDKey(c_this,IndexContext,UuidKey);
}

VS_INT8 *Star_SRPBasic_DelIDKey(void *c_this,void *IndexContext,VS_UUID *UuidKey)
{
    return g_star_CoreFunctionTbl->SRPBasic_DelIDKey(c_this,IndexContext,UuidKey);
}

VS_INT8 *Star_SRPBasic_QueryFirstIDKey(void *c_this,void *IndexContext,VS_QUERYRECORD *QueryRecord,VS_UUID *UuidKey)
{
    return g_star_CoreFunctionTbl->SRPBasic_QueryFirstIDKey(c_this,IndexContext,QueryRecord,UuidKey);
}

VS_INT8 *Star_SRPBasic_QueryNextIDKey(void *c_this,void *IndexContext,VS_QUERYRECORD *QueryRecord,VS_UUID *UuidKey)
{
    return g_star_CoreFunctionTbl->SRPBasic_QueryNextIDKey(c_this,IndexContext,QueryRecord,UuidKey);
}

VS_INT8 *Star_SRPBasic_QueryFirstIDKeyA(void *c_this,void *IndexContext,VS_QUERYRECORD *QueryRecord,VS_UUID *UuidKey)
{
    return g_star_CoreFunctionTbl->SRPBasic_QueryFirstIDKeyA(c_this,IndexContext,QueryRecord,UuidKey);
}

VS_INT8 *Star_SRPBasic_QueryNextIDKeyA(void *c_this,void *IndexContext,VS_QUERYRECORD *QueryRecord,VS_UUID *UuidKey)
{
    return g_star_CoreFunctionTbl->SRPBasic_QueryNextIDKeyA(c_this,IndexContext,QueryRecord,UuidKey);
}

void Star_SRPBasic_InsertIDKeyEx(void *c_this,void *IndexContext,VS_UUID *UuidKey,VS_UWORD ExKey,VS_INT8 *Buf)
{
    g_star_CoreFunctionTbl->SRPBasic_InsertIDKeyEx(c_this,IndexContext,UuidKey,ExKey,Buf);
}

VS_INT8 *Star_SRPBasic_FindIDKeyEx(void *c_this,void *IndexContext,VS_UUID *UuidKey,VS_UWORD ExKey)
{
    return g_star_CoreFunctionTbl->SRPBasic_FindIDKeyEx(c_this,IndexContext,UuidKey,ExKey);
}

VS_INT8 *Star_SRPBasic_DelIDKeyEx(void *c_this,void *IndexContext,VS_UUID *UuidKey,VS_UWORD ExKey)
{
    return g_star_CoreFunctionTbl->SRPBasic_DelIDKeyEx(c_this,IndexContext,UuidKey,ExKey);
}

VS_INT8 *Star_SRPBasic_QueryFirstIDKeyEx(void *c_this,void *IndexContext,VS_QUERYRECORD *QueryRecord,VS_UUID *UuidKey,VS_UWORD *ExKey)
{
    return g_star_CoreFunctionTbl->SRPBasic_QueryFirstIDKeyEx(c_this,IndexContext,QueryRecord,UuidKey,ExKey);
}

VS_INT8 *Star_SRPBasic_QueryNextIDKeyEx(void *c_this,void *IndexContext,VS_QUERYRECORD *QueryRecord,VS_UUID *UuidKey,VS_UWORD *ExKey)
{
    return g_star_CoreFunctionTbl->SRPBasic_QueryNextIDKeyEx(c_this,IndexContext,QueryRecord,UuidKey,ExKey);
}

VS_INT8 *Star_SRPBasic_QueryFirstIDKeyEx_F(void *c_this,void *IndexContext,VS_QUERYRECORD *QueryRecord,VS_UUID *UuidKey,VS_UWORD *ExKey)
{
    return g_star_CoreFunctionTbl->SRPBasic_QueryFirstIDKeyEx_F(c_this,IndexContext,QueryRecord,UuidKey,ExKey);
}

VS_INT8 *Star_SRPBasic_QueryNextIDKeyEx_F(void *c_this,void *IndexContext,VS_QUERYRECORD *QueryRecord,VS_UUID *UuidKey,VS_UWORD *ExKey)
{
    return g_star_CoreFunctionTbl->SRPBasic_QueryNextIDKeyEx_F(c_this,IndexContext,QueryRecord,UuidKey,ExKey);
}

VS_INT8 *Star_SRPBasic_QueryFirstIDKeyExA(void *c_this,void *IndexContext,VS_QUERYRECORD *QueryRecord,VS_UUID *UuidKey,VS_UWORD *ExKey)
{
    return g_star_CoreFunctionTbl->SRPBasic_QueryFirstIDKeyExA(c_this,IndexContext,QueryRecord,UuidKey,ExKey);
}

VS_INT8 *Star_SRPBasic_QueryNextIDKeyExA(void *c_this,void *IndexContext,VS_QUERYRECORD *QueryRecord,VS_UUID *UuidKey,VS_UWORD *ExKey)
{
    return g_star_CoreFunctionTbl->SRPBasic_QueryNextIDKeyExA(c_this,IndexContext,QueryRecord,UuidKey,ExKey);
}

VS_INT32 Star_SRPBasic_GetKeyNumber(void *c_this,void *IndexContext)
{
    return g_star_CoreFunctionTbl->SRPBasic_GetKeyNumber(c_this,IndexContext);
}

void Star_SRPBasic_DelAllKey(void *c_this,void *IndexContext)
{
    g_star_CoreFunctionTbl->SRPBasic_DelAllKey(c_this,IndexContext);
}

void Star_SRPBasic_DestoryIndex(void *c_this,void *IndexContext)
{
    g_star_CoreFunctionTbl->SRPBasic_DestoryIndex(c_this,IndexContext);
}

VS_ULONG Star_SRPBasic_GetHashValue(void *c_this,void *Key,VS_ULONG Length,VS_ULONG InitValue)
{
    return g_star_CoreFunctionTbl->SRPBasic_GetHashValue(c_this,Key,Length,InitValue);
}

void *Star_SRPBasic_CreateMemory_Nor(void *c_this,VS_INT32 ItemSize)
{
    return g_star_CoreFunctionTbl->SRPBasic_CreateMemory_Nor(c_this,ItemSize);
}

void *Star_SRPBasic_CreateMemory_Dbg(void *c_this,VS_INT32 ItemSize,const VS_CHAR *FileName,VS_INT32 LineNumber)
{
    return g_star_CoreFunctionTbl->SRPBasic_CreateMemory_Dbg(c_this,ItemSize,FileName,LineNumber);
}

void *Star_SRPBasic_GetMemoryPtr_Nor(void *c_this,void *MemoryContext)
{
    return g_star_CoreFunctionTbl->SRPBasic_GetMemoryPtr_Nor(c_this,MemoryContext);
}

void *Star_SRPBasic_GetMemoryPtr_Dbg(void *c_this,void *MemoryContext,const VS_CHAR *FileName,VS_INT32 LineNumber)
{
    return g_star_CoreFunctionTbl->SRPBasic_GetMemoryPtr_Dbg(c_this,MemoryContext,FileName,LineNumber);
}

void *Star_SRPBasic_QueryFirstMemoryPtr(void *c_this,void *MemoryContext,VS_QUERYRECORD *QueryRecord)
{
    return g_star_CoreFunctionTbl->SRPBasic_QueryFirstMemoryPtr(c_this,MemoryContext,QueryRecord);
}

void *Star_SRPBasic_QueryNextMemoryPtr(void *c_this,void *MemoryContext,VS_QUERYRECORD *QueryRecord)
{
    return g_star_CoreFunctionTbl->SRPBasic_QueryNextMemoryPtr(c_this,MemoryContext,QueryRecord);
}

void Star_SRPBasic_FreeMemoryPtr(void *c_this,void *MemoryContext,void *Ptr)
{
    g_star_CoreFunctionTbl->SRPBasic_FreeMemoryPtr(c_this,MemoryContext,Ptr);
}

void Star_SRPBasic_ClearMemory(void *c_this,void *MemoryContext)
{
    g_star_CoreFunctionTbl->SRPBasic_ClearMemory(c_this,MemoryContext);
}

void Star_SRPBasic_DestoryMemory(void *c_this,void *MemoryContext)
{
    g_star_CoreFunctionTbl->SRPBasic_DestoryMemory(c_this,MemoryContext);
}

void *Star_SRPBasic_Malloc_Nor(void *c_this,VS_INT32 MemorySize)
{
    return g_star_CoreFunctionTbl->SRPBasic_Malloc_Nor(c_this,MemorySize);
}

void *Star_SRPBasic_Malloc_Dbg(void *c_this,VS_INT32 MemorySize,const VS_CHAR *FileName,VS_INT32 LineNumber)
{
    return g_star_CoreFunctionTbl->SRPBasic_Malloc_Dbg(c_this,MemorySize,FileName,LineNumber);
}

void Star_SRPBasic_Free(void *c_this,void *MemoryPtr)
{
    g_star_CoreFunctionTbl->SRPBasic_Free(c_this,MemoryPtr);
}

void Star_SRPBasic_GetMemoryUsed(void *c_this, VS_UWORD *KernelAllocSize,VS_UWORD *DataAllocSize,VS_UWORD *AppAllocSize, VS_UWORD *ScriptMemoryUsed )
{
    g_star_CoreFunctionTbl->SRPBasic_GetMemoryUsed(c_this,KernelAllocSize,DataAllocSize,AppAllocSize,ScriptMemoryUsed);
}

VS_ULONG Star_SRPBasic_GetMachineID(void *c_this,void *Machine)
{
    return g_star_CoreFunctionTbl->SRPBasic_GetMachineID(c_this,Machine);
}

void *Star_SRPBasic_FindMachine(void *c_this,VS_ULONG MachineID)
{
    return g_star_CoreFunctionTbl->SRPBasic_FindMachine(c_this,MachineID);
}

VS_BOOL Star_SRPBasic_MD5ToUuid(void *c_this,const VS_INT8 *String,VS_UUID *Uuid)
{
    return g_star_CoreFunctionTbl->SRPBasic_MD5ToUuid(c_this,String,Uuid);
}

VS_INT8 *Star_SRPBasic_UuidToMD5(void *c_this,VS_UUID *Uuid)
{
    return g_star_CoreFunctionTbl->SRPBasic_UuidToMD5(c_this,Uuid);
}

VS_INT8 *Star_SRPBasic_StringToUtf8(void *c_this,const VS_INT8 *String)
{
    return g_star_CoreFunctionTbl->SRPBasic_StringToUtf8(c_this,String);
}

VS_INT8 *Star_SRPBasic_Utf8ToString(void *c_this,const VS_INT8 *String)
{
    return g_star_CoreFunctionTbl->SRPBasic_Utf8ToString(c_this,String);
}

VS_BOOL Star_SRPBasic_ProgramRestart(void *c_this)
{
    return g_star_CoreFunctionTbl->SRPBasic_ProgramRestart(c_this);
}

VS_BOOL Star_SRPBasic_HttpDownLoad(void *c_this, VS_UUID *AttachObjectID, const VS_CHAR *ServerUrl,const VS_CHAR *ClientPath,const VS_CHAR *FileName, VS_FileUpDownLoadCallBackProc CallBackProc, VS_UUID *ObjectID, VS_UWORD Para, VS_BOOL SaveFileFlag )
{
    return g_star_CoreFunctionTbl->SRPBasic_HttpDownLoad(c_this,AttachObjectID,ServerUrl,ClientPath,FileName,CallBackProc,ObjectID,Para,SaveFileFlag);
}

void Star_SRPBasic_HttpDownLoadAbort(void *c_this)
{
    g_star_CoreFunctionTbl->SRPBasic_HttpDownLoadAbort(c_this);
}

void Star_SRPBasic_RegWebDownFunction(void *c_this,VS_WebDownInfoProc CallBackProc,VS_UWORD Para)
{
    g_star_CoreFunctionTbl->SRPBasic_RegWebDownFunction(c_this,CallBackProc,Para);
}

void Star_SRPBasic_UnRegWebDownFunction(void *c_this,VS_WebDownInfoProc CallBackProc,VS_UWORD Para)
{
    g_star_CoreFunctionTbl->SRPBasic_UnRegWebDownFunction(c_this,CallBackProc,Para);
}

void Star_SRPBasic_WebDownPrint(void *c_this,VS_ULONG uMes, const VS_CHAR *FileName, VS_UINT64 MaxLength, VS_UINT64 CurLength)
{
    g_star_CoreFunctionTbl->SRPBasic_WebDownPrint(c_this,uMes,FileName,MaxLength,CurLength);
}

VS_BOOL Star_SRPBasic_CanSetStaticData(void *c_this,void *Object,VS_ULONG DataSize)
{
    return g_star_CoreFunctionTbl->SRPBasic_CanSetStaticData(c_this,Object,DataSize);
}

VS_BOOL Star_SRPBasic_SetStaticData(void *c_this, VS_UUID *ObjectID,VS_ULONG UniqueDataUnitID,VS_ULONG DataSize,VS_INT8 *DataBuf,VS_STATICID *RetDataVersion)
{
    return g_star_CoreFunctionTbl->SRPBasic_SetStaticData(c_this,ObjectID,UniqueDataUnitID,DataSize,DataBuf,RetDataVersion);
}

void *Star_SRPBasic_GetEnvDependCheckInfo(void *c_this,const VS_CHAR *ServiceName,VS_ULONG *Size)
{
    return g_star_CoreFunctionTbl->SRPBasic_GetEnvDependCheckInfo(c_this,ServiceName,Size);
}

void Star_SRPBasic_SetEnvDependCheckInfo(void *c_this,VS_ULONG Size,void *Buf)
{
    g_star_CoreFunctionTbl->SRPBasic_SetEnvDependCheckInfo(c_this,Size,Buf);
}

VS_UINT8 Star_SRPBasic_GetEnvStartType(void *c_this)
{
    return g_star_CoreFunctionTbl->SRPBasic_GetEnvStartType(c_this);
}

void *Star_SRPBasic_GetEnvPara(void *c_this)
{
    return g_star_CoreFunctionTbl->SRPBasic_GetEnvPara(c_this);
}

void Star_SRPBasic_SetEnvPara(void *c_this,void *Para)
{
    g_star_CoreFunctionTbl->SRPBasic_SetEnvPara(c_this,Para);
}

void Star_SRPBasic_SetEnvInputPara(void *c_this,void *Para)
{
    g_star_CoreFunctionTbl->SRPBasic_SetEnvInputPara(c_this,Para);
}

void *Star_SRPBasic_GetEnvInputPara(void *c_this)
{
    return g_star_CoreFunctionTbl->SRPBasic_GetEnvInputPara(c_this);
}

VS_CHAR *Star_SRPBasic_GetEnvParentUrl(void *c_this)
{
    return g_star_CoreFunctionTbl->SRPBasic_GetEnvParentUrl(c_this);
}

void Star_SRPBasic_SetEnvCurrentUrl(void *c_this,const VS_CHAR *Url)
{
    g_star_CoreFunctionTbl->SRPBasic_SetEnvCurrentUrl(c_this,Url);
}

VS_INT32 Star_SRPBasic_RedirectToUrlRequest(void *c_this,const VS_CHAR *Url,void *ParaPkg,RedirectToUrl_InfoProc CallBackProc,VS_UWORD Para,const VS_CHAR *WorkDirectory,const VS_CHAR *ChildTermScript)
{
    return g_star_CoreFunctionTbl->SRPBasic_RedirectToUrlRequest(c_this,Url,ParaPkg,CallBackProc,Para,WorkDirectory,ChildTermScript);
}

void Star_SRPBasic_RedirectToUrlFail(void *c_this,const VS_CHAR *Url)
{
    g_star_CoreFunctionTbl->SRPBasic_RedirectToUrlFail(c_this,Url);
}

void Star_SRPBasic_SetRedirectToUrlInfo(void *c_this,void *ParaPkg)
{
    g_star_CoreFunctionTbl->SRPBasic_SetRedirectToUrlInfo(c_this,ParaPkg);
}

void Star_SRPBasic_RedirectToUrlAbort(void *c_this)
{
    g_star_CoreFunctionTbl->SRPBasic_RedirectToUrlAbort(c_this);
}

VS_BOOL Star_SRPBasic_OpenLuaEdit(void *c_this,const VS_CHAR *Module,VS_ULONG Config,VS_BOOL CloseEnable)
{
    return g_star_CoreFunctionTbl->SRPBasic_OpenLuaEdit(c_this,Module,Config,CloseEnable);
}

void Star_SRPBasic_LuaEditDisp(void *c_this,const VS_CHAR *Info)
{
    g_star_CoreFunctionTbl->SRPBasic_LuaEditDisp(c_this,Info);
}

void Star_SRPBasic_CloseLuaEdit(void *c_this)
{
    g_star_CoreFunctionTbl->SRPBasic_CloseLuaEdit(c_this);
}

void Star_SRPBasic_LuaEditHelp(void *c_this,VS_INT32 Type,const VS_CHAR *HelpInfo)
{
    g_star_CoreFunctionTbl->SRPBasic_LuaEditHelp(c_this,Type,HelpInfo);
}

void Star_SRPBasic_RegDllCallBack(void *c_this, VS_MsgCallBackProc MsgCallBackProc, VS_UWORD MsgCallBackPara )
{
    g_star_CoreFunctionTbl->SRPBasic_RegDllCallBack(c_this,MsgCallBackProc,MsgCallBackPara);
}

void Star_SRPBasic_UnRegDllCallBack(void *c_this, VS_MsgCallBackProc MsgCallBackProc, VS_UWORD MsgCallBackPara )
{
    g_star_CoreFunctionTbl->SRPBasic_UnRegDllCallBack(c_this,MsgCallBackProc,MsgCallBackPara);
}

void Star_SRPBasic_CreateUuid(void *c_this,VS_UUID *UuidPtr)
{
    g_star_CoreFunctionTbl->SRPBasic_CreateUuid(c_this,UuidPtr);
}

void Star_SRPBasic_GetSRPTempPath(void *c_this,VS_ULONG BufSize,VS_CHAR *Buf)
{
    g_star_CoreFunctionTbl->SRPBasic_GetSRPTempPath(c_this,BufSize,Buf);
}

VS_BOOL Star_SRPBasic_Compress(void *c_this,VS_UINT8 *dest,VS_ULONG *destLen,VS_UINT8 *source,VS_ULONG sourceLen )
{
    return g_star_CoreFunctionTbl->SRPBasic_Compress(c_this,dest,destLen,source,sourceLen);
}

VS_BOOL Star_SRPBasic_UnCompress(void *c_this,VS_UINT8 *dest,VS_ULONG *destLen,VS_UINT8 *source,VS_ULONG sourceLen )
{
    return g_star_CoreFunctionTbl->SRPBasic_UnCompress(c_this,dest,destLen,source,sourceLen);
}

void *Star_SRPBasic_CreateMemoryFile(void *c_this)
{
    return g_star_CoreFunctionTbl->SRPBasic_CreateMemoryFile(c_this);
}

void *Star_SRPBasic_GetEnvMemoryFile(void *c_this)
{
    return g_star_CoreFunctionTbl->SRPBasic_GetEnvMemoryFile(c_this);
}

void Star_SRPBasic_SetEnvMemoryFile(void *c_this,void *MemoryFile)
{
    g_star_CoreFunctionTbl->SRPBasic_SetEnvMemoryFile(c_this,MemoryFile);
}

void Star_SRPBasic_GetUrl(void *c_this,VS_CHAR *Buf,VS_INT32 BufSize)
{
    g_star_CoreFunctionTbl->SRPBasic_GetUrl(c_this,Buf,BufSize);
}

VS_BOOL Star_SRPBasic_ToAbsoluteUrl(void *c_this,const VS_CHAR *InputUrl,VS_CHAR *OutputUrl,VS_INT32 OutputUrlBufSize )
{
    return g_star_CoreFunctionTbl->SRPBasic_ToAbsoluteUrl(c_this,InputUrl,OutputUrl,OutputUrlBufSize);
}

VS_INT32 Star_SRPBasic_RunFromUrl(void *c_this,const VS_CHAR *Url,VS_INT8 RestartFlag,VS_BOOL WaitFlag)
{
    return g_star_CoreFunctionTbl->SRPBasic_RunFromUrl(c_this,Url,RestartFlag,WaitFlag);
}

VS_INT32 Star_SRPBasic_RunFromBuf(void *c_this,VS_CHAR *Buf,VS_ULONG BufSize,VS_INT8 RestartFlag,VS_BOOL WaitFlag)
{
    return g_star_CoreFunctionTbl->SRPBasic_RunFromBuf(c_this,Buf,BufSize,RestartFlag,WaitFlag);
}

VS_BOOL Star_SRPBasic_IsLoadServiceBusy(void *c_this)
{
    return g_star_CoreFunctionTbl->SRPBasic_IsLoadServiceBusy(c_this);
}

VS_BOOL Star_SRPBasic_IsLoadServiceIdle(void *c_this)
{
    return g_star_CoreFunctionTbl->SRPBasic_IsLoadServiceIdle(c_this);
}

void Star_SRPBasic_SetDepend(void *c_this,const VS_CHAR *ServiceName,VS_BOOL DefaultUrlFlag)
{
    g_star_CoreFunctionTbl->SRPBasic_SetDepend(c_this,ServiceName,DefaultUrlFlag);
}

VS_BOOL Star_SRPBasic_GetServicePathByName(void *c_this,const VS_CHAR *ServiceName,VS_CHAR *ServicePath,VS_ULONG ServicePathSize)
{
    return g_star_CoreFunctionTbl->SRPBasic_GetServicePathByName(c_this,ServiceName,ServicePath,ServicePathSize);
}

void Star_SRPBasic_InsertSearchPath(void *c_this,const VS_CHAR *SearchPath)
{
    g_star_CoreFunctionTbl->SRPBasic_InsertSearchPath(c_this,SearchPath);
}

void Star_SRPBasic_ClearSearchPath(void *c_this)
{
    g_star_CoreFunctionTbl->SRPBasic_ClearSearchPath(c_this);
}

VS_CHAR *Star_SRPBasic_FirstSearchPath(void *c_this,VS_QUERYRECORD *QueryRecord)
{
    return g_star_CoreFunctionTbl->SRPBasic_FirstSearchPath(c_this,QueryRecord);
}

VS_CHAR *Star_SRPBasic_NextSearchPath(void *c_this,VS_QUERYRECORD *QueryRecord)
{
    return g_star_CoreFunctionTbl->SRPBasic_NextSearchPath(c_this,QueryRecord);
}

VS_BOOL Star_SRPBasic_GetSaveFile(void *c_this, const VS_CHAR *Caption, const VS_CHAR *Filter, VS_ULONG FilterIndex, const VS_CHAR *DefExt, VS_CHAR *FileNameBuf,VS_INT32 FileNameBufSize)
{
    return g_star_CoreFunctionTbl->SRPBasic_GetSaveFile(c_this,Caption,Filter,FilterIndex,DefExt,FileNameBuf,FileNameBufSize);
}

VS_BOOL Star_SRPBasic_GetOpenFile(void *c_this, const VS_CHAR *Caption, const VS_CHAR *Filter, VS_ULONG FilterIndex, const VS_CHAR *DefExt, VS_CHAR *FileNameBuf,VS_INT32 FileNameBufSize)
{
    return g_star_CoreFunctionTbl->SRPBasic_GetOpenFile(c_this,Caption,Filter,FilterIndex,DefExt,FileNameBuf,FileNameBufSize);
}

void Star_SRPBasic_SaveServiceStaticData(void *c_this,VS_UUID *ServiceID)
{
    g_star_CoreFunctionTbl->SRPBasic_SaveServiceStaticData(c_this,ServiceID);
}

void Star_SRPBasic_GetStaticVersion(void *c_this, VS_ULONG DataSize,VS_INT8 *DataBuf,VS_STATICID *RetDataVersion)
{
    g_star_CoreFunctionTbl->SRPBasic_GetStaticVersion(c_this,DataSize,DataBuf,RetDataVersion);
}

void *Star_SRPBasic_GetSysDocClass(void *c_this)
{
    return g_star_CoreFunctionTbl->SRPBasic_GetSysDocClass(c_this);
}

void *Star_SRPBasic_FirstDoc(void *c_this,VS_QUERYRECORD *QueryRecord,VS_CHAR **DocName)
{
    return g_star_CoreFunctionTbl->SRPBasic_FirstDoc(c_this,QueryRecord,DocName);
}

void *Star_SRPBasic_NextDoc(void *c_this,VS_QUERYRECORD *QueryRecord,VS_CHAR **DocName)
{
    return g_star_CoreFunctionTbl->SRPBasic_NextDoc(c_this,QueryRecord,DocName);
}

void Star_SRPBasic_RegisterDoc(void *c_this,void *DocObject,const VS_CHAR *DocName)
{
    g_star_CoreFunctionTbl->SRPBasic_RegisterDoc(c_this,DocObject,DocName);
}

void Star_SRPBasic_UnRegisterDoc(void *c_this,void *DocObject)
{
    g_star_CoreFunctionTbl->SRPBasic_UnRegisterDoc(c_this,DocObject);
}

VS_EVENTPARAM_RUNPARAM *Star_SRPBasic_ProcessSysDocEvent(void *c_this,VS_UUID *DocObjectID,VS_UUID *EventID,VS_EVENTPARAM_RUNPARAM *RequestParam)
{
    return g_star_CoreFunctionTbl->SRPBasic_ProcessSysDocEvent(c_this,DocObjectID,EventID,RequestParam);
}

VS_BOOL Star_SRPBasic_RegDocEventFunction(void *c_this,VS_UUID *DocObjectID,VS_UUID *EventID, void *FuncAddr,VS_UWORD Para)
{
    return g_star_CoreFunctionTbl->SRPBasic_RegDocEventFunction(c_this,DocObjectID,EventID,FuncAddr,Para);
}

void Star_SRPBasic_UnRegDocEventFunction(void *c_this,VS_UUID *DocObjectID,VS_UUID *EventID, void *FuncAddr,VS_UWORD Para )
{
    g_star_CoreFunctionTbl->SRPBasic_UnRegDocEventFunction(c_this,DocObjectID,EventID,FuncAddr,Para);
}

void Star_SRPBasic_ToClipBoard(void *c_this,const VS_CHAR *Info)
{
    g_star_CoreFunctionTbl->SRPBasic_ToClipBoard(c_this,Info);
}

VS_CHAR *Star_SRPBasic_FromClipBoard(void *c_this)
{
    return g_star_CoreFunctionTbl->SRPBasic_FromClipBoard(c_this);
}

VS_BOOL Star_SRPBasic_IsWindowlessSite(void *c_this)
{
    return g_star_CoreFunctionTbl->SRPBasic_IsWindowlessSite(c_this);
}

VS_BOOL Star_SRPBasic_IsWindowlessTransparent(void *c_this)
{
    return g_star_CoreFunctionTbl->SRPBasic_IsWindowlessTransparent(c_this);
}

void Star_SRPBasic_RegWindowlessSiteCallBack(void *c_this,struct VSWindowlessSiteCallBackInfo *CallBackInfo, VS_UUID *ObjectID, VS_UWORD Para )
{
    g_star_CoreFunctionTbl->SRPBasic_RegWindowlessSiteCallBack(c_this,CallBackInfo,ObjectID,Para);
}

void Star_SRPBasic_UnRegWindowlessSiteCallBack(void *c_this,struct VSWindowlessSiteCallBackInfo *CallBackInfo, VS_UUID *ObjectID, VS_UWORD Para )
{
    g_star_CoreFunctionTbl->SRPBasic_UnRegWindowlessSiteCallBack(c_this,CallBackInfo,ObjectID,Para);
}

void Star_SRPBasic_Windowless_Draw(void *c_this, void *hDC, void *rcBounds, void *rcInvalid )
{
    g_star_CoreFunctionTbl->SRPBasic_Windowless_Draw(c_this,hDC,rcBounds,rcInvalid);
}

VS_BOOL Star_SRPBasic_Windowless_Message(void *c_this, VS_ULONG uMes,VS_UWORD wParam,VS_UWORD LParam,VS_UWORD *Result )
{
    return g_star_CoreFunctionTbl->SRPBasic_Windowless_Message(c_this,uMes,wParam,LParam,Result);
}

VS_BOOL Star_SRPBasic_Windowless_GetDropTarget(void *c_this, void **DropTarget )
{
    return g_star_CoreFunctionTbl->SRPBasic_Windowless_GetDropTarget(c_this,DropTarget);
}

void Star_SRPBasic_Windowless_Redraw(void *c_this, VS_BOOL fErase )
{
    g_star_CoreFunctionTbl->SRPBasic_Windowless_Redraw(c_this,fErase);
}

void Star_SRPBasic_Windowless_GetDC(void *c_this, void **hDC,VS_RECT *rEct )
{
    g_star_CoreFunctionTbl->SRPBasic_Windowless_GetDC(c_this,hDC,rEct);
}

void Star_SRPBasic_Windowless_ReleaseDC(void *c_this, void *hDC )
{
    g_star_CoreFunctionTbl->SRPBasic_Windowless_ReleaseDC(c_this,hDC);
}

VS_BOOL Star_SRPBasic_SetClientPort(void *c_this,const VS_CHAR *ClientInterface,VS_UINT16 ClientPortNumber)
{
    return g_star_CoreFunctionTbl->SRPBasic_SetClientPort(c_this,ClientInterface,ClientPortNumber);
}

VS_BOOL Star_SRPBasic_SetDebugPort(void *c_this,const VS_CHAR *DebugInterface,VS_UINT16 DebugPortNumber)
{
    return g_star_CoreFunctionTbl->SRPBasic_SetDebugPort(c_this,DebugInterface,DebugPortNumber);
}

VS_BOOL Star_SRPBasic_SetTelnetPort(void *c_this,VS_UINT16 TelnetPortNumber)
{
    return g_star_CoreFunctionTbl->SRPBasic_SetTelnetPort(c_this,TelnetPortNumber);
}

VS_BOOL Star_SRPBasic_SetOutputPort(void *c_this,const VS_CHAR *OutputHost,VS_UINT16 OutputPortNumber)
{
    return g_star_CoreFunctionTbl->SRPBasic_SetOutputPort(c_this,OutputHost,OutputPortNumber);
}

VS_BOOL Star_SRPBasic_SetWebServerPort(void *c_this,const VS_CHAR *WebServerHost,VS_UINT16 WebServerPortNumber,VS_INT32 ConnectionNumber,VS_ULONG PostSize)
{
    return g_star_CoreFunctionTbl->SRPBasic_SetWebServerPort(c_this,WebServerHost,WebServerPortNumber,ConnectionNumber,PostSize);
}

VS_UUID *Star_SRPBasic_GetVSObjectID(void *c_this,VS_INT32 Which)
{
    return g_star_CoreFunctionTbl->SRPBasic_GetVSObjectID(c_this,Which);
}

void *Star_SRPBasic_GetSRPControlInterface(void *c_this)
{
    return g_star_CoreFunctionTbl->SRPBasic_GetSRPControlInterface(c_this);
}

void *Star_SRPBasic_GetFunctionParaInterface(void *c_this)
{
    return g_star_CoreFunctionTbl->SRPBasic_GetFunctionParaInterface(c_this);
}

void *Star_SRPBasic_GetParaPkgInterface(void *c_this)
{
    return g_star_CoreFunctionTbl->SRPBasic_GetParaPkgInterface(c_this);
}

void *Star_SRPBasic_GetSRPLockInterface(void *c_this)
{
    return g_star_CoreFunctionTbl->SRPBasic_GetSRPLockInterface(c_this);
}

void *Star_SRPBasic_GetSXMLInterface(void *c_this)
{
    return g_star_CoreFunctionTbl->SRPBasic_GetSXMLInterface(c_this);
}

void *Star_SRPBasic_GetSRPBinBufInterface(void *c_this)
{
    return g_star_CoreFunctionTbl->SRPBasic_GetSRPBinBufInterface(c_this);
}

void *Star_SRPBasic_GetCommInterface(void *c_this)
{
    return g_star_CoreFunctionTbl->SRPBasic_GetCommInterface(c_this);
}

void *Star_SRPBasic_GetFileDiskInterface(void *c_this)
{
    return g_star_CoreFunctionTbl->SRPBasic_GetFileDiskInterface(c_this);
}

void Star_SRPBasic_GetSRPConfigPath(void *c_this,VS_ULONG BufSize,VS_CHAR *Buf)
{
    g_star_CoreFunctionTbl->SRPBasic_GetSRPConfigPath(c_this,BufSize,Buf);
}

VS_BOOL Star_SRPBasic_RegTempFile(void *c_this,const VS_CHAR *TempFileName,const VS_CHAR *OriFileName)
{
    return g_star_CoreFunctionTbl->SRPBasic_RegTempFile(c_this,TempFileName,OriFileName);
}

VS_CHAR *Star_SRPBasic_GetRegTempFile(void *c_this,const VS_CHAR *OriFileName,VS_CHAR *Buf,VS_INT32 BufSize)
{
    return g_star_CoreFunctionTbl->SRPBasic_GetRegTempFile(c_this,OriFileName,Buf,BufSize);
}

void Star_SRPBasic_UnRegTempFile(void *c_this,const VS_CHAR *TempFileName)
{
    g_star_CoreFunctionTbl->SRPBasic_UnRegTempFile(c_this,TempFileName);
}

void Star_SRPBasic_GetConfigResult(void *c_this,VS_BOOL *DebugCfgResult,VS_BOOL *DirectClientCfgResult,VS_BOOL *TelnetCfgResult,VS_BOOL *WebServerCfgResult)
{
    g_star_CoreFunctionTbl->SRPBasic_GetConfigResult(c_this,DebugCfgResult,DirectClientCfgResult,TelnetCfgResult,WebServerCfgResult);
}

VS_CHAR *Star_SRPBasic_GetConfigEnvTag(void *c_this)
{
    return g_star_CoreFunctionTbl->SRPBasic_GetConfigEnvTag(c_this);
}

void Star_SRPBasic_RegDispatchCallBack(void *c_this,VS_SRPDispatchCallBackProc CallBack,VS_UWORD Para)
{
    g_star_CoreFunctionTbl->SRPBasic_RegDispatchCallBack(c_this,CallBack,Para);
}

void Star_SRPBasic_UnRegDispatchCallBack(void *c_this,VS_SRPDispatchCallBackProc CallBack,VS_UWORD Para)
{
    g_star_CoreFunctionTbl->SRPBasic_UnRegDispatchCallBack(c_this,CallBack,Para);
}

void *Star_SRPBasic_Dup(void *c_this)
{
    return g_star_CoreFunctionTbl->SRPBasic_Dup(c_this);
}

void *Star_SRPBasic_QueryInterface(void *c_this, VS_UUID *InterfaceID )
{
    return g_star_CoreFunctionTbl->SRPBasic_QueryInterface(c_this,InterfaceID);
}

VS_BOOL Star_SRPBasic_LockLuaTable(void *c_this)
{
    return g_star_CoreFunctionTbl->SRPBasic_LockLuaTable(c_this);
}

VS_BOOL Star_SRPBasic_UnLockLuaTable(void *c_this)
{
    return g_star_CoreFunctionTbl->SRPBasic_UnLockLuaTable(c_this);
}

VS_UUID *Star_SRPBasic_GetIDEx(void *c_this,void *Object)
{
    return g_star_CoreFunctionTbl->SRPBasic_GetIDEx(c_this,Object);
}

VS_BOOL Star_SRPBasic_IsRootService(void *c_this)
{
    return g_star_CoreFunctionTbl->SRPBasic_IsRootService(c_this);
}

void Star_SRPBasic_AddRef(void *c_this)
{
    g_star_CoreFunctionTbl->SRPBasic_AddRef(c_this);
}

VS_INT32 Star_SRPBasic_GetRef(void *c_this)
{
    return g_star_CoreFunctionTbl->SRPBasic_GetRef(c_this);
}

void Star_SRPBasic_GetConfig(void *c_this,void *XmlInterface)
{
    g_star_CoreFunctionTbl->SRPBasic_GetConfig(c_this,XmlInterface);
}

void Star_SRPBasic_GetConfigHost(void *c_this, VS_CHAR *Buf,VS_INT32 BufSize )
{
    g_star_CoreFunctionTbl->SRPBasic_GetConfigHost(c_this,Buf,BufSize);
}

VS_CHAR *Star_SRPBasic_LuaToLString(void *c_this,VS_INT32 index,VS_ULONG *len)
{
    return g_star_CoreFunctionTbl->SRPBasic_LuaToLString(c_this,index,len);
}

VS_BOOL Star_SRPBasic_LuaIsInt(void *c_this, VS_INT32 Index )
{
    return g_star_CoreFunctionTbl->SRPBasic_LuaIsInt(c_this,Index);
}

VS_BOOL Star_SRPBasic_ImportServiceFromXmlBuf(void *c_this, const VS_CHAR *Buf, VS_BOOL LoadRunModule )
{
    return g_star_CoreFunctionTbl->SRPBasic_ImportServiceFromXmlBuf(c_this,Buf,LoadRunModule);
}

VS_BOOL Star_SRPBasic_DoFileEx(void *c_this, const VS_CHAR *ScriptInterface,const VS_CHAR *FileName, VS_CHAR **ErrorInfo, const VS_CHAR *WorkDirectory, VS_BOOL IsUTF8,const VS_CHAR *ModuleName )
{
    return g_star_CoreFunctionTbl->SRPBasic_DoFileEx(c_this,ScriptInterface,FileName,ErrorInfo,WorkDirectory,IsUTF8,ModuleName);
}

VS_BOOL Star_SRPBasic_PostDoFileEx(void *c_this, const VS_CHAR *ScriptInterface,const VS_CHAR *FileName, VS_CHAR **ErrorInfo, const VS_CHAR *WorkDirectory, VS_BOOL IsUTF8,const VS_CHAR *ModuleName )
{
    return g_star_CoreFunctionTbl->SRPBasic_PostDoFileEx(c_this,ScriptInterface,FileName,ErrorInfo,WorkDirectory,IsUTF8,ModuleName);
}

void Star_SRPBasic_AddRefEx(void *c_this,void *Object)
{
    g_star_CoreFunctionTbl->SRPBasic_AddRefEx(c_this,Object);
}

void Star_SRPBasic_DelRefEx(void *c_this,void *Object)
{
    g_star_CoreFunctionTbl->SRPBasic_DelRefEx(c_this,Object);
}

VS_BOOL Star_SRPBasic_InitRaw(void *c_this,const VS_CHAR *ScriptInterface,void *SRPInterface)
{
    return g_star_CoreFunctionTbl->SRPBasic_InitRaw(c_this,ScriptInterface,SRPInterface);
}

VS_BOOL Star_SRPBasic_LoadRawModule(void *c_this,const VS_CHAR *ScriptInterface,const VS_CHAR *ModuleName,const VS_CHAR *FileOrString,VS_BOOL IsString,VS_CHAR **ErrorInfo)
{
    return g_star_CoreFunctionTbl->SRPBasic_LoadRawModule(c_this,ScriptInterface,ModuleName,FileOrString,IsString,ErrorInfo);
}

VS_BOOL Star_SRPBasic_LoadRawModuleEx(void *c_this,const VS_CHAR *ScriptInterface,const VS_CHAR *ModuleName,void *Object,VS_CHAR **ErrorInfo)
{
    return g_star_CoreFunctionTbl->SRPBasic_LoadRawModuleEx(c_this,ScriptInterface,ModuleName,Object,ErrorInfo);
}

VS_BOOL Star_SRPBasic_DefScriptRawType(void *c_this,const VS_CHAR *ScriptInterface,const VS_CHAR *ModuleName,const VS_CHAR *FileOrString,VS_BOOL IsString,VS_CHAR **ErrorInfo)
{
    return g_star_CoreFunctionTbl->SRPBasic_DefScriptRawType(c_this,ScriptInterface,ModuleName,FileOrString,IsString,ErrorInfo);
}

void *Star_SRPBasic_GetRawContextBuf(void *c_this,void *Object,const VS_CHAR *ScriptInterface)
{
    return g_star_CoreFunctionTbl->SRPBasic_GetRawContextBuf(c_this,Object,ScriptInterface);
}

VS_INT32 Star_SRPBasic_NewScriptRawTypeGroup(void *c_this)
{
    return g_star_CoreFunctionTbl->SRPBasic_NewScriptRawTypeGroup(c_this);
}

VS_INT32 Star_SRPBasic_GetScriptRawTypeGroup(void *c_this,VS_INT32 ScriptRawType)
{
    return g_star_CoreFunctionTbl->SRPBasic_GetScriptRawTypeGroup(c_this,ScriptRawType);
}

VS_INT32 Star_SRPBasic_RegScriptRawType(void *c_this,const VS_CHAR *ScriptInterface,const VS_CHAR *TypeGroupName,VS_INT32 GroupIndex,const VS_CHAR *TypeName)
{
    return g_star_CoreFunctionTbl->SRPBasic_RegScriptRawType(c_this,ScriptInterface,TypeGroupName,GroupIndex,TypeName);
}

VS_INT32 Star_SRPBasic_GetScriptRawType(void *c_this,const VS_CHAR *ScriptInterface,const VS_CHAR *TypeGroupName,const VS_CHAR *TypeName)
{
    return g_star_CoreFunctionTbl->SRPBasic_GetScriptRawType(c_this,ScriptInterface,TypeGroupName,TypeName);
}

VS_CHAR *Star_SRPBasic_GetScriptRawTypeEx(void *c_this,VS_INT32 RawType,VS_CHAR **ScriptInterface,VS_CHAR **TypeGroupName)
{
    return g_star_CoreFunctionTbl->SRPBasic_GetScriptRawTypeEx(c_this,RawType,ScriptInterface,TypeGroupName);
}

void Star_SRPBasic_ReleaseOwner(void *c_this)
{
    g_star_CoreFunctionTbl->SRPBasic_ReleaseOwner(c_this);
}

VS_BOOL Star_SRPBasic_ReleaseOwnerEx(void *c_this,void *Object)
{
    return g_star_CoreFunctionTbl->SRPBasic_ReleaseOwnerEx(c_this,Object);
}

VS_BOOL Star_SRPBasic_ReleaseOwnerExForScript(void *c_this,const VS_CHAR *ScriptInterface,void *Object)
{
    return g_star_CoreFunctionTbl->SRPBasic_ReleaseOwnerExForScript(c_this,ScriptInterface,Object);
}

void Star_SRPBasic_CaptureOwnerExForScript(void *c_this,const VS_CHAR *ScriptInterface,void *Object)
{
    g_star_CoreFunctionTbl->SRPBasic_CaptureOwnerExForScript(c_this,ScriptInterface,Object);
}

VS_INT32 Star_SRPBasic_GetRefEx(void *c_this,void *Object)
{
    return g_star_CoreFunctionTbl->SRPBasic_GetRefEx(c_this,Object);
}

VS_CHAR *Star_SRPBasic_GetRefInfo(void *c_this,void *Object)
{
    return g_star_CoreFunctionTbl->SRPBasic_GetRefInfo(c_this,Object);
}

void Star_SRPBasic_LogObjectFreeByUnLock(void *c_this,VS_BOOL Flag)
{
    g_star_CoreFunctionTbl->SRPBasic_LogObjectFreeByUnLock(c_this,Flag);
}

void Star_SRPBasic_SUnLockGC(void *c_this)
{
    g_star_CoreFunctionTbl->SRPBasic_SUnLockGC(c_this);
}

VS_INT32 Star_SRPBasic_GetLastError(void *c_this)
{
    return g_star_CoreFunctionTbl->SRPBasic_GetLastError(c_this);
}

VS_CHAR *Star_SRPBasic_GetLastErrorInfo(void *c_this,VS_UINT32 *LineIndex,VS_CHAR **SourceName)
{
    return g_star_CoreFunctionTbl->SRPBasic_GetLastErrorInfo(c_this,LineIndex,SourceName);
}

VS_CHAR *Star_SRPBasic_GetCorePath(void *c_this)
{
    return g_star_CoreFunctionTbl->SRPBasic_GetCorePath(c_this);
}

VS_CHAR *Star_SRPBasic_GetUserPath(void *c_this)
{
    return g_star_CoreFunctionTbl->SRPBasic_GetUserPath(c_this);
}

VS_CHAR *Star_SRPBasic_GetLocalIP(void *c_this)
{
    return g_star_CoreFunctionTbl->SRPBasic_GetLocalIP(c_this);
}

VS_INT32 Star_SRPBasic_GetLocalIPEx(void *c_this,SOCKADDR_IN *SockAddr,VS_INT32 ItemNumber)
{
    return g_star_CoreFunctionTbl->SRPBasic_GetLocalIPEx(c_this,SockAddr,ItemNumber);
}

void Star_SRPBasic_LuaPushInt64(void *c_this,VS_INT64 Value)
{
    g_star_CoreFunctionTbl->SRPBasic_LuaPushInt64(c_this,Value);
}

VS_INT64 Star_SRPBasic_LuaToInt64(void *c_this, VS_INT32 Index )
{
    return g_star_CoreFunctionTbl->SRPBasic_LuaToInt64(c_this,Index);
}

VS_BOOL Star_SRPBasic_LuaIsInt64(void *c_this, VS_INT32 Index )
{
    return g_star_CoreFunctionTbl->SRPBasic_LuaIsInt64(c_this,Index);
}

void Star_SRPBasic_LuaPushUWord(void *c_this,VS_UWORD Value)
{
    g_star_CoreFunctionTbl->SRPBasic_LuaPushUWord(c_this,Value);
}

VS_UWORD Star_SRPBasic_LuaToUWord(void *c_this,VS_INT32 Index )
{
    return g_star_CoreFunctionTbl->SRPBasic_LuaToUWord(c_this,Index);
}

VS_BOOL Star_SRPBasic_LuaIsUWord(void *c_this,VS_INT32 Index )
{
    return g_star_CoreFunctionTbl->SRPBasic_LuaIsUWord(c_this,Index);
}

VS_UINT32 Star_SRPBasic_GetObjectNum(void *c_this)
{
    return g_star_CoreFunctionTbl->SRPBasic_GetObjectNum(c_this);
}

void Star_SRPBinBuf_Release(void *c_this)
{
    g_star_CoreFunctionTbl->SRPBinBuf_Release(c_this);
}

void Star_SRPBinBuf_Init(void *c_this,VS_UINT32 BufSize)
{
    g_star_CoreFunctionTbl->SRPBinBuf_Init(c_this,BufSize);
}

VS_UINT32 Star_SRPBinBuf_GetSize(void *c_this)
{
    return g_star_CoreFunctionTbl->SRPBinBuf_GetSize(c_this);
}

VS_UINT32 Star_SRPBinBuf_GetOffset(void *c_this)
{
    return g_star_CoreFunctionTbl->SRPBinBuf_GetOffset(c_this);
}

VS_INT8 *Star_SRPBinBuf_GetBuf(void *c_this)
{
    return g_star_CoreFunctionTbl->SRPBinBuf_GetBuf(c_this);
}

void Star_SRPBinBuf_Clear(void *c_this)
{
    g_star_CoreFunctionTbl->SRPBinBuf_Clear(c_this);
}

void Star_SRPBinBuf_ClearEx(void *c_this, VS_UINT32 Offset, VS_UINT32 Length )
{
    g_star_CoreFunctionTbl->SRPBinBuf_ClearEx(c_this,Offset,Length);
}

VS_BOOL Star_SRPBinBuf_Set(void *c_this,VS_UINT32 Offset,VS_UINT32 Length,const VS_INT8 *Buf)
{
    return g_star_CoreFunctionTbl->SRPBinBuf_Set(c_this,Offset,Length,Buf);
}

VS_BOOL Star_SRPBinBuf_Get(void *c_this,VS_UINT32 Offset,VS_UINT32 Length,VS_INT8 *Buf)
{
    return g_star_CoreFunctionTbl->SRPBinBuf_Get(c_this,Offset,Length,Buf);
}

VS_INT8 *Star_SRPBinBuf_GetBufPtr(void *c_this,VS_UINT32 Offset)
{
    return g_star_CoreFunctionTbl->SRPBinBuf_GetBufPtr(c_this,Offset);
}

VS_INT8 *Star_SRPBinBuf_GetBufPtrEx(void *c_this,VS_UINT32 Offset,VS_UINT32 Length)
{
    return g_star_CoreFunctionTbl->SRPBinBuf_GetBufPtrEx(c_this,Offset,Length);
}

VS_BOOL Star_SRPBinBuf_SetOffset(void *c_this,VS_UINT32 Offset)
{
    return g_star_CoreFunctionTbl->SRPBinBuf_SetOffset(c_this,Offset);
}

VS_BOOL Star_SRPBinBuf_Fill(void *c_this,VS_UINT32 Offset,VS_UINT32 Length,VS_UINT8 Value)
{
    return g_star_CoreFunctionTbl->SRPBinBuf_Fill(c_this,Offset,Length,Value);
}

VS_BOOL Star_SRPBinBuf_Expand(void *c_this,VS_INT32 NewBufSize)
{
    return g_star_CoreFunctionTbl->SRPBinBuf_Expand(c_this,NewBufSize);
}

VS_BOOL Star_SRPBinBuf_PackObject(void *c_this,void *Object)
{
    return g_star_CoreFunctionTbl->SRPBinBuf_PackObject(c_this,Object);
}

VS_BOOL Star_SRPBinBuf_UnPackObject(void *c_this,void *Object)
{
    return g_star_CoreFunctionTbl->SRPBinBuf_UnPackObject(c_this,Object);
}

VS_BOOL Star_SRPBinBuf_ToUTF8(void *c_this)
{
    return g_star_CoreFunctionTbl->SRPBinBuf_ToUTF8(c_this);
}

VS_BOOL Star_SRPBinBuf_ToAnsi(void *c_this)
{
    return g_star_CoreFunctionTbl->SRPBinBuf_ToAnsi(c_this);
}

void *Star_SRPBinBuf_Dup(void *c_this)
{
    return g_star_CoreFunctionTbl->SRPBinBuf_Dup(c_this);
}

void Star_SRPBinBuf_Insert(void *c_this,VS_UINT32 Offset,VS_UINT32 Length,VS_INT8 *Buf)
{
    g_star_CoreFunctionTbl->SRPBinBuf_Insert(c_this,Offset,Length,Buf);
}

VS_INT32 Star_SRPBinBuf_FindStr(void *c_this,VS_UINT32 Offset,const VS_CHAR *Str)
{
    return g_star_CoreFunctionTbl->SRPBinBuf_FindStr(c_this,Offset,Str);
}

VS_INT32 Star_SRPBinBuf_FindStri(void *c_this,VS_UINT32 Offset,const VS_CHAR *Str)
{
    return g_star_CoreFunctionTbl->SRPBinBuf_FindStri(c_this,Offset,Str);
}

VS_BOOL Star_SRPBinBuf_SetLightBuf(void *c_this,VS_UINT32 Length,VS_INT8 *Buf)
{
    return g_star_CoreFunctionTbl->SRPBinBuf_SetLightBuf(c_this,Length,Buf);
}

VS_BOOL Star_SRPBinBuf_IsLightBuf(void *c_this)
{
    return g_star_CoreFunctionTbl->SRPBinBuf_IsLightBuf(c_this);
}

void Star_SRPBinBuf_AddRef(void *c_this)
{
    g_star_CoreFunctionTbl->SRPBinBuf_AddRef(c_this);
}

VS_INT32 Star_SRPBinBuf_GetRef(void *c_this)
{
    return g_star_CoreFunctionTbl->SRPBinBuf_GetRef(c_this);
}

VS_BOOL Star_SRPBinBuf_AnsiToUnicode(void *c_this,const VS_CHAR *Code,VS_INT32 BytesPerChar)
{
    return g_star_CoreFunctionTbl->SRPBinBuf_AnsiToUnicode(c_this,Code,BytesPerChar);
}

VS_BOOL Star_SRPBinBuf_UnicodeToAnsi(void *c_this,const VS_CHAR *Code,VS_INT32 BytesPerChar)
{
    return g_star_CoreFunctionTbl->SRPBinBuf_UnicodeToAnsi(c_this,Code,BytesPerChar);
}

VS_ULONG Star_SRPBinBuf_WriteFromMemoryFile(void *c_this,void *SRPInterface,VS_ULONG Offset,const VS_CHAR *FileName)
{
    return g_star_CoreFunctionTbl->SRPBinBuf_WriteFromMemoryFile(c_this,SRPInterface,Offset,FileName);
}

VS_INT8 *Star_SRPBinBuf_GetMD5(void *c_this)
{
    return g_star_CoreFunctionTbl->SRPBinBuf_GetMD5(c_this);
}

VS_ULONG Star_SRPBinBuf_GetHashValue(void *c_this)
{
    return g_star_CoreFunctionTbl->SRPBinBuf_GetHashValue(c_this);
}

void Star_SRPBinBuf_ReleaseOwner(void *c_this)
{
    g_star_CoreFunctionTbl->SRPBinBuf_ReleaseOwner(c_this);
}

void Star_SRPBinBuf_FromRaw(void *c_this,VS_BOOL In_FromBytesArray)
{
    g_star_CoreFunctionTbl->SRPBinBuf_FromRaw(c_this,In_FromBytesArray);
}

VS_BOOL Star_SRPBinBuf_IsFromRaw(void *c_this)
{
    return g_star_CoreFunctionTbl->SRPBinBuf_IsFromRaw(c_this);
}

void Star_SRPParaPkg_Release(void *c_this)
{
    g_star_CoreFunctionTbl->SRPParaPkg_Release(c_this);
}

VS_INT32 Star_SRPParaPkg_GetNumber(void *c_this)
{
    return g_star_CoreFunctionTbl->SRPParaPkg_GetNumber(c_this);
}

void Star_SRPParaPkg_Clear(void *c_this)
{
    g_star_CoreFunctionTbl->SRPParaPkg_Clear(c_this);
}

VS_BOOL Star_SRPParaPkg_InsertInt(void *c_this,VS_INT32 Index,VS_INT32 Para)
{
    return g_star_CoreFunctionTbl->SRPParaPkg_InsertInt(c_this,Index,Para);
}

VS_BOOL Star_SRPParaPkg_InsertFloat(void *c_this,VS_INT32 Index,VS_DOUBLE Para)
{
    return g_star_CoreFunctionTbl->SRPParaPkg_InsertFloat(c_this,Index,Para);
}

VS_BOOL Star_SRPParaPkg_InsertStr(void *c_this,VS_INT32 Index,const VS_CHAR *Para)
{
    return g_star_CoreFunctionTbl->SRPParaPkg_InsertStr(c_this,Index,Para);
}

VS_BOOL Star_SRPParaPkg_InsertBin(void *c_this,VS_INT32 Index,VS_INT8 *Para,VS_INT32 Size)
{
    return g_star_CoreFunctionTbl->SRPParaPkg_InsertBin(c_this,Index,Para,Size);
}

VS_BOOL Star_SRPParaPkg_InsertTime(void *c_this,VS_INT32 Index,VS_TIME *hTime)
{
    return g_star_CoreFunctionTbl->SRPParaPkg_InsertTime(c_this,Index,hTime);
}

VS_BOOL Star_SRPParaPkg_InsertEmpty(void *c_this,VS_INT32 Index)
{
    return g_star_CoreFunctionTbl->SRPParaPkg_InsertEmpty(c_this,Index);
}

VS_BOOL Star_SRPParaPkg_ExChange(void *c_this,VS_INT32 DesIndex,VS_INT32 SrcIndex)
{
    return g_star_CoreFunctionTbl->SRPParaPkg_ExChange(c_this,DesIndex,SrcIndex);
}

void Star_SRPParaPkg_Del(void *c_this,VS_INT32 Index)
{
    g_star_CoreFunctionTbl->SRPParaPkg_Del(c_this,Index);
}

VS_INT32 Star_SRPParaPkg_GetType(void *c_this,VS_INT32 Index)
{
    return g_star_CoreFunctionTbl->SRPParaPkg_GetType(c_this,Index);
}

VS_INT32 Star_SRPParaPkg_GetInt(void *c_this,VS_INT32 Index)
{
    return g_star_CoreFunctionTbl->SRPParaPkg_GetInt(c_this,Index);
}

VS_DOUBLE Star_SRPParaPkg_GetFloat(void *c_this,VS_INT32 Index)
{
    return g_star_CoreFunctionTbl->SRPParaPkg_GetFloat(c_this,Index);
}

VS_CHAR *Star_SRPParaPkg_GetStr(void *c_this,VS_INT32 Index)
{
    return g_star_CoreFunctionTbl->SRPParaPkg_GetStr(c_this,Index);
}

VS_INT8 *Star_SRPParaPkg_GetBin(void *c_this,VS_INT32 Index,VS_INT32 *Length)
{
    return g_star_CoreFunctionTbl->SRPParaPkg_GetBin(c_this,Index,Length);
}

VS_BOOL Star_SRPParaPkg_GetTime(void *c_this,VS_INT32 Index,VS_TIME *hTime)
{
    return g_star_CoreFunctionTbl->SRPParaPkg_GetTime(c_this,Index,hTime);
}

void *Star_SRPParaPkg_Dup(void *c_this)
{
    return g_star_CoreFunctionTbl->SRPParaPkg_Dup(c_this);
}

VS_BOOL Star_SRPParaPkg_AppendFrom(void *c_this,void *ParaPkg)
{
    return g_star_CoreFunctionTbl->SRPParaPkg_AppendFrom(c_this,ParaPkg);
}

void Star_SRPParaPkg_SetChangeFlag(void *c_this,VS_INT32 Index)
{
    g_star_CoreFunctionTbl->SRPParaPkg_SetChangeFlag(c_this,Index);
}

void Star_SRPParaPkg_ClearChangeFlag(void *c_this,VS_INT32 Index)
{
    g_star_CoreFunctionTbl->SRPParaPkg_ClearChangeFlag(c_this,Index);
}

void Star_SRPParaPkg_SetChangeFlagEx(void *c_this)
{
    g_star_CoreFunctionTbl->SRPParaPkg_SetChangeFlagEx(c_this);
}

void Star_SRPParaPkg_ClearChangeFlagEx(void *c_this)
{
    g_star_CoreFunctionTbl->SRPParaPkg_ClearChangeFlagEx(c_this);
}

VS_BOOL Star_SRPParaPkg_IsChangeFlag(void *c_this,VS_INT32 Index)
{
    return g_star_CoreFunctionTbl->SRPParaPkg_IsChangeFlag(c_this,Index);
}

VS_BOOL Star_SRPParaPkg_IsChangeFlagEx(void *c_this)
{
    return g_star_CoreFunctionTbl->SRPParaPkg_IsChangeFlagEx(c_this);
}

VS_INT8 *Star_SRPParaPkg_SaveChangeToBuf(void *c_this, VS_BOOL CompressFlag,VS_INT32 *RetSize )
{
    return g_star_CoreFunctionTbl->SRPParaPkg_SaveChangeToBuf(c_this,CompressFlag,RetSize);
}

VS_INT8 *Star_SRPParaPkg_SaveChangeToBufEx(void *c_this, VS_BOOL CompressFlag,VS_INT32 *RetSize )
{
    return g_star_CoreFunctionTbl->SRPParaPkg_SaveChangeToBufEx(c_this,CompressFlag,RetSize);
}

VS_BOOL Star_SRPParaPkg_LoadChangeFromBuf(void *c_this, VS_INT32 BufSize, VS_INT8 *Buf )
{
    return g_star_CoreFunctionTbl->SRPParaPkg_LoadChangeFromBuf(c_this,BufSize,Buf);
}

void Star_SRPParaPkg_FreeBuf(void *c_this, VS_INT8 *Buf )
{
    g_star_CoreFunctionTbl->SRPParaPkg_FreeBuf(c_this,Buf);
}

void Star_SRPParaPkg_AddRef(void *c_this)
{
    g_star_CoreFunctionTbl->SRPParaPkg_AddRef(c_this);
}

VS_INT32 Star_SRPParaPkg_GetRef(void *c_this)
{
    return g_star_CoreFunctionTbl->SRPParaPkg_GetRef(c_this);
}

VS_BOOL Star_SRPParaPkg_InsertBool(void *c_this,VS_INT32 Index,VS_BOOL Para)
{
    return g_star_CoreFunctionTbl->SRPParaPkg_InsertBool(c_this,Index,Para);
}

VS_BOOL Star_SRPParaPkg_GetBool(void *c_this,VS_INT32 Index)
{
    return g_star_CoreFunctionTbl->SRPParaPkg_GetBool(c_this,Index);
}

VS_BOOL Star_SRPParaPkg_InsertObject(void *c_this,VS_INT32 Index,void *Object)
{
    return g_star_CoreFunctionTbl->SRPParaPkg_InsertObject(c_this,Index,Object);
}

void *Star_SRPParaPkg_GetObject(void *c_this,VS_INT32 Index)
{
    return g_star_CoreFunctionTbl->SRPParaPkg_GetObject(c_this,Index);
}

VS_BOOL Star_SRPParaPkg_InsertParaPackage(void *c_this,VS_INT32 Index,void *ParaPkg)
{
    return g_star_CoreFunctionTbl->SRPParaPkg_InsertParaPackage(c_this,Index,ParaPkg);
}

void *Star_SRPParaPkg_GetParaPackage(void *c_this,VS_INT32 Index)
{
    return g_star_CoreFunctionTbl->SRPParaPkg_GetParaPackage(c_this,Index);
}

VS_UINT32 Star_SRPParaPkg_GetMaxSize(void *c_this)
{
    return g_star_CoreFunctionTbl->SRPParaPkg_GetMaxSize(c_this);
}

void Star_SRPParaPkg_SetScriptRawType(void *c_this,VS_INT32 RawType)
{
    g_star_CoreFunctionTbl->SRPParaPkg_SetScriptRawType(c_this,RawType);
}

VS_INT32 Star_SRPParaPkg_GetScriptRawType(void *c_this)
{
    return g_star_CoreFunctionTbl->SRPParaPkg_GetScriptRawType(c_this);
}

void Star_SRPParaPkg_ReleaseOwner(void *c_this)
{
    g_star_CoreFunctionTbl->SRPParaPkg_ReleaseOwner(c_this);
}

void Star_SRPParaPkg_AttachArrayObject(void *c_this,void *Object,const VS_CHAR *VarName,VS_INT32 StartIndexOfArray)
{
    g_star_CoreFunctionTbl->SRPParaPkg_AttachArrayObject(c_this,Object,VarName,StartIndexOfArray);
}

void *Star_SRPParaPkg_BuildVar(void *c_this,const VS_CHAR *TypeSet,va_list argList)
{
    return g_star_CoreFunctionTbl->SRPParaPkg_BuildVar(c_this,TypeSet,argList);
}

void *Star_SRPParaPkg_AsDict(void *c_this,VS_BOOL IsDict)
{
    return g_star_CoreFunctionTbl->SRPParaPkg_AsDict(c_this,IsDict);
}

VS_BOOL Star_SRPParaPkg_IsDict(void *c_this)
{
    return g_star_CoreFunctionTbl->SRPParaPkg_IsDict(c_this);
}

VS_INT32 Star_SRPParaPkg_FindDict(void *c_this,const VS_CHAR *Key)
{
    return g_star_CoreFunctionTbl->SRPParaPkg_FindDict(c_this,Key);
}

VS_INT32 Star_SRPParaPkg_FindDictEx(void *c_this,VS_INT32 Key)
{
    return g_star_CoreFunctionTbl->SRPParaPkg_FindDictEx(c_this,Key);
}

VS_BOOL Star_SRPParaPkg_FromJSon(void *c_this,const VS_CHAR *Buf)
{
    return g_star_CoreFunctionTbl->SRPParaPkg_FromJSon(c_this,Buf);
}

VS_CHAR *Star_SRPParaPkg_ToJSon(void *c_this)
{
    return g_star_CoreFunctionTbl->SRPParaPkg_ToJSon(c_this);
}

VS_BOOL Star_SRPParaPkg_InsertInt64(void *c_this,VS_INT32 Index,VS_INT64 Para)
{
    return g_star_CoreFunctionTbl->SRPParaPkg_InsertInt64(c_this,Index,Para);
}

VS_INT64 Star_SRPParaPkg_GetInt64(void *c_this,VS_INT32 Index)
{
    return g_star_CoreFunctionTbl->SRPParaPkg_GetInt64(c_this,Index);
}

VS_BOOL Star_SRPParaPkg_InsertStrEx(void *c_this,VS_INT32 Index,const VS_CHAR *Para,VS_UINT32 ParaLength)
{
    return g_star_CoreFunctionTbl->SRPParaPkg_InsertStrEx(c_this,Index,Para,ParaLength);
}

VS_CHAR *Star_SRPParaPkg_GetStrEx(void *c_this,VS_INT32 Index,VS_UINT32 *ParaLength)
{
    return g_star_CoreFunctionTbl->SRPParaPkg_GetStrEx(c_this,Index,ParaLength);
}

VS_BOOL Star_SRPParaPkg_InsertBinEx(void *c_this,VS_INT32 Index,VS_INT8 *Para,VS_INT32 Size,VS_BOOL FromBytesArray)
{
    return g_star_CoreFunctionTbl->SRPParaPkg_InsertBinEx(c_this,Index,Para,Size,FromBytesArray);
}

VS_INT8 *Star_SRPParaPkg_GetBinEx(void *c_this,VS_INT32 Index,VS_INT32 *Length,VS_BOOL *FromBytesArray)
{
    return g_star_CoreFunctionTbl->SRPParaPkg_GetBinEx(c_this,Index,Length,FromBytesArray);
}

void Star_SRPI_Release(void *c_this)
{
    g_star_CoreFunctionTbl->SRPI_Release(c_this);
}

VS_INT32 Star_SRPI_GetObjectRegisterInfo(void *c_this,VS_UUID ObjectID,VS_INT8 *InBuf,VS_INT32 InBufLength,VS_INT8 *OutBuf,VS_INT32 OutBufSize)
{
    return g_star_CoreFunctionTbl->SRPI_GetObjectRegisterInfo(c_this,ObjectID,InBuf,InBufLength,OutBuf,OutBufSize);
}

void Star_SRPI_RegisterObjectDependency(void *c_this,VS_UUID ModuleID,VS_UUID ObjectID,VS_INT32 DependIndex,VS_UUID DependObjectID,VS_INT32 DependType,VS_INT32 DependItemNumber,VS_DEPENDATTRIBUTE *DependItemList)
{
    g_star_CoreFunctionTbl->SRPI_RegisterObjectDependency(c_this,ModuleID,ObjectID,DependIndex,DependObjectID,DependType,DependItemNumber,DependItemList);
}

void Star_SRPI_RegisterObjectFunction(void *c_this,VS_UUID ModuleID,VS_UUID ObjectID,VS_UUID FunctionID,void *CallBackPtr,VS_INT32 DependIndexNumber,VS_INT32 *DependIndex)
{
    g_star_CoreFunctionTbl->SRPI_RegisterObjectFunction(c_this,ModuleID,ObjectID,FunctionID,CallBackPtr,DependIndexNumber,DependIndex);
}

void Star_SRPI_RegisterObjectSysEvent(void *c_this,VS_UUID ModuleID,VS_UUID ObjectID,void *CallBackPtr,VS_INT32 DependIndexNumber,VS_INT32 *DependIndex)
{
    g_star_CoreFunctionTbl->SRPI_RegisterObjectSysEvent(c_this,ModuleID,ObjectID,CallBackPtr,DependIndexNumber,DependIndex);
}

void Star_SRPI_RegisterObjectSysEditEvent(void *c_this,VS_UUID ModuleID,VS_UUID ObjectID,void *CallBackPtr,VS_INT32 DependIndexNumber,VS_INT32 *DependIndex)
{
    g_star_CoreFunctionTbl->SRPI_RegisterObjectSysEditEvent(c_this,ModuleID,ObjectID,CallBackPtr,DependIndexNumber,DependIndex);
}

void Star_SRPI_RegisterObjectInEvent(void *c_this,VS_UUID ModuleID,VS_UUID ObjectID,VS_UUID InEventID,void *CallBackPtr,VS_INT32 DependIndexNumber,VS_INT32 *DependIndex)
{
    g_star_CoreFunctionTbl->SRPI_RegisterObjectInEvent(c_this,ModuleID,ObjectID,InEventID,CallBackPtr,DependIndexNumber,DependIndex);
}

void Star_SRPI_RegisterQueryObjectInfo(void *c_this,VS_UUID ModuleID,VS_UUID ObjectID,void *CallBackPtr)
{
    g_star_CoreFunctionTbl->SRPI_RegisterQueryObjectInfo(c_this,ModuleID,ObjectID,CallBackPtr);
}

VS_INT32 Star_SRPI_RegisterDynamicModule(void *c_this, VS_UUID ModuleID, VSModuleFunction_ModuleInitProc ModuleInitProc, VSModuleFunction_ModuleTermProc ModuleTermProc, VSModuleFunction_RequestRegisterObjectProc RequestRegisterObjectProc)
{
    return g_star_CoreFunctionTbl->SRPI_RegisterDynamicModule(c_this,ModuleID,ModuleInitProc,ModuleTermProc,RequestRegisterObjectProc);
}

VS_UINT32 Star_SRPI_GetOsType(void *c_this)
{
    return g_star_CoreFunctionTbl->SRPI_GetOsType(c_this);
}

VS_BOOL Star_SRPI_StringToUuid(void *c_this,const VS_INT8 *String,VS_UUID *Uuid)
{
    return g_star_CoreFunctionTbl->SRPI_StringToUuid(c_this,String,Uuid);
}

VS_INT8 *Star_SRPI_UuidToString(void *c_this,VS_UUID *Uuid)
{
    return g_star_CoreFunctionTbl->SRPI_UuidToString(c_this,Uuid);
}

void *Star_SRPI_GetParent(void *c_this,void *Object)
{
    return g_star_CoreFunctionTbl->SRPI_GetParent(c_this,Object);
}

OBJECTATTRIBUTEINDEX Star_SRPI_GetIndex(void *c_this,void *Object)
{
    return g_star_CoreFunctionTbl->SRPI_GetIndex(c_this,Object);
}

VS_UINT16 Star_SRPI_GetOrder(void *c_this,void *Object)
{
    return g_star_CoreFunctionTbl->SRPI_GetOrder(c_this,Object);
}

void *Star_SRPI_GetClass(void *c_this,void *Object)
{
    return g_star_CoreFunctionTbl->SRPI_GetClass(c_this,Object);
}

void Star_SRPI_GetClassID(void *c_this,void *Object,VS_UUID *UuidPtr)
{
    g_star_CoreFunctionTbl->SRPI_GetClassID(c_this,Object,UuidPtr);
}

void Star_SRPI_GetID(void *c_this,void *Object,VS_UUID *UuidPtr)
{
    g_star_CoreFunctionTbl->SRPI_GetID(c_this,Object,UuidPtr);
}

void *Star_SRPI_GetObject(void *c_this,VS_UUID *ObjectID)
{
    return g_star_CoreFunctionTbl->SRPI_GetObject(c_this,ObjectID);
}

void *Star_SRPI_GetObjectEx(void *c_this,void *ParentObject,const VS_CHAR *Name)
{
    return g_star_CoreFunctionTbl->SRPI_GetObjectEx(c_this,ParentObject,Name);
}

void *Star_SRPI_GetObjectEx2(void *c_this,const VS_CHAR *ServiceName,const VS_CHAR *Name)
{
    return g_star_CoreFunctionTbl->SRPI_GetObjectEx2(c_this,ServiceName,Name);
}

void *Star_SRPI_GetSRPObject(void *c_this,VS_UUID *ObjectID)
{
    return g_star_CoreFunctionTbl->SRPI_GetSRPObject(c_this,ObjectID);
}

void *Star_SRPI_GetSRPObjectEx(void *c_this,void *ParentObject,const VS_CHAR *Name)
{
    return g_star_CoreFunctionTbl->SRPI_GetSRPObjectEx(c_this,ParentObject,Name);
}

void *Star_SRPI_GetPrevEx(void *c_this,void *Object)
{
    return g_star_CoreFunctionTbl->SRPI_GetPrevEx(c_this,Object);
}

void *Star_SRPI_GetNextEx(void *c_this,void *Object)
{
    return g_star_CoreFunctionTbl->SRPI_GetNextEx(c_this,Object);
}

void *Star_SRPI_QueryFirst(void *c_this,void *VSObject)
{
    return g_star_CoreFunctionTbl->SRPI_QueryFirst(c_this,VSObject);
}

void *Star_SRPI_QueryFirstChild(void *c_this,void *Object,OBJECTATTRIBUTEINDEX AttributeIndex)
{
    return g_star_CoreFunctionTbl->SRPI_QueryFirstChild(c_this,Object,AttributeIndex);
}

void *Star_SRPI_QueryNext(void *c_this,void *Object)
{
    return g_star_CoreFunctionTbl->SRPI_QueryNext(c_this,Object);
}

void *Star_SRPI_QueryPrev(void *c_this,void *Object)
{
    return g_star_CoreFunctionTbl->SRPI_QueryPrev(c_this,Object);
}

void *Star_SRPI_QueryFirstEx(void *c_this,VS_QUERYRECORD *QueryRecord)
{
    return g_star_CoreFunctionTbl->SRPI_QueryFirstEx(c_this,QueryRecord);
}

void *Star_SRPI_QueryNextEx(void *c_this,VS_QUERYRECORD *QueryRecord)
{
    return g_star_CoreFunctionTbl->SRPI_QueryNextEx(c_this,QueryRecord);
}

VS_BOOL Star_SRPI_IsObject(void *c_this,void *Object)
{
    return g_star_CoreFunctionTbl->SRPI_IsObject(c_this,Object);
}

void *Star_SRPI_QueryFirstActiveChild(void *c_this,void *Object,VS_UWORD *Context)
{
    return g_star_CoreFunctionTbl->SRPI_QueryFirstActiveChild(c_this,Object,Context);
}

void *Star_SRPI_QueryNextActiveChild(void *c_this,VS_UWORD *Context)
{
    return g_star_CoreFunctionTbl->SRPI_QueryNextActiveChild(c_this,Context);
}

VS_BOOL Star_SRPI_IsObjectInActiveSet(void *c_this,void *Object)
{
    return g_star_CoreFunctionTbl->SRPI_IsObjectInActiveSet(c_this,Object);
}

VS_BOOL Star_SRPI_GetWebServiceFlag(void *c_this,void *Object)
{
    return g_star_CoreFunctionTbl->SRPI_GetWebServiceFlag(c_this,Object);
}

VS_BOOL Star_SRPI_SetWebServiceFlag(void *c_this,void *Object,VS_BOOL WebServiceFlag)
{
    return g_star_CoreFunctionTbl->SRPI_SetWebServiceFlag(c_this,Object,WebServiceFlag);
}

void *Star_SRPI_QueryFirstInst(void *c_this,VS_QUERYRECORD *QueryRecord,void *ClassObject)
{
    return g_star_CoreFunctionTbl->SRPI_QueryFirstInst(c_this,QueryRecord,ClassObject);
}

void *Star_SRPI_QueryNextInst(void *c_this,VS_QUERYRECORD *QueryRecord,void *ClassObject)
{
    return g_star_CoreFunctionTbl->SRPI_QueryNextInst(c_this,QueryRecord,ClassObject);
}

void *Star_SRPI_QueryFirstInstEx(void *c_this,VS_QUERYRECORD *QueryRecord,VS_UUID *ObjectClassID)
{
    return g_star_CoreFunctionTbl->SRPI_QueryFirstInstEx(c_this,QueryRecord,ObjectClassID);
}

void *Star_SRPI_QueryNextInstEx(void *c_this,VS_QUERYRECORD *QueryRecord,VS_UUID *ObjectClassID)
{
    return g_star_CoreFunctionTbl->SRPI_QueryNextInstEx(c_this,QueryRecord,ObjectClassID);
}

void Star_SRPI_QueryInstClose(void *c_this,VS_QUERYRECORD *QueryRecord)
{
    g_star_CoreFunctionTbl->SRPI_QueryInstClose(c_this,QueryRecord);
}

VS_CHAR *Star_SRPI_GetName(void *c_this,void *Object)
{
    return g_star_CoreFunctionTbl->SRPI_GetName(c_this,Object);
}

void Star_SRPI_SetName(void *c_this,void *Object,const VS_CHAR *Name)
{
    g_star_CoreFunctionTbl->SRPI_SetName(c_this,Object,Name);
}

VS_BOOL Star_SRPI_IsInst(void *c_this,VS_UUID *ObjectClassID,void *Object)
{
    return g_star_CoreFunctionTbl->SRPI_IsInst(c_this,ObjectClassID,Object);
}

VS_BOOL Star_SRPI_IsDirectInst(void *c_this,VS_UUID *ObjectClassID,void *Object)
{
    return g_star_CoreFunctionTbl->SRPI_IsDirectInst(c_this,ObjectClassID,Object);
}

VS_BOOL Star_SRPI_IsChild(void *c_this,void *ParentObject,void *Object)
{
    return g_star_CoreFunctionTbl->SRPI_IsChild(c_this,ParentObject,Object);
}

void Star_SRPI_GetObjectSysRootItemID(void *c_this,void *Object,VS_UUID *UuidPtr)
{
    g_star_CoreFunctionTbl->SRPI_GetObjectSysRootItemID(c_this,Object,UuidPtr);
}

void *Star_SRPI_GetObjectSysRootItem(void *c_this,void *Object)
{
    return g_star_CoreFunctionTbl->SRPI_GetObjectSysRootItem(c_this,Object);
}

VS_BOOL Star_SRPI_IsThisService(void *c_this,void *Object)
{
    return g_star_CoreFunctionTbl->SRPI_IsThisService(c_this,Object);
}

VS_BOOL Star_SRPI_IsActiveServiceObject(void *c_this,void *Object)
{
    return g_star_CoreFunctionTbl->SRPI_IsActiveServiceObject(c_this,Object);
}

VS_BOOL Star_SRPI_IsThisClient(void *c_this,void *Object)
{
    return g_star_CoreFunctionTbl->SRPI_IsThisClient(c_this,Object);
}

VS_ULONG Star_SRPI_GetClientID(void *c_this,void *Object)
{
    return g_star_CoreFunctionTbl->SRPI_GetClientID(c_this,Object);
}

VS_BOOL Star_SRPI_ExportObjectHeader(void *c_this, void *Object, const VS_CHAR *FileName )
{
    return g_star_CoreFunctionTbl->SRPI_ExportObjectHeader(c_this,Object,FileName);
}

void Star_SRPI_SetSaveFlag(void *c_this,void *Object,VS_UINT8 SaveFlag)
{
    g_star_CoreFunctionTbl->SRPI_SetSaveFlag(c_this,Object,SaveFlag);
}

VS_UINT8 Star_SRPI_GetSaveFlag(void *c_this,void *Object)
{
    return g_star_CoreFunctionTbl->SRPI_GetSaveFlag(c_this,Object);
}

VS_INT8 *Star_SRPI_SaveToBuf(void *c_this, void *Object, VS_INT32 *ObjectSize, const VS_CHAR *Password, VS_UINT8 SaveFlag, VS_BOOL SaveNameValue )
{
    return g_star_CoreFunctionTbl->SRPI_SaveToBuf(c_this,Object,ObjectSize,Password,SaveFlag,SaveNameValue);
}

VS_BOOL Star_SRPI_SaveToFile(void *c_this, void *Object, const VS_CHAR *FileName, const VS_CHAR *Password, VS_UINT8 SaveFlag, VS_BOOL SaveNameValue )
{
    return g_star_CoreFunctionTbl->SRPI_SaveToFile(c_this,Object,FileName,Password,SaveFlag,SaveNameValue);
}

VS_BOOL Star_SRPI_LoadFromBuf(void *c_this, void *Object, const VS_INT8 *Buf, VS_INT32 BufSize, const VS_CHAR *Password, VS_BOOL LoadAsLocal,VS_BOOL LoadNameValue,VS_BOOL UpdateFlag )
{
    return g_star_CoreFunctionTbl->SRPI_LoadFromBuf(c_this,Object,Buf,BufSize,Password,LoadAsLocal,LoadNameValue,UpdateFlag);
}

void Star_SRPI_DeferLoadFromBuf(void *c_this, void *Object, const VS_INT8 *Buf, VS_INT32 BufSize, const VS_CHAR *Password, VS_BOOL LoadAsLocal,VS_BOOL LoadNameValue,VS_BOOL UpdateFlag )
{
    g_star_CoreFunctionTbl->SRPI_DeferLoadFromBuf(c_this,Object,Buf,BufSize,Password,LoadAsLocal,LoadNameValue,UpdateFlag);
}

VS_BOOL Star_SRPI_LoadFromFile(void *c_this, void *Object, const VS_CHAR *FileName, const VS_CHAR *Password, VS_BOOL LoadAsLocal,VS_BOOL LoadNameValue,VS_BOOL UpdateFlag, VS_BOOL StaticDataUseFile )
{
    return g_star_CoreFunctionTbl->SRPI_LoadFromFile(c_this,Object,FileName,Password,LoadAsLocal,LoadNameValue,UpdateFlag,StaticDataUseFile);
}

void Star_SRPI_DeferLoadFromFile(void *c_this, void *Object, const VS_CHAR *FileName, const VS_CHAR *Password, VS_BOOL LoadAsLocal,VS_BOOL LoadNameValue,VS_BOOL UpdateFlag, VS_BOOL StaticDataUseFile )
{
    g_star_CoreFunctionTbl->SRPI_DeferLoadFromFile(c_this,Object,FileName,Password,LoadAsLocal,LoadNameValue,UpdateFlag,StaticDataUseFile);
}

void Star_SRPI_ResetLoad(void *c_this, void *Object )
{
    g_star_CoreFunctionTbl->SRPI_ResetLoad(c_this,Object);
}

void Star_SRPI_RegLoadMapAttrNameProc(void *c_this, VS_LoadMapAttrNameProc LoadMapAttrNameProc )
{
    g_star_CoreFunctionTbl->SRPI_RegLoadMapAttrNameProc(c_this,LoadMapAttrNameProc);
}

VS_BOOL Star_SRPI_IsLocalControl(void *c_this, void *Object )
{
    return g_star_CoreFunctionTbl->SRPI_IsLocalControl(c_this,Object);
}

VS_BOOL Star_SRPI_IsRemoteCreate(void *c_this, void *Object )
{
    return g_star_CoreFunctionTbl->SRPI_IsRemoteCreate(c_this,Object);
}

void Star_SRPI_SetIDInParent(void *c_this, void *Object,VS_UINT16 IDInParent )
{
    g_star_CoreFunctionTbl->SRPI_SetIDInParent(c_this,Object,IDInParent);
}

VS_UINT16 Star_SRPI_GetIDInParent(void *c_this, void *Object )
{
    return g_star_CoreFunctionTbl->SRPI_GetIDInParent(c_this,Object);
}

void *Star_SRPI_GetChildByID(void *c_this, void *Object,OBJECTATTRIBUTEINDEX AttributeIndex,VS_UINT16 IDInParent )
{
    return g_star_CoreFunctionTbl->SRPI_GetChildByID(c_this,Object,AttributeIndex,IDInParent);
}

VS_BOOL Star_SRPI_GetFunctionID(void *c_this,void *Object,const VS_CHAR *FuntionName,VS_UUID *FunctionID)
{
    return g_star_CoreFunctionTbl->SRPI_GetFunctionID(c_this,Object,FuntionName,FunctionID);
}

VS_BOOL Star_SRPI_GetInEventID(void *c_this,void *Object,const VS_CHAR *InEventName,VS_UUID *InEventID)
{
    return g_star_CoreFunctionTbl->SRPI_GetInEventID(c_this,Object,InEventName,InEventID);
}

VS_BOOL Star_SRPI_GetOutEventID(void *c_this,void *Object,const VS_CHAR *OutEventName,VS_UUID *OutEventID)
{
    return g_star_CoreFunctionTbl->SRPI_GetOutEventID(c_this,Object,OutEventName,OutEventID);
}

VS_CHAR *Star_SRPI_GetOutEventName(void *c_this,VS_UUID *OutEventID)
{
    return g_star_CoreFunctionTbl->SRPI_GetOutEventName(c_this,OutEventID);
}

void *Star_SRPI_GetFunction(void *c_this,VS_UUID *FunctionID,VS_BOOL *GlobalFunctionFlag)
{
    return g_star_CoreFunctionTbl->SRPI_GetFunction(c_this,FunctionID,GlobalFunctionFlag);
}

void *Star_SRPI_GetFunctionEx(void *c_this,void *Object,VS_UUID *FunctionID,VS_BOOL *GlobalFunctionFlag)
{
    return g_star_CoreFunctionTbl->SRPI_GetFunctionEx(c_this,Object,FunctionID,GlobalFunctionFlag);
}

void *Star_SRPI_GetOriFunction(void *c_this,VS_UUID *FunctionID,VS_BOOL *GlobalFunctionFlag)
{
    return g_star_CoreFunctionTbl->SRPI_GetOriFunction(c_this,FunctionID,GlobalFunctionFlag);
}

void Star_SRPI_SetFunction(void *c_this,VS_UUID *FunctionID,void *FuncAddress)
{
    g_star_CoreFunctionTbl->SRPI_SetFunction(c_this,FunctionID,FuncAddress);
}

void Star_SRPI_SetInEvent(void *c_this,VS_UUID *InEventID,void *InEventAddress)
{
    g_star_CoreFunctionTbl->SRPI_SetInEvent(c_this,InEventID,InEventAddress);
}

void *Star_SRPI_GetSysEvent(void *c_this,void *Object, VS_UWORD *Para)
{
    return g_star_CoreFunctionTbl->SRPI_GetSysEvent(c_this,Object,Para);
}

void Star_SRPI_SetSysEvent(void *c_this,void *Object,void *SysEventAddress, VS_UWORD Para)
{
    g_star_CoreFunctionTbl->SRPI_SetSysEvent(c_this,Object,SysEventAddress,Para);
}

void Star_SRPI_SetSysEventMask(void *c_this,void *Object,VS_ULONG EventMask, VSSystemEvent_EventProc EventProc)
{
    g_star_CoreFunctionTbl->SRPI_SetSysEventMask(c_this,Object,EventMask,EventProc);
}

VS_ULONG Star_SRPI_GetSysEventMask(void *c_this,void *Object, VSSystemEvent_EventProc EventProc )
{
    return g_star_CoreFunctionTbl->SRPI_GetSysEventMask(c_this,Object,EventProc);
}

void Star_SRPI_SetChildEventMask(void *c_this,void *Object,VS_ULONG ClassLayer,VS_ULONG EventMask )
{
    g_star_CoreFunctionTbl->SRPI_SetChildEventMask(c_this,Object,ClassLayer,EventMask);
}

VS_ULONG Star_SRPI_GetChildEventMask(void *c_this,void *Object,VS_ULONG ClassLayer )
{
    return g_star_CoreFunctionTbl->SRPI_GetChildEventMask(c_this,Object,ClassLayer);
}

VS_BOOL Star_SRPI_CreateOVLFunction(void *c_this,void *Object,VS_UUID *OriginFunctionID,void *FuncAddress,VS_UUID *NewFunctionID)
{
    return g_star_CoreFunctionTbl->SRPI_CreateOVLFunction(c_this,Object,OriginFunctionID,FuncAddress,NewFunctionID);
}

VS_BOOL Star_SRPI_CreateOVLInEvent(void *c_this,void *Object,VS_UUID *OutEventID,void *InEventAddress,VS_UUID *NewInEventID)
{
    return g_star_CoreFunctionTbl->SRPI_CreateOVLInEvent(c_this,Object,OutEventID,InEventAddress,NewInEventID);
}

VS_ULONG Star_SRPI_EventIDToDWORD(void *c_this,VS_UUID *OutEventID)
{
    return g_star_CoreFunctionTbl->SRPI_EventIDToDWORD(c_this,OutEventID);
}

VS_ULONG Star_SRPI_EventNameToDWORD(void *c_this,VS_UUID *OutEventID)
{
    return g_star_CoreFunctionTbl->SRPI_EventNameToDWORD(c_this,OutEventID);
}

VS_BOOL Star_SRPI_CreateNameScript(void *c_this, void *Object, const VS_CHAR *ScriptName,const VS_CHAR *ScriptBuf )
{
    return g_star_CoreFunctionTbl->SRPI_CreateNameScript(c_this,Object,ScriptName,ScriptBuf);
}

VS_BOOL Star_SRPI_CreateNameScriptEx(void *c_this, void *Object, const VS_CHAR *ScriptName,const VS_CHAR *FileName )
{
    return g_star_CoreFunctionTbl->SRPI_CreateNameScriptEx(c_this,Object,ScriptName,FileName);
}

void Star_SRPI_DeleteNameScript(void *c_this, void *Object, const VS_CHAR *ScriptName )
{
    g_star_CoreFunctionTbl->SRPI_DeleteNameScript(c_this,Object,ScriptName);
}

void Star_SRPI_ChangeScriptName(void *c_this, void *Object, const VS_CHAR *ScriptName, const VS_CHAR *NewScriptName)
{
    g_star_CoreFunctionTbl->SRPI_ChangeScriptName(c_this,Object,ScriptName,NewScriptName);
}

VS_CHAR *Star_SRPI_GetNameScript(void *c_this, void *Object, const VS_CHAR *ScriptName)
{
    return g_star_CoreFunctionTbl->SRPI_GetNameScript(c_this,Object,ScriptName);
}

VS_CHAR *Star_SRPI_QueryFirstNameScript(void *c_this, void *Object,VS_CHAR **ScriptPtr )
{
    return g_star_CoreFunctionTbl->SRPI_QueryFirstNameScript(c_this,Object,ScriptPtr);
}

VS_CHAR *Star_SRPI_QueryNextNameScript(void *c_this, VS_CHAR **ScriptPtr )
{
    return g_star_CoreFunctionTbl->SRPI_QueryNextNameScript(c_this,ScriptPtr);
}

VS_BOOL Star_SRPI_ExecNameScript(void *c_this, void *Object, const VS_CHAR *ScriptName, VS_INT32 nArgs,VS_INT32 nOutArgs )
{
    return g_star_CoreFunctionTbl->SRPI_ExecNameScript(c_this,Object,ScriptName,nArgs,nOutArgs);
}

VS_BOOL Star_SRPI_ExecNameScriptEx(void *c_this, void *Object, const VS_CHAR *ScriptName, VS_INT32 nArgs,VS_INT32 nOutArgs )
{
    return g_star_CoreFunctionTbl->SRPI_ExecNameScriptEx(c_this,Object,ScriptName,nArgs,nOutArgs);
}

VS_BOOL Star_SRPI_ExecScript(void *c_this,void *Object,const VS_CHAR *FuncName,const VS_INT8 *ScriptBuf,VS_INT32 ScriptBufSize,VS_INT32 nArgs,VS_INT32 nOutArgs)
{
    return g_star_CoreFunctionTbl->SRPI_ExecScript(c_this,Object,FuncName,ScriptBuf,ScriptBufSize,nArgs,nOutArgs);
}

VS_BOOL Star_SRPI_ExecScriptEx(void *c_this,void *Object,const VS_CHAR *FuncName,const VS_CHAR *FileName,VS_INT32 nArgs,VS_INT32 nOutArgs)
{
    return g_star_CoreFunctionTbl->SRPI_ExecScriptEx(c_this,Object,FuncName,FileName,nArgs,nOutArgs);
}

void Star_SRPI_ForceReCompile(void *c_this, void *Object, const VS_CHAR *ScriptName )
{
    g_star_CoreFunctionTbl->SRPI_ForceReCompile(c_this,Object,ScriptName);
}

void Star_SRPI_RegCompileFunc(void *c_this, VSModuleFunction_ScriptCompileHookProc HookProc,VS_UWORD Para)
{
    g_star_CoreFunctionTbl->SRPI_RegCompileFunc(c_this,HookProc,Para);
}

VS_ULONG Star_SRPI_GetRemoteID(void *c_this,void *Object)
{
    return g_star_CoreFunctionTbl->SRPI_GetRemoteID(c_this,Object);
}

VS_ULONG Star_SRPI_GetRemoteCallID(void *c_this,void *Object)
{
    return g_star_CoreFunctionTbl->SRPI_GetRemoteCallID(c_this,Object);
}

VS_UINT16 Star_SRPI_GetRemoteSourceTag(void *c_this,void *Object)
{
    return g_star_CoreFunctionTbl->SRPI_GetRemoteSourceTag(c_this,Object);
}

void *Star_SRPI_GetRemoteAttach(void *c_this,void *Object)
{
    return g_star_CoreFunctionTbl->SRPI_GetRemoteAttach(c_this,Object);
}

VS_CHAR *Star_SRPI_GetRemoteCallName(void *c_this,void *Object)
{
    return g_star_CoreFunctionTbl->SRPI_GetRemoteCallName(c_this,Object);
}

VS_BOOL Star_SRPI_IsRemoteCall(void *c_this,void *Object)
{
    return g_star_CoreFunctionTbl->SRPI_IsRemoteCall(c_this,Object);
}

void Star_SRPI_SetDeferRspFlag(void *c_this,void *Object)
{
    g_star_CoreFunctionTbl->SRPI_SetDeferRspFlag(c_this,Object);
}

void Star_SRPI_SetRetCode(void *c_this,void *Object,VS_ULONG RemoteRetCode)
{
    g_star_CoreFunctionTbl->SRPI_SetRetCode(c_this,Object,RemoteRetCode);
}

void Star_SRPI_SetRemoteRspAttach(void *c_this,void *Object,void *RemoteAttach)
{
    g_star_CoreFunctionTbl->SRPI_SetRemoteRspAttach(c_this,Object,RemoteAttach);
}

void Star_SRPI_RemoteCallRsp(void *c_this,void *Object,VS_ULONG ClientID,VS_ULONG RemoteCallID,const VS_CHAR *RemoteCallName,VS_UINT16 RemoteSourceTag,VS_ULONG RetCode,VS_UINT8 RetType,VS_UWORD RetValue, void *RemoteAttach)
{
    g_star_CoreFunctionTbl->SRPI_RemoteCallRsp(c_this,Object,ClientID,RemoteCallID,RemoteCallName,RemoteSourceTag,RetCode,RetType,RetValue,RemoteAttach);
}

VS_BOOL Star_SRPI_FillSoapRspHeader(void *c_this,void *SXMLInterface)
{
    return g_star_CoreFunctionTbl->SRPI_FillSoapRspHeader(c_this,SXMLInterface);
}

void Star_SRPI_SetPrivateTag(void *c_this,VS_ULONG ClientPrivateTag)
{
    g_star_CoreFunctionTbl->SRPI_SetPrivateTag(c_this,ClientPrivateTag);
}

VS_ULONG Star_SRPI_GetRemotePrivateTag(void *c_this,void *Object)
{
    return g_star_CoreFunctionTbl->SRPI_GetRemotePrivateTag(c_this,Object);
}

VS_ULONG Star_SRPI_GetLayer(void *c_this, void *Object )
{
    return g_star_CoreFunctionTbl->SRPI_GetLayer(c_this,Object);
}

void Star_SRPI_SetPrivateValue(void *c_this, void *Object,VS_ULONG ClassLayer,VS_ULONG Index, VS_UWORD Value  )
{
    g_star_CoreFunctionTbl->SRPI_SetPrivateValue(c_this,Object,ClassLayer,Index,Value);
}

VS_BOOL Star_SRPI_GetPrivateValue(void *c_this, void *Object,VS_ULONG ClassLayer,VS_ULONG Index, VS_UWORD *Value, VS_UWORD DefaultValue  )
{
    return g_star_CoreFunctionTbl->SRPI_GetPrivateValue(c_this,Object,ClassLayer,Index,Value,DefaultValue);
}

void *Star_SRPI_MallocPrivateBuf(void *c_this, void *Object,VS_ULONG ClassLayer,VS_ULONG Index, VS_INT32 BufSize  )
{
    return g_star_CoreFunctionTbl->SRPI_MallocPrivateBuf(c_this,Object,ClassLayer,Index,BufSize);
}

void *Star_SRPI_GetPrivateBuf(void *c_this, void *Object,VS_ULONG ClassLayer,VS_ULONG Index, VS_INT32 *BufSize  )
{
    return g_star_CoreFunctionTbl->SRPI_GetPrivateBuf(c_this,Object,ClassLayer,Index,BufSize);
}

void Star_SRPI_FreePrivate(void *c_this, void *Object,VS_ULONG ClassLayer,VS_ULONG Index )
{
    g_star_CoreFunctionTbl->SRPI_FreePrivate(c_this,Object,ClassLayer,Index);
}

VS_BOOL Star_SRPI_SetNameIntValue(void *c_this, void *Object,const VS_CHAR *Name, VS_INT32 Value, VS_BOOL LocalChange  )
{
    return g_star_CoreFunctionTbl->SRPI_SetNameIntValue(c_this,Object,Name,Value,LocalChange);
}

VS_BOOL Star_SRPI_GetNameIntValue(void *c_this, void *Object,const VS_CHAR *Name, VS_INT32 *Value, VS_INT32 DefaultValue  )
{
    return g_star_CoreFunctionTbl->SRPI_GetNameIntValue(c_this,Object,Name,Value,DefaultValue);
}

VS_BOOL Star_SRPI_SetNameFloatValue(void *c_this, void *Object,const VS_CHAR *Name, VS_DOUBLE Value, VS_BOOL LocalChange  )
{
    return g_star_CoreFunctionTbl->SRPI_SetNameFloatValue(c_this,Object,Name,Value,LocalChange);
}

VS_BOOL Star_SRPI_GetNameFloatValue(void *c_this, void *Object,const VS_CHAR *Name, VS_DOUBLE *Value, VS_DOUBLE DefaultValue  )
{
    return g_star_CoreFunctionTbl->SRPI_GetNameFloatValue(c_this,Object,Name,Value,DefaultValue);
}

VS_BOOL Star_SRPI_SetNameBinValue(void *c_this, void *Object,const VS_CHAR *Name, VS_INT8 *Value, VS_UINT16 ValueSize, VS_BOOL LocalChange  )
{
    return g_star_CoreFunctionTbl->SRPI_SetNameBinValue(c_this,Object,Name,Value,ValueSize,LocalChange);
}

VS_INT8 *Star_SRPI_GetNameBinValue(void *c_this, void *Object,const VS_CHAR *Name, VS_UINT16 *ValueSize )
{
    return g_star_CoreFunctionTbl->SRPI_GetNameBinValue(c_this,Object,Name,ValueSize);
}

VS_BOOL Star_SRPI_SetNameStrValue(void *c_this, void *Object,const VS_CHAR *Name, const VS_CHAR *Value, VS_BOOL LocalChange  )
{
    return g_star_CoreFunctionTbl->SRPI_SetNameStrValue(c_this,Object,Name,Value,LocalChange);
}

VS_CHAR *Star_SRPI_GetNameStrValue(void *c_this, void *Object,const VS_CHAR *Name, const VS_CHAR *DefaultValue  )
{
    return g_star_CoreFunctionTbl->SRPI_GetNameStrValue(c_this,Object,Name,DefaultValue);
}

VS_BOOL Star_SRPI_SetNameTimeValue(void *c_this, void *Object,const VS_CHAR *Name, VS_TIME *Value, VS_BOOL LocalChange  )
{
    return g_star_CoreFunctionTbl->SRPI_SetNameTimeValue(c_this,Object,Name,Value,LocalChange);
}

VS_BOOL Star_SRPI_GetNameTimeValue(void *c_this, void *Object,const VS_CHAR *Name, VS_TIME *Value, VS_TIME *DefaultValue  )
{
    return g_star_CoreFunctionTbl->SRPI_GetNameTimeValue(c_this,Object,Name,Value,DefaultValue);
}

void Star_SRPI_FreeNameValue(void *c_this, void *Object,const VS_CHAR *Name )
{
    g_star_CoreFunctionTbl->SRPI_FreeNameValue(c_this,Object,Name);
}

void Star_SRPI_FreeAllNameValue(void *c_this, void *Object )
{
    g_star_CoreFunctionTbl->SRPI_FreeAllNameValue(c_this,Object);
}

VS_UINT8 Star_SRPI_GetNameValueType(void *c_this, void *Object,const VS_CHAR *Name )
{
    return g_star_CoreFunctionTbl->SRPI_GetNameValueType(c_this,Object,Name);
}

VS_CHAR *Star_SRPI_QueryFirstNameValue(void *c_this,void *Object, VS_UWORD *Context, VS_UINT8 *Type )
{
    return g_star_CoreFunctionTbl->SRPI_QueryFirstNameValue(c_this,Object,Context,Type);
}

VS_CHAR *Star_SRPI_QueryNextNameValue(void *c_this,void *Object, VS_UWORD *Context, VS_UINT8 *Type )
{
    return g_star_CoreFunctionTbl->SRPI_QueryNextNameValue(c_this,Object,Context,Type);
}

VS_BOOL Star_SRPI_RegNameValueChangeCallBack(void *c_this,void *Object,VS_ObjectNameValueChangeNotifyProc ObjectNameValueChangeNotifyProc,VS_UWORD Para)
{
    return g_star_CoreFunctionTbl->SRPI_RegNameValueChangeCallBack(c_this,Object,ObjectNameValueChangeNotifyProc,Para);
}

void Star_SRPI_UnRegNameValueChangeCallBack(void *c_this,void *Object,VS_ObjectNameValueChangeNotifyProc ObjectNameValueChangeNotifyProc,VS_UWORD Para)
{
    g_star_CoreFunctionTbl->SRPI_UnRegNameValueChangeCallBack(c_this,Object,ObjectNameValueChangeNotifyProc,Para);
}

VS_UINT8 Star_SRPI_GetSyncStatus(void *c_this, void *Object)
{
    return g_star_CoreFunctionTbl->SRPI_GetSyncStatus(c_this,Object);
}

VS_UINT8 Star_SRPI_GetSyncGroupStatus(void *c_this, VS_UUID *SysRootItemID,VS_SYNCGROUP GroupIndex )
{
    return g_star_CoreFunctionTbl->SRPI_GetSyncGroupStatus(c_this,SysRootItemID,GroupIndex);
}

VS_UINT8 Star_SRPI_GetSyncGroupStatusEx(void *c_this, VS_CHAR *SysRootItemName,VS_SYNCGROUP GroupIndex )
{
    return g_star_CoreFunctionTbl->SRPI_GetSyncGroupStatusEx(c_this,SysRootItemName,GroupIndex);
}

void Star_SRPI_SetSyncGroup(void *c_this,void *Object,VS_SYNCGROUP GroupIndex)
{
    g_star_CoreFunctionTbl->SRPI_SetSyncGroup(c_this,Object,GroupIndex);
}

void Star_SRPI_GetSyncGroup(void *c_this,void *Object,VS_SYNCGROUP *GroupIndex)
{
    g_star_CoreFunctionTbl->SRPI_GetSyncGroup(c_this,Object,GroupIndex);
}

void *Star_SRPI_GetActiveService(void *c_this)
{
    return g_star_CoreFunctionTbl->SRPI_GetActiveService(c_this);
}

void *Star_SRPI_GetService(void *c_this)
{
    return g_star_CoreFunctionTbl->SRPI_GetService(c_this);
}

VS_INT32 Star_SRPI_GetActiveServicePath(void *c_this,VS_INT8 *Buf,VS_INT32 BufSize)
{
    return g_star_CoreFunctionTbl->SRPI_GetActiveServicePath(c_this,Buf,BufSize);
}

VS_CHAR *Star_SRPI_GetActiveServiceName(void *c_this)
{
    return g_star_CoreFunctionTbl->SRPI_GetActiveServiceName(c_this);
}

VS_INT32 Star_SRPI_GetServicePath(void *c_this,VS_INT8 *Buf,VS_INT32 BufSize)
{
    return g_star_CoreFunctionTbl->SRPI_GetServicePath(c_this,Buf,BufSize);
}

VS_CHAR *Star_SRPI_GetServiceName(void *c_this)
{
    return g_star_CoreFunctionTbl->SRPI_GetServiceName(c_this);
}

VS_INT32 Star_SRPI_GetServiceInterval(void *c_this)
{
    return g_star_CoreFunctionTbl->SRPI_GetServiceInterval(c_this);
}

void Star_SRPI_GetServiceID(void *c_this,VS_UUID *UuidPtr)
{
    g_star_CoreFunctionTbl->SRPI_GetServiceID(c_this,UuidPtr);
}

void Star_SRPI_StartVSService(void *c_this,VS_UUID *ServiceID)
{
    g_star_CoreFunctionTbl->SRPI_StartVSService(c_this,ServiceID);
}

void Star_SRPI_ExitVSService(void *c_this)
{
    g_star_CoreFunctionTbl->SRPI_ExitVSService(c_this);
}

void Star_SRPI_SaveService(void *c_this,const VS_CHAR *Path)
{
    g_star_CoreFunctionTbl->SRPI_SaveService(c_this,Path);
}

VS_BOOL Star_SRPI_IsServiceChange(void *c_this)
{
    return g_star_CoreFunctionTbl->SRPI_IsServiceChange(c_this);
}

VS_BOOL Star_SRPI_IsServiceActive(void *c_this)
{
    return g_star_CoreFunctionTbl->SRPI_IsServiceActive(c_this);
}

void Star_SRPI_GetServiceInfo(void *c_this,VS_SERVICEINFO *ServiceInfo)
{
    g_star_CoreFunctionTbl->SRPI_GetServiceInfo(c_this,ServiceInfo);
}

VS_BOOL Star_SRPI_QueryFirstDepend(void *c_this, VS_QUERYRECORD *QueryRecord,VS_UUID *ServiceID,VS_UUID *RetUuid,VS_CHAR **RetServiceName )
{
    return g_star_CoreFunctionTbl->SRPI_QueryFirstDepend(c_this,QueryRecord,ServiceID,RetUuid,RetServiceName);
}

VS_BOOL Star_SRPI_QueryNextDepend(void *c_this, VS_QUERYRECORD *QueryRecord,VS_UUID *RetUuid,VS_CHAR **RetServiceName )
{
    return g_star_CoreFunctionTbl->SRPI_QueryNextDepend(c_this,QueryRecord,RetUuid,RetServiceName);
}

VS_BOOL Star_SRPI_IsOsSupport(void *c_this, VS_UINT16 ProgramRunType, VS_UINT32 OsType )
{
    return g_star_CoreFunctionTbl->SRPI_IsOsSupport(c_this,ProgramRunType,OsType);
}

VS_UWORD Star_SRPI_GetFrameTicket(void *c_this)
{
    return g_star_CoreFunctionTbl->SRPI_GetFrameTicket(c_this);
}

VS_BOOL Star_SRPI_ExportModule(void *c_this, const VS_CHAR *XmlCfgFile, VS_CHAR **ErrorInfo )
{
    return g_star_CoreFunctionTbl->SRPI_ExportModule(c_this,XmlCfgFile,ErrorInfo);
}

VS_ULONG Star_SRPI_GetServiceGroupID(void *c_this)
{
    return g_star_CoreFunctionTbl->SRPI_GetServiceGroupID(c_this);
}

void Star_SRPI_SetPrintToLua(void *c_this,VS_BOOL PrintFlag)
{
    g_star_CoreFunctionTbl->SRPI_SetPrintToLua(c_this,PrintFlag);
}

void Star_SRPI_RegMessageBoxFunction(void *c_this,void *Object,VS_MessageBoxProc MessageBoxProc)
{
    g_star_CoreFunctionTbl->SRPI_RegMessageBoxFunction(c_this,Object,MessageBoxProc);
}

void Star_SRPI_UnRegMessageBoxFunction(void *c_this,void *Object,VS_MessageBoxProc MessageBoxProc)
{
    g_star_CoreFunctionTbl->SRPI_UnRegMessageBoxFunction(c_this,Object,MessageBoxProc);
}

VS_BOOL Star_SRPI_IsBeingTrace(void *c_this,void *Object)
{
    return g_star_CoreFunctionTbl->SRPI_IsBeingTrace(c_this,Object);
}

void Star_SRPI_CaptureLuaDisp(void *c_this,VS_LuaInfoDispProc DispProc,VS_UWORD Para)
{
    g_star_CoreFunctionTbl->SRPI_CaptureLuaDisp(c_this,DispProc,Para);
}

void Star_SRPI_ReleaseLuaDisp(void *c_this,VS_LuaInfoDispProc DispProc,VS_UWORD Para)
{
    g_star_CoreFunctionTbl->SRPI_ReleaseLuaDisp(c_this,DispProc,Para);
}

void Star_SRPI_InsertToSDT(void *c_this,void *Object)
{
    g_star_CoreFunctionTbl->SRPI_InsertToSDT(c_this,Object);
}

void Star_SRPI_DelFromSDT(void *c_this,void *Object)
{
    g_star_CoreFunctionTbl->SRPI_DelFromSDT(c_this,Object);
}

void *Star_SRPI_QueryFirstFromSDT(void *c_this,VS_QUERYRECORD *QueryRecord)
{
    return g_star_CoreFunctionTbl->SRPI_QueryFirstFromSDT(c_this,QueryRecord);
}

void *Star_SRPI_QueryNextFromSDT(void *c_this,VS_QUERYRECORD *QueryRecord)
{
    return g_star_CoreFunctionTbl->SRPI_QueryNextFromSDT(c_this,QueryRecord);
}

void *Star_SRPI_QueryFirstInstFromSDT(void *c_this,VS_QUERYRECORD *QueryRecord,VS_UUID *ObjectClassID)
{
    return g_star_CoreFunctionTbl->SRPI_QueryFirstInstFromSDT(c_this,QueryRecord,ObjectClassID);
}

void *Star_SRPI_QueryNextInstFromSDT(void *c_this,VS_QUERYRECORD *QueryRecord,VS_UUID *ObjectClassID)
{
    return g_star_CoreFunctionTbl->SRPI_QueryNextInstFromSDT(c_this,QueryRecord,ObjectClassID);
}

void *Star_SRPI_MallocStaticObject(void *c_this,void *ParentObject,OBJECTATTRIBUTEINDEX AttributeIndex,VS_UUID *ObjectClassID,VS_INT32 AttachBufSize,void *AttachBuf)
{
    return g_star_CoreFunctionTbl->SRPI_MallocStaticObject(c_this,ParentObject,AttributeIndex,ObjectClassID,AttachBufSize,AttachBuf);
}

void *Star_SRPI_MallocStaticObjectEx(void *c_this,VS_UUID *ObjectID,void *ParentObject,OBJECTATTRIBUTEINDEX AttributeIndex,VS_UUID *ObjectClassID,VS_INT32 AttachBufSize,void *AttachBuf)
{
    return g_star_CoreFunctionTbl->SRPI_MallocStaticObjectEx(c_this,ObjectID,ParentObject,AttributeIndex,ObjectClassID,AttachBufSize,AttachBuf);
}

void *Star_SRPI_MallocGlobalObject(void *c_this,void *ParentObject,OBJECTATTRIBUTEINDEX AttributeIndex,VS_UUID *ObjectClassID,VS_INT32 AttachBufSize,void *AttachBuf,VS_ULONG ClientID)
{
    return g_star_CoreFunctionTbl->SRPI_MallocGlobalObject(c_this,ParentObject,AttributeIndex,ObjectClassID,AttachBufSize,AttachBuf,ClientID);
}

void *Star_SRPI_MallocGlobalObjectEx(void *c_this,VS_UUID *ObjectID,void *ParentObject,OBJECTATTRIBUTEINDEX AttributeIndex,VS_UUID *ObjectClassID,VS_INT32 AttachBufSize,void *AttachBuf,VS_ULONG ClientID)
{
    return g_star_CoreFunctionTbl->SRPI_MallocGlobalObjectEx(c_this,ObjectID,ParentObject,AttributeIndex,ObjectClassID,AttachBufSize,AttachBuf,ClientID);
}

void *Star_SRPI_MallocObject(void *c_this,void *ParentObject,OBJECTATTRIBUTEINDEX AttributeIndex,VS_UUID *ObjectClassID,VS_INT32 AttachBufSize,void *AttachBuf)
{
    return g_star_CoreFunctionTbl->SRPI_MallocObject(c_this,ParentObject,AttributeIndex,ObjectClassID,AttachBufSize,AttachBuf);
}

void *Star_SRPI_MallocObjectEx(void *c_this,VS_UUID *ObjectID,void *ParentObject,OBJECTATTRIBUTEINDEX AttributeIndex,VS_UUID *ObjectClassID,VS_INT32 AttachBufSize,void *AttachBuf)
{
    return g_star_CoreFunctionTbl->SRPI_MallocObjectEx(c_this,ObjectID,ParentObject,AttributeIndex,ObjectClassID,AttachBufSize,AttachBuf);
}

void *Star_SRPI_MallocObjectL(void *c_this,VS_UUID *ObjectClassID,VS_INT32 AttachBufSize,void *AttachBuf)
{
    return g_star_CoreFunctionTbl->SRPI_MallocObjectL(c_this,ObjectClassID,AttachBufSize,AttachBuf);
}

void *Star_SRPI_MallocObjectLEx(void *c_this,VS_UUID *ObjectID,VS_UUID *ObjectClassID,VS_INT32 AttachBufSize,void *AttachBuf)
{
    return g_star_CoreFunctionTbl->SRPI_MallocObjectLEx(c_this,ObjectID,ObjectClassID,AttachBufSize,AttachBuf);
}

void *Star_SRPI_MallocClientObject(void *c_this,void *ParentObject,OBJECTATTRIBUTEINDEX AttributeIndex,VS_UUID *ObjectClassID,VS_INT32 AttachBufSize,void *AttachBuf,VS_ULONG ClientID)
{
    return g_star_CoreFunctionTbl->SRPI_MallocClientObject(c_this,ParentObject,AttributeIndex,ObjectClassID,AttachBufSize,AttachBuf,ClientID);
}

void *Star_SRPI_MallocClientObjectEx(void *c_this,VS_UUID *ObjectID,void *ParentObject,OBJECTATTRIBUTEINDEX AttributeIndex,VS_UUID *ObjectClassID,VS_INT32 AttachBufSize,void *AttachBuf,VS_ULONG ClientID)
{
    return g_star_CoreFunctionTbl->SRPI_MallocClientObjectEx(c_this,ObjectID,ParentObject,AttributeIndex,ObjectClassID,AttachBufSize,AttachBuf,ClientID);
}

VS_BOOL Star_SRPI_WaitMalloc(void *c_this,void *Object)
{
    return g_star_CoreFunctionTbl->SRPI_WaitMalloc(c_this,Object);
}

VS_ULONG Star_SRPI_GetOPPermission(void *c_this)
{
    return g_star_CoreFunctionTbl->SRPI_GetOPPermission(c_this);
}

VS_BOOL Star_SRPI_CopyObject(void *c_this,void *Object,void *SrcObject)
{
    return g_star_CoreFunctionTbl->SRPI_CopyObject(c_this,Object,SrcObject);
}

void Star_SRPI_FreeObject(void *c_this,void *Object)
{
    g_star_CoreFunctionTbl->SRPI_FreeObject(c_this,Object);
}

void Star_SRPI_DeferFreeObject(void *c_this,void *Object)
{
    g_star_CoreFunctionTbl->SRPI_DeferFreeObject(c_this,Object);
}

VS_BOOL Star_SRPI_IsObjectInFree(void *c_this,void *Object)
{
    return g_star_CoreFunctionTbl->SRPI_IsObjectInFree(c_this,Object);
}

void Star_SRPI_ChangeLocal(void *c_this,void *Object,OBJECTATTRIBUTEINDEX AttributeIndex,const VS_INT8 *NewValue)
{
    g_star_CoreFunctionTbl->SRPI_ChangeLocal(c_this,Object,AttributeIndex,NewValue);
}

void Star_SRPI_ChangeObject(void *c_this,void *Object,OBJECTATTRIBUTEINDEX AttributeIndex,const VS_INT8 *NewValue)
{
    g_star_CoreFunctionTbl->SRPI_ChangeObject(c_this,Object,AttributeIndex,NewValue);
}

void Star_SRPI_ChangeParent(void *c_this,void *Object,void *ParentObject,OBJECTATTRIBUTEINDEX AttributeIndex)
{
    g_star_CoreFunctionTbl->SRPI_ChangeParent(c_this,Object,ParentObject,AttributeIndex);
}

void Star_SRPI_MarkChange(void *c_this,void *Object,OBJECTATTRIBUTEINDEX AttributeIndex)
{
    g_star_CoreFunctionTbl->SRPI_MarkChange(c_this,Object,AttributeIndex);
}

VS_BOOL Star_SRPI_RegBeforeChangeCallBack(void *c_this,void *Object,VS_ObjectBeforeChangeNotifyProc ObjectBeforeChangeNotifyProc,VS_UWORD Para,VS_BOOL ChildNotify)
{
    return g_star_CoreFunctionTbl->SRPI_RegBeforeChangeCallBack(c_this,Object,ObjectBeforeChangeNotifyProc,Para,ChildNotify);
}

VS_BOOL Star_SRPI_RegChangeCallBack(void *c_this,void *Object,VS_ObjectChangeNotifyProc ObjectChangeNotifyProc,VS_UWORD Para,VS_BOOL ChildNotify)
{
    return g_star_CoreFunctionTbl->SRPI_RegChangeCallBack(c_this,Object,ObjectChangeNotifyProc,Para,ChildNotify);
}

VS_BOOL Star_SRPI_RegReMallocCallBack(void *c_this,void *Object,VS_ObjectReMallocNotifyProc ObjectReMallocNotifyProc,VS_UWORD Para)
{
    return g_star_CoreFunctionTbl->SRPI_RegReMallocCallBack(c_this,Object,ObjectReMallocNotifyProc,Para);
}

void Star_SRPI_UnRegBeforeChangeCallBack(void *c_this,void *Object,VS_ObjectBeforeChangeNotifyProc ObjectBeforeChangeNotifyProc,VS_UWORD Para)
{
    g_star_CoreFunctionTbl->SRPI_UnRegBeforeChangeCallBack(c_this,Object,ObjectBeforeChangeNotifyProc,Para);
}

void Star_SRPI_UnRegChangeCallBack(void *c_this,void *Object,VS_ObjectChangeNotifyProc ObjectChangeNotifyProc,VS_UWORD Para)
{
    g_star_CoreFunctionTbl->SRPI_UnRegChangeCallBack(c_this,Object,ObjectChangeNotifyProc,Para);
}

void Star_SRPI_UnRegReMallocCallBack(void *c_this,void *Object,VS_ObjectReMallocNotifyProc ObjectReMallocNotifyProc,VS_UWORD Para)
{
    g_star_CoreFunctionTbl->SRPI_UnRegReMallocCallBack(c_this,Object,ObjectReMallocNotifyProc,Para);
}

VS_BOOL Star_SRPI_RegObjectIDChangeNotify(void *c_this,VS_ObjectIDChangeNotifyProc ChangeNotifyProc,VS_UWORD Para)
{
    return g_star_CoreFunctionTbl->SRPI_RegObjectIDChangeNotify(c_this,ChangeNotifyProc,Para);
}

void Star_SRPI_UnRegObjectIDChangeNotify(void *c_this,VS_ObjectIDChangeNotifyProc ChangeNotifyProc,VS_UWORD Para)
{
    g_star_CoreFunctionTbl->SRPI_UnRegObjectIDChangeNotify(c_this,ChangeNotifyProc,Para);
}

VS_BOOL Star_SRPI_RegObjectFreeNotify(void *c_this,VS_ObjectFreeNotifyProc FreeNotifyProc,VS_UWORD Para)
{
    return g_star_CoreFunctionTbl->SRPI_RegObjectFreeNotify(c_this,FreeNotifyProc,Para);
}

void Star_SRPI_UnRegObjectFreeNotify(void *c_this,VS_ObjectFreeNotifyProc FreeNotifyProc,VS_UWORD Para)
{
    g_star_CoreFunctionTbl->SRPI_UnRegObjectFreeNotify(c_this,FreeNotifyProc,Para);
}

void Star_SRPI_DupVString(void *c_this,VS_VSTRING *InVString,VS_VSTRING *OutVString)
{
    g_star_CoreFunctionTbl->SRPI_DupVString(c_this,InVString,OutVString);
}

VS_ULONG Star_SRPI_GetVStringBufSize(void *c_this,VS_VSTRING *VString)
{
    return g_star_CoreFunctionTbl->SRPI_GetVStringBufSize(c_this,VString);
}

void Star_SRPI_ExpandVStringBufSize(void *c_this,VS_VSTRING *VString,VS_ULONG Size)
{
    g_star_CoreFunctionTbl->SRPI_ExpandVStringBufSize(c_this,VString,Size);
}

VS_ULONG Star_SRPI_GetAllocType(void *c_this,void *Object)
{
    return g_star_CoreFunctionTbl->SRPI_GetAllocType(c_this,Object);
}

VS_BOOL Star_SRPI_CreateUser(void *c_this,const VS_CHAR *In_UserName,const VS_CHAR *UserPass,VS_UINT8 ReadWriteOrExecute)
{
    return g_star_CoreFunctionTbl->SRPI_CreateUser(c_this,In_UserName,UserPass,ReadWriteOrExecute);
}

void Star_SRPI_DeleteUser(void *c_this,const VS_CHAR *In_UserName)
{
    g_star_CoreFunctionTbl->SRPI_DeleteUser(c_this,In_UserName);
}

VS_CHAR *Star_SRPI_QueryFirstUser(void *c_this,VS_QUERYRECORD *QueryRecord,VS_UINT8 *ReadWriteOrExecute )
{
    return g_star_CoreFunctionTbl->SRPI_QueryFirstUser(c_this,QueryRecord,ReadWriteOrExecute);
}

VS_CHAR *Star_SRPI_QueryNextUser(void *c_this,VS_QUERYRECORD *QueryRecord,VS_UINT8 *ReadWriteOrExecute )
{
    return g_star_CoreFunctionTbl->SRPI_QueryNextUser(c_this,QueryRecord,ReadWriteOrExecute);
}

void Star_SRPI_SetAppClass(void *c_this,void *Object,VS_ULONG ClassLayer,void *SRPObjectClass)
{
    g_star_CoreFunctionTbl->SRPI_SetAppClass(c_this,Object,ClassLayer,SRPObjectClass);
}

void *Star_SRPI_GetAppClass(void *c_this,void *Object,VS_ULONG ClassLayer)
{
    return g_star_CoreFunctionTbl->SRPI_GetAppClass(c_this,Object,ClassLayer);
}

VS_INT32 Star_SRPI_GetAttributeNumber(void *c_this,void *Object)
{
    return g_star_CoreFunctionTbl->SRPI_GetAttributeNumber(c_this,Object);
}

VS_INT32 Star_SRPI_GetAttributeSize(void *c_this,void *Object)
{
    return g_star_CoreFunctionTbl->SRPI_GetAttributeSize(c_this,Object);
}

VS_CHAR *Star_SRPI_GetAttributeName(void *c_this,void *Object,OBJECTATTRIBUTEINDEX AttributeIndex)
{
    return g_star_CoreFunctionTbl->SRPI_GetAttributeName(c_this,Object,AttributeIndex);
}

VS_BOOL Star_SRPI_GetAttributeInfo(void *c_this,void *Object,OBJECTATTRIBUTEINDEX AttributeIndex,VS_ATTRIBUTEINFO *AttributeInfo)
{
    return g_star_CoreFunctionTbl->SRPI_GetAttributeInfo(c_this,Object,AttributeIndex,AttributeInfo);
}

VS_BOOL Star_SRPI_GetAttributeInfoEx(void *c_this,void *Object,const VS_CHAR *AttributeName,VS_ATTRIBUTEINFO *AttributeInfo)
{
    return g_star_CoreFunctionTbl->SRPI_GetAttributeInfoEx(c_this,Object,AttributeName,AttributeInfo);
}

VS_INT32 Star_SRPI_GetAttachAttributeNumber(void *c_this,void *Object)
{
    return g_star_CoreFunctionTbl->SRPI_GetAttachAttributeNumber(c_this,Object);
}

VS_INT32 Star_SRPI_GetAttachAttributeSize(void *c_this,void *Object)
{
    return g_star_CoreFunctionTbl->SRPI_GetAttachAttributeSize(c_this,Object);
}

VS_BOOL Star_SRPI_GetAttachAttributeInfo(void *c_this,void *Object,OBJECTATTRIBUTEINDEX AttributeIndex,VS_ATTRIBUTEINFO *AttributeInfo)
{
    return g_star_CoreFunctionTbl->SRPI_GetAttachAttributeInfo(c_this,Object,AttributeIndex,AttributeInfo);
}

VS_BOOL Star_SRPI_GetComboBoxItem(void *c_this,VS_UINT8 *ComboBoxID, VS_COMBOBOXITEM *ComboBoxItemBuf)
{
    return g_star_CoreFunctionTbl->SRPI_GetComboBoxItem(c_this,ComboBoxID,ComboBoxItemBuf);
}

VS_INT32 Star_SRPI_GetFunctionNumber(void *c_this,void *Object)
{
    return g_star_CoreFunctionTbl->SRPI_GetFunctionNumber(c_this,Object);
}

VS_BOOL Star_SRPI_GetFunctionInfo(void *c_this,void *Object,VS_INT32 FunctionIndex,VS_FUNCTIONINFO *FunctionInfo)
{
    return g_star_CoreFunctionTbl->SRPI_GetFunctionInfo(c_this,Object,FunctionIndex,FunctionInfo);
}

VS_INT32 Star_SRPI_GetOutEventNumber(void *c_this,void *Object)
{
    return g_star_CoreFunctionTbl->SRPI_GetOutEventNumber(c_this,Object);
}

VS_BOOL Star_SRPI_GetOutEventInfo(void *c_this,void *Object,VS_INT32 OutEventIndex,VS_OUTEVENTINFO *OutEventInfo)
{
    return g_star_CoreFunctionTbl->SRPI_GetOutEventInfo(c_this,Object,OutEventIndex,OutEventInfo);
}

void *Star_SRPI_CreateIndex_Nor(void *c_this,VS_INT32 KeyNumber,VS_UINT16 HashTableBits)
{
    return g_star_CoreFunctionTbl->SRPI_CreateIndex_Nor(c_this,KeyNumber,HashTableBits);
}

void *Star_SRPI_CreateIndexCmp_Nor(void *c_this,VS_INT32 KeyNumber,VS_UINT16 HashTableBits,VS_IndexCompareProc CompareProc)
{
    return g_star_CoreFunctionTbl->SRPI_CreateIndexCmp_Nor(c_this,KeyNumber,HashTableBits,CompareProc);
}

void *Star_SRPI_CreateIDIndex_Nor(void *c_this,VS_UINT16 HashTableBits)
{
    return g_star_CoreFunctionTbl->SRPI_CreateIDIndex_Nor(c_this,HashTableBits);
}

void *Star_SRPI_CreateIDIndexEx_Nor(void *c_this,VS_UINT16 HashTableBits)
{
    return g_star_CoreFunctionTbl->SRPI_CreateIDIndexEx_Nor(c_this,HashTableBits);
}

void *Star_SRPI_CreateIndex_Dbg(void *c_this,VS_INT32 KeyNumber,VS_UINT16 HashTableBits,const VS_CHAR *FileName,VS_INT32 LineNumber)
{
    return g_star_CoreFunctionTbl->SRPI_CreateIndex_Dbg(c_this,KeyNumber,HashTableBits,FileName,LineNumber);
}

void *Star_SRPI_CreateIndexCmp_Dbg(void *c_this,VS_INT32 KeyNumber,VS_UINT16 HashTableBits,VS_IndexCompareProc CompareProc,const VS_CHAR *FileName,VS_INT32 LineNumber)
{
    return g_star_CoreFunctionTbl->SRPI_CreateIndexCmp_Dbg(c_this,KeyNumber,HashTableBits,CompareProc,FileName,LineNumber);
}

void *Star_SRPI_CreateIDIndex_Dbg(void *c_this,VS_UINT16 HashTableBits,const VS_CHAR *FileName,VS_INT32 LineNumber)
{
    return g_star_CoreFunctionTbl->SRPI_CreateIDIndex_Dbg(c_this,HashTableBits,FileName,LineNumber);
}

void *Star_SRPI_CreateIDIndexEx_Dbg(void *c_this,VS_UINT16 HashTableBits,const VS_CHAR *FileName,VS_INT32 LineNumber)
{
    return g_star_CoreFunctionTbl->SRPI_CreateIDIndexEx_Dbg(c_this,HashTableBits,FileName,LineNumber);
}

void Star_SRPI_InsertOneKey(void *c_this,void *IndexContext,VS_UWORD MainKey,VS_INT8 *Buf)
{
    g_star_CoreFunctionTbl->SRPI_InsertOneKey(c_this,IndexContext,MainKey,Buf);
}

VS_INT8 *Star_SRPI_FindOneKey(void *c_this,void *IndexContext,VS_UWORD MainKey)
{
    return g_star_CoreFunctionTbl->SRPI_FindOneKey(c_this,IndexContext,MainKey);
}

VS_INT8 *Star_SRPI_DelOneKey(void *c_this,void *IndexContext,VS_UWORD MainKey)
{
    return g_star_CoreFunctionTbl->SRPI_DelOneKey(c_this,IndexContext,MainKey);
}

VS_INT8 *Star_SRPI_QueryFirstOneKey(void *c_this,void *IndexContext,VS_QUERYRECORD *QueryRecord,VS_UWORD *MainKey)
{
    return g_star_CoreFunctionTbl->SRPI_QueryFirstOneKey(c_this,IndexContext,QueryRecord,MainKey);
}

VS_INT8 *Star_SRPI_QueryNextOneKey(void *c_this,void *IndexContext,VS_QUERYRECORD *QueryRecord,VS_UWORD *MainKey)
{
    return g_star_CoreFunctionTbl->SRPI_QueryNextOneKey(c_this,IndexContext,QueryRecord,MainKey);
}

VS_INT8 *Star_SRPI_QueryFirstOneKeyA(void *c_this,void *IndexContext,VS_QUERYRECORD *QueryRecord,VS_UWORD *MainKey)
{
    return g_star_CoreFunctionTbl->SRPI_QueryFirstOneKeyA(c_this,IndexContext,QueryRecord,MainKey);
}

VS_INT8 *Star_SRPI_QueryNextOneKeyA(void *c_this,void *IndexContext,VS_QUERYRECORD *QueryRecord,VS_UWORD *MainKey)
{
    return g_star_CoreFunctionTbl->SRPI_QueryNextOneKeyA(c_this,IndexContext,QueryRecord,MainKey);
}

void Star_SRPI_InsertTwoKey(void *c_this,void *IndexContext,VS_UWORD MainKey,VS_UWORD SecondKey,VS_INT8 *Buf)
{
    g_star_CoreFunctionTbl->SRPI_InsertTwoKey(c_this,IndexContext,MainKey,SecondKey,Buf);
}

VS_INT8 *Star_SRPI_FindTwoKey(void *c_this,void *IndexContext,VS_UWORD MainKey,VS_UWORD SecondKey)
{
    return g_star_CoreFunctionTbl->SRPI_FindTwoKey(c_this,IndexContext,MainKey,SecondKey);
}

VS_INT8 *Star_SRPI_DelTwoKey(void *c_this,void *IndexContext,VS_UWORD MainKey,VS_UWORD SecondKey)
{
    return g_star_CoreFunctionTbl->SRPI_DelTwoKey(c_this,IndexContext,MainKey,SecondKey);
}

VS_INT8 *Star_SRPI_QueryFirstTwoKey(void *c_this,void *IndexContext,VS_QUERYRECORD *QueryRecord,VS_UWORD *MainKey,VS_UWORD *SecondKey)
{
    return g_star_CoreFunctionTbl->SRPI_QueryFirstTwoKey(c_this,IndexContext,QueryRecord,MainKey,SecondKey);
}

VS_INT8 *Star_SRPI_QueryNextTwoKey(void *c_this,void *IndexContext,VS_QUERYRECORD *QueryRecord,VS_UWORD *MainKey,VS_UWORD *SecondKey)
{
    return g_star_CoreFunctionTbl->SRPI_QueryNextTwoKey(c_this,IndexContext,QueryRecord,MainKey,SecondKey);
}

VS_INT8 *Star_SRPI_QueryFirstTwoKeyA(void *c_this,void *IndexContext,VS_QUERYRECORD *QueryRecord,VS_UWORD *MainKey,VS_UWORD *SecondKey)
{
    return g_star_CoreFunctionTbl->SRPI_QueryFirstTwoKeyA(c_this,IndexContext,QueryRecord,MainKey,SecondKey);
}

VS_INT8 *Star_SRPI_QueryNextTwoKeyA(void *c_this,void *IndexContext,VS_QUERYRECORD *QueryRecord,VS_UWORD *MainKey,VS_UWORD *SecondKey)
{
    return g_star_CoreFunctionTbl->SRPI_QueryNextTwoKeyA(c_this,IndexContext,QueryRecord,MainKey,SecondKey);
}

VS_INT8 *Star_SRPI_QueryFirstTwoKey_F(void *c_this,void *IndexContext,VS_QUERYRECORD *QueryRecord,VS_UWORD MainKey,VS_UWORD *SecondKey)
{
    return g_star_CoreFunctionTbl->SRPI_QueryFirstTwoKey_F(c_this,IndexContext,QueryRecord,MainKey,SecondKey);
}

VS_INT8 *Star_SRPI_QueryNextTwoKey_F(void *c_this,void *IndexContext,VS_QUERYRECORD *QueryRecord,VS_UWORD MainKey,VS_UWORD *SecondKey)
{
    return g_star_CoreFunctionTbl->SRPI_QueryNextTwoKey_F(c_this,IndexContext,QueryRecord,MainKey,SecondKey);
}

VS_INT8 *Star_SRPI_QueryFirstTwoKeyA_F(void *c_this,void *IndexContext,VS_QUERYRECORD *QueryRecord,VS_UWORD MainKey,VS_UWORD *SecondKey)
{
    return g_star_CoreFunctionTbl->SRPI_QueryFirstTwoKeyA_F(c_this,IndexContext,QueryRecord,MainKey,SecondKey);
}

VS_INT8 *Star_SRPI_QueryNextTwoKeyA_F(void *c_this,void *IndexContext,VS_QUERYRECORD *QueryRecord,VS_UWORD MainKey,VS_UWORD *SecondKey)
{
    return g_star_CoreFunctionTbl->SRPI_QueryNextTwoKeyA_F(c_this,IndexContext,QueryRecord,MainKey,SecondKey);
}

void Star_SRPI_InsertThreeKey(void *c_this,void *IndexContext,VS_UWORD MainKey,VS_UWORD SecondKey,VS_UWORD ThirdKey,VS_INT8 *Buf)
{
    g_star_CoreFunctionTbl->SRPI_InsertThreeKey(c_this,IndexContext,MainKey,SecondKey,ThirdKey,Buf);
}

VS_INT8 *Star_SRPI_FindThreeKey(void *c_this,void *IndexContext,VS_UWORD MainKey,VS_UWORD SecondKey,VS_UWORD ThirdKey)
{
    return g_star_CoreFunctionTbl->SRPI_FindThreeKey(c_this,IndexContext,MainKey,SecondKey,ThirdKey);
}

VS_INT8 *Star_SRPI_DelThreeKey(void *c_this,void *IndexContext,VS_UWORD MainKey,VS_UWORD SecondKey,VS_UWORD ThirdKey)
{
    return g_star_CoreFunctionTbl->SRPI_DelThreeKey(c_this,IndexContext,MainKey,SecondKey,ThirdKey);
}

VS_INT8 *Star_SRPI_QueryFirstThreeKey(void *c_this,void *IndexContext,VS_QUERYRECORD *QueryRecord,VS_UWORD *MainKey,VS_UWORD *SecondKey,VS_UWORD *ThirdKey)
{
    return g_star_CoreFunctionTbl->SRPI_QueryFirstThreeKey(c_this,IndexContext,QueryRecord,MainKey,SecondKey,ThirdKey);
}

VS_INT8 *Star_SRPI_QueryNextThreeKey(void *c_this,void *IndexContext,VS_QUERYRECORD *QueryRecord,VS_UWORD *MainKey,VS_UWORD *SecondKey,VS_UWORD *ThirdKey)
{
    return g_star_CoreFunctionTbl->SRPI_QueryNextThreeKey(c_this,IndexContext,QueryRecord,MainKey,SecondKey,ThirdKey);
}

VS_INT8 *Star_SRPI_QueryFirstThreeKeyA(void *c_this,void *IndexContext,VS_QUERYRECORD *QueryRecord,VS_UWORD *MainKey,VS_UWORD *SecondKey,VS_UWORD *ThirdKey)
{
    return g_star_CoreFunctionTbl->SRPI_QueryFirstThreeKeyA(c_this,IndexContext,QueryRecord,MainKey,SecondKey,ThirdKey);
}

VS_INT8 *Star_SRPI_QueryNextThreeKeyA(void *c_this,void *IndexContext,VS_QUERYRECORD *QueryRecord,VS_UWORD *MainKey,VS_UWORD *SecondKey,VS_UWORD *ThirdKey)
{
    return g_star_CoreFunctionTbl->SRPI_QueryNextThreeKeyA(c_this,IndexContext,QueryRecord,MainKey,SecondKey,ThirdKey);
}

VS_INT8 *Star_SRPI_QueryFirstThreeKey_F(void *c_this,void *IndexContext,VS_QUERYRECORD *QueryRecord,VS_UWORD MainKey,VS_UWORD *SecondKey,VS_UWORD *ThirdKey)
{
    return g_star_CoreFunctionTbl->SRPI_QueryFirstThreeKey_F(c_this,IndexContext,QueryRecord,MainKey,SecondKey,ThirdKey);
}

VS_INT8 *Star_SRPI_QueryNextThreeKey_F(void *c_this,void *IndexContext,VS_QUERYRECORD *QueryRecord,VS_UWORD MainKey,VS_UWORD *SecondKey,VS_UWORD *ThirdKey)
{
    return g_star_CoreFunctionTbl->SRPI_QueryNextThreeKey_F(c_this,IndexContext,QueryRecord,MainKey,SecondKey,ThirdKey);
}

VS_INT8 *Star_SRPI_QueryFirstThreeKeyA_F(void *c_this,void *IndexContext,VS_QUERYRECORD *QueryRecord,VS_UWORD MainKey,VS_UWORD *SecondKey,VS_UWORD *ThirdKey)
{
    return g_star_CoreFunctionTbl->SRPI_QueryFirstThreeKeyA_F(c_this,IndexContext,QueryRecord,MainKey,SecondKey,ThirdKey);
}

VS_INT8 *Star_SRPI_QueryNextThreeKeyA_F(void *c_this,void *IndexContext,VS_QUERYRECORD *QueryRecord,VS_UWORD MainKey,VS_UWORD *SecondKey,VS_UWORD *ThirdKey)
{
    return g_star_CoreFunctionTbl->SRPI_QueryNextThreeKeyA_F(c_this,IndexContext,QueryRecord,MainKey,SecondKey,ThirdKey);
}

VS_INT8 *Star_SRPI_QueryFirstThreeKey_S(void *c_this,void *IndexContext,VS_QUERYRECORD *QueryRecord,VS_UWORD MainKey,VS_UWORD SecondKey,VS_UWORD *ThirdKey)
{
    return g_star_CoreFunctionTbl->SRPI_QueryFirstThreeKey_S(c_this,IndexContext,QueryRecord,MainKey,SecondKey,ThirdKey);
}

VS_INT8 *Star_SRPI_QueryNextThreeKey_S(void *c_this,void *IndexContext,VS_QUERYRECORD *QueryRecord,VS_UWORD MainKey,VS_UWORD SecondKey,VS_UWORD *ThirdKey)
{
    return g_star_CoreFunctionTbl->SRPI_QueryNextThreeKey_S(c_this,IndexContext,QueryRecord,MainKey,SecondKey,ThirdKey);
}

VS_INT8 *Star_SRPI_QueryFirstThreeKeyA_S(void *c_this,void *IndexContext,VS_QUERYRECORD *QueryRecord,VS_UWORD MainKey,VS_UWORD SecondKey,VS_UWORD *ThirdKey)
{
    return g_star_CoreFunctionTbl->SRPI_QueryFirstThreeKeyA_S(c_this,IndexContext,QueryRecord,MainKey,SecondKey,ThirdKey);
}

VS_INT8 *Star_SRPI_QueryNextThreeKeyA_S(void *c_this,void *IndexContext,VS_QUERYRECORD *QueryRecord,VS_UWORD MainKey,VS_UWORD SecondKey,VS_UWORD *ThirdKey)
{
    return g_star_CoreFunctionTbl->SRPI_QueryNextThreeKeyA_S(c_this,IndexContext,QueryRecord,MainKey,SecondKey,ThirdKey);
}

void Star_SRPI_InsertIDKey(void *c_this,void *IndexContext,VS_UUID *UuidKey,VS_INT8 *Buf )
{
    g_star_CoreFunctionTbl->SRPI_InsertIDKey(c_this,IndexContext,UuidKey,Buf);
}

VS_INT8 *Star_SRPI_FindIDKey(void *c_this,void *IndexContext,VS_UUID *UuidKey)
{
    return g_star_CoreFunctionTbl->SRPI_FindIDKey(c_this,IndexContext,UuidKey);
}

VS_INT8 *Star_SRPI_DelIDKey(void *c_this,void *IndexContext,VS_UUID *UuidKey)
{
    return g_star_CoreFunctionTbl->SRPI_DelIDKey(c_this,IndexContext,UuidKey);
}

VS_INT8 *Star_SRPI_QueryFirstIDKey(void *c_this,void *IndexContext,VS_QUERYRECORD *QueryRecord,VS_UUID *UuidKey)
{
    return g_star_CoreFunctionTbl->SRPI_QueryFirstIDKey(c_this,IndexContext,QueryRecord,UuidKey);
}

VS_INT8 *Star_SRPI_QueryNextIDKey(void *c_this,void *IndexContext,VS_QUERYRECORD *QueryRecord,VS_UUID *UuidKey)
{
    return g_star_CoreFunctionTbl->SRPI_QueryNextIDKey(c_this,IndexContext,QueryRecord,UuidKey);
}

VS_INT8 *Star_SRPI_QueryFirstIDKeyA(void *c_this,void *IndexContext,VS_QUERYRECORD *QueryRecord,VS_UUID *UuidKey)
{
    return g_star_CoreFunctionTbl->SRPI_QueryFirstIDKeyA(c_this,IndexContext,QueryRecord,UuidKey);
}

VS_INT8 *Star_SRPI_QueryNextIDKeyA(void *c_this,void *IndexContext,VS_QUERYRECORD *QueryRecord,VS_UUID *UuidKey)
{
    return g_star_CoreFunctionTbl->SRPI_QueryNextIDKeyA(c_this,IndexContext,QueryRecord,UuidKey);
}

void Star_SRPI_InsertIDKeyEx(void *c_this,void *IndexContext,VS_UUID *UuidKey,VS_UWORD ExKey,VS_INT8 *Buf)
{
    g_star_CoreFunctionTbl->SRPI_InsertIDKeyEx(c_this,IndexContext,UuidKey,ExKey,Buf);
}

VS_INT8 *Star_SRPI_FindIDKeyEx(void *c_this,void *IndexContext,VS_UUID *UuidKey,VS_UWORD ExKey)
{
    return g_star_CoreFunctionTbl->SRPI_FindIDKeyEx(c_this,IndexContext,UuidKey,ExKey);
}

VS_INT8 *Star_SRPI_DelIDKeyEx(void *c_this,void *IndexContext,VS_UUID *UuidKey,VS_UWORD ExKey)
{
    return g_star_CoreFunctionTbl->SRPI_DelIDKeyEx(c_this,IndexContext,UuidKey,ExKey);
}

VS_INT8 *Star_SRPI_QueryFirstIDKeyEx(void *c_this,void *IndexContext,VS_QUERYRECORD *QueryRecord,VS_UUID *UuidKey,VS_UWORD *ExKey)
{
    return g_star_CoreFunctionTbl->SRPI_QueryFirstIDKeyEx(c_this,IndexContext,QueryRecord,UuidKey,ExKey);
}

VS_INT8 *Star_SRPI_QueryNextIDKeyEx(void *c_this,void *IndexContext,VS_QUERYRECORD *QueryRecord,VS_UUID *UuidKey,VS_UWORD *ExKey)
{
    return g_star_CoreFunctionTbl->SRPI_QueryNextIDKeyEx(c_this,IndexContext,QueryRecord,UuidKey,ExKey);
}

VS_INT8 *Star_SRPI_QueryFirstIDKeyEx_F(void *c_this,void *IndexContext,VS_QUERYRECORD *QueryRecord,VS_UUID *UuidKey,VS_UWORD *ExKey)
{
    return g_star_CoreFunctionTbl->SRPI_QueryFirstIDKeyEx_F(c_this,IndexContext,QueryRecord,UuidKey,ExKey);
}

VS_INT8 *Star_SRPI_QueryNextIDKeyEx_F(void *c_this,void *IndexContext,VS_QUERYRECORD *QueryRecord,VS_UUID *UuidKey,VS_UWORD *ExKey)
{
    return g_star_CoreFunctionTbl->SRPI_QueryNextIDKeyEx_F(c_this,IndexContext,QueryRecord,UuidKey,ExKey);
}

VS_INT8 *Star_SRPI_QueryFirstIDKeyExA(void *c_this,void *IndexContext,VS_QUERYRECORD *QueryRecord,VS_UUID *UuidKey,VS_UWORD *ExKey)
{
    return g_star_CoreFunctionTbl->SRPI_QueryFirstIDKeyExA(c_this,IndexContext,QueryRecord,UuidKey,ExKey);
}

VS_INT8 *Star_SRPI_QueryNextIDKeyExA(void *c_this,void *IndexContext,VS_QUERYRECORD *QueryRecord,VS_UUID *UuidKey,VS_UWORD *ExKey)
{
    return g_star_CoreFunctionTbl->SRPI_QueryNextIDKeyExA(c_this,IndexContext,QueryRecord,UuidKey,ExKey);
}

VS_INT32 Star_SRPI_GetKeyNumber(void *c_this,void *IndexContext)
{
    return g_star_CoreFunctionTbl->SRPI_GetKeyNumber(c_this,IndexContext);
}

void Star_SRPI_DelAllKey(void *c_this,void *IndexContext)
{
    g_star_CoreFunctionTbl->SRPI_DelAllKey(c_this,IndexContext);
}

void Star_SRPI_DestoryIndex(void *c_this,void *IndexContext)
{
    g_star_CoreFunctionTbl->SRPI_DestoryIndex(c_this,IndexContext);
}

VS_ULONG Star_SRPI_GetHashValue(void *c_this,void *Key,VS_ULONG Length,VS_ULONG InitValue)
{
    return g_star_CoreFunctionTbl->SRPI_GetHashValue(c_this,Key,Length,InitValue);
}

void *Star_SRPI_CreateMemory_Nor(void *c_this,VS_INT32 ItemSize)
{
    return g_star_CoreFunctionTbl->SRPI_CreateMemory_Nor(c_this,ItemSize);
}

void *Star_SRPI_CreateMemory_Dbg(void *c_this,VS_INT32 ItemSize,const VS_CHAR *FileName,VS_INT32 LineNumber)
{
    return g_star_CoreFunctionTbl->SRPI_CreateMemory_Dbg(c_this,ItemSize,FileName,LineNumber);
}

void *Star_SRPI_GetMemoryPtr_Nor(void *c_this,void *MemoryContext)
{
    return g_star_CoreFunctionTbl->SRPI_GetMemoryPtr_Nor(c_this,MemoryContext);
}

void *Star_SRPI_GetMemoryPtr_Dbg(void *c_this,void *MemoryContext,const VS_CHAR *FileName,VS_INT32 LineNumber)
{
    return g_star_CoreFunctionTbl->SRPI_GetMemoryPtr_Dbg(c_this,MemoryContext,FileName,LineNumber);
}

void *Star_SRPI_QueryFirstMemoryPtr(void *c_this,void *MemoryContext,VS_QUERYRECORD *QueryRecord)
{
    return g_star_CoreFunctionTbl->SRPI_QueryFirstMemoryPtr(c_this,MemoryContext,QueryRecord);
}

void *Star_SRPI_QueryNextMemoryPtr(void *c_this,void *MemoryContext,VS_QUERYRECORD *QueryRecord)
{
    return g_star_CoreFunctionTbl->SRPI_QueryNextMemoryPtr(c_this,MemoryContext,QueryRecord);
}

void Star_SRPI_FreeMemoryPtr(void *c_this,void *MemoryContext,void *Ptr)
{
    g_star_CoreFunctionTbl->SRPI_FreeMemoryPtr(c_this,MemoryContext,Ptr);
}

void Star_SRPI_ClearMemory(void *c_this,void *MemoryContext)
{
    g_star_CoreFunctionTbl->SRPI_ClearMemory(c_this,MemoryContext);
}

void Star_SRPI_DestoryMemory(void *c_this,void *MemoryContext)
{
    g_star_CoreFunctionTbl->SRPI_DestoryMemory(c_this,MemoryContext);
}

void *Star_SRPI_Malloc_Nor(void *c_this,VS_INT32 MemorySize)
{
    return g_star_CoreFunctionTbl->SRPI_Malloc_Nor(c_this,MemorySize);
}

void *Star_SRPI_Malloc_Dbg(void *c_this,VS_INT32 MemorySize,const VS_CHAR *FileName,VS_INT32 LineNumber)
{
    return g_star_CoreFunctionTbl->SRPI_Malloc_Dbg(c_this,MemorySize,FileName,LineNumber);
}

void Star_SRPI_Free(void *c_this,void *MemoryPtr)
{
    g_star_CoreFunctionTbl->SRPI_Free(c_this,MemoryPtr);
}

void Star_SRPI_GetMemoryUsed(void *c_this, VS_UWORD *KernelAllocSize,VS_UWORD *DataAllocSize,VS_UWORD *AppAllocSize, VS_UWORD *ScriptMemoryUsed )
{
    g_star_CoreFunctionTbl->SRPI_GetMemoryUsed(c_this,KernelAllocSize,DataAllocSize,AppAllocSize,ScriptMemoryUsed);
}

void Star_SRPI_InjectSysEventFunction(void *c_this,VS_ULONG SysEventID,VSSystemEvent_EventProc ProcessFunctionProc)
{
    g_star_CoreFunctionTbl->SRPI_InjectSysEventFunction(c_this,SysEventID,ProcessFunctionProc);
}

void Star_SRPI_RejectSysEventFunction(void *c_this,VS_ULONG SysEventID,VSSystemEvent_EventProc ProcessFunctionProc)
{
    g_star_CoreFunctionTbl->SRPI_RejectSysEventFunction(c_this,SysEventID,ProcessFunctionProc);
}

VS_EVENTPARAM_RUNPARAM *Star_SRPI_GetResponseBuf(void *c_this)
{
    return g_star_CoreFunctionTbl->SRPI_GetResponseBuf(c_this);
}

VS_EVENTPARAM_RUNPARAM *Star_SRPI_GetRequestBuf(void *c_this)
{
    return g_star_CoreFunctionTbl->SRPI_GetRequestBuf(c_this);
}

VS_ULONG Star_SRPI_GetSysEventID(void *c_this,VS_EVENTPARAM *EventParam)
{
    return g_star_CoreFunctionTbl->SRPI_GetSysEventID(c_this,EventParam);
}

void Star_SRPI_FreeResponseBuf(void *c_this,VS_EVENTPARAM_RUNPARAM *ResponseParam)
{
    g_star_CoreFunctionTbl->SRPI_FreeResponseBuf(c_this,ResponseParam);
}

void Star_SRPI_FreeRequestBuf(void *c_this,VS_EVENTPARAM_RUNPARAM *RequestParam)
{
    g_star_CoreFunctionTbl->SRPI_FreeRequestBuf(c_this,RequestParam);
}

void Star_SRPI_AttachResponseBuf(void *c_this,VS_EVENTPARAM *EventParam,VS_EVENTPARAM_RUNPARAM *ResponseParam)
{
    g_star_CoreFunctionTbl->SRPI_AttachResponseBuf(c_this,EventParam,ResponseParam);
}

VS_EVENTPARAM_RUNPARAM *Star_SRPI_ProcessEvent_Nor(void *c_this,VS_UUID *EventID,void *SrcObject,void *DesObject,VS_EVENTPARAM_RUNPARAM *RequestParam)
{
    return g_star_CoreFunctionTbl->SRPI_ProcessEvent_Nor(c_this,EventID,SrcObject,DesObject,RequestParam);
}

VS_EVENTPARAM_RUNPARAM *Star_SRPI_ProcessEvent_Dbg(void *c_this,VS_UUID *EventID,void *SrcObject,void *DesObject,VS_EVENTPARAM_RUNPARAM *RequestParam)
{
    return g_star_CoreFunctionTbl->SRPI_ProcessEvent_Dbg(c_this,EventID,SrcObject,DesObject,RequestParam);
}

VS_EVENTPARAM_RUNPARAM *Star_SRPI_PostProcessEvent_Nor(void *c_this,VS_UUID *EventID,void *SrcObject,void *DesObject,VS_EVENTPARAM_RUNPARAM *RequestParam)
{
    return g_star_CoreFunctionTbl->SRPI_PostProcessEvent_Nor(c_this,EventID,SrcObject,DesObject,RequestParam);
}

VS_EVENTPARAM_RUNPARAM *Star_SRPI_PostProcessEvent_Dbg(void *c_this,VS_UUID *EventID,void *SrcObject,void *DesObject,VS_EVENTPARAM_RUNPARAM *RequestParam)
{
    return g_star_CoreFunctionTbl->SRPI_PostProcessEvent_Dbg(c_this,EventID,SrcObject,DesObject,RequestParam);
}

VS_EVENTPARAM_RUNPARAM *Star_SRPI_ProcessParentEvent(void *c_this,VS_EVENTPARAM *EventParam)
{
    return g_star_CoreFunctionTbl->SRPI_ProcessParentEvent(c_this,EventParam);
}

void Star_SRPI_SetEventAttachBuf(void *c_this,VS_EVENTPARAM_RUNPARAM *RunParam)
{
    g_star_CoreFunctionTbl->SRPI_SetEventAttachBuf(c_this,RunParam);
}

VS_BOOL Star_SRPI_RegEventFunction(void *c_this,void *SrcObject,VS_UUID *EventID, void *Object, void *FuncAddr,VS_UWORD Para)
{
    return g_star_CoreFunctionTbl->SRPI_RegEventFunction(c_this,SrcObject,EventID,Object,FuncAddr,Para);
}

void Star_SRPI_UnRegEventFunction(void *c_this,void *SrcObject,VS_UUID *EventID, void *Object, void *FuncAddr,VS_UWORD Para )
{
    g_star_CoreFunctionTbl->SRPI_UnRegEventFunction(c_this,SrcObject,EventID,Object,FuncAddr,Para);
}

VS_BOOL Star_SRPI_RegSysEventFunction(void *c_this,void *Object,VS_ULONG SysEventID, void *FuncAddr,VS_UWORD Para )
{
    return g_star_CoreFunctionTbl->SRPI_RegSysEventFunction(c_this,Object,SysEventID,FuncAddr,Para);
}

void Star_SRPI_UnRegSysEventFunction(void *c_this,void *Object,VS_ULONG SysEventID, void *FuncAddr,VS_UWORD Para )
{
    g_star_CoreFunctionTbl->SRPI_UnRegSysEventFunction(c_this,Object,SysEventID,FuncAddr,Para);
}

VS_BOOL Star_SRPI_ActiveCmd(void *c_this,void *Object,VS_UINT8 ActiveCmd)
{
    return g_star_CoreFunctionTbl->SRPI_ActiveCmd(c_this,Object,ActiveCmd);
}

VS_UINT8 Star_SRPI_GetActiveCmd(void *c_this,void *Object)
{
    return g_star_CoreFunctionTbl->SRPI_GetActiveCmd(c_this,Object);
}

VS_BOOL Star_SRPI_ActiveClient(void *c_this,VS_ULONG ClientID,void *Object)
{
    return g_star_CoreFunctionTbl->SRPI_ActiveClient(c_this,ClientID,Object);
}

void Star_SRPI_DeactiveClient(void *c_this,VS_ULONG ClientID,void *Object)
{
    g_star_CoreFunctionTbl->SRPI_DeactiveClient(c_this,ClientID,Object);
}

VS_BOOL Star_SRPI_Active(void *c_this,void *Object)
{
    return g_star_CoreFunctionTbl->SRPI_Active(c_this,Object);
}

void Star_SRPI_Deactive(void *c_this,void *Object)
{
    g_star_CoreFunctionTbl->SRPI_Deactive(c_this,Object);
}

void Star_SRPI_DeactiveAll(void *c_this)
{
    g_star_CoreFunctionTbl->SRPI_DeactiveAll(c_this);
}

VS_BOOL Star_SRPI_IsActive(void *c_this,void *Object)
{
    return g_star_CoreFunctionTbl->SRPI_IsActive(c_this,Object);
}

void *Star_SRPI_QueryFirstActiveInst(void *c_this,VS_QUERYRECORD *QueryRecord,VS_UUID *ObjectClassID)
{
    return g_star_CoreFunctionTbl->SRPI_QueryFirstActiveInst(c_this,QueryRecord,ObjectClassID);
}

void *Star_SRPI_QueryNextActiveInst(void *c_this,VS_QUERYRECORD *QueryRecord,VS_UUID *ObjectClassID)
{
    return g_star_CoreFunctionTbl->SRPI_QueryNextActiveInst(c_this,QueryRecord,ObjectClassID);
}

VS_BOOL Star_SRPI_SetClientObject(void *c_this,VS_ULONG ClientID,void *Object)
{
    return g_star_CoreFunctionTbl->SRPI_SetClientObject(c_this,ClientID,Object);
}

void *Star_SRPI_GetClientObject(void *c_this)
{
    return g_star_CoreFunctionTbl->SRPI_GetClientObject(c_this);
}

VS_BOOL Star_SRPI_CreateSysRootItem(void *c_this, const VS_CHAR *SystemRootItemName, const VS_CHAR *DependSysRootItem, VS_UUID *SystemRootItemID, VS_UUID *SystemRootItemIDEx )
{
    return g_star_CoreFunctionTbl->SRPI_CreateSysRootItem(c_this,SystemRootItemName,DependSysRootItem,SystemRootItemID,SystemRootItemIDEx);
}

void Star_SRPI_ActiveAllSysRootItem(void *c_this)
{
    g_star_CoreFunctionTbl->SRPI_ActiveAllSysRootItem(c_this);
}

void Star_SRPI_ActiveSysRootItem(void *c_this, const VS_CHAR *SystemRootItemName )
{
    g_star_CoreFunctionTbl->SRPI_ActiveSysRootItem(c_this,SystemRootItemName);
}

void Star_SRPI_DeactiveSysRootItem(void *c_this,const VS_CHAR *SystemRootItemName)
{
    g_star_CoreFunctionTbl->SRPI_DeactiveSysRootItem(c_this,SystemRootItemName);
}

void Star_SRPI_ActiveCSysRootItem(void *c_this, VS_ULONG ClientID,const VS_CHAR *SystemRootItemName )
{
    g_star_CoreFunctionTbl->SRPI_ActiveCSysRootItem(c_this,ClientID,SystemRootItemName);
}

void Star_SRPI_DeactiveCSysRootItem(void *c_this, VS_ULONG ClientID,const VS_CHAR *SystemRootItemName)
{
    g_star_CoreFunctionTbl->SRPI_DeactiveCSysRootItem(c_this,ClientID,SystemRootItemName);
}

void *Star_SRPI_GetSysRootItem(void *c_this,const VS_CHAR *SystemRootItemName)
{
    return g_star_CoreFunctionTbl->SRPI_GetSysRootItem(c_this,SystemRootItemName);
}

void *Star_SRPI_GetSysRootItemEx(void *c_this,VS_UUID *SystemRootItemID)
{
    return g_star_CoreFunctionTbl->SRPI_GetSysRootItemEx(c_this,SystemRootItemID);
}

VS_CHAR *Star_SRPI_GetSysRootItemName(void *c_this,void  *SystemRootItem)
{
    return g_star_CoreFunctionTbl->SRPI_GetSysRootItemName(c_this,SystemRootItem);
}

void Star_SRPI_GetSysRootItemActiveSet(void *c_this,void  *SystemRootItem,VS_ACTIVESETITEM *ActiveSetPtr)
{
    g_star_CoreFunctionTbl->SRPI_GetSysRootItemActiveSet(c_this,SystemRootItem,ActiveSetPtr);
}

void Star_SRPI_SetSysRootItemActiveSet(void *c_this,void  *SystemRootItem,VS_ACTIVESETITEM *ActiveSetItem)
{
    g_star_CoreFunctionTbl->SRPI_SetSysRootItemActiveSet(c_this,SystemRootItem,ActiveSetItem);
}

void Star_SRPI_SetCSysRootItemActiveSet(void *c_this,VS_ULONG ClientID,void  *SystemRootItem,VS_ACTIVESETITEM *ActiveSetItem)
{
    g_star_CoreFunctionTbl->SRPI_SetCSysRootItemActiveSet(c_this,ClientID,SystemRootItem,ActiveSetItem);
}

VS_CHAR *Star_SRPI_QueryFirstSysRootItem(void *c_this)
{
    return g_star_CoreFunctionTbl->SRPI_QueryFirstSysRootItem(c_this);
}

VS_CHAR *Star_SRPI_QueryNextSysRootItem(void *c_this)
{
    return g_star_CoreFunctionTbl->SRPI_QueryNextSysRootItem(c_this);
}

void *Star_SRPI_QueryFirstGroupObject(void *c_this,void *SystemRootItem,VS_SYNCGROUP GroupIndex,VS_UWORD *QueryGroupContext)
{
    return g_star_CoreFunctionTbl->SRPI_QueryFirstGroupObject(c_this,SystemRootItem,GroupIndex,QueryGroupContext);
}

void *Star_SRPI_QueryNextGroupObject(void *c_this,VS_UWORD *QueryGroupContext)
{
    return g_star_CoreFunctionTbl->SRPI_QueryNextGroupObject(c_this,QueryGroupContext);
}

void *Star_SRPI_QueryFirstSysRootItemChild(void *c_this, void  *SystemRootItem )
{
    return g_star_CoreFunctionTbl->SRPI_QueryFirstSysRootItemChild(c_this,SystemRootItem);
}

VS_BOOL Star_SRPI_RegClientSysRootItemToSyncFunc(void *c_this,void  *SystemRootItem,VS_ClientSysRootItemChangeToSyncProc FuncPtr, VS_UWORD Para)
{
    return g_star_CoreFunctionTbl->SRPI_RegClientSysRootItemToSyncFunc(c_this,SystemRootItem,FuncPtr,Para);
}

void Star_SRPI_UnRegClientSysRootItemToSyncFunc(void *c_this,void  *SystemRootItem,VS_ClientSysRootItemChangeToSyncProc FuncPtr, VS_UWORD Para)
{
    g_star_CoreFunctionTbl->SRPI_UnRegClientSysRootItemToSyncFunc(c_this,SystemRootItem,FuncPtr,Para);
}

void Star_SRPI_InitEdit(void *c_this,void *ClassObject,void *Object)
{
    g_star_CoreFunctionTbl->SRPI_InitEdit(c_this,ClassObject,Object);
}

void Star_SRPI_TermEdit(void *c_this,void *ClassObject,void *Object)
{
    g_star_CoreFunctionTbl->SRPI_TermEdit(c_this,ClassObject,Object);
}

VS_BOOL Star_SRPI_GetEditMode(void *c_this,void *Object)
{
    return g_star_CoreFunctionTbl->SRPI_GetEditMode(c_this,Object);
}

void Star_SRPI_SetEditMode(void *c_this,void *Object,VS_BOOL EditFlag)
{
    g_star_CoreFunctionTbl->SRPI_SetEditMode(c_this,Object,EditFlag);
}

void Star_SRPI_EditCommit(void *c_this)
{
    g_star_CoreFunctionTbl->SRPI_EditCommit(c_this);
}

void Star_SRPI_EditSelect(void *c_this,void *Object)
{
    g_star_CoreFunctionTbl->SRPI_EditSelect(c_this,Object);
}

void Star_SRPI_EditChange(void *c_this,void *Object,OBJECTATTRIBUTEINDEX AttributeIndex,const VS_INT8 *NewValue)
{
    g_star_CoreFunctionTbl->SRPI_EditChange(c_this,Object,AttributeIndex,NewValue);
}

void Star_SRPI_EditMarkChange(void *c_this,void *Object,OBJECTATTRIBUTEINDEX AttributeIndex)
{
    g_star_CoreFunctionTbl->SRPI_EditMarkChange(c_this,Object,AttributeIndex);
}

void Star_SRPI_EditSetSaveFlag(void *c_this,void *Object,VS_UINT8 SaveFlag)
{
    g_star_CoreFunctionTbl->SRPI_EditSetSaveFlag(c_this,Object,SaveFlag);
}

void Star_SRPI_EditSetName(void *c_this,void *Object,const VS_CHAR *Name)
{
    g_star_CoreFunctionTbl->SRPI_EditSetName(c_this,Object,Name);
}

void Star_SRPI_FillAttachBuf(void *c_this,VS_UUID *ObjectClassID,VS_INT8 *AttachBuf,VS_INT32 AttachBufSize)
{
    g_star_CoreFunctionTbl->SRPI_FillAttachBuf(c_this,ObjectClassID,AttachBuf,AttachBufSize);
}

VS_BOOL Star_SRPI_IsEditProcExist(void *c_this,void *Object)
{
    return g_star_CoreFunctionTbl->SRPI_IsEditProcExist(c_this,Object);
}

void Star_SRPI_TriggerEditProc(void *c_this,void *ClassObject,void *Object,VS_UWORD AppCode,VS_UWORD AppCode1)
{
    g_star_CoreFunctionTbl->SRPI_TriggerEditProc(c_this,ClassObject,Object,AppCode,AppCode1);
}

void Star_SRPI_EditDelete(void *c_this,void *Object)
{
    g_star_CoreFunctionTbl->SRPI_EditDelete(c_this,Object);
}

void *Star_SRPI_EditCreate(void *c_this,VS_UUID *ObjectClassID,VS_UUID *ParentObjectID,OBJECTATTRIBUTEINDEX AttributeIndex,VS_ULONG OrderIndex,VS_UINT8 ObjectSaveFlag,VS_INT32 AttachBufSize,void *AttachBuf)
{
    return g_star_CoreFunctionTbl->SRPI_EditCreate(c_this,ObjectClassID,ParentObjectID,AttributeIndex,OrderIndex,ObjectSaveFlag,AttachBufSize,AttachBuf);
}

void *Star_SRPI_EditCreateEx(void *c_this,VS_UUID *ObjectClassID,VS_UUID *ObjectID,VS_UUID *ParentObjectID,OBJECTATTRIBUTEINDEX AttributeIndex,VS_ULONG OrderIndex,VS_UINT8 ObjectSaveFlag,VS_INT32 AttachBufSize,void *AttachBuf)
{
    return g_star_CoreFunctionTbl->SRPI_EditCreateEx(c_this,ObjectClassID,ObjectID,ParentObjectID,AttributeIndex,OrderIndex,ObjectSaveFlag,AttachBufSize,AttachBuf);
}

void Star_SRPI_EditChangeParent(void *c_this,void *Object,void *ParentObject,OBJECTATTRIBUTEINDEX AttributeIndex)
{
    g_star_CoreFunctionTbl->SRPI_EditChangeParent(c_this,Object,ParentObject,AttributeIndex);
}

void Star_SRPI_EditChangeSyncGroup(void *c_this,void *Object,VS_SYNCGROUP GroupIndex)
{
    g_star_CoreFunctionTbl->SRPI_EditChangeSyncGroup(c_this,Object,GroupIndex);
}

void Star_SRPI_EditGetClassID(void *c_this,VS_UUID *ObjectID,OBJECTATTRIBUTEINDEX AttributeIndex,VS_UUID *UuidPtr)
{
    g_star_CoreFunctionTbl->SRPI_EditGetClassID(c_this,ObjectID,AttributeIndex,UuidPtr);
}

void Star_SRPI_EditGetInstID(void *c_this,VS_UUID *ObjectClassID,VS_UUID *UuidPtr)
{
    g_star_CoreFunctionTbl->SRPI_EditGetInstID(c_this,ObjectClassID,UuidPtr);
}

void Star_SRPI_EditSetWndStatus(void *c_this,VS_BOOL Normal)
{
    g_star_CoreFunctionTbl->SRPI_EditSetWndStatus(c_this,Normal);
}

VS_BOOL Star_SRPI_EditUpdateObjectScript(void *c_this, void *Object, const VS_CHAR *ScriptName,const VS_CHAR *ScriptBuf )
{
    return g_star_CoreFunctionTbl->SRPI_EditUpdateObjectScript(c_this,Object,ScriptName,ScriptBuf);
}

VS_BOOL Star_SRPI_EditUpdateObjectScriptEx(void *c_this, void *Object, const VS_CHAR *ScriptName,const VS_CHAR *FileName )
{
    return g_star_CoreFunctionTbl->SRPI_EditUpdateObjectScriptEx(c_this,Object,ScriptName,FileName);
}

VS_BOOL Star_SRPI_RegClientOpFunction(void *c_this,VS_ClientOperationCallBackProc ClientOperationCallBackProc,VS_UWORD Para)
{
    return g_star_CoreFunctionTbl->SRPI_RegClientOpFunction(c_this,ClientOperationCallBackProc,Para);
}

void Star_SRPI_UnRegClientOpFunction(void *c_this,VS_ClientOperationCallBackProc ClientOperationCallBackProc,VS_UWORD Para)
{
    g_star_CoreFunctionTbl->SRPI_UnRegClientOpFunction(c_this,ClientOperationCallBackProc,Para);
}

void Star_SRPI_Redirect(void *c_this, VS_ULONG ClientID,const VS_CHAR *DesServerInterface,const VS_CHAR *DesServerName,VS_UINT16 DesServerPortNumber, void *ParaPkg,VS_RedirectCallBackProc RedirectCallBackProc,VS_UWORD Para )
{
    g_star_CoreFunctionTbl->SRPI_Redirect(c_this,ClientID,DesServerInterface,DesServerName,DesServerPortNumber,ParaPkg,RedirectCallBackProc,Para);
}

void *Star_SRPI_GetServiceMachine(void *c_this)
{
    return g_star_CoreFunctionTbl->SRPI_GetServiceMachine(c_this);
}

void Star_SRPI_DelMachine(void *c_this,void *Machine)
{
    g_star_CoreFunctionTbl->SRPI_DelMachine(c_this,Machine);
}

VS_INT8 *Star_SRPI_GetMachineAttachBuf(void *c_this,void *Machine)
{
    return g_star_CoreFunctionTbl->SRPI_GetMachineAttachBuf(c_this,Machine);
}

void Star_SRPI_SetMachineAttachBuf(void *c_this,void *Machine,VS_INT8 *AppBuf)
{
    g_star_CoreFunctionTbl->SRPI_SetMachineAttachBuf(c_this,Machine,AppBuf);
}

VS_ULONG Star_SRPI_GetMachineID(void *c_this,void *Machine)
{
    return g_star_CoreFunctionTbl->SRPI_GetMachineID(c_this,Machine);
}

void *Star_SRPI_FindMachine(void *c_this,VS_ULONG MachineID)
{
    return g_star_CoreFunctionTbl->SRPI_FindMachine(c_this,MachineID);
}

VS_BOOL Star_SRPI_RegClientMachineProcess(void *c_this,void *CallBackPtr,void *Object,VS_UWORD Para)
{
    return g_star_CoreFunctionTbl->SRPI_RegClientMachineProcess(c_this,CallBackPtr,Object,Para);
}

void Star_SRPI_UnRegClientMachineProcess(void *c_this,void *CallBackPtr,void *Object,VS_UWORD Para)
{
    g_star_CoreFunctionTbl->SRPI_UnRegClientMachineProcess(c_this,CallBackPtr,Object,Para);
}

void Star_SRPI_ClientInitError(void *c_this,void *Machine)
{
    g_star_CoreFunctionTbl->SRPI_ClientInitError(c_this,Machine);
}

void Star_SRPI_ClientInitOk(void *c_this,void *Machine,VS_BOOL ReSyncFlag,const VS_CHAR *TermOldScript,const VS_CHAR *InitNewScript,VS_ULONG ClientPrivateTag,VS_ULONG ClientOPPermission,VS_ULONG ClientUploadMaxSize)
{
    g_star_CoreFunctionTbl->SRPI_ClientInitOk(c_this,Machine,ReSyncFlag,TermOldScript,InitNewScript,ClientPrivateTag,ClientOPPermission,ClientUploadMaxSize);
}

void Star_SRPI_DeleteClient(void *c_this,void *Machine)
{
    g_star_CoreFunctionTbl->SRPI_DeleteClient(c_this,Machine);
}

void Star_SRPI_GetClientInfo(void *c_this,void *Machine,VS_CLIENTINFO *ClientInfo)
{
    g_star_CoreFunctionTbl->SRPI_GetClientInfo(c_this,Machine,ClientInfo);
}

VS_BOOL Star_SRPI_QueryFirstClientInfo(void *c_this,VS_CLIENTINFO *ClientInfo)
{
    return g_star_CoreFunctionTbl->SRPI_QueryFirstClientInfo(c_this,ClientInfo);
}

VS_BOOL Star_SRPI_QueryNextClientInfo(void *c_this,VS_CLIENTINFO *ClientInfo)
{
    return g_star_CoreFunctionTbl->SRPI_QueryNextClientInfo(c_this,ClientInfo);
}

VS_INT32 Star_SRPI_GetClientNumber(void *c_this)
{
    return g_star_CoreFunctionTbl->SRPI_GetClientNumber(c_this);
}

void Star_SRPI_GetClientQos(void *c_this,void *Machine,VS_CLIENTQOS *QosBuf)
{
    g_star_CoreFunctionTbl->SRPI_GetClientQos(c_this,Machine,QosBuf);
}

void Star_SRPI_SetClientQos(void *c_this,void *Machine,VS_CLIENTQOS *QosBuf)
{
    g_star_CoreFunctionTbl->SRPI_SetClientQos(c_this,Machine,QosBuf);
}

void Star_SRPI_GetServiceQos(void *c_this,VS_CLIENTQOS *QosBuf)
{
    g_star_CoreFunctionTbl->SRPI_GetServiceQos(c_this,QosBuf);
}

VS_BOOL Star_SRPI_DownLoad(void *c_this, void *AttachObject,const VS_CHAR *ServerPath,const VS_CHAR *ClientPath,const VS_CHAR *FileName, VS_FileUpDownLoadCallBackProc CallBackProc, void *Object, VS_UWORD Para )
{
    return g_star_CoreFunctionTbl->SRPI_DownLoad(c_this,AttachObject,ServerPath,ClientPath,FileName,CallBackProc,Object,Para);
}

VS_BOOL Star_SRPI_UpLoad(void *c_this, void *AttachObject,const VS_CHAR *ServerPath,const VS_CHAR *ClientPath,const VS_CHAR *FileName, VS_FileUpDownLoadCallBackProc CallBackProc, void *Object, VS_UWORD Para )
{
    return g_star_CoreFunctionTbl->SRPI_UpLoad(c_this,AttachObject,ServerPath,ClientPath,FileName,CallBackProc,Object,Para);
}

void Star_SRPI_GetFileInfo(void *c_this, VS_UPDOWNFILEINFO *InfoPtr )
{
    g_star_CoreFunctionTbl->SRPI_GetFileInfo(c_this,InfoPtr);
}

VS_BOOL Star_SRPI_RegFileCallBack(void *c_this, VS_FileUpDownLoadCallBackProc CallBackProc, void *Object, VS_UWORD Para )
{
    return g_star_CoreFunctionTbl->SRPI_RegFileCallBack(c_this,CallBackProc,Object,Para);
}

void Star_SRPI_UnRegFileCallBack(void *c_this, VS_FileUpDownLoadCallBackProc CallBackProc, void *Object, VS_UWORD Para )
{
    g_star_CoreFunctionTbl->SRPI_UnRegFileCallBack(c_this,CallBackProc,Object,Para);
}

VS_INT32 Star_SRPI_GetFileStatus(void *c_this, VS_CHAR *FileName, VS_UPDOWNFILEMSG *FileInfo )
{
    return g_star_CoreFunctionTbl->SRPI_GetFileStatus(c_this,FileName,FileInfo);
}

VS_INT32 Star_SRPI_GetDataStatus(void *c_this, void *Object,VS_ULONG UniqueDataUnitID, VS_UPDOWNFILEMSG *FileInfo )
{
    return g_star_CoreFunctionTbl->SRPI_GetDataStatus(c_this,Object,UniqueDataUnitID,FileInfo);
}

VS_BOOL Star_SRPI_QueryFirstDown(void *c_this, VS_QUERYRECORD *QueryRecord, VS_UPDOWNFILEMSG *FileInfo )
{
    return g_star_CoreFunctionTbl->SRPI_QueryFirstDown(c_this,QueryRecord,FileInfo);
}

VS_BOOL Star_SRPI_QueryNextDown(void *c_this, VS_QUERYRECORD *QueryRecord, VS_UPDOWNFILEMSG *FileInfo )
{
    return g_star_CoreFunctionTbl->SRPI_QueryNextDown(c_this,QueryRecord,FileInfo);
}

VS_BOOL Star_SRPI_QueryFirstUp(void *c_this, VS_QUERYRECORD *QueryRecord, VS_UPDOWNFILEMSG *FileInfo )
{
    return g_star_CoreFunctionTbl->SRPI_QueryFirstUp(c_this,QueryRecord,FileInfo);
}

VS_BOOL Star_SRPI_QueryNextUp(void *c_this, VS_QUERYRECORD *QueryRecord, VS_UPDOWNFILEMSG *FileInfo )
{
    return g_star_CoreFunctionTbl->SRPI_QueryNextUp(c_this,QueryRecord,FileInfo);
}

VS_INT8 *Star_SRPI_GetStaticData(void *c_this, void *Object,VS_ULONG UniqueDataUnitID,VS_STATICID *DataVersion,VS_ULONG *DataSize, VS_BOOL AutoDownLoad)
{
    return g_star_CoreFunctionTbl->SRPI_GetStaticData(c_this,Object,UniqueDataUnitID,DataVersion,DataSize,AutoDownLoad);
}

VS_INT8 *Star_SRPI_GetStaticDataEx(void *c_this, void *Object,VS_ULONG UniqueDataUnitID,VS_STATICID *DataVersion,VS_ULONG *DataSize, VS_BOOL AutoDownLoad,VS_CHAR *Token)
{
    return g_star_CoreFunctionTbl->SRPI_GetStaticDataEx(c_this,Object,UniqueDataUnitID,DataVersion,DataSize,AutoDownLoad,Token);
}

VS_BOOL Star_SRPI_CanSetStaticData(void *c_this,void *Object,VS_ULONG DataSize)
{
    return g_star_CoreFunctionTbl->SRPI_CanSetStaticData(c_this,Object,DataSize);
}

VS_BOOL Star_SRPI_SetStaticData(void *c_this, void *Object,VS_ULONG UniqueDataUnitID,VS_ULONG DataSize,VS_INT8 *DataBuf,VS_STATICID *RetDataVersion)
{
    return g_star_CoreFunctionTbl->SRPI_SetStaticData(c_this,Object,UniqueDataUnitID,DataSize,DataBuf,RetDataVersion);
}

VS_BOOL Star_SRPI_SetStaticDataEx(void *c_this, void *Object,VS_ULONG UniqueDataUnitID,VS_ULONG *DataSize,VS_ULONG Offset,VS_CHAR *FileName,VS_STATICID *RetDataVersion)
{
    return g_star_CoreFunctionTbl->SRPI_SetStaticDataEx(c_this,Object,UniqueDataUnitID,DataSize,Offset,FileName,RetDataVersion);
}

VS_ULONG Star_SRPI_GetStaticAppCode(void *c_this, void *Object,OBJECTATTRIBUTEINDEX StaticPersistentAttributeIndex)
{
    return g_star_CoreFunctionTbl->SRPI_GetStaticAppCode(c_this,Object,StaticPersistentAttributeIndex);
}

VS_BOOL Star_SRPI_WaitGetStaticData(void *c_this, void *Object,VS_ULONG UniqueDataUnitID,VS_FileUpDownLoadCallBackProc CallBackProc,VS_UWORD Para,VS_BOOL WaitFlag)
{
    return g_star_CoreFunctionTbl->SRPI_WaitGetStaticData(c_this,Object,UniqueDataUnitID,CallBackProc,Para,WaitFlag);
}

VS_BOOL Star_SRPI_WaitSetStaticData(void *c_this, void *Object,VS_ULONG UniqueDataUnitID,VS_FileUpDownLoadCallBackProc CallBackProc,VS_UWORD Para,VS_BOOL WaitFlag)
{
    return g_star_CoreFunctionTbl->SRPI_WaitSetStaticData(c_this,Object,UniqueDataUnitID,CallBackProc,Para,WaitFlag);
}

void Star_SRPI_PackStaticData(void *c_this)
{
    g_star_CoreFunctionTbl->SRPI_PackStaticData(c_this);
}

void Star_SRPI_ForceToSaveStatic(void *c_this)
{
    g_star_CoreFunctionTbl->SRPI_ForceToSaveStatic(c_this);
}

void Star_SRPI_ClearStatic(void *c_this,VS_UINT16 BeforeDays)
{
    g_star_CoreFunctionTbl->SRPI_ClearStatic(c_this,BeforeDays);
}

void Star_SRPI_GetStaticVersion(void *c_this, VS_ULONG DataSize,VS_INT8 *DataBuf,VS_STATICID *RetDataVersion)
{
    g_star_CoreFunctionTbl->SRPI_GetStaticVersion(c_this,DataSize,DataBuf,RetDataVersion);
}

VS_UINT16 Star_SRPI_GetProgramType(void *c_this)
{
    return g_star_CoreFunctionTbl->SRPI_GetProgramType(c_this);
}

VS_BOOL Star_SRPI_IsDefaultServer(void *c_this)
{
    return g_star_CoreFunctionTbl->SRPI_IsDefaultServer(c_this);
}

VS_BOOL Star_SRPI_IsWindowVisible(void *c_this)
{
    return g_star_CoreFunctionTbl->SRPI_IsWindowVisible(c_this);
}

void Star_SRPI_HideWindow(void *c_this)
{
    g_star_CoreFunctionTbl->SRPI_HideWindow(c_this);
}

void Star_SRPI_ShowWindow(void *c_this)
{
    g_star_CoreFunctionTbl->SRPI_ShowWindow(c_this);
}

void Star_SRPI_SetWindowCaption(void *c_this,const VS_CHAR *Caption)
{
    g_star_CoreFunctionTbl->SRPI_SetWindowCaption(c_this,Caption);
}

void Star_SRPI_ExitVSSystem(void *c_this,const VS_CHAR *ErrorInfo)
{
    g_star_CoreFunctionTbl->SRPI_ExitVSSystem(c_this,ErrorInfo);
}

VS_BOOL Star_SRPI_IsAppActive(void *c_this)
{
    return g_star_CoreFunctionTbl->SRPI_IsAppActive(c_this);
}

void Star_SRPI_SetIdleActive(void *c_this,VS_BOOL CreateFlag)
{
    g_star_CoreFunctionTbl->SRPI_SetIdleActive(c_this,CreateFlag);
}

void Star_SRPI_GetVersion(void *c_this,VS_UINT8 *MainVersion,VS_UINT8 *SubVersion,VS_UINT16 *BuildVersion)
{
    g_star_CoreFunctionTbl->SRPI_GetVersion(c_this,MainVersion,SubVersion,BuildVersion);
}

void Star_SRPI_GetVersionInfo(void *c_this,VS_CHAR *InfoBuf,VS_INT32 InfoBufSize)
{
    g_star_CoreFunctionTbl->SRPI_GetVersionInfo(c_this,InfoBuf,InfoBufSize);
}

VS_HWND Star_SRPI_GetWindowHandle(void *c_this)
{
    return g_star_CoreFunctionTbl->SRPI_GetWindowHandle(c_this);
}

void Star_SRPI_GetWindowSize(void *c_this, VS_INT32 *Width, VS_INT32 *Height )
{
    g_star_CoreFunctionTbl->SRPI_GetWindowSize(c_this,Width,Height);
}

void Star_SRPI_SetColor(void *c_this, VS_COLOR Text,VS_COLOR Explane,VS_COLOR ObjName,VS_COLOR AttrType,VS_COLOR Number,VS_COLOR Error )
{
    g_star_CoreFunctionTbl->SRPI_SetColor(c_this,Text,Explane,ObjName,AttrType,Number,Error);
}

void Star_SRPI_SetBkColor(void *c_this, VS_COLOR BkColor )
{
    g_star_CoreFunctionTbl->SRPI_SetBkColor(c_this,BkColor);
}

void Star_SRPI_ShowStatusMenu(void *c_this, VS_BOOL MenuShowFlag, VS_BOOL StatusShowFlag )
{
    g_star_CoreFunctionTbl->SRPI_ShowStatusMenu(c_this,MenuShowFlag,StatusShowFlag);
}

VS_HWND Star_SRPI_GetClientWndHandle(void *c_this)
{
    return g_star_CoreFunctionTbl->SRPI_GetClientWndHandle(c_this);
}

void Star_SRPI_GetClientWndSize(void *c_this, VS_INT32 *Width, VS_INT32 *Height )
{
    g_star_CoreFunctionTbl->SRPI_GetClientWndSize(c_this,Width,Height);
}

void Star_SRPI_SetClientWndSize(void *c_this, VS_INT32 Width, VS_INT32 Height )
{
    g_star_CoreFunctionTbl->SRPI_SetClientWndSize(c_this,Width,Height);
}

void Star_SRPI_SetClientWndFocus(void *c_this, VS_HWND hWnd, VS_BOOL NeedAction )
{
    g_star_CoreFunctionTbl->SRPI_SetClientWndFocus(c_this,hWnd,NeedAction);
}

void Star_SRPI_ClearClientWnd(void *c_this)
{
    g_star_CoreFunctionTbl->SRPI_ClearClientWnd(c_this);
}

void Star_SRPI_HideClientWnd(void *c_this)
{
    g_star_CoreFunctionTbl->SRPI_HideClientWnd(c_this);
}

void Star_SRPI_ShowClientWnd(void *c_this)
{
    g_star_CoreFunctionTbl->SRPI_ShowClientWnd(c_this);
}

void Star_SRPI_SetClientBkColor(void *c_this, VS_COLOR BkColor )
{
    g_star_CoreFunctionTbl->SRPI_SetClientBkColor(c_this,BkColor);
}

void Star_SRPI_SetRunEnv_FromChildCallBack(void *c_this, void *Object,VS_RunEnvCallBackProc CallBack,VS_UWORD Para)
{
    g_star_CoreFunctionTbl->SRPI_SetRunEnv_FromChildCallBack(c_this,Object,CallBack,Para);
}

void Star_SRPI_SetRunEnv_FromParentCallBack(void *c_this, void *Object,VS_RunEnvCallBackProc CallBack,VS_UWORD Para)
{
    g_star_CoreFunctionTbl->SRPI_SetRunEnv_FromParentCallBack(c_this,Object,CallBack,Para);
}

void Star_SRPI_RegRunEnv_FromParentCallBack(void *c_this, void *Object, void *ParentObject, VS_RunEnvCallBackProc CallBack,VS_UWORD Para)
{
    g_star_CoreFunctionTbl->SRPI_RegRunEnv_FromParentCallBack(c_this,Object,ParentObject,CallBack,Para);
}

void Star_SRPI_UnRegRunEnv_FromParentCallBack(void *c_this, void *Object, void *ParentObject, VS_RunEnvCallBackProc CallBack,VS_UWORD Para)
{
    g_star_CoreFunctionTbl->SRPI_UnRegRunEnv_FromParentCallBack(c_this,Object,ParentObject,CallBack,Para);
}

VS_BOOL Star_SRPI_RunEnvToChild(void *c_this,void *Object, void *DesObject, struct StructOfVSRunEnv *RunEnvInfo)
{
    return g_star_CoreFunctionTbl->SRPI_RunEnvToChild(c_this,Object,DesObject,RunEnvInfo);
}

VS_BOOL Star_SRPI_RunEnvToParent(void *c_this,void *Object, struct StructOfVSRunEnv *RunEnvInfo)
{
    return g_star_CoreFunctionTbl->SRPI_RunEnvToParent(c_this,Object,RunEnvInfo);
}

void Star_SRPI_SetMessageHook(void *c_this,VS_SRPMessageProcessHookProc HookProc)
{
    g_star_CoreFunctionTbl->SRPI_SetMessageHook(c_this,HookProc);
}

void *Star_SRPI_GetMessageHook(void *c_this)
{
    return g_star_CoreFunctionTbl->SRPI_GetMessageHook(c_this);
}

VS_BOOL Star_SRPI_RegLuaFunc(void *c_this, void *Object, const VS_CHAR *FuncName, void *FuncAddress, VS_UWORD Para)
{
    return g_star_CoreFunctionTbl->SRPI_RegLuaFunc(c_this,Object,FuncName,FuncAddress,Para);
}

void Star_SRPI_UnRegLuaFunc(void *c_this, void *Object, const VS_CHAR *FuncName, void *FuncAddress, VS_UWORD Para )
{
    g_star_CoreFunctionTbl->SRPI_UnRegLuaFunc(c_this,Object,FuncName,FuncAddress,Para);
}

void Star_SRPI_UnRegLuaFuncEx(void *c_this, void *Object, void *FuncAddress, VS_UWORD Para )
{
    g_star_CoreFunctionTbl->SRPI_UnRegLuaFuncEx(c_this,Object,FuncAddress,Para);
}

void Star_SRPI_ValidRegLuaFunc(void *c_this, void *Object, const VS_CHAR *FuncName, void *FuncAddress, VS_UWORD Para )
{
    g_star_CoreFunctionTbl->SRPI_ValidRegLuaFunc(c_this,Object,FuncName,FuncAddress,Para);
}

void Star_SRPI_InValidRegLuaFunc(void *c_this, void *Object, const VS_CHAR *FuncName, void *FuncAddress, VS_UWORD Para )
{
    g_star_CoreFunctionTbl->SRPI_InValidRegLuaFunc(c_this,Object,FuncName,FuncAddress,Para);
}

VS_BOOL Star_SRPI_RegLuaGetValueFunc(void *c_this, void *Object, VS_LuaGetValueProc GetValueProc, VS_UWORD Para )
{
    return g_star_CoreFunctionTbl->SRPI_RegLuaGetValueFunc(c_this,Object,GetValueProc,Para);
}

VS_BOOL Star_SRPI_RegLuaSetValueFunc(void *c_this, void *Object, VS_LuaSetValueProc SetValueProc, VS_UWORD Para )
{
    return g_star_CoreFunctionTbl->SRPI_RegLuaSetValueFunc(c_this,Object,SetValueProc,Para);
}

VS_BOOL Star_SRPI_UnRegLuaGetValueFunc(void *c_this, void *Object, VS_LuaGetValueProc GetValueProc, VS_UWORD Para )
{
    return g_star_CoreFunctionTbl->SRPI_UnRegLuaGetValueFunc(c_this,Object,GetValueProc,Para);
}

VS_BOOL Star_SRPI_UnRegLuaSetValueFunc(void *c_this, void *Object, VS_LuaSetValueProc SetValueProc, VS_UWORD Para )
{
    return g_star_CoreFunctionTbl->SRPI_UnRegLuaSetValueFunc(c_this,Object,SetValueProc,Para);
}

void Star_SRPI_ValidLuaGetValueFunc(void *c_this, void *Object, VS_LuaGetValueProc GetValueProc, VS_UWORD Para )
{
    g_star_CoreFunctionTbl->SRPI_ValidLuaGetValueFunc(c_this,Object,GetValueProc,Para);
}

void Star_SRPI_ValidLuaSetValueFunc(void *c_this, void *Object, VS_LuaSetValueProc SetValueProc, VS_UWORD Para )
{
    g_star_CoreFunctionTbl->SRPI_ValidLuaSetValueFunc(c_this,Object,SetValueProc,Para);
}

void Star_SRPI_InValidLuaGetValueFunc(void *c_this, void *Object, VS_LuaGetValueProc GetValueProc, VS_UWORD Para )
{
    g_star_CoreFunctionTbl->SRPI_InValidLuaGetValueFunc(c_this,Object,GetValueProc,Para);
}

void Star_SRPI_InValidLuaSetValueFunc(void *c_this, void *Object, VS_LuaSetValueProc SetValueProc, VS_UWORD Para )
{
    g_star_CoreFunctionTbl->SRPI_InValidLuaSetValueFunc(c_this,Object,SetValueProc,Para);
}

void *Star_SRPI_GetLua(void *c_this)
{
    return g_star_CoreFunctionTbl->SRPI_GetLua(c_this);
}

VS_BOOL Star_SRPI_DoBuffer(void *c_this, const VS_CHAR *ScriptInterface,const VS_INT8 *ScriptBuf,VS_INT32 ScriptBufSize,const VS_CHAR *ModuleName, VS_CHAR **ErrorInfo, const VS_CHAR *WorkDirectory, VS_BOOL IsUTF8 )
{
    return g_star_CoreFunctionTbl->SRPI_DoBuffer(c_this,ScriptInterface,ScriptBuf,ScriptBufSize,ModuleName,ErrorInfo,WorkDirectory,IsUTF8);
}

VS_BOOL Star_SRPI_DoFile(void *c_this, const VS_CHAR *ScriptInterface,const VS_CHAR *FileName, VS_CHAR **ErrorInfo, const VS_CHAR *WorkDirectory, VS_BOOL IsUTF8 )
{
    return g_star_CoreFunctionTbl->SRPI_DoFile(c_this,ScriptInterface,FileName,ErrorInfo,WorkDirectory,IsUTF8);
}

void Star_SRPI_LuaNewUserData(void *c_this, VS_INT32 Size )
{
    g_star_CoreFunctionTbl->SRPI_LuaNewUserData(c_this,Size);
}

void Star_SRPI_LuaSetUserDataGC(void *c_this, VS_LuaUserDataGCProc GCProc )
{
    g_star_CoreFunctionTbl->SRPI_LuaSetUserDataGC(c_this,GCProc);
}

void *Star_SRPI_LuaToUserData(void *c_this, VS_INT32 Index )
{
    return g_star_CoreFunctionTbl->SRPI_LuaToUserData(c_this,Index);
}

void Star_SRPI_LuaNewTable(void *c_this)
{
    g_star_CoreFunctionTbl->SRPI_LuaNewTable(c_this);
}

VS_INT32 Star_SRPI_LuaGetTop(void *c_this)
{
    return g_star_CoreFunctionTbl->SRPI_LuaGetTop(c_this);
}

VS_INT32 Star_SRPI_LuaNext(void *c_this, VS_INT32 Index )
{
    return g_star_CoreFunctionTbl->SRPI_LuaNext(c_this,Index);
}

void Star_SRPI_LuaPop(void *c_this, VS_INT32 Index )
{
    g_star_CoreFunctionTbl->SRPI_LuaPop(c_this,Index);
}

void Star_SRPI_LuaPushBool(void *c_this, VS_BOOL Value )
{
    g_star_CoreFunctionTbl->SRPI_LuaPushBool(c_this,Value);
}

void Star_SRPI_LuaPushString(void *c_this, const VS_CHAR *Value )
{
    g_star_CoreFunctionTbl->SRPI_LuaPushString(c_this,Value);
}

void Star_SRPI_LuaPushNumber(void *c_this, VS_DOUBLE Value )
{
    g_star_CoreFunctionTbl->SRPI_LuaPushNumber(c_this,Value);
}

void Star_SRPI_LuaPushInt(void *c_this, VS_INT32 Value )
{
    g_star_CoreFunctionTbl->SRPI_LuaPushInt(c_this,Value);
}

void Star_SRPI_LuaPushNil(void *c_this)
{
    g_star_CoreFunctionTbl->SRPI_LuaPushNil(c_this);
}

VS_BOOL Star_SRPI_LuaPushObject(void *c_this, void *Object )
{
    return g_star_CoreFunctionTbl->SRPI_LuaPushObject(c_this,Object);
}

VS_BOOL Star_SRPI_LuaPushParaPkg(void *c_this, void *ParaPkg, VS_BOOL AutoRelease )
{
    return g_star_CoreFunctionTbl->SRPI_LuaPushParaPkg(c_this,ParaPkg,AutoRelease);
}

VS_BOOL Star_SRPI_LuaPushQueryRecord(void *c_this, VS_QUERYRECORD *QueryRecord, VS_BOOL AutoRelease )
{
    return g_star_CoreFunctionTbl->SRPI_LuaPushQueryRecord(c_this,QueryRecord,AutoRelease);
}

VS_BOOL Star_SRPI_LuaPushRect(void *c_this, VS_RECT *rEct )
{
    return g_star_CoreFunctionTbl->SRPI_LuaPushRect(c_this,rEct);
}

VS_BOOL Star_SRPI_LuaPushFont(void *c_this, VS_FONT *hFont )
{
    return g_star_CoreFunctionTbl->SRPI_LuaPushFont(c_this,hFont);
}

VS_BOOL Star_SRPI_LuaPushTime(void *c_this, VS_TIME *hTime )
{
    return g_star_CoreFunctionTbl->SRPI_LuaPushTime(c_this,hTime);
}

void Star_SRPI_LuaPushFunction(void *c_this, void *FunctionAddr )
{
    g_star_CoreFunctionTbl->SRPI_LuaPushFunction(c_this,FunctionAddr);
}

void Star_SRPI_LuaPushClosure(void *c_this, void *FunctionAddr, VS_INT32 n )
{
    g_star_CoreFunctionTbl->SRPI_LuaPushClosure(c_this,FunctionAddr,n);
}

VS_INT32 Star_SRPI_LuaUpValueIndex(void *c_this, VS_INT32 Index )
{
    return g_star_CoreFunctionTbl->SRPI_LuaUpValueIndex(c_this,Index);
}

void Star_SRPI_LuaPushValue(void *c_this, VS_INT32 Index )
{
    g_star_CoreFunctionTbl->SRPI_LuaPushValue(c_this,Index);
}

void Star_SRPI_LuaInsert(void *c_this, VS_INT32 Index )
{
    g_star_CoreFunctionTbl->SRPI_LuaInsert(c_this,Index);
}

void Star_SRPI_LuaRemove(void *c_this, VS_INT32 Index )
{
    g_star_CoreFunctionTbl->SRPI_LuaRemove(c_this,Index);
}

VS_BOOL Star_SRPI_LuaPCall(void *c_this, VS_INT32 nargs, VS_INT32 nresults )
{
    return g_star_CoreFunctionTbl->SRPI_LuaPCall(c_this,nargs,nresults);
}

void Star_SRPI_LuaRCall(void *c_this,VS_ULONG ClientID,void *Object, const VS_CHAR *ScriptName, VS_INT32 nArgs)
{
    g_star_CoreFunctionTbl->SRPI_LuaRCall(c_this,ClientID,Object,ScriptName,nArgs);
}

void Star_SRPI_LuaRCallEx(void *c_this,VS_ULONG ExcludeClientID,void *Object, const VS_CHAR *ScriptName, VS_INT32 nArgs)
{
    g_star_CoreFunctionTbl->SRPI_LuaRCallEx(c_this,ExcludeClientID,Object,ScriptName,nArgs);
}

VS_BOOL Star_SRPI_LuaSRCall(void *c_this,VS_ULONG WaitTime,VS_ULONG ClientID,void *Object, const VS_CHAR *ScriptName, VS_INT32 nArgs, VS_INT32 *OutArgs)
{
    return g_star_CoreFunctionTbl->SRPI_LuaSRCall(c_this,WaitTime,ClientID,Object,ScriptName,nArgs,OutArgs);
}

VS_BOOL Star_SRPI_LuaARCall(void *c_this,VS_ULONG WaitTime,VS_ULONG ClientID,void *Object, void *CallBackProc, VS_UWORD Para, const VS_CHAR *ScriptName, VS_INT32 nArgs)
{
    return g_star_CoreFunctionTbl->SRPI_LuaARCall(c_this,WaitTime,ClientID,Object,CallBackProc,Para,ScriptName,nArgs);
}

VS_INT32 Star_SRPI_LuaRegEvent(void *c_this,void *SrcObject,VS_UUID *EventID, void *Object, void *FuncAddr)
{
    return g_star_CoreFunctionTbl->SRPI_LuaRegEvent(c_this,SrcObject,EventID,Object,FuncAddr);
}

void Star_SRPI_LuaUnRegEvent(void *c_this,void *SrcObject,VS_UUID *EventID, void *Object, VS_INT32 FuncRefValue )
{
    g_star_CoreFunctionTbl->SRPI_LuaUnRegEvent(c_this,SrcObject,EventID,Object,FuncRefValue);
}

VS_BOOL Star_SRPI_LuaProcessEvent(void *c_this,void *Object,VS_UUID *EventID, VS_INT32 nArgs, VS_INT32 *OutArgs )
{
    return g_star_CoreFunctionTbl->SRPI_LuaProcessEvent(c_this,Object,EventID,nArgs,OutArgs);
}

VS_BOOL Star_SRPI_LuaPostProcessEvent(void *c_this,void *Object,VS_UUID *EventID, VS_INT32 nArgs, VS_INT32 *OutArgs )
{
    return g_star_CoreFunctionTbl->SRPI_LuaPostProcessEvent(c_this,Object,EventID,nArgs,OutArgs);
}

VS_BOOL Star_SRPI_LuaCall(void *c_this, void *Object, const VS_CHAR *ScriptName, VS_INT32 nArgs,VS_INT32 nOutArgs )
{
    return g_star_CoreFunctionTbl->SRPI_LuaCall(c_this,Object,ScriptName,nArgs,nOutArgs);
}

void Star_SRPI_LuaRegHook(void *c_this, void *FuncAddr )
{
    g_star_CoreFunctionTbl->SRPI_LuaRegHook(c_this,FuncAddr);
}

void Star_SRPI_LuaUnRegHook(void *c_this, void *FuncAddr )
{
    g_star_CoreFunctionTbl->SRPI_LuaUnRegHook(c_this,FuncAddr);
}

VS_INT32 Star_SRPI_LuaType(void *c_this, VS_INT32 Index )
{
    return g_star_CoreFunctionTbl->SRPI_LuaType(c_this,Index);
}

VS_BOOL Star_SRPI_LuaToBool(void *c_this, VS_INT32 Index )
{
    return g_star_CoreFunctionTbl->SRPI_LuaToBool(c_this,Index);
}

VS_CHAR *Star_SRPI_LuaToString(void *c_this, VS_INT32 Index )
{
    return g_star_CoreFunctionTbl->SRPI_LuaToString(c_this,Index);
}

VS_DOUBLE Star_SRPI_LuaToNumber(void *c_this, VS_INT32 Index )
{
    return g_star_CoreFunctionTbl->SRPI_LuaToNumber(c_this,Index);
}

VS_INT32 Star_SRPI_LuaToInt(void *c_this, VS_INT32 Index )
{
    return g_star_CoreFunctionTbl->SRPI_LuaToInt(c_this,Index);
}

void *Star_SRPI_LuaToObject(void *c_this, VS_INT32 Index )
{
    return g_star_CoreFunctionTbl->SRPI_LuaToObject(c_this,Index);
}

void *Star_SRPI_LuaToParaPkg(void *c_this, VS_INT32 Index )
{
    return g_star_CoreFunctionTbl->SRPI_LuaToParaPkg(c_this,Index);
}

VS_QUERYRECORD *Star_SRPI_LuaToQueryRecord(void *c_this, VS_INT32 Index )
{
    return g_star_CoreFunctionTbl->SRPI_LuaToQueryRecord(c_this,Index);
}

VS_BOOL Star_SRPI_LuaToRect(void *c_this, VS_INT32 Index, VS_RECT *rEct )
{
    return g_star_CoreFunctionTbl->SRPI_LuaToRect(c_this,Index,rEct);
}

VS_BOOL Star_SRPI_LuaToFont(void *c_this, VS_INT32 Index, VS_FONT *hFont )
{
    return g_star_CoreFunctionTbl->SRPI_LuaToFont(c_this,Index,hFont);
}

VS_BOOL Star_SRPI_LuaToTime(void *c_this, VS_INT32 Index, VS_TIME *hTime )
{
    return g_star_CoreFunctionTbl->SRPI_LuaToTime(c_this,Index,hTime);
}

VS_BOOL Star_SRPI_LuaIsBool(void *c_this, VS_INT32 Index )
{
    return g_star_CoreFunctionTbl->SRPI_LuaIsBool(c_this,Index);
}

VS_BOOL Star_SRPI_LuaIsString(void *c_this, VS_INT32 Index )
{
    return g_star_CoreFunctionTbl->SRPI_LuaIsString(c_this,Index);
}

VS_BOOL Star_SRPI_LuaIsNumber(void *c_this, VS_INT32 Index )
{
    return g_star_CoreFunctionTbl->SRPI_LuaIsNumber(c_this,Index);
}

VS_BOOL Star_SRPI_LuaIsTable(void *c_this, VS_INT32 Index )
{
    return g_star_CoreFunctionTbl->SRPI_LuaIsTable(c_this,Index);
}

VS_BOOL Star_SRPI_LuaIsNil(void *c_this, VS_INT32 Index )
{
    return g_star_CoreFunctionTbl->SRPI_LuaIsNil(c_this,Index);
}

VS_BOOL Star_SRPI_LuaIsObject(void *c_this, VS_INT32 Index )
{
    return g_star_CoreFunctionTbl->SRPI_LuaIsObject(c_this,Index);
}

VS_BOOL Star_SRPI_LuaIsParaPkg(void *c_this, VS_INT32 Index )
{
    return g_star_CoreFunctionTbl->SRPI_LuaIsParaPkg(c_this,Index);
}

VS_BOOL Star_SRPI_LuaIsQueryRecord(void *c_this, VS_INT32 Index )
{
    return g_star_CoreFunctionTbl->SRPI_LuaIsQueryRecord(c_this,Index);
}

VS_BOOL Star_SRPI_LuaIsCFunction(void *c_this, VS_INT32 Index )
{
    return g_star_CoreFunctionTbl->SRPI_LuaIsCFunction(c_this,Index);
}

VS_BOOL Star_SRPI_LuaIsFunction(void *c_this, VS_INT32 Index )
{
    return g_star_CoreFunctionTbl->SRPI_LuaIsFunction(c_this,Index);
}

VS_BOOL Star_SRPI_LuaIsFont(void *c_this, VS_INT32 Index )
{
    return g_star_CoreFunctionTbl->SRPI_LuaIsFont(c_this,Index);
}

VS_BOOL Star_SRPI_LuaIsRect(void *c_this, VS_INT32 Index )
{
    return g_star_CoreFunctionTbl->SRPI_LuaIsRect(c_this,Index);
}

VS_BOOL Star_SRPI_LuaIsTime(void *c_this, VS_INT32 Index )
{
    return g_star_CoreFunctionTbl->SRPI_LuaIsTime(c_this,Index);
}

VS_BOOL Star_SRPI_LuaSetTable(void *c_this, VS_INT32 Index )
{
    return g_star_CoreFunctionTbl->SRPI_LuaSetTable(c_this,Index);
}

VS_BOOL Star_SRPI_LuaGetTable(void *c_this, VS_INT32 Index )
{
    return g_star_CoreFunctionTbl->SRPI_LuaGetTable(c_this,Index);
}

void Star_SRPI_LuaSetGlobal(void *c_this, const VS_CHAR *Name )
{
    g_star_CoreFunctionTbl->SRPI_LuaSetGlobal(c_this,Name);
}

void Star_SRPI_LuaGetGlobal(void *c_this, const VS_CHAR *Name )
{
    g_star_CoreFunctionTbl->SRPI_LuaGetGlobal(c_this,Name);
}

VS_INT32 Star_SRPI_LuaSetRef(void *c_this, void *Object, VS_INT32 Index)
{
    return g_star_CoreFunctionTbl->SRPI_LuaSetRef(c_this,Object,Index);
}

void Star_SRPI_LuaClearRef(void *c_this, void *Object, VS_INT32 LuaRefValue )
{
    g_star_CoreFunctionTbl->SRPI_LuaClearRef(c_this,Object,LuaRefValue);
}

void Star_SRPI_LuaGetRef(void *c_this, void *Object,VS_INT32 LuaRefValue )
{
    g_star_CoreFunctionTbl->SRPI_LuaGetRef(c_this,Object,LuaRefValue);
}

VS_INT32 Star_SRPI_LuaInsertTable2(void *c_this,VS_INT32 TableIndex)
{
    return g_star_CoreFunctionTbl->SRPI_LuaInsertTable2(c_this,TableIndex);
}

void Star_SRPI_LuaRemoveTable2(void *c_this,VS_INT32 TableIndex,VS_INT32 Pos)
{
    g_star_CoreFunctionTbl->SRPI_LuaRemoveTable2(c_this,TableIndex,Pos);
}

void Star_SRPI_LuaPushLString(void *c_this, const VS_CHAR *Value, VS_ULONG Len )
{
    g_star_CoreFunctionTbl->SRPI_LuaPushLString(c_this,Value,Len);
}

VS_BOOL Star_SRPI_LuaObjectNewTempTable(void *c_this, void *Object, const VS_CHAR *Name )
{
    return g_star_CoreFunctionTbl->SRPI_LuaObjectNewTempTable(c_this,Object,Name);
}

VS_BOOL Star_SRPI_LuaObjectIsLock(void *c_this, void *Object )
{
    return g_star_CoreFunctionTbl->SRPI_LuaObjectIsLock(c_this,Object);
}

void Star_SRPI_LuaObjectLock(void *c_this, void *Object )
{
    g_star_CoreFunctionTbl->SRPI_LuaObjectLock(c_this,Object);
}

void Star_SRPI_LuaObjectUnLock(void *c_this, void *Object )
{
    g_star_CoreFunctionTbl->SRPI_LuaObjectUnLock(c_this,Object);
}

VS_BOOL Star_SRPI_GetValueFromLua(void *c_this,const VS_CHAR *String)
{
    return g_star_CoreFunctionTbl->SRPI_GetValueFromLua(c_this,String);
}

VS_BOOL Star_SRPI_LuaPushBinBuf(void *c_this, void *BinBuf, VS_BOOL AutoRelease )
{
    return g_star_CoreFunctionTbl->SRPI_LuaPushBinBuf(c_this,BinBuf,AutoRelease);
}

void *Star_SRPI_LuaToBinBuf(void *c_this, VS_INT32 Index )
{
    return g_star_CoreFunctionTbl->SRPI_LuaToBinBuf(c_this,Index);
}

VS_BOOL Star_SRPI_LuaIsBinBuf(void *c_this, VS_INT32 Index )
{
    return g_star_CoreFunctionTbl->SRPI_LuaIsBinBuf(c_this,Index);
}

VS_BOOL Star_SRPI_DefLuaFunction(void *c_this, void *Object, const VS_CHAR *ScriptName )
{
    return g_star_CoreFunctionTbl->SRPI_DefLuaFunction(c_this,Object,ScriptName);
}

VS_BOOL Star_SRPI_SaveToLuaFunc(void *c_this, void *Object, const VS_CHAR *LuaFileName, const VS_CHAR *FuncName )
{
    return g_star_CoreFunctionTbl->SRPI_SaveToLuaFunc(c_this,Object,LuaFileName,FuncName);
}

VS_BOOL Star_SRPI_LuaPushSXml(void *c_this, void *SXml, VS_BOOL AutoRelease )
{
    return g_star_CoreFunctionTbl->SRPI_LuaPushSXml(c_this,SXml,AutoRelease);
}

void *Star_SRPI_LuaToSXml(void *c_this, VS_INT32 Index )
{
    return g_star_CoreFunctionTbl->SRPI_LuaToSXml(c_this,Index);
}

VS_BOOL Star_SRPI_LuaIsSXml(void *c_this, VS_INT32 Index )
{
    return g_star_CoreFunctionTbl->SRPI_LuaIsSXml(c_this,Index);
}

VS_BOOL Star_SRPI_LuaPushFunctionPara(void *c_this, void *FunctionPara, VS_BOOL AutoRelease )
{
    return g_star_CoreFunctionTbl->SRPI_LuaPushFunctionPara(c_this,FunctionPara,AutoRelease);
}

void *Star_SRPI_LuaToFunctionPara(void *c_this, VS_INT32 Index )
{
    return g_star_CoreFunctionTbl->SRPI_LuaToFunctionPara(c_this,Index);
}

VS_BOOL Star_SRPI_LuaIsFunctionPara(void *c_this, VS_INT32 Index )
{
    return g_star_CoreFunctionTbl->SRPI_LuaIsFunctionPara(c_this,Index);
}

VS_BOOL Star_SRPI_LuaPushCommInterface(void *c_this, void *CommInterface, VS_BOOL AutoRelease )
{
    return g_star_CoreFunctionTbl->SRPI_LuaPushCommInterface(c_this,CommInterface,AutoRelease);
}

void *Star_SRPI_LuaToCommInterface(void *c_this, VS_INT32 Index )
{
    return g_star_CoreFunctionTbl->SRPI_LuaToCommInterface(c_this,Index);
}

VS_BOOL Star_SRPI_LuaIsCommInterface(void *c_this, VS_INT32 Index )
{
    return g_star_CoreFunctionTbl->SRPI_LuaIsCommInterface(c_this,Index);
}

void Star_SRPI_LuaInsertTable(void *c_this,VS_INT32 TableIndex,VS_INT32 Pos)
{
    g_star_CoreFunctionTbl->SRPI_LuaInsertTable(c_this,TableIndex,Pos);
}

void Star_SRPI_LuaRemoveTable(void *c_this,VS_INT32 TableIndex,VS_INT32 Pos)
{
    g_star_CoreFunctionTbl->SRPI_LuaRemoveTable(c_this,TableIndex,Pos);
}

VS_INT32 Star_SRPI_LuaObjLen(void *c_this,VS_INT32 TableIndex)
{
    return g_star_CoreFunctionTbl->SRPI_LuaObjLen(c_this,TableIndex);
}

void Star_SRPI_LuaGetTablei(void *c_this,VS_INT32 TableIndex,VS_INT32 Pos)
{
    g_star_CoreFunctionTbl->SRPI_LuaGetTablei(c_this,TableIndex,Pos);
}

void Star_SRPI_LuaSetTablei(void *c_this,VS_INT32 TableIndex,VS_INT32 Pos)
{
    g_star_CoreFunctionTbl->SRPI_LuaSetTablei(c_this,TableIndex,Pos);
}

void Star_SRPI_LuaInitObject(void *c_this,void *Object,const VS_CHAR *InitScript)
{
    g_star_CoreFunctionTbl->SRPI_LuaInitObject(c_this,Object,InitScript);
}

VS_CHAR *Star_SRPI_GetAttributeLuaString(void *c_this,void *Object)
{
    return g_star_CoreFunctionTbl->SRPI_GetAttributeLuaString(c_this,Object);
}

VS_BOOL Star_SRPI_LockGC(void *c_this,void *Object)
{
    return g_star_CoreFunctionTbl->SRPI_LockGC(c_this,Object);
}

VS_BOOL Star_SRPI_UnLockGC(void *c_this,void *Object)
{
    return g_star_CoreFunctionTbl->SRPI_UnLockGC(c_this,Object);
}

void *Star_SRPI_GetObjectFromLua(void *c_this,const VS_CHAR *String)
{
    return g_star_CoreFunctionTbl->SRPI_GetObjectFromLua(c_this,String);
}

void Star_SRPI_GCCollect(void *c_this)
{
    g_star_CoreFunctionTbl->SRPI_GCCollect(c_this);
}

VS_CHAR *Star_SRPI_GetRegStr(void *c_this,const VS_CHAR *SubKey,const VS_CHAR *ValueName,const VS_CHAR *DefaultValue)
{
    return g_star_CoreFunctionTbl->SRPI_GetRegStr(c_this,SubKey,ValueName,DefaultValue);
}

VS_UINT32 Star_SRPI_GetRegInt(void *c_this,const VS_CHAR *SubKey,const VS_CHAR *ValueName,VS_UINT32 DefaultValue)
{
    return g_star_CoreFunctionTbl->SRPI_GetRegInt(c_this,SubKey,ValueName,DefaultValue);
}

VS_ULONG Star_SRPI_SetupTimer(void *c_this,VS_INT32 Ticket,VS_TimerProc FunctionAddr,void *Object,VS_UWORD Para1,VS_UWORD Para2,VS_UWORD Para3,VS_UWORD Para4 )
{
    return g_star_CoreFunctionTbl->SRPI_SetupTimer(c_this,Ticket,FunctionAddr,Object,Para1,Para2,Para3,Para4);
}

void Star_SRPI_KillTimer(void *c_this,VS_ULONG TimerID)
{
    g_star_CoreFunctionTbl->SRPI_KillTimer(c_this,TimerID);
}

VS_UWORD Star_SRPI_GetTickCount(void *c_this)
{
    return g_star_CoreFunctionTbl->SRPI_GetTickCount(c_this);
}

VS_INT8 *Star_SRPI_GetMD5(void *c_this,VS_INT8 *Buf,VS_INT32 BufSize)
{
    return g_star_CoreFunctionTbl->SRPI_GetMD5(c_this,Buf,BufSize);
}

VS_BOOL Star_SRPI_MD5ToUuid(void *c_this,const VS_INT8 *String,VS_UUID *Uuid)
{
    return g_star_CoreFunctionTbl->SRPI_MD5ToUuid(c_this,String,Uuid);
}

VS_INT8 *Star_SRPI_UuidToMD5(void *c_this,VS_UUID *Uuid)
{
    return g_star_CoreFunctionTbl->SRPI_UuidToMD5(c_this,Uuid);
}

void Star_SRPI_CreateUuid(void *c_this,VS_UUID *UuidPtr)
{
    g_star_CoreFunctionTbl->SRPI_CreateUuid(c_this,UuidPtr);
}

void Star_SRPI_GetSRPTempPath(void *c_this,VS_ULONG BufSize,VS_CHAR *Buf)
{
    g_star_CoreFunctionTbl->SRPI_GetSRPTempPath(c_this,BufSize,Buf);
}

VS_INT8 *Star_SRPI_StringToUtf8(void *c_this,const VS_INT8 *String)
{
    return g_star_CoreFunctionTbl->SRPI_StringToUtf8(c_this,String);
}

VS_INT8 *Star_SRPI_Utf8ToString(void *c_this,const VS_INT8 *String)
{
    return g_star_CoreFunctionTbl->SRPI_Utf8ToString(c_this,String);
}

void Star_SRPI_SetExceptHandler(void *c_this,VS_ExceptHandlerProc ExceptHandlerProc)
{
    g_star_CoreFunctionTbl->SRPI_SetExceptHandler(c_this,ExceptHandlerProc);
}

void Star_SRPI_SRPLock(void *c_this)
{
    g_star_CoreFunctionTbl->SRPI_SRPLock(c_this);
}

void Star_SRPI_SRPUnLock(void *c_this)
{
    g_star_CoreFunctionTbl->SRPI_SRPUnLock(c_this);
}

VS_BOOL Star_SRPI_Compress(void *c_this,VS_UINT8 *dest,VS_ULONG *destLen,VS_UINT8 *source,VS_ULONG sourceLen )
{
    return g_star_CoreFunctionTbl->SRPI_Compress(c_this,dest,destLen,source,sourceLen);
}

VS_BOOL Star_SRPI_UnCompress(void *c_this,VS_UINT8 *dest,VS_ULONG *destLen,VS_UINT8 *source,VS_ULONG sourceLen )
{
    return g_star_CoreFunctionTbl->SRPI_UnCompress(c_this,dest,destLen,source,sourceLen);
}

VS_BOOL Star_SRPI_IsSysRootItemSync(void *c_this,void  *SystemRootItem)
{
    return g_star_CoreFunctionTbl->SRPI_IsSysRootItemSync(c_this,SystemRootItem);
}

VS_BOOL Star_SRPI_WaitSysRootItemSync(void *c_this,void  *SystemRootItem)
{
    return g_star_CoreFunctionTbl->SRPI_WaitSysRootItemSync(c_this,SystemRootItem);
}

void *Star_SRPI_GetAtomicService(void *c_this)
{
    return g_star_CoreFunctionTbl->SRPI_GetAtomicService(c_this);
}

void *Star_SRPI_CreateAtomicSysRootItem(void *c_this, const VS_CHAR *SysRootItemName, const VS_CHAR *DependSysRootItem,VS_UUID *SystemRootItemID, VS_UUID *SystemRootItemIDEx )
{
    return g_star_CoreFunctionTbl->SRPI_CreateAtomicSysRootItem(c_this,SysRootItemName,DependSysRootItem,SystemRootItemID,SystemRootItemIDEx);
}

void *Star_SRPI_GetAtomicSysRootItem(void *c_this, const VS_CHAR *SysRootItemName )
{
    return g_star_CoreFunctionTbl->SRPI_GetAtomicSysRootItem(c_this,SysRootItemName);
}

void *Star_SRPI_GetAtomicObject(void *c_this, VS_UUID *UuidPtr )
{
    return g_star_CoreFunctionTbl->SRPI_GetAtomicObject(c_this,UuidPtr);
}

void *Star_SRPI_GetAtomicObjectEx(void *c_this, void *ParentAtomicObject, const VS_CHAR *ObjectName )
{
    return g_star_CoreFunctionTbl->SRPI_GetAtomicObjectEx(c_this,ParentAtomicObject,ObjectName);
}

void *Star_SRPI_GetAtomicClass(void *c_this,void *AtomicObject)
{
    return g_star_CoreFunctionTbl->SRPI_GetAtomicClass(c_this,AtomicObject);
}

void Star_SRPI_GetAtomicID(void *c_this,void *AtomicObject,VS_UUID *UuidPtr)
{
    g_star_CoreFunctionTbl->SRPI_GetAtomicID(c_this,AtomicObject,UuidPtr);
}

VS_CHAR *Star_SRPI_GetAtomicName(void *c_this,void *AtomicObject)
{
    return g_star_CoreFunctionTbl->SRPI_GetAtomicName(c_this,AtomicObject);
}

void *Star_SRPI_AtomicToObject(void *c_this,void *AtomicObject)
{
    return g_star_CoreFunctionTbl->SRPI_AtomicToObject(c_this,AtomicObject);
}

void *Star_SRPI_ObjectToAtomic(void *c_this,void *Object)
{
    return g_star_CoreFunctionTbl->SRPI_ObjectToAtomic(c_this,Object);
}

void Star_SRPI_FreeAtomicObject(void *c_this,void *Object)
{
    g_star_CoreFunctionTbl->SRPI_FreeAtomicObject(c_this,Object);
}

void *Star_SRPI_CreateAtomicObjectSimple(void *c_this, const VS_CHAR *SysRootItemName,const VS_CHAR *ObjectName,const VS_CHAR *Attribute, VS_UUID *ObjectID, VS_CHAR **ErrorInfo )
{
    return g_star_CoreFunctionTbl->SRPI_CreateAtomicObjectSimple(c_this,SysRootItemName,ObjectName,Attribute,ObjectID,ErrorInfo);
}

void *Star_SRPI_CreateAtomicObjectAttributeSimple(void *c_this, void *AtomicObject,const VS_CHAR *Attribute, VS_CHAR **ErrorInfo )
{
    return g_star_CoreFunctionTbl->SRPI_CreateAtomicObjectAttributeSimple(c_this,AtomicObject,Attribute,ErrorInfo);
}

void *Star_SRPI_CreateAtomicStructSimple(void *c_this, const VS_CHAR *StructName,const VS_CHAR *Attribute, VS_UUID *ObjectID, VS_CHAR **ErrorInfo )
{
    return g_star_CoreFunctionTbl->SRPI_CreateAtomicStructSimple(c_this,StructName,Attribute,ObjectID,ErrorInfo);
}

void *Star_SRPI_CreateAtomicFunctionSimple(void *c_this, void *AtomicObject, const VS_CHAR *FunctionName,const VS_CHAR *Attribute, VS_UUID *ObjectID, VS_CHAR **ErrorInfo, VS_BOOL StdCallFlag,VS_BOOL GlobalFunctionFlag )
{
    return g_star_CoreFunctionTbl->SRPI_CreateAtomicFunctionSimple(c_this,AtomicObject,FunctionName,Attribute,ObjectID,ErrorInfo,StdCallFlag,GlobalFunctionFlag);
}

void Star_SRPI_SetAtomicFunction(void *c_this,void *AtomicFunction,void *FuncAddress)
{
    g_star_CoreFunctionTbl->SRPI_SetAtomicFunction(c_this,AtomicFunction,FuncAddress);
}

void *Star_SRPI_CreateAtomicMacro(void *c_this, const VS_CHAR *MacroName, VS_UINT8 MacroType )
{
    return g_star_CoreFunctionTbl->SRPI_CreateAtomicMacro(c_this,MacroName,MacroType);
}

void *Star_SRPI_CreateAtomicMacroItem(void *c_this, void *MacroObject,const VS_CHAR *MacroItemName, const VS_CHAR *MacroItemValue )
{
    return g_star_CoreFunctionTbl->SRPI_CreateAtomicMacroItem(c_this,MacroObject,MacroItemName,MacroItemValue);
}

void *Star_SRPI_CreateAtomicModule(void *c_this, const VS_CHAR *ModuleName,VS_UINT16 ModuleType,VS_UUID *ModuleID )
{
    return g_star_CoreFunctionTbl->SRPI_CreateAtomicModule(c_this,ModuleName,ModuleType,ModuleID);
}

void *Star_SRPI_CreateAtomicEditModule(void *c_this, const VS_CHAR *ModuleName,VS_UUID *ModuleID )
{
    return g_star_CoreFunctionTbl->SRPI_CreateAtomicEditModule(c_this,ModuleName,ModuleID);
}

void *Star_SRPI_CreateAtomicStruct(void *c_this, const VS_CHAR *StructName,const VS_CHAR *StructCaption,VS_UUID *StructID )
{
    return g_star_CoreFunctionTbl->SRPI_CreateAtomicStruct(c_this,StructName,StructCaption,StructID);
}

void *Star_SRPI_CreateAtomicObject(void *c_this, void *AtomicObject, OBJECTATTRIBUTEINDEX AtomicAttributeIndex, void *AtomicClassObject, const VS_CHAR *ObjectName, VS_UUID *ObjectID )
{
    return g_star_CoreFunctionTbl->SRPI_CreateAtomicObject(c_this,AtomicObject,AtomicAttributeIndex,AtomicClassObject,ObjectName,ObjectID);
}

void *Star_SRPI_CreateAtomicAttachAttribute(void *c_this, void *AtomicObject, const VS_CHAR *AttributeName, const VS_CHAR *Caption, VS_UINT8 Type, VS_ULONG StaticID, VS_UINT8 SyncFlag,VS_UINT8 CreateFlag,VS_UINT8 NotifyFlag,VS_UINT8 EditType,VS_UINT8 EditControl,VS_UINT8 EditReadOnly,const VS_CHAR *Default,const VS_CHAR *Desc)
{
    return g_star_CoreFunctionTbl->SRPI_CreateAtomicAttachAttribute(c_this,AtomicObject,AttributeName,Caption,Type,StaticID,SyncFlag,CreateFlag,NotifyFlag,EditType,EditControl,EditReadOnly,Default,Desc);
}

void *Star_SRPI_CreateAtomicAttribute(void *c_this, void *AtomicObject, const VS_CHAR *AttributeName, const VS_CHAR *Caption, VS_UINT8 Type, VS_ULONG StaticID, VS_UINT8 SyncFlag,VS_UINT8 CreateFlag,VS_UINT8 NotifyFlag,VS_UINT8 EditType,VS_UINT8 EditControl,VS_UINT8 EditReadOnly,const VS_CHAR *Default,const VS_CHAR *Desc )
{
    return g_star_CoreFunctionTbl->SRPI_CreateAtomicAttribute(c_this,AtomicObject,AttributeName,Caption,Type,StaticID,SyncFlag,CreateFlag,NotifyFlag,EditType,EditControl,EditReadOnly,Default,Desc);
}

void *Star_SRPI_CreateAtomicFuncRetAttribute(void *c_this, void *AtomicObject, VS_UINT8 Type,const VS_CHAR *Desc  )
{
    return g_star_CoreFunctionTbl->SRPI_CreateAtomicFuncRetAttribute(c_this,AtomicObject,Type,Desc);
}

void *Star_SRPI_CreateAtomicFuncParaAttribute(void *c_this, void *AtomicObject, const VS_CHAR *AttributeName, const VS_CHAR *AttributeCaption,VS_UINT8 Type,const VS_CHAR *Desc )
{
    return g_star_CoreFunctionTbl->SRPI_CreateAtomicFuncParaAttribute(c_this,AtomicObject,AttributeName,AttributeCaption,Type,Desc);
}

void *Star_SRPI_CreateAtomicStructAttribute(void *c_this, void *AtomicObject, const VS_CHAR *AttributeName, const VS_CHAR *Caption, VS_UINT8 Type,const VS_CHAR *Desc )
{
    return g_star_CoreFunctionTbl->SRPI_CreateAtomicStructAttribute(c_this,AtomicObject,AttributeName,Caption,Type,Desc);
}

VS_BOOL Star_SRPI_SetAtomicAttributeLength(void *c_this, void *AtomicObject, VS_INT32 Length )
{
    return g_star_CoreFunctionTbl->SRPI_SetAtomicAttributeLength(c_this,AtomicObject,Length);
}

VS_BOOL Star_SRPI_SetAtomicAttributeStruct(void *c_this, void *AtomicObject, void *AtomicStruct )
{
    return g_star_CoreFunctionTbl->SRPI_SetAtomicAttributeStruct(c_this,AtomicObject,AtomicStruct);
}

VS_BOOL Star_SRPI_SetAtomicAttributeCombobox(void *c_this, void *AtomicObject, const VS_CHAR *MacroName )
{
    return g_star_CoreFunctionTbl->SRPI_SetAtomicAttributeCombobox(c_this,AtomicObject,MacroName);
}

VS_BOOL Star_SRPI_SetAtomicAttributeSyncFlag(void *c_this, void *AtomicObject, VS_UINT8 SyncFlag )
{
    return g_star_CoreFunctionTbl->SRPI_SetAtomicAttributeSyncFlag(c_this,AtomicObject,SyncFlag);
}

void *Star_SRPI_CreateAtomicScript(void *c_this, void *AtomicObject, const VS_CHAR *ScriptName, VS_UUID *ScriptID, const VS_CHAR *Desc, const VS_INT8 *ScriptBuf )
{
    return g_star_CoreFunctionTbl->SRPI_CreateAtomicScript(c_this,AtomicObject,ScriptName,ScriptID,Desc,ScriptBuf);
}

void *Star_SRPI_CreateAtomicFunction(void *c_this, void *AtomicObject, const VS_CHAR *FunctionName, VS_UUID *FunctionID, const VS_CHAR *Desc, VS_BOOL CantOvl, VS_BOOL CallBack, VS_BOOL StdCallFlag,VS_BOOL GlobalFunctionFlag )
{
    return g_star_CoreFunctionTbl->SRPI_CreateAtomicFunction(c_this,AtomicObject,FunctionName,FunctionID,Desc,CantOvl,CallBack,StdCallFlag,GlobalFunctionFlag);
}

void *Star_SRPI_CreateAtomicLuaFunction(void *c_this, void *AtomicObject, const VS_CHAR *LuaFunctionName, VS_UUID *LuaFunctionID, const VS_CHAR *Desc )
{
    return g_star_CoreFunctionTbl->SRPI_CreateAtomicLuaFunction(c_this,AtomicObject,LuaFunctionName,LuaFunctionID,Desc);
}

void *Star_SRPI_CreateAtomicOvlFunction(void *c_this, void *AtomicObject, const VS_CHAR *FunctionName, const VS_CHAR *OriginFunctionName, VS_UUID *OvlFunctionID, const VS_CHAR *Desc, VS_BOOL CantOvl )
{
    return g_star_CoreFunctionTbl->SRPI_CreateAtomicOvlFunction(c_this,AtomicObject,FunctionName,OriginFunctionName,OvlFunctionID,Desc,CantOvl);
}

void *Star_SRPI_CreateAtomicFunctionEx(void *c_this, void *AtomicObject, const VS_CHAR *FunctionName, VS_UUID *FunctionID, const VS_CHAR *Desc, VS_BOOL CantOvl, VS_BOOL CallBack, const VS_CHAR *Type,VS_CHAR **ErrorInfo, VS_BOOL StdCallFlag,VS_BOOL GlobalFunctionFlag )
{
    return g_star_CoreFunctionTbl->SRPI_CreateAtomicFunctionEx(c_this,AtomicObject,FunctionName,FunctionID,Desc,CantOvl,CallBack,Type,ErrorInfo,StdCallFlag,GlobalFunctionFlag);
}

void *Star_SRPI_CreateAtomicInEvent(void *c_this, void *AtomicObject, const VS_CHAR *InEventName, VS_UUID *InEventID,const VS_CHAR *OutEventName )
{
    return g_star_CoreFunctionTbl->SRPI_CreateAtomicInEvent(c_this,AtomicObject,InEventName,InEventID,OutEventName);
}

void *Star_SRPI_CreateAtomicOutEvent(void *c_this, void *AtomicObject, const VS_CHAR *OutEventName, VS_UUID *OutEventID, const VS_CHAR *Desc, VS_BOOL DynamicFlag )
{
    return g_star_CoreFunctionTbl->SRPI_CreateAtomicOutEvent(c_this,AtomicObject,OutEventName,OutEventID,Desc,DynamicFlag);
}

void *Star_SRPI_GetAtomicFunction(void *c_this,VS_UUID *FunctionID)
{
    return g_star_CoreFunctionTbl->SRPI_GetAtomicFunction(c_this,FunctionID);
}

void *Star_SRPI_GetAtomicFunctionEx(void *c_this,void *AtomicObject,VS_UUID *FunctionID)
{
    return g_star_CoreFunctionTbl->SRPI_GetAtomicFunctionEx(c_this,AtomicObject,FunctionID);
}

void *Star_SRPI_GetAtomicFunctionByName(void *c_this, void *AtomicObject, const VS_CHAR *FunctionName )
{
    return g_star_CoreFunctionTbl->SRPI_GetAtomicFunctionByName(c_this,AtomicObject,FunctionName);
}

void *Star_SRPI_GetAtomicScript(void *c_this, void *AtomicObject, const VS_CHAR *ScriptName )
{
    return g_star_CoreFunctionTbl->SRPI_GetAtomicScript(c_this,AtomicObject,ScriptName);
}

void *Star_SRPI_GetAtomicOutEvent(void *c_this, void *AtomicObject, const VS_CHAR *OutEventName )
{
    return g_star_CoreFunctionTbl->SRPI_GetAtomicOutEvent(c_this,AtomicObject,OutEventName);
}

VS_BOOL Star_SRPI_GetAtomicInfo(void *c_this, void *Atomic, VS_ULONG *AtomicType,VS_UWORD *Para1, VS_UWORD *Para2, VS_UWORD *Para3, VS_UWORD *Para4, VS_UWORD *Para5, VS_UWORD *Para6, VS_UWORD *Para7 )
{
    return g_star_CoreFunctionTbl->SRPI_GetAtomicInfo(c_this,Atomic,AtomicType,Para1,Para2,Para3,Para4,Para5,Para6,Para7);
}

VS_BOOL Star_SRPI_GetAtomicAttributeInfo(void *c_this,void *AtomicObject,VS_INT32 AttributeIndexNumber,OBJECTATTRIBUTEINDEX *AttributeIndex,const VS_CHAR *AttributeName,VS_ATTRIBUTEINFO *AttributeInfo)
{
    return g_star_CoreFunctionTbl->SRPI_GetAtomicAttributeInfo(c_this,AtomicObject,AttributeIndexNumber,AttributeIndex,AttributeName,AttributeInfo);
}

VS_BOOL Star_SRPI_GetAtomicAttributeInfoEx(void *c_this,void *AtomicObject,VS_INT32 AttributeIndexNumber,OBJECTATTRIBUTEINDEX *AttributeIndex,OBJECTATTRIBUTEINDEX ThisAtomicAttributeIndex,VS_ATTRIBUTEINFO *AttributeInfo)
{
    return g_star_CoreFunctionTbl->SRPI_GetAtomicAttributeInfoEx(c_this,AtomicObject,AttributeIndexNumber,AttributeIndex,ThisAtomicAttributeIndex,AttributeInfo);
}

VS_INT32 Star_SRPI_GetAtomicAttachAttributeNumber(void *c_this,void *AtomicObject)
{
    return g_star_CoreFunctionTbl->SRPI_GetAtomicAttachAttributeNumber(c_this,AtomicObject);
}

VS_INT32 Star_SRPI_GetAtomicAttachAttributeSize(void *c_this,void *AtomicObject)
{
    return g_star_CoreFunctionTbl->SRPI_GetAtomicAttachAttributeSize(c_this,AtomicObject);
}

VS_BOOL Star_SRPI_GetAtomicAttachAttributeInfoEx(void *c_this,void *AtomicObject,OBJECTATTRIBUTEINDEX AttachAttributeIndex,VS_ATTRIBUTEINFO *AttributeInfo)
{
    return g_star_CoreFunctionTbl->SRPI_GetAtomicAttachAttributeInfoEx(c_this,AtomicObject,AttachAttributeIndex,AttributeInfo);
}

VS_BOOL Star_SRPI_GetAtomicAttributeLength(void *c_this, void *AtomicObject, VS_INT32 *Length )
{
    return g_star_CoreFunctionTbl->SRPI_GetAtomicAttributeLength(c_this,AtomicObject,Length);
}

void *Star_SRPI_GetAtomicAttributeStruct(void *c_this, void *AtomicObject )
{
    return g_star_CoreFunctionTbl->SRPI_GetAtomicAttributeStruct(c_this,AtomicObject);
}

void *Star_SRPI_GetAtomicAttributeCombobox(void *c_this, void *AtomicObject )
{
    return g_star_CoreFunctionTbl->SRPI_GetAtomicAttributeCombobox(c_this,AtomicObject);
}

VS_UINT8 Star_SRPI_GetAtomicAttributeSyncFlag(void *c_this, void *AtomicObject )
{
    return g_star_CoreFunctionTbl->SRPI_GetAtomicAttributeSyncFlag(c_this,AtomicObject);
}

OBJECTATTRIBUTEINDEX Star_SRPI_ToAttributeIndex(void *c_this,void *AtomicObject,OBJECTATTRIBUTEINDEX AtomicAttributeIndex)
{
    return g_star_CoreFunctionTbl->SRPI_ToAttributeIndex(c_this,AtomicObject,AtomicAttributeIndex);
}

OBJECTATTRIBUTEINDEX Star_SRPI_ToAtomicAttributeIndex(void *c_this,void *AtomicObject,OBJECTATTRIBUTEINDEX AttributeIndex)
{
    return g_star_CoreFunctionTbl->SRPI_ToAtomicAttributeIndex(c_this,AtomicObject,AttributeIndex);
}

VS_INT32 Star_SRPI_GetAtomicStructAttributeNumber(void *c_this,void *AtomicObject)
{
    return g_star_CoreFunctionTbl->SRPI_GetAtomicStructAttributeNumber(c_this,AtomicObject);
}

VS_INT32 Star_SRPI_GetAtomicStructAttributeSize(void *c_this,void *AtomicObject)
{
    return g_star_CoreFunctionTbl->SRPI_GetAtomicStructAttributeSize(c_this,AtomicObject);
}

VS_BOOL Star_SRPI_GetAtomicStructAttributeInfo(void *c_this,void *AtomicObject,const VS_CHAR *AttributeName,VS_ATTRIBUTEINFO *AttributeInfo)
{
    return g_star_CoreFunctionTbl->SRPI_GetAtomicStructAttributeInfo(c_this,AtomicObject,AttributeName,AttributeInfo);
}

VS_BOOL Star_SRPI_GetAtomicStructAttributeInfoEx(void *c_this,void *AtomicObject,OBJECTATTRIBUTEINDEX ThisAtomicAttributeIndex,VS_ATTRIBUTEINFO *AttributeInfo)
{
    return g_star_CoreFunctionTbl->SRPI_GetAtomicStructAttributeInfoEx(c_this,AtomicObject,ThisAtomicAttributeIndex,AttributeInfo);
}

VS_INT32 Star_SRPI_GetAtomicFuncRetAttributeNumber(void *c_this,void *AtomicObject)
{
    return g_star_CoreFunctionTbl->SRPI_GetAtomicFuncRetAttributeNumber(c_this,AtomicObject);
}

VS_INT32 Star_SRPI_GetAtomicFuncParaAttributeNumber(void *c_this,void *AtomicObject)
{
    return g_star_CoreFunctionTbl->SRPI_GetAtomicFuncParaAttributeNumber(c_this,AtomicObject);
}

void *Star_SRPI_QueryFirstAtomicMacro(void *c_this, VS_UWORD *QueryContext, VS_UUID *ServiceID, VS_CHAR **MacroName, VS_UINT8 *Type )
{
    return g_star_CoreFunctionTbl->SRPI_QueryFirstAtomicMacro(c_this,QueryContext,ServiceID,MacroName,Type);
}

void *Star_SRPI_QueryNextAtomicMacro(void *c_this, VS_UWORD *QueryContext, VS_UUID *ServiceID, VS_CHAR **MacroName, VS_UINT8 *Type )
{
    return g_star_CoreFunctionTbl->SRPI_QueryNextAtomicMacro(c_this,QueryContext,ServiceID,MacroName,Type);
}

void *Star_SRPI_QueryFirstAtomicInfo(void *c_this, VS_UWORD *QueryContext, VS_UINT8 AtomicType, VS_UWORD *Para1, VS_UWORD *Para2, VS_UWORD *Para3, VS_UWORD *Para4, VS_UWORD *Para5 )
{
    return g_star_CoreFunctionTbl->SRPI_QueryFirstAtomicInfo(c_this,QueryContext,AtomicType,Para1,Para2,Para3,Para4,Para5);
}

void *Star_SRPI_QueryNextAtomicInfo(void *c_this, VS_UWORD *QueryContext, VS_UINT8 AtomicType, VS_UWORD *Para1, VS_UWORD *Para2, VS_UWORD *Para3, VS_UWORD *Para4, VS_UWORD *Para5 )
{
    return g_star_CoreFunctionTbl->SRPI_QueryNextAtomicInfo(c_this,QueryContext,AtomicType,Para1,Para2,Para3,Para4,Para5);
}

VS_BOOL Star_SRPI_AtomicObjectCanOutput(void *c_this, void *AtomicObject, VS_INT32 HasOutputNumber, void **HasOutputAtomicObject )
{
    return g_star_CoreFunctionTbl->SRPI_AtomicObjectCanOutput(c_this,AtomicObject,HasOutputNumber,HasOutputAtomicObject);
}

VS_BOOL Star_SRPI_AtomicObjectAttributeCanOutput(void *c_this, void *AtomicObject, OBJECTATTRIBUTEINDEX AtomicAttributeIndex,VS_INT32 HasOutputNumber, void **HasOutputAtomicObject )
{
    return g_star_CoreFunctionTbl->SRPI_AtomicObjectAttributeCanOutput(c_this,AtomicObject,AtomicAttributeIndex,HasOutputNumber,HasOutputAtomicObject);
}

VS_BOOL Star_SRPI_SetAtomicAttribute(void *c_this,void *AtomicObject,VS_INT32 AttributeIndexNumber,OBJECTATTRIBUTEINDEX *AttributeIndex,OBJECTATTRIBUTEINDEX ThisAtomicAttributeIndex,const VS_INT8 *NewValue)
{
    return g_star_CoreFunctionTbl->SRPI_SetAtomicAttribute(c_this,AtomicObject,AttributeIndexNumber,AttributeIndex,ThisAtomicAttributeIndex,NewValue);
}

void *Star_SRPI_GetAtomicAttribute(void *c_this, void *AtomicObject, VS_INT32 AttributeIndexNumber,OBJECTATTRIBUTEINDEX *AttributeIndex, OBJECTATTRIBUTEINDEX ThisAtomicAttributeIndex )
{
    return g_star_CoreFunctionTbl->SRPI_GetAtomicAttribute(c_this,AtomicObject,AttributeIndexNumber,AttributeIndex,ThisAtomicAttributeIndex);
}

void *Star_SRPI_GetAtomicAttributeDefault(void *c_this, void *AtomicObject, VS_INT32 AttributeIndexNumber,OBJECTATTRIBUTEINDEX *AttributeIndex, OBJECTATTRIBUTEINDEX ThisAtomicAttributeIndex )
{
    return g_star_CoreFunctionTbl->SRPI_GetAtomicAttributeDefault(c_this,AtomicObject,AttributeIndexNumber,AttributeIndex,ThisAtomicAttributeIndex);
}

VS_SYNCGROUP Star_SRPI_GetAtomicObjectSyncGroup(void *c_this, void *AtomicObject )
{
    return g_star_CoreFunctionTbl->SRPI_GetAtomicObjectSyncGroup(c_this,AtomicObject);
}

VS_BOOL Star_SRPI_SetAtomicObjectSyncGroup(void *c_this, void *AtomicObject, VS_SYNCGROUP SyncGroup )
{
    return g_star_CoreFunctionTbl->SRPI_SetAtomicObjectSyncGroup(c_this,AtomicObject,SyncGroup);
}

VS_BOOL Star_SRPI_GetAtomicObjectAttribute(void *c_this, void *AtomicObject,VS_BOOL *SysEvent,VS_UINT8 *SpecialEvent,VS_UINT8 *ActiveCmd,VS_UINT8 *SaveFlag)
{
    return g_star_CoreFunctionTbl->SRPI_GetAtomicObjectAttribute(c_this,AtomicObject,SysEvent,SpecialEvent,ActiveCmd,SaveFlag);
}

VS_BOOL Star_SRPI_SetAtomicObjectAttribute(void *c_this, void *AtomicObject,VS_BOOL SysEvent,VS_UINT8 SpecialEvent,VS_UINT8 ActiveCmd,VS_UINT8 SaveFlag )
{
    return g_star_CoreFunctionTbl->SRPI_SetAtomicObjectAttribute(c_this,AtomicObject,SysEvent,SpecialEvent,ActiveCmd,SaveFlag);
}

void *Star_SRPI_CreateAtomicDepend(void *c_this, const VS_CHAR *DependServiceName, VS_UUID *DependID)
{
    return g_star_CoreFunctionTbl->SRPI_CreateAtomicDepend(c_this,DependServiceName,DependID);
}

VS_BOOL Star_SRPI_IsValid(void *c_this)
{
    return g_star_CoreFunctionTbl->SRPI_IsValid(c_this);
}

VS_BOOL Star_SRPI_ProgramRestart(void *c_this)
{
    return g_star_CoreFunctionTbl->SRPI_ProgramRestart(c_this);
}

VS_BOOL Star_SRPI_HttpDownLoad(void *c_this, VS_UUID *AttachObjectID, const VS_CHAR *ServerUrl,const VS_CHAR *ClientPath,const VS_CHAR *FileName, VS_FileUpDownLoadCallBackProc CallBackProc, VS_UUID *ObjectID, VS_UWORD Para, VS_BOOL SaveFileFlag )
{
    return g_star_CoreFunctionTbl->SRPI_HttpDownLoad(c_this,AttachObjectID,ServerUrl,ClientPath,FileName,CallBackProc,ObjectID,Para,SaveFileFlag);
}

void Star_SRPI_HttpDownLoadAbort(void *c_this)
{
    g_star_CoreFunctionTbl->SRPI_HttpDownLoadAbort(c_this);
}

void Star_SRPI_RegWebDownFunction(void *c_this,VS_WebDownInfoProc CallBackProc,VS_UWORD Para)
{
    g_star_CoreFunctionTbl->SRPI_RegWebDownFunction(c_this,CallBackProc,Para);
}

void Star_SRPI_UnRegWebDownFunction(void *c_this,VS_WebDownInfoProc CallBackProc,VS_UWORD Para)
{
    g_star_CoreFunctionTbl->SRPI_UnRegWebDownFunction(c_this,CallBackProc,Para);
}

void Star_SRPI_WebDownPrint(void *c_this,VS_ULONG uMes, const VS_CHAR *FileName, VS_UINT64 MaxLength, VS_UINT64 CurLength)
{
    g_star_CoreFunctionTbl->SRPI_WebDownPrint(c_this,uMes,FileName,MaxLength,CurLength);
}

void Star_SRPI_RegDllCallBack(void *c_this, VS_MsgCallBackProc MsgCallBackProc, VS_UWORD MsgCallBackPara )
{
    g_star_CoreFunctionTbl->SRPI_RegDllCallBack(c_this,MsgCallBackProc,MsgCallBackPara);
}

void Star_SRPI_UnRegDllCallBack(void *c_this, VS_MsgCallBackProc MsgCallBackProc, VS_UWORD MsgCallBackPara )
{
    g_star_CoreFunctionTbl->SRPI_UnRegDllCallBack(c_this,MsgCallBackProc,MsgCallBackPara);
}

OBJECTATTRIBUTEINDEX Star_SRPI_AllocQueue(void *c_this,void *ParentObject,void *Object)
{
    return g_star_CoreFunctionTbl->SRPI_AllocQueue(c_this,ParentObject,Object);
}

OBJECTATTRIBUTEINDEX Star_SRPI_AllocQueueEx(void *c_this,void *ParentObject,VS_UUID *ClassID)
{
    return g_star_CoreFunctionTbl->SRPI_AllocQueueEx(c_this,ParentObject,ClassID);
}

VS_BOOL Star_SRPI_GetPeerIP(void *c_this,VS_ULONG ClientID,VSSOCKADDR_IN *ClientIP)
{
    return g_star_CoreFunctionTbl->SRPI_GetPeerIP(c_this,ClientID,ClientIP);
}

VS_ULONG Star_SRPI_GetServerID(void *c_this)
{
    return g_star_CoreFunctionTbl->SRPI_GetServerID(c_this);
}

VS_BOOL Star_SRPI_RemoteSend(void *c_this, void *Object, VS_ULONG ClientID, void *ParaPkg )
{
    return g_star_CoreFunctionTbl->SRPI_RemoteSend(c_this,Object,ClientID,ParaPkg);
}

void *Star_SRPI_GetSysDocClass(void *c_this)
{
    return g_star_CoreFunctionTbl->SRPI_GetSysDocClass(c_this);
}

void *Star_SRPI_FirstDoc(void *c_this,VS_QUERYRECORD *QueryRecord,VS_CHAR **DocName)
{
    return g_star_CoreFunctionTbl->SRPI_FirstDoc(c_this,QueryRecord,DocName);
}

void *Star_SRPI_NextDoc(void *c_this,VS_QUERYRECORD *QueryRecord,VS_CHAR **DocName)
{
    return g_star_CoreFunctionTbl->SRPI_NextDoc(c_this,QueryRecord,DocName);
}

void Star_SRPI_RegisterDoc(void *c_this,void *DocObject,const VS_CHAR *DocName)
{
    g_star_CoreFunctionTbl->SRPI_RegisterDoc(c_this,DocObject,DocName);
}

void Star_SRPI_UnRegisterDoc(void *c_this,void *DocObject)
{
    g_star_CoreFunctionTbl->SRPI_UnRegisterDoc(c_this,DocObject);
}

VS_EVENTPARAM_RUNPARAM *Star_SRPI_ProcessSysDocEvent(void *c_this,VS_UUID *DocObjectID,VS_UUID *EventID,VS_EVENTPARAM_RUNPARAM *RequestParam)
{
    return g_star_CoreFunctionTbl->SRPI_ProcessSysDocEvent(c_this,DocObjectID,EventID,RequestParam);
}

VS_BOOL Star_SRPI_RegDocEventFunction(void *c_this,VS_UUID *DocObjectID,VS_UUID *EventID, void *FuncAddr,VS_UWORD Para)
{
    return g_star_CoreFunctionTbl->SRPI_RegDocEventFunction(c_this,DocObjectID,EventID,FuncAddr,Para);
}

void Star_SRPI_UnRegDocEventFunction(void *c_this,VS_UUID *DocObjectID,VS_UUID *EventID, void *FuncAddr,VS_UWORD Para )
{
    g_star_CoreFunctionTbl->SRPI_UnRegDocEventFunction(c_this,DocObjectID,EventID,FuncAddr,Para);
}

void Star_SRPI_GetActiveServiceID(void *c_this,VS_UUID *UuidPtr)
{
    g_star_CoreFunctionTbl->SRPI_GetActiveServiceID(c_this,UuidPtr);
}

void Star_SRPI_RegisterAttachClass(void *c_this,void *OriginClass,void *AttachClass)
{
    g_star_CoreFunctionTbl->SRPI_RegisterAttachClass(c_this,OriginClass,AttachClass);
}

void Star_SRPI_UnRegisterAttachClass(void *c_this,void *OriginClass,void *AttachClass)
{
    g_star_CoreFunctionTbl->SRPI_UnRegisterAttachClass(c_this,OriginClass,AttachClass);
}

VS_BOOL Star_SRPI_WaitEvent(void *c_this,void *SrcObject,VS_UUID *EventID, void *Object, void *FuncAddr,VS_UWORD Para,VS_BOOL AutoDelete)
{
    return g_star_CoreFunctionTbl->SRPI_WaitEvent(c_this,SrcObject,EventID,Object,FuncAddr,Para,AutoDelete);
}

void Star_SRPI_UnWaitEvent(void *c_this,void *SrcObject,VS_UUID *EventID, void *Object, void *FuncAddr,VS_UWORD Para)
{
    g_star_CoreFunctionTbl->SRPI_UnWaitEvent(c_this,SrcObject,EventID,Object,FuncAddr,Para);
}

VS_INT32 Star_SRPI_LuaPushEventPara(void *c_this,void *EventParam)
{
    return g_star_CoreFunctionTbl->SRPI_LuaPushEventPara(c_this,EventParam);
}

VS_BOOL Star_SRPI_RegChangeCallBackEx(void *c_this,void *Object,VS_ObjectChangeNotifyExProc ObjectChangeNotifyProc,void *DesObject,VS_UWORD Para,VS_BOOL ChildNotify)
{
    return g_star_CoreFunctionTbl->SRPI_RegChangeCallBackEx(c_this,Object,ObjectChangeNotifyProc,DesObject,Para,ChildNotify);
}

void Star_SRPI_UnRegChangeCallBackEx(void *c_this,void *Object,VS_ObjectChangeNotifyExProc ObjectChangeNotifyProc,void *DesObject,VS_UWORD Para)
{
    g_star_CoreFunctionTbl->SRPI_UnRegChangeCallBackEx(c_this,Object,ObjectChangeNotifyProc,DesObject,Para);
}

void Star_SRPI_ToClipBoard(void *c_this,const VS_CHAR *Info)
{
    g_star_CoreFunctionTbl->SRPI_ToClipBoard(c_this,Info);
}

VS_CHAR *Star_SRPI_FromClipBoard(void *c_this)
{
    return g_star_CoreFunctionTbl->SRPI_FromClipBoard(c_this);
}

VS_BOOL Star_SRPI_IsWindowlessSite(void *c_this)
{
    return g_star_CoreFunctionTbl->SRPI_IsWindowlessSite(c_this);
}

void Star_SRPI_RegWindowlessSiteCallBack(void *c_this,struct VSWindowlessSiteCallBackInfo *CallBackInfo, VS_UUID *ObjectID, VS_UWORD Para )
{
    g_star_CoreFunctionTbl->SRPI_RegWindowlessSiteCallBack(c_this,CallBackInfo,ObjectID,Para);
}

void Star_SRPI_UnRegWindowlessSiteCallBack(void *c_this,struct VSWindowlessSiteCallBackInfo *CallBackInfo, VS_UUID *ObjectID, VS_UWORD Para )
{
    g_star_CoreFunctionTbl->SRPI_UnRegWindowlessSiteCallBack(c_this,CallBackInfo,ObjectID,Para);
}

VS_BOOL Star_SRPI_IsWindowlessTransparent(void *c_this)
{
    return g_star_CoreFunctionTbl->SRPI_IsWindowlessTransparent(c_this);
}

void Star_SRPI_Windowless_Redraw(void *c_this, VS_BOOL fErase )
{
    g_star_CoreFunctionTbl->SRPI_Windowless_Redraw(c_this,fErase);
}

void Star_SRPI_Windowless_GetDC(void *c_this, void **hDC,VS_RECT *rEct )
{
    g_star_CoreFunctionTbl->SRPI_Windowless_GetDC(c_this,hDC,rEct);
}

void Star_SRPI_Windowless_ReleaseDC(void *c_this, void *hDC )
{
    g_star_CoreFunctionTbl->SRPI_Windowless_ReleaseDC(c_this,hDC);
}

void Star_SRPI_KillClientWndFocus(void *c_this, VS_HWND hWnd, VS_BOOL NeedAction )
{
    g_star_CoreFunctionTbl->SRPI_KillClientWndFocus(c_this,hWnd,NeedAction);
}

VS_BOOL Star_SRPI_XmlToSysRootItem(void *c_this,void *SXMLInterface,const VS_CHAR *DataPath,const VS_CHAR *SegmentName,SRPParse_PrintProc PrintProc,VS_UWORD Para)
{
    return g_star_CoreFunctionTbl->SRPI_XmlToSysRootItem(c_this,SXMLInterface,DataPath,SegmentName,PrintProc,Para);
}

VS_BOOL Star_SRPI_XmlToObject(void *c_this,void *SXMLInterface,void *ParentObject,OBJECTATTRIBUTEINDEX AttributeIndex,const VS_CHAR *DataPath,const VS_CHAR *SegmentName,SRPParse_PrintProc PrintProc,VS_UWORD Para)
{
    return g_star_CoreFunctionTbl->SRPI_XmlToObject(c_this,SXMLInterface,ParentObject,AttributeIndex,DataPath,SegmentName,PrintProc,Para);
}

VS_BOOL Star_SRPI_ServiceToXml(void *c_this,void *SXMLInterface,const VS_CHAR *PassWord,const VS_CHAR *DataPath,VS_BOOL CFunctionFlag,VS_BOOL OutputObjectID,SRPParse_PrintProc PrintProc,VS_UWORD Para)
{
    return g_star_CoreFunctionTbl->SRPI_ServiceToXml(c_this,SXMLInterface,PassWord,DataPath,CFunctionFlag,OutputObjectID,PrintProc,Para);
}

VS_BOOL Star_SRPI_SysRootItemToXml(void *c_this,void *SXMLInterface,const VS_CHAR *SysRootItemName,const VS_CHAR *DataPath,VS_BOOL CFunctionFlag,VS_BOOL OutputObjectID,SRPParse_PrintProc PrintProc,VS_UWORD Para)
{
    return g_star_CoreFunctionTbl->SRPI_SysRootItemToXml(c_this,SXMLInterface,SysRootItemName,DataPath,CFunctionFlag,OutputObjectID,PrintProc,Para);
}

VS_BOOL Star_SRPI_ObjectToXml(void *c_this,void *SXMLInterface,void *Object,const VS_CHAR *DataPath,VS_BOOL CFunctionFlag,VS_BOOL OutputObjectID,SRPParse_PrintProc PrintProc,VS_UWORD Para)
{
    return g_star_CoreFunctionTbl->SRPI_ObjectToXml(c_this,SXMLInterface,Object,DataPath,CFunctionFlag,OutputObjectID,PrintProc,Para);
}

VS_UUID *Star_SRPI_GetVSObjectID(void *c_this,VS_INT32 Which)
{
    return g_star_CoreFunctionTbl->SRPI_GetVSObjectID(c_this,Which);
}

void *Star_SRPI_GetBasicInterface(void *c_this)
{
    return g_star_CoreFunctionTbl->SRPI_GetBasicInterface(c_this);
}

void *Star_SRPI_GetSXMLInterface(void *c_this)
{
    return g_star_CoreFunctionTbl->SRPI_GetSXMLInterface(c_this);
}

void *Star_SRPI_GetFunctionParaInterface(void *c_this)
{
    return g_star_CoreFunctionTbl->SRPI_GetFunctionParaInterface(c_this);
}

void *Star_SRPI_GetSRPLockInterface(void *c_this)
{
    return g_star_CoreFunctionTbl->SRPI_GetSRPLockInterface(c_this);
}

void *Star_SRPI_GetSRPBinBufInterface(void *c_this)
{
    return g_star_CoreFunctionTbl->SRPI_GetSRPBinBufInterface(c_this);
}

void *Star_SRPI_GetParaPkgInterface(void *c_this)
{
    return g_star_CoreFunctionTbl->SRPI_GetParaPkgInterface(c_this);
}

void *Star_SRPI_GetEnvMemoryFile(void *c_this)
{
    return g_star_CoreFunctionTbl->SRPI_GetEnvMemoryFile(c_this);
}

void *Star_SRPI_GetCommInterface(void *c_this)
{
    return g_star_CoreFunctionTbl->SRPI_GetCommInterface(c_this);
}

void *Star_SRPI_GetFileDiskInterface(void *c_this)
{
    return g_star_CoreFunctionTbl->SRPI_GetFileDiskInterface(c_this);
}

void Star_SRPI_GetSRPConfigPath(void *c_this,VS_ULONG BufSize,VS_CHAR *Buf)
{
    g_star_CoreFunctionTbl->SRPI_GetSRPConfigPath(c_this,BufSize,Buf);
}

VS_BOOL Star_SRPI_RegTempFile(void *c_this,const VS_CHAR *TempFileName,const VS_CHAR *OriFileName)
{
    return g_star_CoreFunctionTbl->SRPI_RegTempFile(c_this,TempFileName,OriFileName);
}

VS_CHAR *Star_SRPI_GetRegTempFile(void *c_this,const VS_CHAR *OriFileName,VS_CHAR *Buf,VS_INT32 BufSize)
{
    return g_star_CoreFunctionTbl->SRPI_GetRegTempFile(c_this,OriFileName,Buf,BufSize);
}

void Star_SRPI_UnRegTempFile(void *c_this,const VS_CHAR *TempFileName)
{
    g_star_CoreFunctionTbl->SRPI_UnRegTempFile(c_this,TempFileName);
}

void *Star_SRPI_QueryInterface(void *c_this, VS_UUID *InterfaceID )
{
    return g_star_CoreFunctionTbl->SRPI_QueryInterface(c_this,InterfaceID);
}

VS_BOOL Star_SRPI_LockLuaTable(void *c_this)
{
    return g_star_CoreFunctionTbl->SRPI_LockLuaTable(c_this);
}

VS_BOOL Star_SRPI_UnLockLuaTable(void *c_this)
{
    return g_star_CoreFunctionTbl->SRPI_UnLockLuaTable(c_this);
}

VS_UUID *Star_SRPI_GetIDEx(void *c_this,void *Object)
{
    return g_star_CoreFunctionTbl->SRPI_GetIDEx(c_this,Object);
}

VS_BOOL Star_SRPI_IsRootService(void *c_this)
{
    return g_star_CoreFunctionTbl->SRPI_IsRootService(c_this);
}

VS_BOOL Star_SRPI_LuaGetObjectValue(void *c_this,void *Object,const VS_CHAR *Name)
{
    return g_star_CoreFunctionTbl->SRPI_LuaGetObjectValue(c_this,Object,Name);
}

VS_BOOL Star_SRPI_LuaSetObjectValue(void *c_this,void *Object,const VS_CHAR *Name)
{
    return g_star_CoreFunctionTbl->SRPI_LuaSetObjectValue(c_this,Object,Name);
}

void *Star_SRPI_GetSRPInterface(void *c_this,void *Object)
{
    return g_star_CoreFunctionTbl->SRPI_GetSRPInterface(c_this,Object);
}

void *Star_SRPI_GetSRPInterfaceEx(void *c_this,VS_UUID *ObjectID)
{
    return g_star_CoreFunctionTbl->SRPI_GetSRPInterfaceEx(c_this,ObjectID);
}

VS_BOOL Star_SRPI_IsThisServiceEx(void *c_this,VS_UUID *ObjectID)
{
    return g_star_CoreFunctionTbl->SRPI_IsThisServiceEx(c_this,ObjectID);
}

void Star_SRPI_AddRef(void *c_this)
{
    g_star_CoreFunctionTbl->SRPI_AddRef(c_this);
}

VS_INT32 Star_SRPI_GetRef(void *c_this)
{
    return g_star_CoreFunctionTbl->SRPI_GetRef(c_this);
}

void Star_SRPI_SetLog(void *c_this,void *Object,VS_BOOL Flag)
{
    g_star_CoreFunctionTbl->SRPI_SetLog(c_this,Object,Flag);
}

void Star_SRPI_SetLogFile(void *c_this,const VS_CHAR *FileName)
{
    g_star_CoreFunctionTbl->SRPI_SetLogFile(c_this,FileName);
}

VS_CHAR *Star_SRPI_GetLogFile(void *c_this)
{
    return g_star_CoreFunctionTbl->SRPI_GetLogFile(c_this);
}

void Star_SRPI_ClearLog(void *c_this)
{
    g_star_CoreFunctionTbl->SRPI_ClearLog(c_this);
}

VS_BOOL Star_SRPI_ApplyLog(void *c_this)
{
    return g_star_CoreFunctionTbl->SRPI_ApplyLog(c_this);
}

VS_UWORD Star_SRPI_Get(void *c_this,void *Object,const VS_CHAR *AttributeName)
{
    return g_star_CoreFunctionTbl->SRPI_Get(c_this,Object,AttributeName);
}

VS_UWORD Star_SRPI_GetEx(void *c_this,void *Object,OBJECTATTRIBUTEINDEX AttributeIndex)
{
    return g_star_CoreFunctionTbl->SRPI_GetEx(c_this,Object,AttributeIndex);
}

VS_FLOAT Star_SRPI_FGet(void *c_this,void *Object,const VS_CHAR *AttributeName)
{
    return g_star_CoreFunctionTbl->SRPI_FGet(c_this,Object,AttributeName);
}

VS_FLOAT Star_SRPI_FGetEx(void *c_this,void *Object,OBJECTATTRIBUTEINDEX AttributeIndex)
{
    return g_star_CoreFunctionTbl->SRPI_FGetEx(c_this,Object,AttributeIndex);
}

VS_CHAR *Star_SRPI_LuaToLString(void *c_this,VS_INT32 index,VS_ULONG *len)
{
    return g_star_CoreFunctionTbl->SRPI_LuaToLString(c_this,index,len);
}

VS_BOOL Star_SRPI_SetNameBoolValue(void *c_this, void *Object,const VS_CHAR *Name, VS_BOOL Value, VS_BOOL LocalChange  )
{
    return g_star_CoreFunctionTbl->SRPI_SetNameBoolValue(c_this,Object,Name,Value,LocalChange);
}

VS_BOOL Star_SRPI_GetNameBoolValue(void *c_this, void *Object,const VS_CHAR *Name, VS_BOOL *Value, VS_BOOL DefaultValue  )
{
    return g_star_CoreFunctionTbl->SRPI_GetNameBoolValue(c_this,Object,Name,Value,DefaultValue);
}

VS_BOOL Star_SRPI_LuaIsInt(void *c_this, VS_INT32 Index )
{
    return g_star_CoreFunctionTbl->SRPI_LuaIsInt(c_this,Index);
}

VS_BOOL Star_SRPI_AtomicAttach(void *c_this, void *AtomicObject,const VS_CHAR *ShareLibName )
{
    return g_star_CoreFunctionTbl->SRPI_AtomicAttach(c_this,AtomicObject,ShareLibName);
}

VS_BOOL Star_SRPI_IsGlobalFunction(void *c_this,VS_UUID *FunctionID)
{
    return g_star_CoreFunctionTbl->SRPI_IsGlobalFunction(c_this,FunctionID);
}

VS_BOOL Star_SRPI_IsGlobalFunctionEx(void *c_this,void *Object,VS_UUID *FunctionID)
{
    return g_star_CoreFunctionTbl->SRPI_IsGlobalFunctionEx(c_this,Object,FunctionID);
}

void Star_SRPI_LuaGetDefinedClass(void *c_this,void *Object,VS_UUID *ObjectID)
{
    g_star_CoreFunctionTbl->SRPI_LuaGetDefinedClass(c_this,Object,ObjectID);
}

VS_BOOL Star_SRPI_LuaGetDefinedClassEx(void *c_this,void *Object,const VS_CHAR *AttributeName,VS_UUID *ObjectID)
{
    return g_star_CoreFunctionTbl->SRPI_LuaGetDefinedClassEx(c_this,Object,AttributeName,ObjectID);
}

VS_BOOL Star_SRPI_ScriptSetBool(void *c_this,void *Object,const VS_CHAR *AttributeName,VS_BOOL Value)
{
    return g_star_CoreFunctionTbl->SRPI_ScriptSetBool(c_this,Object,AttributeName,Value);
}

VS_BOOL Star_SRPI_ScriptSetInt(void *c_this,void *Object,const VS_CHAR *AttributeName,VS_INT32 Value)
{
    return g_star_CoreFunctionTbl->SRPI_ScriptSetInt(c_this,Object,AttributeName,Value);
}

VS_BOOL Star_SRPI_ScriptSetNumber(void *c_this,void *Object,const VS_CHAR *AttributeName,VS_FLOAT Value)
{
    return g_star_CoreFunctionTbl->SRPI_ScriptSetNumber(c_this,Object,AttributeName,Value);
}

VS_BOOL Star_SRPI_ScriptSetStr(void *c_this,void *Object,const VS_CHAR *AttributeName,const VS_CHAR *Value)
{
    return g_star_CoreFunctionTbl->SRPI_ScriptSetStr(c_this,Object,AttributeName,Value);
}

VS_BOOL Star_SRPI_ScriptSetObject(void *c_this,void *Object,const VS_CHAR *AttributeName,VS_UINT8 Type,VS_UWORD Value)
{
    return g_star_CoreFunctionTbl->SRPI_ScriptSetObject(c_this,Object,AttributeName,Type,Value);
}

VS_BOOL Star_SRPI_ScriptGetBool(void *c_this,void *Object,const VS_CHAR *AttributeName)
{
    return g_star_CoreFunctionTbl->SRPI_ScriptGetBool(c_this,Object,AttributeName);
}

VS_INT32 Star_SRPI_ScriptGetInt(void *c_this,void *Object,const VS_CHAR *AttributeName)
{
    return g_star_CoreFunctionTbl->SRPI_ScriptGetInt(c_this,Object,AttributeName);
}

VS_FLOAT Star_SRPI_ScriptGetNumber(void *c_this,void *Object,const VS_CHAR *AttributeName)
{
    return g_star_CoreFunctionTbl->SRPI_ScriptGetNumber(c_this,Object,AttributeName);
}

VS_CHAR *Star_SRPI_ScriptGetStr(void *c_this,void *Object,const VS_CHAR *AttributeName)
{
    return g_star_CoreFunctionTbl->SRPI_ScriptGetStr(c_this,Object,AttributeName);
}

VS_UWORD Star_SRPI_ScriptGetObject(void *c_this,void *Object,const VS_CHAR *AttributeName,VS_UINT8 *RetType)
{
    return g_star_CoreFunctionTbl->SRPI_ScriptGetObject(c_this,Object,AttributeName,RetType);
}

VS_BOOL Star_SRPI_IsRegistered(void *c_this)
{
    return g_star_CoreFunctionTbl->SRPI_IsRegistered(c_this);
}

void Star_SRPI_SetVString(void *c_this,VS_VSTRING *Buf,const VS_CHAR *Str)
{
    g_star_CoreFunctionTbl->SRPI_SetVString(c_this,Buf,Str);
}

VS_VSTRING *Star_SRPI_ToVString(void *c_this,const VS_CHAR *Str)
{
    return g_star_CoreFunctionTbl->SRPI_ToVString(c_this,Str);
}

void Star_SRPI_CheckPassword(void *c_this,VS_BOOL CheckFlag)
{
    g_star_CoreFunctionTbl->SRPI_CheckPassword(c_this,CheckFlag);
}

VS_INT32 Star_SRPI_ScriptGetStack(void *c_this)
{
    return g_star_CoreFunctionTbl->SRPI_ScriptGetStack(c_this);
}

VS_BOOL Star_SRPI_ScriptSetStack(void *c_this,VS_INT32 Top)
{
    return g_star_CoreFunctionTbl->SRPI_ScriptSetStack(c_this,Top);
}

void Star_SRPI_SetSourceScript(void *c_this,void *Object,VS_INT32 SourceScript)
{
    g_star_CoreFunctionTbl->SRPI_SetSourceScript(c_this,Object,SourceScript);
}

VS_INT32 Star_SRPI_GetSourceScript(void *c_this,void *Object)
{
    return g_star_CoreFunctionTbl->SRPI_GetSourceScript(c_this,Object);
}

VS_CHAR *Star_SRPI_FirstShareLib(void *c_this, VS_QUERYRECORD *QueryRecord )
{
    return g_star_CoreFunctionTbl->SRPI_FirstShareLib(c_this,QueryRecord);
}

VS_CHAR *Star_SRPI_NextShareLib(void *c_this, VS_QUERYRECORD *QueryRecord )
{
    return g_star_CoreFunctionTbl->SRPI_NextShareLib(c_this,QueryRecord);
}

VS_HANDLE Star_SRPI_GetShareLib(void *c_this, const VS_CHAR *ShareLibName )
{
    return g_star_CoreFunctionTbl->SRPI_GetShareLib(c_this,ShareLibName);
}

void Star_SRPI_FreeShareLib(void *c_this, VS_HANDLE ShareLibHandle )
{
    g_star_CoreFunctionTbl->SRPI_FreeShareLib(c_this,ShareLibHandle);
}

VS_ULONG Star_SRPI_NewGroup(void *c_this)
{
    return g_star_CoreFunctionTbl->SRPI_NewGroup(c_this);
}

void Star_SRPI_FreeGroup(void *c_this,VS_ULONG GroupID)
{
    g_star_CoreFunctionTbl->SRPI_FreeGroup(c_this,GroupID);
}

VS_LONG Star_SRPI_GroupAdd(void *c_this,VS_ULONG GroupID,void *Object)
{
    return g_star_CoreFunctionTbl->SRPI_GroupAdd(c_this,GroupID,Object);
}

void *Star_SRPI_GroupGet(void *c_this,VS_ULONG GroupID,VS_LONG RefID)
{
    return g_star_CoreFunctionTbl->SRPI_GroupGet(c_this,GroupID,RefID);
}

void Star_SRPI_GroupRemove(void *c_this,VS_ULONG GroupID,VS_LONG RefID)
{
    g_star_CoreFunctionTbl->SRPI_GroupRemove(c_this,GroupID,RefID);
}

void Star_SRPI_GroupRemoveEx(void *c_this,VS_ULONG GroupID,void *Object)
{
    g_star_CoreFunctionTbl->SRPI_GroupRemoveEx(c_this,GroupID,Object);
}

void Star_SRPI_GroupClear(void *c_this,VS_ULONG GroupID,VS_BOOL FreeObject)
{
    g_star_CoreFunctionTbl->SRPI_GroupClear(c_this,GroupID,FreeObject);
}

VS_BOOL Star_SRPI_DoFileEx(void *c_this, const VS_CHAR *ScriptInterface,const VS_CHAR *FileName, VS_CHAR **ErrorInfo, const VS_CHAR *WorkDirectory, VS_BOOL IsUTF8,const VS_CHAR *ModuleName )
{
    return g_star_CoreFunctionTbl->SRPI_DoFileEx(c_this,ScriptInterface,FileName,ErrorInfo,WorkDirectory,IsUTF8,ModuleName);
}

VS_BOOL Star_SRPI_SetCallSuper(void *c_this,void *Object)
{
    return g_star_CoreFunctionTbl->SRPI_SetCallSuper(c_this,Object);
}

VS_BOOL Star_SRPI_SetCallBase(void *c_this,void *Object,void *Class)
{
    return g_star_CoreFunctionTbl->SRPI_SetCallBase(c_this,Object,Class);
}

VS_BOOL Star_SRPI_PushCallBase(void *c_this,void *Object,void *Class)
{
    return g_star_CoreFunctionTbl->SRPI_PushCallBase(c_this,Object,Class);
}

VS_BOOL Star_SRPI_PopCallBase(void *c_this,void *Object,void *Class)
{
    return g_star_CoreFunctionTbl->SRPI_PopCallBase(c_this,Object,Class);
}

void Star_SRPI_RegGetObjectCallBack(void *c_this,VS_GetObjectCallBackProc CallBackProc,VS_UWORD Para)
{
    g_star_CoreFunctionTbl->SRPI_RegGetObjectCallBack(c_this,CallBackProc,Para);
}

void Star_SRPI_UnRegGetObjectCallBack(void *c_this,VS_GetObjectCallBackProc CallBackProc,VS_UWORD Para)
{
    g_star_CoreFunctionTbl->SRPI_UnRegGetObjectCallBack(c_this,CallBackProc,Para);
}

void Star_SRPI_RegGetObjectExCallBack(void *c_this,VS_GetObjectExCallBackProc CallBackProc,VS_UWORD Para)
{
    g_star_CoreFunctionTbl->SRPI_RegGetObjectExCallBack(c_this,CallBackProc,Para);
}

void Star_SRPI_UnRegGetObjectExCallBack(void *c_this,VS_GetObjectExCallBackProc CallBackProc,VS_UWORD Para)
{
    g_star_CoreFunctionTbl->SRPI_UnRegGetObjectExCallBack(c_this,CallBackProc,Para);
}

void Star_SRPI_LuaReplace(void *c_this,VS_INT32 index)
{
    g_star_CoreFunctionTbl->SRPI_LuaReplace(c_this,index);
}

void Star_SRPI_LuaCheckStack(void *c_this,VS_INT32 sz)
{
    g_star_CoreFunctionTbl->SRPI_LuaCheckStack(c_this,sz);
}

VS_BOOL Star_SRPI_LuaIsUserData(void *c_this,VS_INT32 index)
{
    return g_star_CoreFunctionTbl->SRPI_LuaIsUserData(c_this,index);
}

VS_BOOL Star_SRPI_LuaIsLightUserData(void *c_this,VS_INT32 index)
{
    return g_star_CoreFunctionTbl->SRPI_LuaIsLightUserData(c_this,index);
}

VS_INT32 Star_SRPI_LuaRawEqual(void *c_this,VS_INT32 index1, VS_INT32 index2)
{
    return g_star_CoreFunctionTbl->SRPI_LuaRawEqual(c_this,index1,index2);
}

VS_INT32 Star_SRPI_LuaCompare(void *c_this,VS_INT32 index1, VS_INT32 index2, VS_INT32 op)
{
    return g_star_CoreFunctionTbl->SRPI_LuaCompare(c_this,index1,index2,op);
}

void Star_SRPI_LuaConcat(void *c_this,VS_INT32 n)
{
    g_star_CoreFunctionTbl->SRPI_LuaConcat(c_this,n);
}

void Star_SRPI_LuaCopy(void *c_this,VS_INT32 fromidx, VS_INT32 toidx)
{
    g_star_CoreFunctionTbl->SRPI_LuaCopy(c_this,fromidx,toidx);
}

void *Star_SRPI_LuaToPointer(void *c_this,VS_INT32 index)
{
    return g_star_CoreFunctionTbl->SRPI_LuaToPointer(c_this,index);
}

void *Star_SRPI_LuaToCFunction(void *c_this,VS_INT32 index)
{
    return g_star_CoreFunctionTbl->SRPI_LuaToCFunction(c_this,index);
}

void Star_SRPI_LuaPushLightUserData(void *c_this,void *p)
{
    g_star_CoreFunctionTbl->SRPI_LuaPushLightUserData(c_this,p);
}

void Star_SRPI_LuaRawGet(void *c_this,VS_INT32 index)
{
    g_star_CoreFunctionTbl->SRPI_LuaRawGet(c_this,index);
}

void Star_SRPI_LuaRawGeti(void *c_this,VS_INT32 index, VS_INT32 n)
{
    g_star_CoreFunctionTbl->SRPI_LuaRawGeti(c_this,index,n);
}

void Star_SRPI_LuaCreateTable(void *c_this,VS_INT32 narr, VS_INT32 nrec)
{
    g_star_CoreFunctionTbl->SRPI_LuaCreateTable(c_this,narr,nrec);
}

VS_INT32 Star_SRPI_LuaGetMetatable(void *c_this,VS_INT32 index)
{
    return g_star_CoreFunctionTbl->SRPI_LuaGetMetatable(c_this,index);
}

void Star_SRPI_LuaSetField(void *c_this,VS_INT32 index, const VS_CHAR *k)
{
    g_star_CoreFunctionTbl->SRPI_LuaSetField(c_this,index,k);
}

void Star_SRPI_LuaRawSet(void *c_this,VS_INT32 index)
{
    g_star_CoreFunctionTbl->SRPI_LuaRawSet(c_this,index);
}

void Star_SRPI_LuaRawSeti(void *c_this,VS_INT32 index, VS_INT32 n)
{
    g_star_CoreFunctionTbl->SRPI_LuaRawSeti(c_this,index,n);
}

void Star_SRPI_LuaSetMetatable(void *c_this,VS_INT32 index)
{
    g_star_CoreFunctionTbl->SRPI_LuaSetMetatable(c_this,index);
}

VS_INT32 Star_SRPI_Lua_PCall(void *c_this,VS_INT32 nargs, VS_INT32 nresults, VS_INT32 msgh)
{
    return g_star_CoreFunctionTbl->SRPI_Lua_PCall(c_this,nargs,nresults,msgh);
}

void Star_SRPI_Lua_Call(void *c_this,VS_INT32 nargs, VS_INT32 nresults)
{
    g_star_CoreFunctionTbl->SRPI_Lua_Call(c_this,nargs,nresults);
}

void *Star_SRPI_LuaAtPanic(void *c_this,void *panicf)
{
    return g_star_CoreFunctionTbl->SRPI_LuaAtPanic(c_this,panicf);
}

VS_INT32 Star_SRPI_LuaGC(void *c_this,VS_INT32 what, VS_INT32 data)
{
    return g_star_CoreFunctionTbl->SRPI_LuaGC(c_this,what,data);
}

VS_INT32 Star_SRPI_LuaError(void *c_this)
{
    return g_star_CoreFunctionTbl->SRPI_LuaError(c_this);
}

VS_INT32 Star_SRPI_LuaIsNoneOrNil(void *c_this,VS_INT32 index)
{
    return g_star_CoreFunctionTbl->SRPI_LuaIsNoneOrNil(c_this,index);
}

VS_CHAR *Star_SRPI_LuaTypeName(void *c_this,VS_INT32 tp)
{
    return g_star_CoreFunctionTbl->SRPI_LuaTypeName(c_this,tp);
}

void Star_SRPI_LuaL_CheckAny(void *c_this,VS_INT32 narg)
{
    g_star_CoreFunctionTbl->SRPI_LuaL_CheckAny(c_this,narg);
}

VS_INT32 Star_SRPI_LuaL_CheckInt(void *c_this,VS_INT32 narg)
{
    return g_star_CoreFunctionTbl->SRPI_LuaL_CheckInt(c_this,narg);
}

VS_LONG Star_SRPI_LuaL_CheckLong(void *c_this,VS_INT32 narg)
{
    return g_star_CoreFunctionTbl->SRPI_LuaL_CheckLong(c_this,narg);
}

const VS_CHAR *Star_SRPI_LuaL_CheckLString(void *c_this,VS_INT32 narg, VS_INT32 *l)
{
    return g_star_CoreFunctionTbl->SRPI_LuaL_CheckLString(c_this,narg,l);
}

VS_DOUBLE Star_SRPI_LuaL_CheckNumber(void *c_this,VS_INT32 narg)
{
    return g_star_CoreFunctionTbl->SRPI_LuaL_CheckNumber(c_this,narg);
}

VS_INT32 Star_SRPI_LuaL_CheckOption(void *c_this,VS_INT32 narg,const VS_CHAR *def,const VS_CHAR *lst[])
{
    return g_star_CoreFunctionTbl->SRPI_LuaL_CheckOption(c_this,narg,def,lst);
}

void Star_SRPI_LuaL_CheckStack(void *c_this,VS_INT32 sz, const VS_CHAR *msg)
{
    g_star_CoreFunctionTbl->SRPI_LuaL_CheckStack(c_this,sz,msg);
}

const VS_CHAR *Star_SRPI_LuaL_CheckString(void *c_this,VS_INT32 narg)
{
    return g_star_CoreFunctionTbl->SRPI_LuaL_CheckString(c_this,narg);
}

void Star_SRPI_LuaL_CheckType(void *c_this,VS_INT32 narg, VS_INT32 t)
{
    g_star_CoreFunctionTbl->SRPI_LuaL_CheckType(c_this,narg,t);
}

void *Star_SRPI_LuaL_CheckUData(void *c_this,VS_INT32 narg, const VS_CHAR *tname)
{
    return g_star_CoreFunctionTbl->SRPI_LuaL_CheckUData(c_this,narg,tname);
}

void Star_SRPI_LuaL_CheckVersion(void *c_this)
{
    g_star_CoreFunctionTbl->SRPI_LuaL_CheckVersion(c_this);
}

VS_INT32 Star_SRPI_LuaL_DoFile(void *c_this,const VS_CHAR *filename)
{
    return g_star_CoreFunctionTbl->SRPI_LuaL_DoFile(c_this,filename);
}

VS_INT32 Star_SRPI_LuaL_DoString(void *c_this,const VS_CHAR *str)
{
    return g_star_CoreFunctionTbl->SRPI_LuaL_DoString(c_this,str);
}

VS_INT32 Star_SRPI_LuaL_Error(void *c_this,const VS_CHAR *info)
{
    return g_star_CoreFunctionTbl->SRPI_LuaL_Error(c_this,info);
}

void Star_SRPI_LuaL_GetMetatable(void *c_this,const VS_CHAR *tname)
{
    g_star_CoreFunctionTbl->SRPI_LuaL_GetMetatable(c_this,tname);
}

VS_INT32 Star_SRPI_LuaL_GetSubTable(void *c_this,VS_INT32 idx, const VS_CHAR *fname)
{
    return g_star_CoreFunctionTbl->SRPI_LuaL_GetSubTable(c_this,idx,fname);
}

VS_INT32 Star_SRPI_LuaL_Len(void *c_this,VS_INT32 index)
{
    return g_star_CoreFunctionTbl->SRPI_LuaL_Len(c_this,index);
}

VS_INT32 Star_SRPI_LuaL_LoadBuffer(void *c_this,const VS_CHAR *buff,VS_INT32 sz,const VS_CHAR *name)
{
    return g_star_CoreFunctionTbl->SRPI_LuaL_LoadBuffer(c_this,buff,sz,name);
}

VS_INT32 Star_SRPI_LuaL_LoadBufferx(void *c_this,const VS_CHAR *buff,VS_INT32 sz,const VS_CHAR *name,const VS_CHAR *mode)
{
    return g_star_CoreFunctionTbl->SRPI_LuaL_LoadBufferx(c_this,buff,sz,name,mode);
}

VS_INT32 Star_SRPI_LuaL_LoadFile(void *c_this,const VS_CHAR *filename)
{
    return g_star_CoreFunctionTbl->SRPI_LuaL_LoadFile(c_this,filename);
}

VS_INT32 Star_SRPI_LuaL_LoadFilex(void *c_this,const VS_CHAR *filename,const VS_CHAR *mode)
{
    return g_star_CoreFunctionTbl->SRPI_LuaL_LoadFilex(c_this,filename,mode);
}

VS_INT32 Star_SRPI_LuaL_LoadString(void *c_this,const VS_CHAR *s)
{
    return g_star_CoreFunctionTbl->SRPI_LuaL_LoadString(c_this,s);
}

void Star_SRPI_LuaL_NewLib(void *c_this,const VSLuaL_Reg *l)
{
    g_star_CoreFunctionTbl->SRPI_LuaL_NewLib(c_this,l);
}

VS_INT32 Star_SRPI_LuaL_NewMetatable(void *c_this,const VS_CHAR *tname)
{
    return g_star_CoreFunctionTbl->SRPI_LuaL_NewMetatable(c_this,tname);
}

VS_INT32 Star_SRPI_LuaL_Ref(void *c_this,VS_INT32 t)
{
    return g_star_CoreFunctionTbl->SRPI_LuaL_Ref(c_this,t);
}

void Star_SRPI_LuaL_Requiref(void *c_this,const VS_CHAR *modname,void *openf, VS_INT32 glb)
{
    g_star_CoreFunctionTbl->SRPI_LuaL_Requiref(c_this,modname,openf,glb);
}

void Star_SRPI_LuaL_SetFuncs(void *c_this,const VSLuaL_Reg *l, VS_INT32 nup)
{
    g_star_CoreFunctionTbl->SRPI_LuaL_SetFuncs(c_this,l,nup);
}

void Star_SRPI_LuaL_SetMetatable(void *c_this,const VS_CHAR *tname)
{
    g_star_CoreFunctionTbl->SRPI_LuaL_SetMetatable(c_this,tname);
}

void *Star_SRPI_LuaL_TestUData(void *c_this,VS_INT32 narg, const VS_CHAR *tname)
{
    return g_star_CoreFunctionTbl->SRPI_LuaL_TestUData(c_this,narg,tname);
}

const VS_CHAR *Star_SRPI_LuaL_ToLString(void *c_this,VS_INT32 idx, VS_INT32 *len)
{
    return g_star_CoreFunctionTbl->SRPI_LuaL_ToLString(c_this,idx,len);
}

const VS_CHAR *Star_SRPI_LuaL_TypeName(void *c_this,VS_INT32 index)
{
    return g_star_CoreFunctionTbl->SRPI_LuaL_TypeName(c_this,index);
}

void Star_SRPI_LuaL_UnRef(void *c_this,VS_INT32 t, VS_INT32 ref)
{
    g_star_CoreFunctionTbl->SRPI_LuaL_UnRef(c_this,t,ref);
}

void Star_SRPI_LuaL_Where(void *c_this,VS_INT32 lvl)
{
    g_star_CoreFunctionTbl->SRPI_LuaL_Where(c_this,lvl);
}

void *Star_SRPI_GetControlService(void *c_this)
{
    return g_star_CoreFunctionTbl->SRPI_GetControlService(c_this);
}

VS_BOOL Star_SRPI_RegLuaFuncFilter(void *c_this, void *Object, VS_LuaFuncFilterProc Filter, VS_UWORD Para)
{
    return g_star_CoreFunctionTbl->SRPI_RegLuaFuncFilter(c_this,Object,Filter,Para);
}

VS_BOOL Star_SRPI_UnRegLuaFuncFilter(void *c_this, void *Object, VS_LuaFuncFilterProc Filter, VS_UWORD Para )
{
    return g_star_CoreFunctionTbl->SRPI_UnRegLuaFuncFilter(c_this,Object,Filter,Para);
}

VS_BOOL Star_SRPI_RegNewFunctionCallBack(void *c_this, void *Object, VS_NewFunctionCallBackProc callback, VS_UWORD Para)
{
    return g_star_CoreFunctionTbl->SRPI_RegNewFunctionCallBack(c_this,Object,callback,Para);
}

VS_BOOL Star_SRPI_UnRegNewFunctionCallBack(void *c_this, void *Object, VS_NewFunctionCallBackProc callback, VS_UWORD Para )
{
    return g_star_CoreFunctionTbl->SRPI_UnRegNewFunctionCallBack(c_this,Object,callback,Para);
}

VS_BOOL Star_SRPI_IsRegLuaFunc(void *c_this, void *Object, const VS_CHAR *FuncName, void *FuncAddress, VS_UWORD Para)
{
    return g_star_CoreFunctionTbl->SRPI_IsRegLuaFunc(c_this,Object,FuncName,FuncAddress,Para);
}

void *Star_SRPI_IMallocStaticObject(void *c_this,void *ParentObject,OBJECTATTRIBUTEINDEX AttributeIndex,VS_UUID *ObjectClassID,VS_PARAPKGPTR InitBuf)
{
    return g_star_CoreFunctionTbl->SRPI_IMallocStaticObject(c_this,ParentObject,AttributeIndex,ObjectClassID,InitBuf);
}

void *Star_SRPI_IMallocStaticObjectEx(void *c_this,VS_UUID *ObjectID,void *ParentObject,OBJECTATTRIBUTEINDEX AttributeIndex,VS_UUID *ObjectClassID,VS_PARAPKGPTR InitBuf)
{
    return g_star_CoreFunctionTbl->SRPI_IMallocStaticObjectEx(c_this,ObjectID,ParentObject,AttributeIndex,ObjectClassID,InitBuf);
}

void *Star_SRPI_IMallocGlobalObject(void *c_this,void *ParentObject,OBJECTATTRIBUTEINDEX AttributeIndex,VS_UUID *ObjectClassID,VS_PARAPKGPTR InitBuf,VS_ULONG ClientID)
{
    return g_star_CoreFunctionTbl->SRPI_IMallocGlobalObject(c_this,ParentObject,AttributeIndex,ObjectClassID,InitBuf,ClientID);
}

void *Star_SRPI_IMallocGlobalObjectEx(void *c_this,VS_UUID *ObjectID,void *ParentObject,OBJECTATTRIBUTEINDEX AttributeIndex,VS_UUID *ObjectClassID,VS_PARAPKGPTR InitBuf,VS_ULONG ClientID)
{
    return g_star_CoreFunctionTbl->SRPI_IMallocGlobalObjectEx(c_this,ObjectID,ParentObject,AttributeIndex,ObjectClassID,InitBuf,ClientID);
}

void *Star_SRPI_IMallocObject(void *c_this,void *ParentObject,OBJECTATTRIBUTEINDEX AttributeIndex,VS_UUID *ObjectClassID,VS_PARAPKGPTR InitBuf)
{
    return g_star_CoreFunctionTbl->SRPI_IMallocObject(c_this,ParentObject,AttributeIndex,ObjectClassID,InitBuf);
}

void *Star_SRPI_IMallocObjectEx(void *c_this,VS_UUID *ObjectID,void *ParentObject,OBJECTATTRIBUTEINDEX AttributeIndex,VS_UUID *ObjectClassID,VS_PARAPKGPTR InitBuf)
{
    return g_star_CoreFunctionTbl->SRPI_IMallocObjectEx(c_this,ObjectID,ParentObject,AttributeIndex,ObjectClassID,InitBuf);
}

void *Star_SRPI_IMallocObjectL(void *c_this,VS_UUID *ObjectClassID,VS_PARAPKGPTR InitBuf)
{
    return g_star_CoreFunctionTbl->SRPI_IMallocObjectL(c_this,ObjectClassID,InitBuf);
}

void *Star_SRPI_IMallocObjectLEx(void *c_this,VS_UUID *ObjectID,VS_UUID *ObjectClassID,VS_PARAPKGPTR InitBuf)
{
    return g_star_CoreFunctionTbl->SRPI_IMallocObjectLEx(c_this,ObjectID,ObjectClassID,InitBuf);
}

void *Star_SRPI_IMallocClientObject(void *c_this,void *ParentObject,OBJECTATTRIBUTEINDEX AttributeIndex,VS_UUID *ObjectClassID,VS_PARAPKGPTR InitBuf,VS_ULONG ClientID)
{
    return g_star_CoreFunctionTbl->SRPI_IMallocClientObject(c_this,ParentObject,AttributeIndex,ObjectClassID,InitBuf,ClientID);
}

void *Star_SRPI_IMallocClientObjectEx(void *c_this,VS_UUID *ObjectID,void *ParentObject,OBJECTATTRIBUTEINDEX AttributeIndex,VS_UUID *ObjectClassID,VS_PARAPKGPTR InitBuf,VS_ULONG ClientID)
{
    return g_star_CoreFunctionTbl->SRPI_IMallocClientObjectEx(c_this,ObjectID,ParentObject,AttributeIndex,ObjectClassID,InitBuf,ClientID);
}

VS_BOOL Star_SRPI_LoadRawModule(void *c_this,const VS_CHAR *ScriptInterface,const VS_CHAR *ModuleName,const VS_CHAR *FileOrString,VS_BOOL IsString,VS_CHAR **ErrorInfo)
{
    return g_star_CoreFunctionTbl->SRPI_LoadRawModule(c_this,ScriptInterface,ModuleName,FileOrString,IsString,ErrorInfo);
}

VS_BOOL Star_SRPI_LoadRawModuleEx(void *c_this,const VS_CHAR *ScriptInterface,const VS_CHAR *ModuleName,void *Object,VS_CHAR **ErrorInfo)
{
    return g_star_CoreFunctionTbl->SRPI_LoadRawModuleEx(c_this,ScriptInterface,ModuleName,Object,ErrorInfo);
}

VS_BOOL Star_SRPI_AttachRawContext(void *c_this,void *Object,const VS_CHAR *ScriptInterface,const VS_CHAR *ContextName, VS_BOOL IsClass, const VS_CHAR *ContextInfo)
{
    return g_star_CoreFunctionTbl->SRPI_AttachRawContext(c_this,Object,ScriptInterface,ContextName,IsClass,ContextInfo);
}

void Star_SRPI_DetachRawContext(void *c_this,void *Object,VS_BOOL CallUnLockGC)
{
    g_star_CoreFunctionTbl->SRPI_DetachRawContext(c_this,Object,CallUnLockGC);
}

VS_CHAR *Star_SRPI_GetRawContextType(void *c_this,void *Object,VS_CHAR **ScriptInterface)
{
    return g_star_CoreFunctionTbl->SRPI_GetRawContextType(c_this,Object,ScriptInterface);
}

VS_BOOL Star_SRPI_CreateRawContextBuf(void *c_this,void *Object,const VS_CHAR *ScriptInterface,VS_INT8 *ContextBuf,VS_INT32 ContextBufSize)
{
    return g_star_CoreFunctionTbl->SRPI_CreateRawContextBuf(c_this,Object,ScriptInterface,ContextBuf,ContextBufSize);
}

void *Star_SRPI_GetRawContextBuf(void *c_this,void *Object,const VS_CHAR *ScriptInterface)
{
    return g_star_CoreFunctionTbl->SRPI_GetRawContextBuf(c_this,Object,ScriptInterface);
}

VS_BOOL Star_SRPI_HasRawContext(void *c_this,void *Object)
{
    return g_star_CoreFunctionTbl->SRPI_HasRawContext(c_this,Object);
}

VS_BOOL Star_SRPI_RawContextEquals(void *c_this,void *Object1,void *Object2)
{
    return g_star_CoreFunctionTbl->SRPI_RawContextEquals(c_this,Object1,Object2);
}

void *Star_SRPI_NewRawProxy(void *c_this,const VS_CHAR *ScriptInterface,void *AttachObject,const VS_CHAR *AttachFunction,const VS_CHAR *ProyInfo,VS_INT32 ProxyType)
{
    return g_star_CoreFunctionTbl->SRPI_NewRawProxy(c_this,ScriptInterface,AttachObject,AttachFunction,ProyInfo,ProxyType);
}

void *Star_SRPI_NewRawProxyEx(void *c_this,void *Object,const VS_CHAR *ScriptInterface,const VS_CHAR *AttachFunction,const VS_CHAR *ProyInfo)
{
    return g_star_CoreFunctionTbl->SRPI_NewRawProxyEx(c_this,Object,ScriptInterface,AttachFunction,ProyInfo);
}

VS_CHAR *Star_SRPI_CreateRawProxyCode(void *c_this, const VS_CHAR *ScriptInterface,const VS_CHAR *NewPackageName,const VS_CHAR *Imports,const VS_CHAR *NewClassName,const VS_CHAR *BaseClass, const VS_CHAR *Methods, const VS_CHAR *Interface )
{
    return g_star_CoreFunctionTbl->SRPI_CreateRawProxyCode(c_this,ScriptInterface,NewPackageName,Imports,NewClassName,BaseClass,Methods,Interface);
}

void *Star_SRPI_ImportRawContext(void *c_this,const VS_CHAR *ScriptInterface,const VS_CHAR *ContextName, VS_BOOL IsClass, const VS_CHAR *ContextInfo)
{
    return g_star_CoreFunctionTbl->SRPI_ImportRawContext(c_this,ScriptInterface,ContextName,IsClass,ContextInfo);
}

void *Star_SRPI_AssignRawObject(void *c_this, void *Object,void *RawObject )
{
    return g_star_CoreFunctionTbl->SRPI_AssignRawObject(c_this,Object,RawObject);
}

VS_PARAPKGPTR Star_SRPI_GetInitPara(void *c_this,void *Object)
{
    return g_star_CoreFunctionTbl->SRPI_GetInitPara(c_this,Object);
}

void* Star_SRPI_NewScriptRawType(void *c_this, VS_INT32 RawType, VS_BOOL *IsParaPkg )
{
    return g_star_CoreFunctionTbl->SRPI_NewScriptRawType(c_this,RawType,IsParaPkg);
}

VS_BOOL Star_SRPI_SetScriptRawType(void *c_this,void *Object,VS_INT32 RawType)
{
    return g_star_CoreFunctionTbl->SRPI_SetScriptRawType(c_this,Object,RawType);
}

VS_INT32 Star_SRPI_GetScriptRawType(void *c_this,void *Object)
{
    return g_star_CoreFunctionTbl->SRPI_GetScriptRawType(c_this,Object);
}

VS_BOOL Star_SRPI_RegRawLuaSetValueFunc(void *c_this, void *Object, VS_LuaSetValueProc SetValueProc, VS_UWORD Para )
{
    return g_star_CoreFunctionTbl->SRPI_RegRawLuaSetValueFunc(c_this,Object,SetValueProc,Para);
}

void *Star_SRPI_GetRawLuaSetValueFunc(void *c_this, void *Object, const VS_CHAR *ValueName,VS_UWORD *Para )
{
    return g_star_CoreFunctionTbl->SRPI_GetRawLuaSetValueFunc(c_this,Object,ValueName,Para);
}

VS_BOOL Star_SRPI_UnRegRawLuaSetValueFunc(void *c_this, void *Object, VS_LuaSetValueProc SetValueProc, VS_UWORD Para )
{
    return g_star_CoreFunctionTbl->SRPI_UnRegRawLuaSetValueFunc(c_this,Object,SetValueProc,Para);
}

void Star_SRPI_AddRefEx(void *c_this,void *Object)
{
    g_star_CoreFunctionTbl->SRPI_AddRefEx(c_this,Object);
}

void Star_SRPI_DelRefEx(void *c_this,void *Object)
{
    g_star_CoreFunctionTbl->SRPI_DelRefEx(c_this,Object);
}

void Star_SRPI_ReleaseOwner(void *c_this)
{
    g_star_CoreFunctionTbl->SRPI_ReleaseOwner(c_this);
}

VS_BOOL Star_SRPI_ReleaseOwnerEx(void *c_this,void *Object)
{
    return g_star_CoreFunctionTbl->SRPI_ReleaseOwnerEx(c_this,Object);
}

VS_BOOL Star_SRPI_ReleaseOwnerExForScript(void *c_this,const VS_CHAR *ScriptInterface,void *Object)
{
    return g_star_CoreFunctionTbl->SRPI_ReleaseOwnerExForScript(c_this,ScriptInterface,Object);
}

void Star_SRPI_CaptureOwnerExForScript(void *c_this,const VS_CHAR *ScriptInterface,void *Object)
{
    g_star_CoreFunctionTbl->SRPI_CaptureOwnerExForScript(c_this,ScriptInterface,Object);
}

VS_INT32 Star_SRPI_GetRefEx(void *c_this,void *Object)
{
    return g_star_CoreFunctionTbl->SRPI_GetRefEx(c_this,Object);
}

VS_CHAR *Star_SRPI_GetRefInfo(void *c_this,void *Object)
{
    return g_star_CoreFunctionTbl->SRPI_GetRefInfo(c_this,Object);
}

VS_INT32 Star_SRPI_GetLastError(void *c_this)
{
    return g_star_CoreFunctionTbl->SRPI_GetLastError(c_this);
}

VS_CHAR *Star_SRPI_GetLastErrorInfo(void *c_this,VS_UINT32 *LineIndex,VS_CHAR **SourceName)
{
    return g_star_CoreFunctionTbl->SRPI_GetLastErrorInfo(c_this,LineIndex,SourceName);
}

void *Star_SRPI_CreateAtomicFunctionSimpleEx(void *c_this,void *AtomicObject, const VS_CHAR *FunctionName,const VS_CHAR *Attribute, void *FuncAddress, VS_CHAR **ErrorInfo)
{
    return g_star_CoreFunctionTbl->SRPI_CreateAtomicFunctionSimpleEx(c_this,AtomicObject,FunctionName,Attribute,FuncAddress,ErrorInfo);
}

void *Star_SRPI_LuaIsFunctionDefined(void *c_this, void *Object, const VS_CHAR *FuncName, VS_BOOL IncludeRawOrDefaultFunction )
{
    return g_star_CoreFunctionTbl->SRPI_LuaIsFunctionDefined(c_this,Object,FuncName,IncludeRawOrDefaultFunction);
}

void *Star_SRPI_LuaToRaw(void *c_this,VS_INT32 Index,VS_BOOL IsClass)
{
    return g_star_CoreFunctionTbl->SRPI_LuaToRaw(c_this,Index,IsClass);
}

VS_BOOL Star_SRPI_LuaTableToParaPkg(void *c_this,VS_INT32 Index,void *ParaPkg,VS_BOOL TableCanBeWrap)
{
    return g_star_CoreFunctionTbl->SRPI_LuaTableToParaPkg(c_this,Index,ParaPkg,TableCanBeWrap);
}

VS_BOOL Star_SRPI_ScriptSetBoolIndex(void *c_this,void *Object,VS_INT32 Index,VS_BOOL Value)
{
    return g_star_CoreFunctionTbl->SRPI_ScriptSetBoolIndex(c_this,Object,Index,Value);
}

VS_BOOL Star_SRPI_ScriptSetIntIndex(void *c_this,void *Object,VS_INT32 Index,VS_INT32 Value)
{
    return g_star_CoreFunctionTbl->SRPI_ScriptSetIntIndex(c_this,Object,Index,Value);
}

VS_BOOL Star_SRPI_ScriptSetNumberIndex(void *c_this,void *Object,VS_INT32 Index,VS_FLOAT Value)
{
    return g_star_CoreFunctionTbl->SRPI_ScriptSetNumberIndex(c_this,Object,Index,Value);
}

VS_BOOL Star_SRPI_ScriptSetStrIndex(void *c_this,void *Object,VS_INT32 Index,const VS_CHAR *Value)
{
    return g_star_CoreFunctionTbl->SRPI_ScriptSetStrIndex(c_this,Object,Index,Value);
}

VS_BOOL Star_SRPI_ScriptSetObjectIndex(void *c_this,void *Object,VS_INT32 Index,VS_UINT8 Type,VS_UWORD Value)
{
    return g_star_CoreFunctionTbl->SRPI_ScriptSetObjectIndex(c_this,Object,Index,Type,Value);
}

VS_BOOL Star_SRPI_ScriptGetBoolIndex(void *c_this,void *Object,VS_INT32 Index)
{
    return g_star_CoreFunctionTbl->SRPI_ScriptGetBoolIndex(c_this,Object,Index);
}

VS_INT32 Star_SRPI_ScriptGetIntIndex(void *c_this,void *Object,VS_INT32 Index)
{
    return g_star_CoreFunctionTbl->SRPI_ScriptGetIntIndex(c_this,Object,Index);
}

VS_FLOAT Star_SRPI_ScriptGetNumberIndex(void *c_this,void *Object,VS_INT32 Index)
{
    return g_star_CoreFunctionTbl->SRPI_ScriptGetNumberIndex(c_this,Object,Index);
}

VS_CHAR *Star_SRPI_ScriptGetStrIndex(void *c_this,void *Object,VS_INT32 Index)
{
    return g_star_CoreFunctionTbl->SRPI_ScriptGetStrIndex(c_this,Object,Index);
}

VS_UWORD Star_SRPI_ScriptGetObjectIndex(void *c_this,void *Object,VS_INT32 Index,VS_UINT8 *RetType)
{
    return g_star_CoreFunctionTbl->SRPI_ScriptGetObjectIndex(c_this,Object,Index,RetType);
}

VS_UWORD Star_SRPI_ScriptGetRawObject(void *c_this,void *Object,const VS_CHAR *AttributeName,VS_UINT8 *RetType)
{
    return g_star_CoreFunctionTbl->SRPI_ScriptGetRawObject(c_this,Object,AttributeName,RetType);
}

VS_UWORD Star_SRPI_ScriptGetRawObjectIndex(void *c_this,void *Object,VS_INT32 Index,VS_UINT8 *RetType)
{
    return g_star_CoreFunctionTbl->SRPI_ScriptGetRawObjectIndex(c_this,Object,Index,RetType);
}

void Star_SRPI_SetReturnRawFlag(void *c_this,void *Object,VS_BOOL ReturnRawFlag)
{
    g_star_CoreFunctionTbl->SRPI_SetReturnRawFlag(c_this,Object,ReturnRawFlag);
}

VS_BOOL Star_SRPI_GetReturnRawFlag(void *c_this,void *Object)
{
    return g_star_CoreFunctionTbl->SRPI_GetReturnRawFlag(c_this,Object);
}

VS_BOOL Star_SRPI_LuaSyncCall(void *c_this, void *Object, const VS_CHAR *ScriptName, VS_INT32 nArgs,VS_INT32 nOutArgs )
{
    return g_star_CoreFunctionTbl->SRPI_LuaSyncCall(c_this,Object,ScriptName,nArgs,nOutArgs);
}

void Star_SRPI_LuaPushInt64(void *c_this,VS_INT64 Value)
{
    g_star_CoreFunctionTbl->SRPI_LuaPushInt64(c_this,Value);
}

VS_INT64 Star_SRPI_LuaToInt64(void *c_this, VS_INT32 Index )
{
    return g_star_CoreFunctionTbl->SRPI_LuaToInt64(c_this,Index);
}

VS_BOOL Star_SRPI_LuaIsInt64(void *c_this, VS_INT32 Index )
{
    return g_star_CoreFunctionTbl->SRPI_LuaIsInt64(c_this,Index);
}

void Star_SRPI_LuaPushUWord(void *c_this,VS_UWORD Value)
{
    g_star_CoreFunctionTbl->SRPI_LuaPushUWord(c_this,Value);
}

VS_UWORD Star_SRPI_LuaToUWord(void *c_this,VS_INT32 Index )
{
    return g_star_CoreFunctionTbl->SRPI_LuaToUWord(c_this,Index);
}

VS_BOOL Star_SRPI_LuaIsUWord(void *c_this,VS_INT32 Index )
{
    return g_star_CoreFunctionTbl->SRPI_LuaIsUWord(c_this,Index);
}

VS_INT64 Star_SRPI_SRemoteCallInt64Var(void *c_this,VS_ULONG WaitTime,VS_ULONG ClientID,VS_ULONG *RetCode,void *Object,VS_UUID *FunctionID,va_list argList)
{
    return g_star_CoreFunctionTbl->SRPI_SRemoteCallInt64Var(c_this,WaitTime,ClientID,RetCode,Object,FunctionID,argList);
}

VS_DOUBLE Star_SRPI_SRemoteCallDoubleVar(void *c_this,VS_ULONG WaitTime,VS_ULONG ClientID,VS_ULONG *RetCode,void *Object,VS_UUID *FunctionID,va_list argList)
{
    return g_star_CoreFunctionTbl->SRPI_SRemoteCallDoubleVar(c_this,WaitTime,ClientID,RetCode,Object,FunctionID,argList);
}

VS_DOUBLE Star_SRPI_CallDoubleVar(void *c_this,void *Object,const VS_CHAR *FunctionName,va_list argList)
{
    return g_star_CoreFunctionTbl->SRPI_CallDoubleVar(c_this,Object,FunctionName,argList);
}

VS_INT64 Star_SRPI_CallInt64Var(void *c_this,void *Object,const VS_CHAR *FunctionName,va_list argList)
{
    return g_star_CoreFunctionTbl->SRPI_CallInt64Var(c_this,Object,FunctionName,argList);
}

VS_INT64 Star_SRPI_GetInt64(void *c_this,void *Object,const VS_CHAR *AttributeName)
{
    return g_star_CoreFunctionTbl->SRPI_GetInt64(c_this,Object,AttributeName);
}

VS_INT64 Star_SRPI_GetInt64Ex(void *c_this,void *Object,OBJECTATTRIBUTEINDEX AttributeIndex)
{
    return g_star_CoreFunctionTbl->SRPI_GetInt64Ex(c_this,Object,AttributeIndex);
}

VS_DOUBLE Star_SRPI_GetDouble(void *c_this,void *Object,const VS_CHAR *AttributeName)
{
    return g_star_CoreFunctionTbl->SRPI_GetDouble(c_this,Object,AttributeName);
}

VS_DOUBLE Star_SRPI_GetDoubleEx(void *c_this,void *Object,OBJECTATTRIBUTEINDEX AttributeIndex)
{
    return g_star_CoreFunctionTbl->SRPI_GetDoubleEx(c_this,Object,AttributeIndex);
}

VS_INT64 Star_SRPI_ScriptCallInt64Var(void *c_this,void *Object,VS_ULONG *RetCode,const VS_CHAR *FunctionName,const VS_CHAR *TypeSet,va_list argList)
{
    return g_star_CoreFunctionTbl->SRPI_ScriptCallInt64Var(c_this,Object,RetCode,FunctionName,TypeSet,argList);
}

VS_DOUBLE Star_SRPI_ScriptCallDoubleVar(void *c_this,void *Object,VS_ULONG *RetCode,const VS_CHAR *FunctionName,const VS_CHAR *TypeSet,va_list argList)
{
    return g_star_CoreFunctionTbl->SRPI_ScriptCallDoubleVar(c_this,Object,RetCode,FunctionName,TypeSet,argList);
}

VS_INT64 Star_SRPI_ScriptSRCallInt64Var(void *c_this,VS_ULONG WaitTime,VS_ULONG ClientID,VS_ULONG *RetCode,void *Object, const VS_CHAR *ScriptName,const VS_CHAR *TypeSet,va_list argList)
{
    return g_star_CoreFunctionTbl->SRPI_ScriptSRCallInt64Var(c_this,WaitTime,ClientID,RetCode,Object,ScriptName,TypeSet,argList);
}

VS_DOUBLE Star_SRPI_ScriptSRCallDoubleVar(void *c_this,VS_ULONG WaitTime,VS_ULONG ClientID,VS_ULONG *RetCode,void *Object, const VS_CHAR *ScriptName,const VS_CHAR *TypeSet,va_list argList)
{
    return g_star_CoreFunctionTbl->SRPI_ScriptSRCallDoubleVar(c_this,WaitTime,ClientID,RetCode,Object,ScriptName,TypeSet,argList);
}

VS_BOOL Star_SRPI_ScriptSetInt64(void *c_this,void *Object,const VS_CHAR *AttributeName,VS_INT64 Value)
{
    return g_star_CoreFunctionTbl->SRPI_ScriptSetInt64(c_this,Object,AttributeName,Value);
}

VS_BOOL Star_SRPI_ScriptSetDouble(void *c_this,void *Object,const VS_CHAR *AttributeName,VS_DOUBLE Value)
{
    return g_star_CoreFunctionTbl->SRPI_ScriptSetDouble(c_this,Object,AttributeName,Value);
}

VS_INT64 Star_SRPI_ScriptGetInt64(void *c_this,void *Object,const VS_CHAR *AttributeName)
{
    return g_star_CoreFunctionTbl->SRPI_ScriptGetInt64(c_this,Object,AttributeName);
}

VS_DOUBLE Star_SRPI_ScriptGetDouble(void *c_this,void *Object,const VS_CHAR *AttributeName)
{
    return g_star_CoreFunctionTbl->SRPI_ScriptGetDouble(c_this,Object,AttributeName);
}

VS_BOOL Star_SRPI_ScriptSetInt64Index(void *c_this,void *Object,VS_INT32 Index,VS_INT64 Value)
{
    return g_star_CoreFunctionTbl->SRPI_ScriptSetInt64Index(c_this,Object,Index,Value);
}

VS_BOOL Star_SRPI_ScriptSetDoubleIndex(void *c_this,void *Object,VS_INT32 Index,VS_DOUBLE Value)
{
    return g_star_CoreFunctionTbl->SRPI_ScriptSetDoubleIndex(c_this,Object,Index,Value);
}

VS_INT64 Star_SRPI_ScriptGetInt64Index(void *c_this,void *Object,VS_INT32 Index)
{
    return g_star_CoreFunctionTbl->SRPI_ScriptGetInt64Index(c_this,Object,Index);
}

VS_DOUBLE Star_SRPI_ScriptGetDoubleIndex(void *c_this,void *Object,VS_INT32 Index)
{
    return g_star_CoreFunctionTbl->SRPI_ScriptGetDoubleIndex(c_this,Object,Index);
}

VS_INT64 Star_SRPI_ScriptGetRawObjectInt64(void *c_this,void *Object,const VS_CHAR *AttributeName)
{
    return g_star_CoreFunctionTbl->SRPI_ScriptGetRawObjectInt64(c_this,Object,AttributeName);
}

VS_DOUBLE Star_SRPI_ScriptGetRawObjectDouble(void *c_this,void *Object,const VS_CHAR *AttributeName)
{
    return g_star_CoreFunctionTbl->SRPI_ScriptGetRawObjectDouble(c_this,Object,AttributeName);
}

VS_INT64 Star_SRPI_ScriptGetRawObjectIndexInt64(void *c_this,void *Object,VS_INT32 Index)
{
    return g_star_CoreFunctionTbl->SRPI_ScriptGetRawObjectIndexInt64(c_this,Object,Index);
}

VS_DOUBLE Star_SRPI_ScriptGetRawObjectIndexDouble(void *c_this,void *Object,VS_INT32 Index)
{
    return g_star_CoreFunctionTbl->SRPI_ScriptGetRawObjectIndexDouble(c_this,Object,Index);
}

VS_INT64 Star_SRPI_ScriptCallInt64Var2(void *c_this,void *Object,VS_ULONG *RetCode,const VS_CHAR *FunctionName,const VS_CHAR *TypeSet,VS_UINT8 *RetType,va_list argList)
{
    return g_star_CoreFunctionTbl->SRPI_ScriptCallInt64Var2(c_this,Object,RetCode,FunctionName,TypeSet,RetType,argList);
}

VS_DOUBLE Star_SRPI_ScriptCallDoubleVar2(void *c_this,void *Object,VS_ULONG *RetCode,const VS_CHAR *FunctionName,const VS_CHAR *TypeSet,VS_UINT8 *RetType,va_list argList)
{
    return g_star_CoreFunctionTbl->SRPI_ScriptCallDoubleVar2(c_this,Object,RetCode,FunctionName,TypeSet,RetType,argList);
}

VS_INT64 Star_SRPI_ScriptSRCallInt64Var2(void *c_this,VS_ULONG WaitTime,VS_ULONG ClientID,VS_ULONG *RetCode,void *Object, const VS_CHAR *ScriptName,const VS_CHAR *TypeSet,VS_UINT8 *RetType,va_list argList)
{
    return g_star_CoreFunctionTbl->SRPI_ScriptSRCallInt64Var2(c_this,WaitTime,ClientID,RetCode,Object,ScriptName,TypeSet,RetType,argList);
}

VS_DOUBLE Star_SRPI_ScriptSRCallDoubleVar2(void *c_this,VS_ULONG WaitTime,VS_ULONG ClientID,VS_ULONG *RetCode,void *Object, const VS_CHAR *ScriptName,const VS_CHAR *TypeSet,VS_UINT8 *RetType,va_list argList)
{
    return g_star_CoreFunctionTbl->SRPI_ScriptSRCallDoubleVar2(c_this,WaitTime,ClientID,RetCode,Object,ScriptName,TypeSet,RetType,argList);
}

VS_INT64 Star_SRPI_ScriptSyncCallInt64Var(void *c_this,void *Object,VS_ULONG *RetCode,const VS_CHAR *FunctionName,const VS_CHAR *TypeSet,va_list argList)
{
    return g_star_CoreFunctionTbl->SRPI_ScriptSyncCallInt64Var(c_this,Object,RetCode,FunctionName,TypeSet,argList);
}

VS_DOUBLE Star_SRPI_ScriptSyncCallDoubleVar(void *c_this,void *Object,VS_ULONG *RetCode,const VS_CHAR *FunctionName,const VS_CHAR *TypeSet,va_list argList)
{
    return g_star_CoreFunctionTbl->SRPI_ScriptSyncCallDoubleVar(c_this,Object,RetCode,FunctionName,TypeSet,argList);
}

VS_INT64 Star_SRPI_ScriptSyncCallInt64Var2(void *c_this,void *Object,VS_ULONG *RetCode,const VS_CHAR *FunctionName,const VS_CHAR *TypeSet,VS_UINT8 *RetType,va_list argList)
{
    return g_star_CoreFunctionTbl->SRPI_ScriptSyncCallInt64Var2(c_this,Object,RetCode,FunctionName,TypeSet,RetType,argList);
}

VS_DOUBLE Star_SRPI_ScriptSyncCallDoubleVar2(void *c_this,void *Object,VS_ULONG *RetCode,const VS_CHAR *FunctionName,const VS_CHAR *TypeSet,VS_UINT8 *RetType,va_list argList)
{
    return g_star_CoreFunctionTbl->SRPI_ScriptSyncCallDoubleVar2(c_this,Object,RetCode,FunctionName,TypeSet,RetType,argList);
}

VS_UWORD Star_SRPI_ScriptGetObjectEx(void *c_this,void *Object,const VS_CHAR *AttributeName,VS_UINT8 *RetType,VS_DOUBLE *RetDouble,VS_INT64 *RetInt64)
{
    return g_star_CoreFunctionTbl->SRPI_ScriptGetObjectEx(c_this,Object,AttributeName,RetType,RetDouble,RetInt64);
}

VS_UWORD Star_SRPI_ScriptGetObjectIndexEx(void *c_this,void *Object,VS_INT32 Index,VS_UINT8 *RetType,VS_DOUBLE *RetDouble,VS_INT64 *RetInt64)
{
    return g_star_CoreFunctionTbl->SRPI_ScriptGetObjectIndexEx(c_this,Object,Index,RetType,RetDouble,RetInt64);
}

VS_UWORD Star_SRPI_ScriptGetRawObjectEx(void *c_this,void *Object,const VS_CHAR *AttributeName,VS_UINT8 *RetType,VS_DOUBLE *RetDouble,VS_INT64 *RetInt64)
{
    return g_star_CoreFunctionTbl->SRPI_ScriptGetRawObjectEx(c_this,Object,AttributeName,RetType,RetDouble,RetInt64);
}

VS_UWORD Star_SRPI_ScriptGetRawObjectIndexEx(void *c_this,void *Object,VS_INT32 Index,VS_UINT8 *RetType,VS_DOUBLE *RetDouble,VS_INT64 *RetInt64)
{
    return g_star_CoreFunctionTbl->SRPI_ScriptGetRawObjectIndexEx(c_this,Object,Index,RetType,RetDouble,RetInt64);
}

void Star_SRPI_RemoteCallRspInt64(void *c_this,void *Object,VS_ULONG ClientID,VS_ULONG RemoteCallID,const VS_CHAR *RemoteCallName,VS_UINT16 RemoteSourceTag,VS_ULONG RetCode,VS_INT64 RetValue, void *RemoteAttach)
{
    g_star_CoreFunctionTbl->SRPI_RemoteCallRspInt64(c_this,Object,ClientID,RemoteCallID,RemoteCallName,RemoteSourceTag,RetCode,RetValue,RemoteAttach);
}

void Star_SRPI_RemoteCallRspDouble(void *c_this,void *Object,VS_ULONG ClientID,VS_ULONG RemoteCallID,const VS_CHAR *RemoteCallName,VS_UINT16 RemoteSourceTag,VS_ULONG RetCode,VS_DOUBLE RetValue, void *RemoteAttach)
{
    g_star_CoreFunctionTbl->SRPI_RemoteCallRspDouble(c_this,Object,ClientID,RemoteCallID,RemoteCallName,RemoteSourceTag,RetCode,RetValue,RemoteAttach);
}

void *Star_SRPI_RawToParaPkg(void *c_this,void *Object)
{
    return g_star_CoreFunctionTbl->SRPI_RawToParaPkg(c_this,Object);
}

VS_CHAR *Star_SRPI_GetNameEx(void *c_this,void *Object)
{
    return g_star_CoreFunctionTbl->SRPI_GetNameEx(c_this,Object);
}

void Star_SRPMF_Release(void *c_this)
{
    g_star_CoreFunctionTbl->SRPMF_Release(c_this);
}

VS_INT32 Star_SRPMF_GetNumber(void *c_this)
{
    return g_star_CoreFunctionTbl->SRPMF_GetNumber(c_this);
}

VS_BOOL Star_SRPMF_InsertFile(void *c_this, const VS_CHAR *FileName, VS_UINT8 *FileBuf, VS_ULONG FileBufSize, VS_UUID *FileID )
{
    return g_star_CoreFunctionTbl->SRPMF_InsertFile(c_this,FileName,FileBuf,FileBufSize,FileID);
}

VS_BOOL Star_SRPMF_SetFromDisk(void *c_this, VS_CHAR *FileListInfo, const VS_CHAR *DiskFileName, VS_ULONG FileStartOffset )
{
    return g_star_CoreFunctionTbl->SRPMF_SetFromDisk(c_this,FileListInfo,DiskFileName,FileStartOffset);
}

VS_BOOL Star_SRPMF_SetFromMemory(void *c_this, VS_CHAR *FileListInfo, VS_UINT8 *FileMemory, VS_ULONG FileStartOffset )
{
    return g_star_CoreFunctionTbl->SRPMF_SetFromMemory(c_this,FileListInfo,FileMemory,FileStartOffset);
}

VS_BOOL Star_SRPMF_IsExist(void *c_this, const VS_CHAR *FileName )
{
    return g_star_CoreFunctionTbl->SRPMF_IsExist(c_this,FileName);
}

VS_ULONG Star_SRPMF_GetSize(void *c_this, const VS_CHAR *FileName  )
{
    return g_star_CoreFunctionTbl->SRPMF_GetSize(c_this,FileName);
}

VS_ULONG Star_SRPMF_Read(void *c_this, const VS_CHAR *FileName, VS_UINT8 *ReadBuf  )
{
    return g_star_CoreFunctionTbl->SRPMF_Read(c_this,FileName,ReadBuf);
}

void Star_SRPMF_AddRef(void *c_this)
{
    g_star_CoreFunctionTbl->SRPMF_AddRef(c_this);
}

VS_INT32 Star_SRPMF_GetRef(void *c_this)
{
    return g_star_CoreFunctionTbl->SRPMF_GetRef(c_this);
}

void Star_SRPMF_ReleaseOwner(void *c_this)
{
    g_star_CoreFunctionTbl->SRPMF_ReleaseOwner(c_this);
}

void Star_SRPFD_Release(void *c_this)
{
    g_star_CoreFunctionTbl->SRPFD_Release(c_this);
}

VS_BOOL Star_SRPFD_Open(void *c_this,VS_ULONG SectorNumberPerCluster,const VS_CHAR *FileName,VS_BOOL CreateFlag)
{
    return g_star_CoreFunctionTbl->SRPFD_Open(c_this,SectorNumberPerCluster,FileName,CreateFlag);
}

VS_ULONG Star_SRPFD_GetEmptySector(void *c_this)
{
    return g_star_CoreFunctionTbl->SRPFD_GetEmptySector(c_this);
}

void Star_SRPFD_ClearSectorList(void *c_this, VS_INT32 SectorNumber, VS_ULONG *SectorIndex )
{
    g_star_CoreFunctionTbl->SRPFD_ClearSectorList(c_this,SectorNumber,SectorIndex);
}

void Star_SRPFD_FlushDirtySector(void *c_this)
{
    g_star_CoreFunctionTbl->SRPFD_FlushDirtySector(c_this);
}

VS_BOOL Star_SRPFD_IsSectorEmpty(void *c_this, VS_ULONG SectorIndex )
{
    return g_star_CoreFunctionTbl->SRPFD_IsSectorEmpty(c_this,SectorIndex);
}

VS_BOOL Star_SRPFD_SetSectorInUse(void *c_this, VS_ULONG SectorIndex )
{
    return g_star_CoreFunctionTbl->SRPFD_SetSectorInUse(c_this,SectorIndex);
}

VS_ULONG Star_SRPFD_WriteSector(void *c_this,VS_ULONG SectorIndex,VS_UINT8 *DataHeader,VS_ULONG NextSector,VS_ULONG DataOffset,VS_ULONG DataSize,VS_INT8 *DataBuf)
{
    return g_star_CoreFunctionTbl->SRPFD_WriteSector(c_this,SectorIndex,DataHeader,NextSector,DataOffset,DataSize,DataBuf);
}

VS_ULONG Star_SRPFD_ReadSector(void *c_this,VS_ULONG SectorIndex,VS_UINT8 *DataHeader,VS_ULONG *NextSector,VS_ULONG DataOffset,VS_ULONG DataSize,VS_INT8 *DataBuf)
{
    return g_star_CoreFunctionTbl->SRPFD_ReadSector(c_this,SectorIndex,DataHeader,NextSector,DataOffset,DataSize,DataBuf);
}

VS_BOOL Star_SRPFD_ReadFileHeader(void *c_this,VS_UINT8 *Buf)
{
    return g_star_CoreFunctionTbl->SRPFD_ReadFileHeader(c_this,Buf);
}

VS_BOOL Star_SRPFD_SaveFileHeader(void *c_this,VS_UINT8 *Buf)
{
    return g_star_CoreFunctionTbl->SRPFD_SaveFileHeader(c_this,Buf);
}

VS_BOOL Star_SRPFD_GetNextSectorIndex(void *c_this, VS_ULONG SectorIndex,VS_UINT8 *DataHeader, VS_ULONG *NextSector )
{
    return g_star_CoreFunctionTbl->SRPFD_GetNextSectorIndex(c_this,SectorIndex,DataHeader,NextSector);
}

VS_ULONG Star_SRPFD_GetSize(void *c_this,VS_ULONG *DiskSize)
{
    return g_star_CoreFunctionTbl->SRPFD_GetSize(c_this,DiskSize);
}

void Star_SRPFD_Clear(void *c_this)
{
    g_star_CoreFunctionTbl->SRPFD_Clear(c_this);
}

void Star_SRPFD_Close(void *c_this)
{
    g_star_CoreFunctionTbl->SRPFD_Close(c_this);
}

void Star_SRPFD_AddRef(void *c_this)
{
    g_star_CoreFunctionTbl->SRPFD_AddRef(c_this);
}

VS_INT32 Star_SRPFD_GetRef(void *c_this)
{
    return g_star_CoreFunctionTbl->SRPFD_GetRef(c_this);
}

void Star_SRPFD_ReleaseOwner(void *c_this)
{
    g_star_CoreFunctionTbl->SRPFD_ReleaseOwner(c_this);
}

void Star_SRPCS_Release(void *c_this)
{
    g_star_CoreFunctionTbl->SRPCS_Release(c_this);
}

VS_INT8 *Star_SRPCS_AnsiToUnicode(void *c_this,VS_UINT32 CodePage,const VS_CHAR *ToCode,const VS_INT8 *AnsiStr,VS_INT32 StrLength)
{
    return g_star_CoreFunctionTbl->SRPCS_AnsiToUnicode(c_this,CodePage,ToCode,AnsiStr,StrLength);
}

VS_INT8 *Star_SRPCS_UnicodeToAnsi(void *c_this,const VS_CHAR *FromCode,VS_UINT32 CodePage,const VS_INT8 *WideStr,VS_INT32 StrLength,VS_INT32 BytesPerChar)
{
    return g_star_CoreFunctionTbl->SRPCS_UnicodeToAnsi(c_this,FromCode,CodePage,WideStr,StrLength,BytesPerChar);
}

VS_INT8 *Star_SRPCS_AnsiToUTF8(void *c_this,const VS_INT8 *AnsiStr,VS_INT32 StrLength)
{
    return g_star_CoreFunctionTbl->SRPCS_AnsiToUTF8(c_this,AnsiStr,StrLength);
}

VS_INT8 *Star_SRPCS_UTF8ToAnsi(void *c_this,const VS_INT8 *UTFStr,VS_INT32 StrLength)
{
    return g_star_CoreFunctionTbl->SRPCS_UTF8ToAnsi(c_this,UTFStr,StrLength);
}

VS_INT8 *Star_SRPCS_ToOSPlatString(void *c_this,const VS_INT8 *Str,VS_INT32 StrLength)
{
    return g_star_CoreFunctionTbl->SRPCS_ToOSPlatString(c_this,Str,StrLength);
}

VS_INT8 *Star_SRPCS_ToOSPlatStringEx(void *c_this,VS_UINT32 OSType,const VS_INT8 *Str,VS_INT32 StrLength)
{
    return g_star_CoreFunctionTbl->SRPCS_ToOSPlatStringEx(c_this,OSType,Str,StrLength);
}

void Star_SRPCS_FreeBuf(void *c_this,void *Buf)
{
    g_star_CoreFunctionTbl->SRPCS_FreeBuf(c_this,Buf);
}

void Star_SRPCS_vs_reg_beginlock(void *c_this)
{
    g_star_CoreFunctionTbl->SRPCS_vs_reg_beginlock(c_this);
}

void Star_SRPCS_vs_reg_endlock(void *c_this)
{
    g_star_CoreFunctionTbl->SRPCS_vs_reg_endlock(c_this);
}

VS_ULONG Star_SRPCS_vs_reg_createkeyex(void *c_this,vs_reg_hkey hKey,const VS_CHAR *SubKey,const VS_CHAR *Class,vs_reg_hkey *RetKey,VS_ULONG *DisPosition)
{
    return g_star_CoreFunctionTbl->SRPCS_vs_reg_createkeyex(c_this,hKey,SubKey,Class,RetKey,DisPosition);
}

VS_ULONG Star_SRPCS_vs_reg_closekey(void *c_this,vs_reg_hkey hKey)
{
    return g_star_CoreFunctionTbl->SRPCS_vs_reg_closekey(c_this,hKey);
}

VS_ULONG Star_SRPCS_vs_reg_setvalue(void *c_this,vs_reg_hkey hKey,const VS_CHAR *ValueName,VS_ULONG Type,const VS_CHAR *Value,VS_ULONG ValueSize)
{
    return g_star_CoreFunctionTbl->SRPCS_vs_reg_setvalue(c_this,hKey,ValueName,Type,Value,ValueSize);
}

VS_ULONG Star_SRPCS_vs_reg_openkeyex(void *c_this,vs_reg_hkey hKey,const VS_CHAR *SubKey,vs_reg_hkey *RetKey)
{
    return g_star_CoreFunctionTbl->SRPCS_vs_reg_openkeyex(c_this,hKey,SubKey,RetKey);
}

VS_ULONG Star_SRPCS_vs_reg_queryvalueex(void *c_this,vs_reg_hkey hKey,const VS_CHAR *ValueName,VS_ULONG *Type,VS_UINT8 *DataBuf,VS_ULONG *DataBufSize)
{
    return g_star_CoreFunctionTbl->SRPCS_vs_reg_queryvalueex(c_this,hKey,ValueName,Type,DataBuf,DataBufSize);
}

VS_ULONG Star_SRPCS_vs_reg_deletekeyex(void *c_this,vs_reg_hkey hKey,const VS_CHAR *SubKey)
{
    return g_star_CoreFunctionTbl->SRPCS_vs_reg_deletekeyex(c_this,hKey,SubKey);
}

VS_ULONG Star_SRPCS_vs_reg_enumkey(void *c_this,vs_reg_hkey hKey,VS_ULONG Index,VS_CHAR *NameBuf,VS_ULONG NameBufSize)
{
    return g_star_CoreFunctionTbl->SRPCS_vs_reg_enumkey(c_this,hKey,Index,NameBuf,NameBufSize);
}

VS_INT32 Star_SRPCS_GetCharBytes(void *c_this,const VS_INT8 *Buf)
{
    return g_star_CoreFunctionTbl->SRPCS_GetCharBytes(c_this,Buf);
}

VS_INT8 *Star_SRPCS_ToAnsi(void *c_this,const VS_CHAR *Locale,const VS_INT8 *Str)
{
    return g_star_CoreFunctionTbl->SRPCS_ToAnsi(c_this,Locale,Str);
}

VS_INT8 *Star_SRPCS_FromAnsi(void *c_this,const VS_CHAR *Locale,const VS_INT8 *Str)
{
    return g_star_CoreFunctionTbl->SRPCS_FromAnsi(c_this,Locale,Str);
}

VS_INT8 *Star_SRPCS_vs_iconv(void *c_this,const VS_CHAR *FromLocale,const VS_CHAR *ToLocale,const VS_INT8 *InBuf,VS_INT32 InBufSize,VS_INT32 *RetBufSize)
{
    return g_star_CoreFunctionTbl->SRPCS_vs_iconv(c_this,FromLocale,ToLocale,InBuf,InBufSize,RetBufSize);
}

VS_INT8 *Star_SRPCS_AnsiToUnicodeEx(void *c_this,VS_UINT32 CodePage,const VS_CHAR *ToCode,const VS_INT8 *AnsiStr,VS_INT32 StrLength,VS_INT32 *RetCharLength)
{
    return g_star_CoreFunctionTbl->SRPCS_AnsiToUnicodeEx(c_this,CodePage,ToCode,AnsiStr,StrLength,RetCharLength);
}

VS_INT8 *Star_SRPCS_UnicodeToAnsiEx(void *c_this,const VS_CHAR *FromCode,VS_UINT32 CodePage,const VS_INT8 *WideStr,VS_INT32 StrLength,VS_INT32 BytesPerChar,VS_INT32 *RetCharLength)
{
    return g_star_CoreFunctionTbl->SRPCS_UnicodeToAnsiEx(c_this,FromCode,CodePage,WideStr,StrLength,BytesPerChar,RetCharLength);
}

VS_INT8 *Star_SRPCS_AnsiToUTF8Ex(void *c_this,const VS_INT8 *AnsiStr,VS_INT32 StrLength,VS_INT32 *RetCharLength)
{
    return g_star_CoreFunctionTbl->SRPCS_AnsiToUTF8Ex(c_this,AnsiStr,StrLength,RetCharLength);
}

VS_INT8 *Star_SRPCS_UTF8ToAnsiEx(void *c_this,const VS_INT8 *UTFStr,VS_INT32 StrLength,VS_INT32 *RetCharLength)
{
    return g_star_CoreFunctionTbl->SRPCS_UTF8ToAnsiEx(c_this,UTFStr,StrLength,RetCharLength);
}

void Star_SRPFP_Release(void *c_this)
{
    g_star_CoreFunctionTbl->SRPFP_Release(c_this);
}

void Star_SRPFP_Clear(void *c_this)
{
    g_star_CoreFunctionTbl->SRPFP_Clear(c_this);
}

VS_INT32 Star_SRPFP_GetNumber(void *c_this)
{
    return g_star_CoreFunctionTbl->SRPFP_GetNumber(c_this);
}

VS_UINT8 Star_SRPFP_GetType(void *c_this,VS_INT32 Index)
{
    return g_star_CoreFunctionTbl->SRPFP_GetType(c_this,Index);
}

VS_UWORD Star_SRPFP_GetValue(void *c_this,VS_INT32 Index)
{
    return g_star_CoreFunctionTbl->SRPFP_GetValue(c_this,Index);
}

VS_BOOL Star_SRPFP_SetValue(void *c_this,VS_INT32 Index,VS_UINT8 In_Type,VS_UWORD In_Para)
{
    return g_star_CoreFunctionTbl->SRPFP_SetValue(c_this,Index,In_Type,In_Para);
}

VS_BOOL Star_SRPFP_Call(void *c_this,void *Object,VS_UUID *FunctionID,VS_UWORD *RetValue,VS_UINT8 *RetType)
{
    return g_star_CoreFunctionTbl->SRPFP_Call(c_this,Object,FunctionID,RetValue,RetType);
}

void *Star_SRPFP_Dup(void *c_this)
{
    return g_star_CoreFunctionTbl->SRPFP_Dup(c_this);
}

void Star_SRPFP_AddRef(void *c_this)
{
    g_star_CoreFunctionTbl->SRPFP_AddRef(c_this);
}

VS_INT32 Star_SRPFP_GetRef(void *c_this)
{
    return g_star_CoreFunctionTbl->SRPFP_GetRef(c_this);
}

void Star_SRPFP_ReleaseOwner(void *c_this)
{
    g_star_CoreFunctionTbl->SRPFP_ReleaseOwner(c_this);
}

VS_FLOAT Star_SRPFP_GetFloatValue(void *c_this,VS_INT32 Index)
{
    return g_star_CoreFunctionTbl->SRPFP_GetFloatValue(c_this,Index);
}

VS_DOUBLE Star_SRPFP_GetDoubleValue(void *c_this,VS_INT32 Index)
{
    return g_star_CoreFunctionTbl->SRPFP_GetDoubleValue(c_this,Index);
}

VS_INT64 Star_SRPFP_GetInt64Value(void *c_this,VS_INT32 Index)
{
    return g_star_CoreFunctionTbl->SRPFP_GetInt64Value(c_this,Index);
}

VS_BOOL Star_SRPFP_SetFloatValue(void *c_this,VS_INT32 Index,VS_FLOAT In_Para)
{
    return g_star_CoreFunctionTbl->SRPFP_SetFloatValue(c_this,Index,In_Para);
}

VS_BOOL Star_SRPFP_SetDoubleValue(void *c_this,VS_INT32 Index,VS_DOUBLE In_Para)
{
    return g_star_CoreFunctionTbl->SRPFP_SetDoubleValue(c_this,Index,In_Para);
}

VS_BOOL Star_SRPFP_SetInt64Value(void *c_this,VS_INT32 Index,VS_INT64 In_Para)
{
    return g_star_CoreFunctionTbl->SRPFP_SetInt64Value(c_this,Index,In_Para);
}

VS_BOOL Star_SRPFP_CallEx(void *c_this,void *Object,VS_UUID *FunctionID,VS_UWORD *RetValue,VS_DOUBLE *RetDouble,VS_INT64 *RetInt64,VS_UINT8 *RetType)
{
    return g_star_CoreFunctionTbl->SRPFP_CallEx(c_this,Object,FunctionID,RetValue,RetDouble,RetInt64,RetType);
}

VS_BOOL Star_SRPFP_SetValueFromLua(void *c_this,VS_INT32 Index,VS_INT32 LuaIndex)
{
    return g_star_CoreFunctionTbl->SRPFP_SetValueFromLua(c_this,Index,LuaIndex);
}

void Star_SRPLock_Release(void *c_this)
{
    g_star_CoreFunctionTbl->SRPLock_Release(c_this);
}

void Star_SRPLock_Lock(void *c_this)
{
    g_star_CoreFunctionTbl->SRPLock_Lock(c_this);
}

void Star_SRPLock_UnLock(void *c_this)
{
    g_star_CoreFunctionTbl->SRPLock_UnLock(c_this);
}

void Star_StarCore_Release(void *c_this)
{
    g_star_CoreFunctionTbl->StarCore_Release(c_this);
}

VS_INT32 Star_StarCore_GetInitResult(void *c_this)
{
    return g_star_CoreFunctionTbl->StarCore_GetInitResult(c_this);
}

void Star_StarCore_SetWnd(void *c_this,VS_HWND In_hWnd)
{
    g_star_CoreFunctionTbl->StarCore_SetWnd(c_this,In_hWnd);
}

void Star_StarCore_SetWndActive( void *c_this,VS_BOOL In_ActiveFlag )
{
    g_star_CoreFunctionTbl->StarCore_SetWndActive(c_this,In_ActiveFlag);
}

void *Star_StarCore_CreateService(void *c_this,const VS_CHAR *ServiceName,VSImportServiceDef *ImportService)
{
    return g_star_CoreFunctionTbl->StarCore_CreateService(c_this,ServiceName,ImportService);
}

void *Star_StarCore_CreateService1(void *c_this,const VS_CHAR *ServicePath,const VS_CHAR *ServiceName,VS_UUID *ServiceID,const VS_CHAR *RootPass,VSImportServiceDef *ImportService)
{
    return g_star_CoreFunctionTbl->StarCore_CreateService1(c_this,ServicePath,ServiceName,ServiceID,RootPass,ImportService);
}

void *Star_StarCore_CreateService2(void *c_this,const VS_CHAR *ServicePath,const VS_CHAR *ServiceName,VS_UUID *ServiceID,const VS_CHAR *RootPass,VS_INT32 FrameInterval,VS_INT32 NetPkgSize,VS_INT32 UploadPkgSize,VS_INT32 DownloadPkgSize,VS_INT32 DataUpPkgSize,VS_INT32 DataDownPkgSize,VSImportServiceDef *ImportService)
{
    return g_star_CoreFunctionTbl->StarCore_CreateService2(c_this,ServicePath,ServiceName,ServiceID,RootPass,FrameInterval,NetPkgSize,UploadPkgSize,DownloadPkgSize,DataUpPkgSize,DataDownPkgSize,ImportService);
}

void Star_StarCore_Flush(void *c_this,VS_BOOL WaitFlag)
{
    g_star_CoreFunctionTbl->StarCore_Flush(c_this,WaitFlag);
}

void Star_StarCore_MsgLoop(void *c_this,VS_SRPMsgLoopExitProc SRPMsgLoopExitProc)
{
    g_star_CoreFunctionTbl->StarCore_MsgLoop(c_this,SRPMsgLoopExitProc);
}

void *Star_StarCore_GetControlInterface(void *c_this)
{
    return g_star_CoreFunctionTbl->StarCore_GetControlInterface(c_this);
}

void *Star_StarCore_GetBasicInterface(void *c_this)
{
    return g_star_CoreFunctionTbl->StarCore_GetBasicInterface(c_this);
}

void Star_SRPMM_memset(void *Buf,VS_INT8 c,VS_INT32 Len)
{
    g_star_CoreFunctionTbl->SRPMM_memset(Buf,c,Len);
}

void Star_SRPMM_memcpy(void *DesBuf,const void *SrcBuf,VS_INT32 Len)
{
    g_star_CoreFunctionTbl->SRPMM_memcpy(DesBuf,SrcBuf,Len);
}

VS_INT32 Star_SRPMM_strlen(VS_INT8 *Buf)
{
    return g_star_CoreFunctionTbl->SRPMM_strlen(Buf);
}

