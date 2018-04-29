#include "vsopenapi_c.h"
#include "vsopenapi_c_stub.h"
#include "stargo_native.h"

static VS_HANDLE hDllInstance;
static VSCore_RegisterCallBackInfoProc RegisterCallBackInfoProc = NULL;
static VSCore_UnRegisterCallBackInfoProc UnRegisterCallBackInfoProc = NULL;
static VSCore_InitProc VSInitProc = NULL;
static VSCore_TermProc VSTermProc = NULL;
static VSCore_TermExProc VSTermExProc = NULL;
static VSCore_HasInitProc HasInitProc = NULL;
static VSCore_QueryControlInterfaceProc QueryControlInterfaceProc = NULL;
static SRPControl_GetCFunctionTable_Proc Control_GetCFunctionTable;

void *StarGo_SRPControlInterface = NULL;
void *StarGo_SRPCoreShellInterface = NULL;

VS_INT32 StarGo_ScriptInterfaceIndex;

VS_BOOL StarGo_ModuleInitFlag = VS_FALSE;
static VS_BOOL ModuleLoadFlag = VS_FALSE;
VS_BOOL StarGo_ModuleLoadFromStarcore = VS_FALSE;

VS_CHAR  StarGo_g_ShareLibraryPath[512] = {0};
VS_CHAR  StarGo_g_CoreLibraryPath[512] = {0};
VS_CHAR  StarGo_g_CoreOperationPath[512] = {0};

/*-------------callback from go begin----*/
extern void GoScriptTerm();

extern VS_UWORD GoMsgCallBack(VS_ULONG ServiceGroupID, VS_ULONG uMsg, VS_UWORD wParam, VS_UWORD lParam, VS_BOOL *IsProcessed, VS_UWORD Para);
extern void GoSRPDispatchRequestCallBack();
extern void GoFreeScriptObject(VS_UWORD RefItem);
extern void GoObjectFreeNotify(void *Object,VS_UWORD RefItem);
extern void GoObjectIDChangeNotify(void *Object, VS_UWORD Para, VS_UUID *NewObjectID);
extern VS_INT32 GoSRPObject_ScriptCallBack(void *L);
extern VS_BOOL GoRawContext_LuaFuncFilter(void *object, void *ForWhichObject, VS_CHAR *FuncName, VS_UWORD Para);
extern VS_INT32 GoRawContext_GeneralFunction(void *L);

extern VS_CHAR *GoVSScript_GetRawContextType(VS_UWORD Para, VS_ULONG ServiceGroupIndex, void *object);
extern VS_PARAPKGPTR GoVSScript_RawToParaPkg( VS_UWORD Para, VS_ULONG ServiceGroupIndex,void *Object );
extern VS_BOOL GoVSScript_AttachRawContext(VS_UWORD Para, VS_ULONG ServiceGroupIndex, void *object, VS_CHAR *ContextName, VS_BOOL IsClass, VS_CHAR *ContextInfo);
extern VS_BOOL GoVSScript_InitRaw(VS_UWORD Para, void *BasicSRPInterface, void *SRPInterface);

extern VS_BOOL GoRawContext_RegGetValue(void *Object, void *ForWhichObject, VS_CHAR *Name, VS_UWORD Para, VS_BOOL GetAllRawAttributeFlag);
extern VS_BOOL GoRawContext_RegSetValue(void *Object, void *ForWhichObject, VS_CHAR *Name, VS_INT32 Index, VS_UWORD Para);

extern void GoInitFromStarCore();
/*-------------callback from go end------*/

static void stargo_starcore_ScriptTerm()
{
	if( StarGo_SRPControlInterface != NULL )
		Star_SRPControl_ClearScriptObject(StarGo_SRPControlInterface,stargo_FreeScriptObject, 0 );
	if( StarGo_ModuleInitFlag == VS_FALSE ){

		GoScriptTerm();
		
		ModuleLoadFlag = VS_FALSE;
		StarGo_ModuleInitFlag = VS_FALSE;
		if( StarGo_SRPCoreShellInterface != NULL )
			Star_SRPCS_Release(StarGo_SRPCoreShellInterface);
		StarGo_SRPCoreShellInterface = NULL;

		return;
	}
	
	GoScriptTerm();

	if( StarGo_SRPCoreShellInterface != NULL )
		Star_SRPCS_Release(StarGo_SRPCoreShellInterface);
	StarGo_SRPCoreShellInterface = NULL;

	ModuleLoadFlag = VS_FALSE;
	StarGo_ModuleInitFlag = VS_FALSE;
		
	if( StarGo_SRPControlInterface != NULL )
		Star_SRPControl_Release(StarGo_SRPControlInterface);
	StarGo_SRPControlInterface = NULL;

	return;
}

static VS_CHAR *stargo_VSScript_GetRawContextType(VS_UWORD Para, VS_ULONG ServiceGroupIndex, void *object)
{
	return GoVSScript_GetRawContextType(Para, ServiceGroupIndex, object);
}

static VS_PARAPKGPTR VSScript_RawToParaPkg( VS_UWORD Para, VS_ULONG ServiceGroupIndex,void *Object )
{
	return GoVSScript_RawToParaPkg( Para, ServiceGroupIndex,Object );
}

static VS_BOOL VSScript_AttachRawContext(VS_UWORD Para, VS_ULONG ServiceGroupIndex, void *object, VS_CHAR *ContextName, VS_BOOL IsClass, VS_CHAR *ContextInfo)
{
	return GoVSScript_AttachRawContext(Para,ServiceGroupIndex,object,ContextName,IsClass,ContextInfo);
}

static VS_BOOL VSScript_InitRaw(VS_UWORD Para, void *BasicSRPInterface, void *SRPInterface)
{
	return GoVSScript_InitRaw(Para,BasicSRPInterface,SRPInterface);
}

static VS_INT32 stargo_starcore_Register(VS_BOOL NeedUnLoad)
{
	struct StructOfVSScriptContext ScriptContext;

	if( StarGo_SRPControlInterface == NULL )
		return -1;
	memset(&ScriptContext,0,sizeof(struct StructOfVSScriptContext));
	ScriptContext.InitRawProc = VSScript_InitRaw;
	ScriptContext.GetRawContextTypeProc = stargo_VSScript_GetRawContextType;
	ScriptContext.AttachRawContextProc = VSScript_AttachRawContext;
	ScriptContext.RawToParaPkgProc = VSScript_RawToParaPkg;
#if VS_MAINVERSION < 2 || (VS_MAINVERSION == 2 && VS_SUBVERSION <= 82) || (VS_MAINVERSION == 2 && VS_SUBVERSION == 82 && VS_BUILDVERSION <= 259 )
	ScriptContext.Reserved1[0] = VS_TRUE;  /*--2.52--*/
#endif	
    if( NeedUnLoad == VS_TRUE )
	    Star_SRPControl_RegScriptInterface(StarGo_SRPControlInterface,"go", &ScriptContext, 0, stargo_starcore_ScriptTerm); 
	else
	    Star_SRPControl_RegScriptInterface(StarGo_SRPControlInterface,"go", &ScriptContext, 0, NULL); 
    return 0;
}

VS_ULONG stargo_starcore_Load()
{
	VS_CHAR ModuleName[512];
	VS_INT32 Result;
	
	if( StarGo_ModuleInitFlag == VS_TRUE )
	    return 0;	
	if( vs_string_strlen(StarGo_g_CoreLibraryPath) == 0){
		VS_CHAR EnvModuleName[128];
		VS_CHAR CurrentPath[512];
			
		vs_dir_getcwd(CurrentPath,512);
		if( vs_get_env("SRPMODULE",EnvModuleName,128) == VS_FALSE )
			sprintf(EnvModuleName,"libstarcore");
		if( vs_string_strlen(StarGo_g_ShareLibraryPath) == 0){
			sprintf(ModuleName,"%s/%s%s",CurrentPath,EnvModuleName,VS_MODULEEXT);
			hDllInstance = vs_dll_open( ModuleName );
			//if( vs_file_exist(ModuleName) == VS_FALSE )
			if( hDllInstance == NULL ){
			    sprintf(ModuleName,"%s%s%s",VS_COREPATH,EnvModuleName,VS_MODULEEXT);
				hDllInstance = vs_dll_open( ModuleName );
			}
		}else{
			sprintf(ModuleName,"%s/%s%s",StarGo_g_ShareLibraryPath,EnvModuleName,VS_MODULEEXT);
			hDllInstance = vs_dll_open( ModuleName );
		}
		if( hDllInstance == NULL ){
			sprintf(ModuleName,"%s/%s%s",CurrentPath,EnvModuleName,VS_MODULEEXT);
			hDllInstance = vs_dll_open( ModuleName );
			if( hDllInstance == NULL ){
			    sprintf(ModuleName,"%s%s%s",VS_COREPATH,EnvModuleName,VS_MODULEEXT);
				hDllInstance = vs_dll_open( ModuleName );
			}
		}
	}else{
		VS_CHAR EnvModuleName[128];
		VS_CHAR CurrentPath[512];
		
		vs_dir_getcwd(CurrentPath,512);			
		if( vs_get_env("SRPMODULE",EnvModuleName,128) == VS_FALSE )
			sprintf(EnvModuleName,"libstarcore");
		sprintf(ModuleName,"%s/%s%s",StarGo_g_CoreLibraryPath,EnvModuleName,VS_MODULEEXT);
		hDllInstance = vs_dll_open( ModuleName );
		if( hDllInstance == NULL ){
			if( vs_string_strlen(StarGo_g_ShareLibraryPath) == 0){
				sprintf(ModuleName,"%s/%s%s",CurrentPath,EnvModuleName,VS_MODULEEXT);
				hDllInstance = vs_dll_open( ModuleName );
				if( hDllInstance == NULL ){
				    sprintf(ModuleName,"%s%s%s",VS_COREPATH,EnvModuleName,VS_MODULEEXT);
					hDllInstance = vs_dll_open( ModuleName );
				}
			}else{
				sprintf(ModuleName,"%s/%s%s",StarGo_g_ShareLibraryPath,EnvModuleName,VS_MODULEEXT);
				hDllInstance = vs_dll_open( ModuleName );
			}
			if( hDllInstance == NULL ){
				sprintf(ModuleName,"%s/%s%s",CurrentPath,EnvModuleName,VS_MODULEEXT);
				hDllInstance = vs_dll_open( ModuleName );
				if( hDllInstance == NULL ){
					sprintf(ModuleName,"%s%s%s",VS_COREPATH,EnvModuleName,VS_MODULEEXT);
					hDllInstance = vs_dll_open( ModuleName );
				}
			}
		}
	}
	if( hDllInstance != NULL ){		
		ModuleLoadFlag = VS_TRUE;
			
		RegisterCallBackInfoProc = (VSCore_RegisterCallBackInfoProc)vs_dll_sym( hDllInstance, VSCORE_REGISTERCALLBACKINFO_NAME );
		UnRegisterCallBackInfoProc = (VSCore_UnRegisterCallBackInfoProc)vs_dll_sym( hDllInstance, VSCORE_UNREGISTERCALLBACKINFO_NAME );
		VSInitProc = (VSCore_InitProc)vs_dll_sym( hDllInstance, VSCORE_INIT_NAME );
		VSTermProc = (VSCore_TermProc)vs_dll_sym( hDllInstance, VSCORE_TERM_NAME );
		VSTermExProc = (VSCore_TermExProc)vs_dll_sym( hDllInstance, VSCORE_TERMEX_NAME );
		HasInitProc = (VSCore_HasInitProc)vs_dll_sym( hDllInstance, VSCORE_HASINIT_NAME );
		QueryControlInterfaceProc = (VSCore_QueryControlInterfaceProc)vs_dll_sym( hDllInstance, VSCORE_QUERYCONTROLINTERFACE_NAME );						
        Control_GetCFunctionTable = (SRPControl_GetCFunctionTable_Proc)vs_dll_sym(hDllInstance,"SRPControl_GetCFunctionTable");
		
		//--Init
		if( HasInitProc() == VS_FALSE ){
			VS_STARCONFIGEX m_config;

			memset(&m_config,0,sizeof(VS_STARCONFIGEX));
			VS_STRNCPY(m_config.ShareLibraryPath,StarGo_g_ShareLibraryPath,512);
			VS_STRNCPY(m_config.CoreLibraryPath,StarGo_g_CoreLibraryPath,512);
			VS_STRNCPY(m_config.CoreOperationPath,StarGo_g_CoreOperationPath,512);
			Result = VSInitProc( VS_TRUE, VS_TRUE, "",0, "", 0,&m_config );
			if( Result != VSINIT_ERROR ){
				StarGo_SRPControlInterface = QueryControlInterfaceProc();
				g_star_CoreFunctionTbl = (struct StructOfVSStarCoreInterfaceTable *)Control_GetCFunctionTable(StarGo_SRPControlInterface);
				
				stargo_starcore_Register(VS_TRUE);
				StarGo_ScriptInterfaceIndex = g_star_CoreFunctionTbl->SRPControl_GetScriptInterfaceIndex(StarGo_SRPControlInterface,"go");								
				
				StarGo_SRPCoreShellInterface = g_star_CoreFunctionTbl->SRPControl_GetCoreShellInterface(StarGo_SRPControlInterface);	            
				StarGo_ModuleInitFlag = VS_TRUE;
			}
		}else{
			StarGo_SRPControlInterface = QueryControlInterfaceProc();
			StarGo_ModuleInitFlag = VS_TRUE;
		}
	}else
		return -1;
	return 0;	
}

VS_ULONG stargo_starcore_Init(VS_BOOL ServerFlag, VS_BOOL ShowMenuFlag,VS_BOOL ShowOutWndFlag, VS_BOOL SRPPrintFlag, VS_CHAR *DebugInterface, VS_INT32 DebugPortNumber, VS_CHAR *ClientInterface, VS_INT32 ClientPortNumber)
{
	VS_INT32 Result;
	VS_STARCONFIGEX m_config;

	if( ModuleLoadFlag == VS_FALSE ){
		return 0;
	}
	if( StarGo_ModuleLoadFromStarcore == VS_TRUE ){
		return 0; /*--load from starcore, can not init */
	}
	memset(&m_config,0,sizeof(VS_STARCONFIGEX));
	VS_STRNCPY(m_config.ShareLibraryPath,StarGo_g_ShareLibraryPath,512);
	VS_STRNCPY(m_config.CoreLibraryPath,StarGo_g_CoreLibraryPath,512);
	VS_STRNCPY(m_config.CoreOperationPath,StarGo_g_CoreOperationPath,512);
	Result = VSInitProc( ServerFlag, SRPPrintFlag, DebugInterface,DebugPortNumber, ClientInterface, ClientPortNumber,&m_config );
	if( Result != VSINIT_ERROR )
		StarGo_ModuleInitFlag = VS_TRUE;	
	return 0;
}

/*-----------------------------------------------------------------------------*/
extern void *StarGo_GetFunctionTbl_FromContol(void *SRPControl);

SRPDLLEXPORT VS_BOOL SRPAPI star_go_ScriptInit(VS_CHAR *ScriptName, VS_CHAR *Para, VSCore_RegisterCallBackInfoProc In_RegisterCallBackInfoProc, VSCore_UnRegisterCallBackInfoProc In_UnRegisterCallBackInfoProc, VSCore_InitProc In_InitProc, VSCore_TermProc In_TermProc, VSCore_TermExProc In_TermExProc, VSCore_HasInitProc In_HasInitProc, VSCore_QueryControlInterfaceProc In_QueryControlInterfaceProc, void *VirtualMachine)
{	
	if( vs_string_stricmp(ScriptName,"GO") != 0 ){
		return VS_FALSE;
	}
	
	StarGo_SRPControlInterface = In_QueryControlInterfaceProc();
	g_star_CoreFunctionTbl = StarGo_GetFunctionTbl_FromContol(StarGo_SRPControlInterface);
	
	/*--check version--*/
    if( g_star_CoreFunctionTbl -> CoreMainVerson < VS_MAINVERSION ){
		Star_SRPControl_Release(StarGo_SRPControlInterface);
		StarGo_SRPControlInterface = NULL;
		return VS_FALSE;
	}else if( g_star_CoreFunctionTbl -> CoreMainVerson == VS_MAINVERSION ){
		if( g_star_CoreFunctionTbl -> CoreSubVerson < VS_SUBVERSION ){
			Star_SRPControl_Release(StarGo_SRPControlInterface);
			StarGo_SRPControlInterface = NULL;			
 			return VS_FALSE;
		}else if( g_star_CoreFunctionTbl -> CoreSubVerson == VS_SUBVERSION ){
			if( g_star_CoreFunctionTbl -> CoreBuildVerson < VS_BUILDVERSION ){
				Star_SRPControl_Release(StarGo_SRPControlInterface);
				StarGo_SRPControlInterface = NULL;				
	 			return VS_FALSE	;		
			}
		}
	}
	
	RegisterCallBackInfoProc = In_RegisterCallBackInfoProc;
	UnRegisterCallBackInfoProc = In_UnRegisterCallBackInfoProc;
	VSInitProc = In_InitProc;
	VSTermProc = In_TermProc;
	VSTermExProc = In_TermExProc;
	HasInitProc = In_HasInitProc;
	QueryControlInterfaceProc = In_QueryControlInterfaceProc;	
					
	stargo_starcore_Register(VS_TRUE);
	StarGo_ScriptInterfaceIndex = g_star_CoreFunctionTbl->SRPControl_GetScriptInterfaceIndex(StarGo_SRPControlInterface,"go");								
				
	StarGo_SRPCoreShellInterface = g_star_CoreFunctionTbl->SRPControl_GetCoreShellInterface(StarGo_SRPControlInterface);	            

	StarGo_ModuleInitFlag = VS_TRUE;
	ModuleLoadFlag = VS_TRUE;
	StarGo_ModuleLoadFromStarcore = VS_TRUE;
	
	GoInitFromStarCore();
	
	return VS_TRUE;
}		

SRPDLLEXPORT VS_BOOL SRPAPI star_go_ScriptInit2(VS_CHAR *ScriptName, VS_CHAR *Para, VSCore_RegisterCallBackInfoProc In_RegisterCallBackInfoProc, VSCore_UnRegisterCallBackInfoProc In_UnRegisterCallBackInfoProc, VSCore_InitProc In_InitProc, VSCore_TermProc In_TermProc, VSCore_TermExProc In_TermExProc, VSCore_HasInitProc In_HasInitProc, VSCore_QueryControlInterfaceProc In_QueryControlInterfaceProc, struct StructOfVSStarCoreInterfaceTable *InterfaceTable, void *VirtualMachine)
{		
	StarGo_SRPControlInterface = In_QueryControlInterfaceProc();
	g_star_CoreFunctionTbl = InterfaceTable;	
	
	/*--check version--*/
    if( g_star_CoreFunctionTbl -> CoreMainVerson < VS_MAINVERSION ){
		Star_SRPControl_Release(StarGo_SRPControlInterface);
		StarGo_SRPControlInterface = NULL;
		return VS_FALSE;
	}else if( g_star_CoreFunctionTbl -> CoreMainVerson == VS_MAINVERSION ){
		if( g_star_CoreFunctionTbl -> CoreSubVerson < VS_SUBVERSION ){
			Star_SRPControl_Release(StarGo_SRPControlInterface);
			StarGo_SRPControlInterface = NULL;			
 			return VS_FALSE;
		}else if( g_star_CoreFunctionTbl -> CoreSubVerson == VS_SUBVERSION ){
			if( g_star_CoreFunctionTbl -> CoreBuildVerson < VS_BUILDVERSION ){
				Star_SRPControl_Release(StarGo_SRPControlInterface);
				StarGo_SRPControlInterface = NULL;				
	 			return VS_FALSE	;		
			}
		}
	}
	
	RegisterCallBackInfoProc = In_RegisterCallBackInfoProc;
	UnRegisterCallBackInfoProc = In_UnRegisterCallBackInfoProc;
	VSInitProc = In_InitProc;
	VSTermProc = In_TermProc;
	VSTermExProc = In_TermExProc;
	HasInitProc = In_HasInitProc;
	QueryControlInterfaceProc = In_QueryControlInterfaceProc;	
					
	stargo_starcore_Register(VS_TRUE);
	StarGo_ScriptInterfaceIndex = g_star_CoreFunctionTbl->SRPControl_GetScriptInterfaceIndex(StarGo_SRPControlInterface,"go");								
				
	StarGo_SRPCoreShellInterface = g_star_CoreFunctionTbl->SRPControl_GetCoreShellInterface(StarGo_SRPControlInterface);	            

	StarGo_ModuleInitFlag = VS_TRUE;
	ModuleLoadFlag = VS_TRUE;
	StarGo_ModuleLoadFromStarcore = VS_TRUE;
	
	GoInitFromStarCore();
	
	return VS_TRUE;
}		


SRPDLLEXPORT VS_BOOL SRPAPI StarCoreService_Init2(void *StarCore, struct StructOfVSStarCoreInterfaceTable *InterfaceTable )
{
	g_star_CoreFunctionTbl = InterfaceTable;
	StarGo_SRPControlInterface = Star_StarCore_GetControlInterface(StarCore);
	Star_SRPControl_AddRef(StarGo_SRPControlInterface);
		
	/*--check version--*/
    if( g_star_CoreFunctionTbl -> CoreMainVerson < VS_MAINVERSION ){
		Star_SRPControl_Release(StarGo_SRPControlInterface);
		StarGo_SRPControlInterface = NULL;
		return VS_FALSE;
	}else if( g_star_CoreFunctionTbl -> CoreMainVerson == VS_MAINVERSION ){
		if( g_star_CoreFunctionTbl -> CoreSubVerson < VS_SUBVERSION ){
			Star_SRPControl_Release(StarGo_SRPControlInterface);
			StarGo_SRPControlInterface = NULL;			
 			return VS_FALSE;
		}else if( g_star_CoreFunctionTbl -> CoreSubVerson == VS_SUBVERSION ){
			if( g_star_CoreFunctionTbl -> CoreBuildVerson < VS_BUILDVERSION ){
				Star_SRPControl_Release(StarGo_SRPControlInterface);
				StarGo_SRPControlInterface = NULL;				
	 			return VS_FALSE	;		
			}
		}
	}
	stargo_starcore_Register(VS_FALSE);
	//Star_SRPControl_SetScriptInterfaceIndex(StarGo_SRPControlInterface,"go");
	StarGo_ScriptInterfaceIndex = g_star_CoreFunctionTbl->SRPControl_GetScriptInterfaceIndex(StarGo_SRPControlInterface,"go");								
				
	StarGo_SRPCoreShellInterface = g_star_CoreFunctionTbl->SRPControl_GetCoreShellInterface(StarGo_SRPControlInterface);	            
	StarGo_ModuleInitFlag = VS_TRUE;
	ModuleLoadFlag = VS_TRUE;
	StarGo_ModuleLoadFromStarcore = VS_TRUE;
	
	GoInitFromStarCore();
	
	void *BasicSRPInterface = Star_StarCore_GetBasicInterface(StarCore);	
	void *SRPInterface = Star_SRPBasic_GetSRPInterface(BasicSRPInterface,Star_SRPBasic_QueryActiveService(BasicSRPInterface,NULL),"","");	
	if( SRPInterface != NULL ){
	    GoVSScript_InitRaw(0,BasicSRPInterface,SRPInterface);
		Star_SRPI_Release(SRPInterface);
	}
	
	return VS_TRUE + 1;  /*---should not unload the share library, valid for cle above 2.60 */
}

SRPDLLEXPORT void SRPAPI StarCoreService_Term2(void *StarCore, struct StructOfVSStarCoreInterfaceTable *InterfaceTable )
{
	stargo_starcore_ScriptTerm();
}

VS_INT64 stargo_CoreHandle()
{
	return (VS_INT64)hDllInstance;
}

VS_UWORD stargo_MsgCallBack( VS_ULONG ServiceGroupID, VS_ULONG uMsg, VS_UWORD wParam, VS_UWORD lParam, VS_BOOL *IsProcessed, VS_UWORD Para )
{
	return GoMsgCallBack(ServiceGroupID,uMsg,wParam,lParam,IsProcessed,Para );
}

void stargo_RegisterCallBackInfo( void* MsgCallBackProc, VS_UWORD MsgCallBackPara )
{
	if( RegisterCallBackInfoProc == NULL )
	    return;
	RegisterCallBackInfoProc((VS_MsgCallBackProc)MsgCallBackProc,MsgCallBackPara);
}
void stargo_UnRegisterCallBackInfo( void* MsgCallBackProc, VS_UWORD MsgCallBackPara )
{
	if( UnRegisterCallBackInfoProc == NULL )
	    return;
	UnRegisterCallBackInfoProc((VS_MsgCallBackProc)MsgCallBackProc,MsgCallBackPara);
}

void stargo_SRPDispatchRequestCallBack(VS_UWORD Para)
{
	GoSRPDispatchRequestCallBack();
}
 
void stargo_Term( )
{
	if( VSTermProc != NULL )
	    VSTermProc();
}

void stargo_TermEx( )
{
	if( VSTermExProc != NULL )
	    VSTermExProc();
}

void stargo_inituuid(VS_UUID *u)
{
	INIT_UUID( (*u) );
}

void *stargo_MovePointer(void *In,VS_INT32 Step)
{
	return (void *)(((VS_INT8 *)In) + Step);
}

VS_CHAR *stargo_GetCharByIndex(VS_CHAR *Ptr,VS_INT32 Index)
{
	return Ptr + Index;
}

void stargo_starcore_unLoad()
{
	if( StarGo_ModuleLoadFromStarcore == VS_TRUE )
	    return;
	if( VSTermExProc != NULL )
		VSTermExProc();
	if( hDllInstance != NULL )
		vs_dll_close(hDllInstance);
	hDllInstance = NULL;
	StarGo_ModuleInitFlag = VS_FALSE;	
}

VS_BOOL stargo_uuidisequal(VS_UUID *u1,VS_UUID *u2)
{
	return UUID_ISEQUAL((*u1),(*u2));
}

VS_BOOL stargo_uuidisvalid(VS_UUID *u)
{
	if( UUID_ISINVALID( (*u) ) )
	    return VS_TRUE;
	else
	    return VS_FALSE;
}

void *stargo_ToPointer64(VS_INT64 in)
{
	return (void *)in;
}

void *stargo_ToPointer(VS_UWORD in)
{
	return (void *)in;
}

void *stargo_GetUWordPointer(VS_UWORD in)
{
	return ((void **)in)[0];
}
void stargo_SetUWordPointer(VS_UWORD in,void *ptr)
{
	((void **)in)[0] = ptr;
}

VS_INT64 stargo_PointerToInt64(void *Ptr)
{
	return (VS_INT64)((VS_UINT64)((VS_UWORD)Ptr));
}

VS_UWORD stargo_PointerToUWord(void *Ptr)
{
	return (VS_UWORD)Ptr;
}

VS_CHAR *stargo_IPToString(SOCKADDR_IN *ip)
{
	static VS_CHAR Buf[256];
    sprintf(Buf,"%d.%d.%d.%d",((struct _in_addr *)&ip->sin_addr)->S_un.S_un_b.s_b1,
			((struct _in_addr *)&ip->sin_addr)->S_un.S_un_b.s_b2,
			((struct _in_addr *)&ip->sin_addr)->S_un.S_un_b.s_b3,
			((struct _in_addr *)&ip->sin_addr)->S_un.S_un_b.s_b4);	
	return Buf;
}

struct StructOfObjectRefInSrvGroup *stargo_MallocStructOfObjectRefInSrvGroup()
{
	return (struct StructOfObjectRefInSrvGroup *)malloc(sizeof(struct StructOfObjectRefInSrvGroup));
}

void stargo_FreeStructOfObjectRefInSrvGroup(struct StructOfObjectRefInSrvGroup *Val)
{
	if( Val == NULL )
	    return;
	free(Val);
}

VS_INT32 stargo_SizeOfStructOfGoRawContext()
{
	return sizeof(struct StructOfGoRawContext);
}

struct classRawContextRefItem *stargo_MallocclassRawContextRefItem()
{
	return (struct classRawContextRefItem *)malloc(sizeof(struct classRawContextRefItem));
}

struct StructOfGoRawContext_Para *stargo_MallocStructOfGoRawContext_Para()
{
	return (struct StructOfGoRawContext_Para *)malloc(sizeof(struct StructOfGoRawContext_Para));
}

void stargo_SRPI_ProcessError(void *c_this,VS_INT32 AlarmLevel,const VS_CHAR *SourceName,VS_INT32 LineIndex,const VS_CHAR *Info)
{
	g_star_CoreFunctionTbl->SRPI_ProcessError(c_this,AlarmLevel,SourceName,LineIndex,"%s",Info);
}

void stargo_SRPBasic_ProcessError(void *c_this,VS_INT32 AlarmLevel,const VS_CHAR *SourceName,VS_INT32 LineIndex,const VS_CHAR *Info)
{
	g_star_CoreFunctionTbl->SRPBasic_ProcessError(c_this,AlarmLevel,SourceName,LineIndex,"%s",Info);
}

void stargo_SRPControl_ProcessError(void *c_this,VS_INT32 AlarmLevel,const VS_CHAR *SourceName,VS_INT32 LineIndex,const VS_CHAR *Info)
{
	g_star_CoreFunctionTbl->SRPControl_ProcessError(c_this,AlarmLevel,SourceName,LineIndex,Info);
}

VS_UWORD stargo_SRPI_ScriptCall(void *c_this,void *Object,VS_ULONG *RetCode,const VS_CHAR *FunctionName,const VS_CHAR *TypeSet)
{
	return g_star_CoreFunctionTbl->SRPI_ScriptCall(c_this,Object,RetCode,FunctionName,TypeSet);
}

void stargo_FreeScriptObject(VS_UWORD Para, VS_UWORD ScriptObject)
{	
    GoFreeScriptObject(ScriptObject);
}

void stargo_ObjectIDChangeNotify(void *Object,VS_UWORD Para,VS_UUID *NewObjectID)
{
	GoObjectIDChangeNotify(Object,Para, NewObjectID);
}

void stargo_ObjectFreeNotify(void *Object,VS_UWORD Para)
{
	GoObjectFreeNotify(Object,Para);
}


VS_INT32 stargo_SRPObject_ScriptCallBack( void *L )
{
	return GoSRPObject_ScriptCallBack(L);
}

VS_INT32 stargo_VSScript_GoRawContext_GeneralFunction(void *L)
{
	return GoRawContext_GeneralFunction(L);
}

VS_BOOL stargo_VSScript_GoRawContext_LuaFuncFilter(void *object, void *ForWhichObject, VS_CHAR *FuncName, VS_UWORD Para)
{
	return GoRawContext_LuaFuncFilter(object,ForWhichObject,FuncName,Para);
}

VS_BOOL stargo_VSScript_GoRawContext_RegGetValue(void *Object, void *ForWhichObject, VS_CHAR *Name, VS_UWORD Para, VS_BOOL GetAllRawAttributeFlag)
{
	return GoRawContext_RegGetValue(Object,ForWhichObject,Name,Para,GetAllRawAttributeFlag);
}

VS_BOOL stargo_VSScript_GoRawContext_RegSetValue(void *Object, void *ForWhichObject, VS_CHAR *Name, VS_INT32 Index, VS_UWORD Para)
{
	return GoRawContext_RegSetValue(Object,ForWhichObject,Name,Index,Para);
}

void stargo_VSScript_GoRawContext_NewFunctionCallBack(void *Object, void *DesObject, VS_CHAR *FuncName, VS_UWORD Para)
{
	return;
}
